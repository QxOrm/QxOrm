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

#ifndef _QX_SQL_RELATION_H_
#define _QX_SQL_RELATION_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/mpl/if.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_pointer.hpp>

#include "../../include/QxDao/QxDao.h"
#include "../../include/QxDao/IxSqlRelation.h"
#include "../../include/QxDao/IxSqlQueryBuilder.h"

#include "../../include/QxTraits/remove_attr.h"
#include "../../include/QxTraits/remove_smart_ptr.h"
#include "../../include/QxTraits/generic_container.h"
#include "../../include/QxTraits/is_container.h"
#include "../../include/QxTraits/is_valid_primary_key.h"

namespace qx {

template <class T>
class QxClass;

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

   static QxCollection<QString, IxDataMember *> m_lstDataMember;     // Optimization : collection of 'IxDataMember'
   static IxSqlRelationX m_lstSqlRelation;                           // Optimization : collection of 'IxSqlRelation'
   static QMutex m_oMutex;                                           // Mutex : 'QxSqlRelation' is thread-safe
   bool m_bInitInEvent;                                              // Class initialisation in progress

public:

   QxSqlRelation(IxDataMember * p) : IxSqlRelation(p), m_bInitInEvent(false) { ; }
   virtual ~QxSqlRelation() { BOOST_STATIC_ASSERT(is_valid); }

   virtual void init()
   {
      if (m_bInitInEvent) { return; }; m_bInitInEvent = true;
      QMutexLocker locker(& QxSqlRelation<DataType, Owner>::m_oMutex);
      m_pDataMemberX = QxClass<type_data>::getSingleton()->dataMemberX();
      m_pDataMemberId = (m_pDataMemberX ? m_pDataMemberX->getId_WithDaoStrategy() : NULL);
      m_lstDataMemberPtr = (& QxSqlRelation<DataType, Owner>::m_lstDataMember);
      m_lstSqlRelationPtr = (& QxSqlRelation<DataType, Owner>::m_lstSqlRelation);
      qAssert(m_pDataMemberX && m_pDataMemberId);
      if (getDataCount() > 0 || getRelationCount() > 0) { m_bInitInEvent = false; return; }
      IxDataMember * p = NULL; long lCount = m_pDataMemberX->count_WithDaoStrategy();
      for (long l = 0; l < lCount; ++l) { if ((p = isValid_DataMember(l))) { m_lstDataMember.insert(p->getKey(), p); } }
      for (long l = 0; l < lCount; ++l) { if ((p = isValid_SqlRelation(l))) { m_lstSqlRelation.insert(p->getKey(), p->getSqlRelation()); } }
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
   { qAssert(params.owner() && m_pDataMember); return static_cast<DataType *>(m_pDataMember->getDataVoidPtr(params.owner())); }

   inline type_owner & getOwner(QxSqlRelationParams & params) const
   { qAssert(params.owner()); return (* static_cast<type_owner *>(params.owner())); }

   inline type_data & getData(QxSqlRelationParams & params) const
   { return getData_Helper<is_data_pointer, is_data_container, 0>::get(getDataTypePtr(params)); }

   inline type_container & getContainer(QxSqlRelationParams & params) const
   { return getContainer_Helper<is_data_pointer, is_data_container, 0>::get(getDataTypePtr(params)); }

   inline type_item createItem() const
   { return createItem_Helper<is_data_container, 0>::get(); }

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

};

template <class DataType, class Owner> QxCollection<QString, IxDataMember *> QxSqlRelation<DataType, Owner>::m_lstDataMember;
template <class DataType, class Owner> IxSqlRelationX QxSqlRelation<DataType, Owner>::m_lstSqlRelation;
template <class DataType, class Owner> QMutex QxSqlRelation<DataType, Owner>::m_oMutex;

} // namespace qx

#include "../../include/QxDao/QxSqlRelation_OneToOne.h"
#include "../../include/QxDao/QxSqlRelation_OneToMany.h"
#include "../../include/QxDao/QxSqlRelation_ManyToOne.h"
#include "../../include/QxDao/QxSqlRelation_ManyToMany.h"
#include "../../include/QxDao/QxSqlRelation_RawData.h"

#endif // _QX_SQL_RELATION_H_
