/****************************************************************************
**
** https://www.qxorm.com/
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
#include <QxDao/IxDao_Helper.h>

#include <QxRegister/IxClass.h>

#include <QxCollection/QxCollectionIterator.h>

#include <QxTraits/is_valid_primary_key.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

struct Q_DECL_HIDDEN QxSqlRelationLinked::QxSqlRelationLinkedImpl
{

   enum e_hierarchy_action { e_hierarchy_select, e_hierarchy_from, e_hierarchy_join, e_hierarchy_where_soft_delete };

   typedef std::shared_ptr<QxSqlRelationLinked> type_ptr;
   typedef std::tuple<qx::dao::sql_join::join_type, IxSqlRelation *, QPair<QSet<QString>, long>, QString> type_relation;
   typedef qx::QxCollection<QString, type_relation> type_lst_relation;
   typedef QHash<QString, type_ptr> type_lst_relation_linked;

   type_lst_relation m_relationX;                     //!< List of relationships for current level
   type_lst_relation_linked m_relationLinkedX;        //!< List of child to build the hierarchy
   IxSqlRelationX * m_allRelationX;                   //!< List of all relationships per level
   IxSqlRelationX_ptr m_allRelationXOrdered;          //!< List of all relationships per level (order defined by user, used only when necessary, for example with custom join sub-queries)
   bool m_bRoot;                                      //!< Root of the hierarchy
   QSet<QString> m_lstRootColumns;                    //!< Root columns to fetch (using syntax { col_1, col_2, etc... } ), if empty then fetch all root columns
   long m_lRootColumnsOffset;                         //!< Root columns offset to resolve SQL query output
   bool m_bRootColumnsModeRemove;                     //!< Special syntax to remove root columns instead of adding root columns : -{ column1, column2, etc... }
   QString m_sRootCustomAlias;                        //!< Root custom alias using <my_alias> syntax

   static QMutex m_mutex;                                                        //!< Mutex => qx::QxSqlRelationLinked is thread-safe
   static QHash<QPair<IxClass *, QByteArray>, type_ptr> m_relationLinkedSaved;   //!< Keep relations linked in memory for optimization (to avoid too many parsing)

   QxSqlRelationLinkedImpl(bool bRoot) : m_allRelationX(NULL), m_bRoot(bRoot), m_lRootColumnsOffset(0), m_bRootColumnsModeRemove(false) { ; }
   ~QxSqlRelationLinkedImpl() { ; }

   qx_bool buildHierarchy(IxSqlRelationX * pRelationX, const QStringList & sRelationX, qx::dao::detail::IxDao_Helper * pDaoHelper);
   qx_bool insertRelationToHierarchy(const QStringList & sRelationX, const QString & sKey, qx::dao::sql_join::join_type eJoinType, qx::dao::detail::IxDao_Helper * pDaoHelper);
   QStringList removeColumns(const QStringList & columnsToRemove, IxSqlRelation * pRelation) const;

   bool checkRootColumns(const QString & s) const { return (m_lstRootColumns.isEmpty() || (m_bRootColumnsModeRemove ? (! m_lstRootColumns.contains(s)) : m_lstRootColumns.contains(s))); }

   void hierarchyAction(QxSqlRelationParams & params, e_hierarchy_action action)
   {
      if (m_bRoot) { params.setIndex(0); params.setIndexOwner(0); params.setCustomAlias(m_sRootCustomAlias); params.setCustomAliasOwner(m_sRootCustomAlias); }
      IxSqlRelationX * pAllRelationX = (m_allRelationXOrdered ? m_allRelationXOrdered.get() : m_allRelationX); if (! pAllRelationX) { qAssert(false); return; }
      for (auto itr = pAllRelationX->begin(); itr != pAllRelationX->end(); ++itr)
      {
         IxSqlRelation * p = itr->second; if (! p) { continue; }
         params.setIndex(params.index() + 1);
         params.setRelationX(& m_relationLinkedX);
         params.setJoinType(qx::dao::sql_join::no_join);

         if (! m_relationX.exist(p->getKey()))
         {
            if (m_bRoot && checkRootColumns(p->getKey()))
            {
               switch (action)
               {
                  case e_hierarchy_select:               p->lazySelect(params); break;
                  case e_hierarchy_from:                 p->lazyFrom(params); break;
                  case e_hierarchy_join:                 p->lazyJoin(params); break;
                  case e_hierarchy_where_soft_delete:    p->lazyWhereSoftDelete(params); break;
                  default:                               qAssert(false); break;
               }
            }
            continue;
         }

         QxSqlRelationLinkedImpl::type_relation & temp = const_cast<QxSqlRelationLinkedImpl::type_relation &>(m_relationX.getByKey(p->getKey()));
         params.setJoinType(std::get<0>(temp));
         params.setColumns(& std::get<2>(temp));
         params.setCustomAlias(std::get<3>(temp));

         switch (action)
         {
            case e_hierarchy_select:               p->eagerSelect(params); break;
            case e_hierarchy_from:                 p->eagerFrom(params); break;
            case e_hierarchy_join:                 p->eagerJoin(params); break;
            case e_hierarchy_where_soft_delete:    p->eagerWhereSoftDelete(params); break;
            default:                               qAssert(false); break;
         }

         QxSqlRelationLinked_ptr pRelationLinked = m_relationLinkedX.value(p->getKey()); if (! pRelationLinked) { continue; }
         long lOldIndexOwner = params.indexOwner();
         params.setIndexOwner(params.index());
         QString sOldCustomAliasOwner = params.getCustomAliasOwner();
         params.setCustomAliasOwner(std::get<3>(temp));

         switch (action)
         {
            case e_hierarchy_select:               pRelationLinked->hierarchySelect(params); break;
            case e_hierarchy_from:                 pRelationLinked->hierarchyFrom(params); break;
            case e_hierarchy_join:                 pRelationLinked->hierarchyJoin(params); break;
            case e_hierarchy_where_soft_delete:    pRelationLinked->hierarchyWhereSoftDelete(params); break;
            default:                               qAssert(false); break;
         }

         params.setIndexOwner(lOldIndexOwner);
         params.setCustomAliasOwner(sOldCustomAliasOwner);
      }
   }

   static std::shared_ptr<QxSqlRelationLinked> getRelationLinkedSaved(const QPair<IxClass *, QByteArray> & key)               { QMutexLocker locker(& m_mutex); return m_relationLinkedSaved.value(key); }
   static void insertRelationLinkedSaved(const QPair<IxClass *, QByteArray> & key, std::shared_ptr<QxSqlRelationLinked> ptr)  { QMutexLocker locker(& m_mutex); m_relationLinkedSaved.insert(key, ptr); }

};

QMutex QxSqlRelationLinked::QxSqlRelationLinkedImpl::m_mutex;
QHash<QPair<IxClass *, QByteArray>, std::shared_ptr<QxSqlRelationLinked> > QxSqlRelationLinked::QxSqlRelationLinkedImpl::m_relationLinkedSaved;

QxSqlRelationLinked::QxSqlRelationLinked() : m_pImpl(new QxSqlRelationLinkedImpl(true)) { ; }

QxSqlRelationLinked::QxSqlRelationLinked(bool bRoot) : m_pImpl(new QxSqlRelationLinkedImpl(bRoot)) { ; }

QxSqlRelationLinked::~QxSqlRelationLinked() { ; }

bool QxSqlRelationLinked::isRoot() const { return m_pImpl->m_bRoot; }

bool QxSqlRelationLinked::checkRootColumns(const QString & s) const { return m_pImpl->checkRootColumns(s); }

long QxSqlRelationLinked::getRootColumnsCount() const { return m_pImpl->m_lstRootColumns.count(); }

long QxSqlRelationLinked::getRootColumnsOffset() const { return m_pImpl->m_lRootColumnsOffset; }

void QxSqlRelationLinked::setRootColumnsOffset(long l) { m_pImpl->m_lRootColumnsOffset = l; }

QString QxSqlRelationLinked::getRootCustomAlias() const { return m_pImpl->m_sRootCustomAlias; }

QxSqlRelationLinked::type_lst_relation_linked QxSqlRelationLinked::getRelationLinkedX() const { return m_pImpl->m_relationLinkedX; }

QxSqlRelationLinked::type_lst_relation QxSqlRelationLinked::getRelationX() const { return m_pImpl->m_relationX; }

std::shared_ptr<QxSqlRelationLinked> QxSqlRelationLinked::getHierarchy(IxClass * pClass, const QStringList & sRelationX, qx_bool & bOk, qx::dao::detail::IxDao_Helper * pDaoHelper /* = NULL */)
{
   if (! pClass) { qAssert(false); bOk = qx_bool(false, "class is empty"); return std::shared_ptr<QxSqlRelationLinked>(); }
   QByteArray hash = sRelationX.join("|").toLatin1();
   QPair<IxClass *, QByteArray> key(pClass, hash);
   bool bHasJoinSubQuery = (pDaoHelper ? (! pDaoHelper->qxQuery().getJoinQueryHash().isEmpty()) : false);
   std::shared_ptr<QxSqlRelationLinked> ptr = (bHasJoinSubQuery ? std::shared_ptr<QxSqlRelationLinked>() : QxSqlRelationLinked::QxSqlRelationLinkedImpl::getRelationLinkedSaved(key));
   std::shared_ptr<QxSqlRelationLinked> result = std::make_shared<QxSqlRelationLinked>();
   if (ptr) { (* result->m_pImpl) = (* ptr->m_pImpl); return result; }

   ptr = std::make_shared<QxSqlRelationLinked>();
   bOk = ptr->m_pImpl->buildHierarchy(pClass->getSqlRelationX().get(), sRelationX, pDaoHelper);
   if (! bOk) { return std::shared_ptr<QxSqlRelationLinked>(); }
   if (! bHasJoinSubQuery) { QxSqlRelationLinked::QxSqlRelationLinkedImpl::insertRelationLinkedSaved(key, ptr); }
   (* result->m_pImpl) = (* ptr->m_pImpl);
   return result;
}

qx_bool QxSqlRelationLinked::QxSqlRelationLinkedImpl::buildHierarchy(IxSqlRelationX * pRelationX, const QStringList & sRelationX, qx::dao::detail::IxDao_Helper * pDaoHelper)
{
   if (! pRelationX) { qAssert(false); return qx_bool(false); }
   if (m_bRoot) { m_relationLinkedX.clear(); m_relationX.clear(); }
   m_allRelationX = pRelationX;

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

      if (sKey.startsWith("*"))
      {
         QString suffix = sKey.right(sKey.size() - 1);
         QxCollectionIterator<QString, IxSqlRelation *> itr(* m_allRelationX);
         while (itr.next())
         {
            qx_bool bResult = insertRelationToHierarchy(sNewRelationX, (itr.key() + suffix), eJoinType, pDaoHelper);
            if (! bResult) { return bResult; }
         }
      }
      else
      {
         qx_bool bResult = insertRelationToHierarchy(sNewRelationX, sKey, eJoinType, pDaoHelper);
         if (! bResult) { return bResult; }
      }
   }

   bool bRelationXOrdered = (pDaoHelper ? (! pDaoHelper->qxQuery().getJoinQueryHash().isEmpty()) : false);
   if (bRelationXOrdered && m_allRelationXOrdered)
   {
      QxCollectionIterator<QString, IxSqlRelation *> itr(* m_allRelationX);
      while (itr.next())
      {
         QString sKey = itr.key(); if (sKey.isEmpty()) { qAssert(false); continue; }
         IxSqlRelation * pRelation = itr.value(); if (! pRelation) { qAssert(false); continue; }
         if (! m_allRelationXOrdered->exist(sKey)) { m_allRelationXOrdered->insert(sKey, pRelation); }
      }
   }

   if (m_allRelationXOrdered) { qAssert(m_allRelationXOrdered->count() == m_allRelationX->count()); }
   return qx_bool(true);
}

qx_bool QxSqlRelationLinked::QxSqlRelationLinkedImpl::insertRelationToHierarchy(const QStringList & sRelationX, const QString & sKey, qx::dao::sql_join::join_type eJoinType, qx::dao::detail::IxDao_Helper * pDaoHelper)
{
   bool bModeRemoveColumns = false;
   QStringList columns; QString sKeyTemp = sKey;
   if (sKey.contains("{") && sKey.contains("}"))
   {
      int iPos1 = sKey.indexOf("{"); int iPos2 = sKey.indexOf("}");
      if (iPos1 >= iPos2) { return qx_bool(false, QString("invalid relation : character '}' before than character '{' (") + sKey + ")"); }
      if (iPos1 > 0) { bModeRemoveColumns = (sKey.at(iPos1 - 1) == QChar('-')); } // syntax to remove columns instead of adding columns : -{ column1, column2, etc... }
      if (iPos1 > 1) { bModeRemoveColumns = (bModeRemoveColumns || ((sKey.at(iPos1 - 2) == QChar('-')) && (sKey.at(iPos1 - 1) == QChar(' ')))); } // syntax to remove columns instead of adding columns : - { column1, column2, etc... }
      sKeyTemp = sKey.left(iPos1); sKeyTemp = sKeyTemp.trimmed();
      if (sKeyTemp.endsWith("-")) { sKeyTemp = sKeyTemp.left(sKeyTemp.count() - 1).trimmed(); }
      QString sColumns = sKey.mid((iPos1 + 1), (iPos2 - iPos1 - 1));
      columns = sColumns.split(",");
      for (long l = 0; l < columns.count(); l++) { columns[l] = columns.at(l).trimmed(); }
      if ((columns.count() == 1) && ((columns.at(0) == "*") || (columns.at(0) == ""))) { columns = QStringList(); }
   }

   QString customAlias, customAliasSuffix, customAliasPrefix;
   if (sKeyTemp.contains("<") && sKeyTemp.contains(">"))
   {
      int iPos1 = sKeyTemp.indexOf("<"); int iPos2 = sKeyTemp.indexOf(">");
      if (iPos1 >= iPos2) { return qx_bool(false, QString("invalid custom alias : character '>' before than character '<' (") + sKeyTemp + ")"); }
      customAlias = sKeyTemp.mid((iPos1 + 1), (iPos2 - iPos1 - 1)).trimmed();
      if (customAlias.startsWith("...")) { customAliasSuffix = customAlias.right(customAlias.size() - 3); customAlias = ""; }
      if (customAlias.endsWith("...")) { customAliasPrefix = customAlias.left(customAlias.size() - 3); customAlias = ""; }
      if (customAlias.contains(" ") || customAliasSuffix.contains(" ") || customAliasPrefix.contains(" ")) { return qx_bool(false, QString("invalid custom alias : custom alias cannot contain a space (") + sKeyTemp + ")"); }
      if (customAlias.contains(".") || customAliasSuffix.contains(".") || customAliasPrefix.contains(".")) { return qx_bool(false, QString("invalid custom alias : custom alias cannot contain a dot (") + sKeyTemp + ")"); }
      sKeyTemp = sKeyTemp.left(iPos1); sKeyTemp = sKeyTemp.trimmed();
   }

   if (m_bRoot && sKeyTemp.isEmpty() && (columns.count() > 0))
#if (QT_VERSION >= 0x051400)
   { m_lstRootColumns = QSet(columns.begin(), columns.end()); m_bRootColumnsModeRemove = bModeRemoveColumns; m_sRootCustomAlias = customAlias; return qx_bool(true); }
#else // (QT_VERSION >= 0x051400)
   { m_lstRootColumns = columns.toSet(); m_bRootColumnsModeRemove = bModeRemoveColumns; m_sRootCustomAlias = customAlias; return qx_bool(true); }
#endif // (QT_VERSION >= 0x051400)
   else if (m_bRoot && sKeyTemp.isEmpty() && (columns.count() == 0))
   { m_sRootCustomAlias = customAlias; return qx_bool(true); }

   if (! m_allRelationX || ! m_allRelationX->exist(sKeyTemp))
   { qAssert(false); return qx_bool(false, QString("invalid relation key : '") + sKeyTemp + "' (" + sKey + ")"); }
   IxSqlRelation * pRelation = m_allRelationX->getByKey(sKeyTemp);
   if (! pRelation) { qAssert(false); return qx_bool(false, QString("invalid relation pointer : 'NULL pointer'")); }
   if (bModeRemoveColumns && (columns.count() > 0)) { columns = removeColumns(columns, pRelation); }

   QString sDataIdKey = (pRelation->getDataId() ? pRelation->getDataId()->getKey() : QString());
   Q_FOREACH(QString sColumn, columns)
   {
      if ((! pRelation->getDataByKey(sColumn)) && (sDataIdKey != sColumn))
      { return qx_bool(false, QString("invalid relation column : '" + sKeyTemp + "." + sColumn + "' (" + sKey + ")")); }
   }

   bool bRelationXOrdered = (pDaoHelper ? (! pDaoHelper->qxQuery().getJoinQueryHash().isEmpty()) : false);
   if (bRelationXOrdered && ! m_allRelationXOrdered) { m_allRelationXOrdered = std::make_shared<IxSqlRelationX>(); }
   if (bRelationXOrdered && ! m_allRelationXOrdered->exist(sKeyTemp)) { m_allRelationXOrdered->insert(sKeyTemp, pRelation); }

   if (! customAliasSuffix.isEmpty() && pRelation->getClass()) { customAlias = (pRelation->getClass()->getKey() + customAliasSuffix); }
   if (! customAliasPrefix.isEmpty() && pRelation->getClass()) { customAlias = (customAliasPrefix + pRelation->getClass()->getKey()); }
#if (QT_VERSION >= 0x051400)
   if (! m_relationX.exist(sKeyTemp)) { m_relationX.insert(sKeyTemp, QxSqlRelationLinkedImpl::type_relation(eJoinType, pRelation, qMakePair(QSet(columns.begin(), columns.end()), static_cast<long>(0)), customAlias)); }
#else // (QT_VERSION >= 0x051400)
   if (! m_relationX.exist(sKeyTemp)) { m_relationX.insert(sKeyTemp, QxSqlRelationLinkedImpl::type_relation(eJoinType, pRelation, qMakePair(columns.toSet(), static_cast<long>(0)), customAlias)); }
#endif // (QT_VERSION >= 0x051400)
   if (sRelationX.count() <= 0) { return qx_bool(true); }

   QxSqlRelationLinked_ptr pRelationLinked = m_relationLinkedX.value(sKeyTemp);
   if (! pRelationLinked)
   {
      pRelationLinked = QxSqlRelationLinked_ptr(new QxSqlRelationLinked(false));
      m_relationLinkedX.insert(sKeyTemp, pRelationLinked);
   }

   return pRelationLinked->m_pImpl->buildHierarchy(pRelation->getLstRelation(), sRelationX, pDaoHelper);
}

QStringList QxSqlRelationLinked::QxSqlRelationLinkedImpl::removeColumns(const QStringList & columnsToRemove, IxSqlRelation * pRelation) const
{
   if (! pRelation) { return QStringList(); }
   IxDataMember * pCurrData = NULL; IxSqlRelation * pCurrRelation = NULL;
#if (QT_VERSION >= 0x051400)
   QSet<QString> columnsToRemoveSet(columnsToRemove.begin(), columnsToRemove.end());
#else // (QT_VERSION >= 0x051400)
   QSet<QString> columnsToRemoveSet = columnsToRemove.toSet();
#endif // (QT_VERSION >= 0x051400)
   QStringList columns;

   long lCurrIndex = 0;
   while ((pCurrData = pRelation->nextData(lCurrIndex)))
   { if (! columnsToRemoveSet.contains(pCurrData->getKey())) { columns.append(pCurrData->getKey()); } }

   lCurrIndex = 0;
   while ((pCurrRelation = pRelation->nextRelation(lCurrIndex)))
   { if (! columnsToRemoveSet.contains(pCurrRelation->getKey())) { columns.append(pCurrRelation->getKey()); } }

   return columns;
}

void QxSqlRelationLinked::hierarchySelect(QxSqlRelationParams & params) { m_pImpl->hierarchyAction(params, QxSqlRelationLinkedImpl::e_hierarchy_select); }

void QxSqlRelationLinked::hierarchyFrom(QxSqlRelationParams & params) { m_pImpl->hierarchyAction(params, QxSqlRelationLinkedImpl::e_hierarchy_from); }

void QxSqlRelationLinked::hierarchyJoin(QxSqlRelationParams & params) { m_pImpl->hierarchyAction(params, QxSqlRelationLinkedImpl::e_hierarchy_join); }

void QxSqlRelationLinked::hierarchyWhereSoftDelete(QxSqlRelationParams & params) { m_pImpl->hierarchyAction(params, QxSqlRelationLinkedImpl::e_hierarchy_where_soft_delete); }

void QxSqlRelationLinked::hierarchyResolveOutput(QxSqlRelationParams & params)
{
   if (m_pImpl->m_bRoot) { params.setIndex(0); params.setIndexOwner(0); params.setCustomAlias(m_pImpl->m_sRootCustomAlias); params.setCustomAliasOwner(m_pImpl->m_sRootCustomAlias); }
   IxSqlRelationX * pAllRelationX = (m_pImpl->m_allRelationXOrdered ? m_pImpl->m_allRelationXOrdered.get() : m_pImpl->m_allRelationX); if (! pAllRelationX) { qAssert(false); return; }
   QVariant vId, vIdRelation;
   bool bByPass(false), bComplex(params.builder().getCartesianProduct());
   for (auto itr = pAllRelationX->begin(); itr != pAllRelationX->end(); ++itr)
   {
      IxSqlRelation * p = itr->second; if (! p) { continue; }
      if (! isValidDaoHelper(params)) { return; }
      params.setIndex(params.index() + 1);
      params.setRelationX(& m_pImpl->m_relationLinkedX);
      params.setJoinType(qx::dao::sql_join::no_join);
      bool bEager = m_pImpl->m_relationX.exist(p->getKey());
      if (bEager)
      {
         QxSqlRelationLinkedImpl::type_relation & temp = const_cast<QxSqlRelationLinkedImpl::type_relation &>(m_pImpl->m_relationX.getByKey(p->getKey()));
         params.setJoinType(std::get<0>(temp));
         params.setColumns(& std::get<2>(temp));
         params.setCustomAlias(std::get<3>(temp));
      }
      if (bComplex) { vIdRelation = ((m_pImpl->m_bRoot || bEager) ? p->getIdFromQuery(bEager, params) : QVariant()); }
      bool bValidId = (bComplex && qx::trait::is_valid_primary_key(vIdRelation));
      void * pFetched = (bValidId ? params.builder().existIdX(params.index(), params.id(), vIdRelation) : NULL);
      bByPass = (bValidId && (pFetched != NULL));
      if (bByPass) { p->updateOffset(bEager, params); }
      else
      {
         if (bEager) { pFetched = p->eagerFetch_ResolveOutput(params); }
         else if (m_pImpl->m_bRoot && checkRootColumns(p->getKey())) { p->lazyFetch_ResolveOutput(params); }
         if (bValidId && pFetched) { params.builder().insertIdX(params.index(), params.id(), vIdRelation, pFetched); }
         if (! isValidDaoHelper(params)) { return; }
      }
      if (bEager)
      {
         QxSqlRelationLinkedImpl::type_relation & temp = const_cast<QxSqlRelationLinkedImpl::type_relation &>(m_pImpl->m_relationX.getByKey(p->getKey()));
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
         QString sOldCustomAliasOwner = params.getCustomAliasOwner(); params.setCustomAliasOwner(std::get<3>(temp));
         QVariant vOldId = params.id(); params.setId(QVariant(vOldId.toString() + "|" + vIdRelation.toString()));
         pRelationLinked->hierarchyResolveOutput(params);
         params.setIndexOwner(lOldIndexOwner);
         params.setCustomAliasOwner(sOldCustomAliasOwner);
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
   IxSqlRelationX * pAllRelationX = (m_pImpl->m_allRelationXOrdered ? m_pImpl->m_allRelationXOrdered.get() : m_pImpl->m_allRelationX); if (! pAllRelationX) { qAssert(false); return; }
   for (auto itr = pAllRelationX->begin(); itr != pAllRelationX->end(); ++itr)
   {
      IxSqlRelation * p = itr->second; if (! p) { continue; }
      params.setRelationX(& m_pImpl->m_relationLinkedX);
      bool bEager = m_pImpl->m_relationX.exist(p->getKey());
      if (bEager)
      {
         QxSqlRelationLinkedImpl::type_relation & temp = const_cast<QxSqlRelationLinkedImpl::type_relation &>(m_pImpl->m_relationX.getByKey(p->getKey()));
         params.setColumns(& std::get<2>(temp));
         params.setCustomAlias(std::get<3>(temp));
      }
      else { params.setColumns(NULL); params.setCustomAlias(""); }
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
