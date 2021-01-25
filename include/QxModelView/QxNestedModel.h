/****************************************************************************
**
** https://www.qxorm.com/
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

#ifndef _QX_NESTED_MODEL_H_
#define _QX_NESTED_MODEL_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxNestedModel.h
 * \author Lionel Marty
 * \ingroup QxModelView
 * \brief qx::model_view::create_nested_model is used by QxEntityEditor to manage complex data structure to work with relationships in QML views and Qt model/view architecture
 */

#include <QxConvert/QxConvert.h>

#include <QxCollection/QxCollection.h>

#include <QxTraits/is_qx_registered.h>
#include <QxTraits/is_container.h>
#include <QxTraits/is_smart_ptr.h>
#include <QxTraits/get_base_class.h>
#include <QxTraits/get_class_name_primitive.h>
#include <QxTraits/construct_ptr.h>
#include <QxTraits/generic_container.h>
#include <QxTraits/is_valid_primary_key.h>

#include <QxSerialize/QxClone.h>

#include <QxModelView/IxModel.h>
#include <QxModelView/QxModel.h>

namespace qx {
namespace model_view {

template <class T>
qx::IxModel * create_nested_model(qx::IxModel * pParent, const QModelIndex & idxParent, T & t);

template <class T, class M>
qx::IxModel * create_nested_model_with_type(qx::IxModel * pParent, const QModelIndex & idxParent, T & t, M * pModelType);

template <class T>
void sync_nested_model(qx::IxModel * pModel, T & t);

} // namespace model_view
} // namespace qx

namespace qx {
namespace model_view {
namespace detail {

template <class T, class M /* = void */>
struct QxNestedModel;

template <class T, bool bIsQObject /* = false */>
struct QxNestedModel_Helper
{

   static std::shared_ptr<T> clone(T & t)
   { std::shared_ptr<T> p = std::make_shared<T>(); (* p) = t; return p; }

   static void synchronize(T & t1, T & t2)
   { t1 = t2; }

};

template <class T>
struct QxNestedModel_Helper<T, true>
{

   static std::shared_ptr<T> clone(T & t)
   { std::shared_ptr<T> p; p.reset(qx::clone_to_nude_ptr(t)); qAssert(p); return p; }

   static void synchronize(T & t1, T & t2)
   {
      qx::IxClass * pClass = qx::QxClass<T>::getSingleton();
      qx::IxDataMemberX * pDataMemberX = (pClass ? pClass->getDataMemberX() : NULL);
      for (long l = 0; (pDataMemberX && (l < pDataMemberX->count_WithDaoStrategy())); l++)
      {
         qx::IxDataMember * pDataMember = pDataMemberX->get_WithDaoStrategy(l); if (! pDataMember) { continue; }
         QVariant value = pDataMember->toVariant(& t2);
         pDataMember->fromVariant((& t1), value);
      }
   }

};

template <class T, class M, bool bIsTypeVoid /* = false */>
struct QxNestedModel_Creator
{ static qx::IxModel * newModel(qx::IxModel * pParent) { return new M(pParent); } };

template <class T, class M>
struct QxNestedModel_Creator<T, M, true>
{ static qx::IxModel * newModel(qx::IxModel * pParent) { return new qx::QxModel<T>(pParent); } };

template <class T, class M /* = void */>
struct QxNestedModel_Generic
{

   typedef typename qx::QxModel<T>::type_collection type_collection;
   typedef typename qx::QxModel<T>::type_primary_key type_primary_key;
   typedef typename qx::QxModel<T>::type_ptr type_ptr;

   enum { is_valid = qx::trait::is_qx_registered<T>::value };

   static inline qx::IxModel * create(qx::IxModel * pParent, const QModelIndex & idxParent, T & t)
   {
      static_assert(is_valid, "is_valid");
      qx::IxModel * pModel = qx::model_view::detail::QxNestedModel_Creator<T, M, std::is_same<M, void>::value>::newModel(pParent);
      pModel->setParentModel(pParent);
      type_collection * pListOfItems = static_cast<type_collection *>(pModel->getCollection());
      long & idx = pModel->m_lManualInsertIndex;
      type_primary_key key;

      pModel->beginInsertRows(idxParent, 0, 0);
      type_ptr ptr = qx::model_view::detail::QxNestedModel_Helper<T, std::is_base_of<QObject, T>::value>::clone(t);
      qx::IxDataMember * pDataMemberId = pModel->m_pDataMemberId;
      if (! pDataMemberId) { qAssert(false); pModel->endInsertRows(); return pModel; }
      QVariant value = pDataMemberId->toVariant(& t);
      if (! qx::trait::is_valid_primary_key(value))
      { idx--; value = QVariant(static_cast<qlonglong>(idx)); }
      qx::cvt::from_variant(value, key);
      pListOfItems->insert(0, key, ptr);
      pModel->endInsertRows();
      return pModel;
   }

   static inline void synchronize(qx::IxModel * pModel, T & t)
   {
      if (! pModel) { qAssert(false); return; }
      type_collection * pListOfItems = static_cast<type_collection *>(pModel->getCollection());
      if (! pListOfItems || (pListOfItems->count() <= 0)) { return; }
      type_ptr ptr = pListOfItems->getByIndex(0); if (! ptr) { return; }
      qx::model_view::detail::QxNestedModel_Helper<T, std::is_base_of<QObject, T>::value>::synchronize(t, (* ptr));
   }

};

template <class T, class M /* = void */>
struct QxNestedModel_Container
{

   typedef qx::trait::generic_container<T> type_generic_container;
   typedef typename type_generic_container::type_value_qx type_data;
   typedef typename type_generic_container::type_item type_item;
   typedef typename qx::QxModel<type_data>::type_collection type_collection;
   typedef typename qx::QxModel<type_data>::type_primary_key type_primary_key;
   typedef typename qx::QxModel<type_data>::type_ptr type_ptr;

   enum { is_valid = qx::trait::is_qx_registered<type_data>::value };

   static inline qx::IxModel * create(qx::IxModel * pParent, const QModelIndex & idxParent, T & t)
   {
      int iCurrRow = 0;
      static_assert(is_valid, "is_valid");
      qx::IxModel * pModel = qx::model_view::detail::QxNestedModel_Creator<type_data, M, std::is_same<M, void>::value>::newModel(pParent);
      pModel->setParentModel(pParent);
      long lCount = static_cast<long>(type_generic_container::size(t));
      if (lCount <= 0) { return pModel; }

      pModel->beginInsertRows(idxParent, 0, (lCount - 1));
      for (typename T::iterator it = t.begin(); it != t.end(); ++it)
      { insertItem(pModel, (* it), iCurrRow); iCurrRow++; }
      pModel->endInsertRows();
      return pModel;
   }

   template <typename U>
   static inline bool insert(qx::IxModel * pModel, U & item, int iRow)
   {
      if (! pModel) { qAssert(false); return false; }
      type_collection * pListOfItems = static_cast<type_collection *>(pModel->getCollection());
      long & idx = pModel->m_lManualInsertIndex;
      type_primary_key key;

      type_ptr ptr = qx::model_view::detail::QxNestedModel_Helper<U, std::is_base_of<QObject, U>::value>::clone(item);
      qx::IxDataMember * pDataMemberId = pModel->m_pDataMemberId;
      if (! pDataMemberId) { qAssert(false); return false; }
      QVariant value = pDataMemberId->toVariant(& item);
      if (! qx::trait::is_valid_primary_key(value))
      { idx--; value = QVariant(static_cast<qlonglong>(idx)); }
      qx::cvt::from_variant(value, key);
      pListOfItems->insert(iRow, key, ptr);
      return true;
   }

   static inline void synchronize(qx::IxModel * pModel, T & t)
   {
      if (! pModel) { qAssert(false); return; }
      type_generic_container::clear(t);
      type_collection * pListOfItems = static_cast<type_collection *>(pModel->getCollection());

      for (long l = 0; l < pListOfItems->count(); l++)
      {
         type_ptr ptr = pListOfItems->getByIndex(l); if (! ptr) { continue; }
         type_item item = type_generic_container::createItem();
         type_data & item_val = item.value_qx();
         qx::model_view::detail::QxNestedModel_Helper<type_data, std::is_base_of<QObject, type_data>::value>::synchronize(item_val, (* ptr));
         QVariant vKey = QVariant(static_cast<qlonglong>(l));
         qx::cvt::from_variant(vKey, item.key());
         type_generic_container::insertItem(t, item);
      }
   }

private:

   template <typename U>
   static inline bool insertItem(qx::IxModel * pModel, U & item, int iRow)
   { return insertItem_Helper<U, std::is_pointer<U>::value || qx::trait::is_smart_ptr<U>::value>::insert(pModel, item, iRow); }

   template <typename U, bool bIsPointer /* = true */>
   struct insertItem_Helper
   {
      static inline bool insert(qx::IxModel * pModel, U & item, int iRow)
      { return (item ? qx::model_view::detail::QxNestedModel_Container<T, M>::insertItem(pModel, (* item), iRow) : true); }
   };

   template <typename U1, typename U2>
   struct insertItem_Helper<std::pair<U1, U2>, false>
   {
      static inline bool insert(qx::IxModel * pModel, std::pair<U1, U2> & item, int iRow)
      { return qx::model_view::detail::QxNestedModel_Container<T, M>::insertItem(pModel, item.second, iRow); }
   };

   template <typename U1, typename U2>
   struct insertItem_Helper<const std::pair<U1, U2>, false>
   {
      static inline bool insert(qx::IxModel * pModel, const std::pair<U1, U2> & item, int iRow)
      { return qx::model_view::detail::QxNestedModel_Container<T, M>::insertItem(pModel, item.second, iRow); }
   };

#if (QT_VERSION < 0x060000)
   template <typename U1, typename U2>
   struct insertItem_Helper<QPair<U1, U2>, false>
   {
      static inline bool insert(qx::IxModel * pModel, QPair<U1, U2> & item, int iRow)
      { return qx::model_view::detail::QxNestedModel_Container<T, M>::insertItem(pModel, item.second, iRow); }
   };

   template <typename U1, typename U2>
   struct insertItem_Helper<const QPair<U1, U2>, false>
   {
      static inline bool insert(qx::IxModel * pModel, const QPair<U1, U2> & item, int iRow)
      { return qx::model_view::detail::QxNestedModel_Container<T, M>::insertItem(pModel, item.second, iRow); }
   };
#endif // (QT_VERSION < 0x060000)

   template <typename U>
   struct insertItem_Helper<U, false>
   {
      enum { is_same_type = std::is_same<qx::model_view::detail::QxNestedModel_Container<T, M>::type_data, U>::value };
      static bool insert(qx::IxModel * pModel, U & item, int iRow)
      { static_assert(is_same_type, "is_same_type"); return qx::model_view::detail::QxNestedModel_Container<T, M>::insert(pModel, item, iRow); }
   };

};

template <class T, class M /* = void */>
struct QxNestedModel_Ptr
{

   static inline qx::IxModel * create(qx::IxModel * pParent, const QModelIndex & idxParent, T & t)
   { return (t ? create_Helper(pParent, idxParent, (* t)) : create_NullHelper(pParent, idxParent)); }

   static inline void synchronize(qx::IxModel * pModel, T & t)
   { if (! t) { qx::trait::construct_ptr<T>::get(t); }; if (t) { qx::model_view::sync_nested_model(pModel, (* t)); } }

private:

   template <class U>
   static inline qx::IxModel * create_Helper(qx::IxModel * pParent, const QModelIndex & idxParent, U & u)
   { return qx::model_view::detail::QxNestedModel<U, M>::create(pParent, idxParent, u); }

   static inline qx::IxModel * create_NullHelper(qx::IxModel * pParent, const QModelIndex & idxParent)
   {
      M * pModelType = NULL; Q_UNUSED(pModelType);
      T t; qx::trait::construct_ptr<T>::get(t); if (! t) { qAssert(false); return NULL; }
      qx::IxModel * pModel = qx::model_view::create_nested_model_with_type(pParent, idxParent, (* t), pModelType);
      if (pModel) { pModel->clear(); } qAssert(pModel != NULL);
      return pModel;
   }

};

template <class T, class M /* = void */>
struct QxNestedModel
{

   typedef typename std::conditional< std::is_pointer<T>::value, qx::model_view::detail::QxNestedModel_Ptr<T, M>, qx::model_view::detail::QxNestedModel_Generic<T, M> >::type type_model_view_1;
   typedef typename std::conditional< qx::trait::is_smart_ptr<T>::value, qx::model_view::detail::QxNestedModel_Ptr<T, M>, type_model_view_1 >::type type_model_view_2;
   typedef typename std::conditional< qx::trait::is_container<T>::value, qx::model_view::detail::QxNestedModel_Container<T, M>, type_model_view_2 >::type type_model_view_3;

   static inline qx::IxModel * create(qx::IxModel * pParent, const QModelIndex & idxParent, T & t)
   { return type_model_view_3::create(pParent, idxParent, t); }

   static inline void synchronize(qx::IxModel * pModel, T & t)
   { type_model_view_3::synchronize(pModel, t); }

};

} // namespace detail
} // namespace model_view
} // namespace qx

namespace qx {
namespace model_view {

/*!
 * \ingroup QxModelView
 * \brief qx::model_view::create_nested_model is used by QxEntityEditor to manage complex data structure to work with relationships in QML views and Qt model/view architecture
 * \param pParent Parent model, qx::model_view::create_nested_model creates a child model associated to this parent model (a NULL value means that the created model is a root model)
 * \param idxParent Index parent model, qx::model_view::create_nested_model creates a child model indexed by this parent index model (an empty index means that the created model is a root model)
 * \param t Item which contain all values exposed by the model to the views, t item can be a simple type, a pointer, a smart pointer, or a collection of items
 */
template <class T>
qx::IxModel * create_nested_model(qx::IxModel * pParent, const QModelIndex & idxParent, T & t)
{ return qx::model_view::detail::QxNestedModel<T, void>::create(pParent, idxParent, t); }

template <class T, class M>
qx::IxModel * create_nested_model_with_type(qx::IxModel * pParent, const QModelIndex & idxParent, T & t, M * pModelType)
{ Q_UNUSED(pModelType); static_assert((std::is_base_of<qx::IxModel, M>::value || std::is_same<M, void>::value), "(std::is_base_of<qx::IxModel, M>::value || std::is_same<M, void>::value)"); return qx::model_view::detail::QxNestedModel<T, M>::create(pParent, idxParent, t); }

template <class T>
void sync_nested_model(qx::IxModel * pModel, T & t)
{ qx::model_view::detail::QxNestedModel<T, void>::synchronize(pModel, t); }

} // namespace model_view
} // namespace qx

#endif // _QX_NESTED_MODEL_H_
