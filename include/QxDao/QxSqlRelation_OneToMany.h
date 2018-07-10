/****************************************************************************
**
** http://www.qxorm.com/
** http://sourceforge.net/projects/qxorm/
** Original file by Lionel Marty
**
** This file is part of the QxOrm library
**
** This software is provided 'as-is', without any express or implied
** warranty. In no event will the authors be held liable for any
** damages arising from the use of this software.
**
** GNU Lesser General Public License Usage
** This file must be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file 'license.lgpl.txt' included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you have questions regarding the use of this file, please contact :
** contact@qxorm.com
**
****************************************************************************/

#ifndef _QX_SQL_RELATION_ONE_TO_MANY_H_
#define _QX_SQL_RELATION_ONE_TO_MANY_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSqlRelation_OneToMany.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Manage a relationship one-to-many defined between 2 classes (or between 2 tables in database)
 */

#include <QxDao/QxSqlRelation.h>

namespace qx {

/*!
 * \ingroup QxDao
 * \brief qx::QxSqlRelation_OneToMany<DataType, Owner> : manage a relationship one-to-many defined between 2 classes (or between 2 tables in database)
 */
template <class DataType, class Owner>
class QxSqlRelation_OneToMany : public QxSqlRelation<DataType, Owner>
{

private:

   typedef typename QxSqlRelation<DataType, Owner>::type_owner type_owner;
   typedef typename QxSqlRelation<DataType, Owner>::type_data type_data;
   typedef typename QxSqlRelation<DataType, Owner>::type_container type_container;
   typedef typename QxSqlRelation<DataType, Owner>::type_generic_container type_generic_container;
   typedef typename QxSqlRelation<DataType, Owner>::type_item type_item;

   enum { is_data_container = QxSqlRelation<DataType, Owner>::is_data_container };

protected:

   QString m_sForeignKey;  //!< SQL query foreign key

public:

   QxSqlRelation_OneToMany(IxDataMember * p, const QString & sForeignKey) : QxSqlRelation<DataType, Owner>(p), m_sForeignKey(sForeignKey) { qAssert(! m_sForeignKey.isEmpty()); }
   virtual ~QxSqlRelation_OneToMany() { BOOST_STATIC_ASSERT(is_data_container); }

   virtual QString getDescription() const                                     { return "relation one-to-many"; }
   virtual QString getExtraTable() const                                      { return ""; }
   virtual QString createExtraTable() const                                   { return ""; }
   virtual bool getCartesianProduct() const                                   { return true; }
   virtual void createTable(QxSqlRelationParams & params) const               { Q_UNUSED(params); }
   virtual void lazySelect(QxSqlRelationParams & params) const                { Q_UNUSED(params); }
   virtual void lazyFrom(QxSqlRelationParams & params) const                  { Q_UNUSED(params); }
   virtual void eagerFrom(QxSqlRelationParams & params) const                 { Q_UNUSED(params); }
   virtual void lazyJoin(QxSqlRelationParams & params) const                  { Q_UNUSED(params); }
   virtual void lazyWhere(QxSqlRelationParams & params) const                 { Q_UNUSED(params); }
   virtual void eagerWhere(QxSqlRelationParams & params) const                { Q_UNUSED(params); }
   virtual void lazyWhereSoftDelete(QxSqlRelationParams & params) const       { Q_UNUSED(params); }
   virtual void lazyFetch_ResolveInput(QxSqlRelationParams & params) const    { Q_UNUSED(params); }
   virtual void eagerFetch_ResolveInput(QxSqlRelationParams & params) const   { Q_UNUSED(params); }
   virtual void lazyFetch_ResolveOutput(QxSqlRelationParams & params) const   { Q_UNUSED(params); }
   virtual void lazyInsert(QxSqlRelationParams & params) const                { Q_UNUSED(params); }
   virtual void lazyInsert_Values(QxSqlRelationParams & params) const         { Q_UNUSED(params); }
   virtual void lazyUpdate(QxSqlRelationParams & params) const                { Q_UNUSED(params); }
   virtual void lazyInsert_ResolveInput(QxSqlRelationParams & params) const   { Q_UNUSED(params); }
   virtual void lazyUpdate_ResolveInput(QxSqlRelationParams & params) const   { Q_UNUSED(params); }
   virtual QSqlError onBeforeSave(QxSqlRelationParams & params) const         { Q_UNUSED(params); return QSqlError(); }

   virtual QSqlError onAfterSave(QxSqlRelationParams & params) const
   { return qx::dao::save(this->getContainer(params), (& params.database())); }

   virtual QVariant getIdFromQuery(bool bEager, QxSqlRelationParams & params) const
   {
      QString sId; IxDataMember * pId = this->getDataId(); if (! bEager || ! pId) { return QVariant(); }
      for (int i = 0; i < pId->getNameCount(); i++) { sId += params.query().value(params.offset() + i).toString() + "|"; }
      return QVariant(sId);
   }

   virtual void updateOffset(bool bEager, QxSqlRelationParams & params) const
   {
      if (! bEager) { return; }
      IxDataMember * pForeign = this->getDataByKey(m_sForeignKey);
      bool bAddOffsetForeign = (pForeign && ! this->getLstDataMember()->exist(m_sForeignKey));
      long lOffsetId = (this->getDataId() ? this->getDataId()->getNameCount() : 0);
      long lNewOffset = (params.offset() + this->getDataCount() + lOffsetId);
      lNewOffset = (lNewOffset + (bAddOffsetForeign ? pForeign->getNameCount() : 0));
      lNewOffset = (lNewOffset + (this->m_oSoftDelete.isEmpty() ? 0 : 1));
      params.setOffset(lNewOffset);
   }

   virtual void eagerSelect(QxSqlRelationParams & params) const
   {
      long l1(0);
      QString & sql = params.sql();
      IxDataMember * pForeign = this->getDataByKey(m_sForeignKey); qAssert(pForeign);
      IxDataMember * p = NULL; IxDataMember * pId = this->getDataId(); qAssert(pId);
      QString tableAlias = this->tableAlias(params);
      if (pId) { sql += (pId->getSqlTablePointNameAsAlias(tableAlias) + ", "); }
      if (pForeign) { sql += (pForeign->getSqlTablePointNameAsAlias(tableAlias) + ", "); }
      while ((p = this->nextData(l1))) { if (p != pForeign) { sql += (p->getSqlTablePointNameAsAlias(tableAlias) + ", "); } }
      if (! this->m_oSoftDelete.isEmpty()) { sql += (this->m_oSoftDelete.buildSqlTablePointName(tableAlias) + ", "); }
   }

   virtual void eagerJoin(QxSqlRelationParams & params) const
   {
      QString & sql = params.sql();
      IxDataMember * pId = params.builder().getDataId(); qAssert(pId);
      IxDataMember * pForeign = this->getDataByKey(m_sForeignKey); qAssert(pForeign);
      QString table = this->table(); QString tableAlias = this->tableAlias(params); QString tableRef = params.builder().table();
      if (! pId || ! pForeign) { return; }
      sql += this->getSqlJoin() + table + " " + tableAlias + " ON ";
      params.builder().addSqlQueryAlias(table, tableAlias);
      for (int i = 0; i < pId->getNameCount(); i++)
      { sql += pForeign->getSqlAlias(tableAlias, true, i) + " = " + pId->getSqlAlias(tableRef, true, i) + " AND "; }
      sql = sql.left(sql.count() - 5); // Remove last " AND "
   }

   virtual void eagerWhereSoftDelete(QxSqlRelationParams & params) const
   {
      if (this->m_oSoftDelete.isEmpty()) { return; }
      QString & sql = params.sql();
      QString tableAlias = this->tableAlias(params);
      sql += qx::IxSqlQueryBuilder::addSqlCondition(sql);
      sql += this->m_oSoftDelete.buildSqlQueryToFetch(tableAlias);
   }

   virtual void eagerFetch_ResolveOutput(QxSqlRelationParams & params) const
   {
      if (! this->verifyOffset(params, true)) { return; }
      QSqlQuery & query = params.query();
      IxDataMember * p = NULL; IxDataMember * pId = this->getDataId(); qAssert(pId); if (! pId) { return; }
      IxDataMember * pForeign = this->getDataByKey(m_sForeignKey); qAssert(pForeign); if (! pForeign) { return; }
      long lIndex = 0; long lOffsetId = (pId ? pId->getNameCount() : 0); long lOffsetForeign = (pForeign ? pForeign->getNameCount() : 0);
      long lOffsetOld = params.offset(); this->updateOffset(true, params);
      long lOffsetRelation = (lOffsetOld + lOffsetId + lOffsetForeign);
      bool bValidId(false), bValidForeign(false);
      for (int i = 0; i < pId->getNameCount(); i++)
      { QVariant vId = query.value(lOffsetOld + i); bValidId = (bValidId || qx::trait::is_valid_primary_key(vId)); }
      for (int i = 0; i < pForeign->getNameCount(); i++)
      { QVariant vForeign = query.value(lOffsetOld + lOffsetId + i); bValidForeign = (bValidForeign || qx::trait::is_valid_primary_key(vForeign)); }
      if (! bValidId || ! bValidForeign) { return; }
      type_item item = this->createItem();
      type_data & item_val = item.value_qx();
      for (int i = 0; i < pId->getNameCount(); i++)
      { QVariant v = query.value(lOffsetOld + i); qx::cvt::from_variant(v, item.key(), "", i); }
      for (int i = 0; i < pId->getNameCount(); i++)
      { QVariant v = query.value(lOffsetOld + i); pId->fromVariant((& item_val), v, "", i); }
      for (int i = 0; i < pForeign->getNameCount(); i++)
      { QVariant v = query.value(lOffsetOld + lOffsetId + i); pForeign->fromVariant((& item_val), v, "", i); }
      while ((p = this->nextData(lIndex)))
      { if (p != pForeign) { p->fromVariant((& item_val), query.value(lOffsetRelation++)); } }
      type_generic_container::insertItem(this->getContainer(params), item);
   }

};

} // namespace qx

#endif // _QX_SQL_RELATION_ONE_TO_MANY_H_
