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

#ifndef _QX_SQL_RELATION_ONE_TO_ONE_H_
#define _QX_SQL_RELATION_ONE_TO_ONE_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSqlRelation_OneToOne.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Manage a relationship one-to-one defined between 2 classes (or between 2 tables in database)
 */

#include <QxDao/QxSqlRelation.h>

namespace qx {

/*!
 * \ingroup QxDao
 * \brief qx::QxSqlRelation_OneToOne<DataType, Owner> : manage a relationship one-to-one defined between 2 classes (or between 2 tables in database)
 */
template <class DataType, class Owner>
class QxSqlRelation_OneToOne : public QxSqlRelation<DataType, Owner>
{

private:

   typedef typename QxSqlRelation<DataType, Owner>::type_owner type_owner;
   typedef typename QxSqlRelation<DataType, Owner>::type_data type_data;

public:

   QxSqlRelation_OneToOne(IxDataMember * p) : QxSqlRelation<DataType, Owner>(p) { this->m_eRelationType = qx::IxSqlRelation::one_to_one; }
   virtual ~QxSqlRelation_OneToOne() { ; }

   virtual QString getDescription() const                                     { return "relation one-to-one"; }
   virtual QString getExtraTable() const                                      { return ""; }
   virtual QString createExtraTable() const                                   { return ""; }
   virtual bool getCartesianProduct() const                                   { return false; }
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
   {
      if (this->isNullData(params)) { return QSqlError(); }
      return qx::dao::save(this->getData(params), (& params.database()));
   }

   virtual QVariant getIdFromQuery(bool bEager, QxSqlRelationParams & params) const
   {
      QString sId; IxDataMember * pId = this->getDataId(); if (! bEager || ! pId) { return QVariant(); }
      for (int i = 0; i < pId->getNameCount(); i++) { sId += params.query().value(params.offset() + i).toString() + "|"; }
      return QVariant(sId);
   }

   virtual void updateOffset(bool bEager, QxSqlRelationParams & params) const
   {
      if (! bEager) { return; }
      long lOffsetNew = params.offset() + this->getDataCount();
      lOffsetNew += (this->getDataId() ? this->getDataId()->getNameCount() : 0);
      lOffsetNew += (this->m_oSoftDelete.isEmpty() ? 0 : 1);
      params.setOffset(lOffsetNew);
   }

   virtual void eagerSelect(QxSqlRelationParams & params) const
   {
      long l1(0);
      QString & sql = params.sql();
      QString tableAlias = this->tableAlias(params);
      IxDataMember * p = NULL; IxDataMember * pId = this->getDataId(); qAssert(pId);
      if (pId) { sql += (pId->getSqlTablePointNameAsAlias(tableAlias) + ", "); }
      while ((p = this->nextData(l1))) { sql += (p->getSqlTablePointNameAsAlias(tableAlias) + ", "); }
      if (! this->m_oSoftDelete.isEmpty()) { sql += (this->m_oSoftDelete.buildSqlTablePointName(tableAlias) + ", "); }
   }

   virtual void eagerJoin(QxSqlRelationParams & params) const
   {
      QString & sql = params.sql();
      IxDataMember * pId = this->getDataId(); qAssert(pId);
      IxDataMember * pIdRef = this->getDataIdOwner(); qAssert(pIdRef);
      QString table = this->table(); QString tableAlias = this->tableAlias(params);
      QString tableRef = this->tableAliasOwner(params);
      if (! pId || ! pIdRef) { return; }
      sql += this->getSqlJoin(params.joinType()) + table + " " + tableAlias + " ON ";
      params.builder().addSqlQueryAlias(table, tableAlias);
      for (int i = 0; i < pId->getNameCount(); i++)
      { sql += pId->getSqlAlias(tableAlias, true, i) + " = " + pIdRef->getSqlAlias(tableRef, true, i) + " AND "; }
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

   virtual void * eagerFetch_ResolveOutput(QxSqlRelationParams & params) const
   {
      if (! this->verifyOffset(params, true)) { return NULL; }
      QSqlQuery & query = params.query();
      IxDataMember * p = NULL; IxDataMember * pId = this->getDataId(); qAssert(pId); if (! pId) { return NULL; }
      long lIndex = 0; long lOffsetId = (pId ? pId->getNameCount() : 0); bool bValidId(false);
      long lOffsetOld = params.offset(); this->updateOffset(true, params);
      for (int i = 0; i < pId->getNameCount(); i++)
      { QVariant v = query.value(lOffsetOld + i); bValidId = (bValidId || qx::trait::is_valid_primary_key(v)); }
      if (! bValidId) { return NULL; }
      type_data & currData = this->getData(params);
      for (int i = 0; i < pId->getNameCount(); i++)
      { QVariant v = query.value(lOffsetOld + i); pId->fromVariant((& currData), v, i); }
      while ((p = this->nextData(lIndex)))
      { p->fromVariant((& currData), query.value(lIndex + lOffsetOld + lOffsetId - 1)); }
      return (& currData);
   }

};

} // namespace qx

#endif // _QX_SQL_RELATION_ONE_TO_ONE_H_
