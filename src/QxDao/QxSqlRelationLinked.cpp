/****************************************************************************
**
** http://www.qxorm.com/
** Copyright (C) 2013 Lionel Marty (contact@qxorm.com)
**
** This file is part of the QxOrm library
**
** This software is provided 'as-is', without any express or implied
** warranty. In no event will the authors be held liable for any
** damages arising from the use of this software
**
** Commercial Usage
** Licensees holding valid commercial QxOrm licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Lionel Marty
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file 'license.gpl3.txt' included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met : http://www.gnu.org/copyleft/gpl.html
**
** If you are unsure which license is appropriate for your use, or
** if you have questions regarding the use of this file, please contact :
** contact@qxorm.com
**
****************************************************************************/

#include <QxPrecompiled.h>

#include <QxDao/QxSqlRelationLinked.h>
#include <QxDao/IxSqlQueryBuilder.h>

#include <QxCollection/QxCollectionIterator.h>

#include <QxTraits/is_valid_primary_key.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

QxSqlRelationLinked::QxSqlRelationLinked() : m_allRelationX(NULL), m_bRoot(true) { ; }

QxSqlRelationLinked::QxSqlRelationLinked(bool bRoot) : m_allRelationX(NULL), m_bRoot(bRoot) { ; }

QxSqlRelationLinked::~QxSqlRelationLinked() { ; }

qx_bool QxSqlRelationLinked::buildHierarchy(IxSqlRelationX * pRelationX, const QStringList & sRelationX)
{
   if (! pRelationX) { qAssert(false); return qx_bool(false); }
   m_allRelationX = pRelationX;
   m_relationLinkedX.clear();
   m_relationX.clear();

   Q_FOREACH(QString sRelation, sRelationX)
   {
      QString sKey;
      sRelation = sRelation.trimmed();
      int iJoin = QString(QX_LEFT_OUTER_JOIN).size();
      qAssert(iJoin == QString(QX_INNER_JOIN).size());
      qx::dao::sql_join::join_type eJoinType = qx::dao::sql_join::no_join;

      if (sRelation.left(iJoin) == QX_LEFT_OUTER_JOIN) { eJoinType = qx::dao::sql_join::left_outer_join; }
      else if (sRelation.left(iJoin) == QX_INNER_JOIN) { eJoinType = qx::dao::sql_join::inner_join; }
      int iOffset = ((eJoinType == qx::dao::sql_join::no_join) ? 0 : iJoin);
      int iPosLeftOuter = sRelation.indexOf(QX_LEFT_OUTER_JOIN, 1);
      int iPosInner = sRelation.indexOf(QX_INNER_JOIN, 1);
      int iPos = -1;

      if (iPosLeftOuter < 0) { iPos = iPosInner; }
      else if (iPosInner < 0) { iPos = iPosLeftOuter; }
      else { iPos = ((iPosLeftOuter < iPosInner) ? iPosLeftOuter : iPosInner); }

      if (iPos >= 0) { sKey = sRelation.mid(iOffset, (iPos - iOffset)); }
      else { sKey = sRelation.mid(iOffset); }
      sRelation.remove(0, (sKey.size() + iOffset));
      sKey = sKey.trimmed();
      sRelation = sRelation.trimmed();
      if (sKey.isEmpty()) { continue; }
      QStringList sNewRelationX = (sRelation.isEmpty() ? QStringList() : (QStringList() << sRelation));

      if (sKey == "*")
      {
         QxCollectionIterator<QString, IxSqlRelation *> itr(* m_allRelationX);
         while (itr.next())
         {
            qx_bool bResult = insertRelationToHierarchy(sNewRelationX, itr.key(), eJoinType);
            if (! bResult) { return bResult; }
         }
      }
      else
      {
         qx_bool bResult = insertRelationToHierarchy(sNewRelationX, sKey, eJoinType);
         if (! bResult) { return bResult; }
      }
   }

   return qx_bool(true);
}

qx_bool QxSqlRelationLinked::insertRelationToHierarchy(const QStringList & sRelationX, const QString & sKey, qx::dao::sql_join::join_type eJoinType)
{
   if (! m_allRelationX || ! m_allRelationX->exist(sKey))
   { qAssert(false); return qx_bool(false, QString("invalid relation key : '") + sKey + QString("'")); }
   IxSqlRelation * pRelation = m_allRelationX->getByKey(sKey);
   if (! pRelation) { qAssert(false); return qx_bool(false, QString("invalid relation pointer : 'NULL pointer'")); }

   if (! m_relationX.exist(sKey)) { m_relationX.insert(sKey, type_relation(eJoinType, pRelation)); }
   if (sRelationX.count() <= 0) { return qx_bool(true); }

   QxSqlRelationLinked_ptr pRelationLinked = m_relationLinkedX.value(sKey);
   if (! pRelationLinked)
   {
      pRelationLinked = QxSqlRelationLinked_ptr(new QxSqlRelationLinked(false));
      m_relationLinkedX.insert(sKey, pRelationLinked);
   }

   return pRelationLinked->buildHierarchy(pRelation->getLstRelation(), sRelationX);
}

void QxSqlRelationLinked::hierarchySelect(QxSqlRelationParams & params)
{
   if (m_bRoot) { params.setIndex(0); params.setIndexOwner(0); }
   if (m_allRelationX == NULL) { qAssert(false); return; }
   _foreach_if(IxSqlRelation * p, (* m_allRelationX), (p != NULL))
   {
      params.setIndex(params.index() + 1);
      params.setJoinType(qx::dao::sql_join::no_join);
      if (! m_relationX.exist(p->getKey()))
      { if (m_bRoot) { p->lazySelect(params); } continue; }
      params.setJoinType(m_relationX.getByKey(p->getKey()).get<0>());
      p->eagerSelect(params);
      QxSqlRelationLinked_ptr pRelationLinked = m_relationLinkedX.value(p->getKey());
      if (! pRelationLinked) { continue; }
      long lOldIndexOwner = params.indexOwner();
      params.setIndexOwner(params.index());
      pRelationLinked->hierarchySelect(params);
      params.setIndexOwner(lOldIndexOwner);
   }
}

void QxSqlRelationLinked::hierarchyFrom(QxSqlRelationParams & params)
{
   if (m_bRoot) { params.setIndex(0); params.setIndexOwner(0); }
   if (m_allRelationX == NULL) { qAssert(false); return; }
   _foreach_if(IxSqlRelation * p, (* m_allRelationX), (p != NULL))
   {
      params.setIndex(params.index() + 1);
      params.setJoinType(qx::dao::sql_join::no_join);
      if (! m_relationX.exist(p->getKey()))
      { if (m_bRoot) { p->lazyFrom(params); } continue; }
      params.setJoinType(m_relationX.getByKey(p->getKey()).get<0>());
      p->eagerFrom(params);
      QxSqlRelationLinked_ptr pRelationLinked = m_relationLinkedX.value(p->getKey());
      if (! pRelationLinked) { continue; }
      long lOldIndexOwner = params.indexOwner();
      params.setIndexOwner(params.index());
      pRelationLinked->hierarchyFrom(params);
      params.setIndexOwner(lOldIndexOwner);
   }
}

void QxSqlRelationLinked::hierarchyJoin(QxSqlRelationParams & params)
{
   if (m_bRoot) { params.setIndex(0); params.setIndexOwner(0); }
   if (m_allRelationX == NULL) { qAssert(false); return; }
   _foreach_if(IxSqlRelation * p, (* m_allRelationX), (p != NULL))
   {
      params.setIndex(params.index() + 1);
      params.setJoinType(qx::dao::sql_join::no_join);
      if (! m_relationX.exist(p->getKey()))
      { if (m_bRoot) { p->lazyJoin(params); } continue; }
      params.setJoinType(m_relationX.getByKey(p->getKey()).get<0>());
      p->eagerJoin(params);
      QxSqlRelationLinked_ptr pRelationLinked = m_relationLinkedX.value(p->getKey());
      if (! pRelationLinked) { continue; }
      long lOldIndexOwner = params.indexOwner();
      params.setIndexOwner(params.index());
      pRelationLinked->hierarchyJoin(params);
      params.setIndexOwner(lOldIndexOwner);
   }
}

void QxSqlRelationLinked::hierarchyWhereSoftDelete(QxSqlRelationParams & params)
{
   if (m_bRoot) { params.setIndex(0); params.setIndexOwner(0); }
   if (m_allRelationX == NULL) { qAssert(false); return; }
   _foreach_if(IxSqlRelation * p, (* m_allRelationX), (p != NULL))
   {
      params.setIndex(params.index() + 1);
      params.setJoinType(qx::dao::sql_join::no_join);
      if (! m_relationX.exist(p->getKey()))
      { if (m_bRoot) { p->lazyWhereSoftDelete(params); } continue; }
      params.setJoinType(m_relationX.getByKey(p->getKey()).get<0>());
      p->eagerWhereSoftDelete(params);
      QxSqlRelationLinked_ptr pRelationLinked = m_relationLinkedX.value(p->getKey());
      if (! pRelationLinked) { continue; }
      long lOldIndexOwner = params.indexOwner();
      params.setIndexOwner(params.index());
      pRelationLinked->hierarchyWhereSoftDelete(params);
      params.setIndexOwner(lOldIndexOwner);
   }
}

void QxSqlRelationLinked::hierarchyResolveOutput(QxSqlRelationParams & params)
{
   if (m_bRoot) { params.setIndex(0); params.setIndexOwner(0); }
   if (m_allRelationX == NULL) { qAssert(false); return; }
   QVariant vId, vIdRelation;
   bool bByPass(false), bComplex(params.builder().getCartesianProduct());
   _foreach_if(IxSqlRelation * p, (* m_allRelationX), (p != NULL))
   {
      params.setIndex(params.index() + 1);
      params.setJoinType(qx::dao::sql_join::no_join);
      bool bEager = m_relationX.exist(p->getKey());
      if (bEager) { params.setJoinType(m_relationX.getByKey(p->getKey()).get<0>()); }
      if (bComplex) { vIdRelation = ((m_bRoot || bEager) ? p->getIdFromQuery(bEager, params) : QVariant()); }
      bool bValidId = (bComplex && qx::trait::is_valid_primary_key(vIdRelation));
      void * pFetched = (bValidId ? params.builder().existIdX(params.index(), params.id(), vIdRelation) : NULL);
      bByPass = (bValidId && (pFetched != NULL));
      if (bByPass) { p->updateOffset(bEager, params); }
      else
      {
         if (bEager) { pFetched = p->eagerFetch_ResolveOutput(params); }
         else if (m_bRoot) { p->lazyFetch_ResolveOutput(params); }
         if (bValidId && pFetched) { params.builder().insertIdX(params.index(), params.id(), vIdRelation, pFetched); }
      }
      if (bEager)
      {
         QxSqlRelationLinked_ptr pRelationLinked = m_relationLinkedX.value(p->getKey());
         if (! pRelationLinked) { continue; }
         if (! pFetched)
         {
            params.setIndex(params.index() + pRelationLinked->getAllRelationCount());
            pRelationLinked->updateOffset(params);
            continue;
         }
         void * pOldOwner = params.owner(); params.setOwner(pFetched);
         long lOldIndexOwner = params.indexOwner(); params.setIndexOwner(params.index());
         QVariant vOldId = params.id(); params.setId(QVariant(vOldId.toString() + "|" + vIdRelation.toString()));
         pRelationLinked->hierarchyResolveOutput(params);
         params.setIndexOwner(lOldIndexOwner);
         params.setOwner(pOldOwner);
         params.setId(vOldId);
      }
   }
}

QSqlError QxSqlRelationLinked::hierarchyOnBeforeSave(QxSqlRelationParams & params)
{
   _foreach_if(type_relation item, m_relationX, (item.get<1>() != NULL))
   { QSqlError err = item.get<1>()->onBeforeSave(params); if (err.isValid()) { return err; } }
   return QSqlError();
}

QSqlError QxSqlRelationLinked::hierarchyOnAfterSave(QxSqlRelationParams & params)
{
   _foreach_if(type_relation item, m_relationX, (item.get<1>() != NULL))
   { QSqlError err = item.get<1>()->onAfterSave(params); if (err.isValid()) { return err; } }
   return QSqlError();
}

bool QxSqlRelationLinked::getCartesianProduct() const
{
   _foreach_if(type_relation item, m_relationX, (item.get<1>() != NULL))
   { if (item.get<1>()->getCartesianProduct()) { return true; } }
   Q_FOREACH(QxSqlRelationLinked_ptr pRelationLinked, m_relationLinkedX)
   { if (pRelationLinked && pRelationLinked->getCartesianProduct()) { return true; } }
   return false;
}

long QxSqlRelationLinked::getAllRelationCount() const
{
   long lCount = 0;
   if (! m_allRelationX) { return 0; }
   Q_FOREACH(QxSqlRelationLinked_ptr pRelationLinked, m_relationLinkedX)
   { lCount += pRelationLinked->getAllRelationCount(); }
   return (lCount + m_allRelationX->count());
}

long QxSqlRelationLinked::getRelationCount() const
{
   long lCount = 0;
   Q_FOREACH(QxSqlRelationLinked_ptr pRelationLinked, m_relationLinkedX)
   { lCount += pRelationLinked->getRelationCount(); }
   return (lCount + m_relationX.count());
}

void QxSqlRelationLinked::updateOffset(QxSqlRelationParams & params)
{
   if (m_allRelationX == NULL) { qAssert(false); return; }
   Q_FOREACH(QxSqlRelationLinked_ptr pRelationLinked, m_relationLinkedX)
   { pRelationLinked->updateOffset(params); }
   _foreach_if(IxSqlRelation * p, (* m_allRelationX), (p != NULL))
   { p->updateOffset(m_relationX.exist(p->getKey()), params); }
}

} // namespace qx
