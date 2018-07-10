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

#ifndef _QX_SQL_RELATION_MANY_TO_MANY_H_
#define _QX_SQL_RELATION_MANY_TO_MANY_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QxDao/QxSqlRelation.h>

namespace qx {

template <class DataType, class Owner>
class QxSqlRelation_ManyToMany : public QxSqlRelation<DataType, Owner>
{

private:

   typedef typename QxSqlRelation<DataType, Owner>::type_owner type_owner;
   typedef typename QxSqlRelation<DataType, Owner>::type_data type_data;
   typedef typename QxSqlRelation<DataType, Owner>::type_container type_container;
   typedef typename QxSqlRelation<DataType, Owner>::type_generic_container type_generic_container;
   typedef typename QxSqlRelation<DataType, Owner>::type_item type_item;
   typedef typename type_generic_container::type_iterator type_iterator;

   enum { is_data_container = QxSqlRelation<DataType, Owner>::is_data_container };

protected:

   QString m_sExtraTable;           // Extra table that holds the relationship
   QString m_sForeignKeyOwner;      // Sql query foreign key for owner
   QString m_sForeignKeyDataType;   // Sql query foreign key for data type

public:

   QxSqlRelation_ManyToMany(IxDataMember * p, const QString & sExtraTable, const QString & sForeignKeyOwner, const QString & sForeignKeyDataType) : QxSqlRelation<DataType, Owner>(p), m_sExtraTable(sExtraTable), m_sForeignKeyOwner(sForeignKeyOwner), m_sForeignKeyDataType(sForeignKeyDataType) { this->verify(); }
   virtual ~QxSqlRelation_ManyToMany() { BOOST_STATIC_ASSERT(is_data_container); }

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

   virtual QVariant getIdFromQuery(bool bEager, QxSqlRelationParams & params) const
   { return (bEager ? params.query().value(params.offset()) : QVariant()); }

   virtual void updateOffset(bool bEager, QxSqlRelationParams & params) const
   { if (bEager) { params.setOffset(params.offset() + this->getDataCount() + (this->getDataId() ? 1 : 0)); } }

   virtual void eagerSelect(QxSqlRelationParams & params) const
   {
      long l1(0);
      QString & sql = params.sql();
      IxDataMember * p = NULL; IxDataMember * pId = this->getDataId(); qAssert(pId);
      QString tableAlias = this->tableAlias(params);
      if (pId) { sql += (tableAlias + "." + pId->getName() + " AS " + pId->getSqlAlias(& tableAlias) + ", "); }
      while ((p = this->nextData(l1))) { sql += (tableAlias + "." + p->getName() + " AS " + p->getSqlAlias(& tableAlias) + ", "); }
   }

   virtual void eagerJoin(QxSqlRelationParams & params) const
   {
      QString & sql = params.sql();
      IxDataMember * pIdOwner = params.builder().getDataId(); qAssert(pIdOwner);
      IxDataMember * pIdData = this->getDataId(); qAssert(pIdData);
      QString table = this->table(); QString tableAlias = this->tableAlias(params); QString tableOwner = params.builder().table();
      if (! pIdOwner || ! pIdData) { return; }
      sql += this->getSqlJoin() + m_sExtraTable + " ON " + pIdOwner->getSqlAlias(& tableOwner, true) + " = " + m_sExtraTable + "." + m_sForeignKeyOwner;
      sql += this->getSqlJoin() + table + " " + tableAlias + " ON " + m_sExtraTable + "." + m_sForeignKeyDataType + " = " + pIdData->getSqlAlias(& tableAlias, true);
   }

   virtual void eagerFetch_ResolveOutput(QxSqlRelationParams & params) const
   {
      if (! this->verifyOffset(params, true)) { return; }
      QSqlQuery & query = params.query();
      IxDataMember * p = NULL; IxDataMember * pId = this->getDataId(); qAssert(pId);
      long lIndex = 0; long lOffsetId = (pId ? 1 : 0);
      long lOffsetOld = params.offset(); params.setOffset(lOffsetOld + this->getDataCount() + lOffsetId);
      QVariant vId = query.value(lOffsetOld);
      if (! qx::trait::is_valid_primary_key(vId)) { return; }
      type_item item = this->createItem();
      type_data & item_val = item.value_qx();
      qx::cvt::from_variant(vId, item.key());
      if (pId) { pId->fromVariant((& item_val), vId); }
      while ((p = this->nextData(lIndex)))
      { p->fromVariant((& item_val), query.value(lIndex + lOffsetOld + lOffsetId - 1)); }
      type_generic_container::insertItem(this->getContainer(params), item);
   }

   virtual QSqlError onAfterSave(QxSqlRelationParams & params) const
   {
      QSqlError daoError = qx::dao::save(this->getContainer(params), (& params.database()));
      if (daoError.isValid()) { return daoError; }
      daoError = this->deleteFromExtraTable(params);
      if (daoError.isValid()) { return daoError; }
      daoError = this->insertIntoExtraTable(params);
      if (daoError.isValid()) { return daoError; }

      return QSqlError();
   }

private:

   inline void verify()
   { qAssert(! m_sExtraTable.isEmpty() && ! m_sForeignKeyOwner.isEmpty() && ! m_sForeignKeyDataType.isEmpty() && (m_sForeignKeyOwner != m_sForeignKeyDataType)); }

   QSqlError deleteFromExtraTable(QxSqlRelationParams & params) const
   {
      IxDataMember * pIdOwner = params.builder().getDataId(); qAssert(pIdOwner);
      QString sqlId = m_sExtraTable + "." + m_sForeignKeyOwner;
      QString sql = "DELETE FROM " + m_sExtraTable;
      sql += " WHERE " + sqlId + " = " + pIdOwner->getSqlPlaceHolder();
      qDebug("[QxOrm] sql query (extra-table) : %s", qPrintable(sql));

      QSqlQuery queryDelete(params.database());
      queryDelete.prepare(sql);
      pIdOwner->setSqlPlaceHolder(queryDelete, params.owner());
      if (! queryDelete.exec()) { return queryDelete.lastError(); }

      return QSqlError();
   }

   QSqlError insertIntoExtraTable(QxSqlRelationParams & params) const
   {
      IxDataMember * pIdOwner = params.builder().getDataId(); qAssert(pIdOwner);
      IxDataMember * pIdData = this->getDataId(); qAssert(pIdData);
      QString sql = "INSERT INTO " + m_sExtraTable + " (";
      sql += pIdOwner->getName() + ", " + pIdData->getName() + ") VALUES (";
      sql += pIdOwner->getSqlPlaceHolder() + ", " + pIdData->getSqlPlaceHolder() + ")";
      qDebug("[QxOrm] sql query (extra-table) : %s", qPrintable(sql));

      type_item item;
      type_container container = this->getContainer(params);
      type_iterator itr = type_generic_container::begin(container, item);
      type_iterator itr_end = type_generic_container::end(container);
      QSqlQuery queryInsert(params.database());
      queryInsert.prepare(sql);

      while (itr != itr_end)
      {
         pIdOwner->setSqlPlaceHolder(queryInsert, params.owner());
         pIdData->setSqlPlaceHolder(queryInsert, (& item.value_qx()));
         if (! queryInsert.exec()) { return queryInsert.lastError(); }
         itr = type_generic_container::next(container, itr, item);
      }

      return QSqlError();
   }

};

} // namespace qx

#endif // _QX_SQL_RELATION_MANY_TO_MANY_H_
