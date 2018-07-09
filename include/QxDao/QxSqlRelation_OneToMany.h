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

#ifndef _QX_SQL_RELATION_ONE_TO_MANY_H_
#define _QX_SQL_RELATION_ONE_TO_MANY_H_

#ifdef _MSC_VER
#pragma once
#endif

#include "../../include/QxDao/QxSqlRelation.h"

namespace qx {

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

   QString m_sForeignKey;  // Sql query foreign key

public:

   QxSqlRelation_OneToMany(IxDataMember * p, const QString & sForeignKey) : QxSqlRelation<DataType, Owner>(p), m_sForeignKey(sForeignKey) { qAssert(! m_sForeignKey.isEmpty()); }
   virtual ~QxSqlRelation_OneToMany() { BOOST_STATIC_ASSERT(is_data_container); }

   virtual bool getCartesianProduct() const                                   { return true; }
   virtual void createTable(QxSqlRelationParams & params) const               { Q_UNUSED(params); }
   virtual void lazySelect(QxSqlRelationParams & params) const                { Q_UNUSED(params); }
   virtual void lazyFrom(QxSqlRelationParams & params) const                  { Q_UNUSED(params); }
   virtual void eagerFrom(QxSqlRelationParams & params) const                 { Q_UNUSED(params); }
   virtual void lazyJoin(QxSqlRelationParams & params) const                  { Q_UNUSED(params); }
   virtual void lazyWhere(QxSqlRelationParams & params) const                 { Q_UNUSED(params); }
   virtual void eagerWhere(QxSqlRelationParams & params) const                { Q_UNUSED(params); }
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
   { return (bEager ? params.query().value(params.offset()) : QVariant()); }

   virtual void updateOffset(bool bEager, QxSqlRelationParams & params) const
   {
      if (! bEager) { return; }
      IxDataMember * pForeign = this->getDataByKey(m_sForeignKey);
      bool bAddOffsetForeign = (pForeign && ! this->getLstDataMember()->exist(m_sForeignKey));
      long lNewOffset = (params.offset() + this->getDataCount() + (this->getDataId() ? 1 : 0));
      lNewOffset = (lNewOffset + (bAddOffsetForeign ? 1 : 0));
      params.setOffset(lNewOffset);
   }

   virtual void eagerSelect(QxSqlRelationParams & params) const
   {
      long l1(0);
      QString & sql = params.sql();
      IxDataMember * pForeign = this->getDataByKey(m_sForeignKey); qAssert(pForeign);
      IxDataMember * p = NULL; IxDataMember * pId = this->getDataId(); qAssert(pId);
      QString tableAlias = this->tableAlias(params);
      if (pId) { sql += (tableAlias + "." + pId->getName() + " AS " + pId->getSqlAlias(& tableAlias) + ", "); }
      if (pForeign) { sql += (tableAlias + "." + pForeign->getName() + " AS " + pForeign->getSqlAlias(& tableAlias) + ", "); }
      while ((p = this->nextData(l1))) { if (p != pForeign) { sql += (tableAlias + "." + p->getName() + " AS " + p->getSqlAlias(& tableAlias) + ", "); } }
   }

   virtual void eagerJoin(QxSqlRelationParams & params) const
   {
      QString & sql = params.sql();
      IxDataMember * pId = params.builder().getDataId(); qAssert(pId);
      IxDataMember * pForeign = this->getDataByKey(m_sForeignKey); qAssert(pForeign);
      QString table = this->table(); QString tableAlias = this->tableAlias(params); QString tableRef = params.builder().table();
      if (pId && pForeign) { sql += this->getSqlJoin() + table + " " + tableAlias + " ON " + pForeign->getSqlAlias(& tableAlias) + " = " + pId->getSqlAlias(& tableRef); }
   }

   virtual void eagerFetch_ResolveOutput(QxSqlRelationParams & params) const
   {
      if (! this->verifyOffset(params, true)) { return; }
      QSqlQuery & query = params.query();
      IxDataMember * pForeign = this->getDataByKey(m_sForeignKey); qAssert(pForeign);
      IxDataMember * p = NULL; IxDataMember * pId = this->getDataId(); qAssert(pId);
      long lIndex = 0; long lOffsetId = (pId ? 1 : 0); long lOffsetForeign = (pForeign ? 1 : 0);
      long lOffsetOld = params.offset(); this->updateOffset(true, params);
      long lOffsetRelation = (lOffsetOld + lOffsetId + lOffsetForeign);
      QVariant vId = query.value(lOffsetOld);
      QVariant vForeign = query.value(lOffsetOld + lOffsetId);
      bool bValidId = qx::trait::is_valid_primary_key(vId);
      bool bValidForeign = qx::trait::is_valid_primary_key(vForeign);
      if (! bValidId || ! bValidForeign) { return; }
      type_item item = this->createItem();
      type_data & item_val = item.value_qx();
      qx::cvt::from_variant(vId, item.key());
      if (pId) { pId->fromVariant((& item_val), vId); }
      if (pForeign) { pForeign->fromVariant((& item_val), vForeign); }
      while ((p = this->nextData(lIndex)))
      { if (p != pForeign) { p->fromVariant((& item_val), query.value(lOffsetRelation++)); } }
      type_generic_container::insertItem(this->getContainer(params), item);
   }

};

} // namespace qx

#endif // _QX_SQL_RELATION_ONE_TO_MANY_H_
