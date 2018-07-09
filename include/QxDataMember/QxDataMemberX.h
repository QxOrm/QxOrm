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

#ifndef _QX_DATA_MEMBER_X_H_
#define _QX_DATA_MEMBER_X_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/type_traits/is_integral.hpp>

#include "../../include/QxDataMember/IxDataMemberX.h"
#include "../../include/QxDataMember/QxDataMember.h"

#include "../../include/QxDao/QxSqlRelation.h"

#include "../../include/QxSingleton/QxSingleton.h"

#include "../../include/QxFactory/QxFactory.h"

#include "../../include/QxTraits/get_base_class.h"
#include "../../include/QxTraits/get_primary_key.h"
#include "../../include/QxTraits/get_sql_type.h"

namespace qx {

template <class T>
class QxDataMemberX : public IxDataMemberX, public QxSingleton< QxDataMemberX<T> >
{

   friend class QxSingleton< QxDataMemberX<T> >;

public:

   typedef typename qx::trait::get_primary_key<T>::type type_primary_key;
   typedef typename qx::trait::get_base_class<T>::type type_base_class;

protected:

   QxDataMember<type_primary_key, T> * m_pDataMemberId;  // Data member id with primary key type

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

   template <typename V> IxDataMember * add(V T::* pData, const QString & sKey);
   template <typename V> IxDataMember * add(V T::* pData, const QString & sKey, long lVersion);
   template <typename V> IxDataMember * add(V T::* pData, const QString & sKey, long lVersion, bool bSerialize);
   template <typename V> IxDataMember * add(V T::* pData, const QString & sKey, long lVersion, bool bSerialize, bool bDao);

   template <typename V> IxSqlRelation * relationOneToOne(V T::* pData, const QString & sKey);
   template <typename V> IxSqlRelation * relationOneToOne(V T::* pData, const QString & sKey, long lVersion);
   template <typename V> IxSqlRelation * relationManyToOne(V T::* pData, const QString & sKey);
   template <typename V> IxSqlRelation * relationManyToOne(V T::* pData, const QString & sKey, long lVersion);
   template <typename V> IxSqlRelation * relationOneToMany(V T::* pData, const QString & sKey, const QString & sForeignKey);
   template <typename V> IxSqlRelation * relationOneToMany(V T::* pData, const QString & sKey, const QString & sForeignKey, long lVersion);
   template <typename V> IxSqlRelation * relationManyToMany(V T::* pData, const QString & sKey, const QString & sExtraTable, const QString & sForeignKeyOwner, const QString & sForeignKeyDataType);
   template <typename V> IxSqlRelation * relationManyToMany(V T::* pData, const QString & sKey, const QString & sExtraTable, const QString & sForeignKeyOwner, const QString & sForeignKeyDataType, long lVersion);

   template <class Archive> inline void toArchive(const T * pOwner, Archive & ar, const unsigned int file_version) const;
   template <class Archive> inline void fromArchive(T * pOwner, Archive & ar, const unsigned int file_version);

private:

   inline IxDataMemberX * getBaseClass_Helper() const { return QxDataMemberX<type_base_class>::getSingleton(); }

   long count_WithDaoStrategy_Helper() const
   {
      if (getDaoStrategy() == QX_TABLE_PER_CLASS) { return count(); }
      else { return (count() + getBaseClass_Helper()->count_WithDaoStrategy()); }
      qAssert(false); return 0;
   }

   bool exist_WithDaoStrategy_Helper(const QString & sKey) const
   {
      if (getDaoStrategy() == QX_TABLE_PER_CLASS) { return exist(sKey); }
      else { return (exist(sKey) || getBaseClass_Helper()->exist_WithDaoStrategy(sKey)); }
      qAssert(false); return false;
   }

   IxDataMember * get_WithDaoStrategy_Helper(long lIndex) const
   {
      if (getDaoStrategy() == QX_TABLE_PER_CLASS) { return get(lIndex); }
      else { return (((lIndex >= 0) && (lIndex < count())) ? get(lIndex) : getBaseClass_Helper()->get_WithDaoStrategy(lIndex - count())); }
      qAssert(false); return NULL;
   }

   IxDataMember * get_WithDaoStrategy_Helper(const QString & sKey) const
   {
      if (getDaoStrategy() == QX_TABLE_PER_CLASS) { return get(sKey); }
      else { return (exist(sKey) ? get(sKey) : getBaseClass_Helper()->get_WithDaoStrategy(sKey)); }
      qAssert(false); return NULL;
   }

   IxDataMember * getId_WithDaoStrategy_Helper() const
   {
      if (getDaoStrategy() == QX_TABLE_PER_CLASS) { return m_pDataMemberId; }
      else { return (m_pDataMemberId ? m_pDataMemberId : getBaseClass_Helper()->getId_WithDaoStrategy()); }
      qAssert(false); return NULL;
   }

};

} // namespace qx

#include "../../inl/QxDataMember/QxDataMemberX.inl"

#endif // _QX_DATA_MEMBER_X_H_
