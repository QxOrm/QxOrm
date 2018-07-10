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

#ifndef _QX_SQL_RELATION_MANY_TO_ONE_H_
#define _QX_SQL_RELATION_MANY_TO_ONE_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSqlRelation_ManyToOne.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Manage a relationship many-to-one defined between 2 classes (or between 2 tables in database)
 */

#include <QxDao/QxSqlRelation.h>

namespace qx {

/*!
 * \ingroup QxDao
 * \brief qx::QxSqlRelation_ManyToOne<DataType, Owner> : manage a relationship many-to-one defined between 2 classes (or between 2 tables in database)
 */
template <class DataType, class Owner>
class QxSqlRelation_ManyToOne : public QxSqlRelation<DataType, Owner>
{

private:

   typedef typename QxSqlRelation<DataType, Owner>::type_owner type_owner;
   typedef typename QxSqlRelation<DataType, Owner>::type_data type_data;

public:

   QxSqlRelation_ManyToOne(IxDataMember * p) : QxSqlRelation<DataType, Owner>(p) { ; }
   virtual ~QxSqlRelation_ManyToOne() { ; }

   virtual QString getDescription() const                                     { return "relation many-to-one"; }
   virtual bool getCartesianProduct() const                                   { return false; }
   virtual void lazyFrom(QxSqlRelationParams & params) const                  { Q_UNUSED(params); }
   virtual void eagerFrom(QxSqlRelationParams & params) const                 { Q_UNUSED(params); }
   virtual void lazyJoin(QxSqlRelationParams & params) const                  { Q_UNUSED(params); }
   virtual void lazyWhere(QxSqlRelationParams & params) const                 { Q_UNUSED(params); }
   virtual void eagerWhere(QxSqlRelationParams & params) const                { Q_UNUSED(params); }
   virtual void lazyWhereSoftDelete(QxSqlRelationParams & params) const       { Q_UNUSED(params); }
   virtual void lazyFetch_ResolveInput(QxSqlRelationParams & params) const    { Q_UNUSED(params); }
   virtual void eagerFetch_ResolveInput(QxSqlRelationParams & params) const   { Q_UNUSED(params); }
   virtual QSqlError onBeforeSave(QxSqlRelationParams & params) const         { Q_UNUSED(params); return QSqlError(); }
   virtual QSqlError createExtraTable(QxSqlRelationParams & params) const     { Q_UNUSED(params); return QSqlError(); }

   virtual QSqlError onAfterSave(QxSqlRelationParams & params) const
   { return qx::dao::save(this->getData(params), (& params.database())); }

   virtual void lazyUpdate_ResolveInput(QxSqlRelationParams & params) const
   { this->lazyInsert_ResolveInput(params); }

   virtual QVariant getIdFromQuery(bool bEager, QxSqlRelationParams & params) const
   {
      Q_UNUSED(bEager); QString sId; IxDataMember * pId = this->getDataId(); if (! pId) { return QVariant(); }
      for (int i = 0; i < pId->getNameCount(); i++) { sId += params.query().value(params.offset() + i).toString() + "|"; }
      return QVariant(sId);
   }

   virtual void updateOffset(bool bEager, QxSqlRelationParams & params) const
   {
      long lOffsetDataMember = (this->getDataMember() ? this->getDataMember()->getNameCount() : 0);
      long lOffsetDataId = (bEager ? (this->getDataId() ? this->getDataId()->getNameCount() : 0) : 0);
      long lOffsetDataCount = (bEager ? this->getDataCount() : 0);
      long lOffsetSoftDelete = (bEager ? (this->m_oSoftDelete.isEmpty() ? 0 : 1) : 0);
      params.setOffset(params.offset() + lOffsetDataMember + lOffsetDataId + lOffsetDataCount + lOffsetSoftDelete);
   }

   virtual void createTable(QxSqlRelationParams & params) const
   {
      QString & sql = params.sql();
      IxDataMember * pData = this->getDataMember(); qAssert(pData);
      if (pData) { sql += pData->getSqlNameAndTypeAndParams(", ") + ", "; qAssert(! pData->getSqlType().isEmpty()); }
   }

   virtual void lazySelect(QxSqlRelationParams & params) const
   {
      QString & sql = params.sql();
      QString tableRef = params.builder().table();
      IxDataMember * pData = this->getDataMember(); qAssert(pData);
      if (pData) { sql += (pData->getSqlTablePointNameAsAlias(tableRef) + ", "); }
   }

   virtual void eagerSelect(QxSqlRelationParams & params) const
   {
      long l1(0);
      QString & sql = params.sql();
      IxDataMember * pData = this->getDataMember(); qAssert(pData);
      IxDataMember * p = NULL; IxDataMember * pId = this->getDataId(); qAssert(pId);
      QString table = this->table(); QString tableAlias = this->tableAlias(params); QString tableRef = params.builder().table();
      if (pData) { sql += (pData->getSqlTablePointNameAsAlias(tableRef) + ", "); }
      if (pId) { sql += (pId->getSqlTablePointNameAsAlias(tableAlias) + ", "); }
      while ((p = this->nextData(l1))) { sql += (p->getSqlTablePointNameAsAlias(tableAlias) + ", "); }
      if (! this->m_oSoftDelete.isEmpty()) { sql += (this->m_oSoftDelete.buildSqlTablePointName(tableAlias) + ", "); }
   }

   virtual void eagerJoin(QxSqlRelationParams & params) const
   {
      QString & sql = params.sql();
      IxDataMember * pId = this->getDataId(); qAssert(pId);
      IxDataMember * pData = this->getDataMember(); qAssert(pData);
      QString table = this->table(); QString tableAlias = this->tableAlias(params); QString tableRef = params.builder().table();
      if (! pId || ! pData) { return; }
      sql += this->getSqlJoin() + table + " " + tableAlias + " ON ";
      for (int i = 0; i < pId->getNameCount(); i++)
      { sql += pId->getSqlAlias(tableAlias, true, i) + " = " + pData->getSqlAlias(tableRef, true, i) + " AND "; }
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

   virtual void lazyFetch_ResolveOutput(QxSqlRelationParams & params) const
   {
      if (! this->verifyOffset(params, false)) { return; }
      QSqlQuery & query = params.query();
      typename QxSqlRelation<DataType, Owner>::type_owner & currOwner = this->getOwner(params);
      IxDataMember * pData = this->getDataMember(); qAssert(pData); if (! pData) { return; }
      for (int i = 0; i < pData->getNameCount(); i++)
      { QVariant vId = query.value(params.offset() + i); pData->fromVariant((& currOwner), vId, i); }
      this->updateOffset(false, params);
   }

   virtual void eagerFetch_ResolveOutput(QxSqlRelationParams & params) const
   {
      if (! this->verifyOffset(params, false)) { return; }
      QSqlQuery & query = params.query();
      typename QxSqlRelation<DataType, Owner>::type_owner & currOwner = this->getOwner(params);
      IxDataMember * pData = this->getDataMember(); qAssert(pData); if (! pData) { return; }
      IxDataMember * p = NULL; IxDataMember * pId = this->getDataId(); qAssert(pId); if (! pId) { return; }
      long lIndex = 0; long lOffsetId = (pId ? pId->getNameCount() : 0); long lOffsetData = (pData ? pData->getNameCount() : 0);
      long lOffsetOld = params.offset(); this->updateOffset(true, params);
      long lOffsetRelation = (lOffsetOld + lOffsetId + lOffsetData);
      bool bValidId(false), bValidIdBis(false);
      for (int i = 0; i < pData->getNameCount(); i++)
      { QVariant vId = query.value(lOffsetOld + i); bValidId = (bValidId || qx::trait::is_valid_primary_key(vId)); }
      for (int i = 0; i < pId->getNameCount(); i++)
      { QVariant vIdBis = query.value(lOffsetOld + lOffsetData + i); bValidIdBis = (bValidIdBis || qx::trait::is_valid_primary_key(vIdBis)); }
      if (pData && bValidId) { for (int i = 0; i < pData->getNameCount(); i++) { pData->fromVariant((& currOwner), query.value(lOffsetOld + i), i); } }
      if (! bValidIdBis) { return; }
      type_data & currData = this->getData(params);
      if (pId) { for (int i = 0; i < pId->getNameCount(); i++) { pId->fromVariant((& currData), query.value(lOffsetOld + lOffsetData + i), i); } }
      while ((p = this->nextData(lIndex)))
      { p->fromVariant((& currData), query.value(lOffsetRelation++)); }
   }

   virtual void lazyInsert(QxSqlRelationParams & params) const
   {
      QString & sql = params.sql();
      IxDataMember * pData = this->getDataMember(); qAssert(pData);
      if (pData) { sql += pData->getSqlName(", ") + ", "; }
   }

   virtual void lazyInsert_Values(QxSqlRelationParams & params) const
   {
      QString & sql = params.sql();
      IxDataMember * pData = this->getDataMember(); qAssert(pData);
      if (pData) { sql += pData->getSqlPlaceHolder("", -1, ", ") + ", "; }
   }

   virtual void lazyUpdate(QxSqlRelationParams & params) const
   {
      QString & sql = params.sql();
      IxDataMember * pData = this->getDataMember(); qAssert(pData);
      if (pData) { sql += pData->getSqlNameEqualToPlaceHolder("", ", ") + ", "; }
   }

   virtual void lazyInsert_ResolveInput(QxSqlRelationParams & params) const
   {
      QSqlQuery & query = params.query();
      typename QxSqlRelation<DataType, Owner>::type_owner & currOwner = this->getOwner(params);
      IxDataMember * pData = this->getDataMember(); qAssert(pData);
      if (pData) { pData->setSqlPlaceHolder(query, (& currOwner)); }
   }

};

} // namespace qx

#endif // _QX_SQL_RELATION_MANY_TO_ONE_H_
