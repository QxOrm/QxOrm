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

#ifndef _QX_SQL_RELATION_H_
#define _QX_SQL_RELATION_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSqlRelation.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Base class for all relationships defined between 2 classes (or between 2 tables in database)
 */

#include <boost/mpl/if.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_pointer.hpp>

#include <QxDao/QxDao.h>
#include <QxDao/IxSqlRelation.h>
#include <QxDao/IxSqlQueryBuilder.h>

#include <QxTraits/remove_attr.h>
#include <QxTraits/remove_smart_ptr.h>
#include <QxTraits/generic_container.h>
#include <QxTraits/is_container.h>
#include <QxTraits/is_valid_primary_key.h>
#include <QxTraits/is_qx_registered.h>

#include <QxRegister/IxClass.h>

namespace qx {

template <class T>
class QxClass;

/*!
 * \ingroup QxDao
 * \brief qx::QxSqlRelation<DataType, Owner> : base class for all relationships defined between 2 classes (or between 2 tables in database)
 */
template <class DataType, class Owner>
class QxSqlRelation : public IxSqlRelation
{

protected:

   typedef typename qx::trait::remove_attr<DataType>::type type_tmp_1;
   typedef typename qx::trait::remove_smart_ptr<type_tmp_1>::type type_tmp_2;
   typedef type_tmp_2 type_container;
   typedef qx::trait::generic_container<type_container> type_generic_container;
   typedef typename type_generic_container::type_item type_item;
   typedef typename boost::mpl::if_c<qx::trait::is_container<type_container>::value, typename type_generic_container::type_value_qx, type_container>::type type_tmp_3;
   typedef typename QxSqlRelation<DataType, Owner>::type_tmp_3 type_data;
   typedef Owner type_owner;

   enum { is_valid = (qx::trait::is_qx_registered<type_data>::value && qx::trait::is_qx_registered<type_owner>::value) };
   enum { is_data_pointer = (boost::is_pointer<DataType>::value || qx::trait::is_smart_ptr<DataType>::value) };
   enum { is_data_container = qx::trait::is_container<type_container>::value };
   enum { is_same_data_owner = boost::is_same<type_data, type_owner>::value };

protected:

   QMutex m_oMutex;        //!< Mutex : 'QxSqlRelation' is thread-safe
   bool m_bInitInEvent;    //!< Class initialisation in progress

public:

   QxSqlRelation(IxDataMember * p) : IxSqlRelation(p), m_bInitInEvent(false) { ; }
   virtual ~QxSqlRelation() { BOOST_STATIC_ASSERT(is_valid); }

   virtual void init()
   {
      if (m_bInitInEvent) { return; }; m_bInitInEvent = true;
      QMutexLocker locker(& this->m_oMutex);
      m_pClass = QxClass<type_data>::getSingleton();
      m_pClassOwner = QxClass<type_owner>::getSingleton();
      m_pDataMemberX = (m_pClass ? m_pClass->getDataMemberX() : NULL);
      m_pDataMemberId = (m_pDataMemberX ? m_pDataMemberX->getId_WithDaoStrategy() : NULL);
      m_pDataMemberIdOwner = ((m_pClassOwner && m_pClassOwner->getDataMemberX()) ? m_pClassOwner->getDataMemberX()->getId_WithDaoStrategy() : NULL);
      if (m_lstDataMemberPtr || m_lstSqlRelationPtr) { m_bInitInEvent = false; return; }
      if (m_pClass) { m_oSoftDelete = m_pClass->getSoftDelete(); }

#ifdef _QX_MODE_DEBUG
      QString sCheckMsg = "Check relationship '" + this->getKey() + "' from '" + (m_pClassOwner ? m_pClassOwner->getKey() : QString()) + "' to '" + (m_pClass ? m_pClass->getKey() : QString()) + "'";
      if (! m_pClass) { QString sAssertMsg = sCheckMsg + " : m_pClass is equal to NULL"; qAssertMsg(false, "[QxOrm] qx::QxSqlRelation::init()", qPrintable(sAssertMsg)); }
      if (! m_pClassOwner) { QString sAssertMsg = sCheckMsg + " : m_pClassOwner is equal to NULL"; qAssertMsg(false, "[QxOrm] qx::QxSqlRelation::init()", qPrintable(sAssertMsg)); }
      if (! m_pDataMember) { QString sAssertMsg = sCheckMsg + " : m_pDataMember is equal to NULL"; qAssertMsg(false, "[QxOrm] qx::QxSqlRelation::init()", qPrintable(sAssertMsg)); }
      if (! m_pDataMemberX) { QString sAssertMsg = sCheckMsg + " : m_pDataMemberX is equal to NULL"; qAssertMsg(false, "[QxOrm] qx::QxSqlRelation::init()", qPrintable(sAssertMsg)); }
      if (! m_pDataMemberId) { QString sAssertMsg = sCheckMsg + " : m_pDataMemberId is equal to NULL"; qAssertMsg(false, "[QxOrm] qx::QxSqlRelation::init()", qPrintable(sAssertMsg)); }
#endif // _QX_MODE_DEBUG

      if (IxSqlRelation::m_bTraceRelationInit)
      { QString sTraceMsg = "[QxOrm] Init relationship '" + this->getKey() + "' from '" + (m_pClassOwner ? m_pClassOwner->getKey() : QString()) + "' to '" + (m_pClass ? m_pClass->getKey() : QString()) + "'"; qDebug() << sTraceMsg; }

      m_lstSqlRelationPtr = new IxSqlRelationX();
      m_lstDataMemberPtr = new QxCollection<QString, IxDataMember *>();
      if ((getDataCount() > 0) || (getRelationCount() > 0)) { m_bInitInEvent = false; return; }
      IxDataMember * p = NULL; long lCount = m_pDataMemberX->count_WithDaoStrategy();

      for (long l = 0; l < lCount; ++l)
      {
         p = isValid_DataMember(l); if (! p) { continue; }
#ifdef _QX_MODE_DEBUG
         if (m_lstDataMemberPtr->exist(p->getKey()))
         { QString sDebugMsg = "[QxOrm] Relationship '" + this->getKey() + "' from '" + (m_pClassOwner ? m_pClassOwner->getKey() : QString()) + "' to '" + (m_pClass ? m_pClass->getKey() : QString()) + "' : data member '" + p->getKey() + "' already exists in the collection"; qDebug() << sDebugMsg; }
#endif // _QX_MODE_DEBUG
         m_lstDataMemberPtr->insert(p->getKey(), p);
      }

      for (long l = 0; l < lCount; ++l)
      {
         p = isValid_SqlRelation(l); if (! p) { continue; }
#ifdef _QX_MODE_DEBUG
         if (m_lstSqlRelationPtr->exist(p->getKey()))
         { QString sDebugMsg = "[QxOrm] Relationship '" + this->getKey() + "' from '" + (m_pClassOwner ? m_pClassOwner->getKey() : QString()) + "' to '" + (m_pClass ? m_pClass->getKey() : QString()) + "' : relation '" + p->getKey() + "' already exists in the collection"; qDebug() << sDebugMsg; }
#endif // _QX_MODE_DEBUG
         m_lstSqlRelationPtr->insert(p->getKey(), p->getSqlRelation());
      }

      m_bInitInEvent = false;
   }

private:

   inline IxDataMember * isValid_DataMember(long lIndex) const
   {
      IxDataMember * p = m_pDataMemberX->get_WithDaoStrategy(lIndex);
      bool bValid = (p && p->getDao() && ! p->hasSqlRelation());
      bValid = (bValid && (p != m_pDataMemberId));
      return (bValid ? p : NULL);
   }

   inline IxDataMember * isValid_SqlRelation(long lIndex) const
   {
      IxDataMember * p = m_pDataMemberX->get_WithDaoStrategy(lIndex);
      bool bIsValid = (p && p->getDao() && p->hasSqlRelation());
      if (bIsValid && (! is_same_data_owner) && (p != m_pDataMember)) { p->getSqlRelation()->init(); }
      return (bIsValid ? p : NULL);
   }

protected:

   inline DataType * getDataTypePtr(QxSqlRelationParams & params) const
   { qAssert(params.owner() && m_pDataMember); return static_cast<DataType *>(m_pDataMember->getValueVoidPtr(params.owner())); }

   inline type_owner & getOwner(QxSqlRelationParams & params) const
   { qAssert(params.owner()); return (* static_cast<type_owner *>(params.owner())); }

   inline type_data & getData(QxSqlRelationParams & params) const
   { return getData_Helper<is_data_pointer, is_data_container, 0>::get(getDataTypePtr(params)); }

   inline type_container & getContainer(QxSqlRelationParams & params) const
   { return getContainer_Helper<is_data_pointer, is_data_container, 0>::get(getDataTypePtr(params)); }

   inline type_item createItem() const
   { return createItem_Helper<is_data_container, 0>::get(); }

   inline bool isNullData(QxSqlRelationParams & params) const
   { return isNullData_Helper<is_data_pointer, 0>::get(getDataTypePtr(params)); }

   bool callTriggerBeforeFetch(type_data & t, QxSqlRelationParams & params) const
   {
      if (! params.builder().getDaoHelper()) { return true; }
      qx::dao::on_before_fetch<type_data>((& t), params.builder().getDaoHelper());
      return params.builder().getDaoHelper()->isValid();
   }

   bool callTriggerAfterFetch(type_data & t, QxSqlRelationParams & params) const
   {
      if (! params.builder().getDaoHelper()) { return true; }
      qx::dao::on_after_fetch<type_data>((& t), params.builder().getDaoHelper());
      return params.builder().getDaoHelper()->isValid();
   }

private:

   template <bool bIsPointer /* = false */, bool bIsContainer /* = false */, int dummy>
   struct getData_Helper
   { static inline type_data & get(DataType * t) { return (* t); } };

   template <int dummy>
   struct getData_Helper<true, false, dummy>
   { static inline type_data & get(DataType * t) { if (! (* t)) { qx::trait::construct_ptr<DataType>::get(* t); }; return (** t); } };

   template <int dummy>
   struct getData_Helper<false, true, dummy>
   { static inline type_data & get(DataType * t) { qAssert(false); Q_UNUSED(t); type_data * pDummy(NULL); return (* pDummy); } };

   template <int dummy>
   struct getData_Helper<true, true, dummy>
   { static inline type_data & get(DataType * t) { qAssert(false); Q_UNUSED(t); type_data * pDummy(NULL); return (* pDummy); } };

   template <bool bIsPointer /* = false */, bool bIsContainer /* = false */, int dummy>
   struct getContainer_Helper
   { static inline type_container & get(DataType * t) { qAssert(false); Q_UNUSED(t); type_container * pDummy(NULL); return (* pDummy); } };

   template <int dummy>
   struct getContainer_Helper<true, false, dummy>
   { static inline type_container & get(DataType * t) { qAssert(false); Q_UNUSED(t); type_container * pDummy(NULL); return (* pDummy); } };

   template <int dummy>
   struct getContainer_Helper<false, true, dummy>
   { static inline type_container & get(DataType * t) { return (* t); } };

   template <int dummy>
   struct getContainer_Helper<true, true, dummy>
   { static inline type_container & get(DataType * t) { if (! (* t)) { qx::trait::construct_ptr<DataType>::get(* t); }; return (** t); } };

   template <bool bIsContainer /* = false */, int dummy>
   struct createItem_Helper
   { static inline type_item get() { qAssert(false); type_item * pDummy(NULL); return (* pDummy); } };

   template <int dummy>
   struct createItem_Helper<true, dummy>
   { static inline type_item get() { return type_generic_container::createItem(); } };

   template <bool bIsPointer /* = false */, int dummy>
   struct isNullData_Helper
   { static inline bool get(DataType * t) { Q_UNUSED(t); return false; } };

   template <int dummy>
   struct isNullData_Helper<true, dummy>
   { static inline bool get(DataType * t) { return ((! (* t)) ? true : false); } };

};

} // namespace qx

#include <QxDao/QxSqlRelation_OneToOne.h>
#include <QxDao/QxSqlRelation_OneToMany.h>
#include <QxDao/QxSqlRelation_ManyToOne.h>
#include <QxDao/QxSqlRelation_ManyToMany.h>
#include <QxDao/QxSqlRelation_RawData.h>

#endif // _QX_SQL_RELATION_H_
