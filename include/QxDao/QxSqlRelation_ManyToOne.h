/****************************************************************************
**
** Copyright (C) 2010 QxOrm France and/or its subsidiary(-ies)
** Contact: QxOrm France Information (contact@qxorm.com)
**
** This file is part of the QxOrm library
**
** Commercial Usage
** Licensees holding valid QxOrm Commercial licenses may use this file in
** accordance with the QxOrm Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and QxOrm France
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file 'license.gpl3.txt' included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html
**
** If you are unsure which license is appropriate for your use, please
** contact the support department at support@qxorm.com
**
****************************************************************************/

#ifndef _QX_SQL_RELATION_MANY_TO_ONE_H_
#define _QX_SQL_RELATION_MANY_TO_ONE_H_

#ifdef _MSC_VER
#pragma once
#endif

#include "../../include/QxDao/QxSqlRelation.h"

namespace qx {

template <class DataType, class Owner>
class QxSqlRelation_ManyToOne : public QxSqlRelation<DataType, Owner>
{

private:

   typedef typename QxSqlRelation<DataType, Owner>::type_owner type_owner;
   typedef typename QxSqlRelation<DataType, Owner>::type_data type_data;

public:

   QxSqlRelation_ManyToOne(IxDataMember * p) : QxSqlRelation<DataType, Owner>(p) { ; }
   virtual ~QxSqlRelation_ManyToOne() { ; }

   virtual bool getCartesianProduct() const                                   { return false; }
   virtual void lazyFrom(QxSqlRelationParams & params) const                  { Q_UNUSED(params); }
   virtual void eagerFrom(QxSqlRelationParams & params) const                 { Q_UNUSED(params); }
   virtual void lazyJoin(QxSqlRelationParams & params) const                  { Q_UNUSED(params); }
   virtual void lazyWhere(QxSqlRelationParams & params) const                 { Q_UNUSED(params); }
   virtual void eagerWhere(QxSqlRelationParams & params) const                { Q_UNUSED(params); }
   virtual void lazyFetch_ResolveInput(QxSqlRelationParams & params) const    { Q_UNUSED(params); }
   virtual void eagerFetch_ResolveInput(QxSqlRelationParams & params) const   { Q_UNUSED(params); }
   virtual QSqlError onBeforeSave(QxSqlRelationParams & params) const         { Q_UNUSED(params); return QSqlError(); }

   virtual QSqlError onAfterSave(QxSqlRelationParams & params) const
   { return qx::dao::save(this->getData(params), (& params.database())); }

   virtual void lazyUpdate_ResolveInput(QxSqlRelationParams & params) const
   { this->lazyInsert_ResolveInput(params); }

   virtual QVariant getIdFromQuery(bool bEager, QxSqlRelationParams & params) const
   { Q_UNUSED(bEager); return params.query().value(params.offset()); }

   virtual void updateOffset(bool bEager, QxSqlRelationParams & params) const
   { params.setOffset(params.offset() + (this->getDataMember() ? 1 : 0) + (bEager ? (this->getDataCount() + (this->getDataId() ? 1 : 0)) : 0)); }

   virtual void createTable(QxSqlRelationParams & params) const
   {
      QString & sql = params.sql();
      IxDataMember * pData = this->getDataMember(); qAssert(pData);
      if (pData) { sql += pData->getName() + " " + pData->getSqlTypeAndParams() + ", "; qAssert(! pData->getSqlType().isEmpty()); }
   }

   virtual void lazySelect(QxSqlRelationParams & params) const
   {
      QString & sql = params.sql();
      QString tableRef = params.builder().table();
      IxDataMember * pData = this->getDataMember(); qAssert(pData);
      if (pData) { sql += (tableRef + "." + pData->getName() + " AS " + pData->getSqlAlias(& tableRef) + ", "); }
   }

   virtual void eagerSelect(QxSqlRelationParams & params) const
   {
      long l1(0);
      QString & sql = params.sql();
      IxDataMember * pData = this->getDataMember(); qAssert(pData);
      IxDataMember * p = NULL; IxDataMember * pId = this->getDataId(); qAssert(pId);
      //IxSqlRelation * pRelation = NULL;
      //QxSqlQueryBuilder<DataType> builderBis;
      //QxSqlRelationParams paramsBis(0, 0, (& sql), (& builderBis), NULL, NULL);
      QString table = this->table(); QString tableAlias = this->tableAlias(params); QString tableRef = params.builder().table();
      if (pData) { sql += (tableRef + "." + pData->getName() + " AS " + pData->getSqlAlias(& tableRef) + ", "); }
      if (pId) { sql += (tableAlias + "." + pId->getName() + " AS " + pId->getSqlAlias(& tableAlias) + ", "); }
      while ((p = this->nextData(l1))) { sql += (tableAlias + "." + p->getName() + " AS " + p->getSqlAlias(& tableAlias) + ", "); }
      //while ((pRelation = this->nextRelation(l2))) { params.setIndex(m_lOffsetRelation + l2); pRelation->lazySelect(paramsBis); }
   }

   virtual void eagerJoin(QxSqlRelationParams & params) const
   {
      QString & sql = params.sql();
      IxDataMember * pId = this->getDataId(); qAssert(pId);
      IxDataMember * pData = this->getDataMember(); qAssert(pData);
      QString table = this->table(); QString tableAlias = this->tableAlias(params); QString tableRef = params.builder().table();
      if (pId && pData) { sql += this->getSqlJoin() + table + " " + tableAlias + " ON " + pId->getSqlAlias(& tableAlias) + " = " + pData->getSqlAlias(& tableRef); }
   }

   virtual void lazyFetch_ResolveOutput(QxSqlRelationParams & params) const
   {
      if (! this->verifyOffset(params, false)) { return; }
      QSqlQuery & query = params.query();
      typename QxSqlRelation<DataType, Owner>::type_owner & currOwner = this->getOwner(params);
      IxDataMember * pData = this->getDataMember(); qAssert(pData);
      QVariant vId = query.value(params.offset());
      if (pData && qx::trait::is_valid_primary_key(vId)) { pData->fromVariant((& currOwner), vId); }
      params.setOffset(params.offset() + (pData ? 1 : 0));
   }

   virtual void eagerFetch_ResolveOutput(QxSqlRelationParams & params) const
   {
      if (! this->verifyOffset(params, false)) { return; }
      QSqlQuery & query = params.query();
      typename QxSqlRelation<DataType, Owner>::type_owner & currOwner = this->getOwner(params);
      IxDataMember * pData = this->getDataMember(); qAssert(pData);
      IxDataMember * p = NULL; IxDataMember * pId = this->getDataId(); qAssert(pId);
      long lIndex = 0; long lOffsetId = (pId ? 1 : 0); long lOffsetData = (pData ? 1 : 0);
      long lOffsetOld = params.offset(); params.setOffset(lOffsetOld + this->getDataCount() + lOffsetId + lOffsetData);
      long lOffsetRelation = (lOffsetOld + lOffsetId + lOffsetData);
      QVariant vId = query.value(lOffsetOld); bool bValidId = qx::trait::is_valid_primary_key(vId);
      QVariant vIdBis = query.value(lOffsetOld + lOffsetData); bool bValidIdBis = qx::trait::is_valid_primary_key(vIdBis);
      if (pData && bValidId) { pData->fromVariant((& currOwner), vId); }
      if (! bValidIdBis) { return; }
      type_data & currData = this->getData(params);
      if (pId) { pId->fromVariant((& currData), vIdBis); }
      while ((p = this->nextData(lIndex)))
      { p->fromVariant((& currData), query.value(lOffsetRelation++)); }
   }

   virtual void lazyInsert(QxSqlRelationParams & params) const
   {
      QString & sql = params.sql();
      IxDataMember * pData = this->getDataMember(); qAssert(pData);
      if (pData) { sql += pData->getName() + ", "; }
   }

   virtual void lazyInsert_Values(QxSqlRelationParams & params) const
   {
      QString & sql = params.sql();
      IxDataMember * pData = this->getDataMember(); qAssert(pData);
      if (pData) { sql += pData->getSqlPlaceHolder() + ", "; }
   }

   virtual void lazyUpdate(QxSqlRelationParams & params) const
   {
      QString & sql = params.sql();
      IxDataMember * pData = this->getDataMember(); qAssert(pData);
      if (pData) { sql += pData->getName() + " = " + pData->getSqlPlaceHolder() + ", "; }
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
