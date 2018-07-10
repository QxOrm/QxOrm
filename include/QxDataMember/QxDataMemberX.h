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

#ifndef _QX_DATA_MEMBER_X_H_
#define _QX_DATA_MEMBER_X_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxDataMemberX.h
 * \author Lionel Marty
 * \ingroup QxDataMember
 * \brief Concrete list of class properties registered into QxOrm context
 */

#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_base_of.hpp>

#include <QxDataMember/IxDataMemberX.h>
#include <QxDataMember/QxDataMember.h>

#include <QxDao/QxSqlRelation.h>

#include <QxSingleton/QxSingleton.h>

#include <QxFactory/QxFactory.h>

#include <QxTraits/get_base_class.h>
#include <QxTraits/get_primary_key.h>
#include <QxTraits/get_sql_type.h>

namespace qx {

/*!
 * \ingroup QxDataMember
 * \brief qx::QxDataMemberX<T> : concrete list of properties registered into QxOrm context for the class T
 */
template <class T>
class QxDataMemberX : public IxDataMemberX, public QxSingleton< QxDataMemberX<T> >
{

   friend class QxSingleton< QxDataMemberX<T> >;

public:

   typedef typename qx::trait::get_primary_key<T>::type type_primary_key;
   typedef typename qx::trait::get_base_class<T>::type type_base_class;

protected:

   QxDataMember<type_primary_key, T> * m_pDataMemberId;  //!< Data member id with primary key type

protected:

   QxDataMemberX() : IxDataMemberX(), QxSingleton< QxDataMemberX<T> >(QString("qx::QxDataMemberX_") + qx::trait::get_class_name<T>::get_xml_tag()), m_pDataMemberId(NULL) { ; }
   virtual ~QxDataMemberX() { ; }

public:

   virtual IxDataMember * getId() const { return m_pDataMemberId; }

   virtual long count_WithDaoStrategy() const                              { return count_WithDaoStrategy_Helper(); }
   virtual bool exist_WithDaoStrategy(const QString & sKey) const          { return exist_WithDaoStrategy_Helper(sKey); }
   virtual IxDataMember * get_WithDaoStrategy(long lIndex) const           { return get_WithDaoStrategy_Helper(lIndex); }
   virtual IxDataMember * get_WithDaoStrategy(const QString & sKey) const  { return get_WithDaoStrategy_Helper(sKey); }
   virtual IxDataMember * getId_WithDaoStrategy() const                    { return getId_WithDaoStrategy_Helper(); }

   IxDataMember * id(type_primary_key T::* pDataMemberId, const QString & sKey);
   IxDataMember * id(type_primary_key T::* pDataMemberId, const QString & sKey, long lVersion);

   template <typename V, typename U> IxDataMember * add(V U::* pData, const QString & sKey);
   template <typename V, typename U> IxDataMember * add(V U::* pData, const QString & sKey, long lVersion);
   template <typename V, typename U> IxDataMember * add(V U::* pData, const QString & sKey, long lVersion, bool bSerialize);
   template <typename V, typename U> IxDataMember * add(V U::* pData, const QString & sKey, long lVersion, bool bSerialize, bool bDao);

   template <typename V, typename U> IxSqlRelation * relationOneToOne(V U::* pData, const QString & sKey);
   template <typename V, typename U> IxSqlRelation * relationOneToOne(V U::* pData, const QString & sKey, long lVersion);
   template <typename V, typename U> IxSqlRelation * relationManyToOne(V U::* pData, const QString & sKey);
   template <typename V, typename U> IxSqlRelation * relationManyToOne(V U::* pData, const QString & sKey, long lVersion);
   template <typename V, typename U> IxSqlRelation * relationOneToMany(V U::* pData, const QString & sKey, const QString & sForeignKey);
   template <typename V, typename U> IxSqlRelation * relationOneToMany(V U::* pData, const QString & sKey, const QString & sForeignKey, long lVersion);
   template <typename V, typename U> IxSqlRelation * relationManyToMany(V U::* pData, const QString & sKey, const QString & sExtraTable, const QString & sForeignKeyOwner, const QString & sForeignKeyDataType);
   template <typename V, typename U> IxSqlRelation * relationManyToMany(V U::* pData, const QString & sKey, const QString & sExtraTable, const QString & sForeignKeyOwner, const QString & sForeignKeyDataType, long lVersion);

   template <class Archive> inline void toArchive(const T * pOwner, Archive & ar, const unsigned int file_version) const;
   template <class Archive> inline void fromArchive(T * pOwner, Archive & ar, const unsigned int file_version);

private:

   inline IxDataMemberX * getBaseClass_Helper() const { return QxDataMemberX<type_base_class>::getSingleton(); }

   long count_WithDaoStrategy_Helper() const
   {
      if (getDaoStrategy() == qx::dao::strategy::single_table_inheritance)
      { return ((getBaseClass_Helper()->getDaoStrategy() != getDaoStrategy()) ? count() : getBaseClass_Helper()->count_WithDaoStrategy()); }
      else if (getDaoStrategy() == qx::dao::strategy::class_table_inheritance)
      { return (count() + ((! m_pDataMemberId && getId_WithDaoStrategy()) ? 1 : 0)); }
      else if (getDaoStrategy() == qx::dao::strategy::concrete_table_inheritance)
      { return (count() + getBaseClass_Helper()->count_WithDaoStrategy()); }
      qAssert(false); return 0;
   }

   bool exist_WithDaoStrategy_Helper(const QString & sKey) const
   {
      if (getDaoStrategy() == qx::dao::strategy::single_table_inheritance)
      { return ((getBaseClass_Helper()->getDaoStrategy() != getDaoStrategy()) ? exist(sKey) : getBaseClass_Helper()->exist_WithDaoStrategy(sKey)); }
      else if (getDaoStrategy() == qx::dao::strategy::class_table_inheritance)
      { return (exist(sKey) || (getId_WithDaoStrategy() ? (getId_WithDaoStrategy()->getKey() == sKey) : false)); }
      else if (getDaoStrategy() == qx::dao::strategy::concrete_table_inheritance)
      { return (exist(sKey) || getBaseClass_Helper()->exist_WithDaoStrategy(sKey)); }
      qAssert(false); return false;
   }

   IxDataMember * get_WithDaoStrategy_Helper(long lIndex) const
   {
      if (getDaoStrategy() == qx::dao::strategy::single_table_inheritance)
      { return ((getBaseClass_Helper()->getDaoStrategy() != getDaoStrategy()) ? get(lIndex) : getBaseClass_Helper()->get_WithDaoStrategy(lIndex)); }
      else if (getDaoStrategy() == qx::dao::strategy::class_table_inheritance)
      { return ((! m_pDataMemberId && (lIndex == count())) ? getId_WithDaoStrategy() : get(lIndex)); }
      else if (getDaoStrategy() == qx::dao::strategy::concrete_table_inheritance)
      { return (((lIndex >= 0) && (lIndex < count())) ? get(lIndex) : getBaseClass_Helper()->get_WithDaoStrategy(lIndex - count())); }
      qAssert(false); return NULL;
   }

   IxDataMember * get_WithDaoStrategy_Helper(const QString & sKey) const
   {
      if (getDaoStrategy() == qx::dao::strategy::single_table_inheritance)
      { return ((getBaseClass_Helper()->getDaoStrategy() != getDaoStrategy()) ? get(sKey) : getBaseClass_Helper()->get_WithDaoStrategy(sKey)); }
      else if (getDaoStrategy() == qx::dao::strategy::class_table_inheritance)
      { return ((getId_WithDaoStrategy() && (getId_WithDaoStrategy()->getKey() == sKey)) ? getId_WithDaoStrategy() : get(sKey)); }
      else if (getDaoStrategy() == qx::dao::strategy::concrete_table_inheritance)
      { return (exist(sKey) ? get(sKey) : getBaseClass_Helper()->get_WithDaoStrategy(sKey)); }
      qAssert(false); return NULL;
   }

   IxDataMember * getId_WithDaoStrategy_Helper() const
   {
      if (getDaoStrategy() == qx::dao::strategy::single_table_inheritance)
      { return ((getBaseClass_Helper()->getDaoStrategy() != getDaoStrategy()) ? m_pDataMemberId : getBaseClass_Helper()->getId_WithDaoStrategy()); }
      else if (getDaoStrategy() == qx::dao::strategy::class_table_inheritance)
      { return (m_pDataMemberId ? m_pDataMemberId : getBaseClass_Helper()->getId_WithDaoStrategy()); }
      else if (getDaoStrategy() == qx::dao::strategy::concrete_table_inheritance)
      { return (m_pDataMemberId ? m_pDataMemberId : getBaseClass_Helper()->getId_WithDaoStrategy()); }
      qAssert(false); return NULL;
   }

};

} // namespace qx

#include "../../inl/QxDataMember/QxDataMemberX.inl"

#endif // _QX_DATA_MEMBER_X_H_
