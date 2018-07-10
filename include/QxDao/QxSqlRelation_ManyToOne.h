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

   QxSqlRelation_ManyToOne(IxDataMember * p) : QxSqlRelation<DataType, Owner>(p) { this->setRelationType(qx::IxSqlRelation::many_to_one); }
   virtual ~QxSqlRelation_ManyToOne() { ; }

   virtual QString getDescription() const                                     { return "relation many-to-one"; }
   virtual QString createExtraTable() const                                   { return ""; }
   virtual bool getCartesianProduct() const                                   { return false; }
   virtual void lazyFrom(QxSqlRelationParams & params) const                  { Q_UNUSED(params); }
   virtual void eagerFrom(QxSqlRelationParams & params) const                 { Q_UNUSED(params); }
   virtual void lazyJoin(QxSqlRelationParams & params) const                  { Q_UNUSED(params); }
   virtual void lazyWhere(QxSqlRelationParams & params) const                 { Q_UNUSED(params); }
   virtual void eagerWhere(QxSqlRelationParams & params) const                { Q_UNUSED(params); }
   virtual void lazyWhereSoftDelete(QxSqlRelationParams & params) const       { Q_UNUSED(params); }
   virtual void lazyFetch_ResolveInput(QxSqlRelationParams & params) const    { Q_UNUSED(params); }
   virtual void eagerFetch_ResolveInput(QxSqlRelationParams & params) const   { Q_UNUSED(params); }
   virtual QSqlError onAfterSave(QxSqlRelationParams & params) const          { Q_UNUSED(params); return QSqlError(); }

   virtual QSqlError onBeforeSave(QxSqlRelationParams & params) const
   {
      if (this->isNullData(params) || params.recursiveMode()) { return QSqlError(); }
      return qx::dao::save(this->getData(params), (& params.database()));
   }

   virtual void lazyUpdate_ResolveInput(QxSqlRelationParams & params) const
   { this->lazyInsert_ResolveInput(params); }

   virtual QVariant getIdFromQuery(bool bEager, QxSqlRelationParams & params) const
   { return this->getIdFromQuery_ManyToOne(bEager, params); }

   virtual void updateOffset(bool bEager, QxSqlRelationParams & params) const
   { this->updateOffset_ManyToOne(bEager, params); }

   virtual void createTable(QxSqlRelationParams & params) const
   { this->createTable_ManyToOne(params); }

   virtual void lazySelect(QxSqlRelationParams & params) const
   { this->lazySelect_ManyToOne(params); }

   virtual void eagerSelect(QxSqlRelationParams & params) const
   { this->eagerSelect_ManyToOne(params); }

   virtual void eagerJoin(QxSqlRelationParams & params) const
   { this->eagerJoin_ManyToOne(params); }

   virtual void eagerWhereSoftDelete(QxSqlRelationParams & params) const
   { this->eagerWhereSoftDelete_ManyToOne(params); }

   virtual void lazyFetch_ResolveOutput(QxSqlRelationParams & params) const
   {
      if (! this->verifyOffset(params, false)) { return; }
      QSqlQuery & query = params.query();
      typename QxSqlRelation<DataType, Owner>::type_owner & currOwner = this->getOwner(params);
      IxDataMember * pData = this->getDataMember(); qAssert(pData); if (! pData) { return; }
      bool bValidId(false);
      for (int i = 0; i < pData->getNameCount(); i++)
      { QVariant vId = query.value(params.offset() + i); bValidId = (bValidId || qx::trait::is_valid_primary_key(vId)); }
      if (pData && bValidId) { for (int i = 0; i < pData->getNameCount(); i++) { pData->fromVariant((& currOwner), query.value(params.offset() + i), i, qx::cvt::context::e_database); } }
      this->updateOffset(false, params);
   }

   virtual void * eagerFetch_ResolveOutput(QxSqlRelationParams & params) const
   {
      if (! this->verifyOffset(params, false)) { return NULL; }
      QSqlQuery & query = params.query();
      typename QxSqlRelation<DataType, Owner>::type_owner & currOwner = this->getOwner(params);
      IxDataMember * pData = this->getDataMember(); qAssert(pData); if (! pData) { return NULL; }
      IxDataMember * p = NULL; IxDataMember * pId = this->getDataId(); qAssert(pId); if (! pId) { return NULL; }
      long lIndex = 0; long lOffsetId = (pId ? pId->getNameCount() : 0); long lOffsetData = (pData ? pData->getNameCount() : 0);
      long lOffsetOld = params.offset(); this->updateOffset(true, params);
      long lOffsetRelation = (lOffsetOld + lOffsetId + lOffsetData);
      long lRelation = 0; IxSqlRelation * pRelation = NULL;
      bool bValidId(false), bValidIdBis(false);
      for (int i = 0; i < pData->getNameCount(); i++)
      { QVariant vId = query.value(lOffsetOld + i); bValidId = (bValidId || qx::trait::is_valid_primary_key(vId)); }
      for (int i = 0; i < pId->getNameCount(); i++)
      { QVariant vIdBis = query.value(lOffsetOld + lOffsetData + i); bValidIdBis = (bValidIdBis || qx::trait::is_valid_primary_key(vIdBis)); }
      if (pData && bValidId) { for (int i = 0; i < pData->getNameCount(); i++) { pData->fromVariant((& currOwner), query.value(lOffsetOld + i), i, qx::cvt::context::e_database); } }
      if (! bValidIdBis) { return NULL; }

      type_data & currData = this->getData(params);
      if (! this->callTriggerBeforeFetch(currData, params)) { return NULL; }
      if (pId) { for (int i = 0; i < pId->getNameCount(); i++) { pId->fromVariant((& currData), query.value(lOffsetOld + lOffsetData + i), i, qx::cvt::context::e_database); } }
      while ((p = this->nextData(lIndex)))
      { if (params.checkColumns(p->getKey())) { p->fromVariant((& currData), query.value(lOffsetRelation++), -1, qx::cvt::context::e_database); } }

      if (params.relationX())
      {
         long lIndexOwnerOld = params.indexOwner(); params.setIndexOwner(params.index());
         void * pOwnerOld = params.owner(); params.setOwner(& currData);
         lOffsetOld = params.offset(); params.setOffset(lOffsetRelation++);
         while ((pRelation = this->nextRelation(lRelation)))
         { if (this->addLazyRelation(params, pRelation)) { pRelation->lazyFetch_ResolveOutput(params); } }
         params.setOwner(pOwnerOld); params.setOffset(lOffsetOld);
         params.setIndexOwner(lIndexOwnerOld);
      }

      if (! this->callTriggerAfterFetch(currData, params)) { return NULL; }
      return (& currData);
   }

   virtual void lazyInsert(QxSqlRelationParams & params) const
   { this->lazyInsert_ManyToOne(params); }

   virtual void lazyInsert_Values(QxSqlRelationParams & params) const
   { this->lazyInsert_Values_ManyToOne(params); }

   virtual void lazyUpdate(QxSqlRelationParams & params) const
   { this->lazyUpdate_ManyToOne(params); }

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
