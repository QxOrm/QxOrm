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

   QxSqlRelation_OneToOne(IxDataMember * p) : QxSqlRelation<DataType, Owner>(p) { this->setRelationType(qx::IxSqlRelation::one_to_one); }
   virtual ~QxSqlRelation_OneToOne() { ; }

   virtual QString getDescription() const                                     { return "relation one-to-one"; }
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
      if (! params.recursiveMode()) { return qx::dao::save(this->getData(params), (& params.database())); }
      else { return qx::dao::save_with_relation_recursive(this->getData(params), params.saveMode(), (& params.database()), (& params)); }
   }

   virtual QVariant getIdFromQuery(bool bEager, QxSqlRelationParams & params) const
   { return this->getIdFromQuery_OneToOne(bEager, params); }

   virtual void updateOffset(bool bEager, QxSqlRelationParams & params) const
   { this->updateOffset_OneToOne(bEager, params); }

   virtual void eagerSelect(QxSqlRelationParams & params) const
   { this->eagerSelect_OneToOne(params); }

   virtual void eagerJoin(QxSqlRelationParams & params) const
   { this->eagerJoin_OneToOne(params); }

   virtual void eagerWhereSoftDelete(QxSqlRelationParams & params) const
   { this->eagerWhereSoftDelete_OneToOne(params); }

   virtual void * eagerFetch_ResolveOutput(QxSqlRelationParams & params) const
   {
      if (! this->verifyOffset(params, true)) { return NULL; }
      QSqlQuery & query = params.query();
      IxDataMember * p = NULL; IxDataMember * pId = this->getDataId(); qAssert(pId); if (! pId) { return NULL; }
      long lIndex = 0; long lOffsetId = (pId ? pId->getNameCount() : 0); bool bValidId(false);
      long lOffsetOld = params.offset(); this->updateOffset(true, params);
      long lRelation = 0; IxSqlRelation * pRelation = NULL;
      for (int i = 0; i < pId->getNameCount(); i++)
      { QVariant v = query.value(lOffsetOld + i); bValidId = (bValidId || qx::trait::is_valid_primary_key(v)); }
      if (! bValidId) { return NULL; }

      type_data & currData = this->getData(params);
      if (! this->callTriggerBeforeFetch(currData, params)) { return NULL; }
      for (int i = 0; i < pId->getNameCount(); i++)
      { QVariant v = query.value(lOffsetOld + i); pId->fromVariant((& currData), v, i, qx::cvt::context::e_database); }
      long lOffsetRelation = (lOffsetOld + lOffsetId); long lCurrIndex = 0;
      while ((p = this->nextData(lIndex)))
      { if (params.checkColumns(p->getKey())) { p->fromVariant((& currData), query.value(lCurrIndex + lOffsetRelation), -1, qx::cvt::context::e_database); lCurrIndex++; } }

      if (params.relationX())
      {
         long lOffsetCurrent = (lCurrIndex + lOffsetRelation);
         long lIndexOwnerOld = params.indexOwner(); params.setIndexOwner(params.index());
         void * pOwnerOld = params.owner(); params.setOwner(& currData);
         lOffsetOld = params.offset(); params.setOffset(lOffsetCurrent);
         while ((pRelation = this->nextRelation(lRelation)))
         { if (this->addLazyRelation(params, pRelation)) { pRelation->lazyFetch_ResolveOutput(params); } }
         params.setOwner(pOwnerOld); params.setOffset(lOffsetOld);
         params.setIndexOwner(lIndexOwnerOld);
      }

      if (! this->callTriggerAfterFetch(currData, params)) { return NULL; }
      return (& currData);
   }

};

} // namespace qx

#endif // _QX_SQL_RELATION_ONE_TO_ONE_H_
