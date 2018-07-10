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
   typedef typename type_generic_container::type_iterator type_iterator;
   typedef typename type_item::type_value type_value;

   enum { is_data_container = QxSqlRelation<DataType, Owner>::is_data_container };

public:

   QxSqlRelation_OneToMany(IxDataMember * p, const QString & sForeignKey) : QxSqlRelation<DataType, Owner>(p) { this->setRelationType(qx::IxSqlRelation::one_to_many); this->setForeignKey(sForeignKey); qAssert(! this->getForeignKey().isEmpty()); }
   virtual ~QxSqlRelation_OneToMany() { static_assert(is_data_container, "is_data_container"); }

   virtual QString getDescription() const                                     { return "relation one-to-many"; }
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
   {
      if (this->isNullData(params)) { return QSqlError(); }
      this->forceParentIdToAllChildren(params);
      if (! params.recursiveMode()) { return qx::dao::save(this->getContainer(params), (& params.database())); }
      else { return qx::dao::save_with_relation_recursive(this->getContainer(params), params.saveMode(), (& params.database()), (& params)); }
   }

   virtual QVariant getIdFromQuery(bool bEager, QxSqlRelationParams & params) const
   { return this->getIdFromQuery_OneToMany(bEager, params); }

   virtual void updateOffset(bool bEager, QxSqlRelationParams & params) const
   { this->updateOffset_OneToMany(bEager, params); }

   virtual void eagerSelect(QxSqlRelationParams & params) const
   { this->eagerSelect_OneToMany(params); }

   virtual void eagerJoin(QxSqlRelationParams & params) const
   { this->eagerJoin_OneToMany(params); }

   virtual void eagerWhereSoftDelete(QxSqlRelationParams & params) const
   { this->eagerWhereSoftDelete_OneToMany(params); }

   virtual void * eagerFetch_ResolveOutput(QxSqlRelationParams & params) const
   {
      if (! this->verifyOffset(params, true)) { return NULL; }
      QSqlQuery & query = params.query();
      IxDataMember * p = NULL; IxDataMember * pId = this->getDataId(); qAssert(pId); if (! pId) { return NULL; }
      IxDataMember * pForeign = this->getDataByKey(this->getForeignKey()); qAssert(pForeign); if (! pForeign) { return NULL; }
      long lIndex = 0; long lOffsetId = (pId ? pId->getNameCount() : 0); long lOffsetForeign = (pForeign ? pForeign->getNameCount() : 0);
      long lOffsetOld = params.offset(); this->updateOffset(true, params);
      long lOffsetRelation = (lOffsetOld + lOffsetId + lOffsetForeign);
      long lRelation = 0; IxSqlRelation * pRelation = NULL;
      bool bValidId(false), bValidForeign(false);
      for (int i = 0; i < pId->getNameCount(); i++)
      { QVariant vId = query.value(lOffsetOld + i); bValidId = (bValidId || qx::trait::is_valid_primary_key(vId)); }
      for (int i = 0; i < pForeign->getNameCount(); i++)
      { QVariant vForeign = query.value(lOffsetOld + lOffsetId + i); bValidForeign = (bValidForeign || qx::trait::is_valid_primary_key(vForeign)); }
      if (! bValidId || ! bValidForeign) { return NULL; }

      type_item item = this->createItem();
      type_data & item_val = item.value_qx();
      if (! this->callTriggerBeforeFetch(item_val, params)) { return NULL; }
      for (int i = 0; i < pId->getNameCount(); i++)
      { QVariant v = query.value(lOffsetOld + i); qx::cvt::from_variant(v, item.key(), "", i, qx::cvt::context::e_database); }
      for (int i = 0; i < pId->getNameCount(); i++)
      { QVariant v = query.value(lOffsetOld + i); pId->fromVariant((& item_val), v, "", i, qx::cvt::context::e_database); }
      for (int i = 0; i < pForeign->getNameCount(); i++)
      { QVariant v = query.value(lOffsetOld + lOffsetId + i); pForeign->fromVariant((& item_val), v, "", i, qx::cvt::context::e_database); }
      while ((p = this->nextData(lIndex)))
      { if ((p != pForeign) && (params.checkColumns(p->getKey()))) { p->fromVariant((& item_val), query.value(lOffsetRelation++), -1, qx::cvt::context::e_database); } }

      if (params.relationX())
      {
         long lIndexOwnerOld = params.indexOwner(); params.setIndexOwner(params.index());
         void * pOwnerOld = params.owner(); params.setOwner(& item_val);
         lOffsetOld = params.offset(); params.setOffset(lOffsetRelation++);
         while ((pRelation = this->nextRelation(lRelation)))
         { if (this->addLazyRelation(params, pRelation)) { pRelation->lazyFetch_ResolveOutput(params); } }
         params.setOwner(pOwnerOld); params.setOffset(lOffsetOld);
         params.setIndexOwner(lIndexOwnerOld);
      }

      if (! this->callTriggerAfterFetch(item_val, params)) { return NULL; }
      type_value * pValue = type_generic_container::insertItem(this->getContainer(params), item);
      if (! type_item::is_value_pointer && pValue) { return pValue; }
      return (& item_val);
   }

private:

   void forceParentIdToAllChildren(QxSqlRelationParams & params) const
   {
      bool bForce = qx::QxSqlDatabase::getSingleton()->getForceParentIdToAllChildren();
      if (! bForce || ! params.owner()) { return; }
      IxDataMember * pIdOwner = this->getDataIdOwner(); if (! pIdOwner) { return; }
      IxDataMember * pForeign = this->getDataByKey(this->getForeignKey()); if (! pForeign) { return; }
      if (pIdOwner->getNameCount() != pForeign->getNameCount()) { return; }

      QList<QVariant> vIdOwner;
      for (int i = 0; i < pIdOwner->getNameCount(); i++)
      { vIdOwner.append(pIdOwner->toVariant(params.owner(), i, qx::cvt::context::e_database)); }

      type_item item;
      type_container & container = this->getContainer(params);
      type_iterator itr = type_generic_container::begin(container, item);
      type_iterator itr_end = type_generic_container::end(container);

      while (itr != itr_end)
      {
         type_data & item_val = item.value_qx();
         for (int i = 0; i < vIdOwner.count(); i++)
         { pForeign->fromVariant((& item_val), vIdOwner.at(i), "", i, qx::cvt::context::e_database); }
         itr = type_generic_container::next(container, itr, item);
      }
   }

};

} // namespace qx

#endif // _QX_SQL_RELATION_ONE_TO_MANY_H_
