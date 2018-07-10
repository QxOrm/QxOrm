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

#include <QxDao/QxSqlRelation.h>

namespace qx {

template <class DataType, class Owner>
class QxSqlRelation_OneToOne : public QxSqlRelation<DataType, Owner>
{

private:

   typedef typename QxSqlRelation<DataType, Owner>::type_owner type_owner;
   typedef typename QxSqlRelation<DataType, Owner>::type_data type_data;

public:

   QxSqlRelation_OneToOne(IxDataMember * p) : QxSqlRelation<DataType, Owner>(p) { ; }
   virtual ~QxSqlRelation_OneToOne() { ; }

   virtual bool getCartesianProduct() const                                   { return false; }
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
   { return qx::dao::save(this->getData(params), (& params.database())); }

   virtual QVariant getIdFromQuery(bool bEager, QxSqlRelationParams & params) const
   { return (bEager ? params.query().value(params.offset()) : QVariant()); }

   virtual void updateOffset(bool bEager, QxSqlRelationParams & params) const
   { if (bEager) { params.setOffset(params.offset() + this->getDataCount() + (this->getDataId() ? 1 : 0)); } }

   virtual void eagerSelect(QxSqlRelationParams & params) const
   {
      long l1(0);
      QString & sql = params.sql();
      QString tableAlias = this->tableAlias(params);
      IxDataMember * p = NULL; IxDataMember * pId = this->getDataId(); qAssert(pId);
      //IxSqlRelation * pRelation = NULL;
      //QxSqlQueryBuilder<DataType> builderBis;
      //QxSqlRelationParams paramsBis(0, 0, (& sql), (& builderBis), NULL, NULL);
      if (pId) { sql += (tableAlias + "." + pId->getName() + " AS " + pId->getSqlAlias(& tableAlias) + ", "); }
      while ((p = this->nextData(l1))) { sql += (tableAlias + "." + p->getName() + " AS " + p->getSqlAlias(& tableAlias) + ", "); }
      //while ((pRelation = this->nextRelation(l2))) { params.setIndex(m_lOffsetRelation + l2); pRelation->lazySelect(paramsBis); }
   }

   virtual void eagerJoin(QxSqlRelationParams & params) const
   {
      QString & sql = params.sql();
      IxDataMember * pId = this->getDataId(); qAssert(pId);
      IxDataMember * pIdRef = params.builder().getDataId(); qAssert(pIdRef);
      QString table = this->table(); QString tableAlias = this->tableAlias(params); QString tableRef = params.builder().table();
      if (pId && pIdRef) { sql += this->getSqlJoin() + table + " " + tableAlias + " ON " + pId->getSqlAlias(& tableAlias, true) + " = " + pIdRef->getSqlAlias(& tableRef, true); }
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
      type_data & currData = this->getData(params);
      if (pId) { pId->fromVariant((& currData), vId); }
      while ((p = this->nextData(lIndex)))
      { p->fromVariant((& currData), query.value(lIndex + lOffsetOld + lOffsetId - 1)); }
   }

};

} // namespace qx

#endif // _QX_SQL_RELATION_ONE_TO_ONE_H_
