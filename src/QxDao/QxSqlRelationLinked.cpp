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

struct QxSqlRelationLinked::QxSqlRelationLinkedImpl
{

   typedef std::shared_ptr<QxSqlRelationLinked> type_ptr;
   typedef std::tuple<qx::dao::sql_join::join_type, IxSqlRelation *, QPair<QSet<QString>, long> > type_relation;
   typedef qx::QxCollection<QString, type_relation> type_lst_relation;
   typedef QHash<QString, type_ptr> type_lst_relation_linked;

   type_lst_relation m_relationX;               //!< List of relationships for current level
   type_lst_relation_linked m_relationLinkedX;  //!< List of child to build the hierarchy
   IxSqlRelationX * m_allRelationX;             //!< List of all relationships per level
   bool m_bRoot;                                //!< Root of the hierarchy
   QSet<QString> m_lstRootColumns;              //!< Root columns to fetch (using syntax { col_1, col_2, etc... } ), if empty then fetch all root columns
   long m_lRootColumnsOffset;                   //!< Root columns offset to resolve SQL query output
   bool m_bRootColumnsModeRemove;               //!< Special syntax to remove root columns instead of adding root columns : -{ column1, column2, etc... }

   QxSqlRelationLinkedImpl() : m_allRelationX(NULL), m_bRoot(true), m_lRootColumnsOffset(0), m_bRootColumnsModeRemove(false) { ; }
   QxSqlRelationLinkedImpl(bool bRoot) : m_allRelationX(NULL), m_bRoot(bRoot), m_lRootColumnsOffset(0), m_bRootColumnsModeRemove(false) { ; }
   ~QxSqlRelationLinkedImpl() { ; }

};

QxSqlRelationLinked::QxSqlRelationLinked() : m_pImpl(new QxSqlRelationLinkedImpl()) { ; }

QxSqlRelationLinked::QxSqlRelationLinked(bool bRoot) : m_pImpl(new QxSqlRelationLinkedImpl(bRoot)) { ; }

QxSqlRelationLinked::~QxSqlRelationLinked() { ; }

bool QxSqlRelationLinked::checkRootColumns(const QString & s) const { return (m_pImpl->m_lstRootColumns.isEmpty() || (m_pImpl->m_bRootColumnsModeRemove ? (! m_pImpl->m_lstRootColumns.contains(s)) : m_pImpl->m_lstRootColumns.contains(s))); }

long QxSqlRelationLinked::getRootColumnsCount() const { return m_pImpl->m_lstRootColumns.count(); }

long QxSqlRelationLinked::getRootColumnsOffset() const { return m_pImpl->m_lRootColumnsOffset; }

void QxSqlRelationLinked::setRootColumnsOffset(long l) { m_pImpl->m_lRootColumnsOffset = l; }

qx_bool QxSqlRelationLinked::buildHierarchy(IxSqlRelationX * pRelationX, const QStringList & sRelationX)
{
   if (! pRelationX) { qAssert(false); return qx_bool(false); }
   if (m_pImpl->m_bRoot) { m_pImpl->m_relationLinkedX.clear(); m_pImpl->m_relationX.clear(); }
   m_pImpl->m_allRelationX = pRelationX;

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
         QxCollectionIterator<QString, IxSqlRelation *> itr(* m_pImpl->m_allRelationX);
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
   bool bModeRemoveColumns = false;
   QStringList columns; QString sKeyTemp = sKey;
   if (sKey.contains("{") && sKey.contains("}"))
   {
      int iPos1 = sKey.indexOf("{"); int iPos2 = sKey.indexOf("}");
      if (iPos1 >= iPos2) { return qx_bool(false, QString("invalid relation : character '}' before than character '{' (") + sKey + ")"); }
      if (iPos1 > 0) { bModeRemoveColumns = (sKey.at(iPos1 - 1) == QChar('-')); } // syntax to remove columns instead of adding columns : -{ column1, column2, etc... }
      sKeyTemp = sKey.left(iPos1); sKeyTemp = sKeyTemp.trimmed();
      if (sKeyTemp.endsWith("-")) { sKeyTemp = sKeyTemp.left(sKeyTemp.count() - 1).trimmed(); }
      QString sColumns = sKey.mid((iPos1 + 1), (iPos2 - iPos1 - 1));
      columns = sColumns.split(",");
      for (long l = 0; l < columns.count(); l++) { columns[l] = columns.at(l).trimmed(); }
      if ((columns.count() == 1) && ((columns.at(0) == "*") || (columns.at(0) == ""))) { columns = QStringList(); }
   }

   if (m_pImpl->m_bRoot && sKeyTemp.isEmpty() && (columns.count() > 0))
   { m_pImpl->m_lstRootColumns = columns.toSet(); m_pImpl->m_bRootColumnsModeRemove = bModeRemoveColumns; return qx_bool(true); }
   else if (m_pImpl->m_bRoot && sKeyTemp.isEmpty() && (columns.count() == 0))
   { return qx_bool(true); }

   if (! m_pImpl->m_allRelationX || ! m_pImpl->m_allRelationX->exist(sKeyTemp))
   { qAssert(false); return qx_bool(false, QString("invalid relation key : '") + sKeyTemp + "' (" + sKey + ")"); }
   IxSqlRelation * pRelation = m_pImpl->m_allRelationX->getByKey(sKeyTemp);
   if (! pRelation) { qAssert(false); return qx_bool(false, QString("invalid relation pointer : 'NULL pointer'")); }
   if (bModeRemoveColumns && (columns.count() > 0)) { columns = removeColumns(columns, pRelation); }

   QString sDataIdKey = (pRelation->getDataId() ? pRelation->getDataId()->getKey() : QString());
   Q_FOREACH(QString sColumn, columns)
   {
      if ((! pRelation->getDataByKey(sColumn)) && (sDataIdKey != sColumn))
      { return qx_bool(false, QString("invalid relation column : '" + sKeyTemp + "." + sColumn + "' (" + sKey + ")")); }
   }

   if (! m_pImpl->m_relationX.exist(sKeyTemp)) { m_pImpl->m_relationX.insert(sKeyTemp, QxSqlRelationLinkedImpl::type_relation(eJoinType, pRelation, qMakePair(columns.toSet(), static_cast<long>(0)))); }
   if (sRelationX.count() <= 0) { return qx_bool(true); }

   QxSqlRelationLinked_ptr pRelationLinked = m_pImpl->m_relationLinkedX.value(sKeyTemp);
   if (! pRelationLinked)
   {
      pRelationLinked = QxSqlRelationLinked_ptr(new QxSqlRelationLinked(false));
      m_pImpl->m_relationLinkedX.insert(sKeyTemp, pRelationLinked);
   }

   return pRelationLinked->buildHierarchy(pRelation->getLstRelation(), sRelationX);
}

QStringList QxSqlRelationLinked::removeColumns(const QStringList & columnsToRemove, IxSqlRelation * pRelation) const
{
   if (! pRelation) { return QStringList(); }
   IxDataMember * pCurrData = NULL; IxSqlRelation * pCurrRelation = NULL;
   QSet<QString> columnsToRemoveSet = columnsToRemove.toSet();
   QStringList columns;

   long lCurrIndex = 0;
   while ((pCurrData = pRelation->nextData(lCurrIndex)))
   { if (! columnsToRemoveSet.contains(pCurrData->getKey())) { columns.append(pCurrData->getKey()); } }

   lCurrIndex = 0;
   while ((pCurrRelation = pRelation->nextRelation(lCurrIndex)))
   { if (! columnsToRemoveSet.contains(pCurrRelation->getKey())) { columns.append(pCurrRelation->getKey()); } }

   return columns;
}

void QxSqlRelationLinked::hierarchySelect(QxSqlRelationParams & params)
{
   if (m_pImpl->m_bRoot) { params.setIndex(0); params.setIndexOwner(0); }
   if (m_pImpl->m_allRelationX == NULL) { qAssert(false); return; }
   for (auto itr = m_pImpl->m_allRelationX->begin(); itr != m_pImpl->m_allRelationX->end(); ++itr)
   {
      IxSqlRelation * p = itr->second; if (! p) { continue; }
      params.setIndex(params.index() + 1);
      params.setRelationX(& m_pImpl->m_relationLinkedX);
      params.setJoinType(qx::dao::sql_join::no_join);
      if (! m_pImpl->m_relationX.exist(p->getKey()))
      { if (m_pImpl->m_bRoot) { p->lazySelect(params); } continue; }
      QxSqlRelationLinkedImpl::type_relation & temp = const_cast<QxSqlRelationLinkedImpl::type_relation &>(m_pImpl->m_relationX.getByKey(p->getKey()));
      params.setJoinType(std::get<0>(temp));
      params.setColumns(& std::get<2>(temp));
      p->eagerSelect(params);
      QxSqlRelationLinked_ptr pRelationLinked = m_pImpl->m_relationLinkedX.value(p->getKey());
      if (! pRelationLinked) { continue; }
      long lOldIndexOwner = params.indexOwner();
      params.setIndexOwner(params.index());
      pRelationLinked->hierarchySelect(params);
      params.setIndexOwner(lOldIndexOwner);
   }
}

void QxSqlRelationLinked::hierarchyFrom(QxSqlRelationParams & params)
{
   if (m_pImpl->m_bRoot) { params.setIndex(0); params.setIndexOwner(0); }
   if (m_pImpl->m_allRelationX == NULL) { qAssert(false); return; }
   for (auto itr = m_pImpl->m_allRelationX->begin(); itr != m_pImpl->m_allRelationX->end(); ++itr)
   {
      IxSqlRelation * p = itr->second; if (! p) { continue; }
      params.setIndex(params.index() + 1);
      params.setRelationX(& m_pImpl->m_relationLinkedX);
      params.setJoinType(qx::dao::sql_join::no_join);
      if (! m_pImpl->m_relationX.exist(p->getKey()))
      { if (m_pImpl->m_bRoot) { p->lazyFrom(params); } continue; }
      QxSqlRelationLinkedImpl::type_relation & temp = const_cast<QxSqlRelationLinkedImpl::type_relation &>(m_pImpl->m_relationX.getByKey(p->getKey()));
      params.setJoinType(std::get<0>(temp));
      params.setColumns(& std::get<2>(temp));
      p->eagerFrom(params);
      QxSqlRelationLinked_ptr pRelationLinked = m_pImpl->m_relationLinkedX.value(p->getKey());
      if (! pRelationLinked) { continue; }
      long lOldIndexOwner = params.indexOwner();
      params.setIndexOwner(params.index());
      pRelationLinked->hierarchyFrom(params);
      params.setIndexOwner(lOldIndexOwner);
   }
}

void QxSqlRelationLinked::hierarchyJoin(QxSqlRelationParams & params)
{
   if (m_pImpl->m_bRoot) { params.setIndex(0); params.setIndexOwner(0); }
   if (m_pImpl->m_allRelationX == NULL) { qAssert(false); return; }
   for (auto itr = m_pImpl->m_allRelationX->begin(); itr != m_pImpl->m_allRelationX->end(); ++itr)
   {
      IxSqlRelation * p = itr->second; if (! p) { continue; }
      params.setIndex(params.index() + 1);
      params.setRelationX(& m_pImpl->m_relationLinkedX);
      params.setJoinType(qx::dao::sql_join::no_join);
      if (! m_pImpl->m_relationX.exist(p->getKey()))
      { if (m_pImpl->m_bRoot) { p->lazyJoin(params); } continue; }
      QxSqlRelationLinkedImpl::type_relation & temp = const_cast<QxSqlRelationLinkedImpl::type_relation &>(m_pImpl->m_relationX.getByKey(p->getKey()));
      params.setJoinType(std::get<0>(temp));
      params.setColumns(& std::get<2>(temp));
      p->eagerJoin(params);
      QxSqlRelationLinked_ptr pRelationLinked = m_pImpl->m_relationLinkedX.value(p->getKey());
      if (! pRelationLinked) { continue; }
      long lOldIndexOwner = params.indexOwner();
      params.setIndexOwner(params.index());
      pRelationLinked->hierarchyJoin(params);
      params.setIndexOwner(lOldIndexOwner);
   }
}

void QxSqlRelationLinked::hierarchyWhereSoftDelete(QxSqlRelationParams & params)
{
   if (m_pImpl->m_bRoot) { params.setIndex(0); params.setIndexOwner(0); }
   if (m_pImpl->m_allRelationX == NULL) { qAssert(false); return; }
   for (auto itr = m_pImpl->m_allRelationX->begin(); itr != m_pImpl->m_allRelationX->end(); ++itr)
   {
      IxSqlRelation * p = itr->second; if (! p) { continue; }
      params.setIndex(params.index() + 1);
      params.setRelationX(& m_pImpl->m_relationLinkedX);
      params.setJoinType(qx::dao::sql_join::no_join);
      if (! m_pImpl->m_relationX.exist(p->getKey()))
      { if (m_pImpl->m_bRoot) { p->lazyWhereSoftDelete(params); } continue; }
      QxSqlRelationLinkedImpl::type_relation & temp = const_cast<QxSqlRelationLinkedImpl::type_relation &>(m_pImpl->m_relationX.getByKey(p->getKey()));
      params.setJoinType(std::get<0>(temp));
      params.setColumns(& std::get<2>(temp));
      p->eagerWhereSoftDelete(params);
      QxSqlRelationLinked_ptr pRelationLinked = m_pImpl->m_relationLinkedX.value(p->getKey());
      if (! pRelationLinked) { continue; }
      long lOldIndexOwner = params.indexOwner();
      params.setIndexOwner(params.index());
      pRelationLinked->hierarchyWhereSoftDelete(params);
      params.setIndexOwner(lOldIndexOwner);
   }
}

void QxSqlRelationLinked::hierarchyResolveOutput(QxSqlRelationParams & params)
{
   if (m_pImpl->m_bRoot) { params.setIndex(0); params.setIndexOwner(0); }
   if (m_pImpl->m_allRelationX == NULL) { qAssert(false); return; }
   QVariant vId, vIdRelation;
   bool bByPass(false), bComplex(params.builder().getCartesianProduct());
   for (auto itr = m_pImpl->m_allRelationX->begin(); itr != m_pImpl->m_allRelationX->end(); ++itr)
   {
      IxSqlRelation * p = itr->second; if (! p) { continue; }
      if (! isValidDaoHelper(params)) { return; }
      params.setIndex(params.index() + 1);
      params.setRelationX(& m_pImpl->m_relationLinkedX);
      params.setJoinType(qx::dao::sql_join::no_join);
      bool bEager = m_pImpl->m_relationX.exist(p->getKey());
      if (bEager) { QxSqlRelationLinkedImpl::type_relation & temp = const_cast<QxSqlRelationLinkedImpl::type_relation &>(m_pImpl->m_relationX.getByKey(p->getKey())); params.setJoinType(std::get<0>(temp)); params.setColumns(& std::get<2>(temp)); }
      if (bComplex) { vIdRelation = ((m_pImpl->m_bRoot || bEager) ? p->getIdFromQuery(bEager, params) : QVariant()); }
      bool bValidId = (bComplex && qx::trait::is_valid_primary_key(vIdRelation));
      void * pFetched = (bValidId ? params.builder().existIdX(params.index(), params.id(), vIdRelation) : NULL);
      bByPass = (bValidId && (pFetched != NULL));
      if (bByPass) { p->updateOffset(bEager, params); }
      else
      {
         if (bEager) { pFetched = p->eagerFetch_ResolveOutput(params); }
         else if (m_pImpl->m_bRoot) { p->lazyFetch_ResolveOutput(params); }
         if (bValidId && pFetched) { params.builder().insertIdX(params.index(), params.id(), vIdRelation, pFetched); }
         if (! isValidDaoHelper(params)) { return; }
      }
      if (bEager)
      {
         QxSqlRelationLinked_ptr pRelationLinked = m_pImpl->m_relationLinkedX.value(p->getKey());
         if (! pRelationLinked) { continue; }
         if (! pFetched)
         {
            params.setRelationX(NULL);
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
   for (auto itr = m_pImpl->m_relationX.begin(); itr != m_pImpl->m_relationX.end(); ++itr)
   {
      const QxSqlRelationLinkedImpl::type_relation & item = itr->second; if (! std::get<1>(item)) { continue; }
      QSqlError err = std::get<1>(item)->onBeforeSave(params);
      if (err.isValid()) { return err; }
   }
   return QSqlError();
}

QSqlError QxSqlRelationLinked::hierarchyOnAfterSave(QxSqlRelationParams & params)
{
   for (auto itr = m_pImpl->m_relationX.begin(); itr != m_pImpl->m_relationX.end(); ++itr)
   {
      const QxSqlRelationLinkedImpl::type_relation & item = itr->second; if (! std::get<1>(item)) { continue; }
      QSqlError err = std::get<1>(item)->onAfterSave(params);
      if (err.isValid()) { return err; }
   }
   return QSqlError();
}

bool QxSqlRelationLinked::getCartesianProduct() const
{
   for (auto itr = m_pImpl->m_relationX.begin(); itr != m_pImpl->m_relationX.end(); ++itr)
   {
      const QxSqlRelationLinkedImpl::type_relation & item = itr->second; if (! std::get<1>(item)) { continue; }
      if (std::get<1>(item)->getCartesianProduct()) { return true; }
   }

   Q_FOREACH(QxSqlRelationLinked_ptr pRelationLinked, m_pImpl->m_relationLinkedX)
   { if (pRelationLinked && pRelationLinked->getCartesianProduct()) { return true; } }
   return false;
}

long QxSqlRelationLinked::getAllRelationCount() const
{
   long lCount = 0;
   if (! m_pImpl->m_allRelationX) { return 0; }
   Q_FOREACH(QxSqlRelationLinked_ptr pRelationLinked, m_pImpl->m_relationLinkedX)
   { lCount += pRelationLinked->getAllRelationCount(); }
   return (lCount + m_pImpl->m_allRelationX->count());
}

long QxSqlRelationLinked::getRelationCount() const
{
   long lCount = 0;
   Q_FOREACH(QxSqlRelationLinked_ptr pRelationLinked, m_pImpl->m_relationLinkedX)
   { lCount += pRelationLinked->getRelationCount(); }
   return (lCount + m_pImpl->m_relationX.count());
}

void QxSqlRelationLinked::updateOffset(QxSqlRelationParams & params)
{
   if (m_pImpl->m_allRelationX == NULL) { qAssert(false); return; }
   for (auto itr = m_pImpl->m_allRelationX->begin(); itr != m_pImpl->m_allRelationX->end(); ++itr)
   {
      IxSqlRelation * p = itr->second; if (! p) { continue; }
      params.setRelationX(& m_pImpl->m_relationLinkedX);
      bool bEager = m_pImpl->m_relationX.exist(p->getKey());
      if (bEager) { QxSqlRelationLinkedImpl::type_relation & temp = const_cast<QxSqlRelationLinkedImpl::type_relation &>(m_pImpl->m_relationX.getByKey(p->getKey())); params.setColumns(& std::get<2>(temp)); } else { params.setColumns(NULL); }
      if (bEager) { p->updateOffset(true, params); }
      else if (m_pImpl->m_bRoot) { p->updateOffset(false, params); }
      QxSqlRelationLinked_ptr pRelationLinked = m_pImpl->m_relationLinkedX.value(p->getKey());
      if (! pRelationLinked) { continue; }
      pRelationLinked->updateOffset(params);
   }
}

bool QxSqlRelationLinked::existRelation(const QString & sKey) const
{
   return m_pImpl->m_relationX.exist(sKey);
}

bool QxSqlRelationLinked::isValidDaoHelper(QxSqlRelationParams & params) const
{
   if (! params.builder().getDaoHelper()) { return true; }
   return params.builder().getDaoHelper()->isValid();
}

} // namespace qx
