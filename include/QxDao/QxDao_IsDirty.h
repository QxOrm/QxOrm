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

#ifndef _QX_DAO_IS_DIRTY_H_
#define _QX_DAO_IS_DIRTY_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/static_assert.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/type_traits/is_pointer.hpp>

#include <QtCore/qstringlist.h>

#include <QxDao/QxSqlQueryBuilder.h>
#include <QxDao/IxSqlRelation.h>

#include <QxTraits/is_qx_registered.h>
#include <QxTraits/is_container.h>
#include <QxTraits/is_smart_ptr.h>
#include <QxTraits/generic_container.h>

namespace qx {
namespace dao {
namespace detail {

template <class T>
inline void is_dirty(const T & obj1, const T & obj2, QStringList & lstDiff);

template <class T>
struct QxDao_IsDirty_Generic
{

   static void compare(const T & obj1, const T & obj2, QStringList & lstDiff)
   {
      BOOST_STATIC_ASSERT(qx::trait::is_qx_registered<T>::value);

      qx::QxSqlQueryBuilder_Count<T> builder; builder.init();
      qx::IxDataMember * pId = builder.getDataId();
      if (pId && (! pId->isEqual((& obj1), (& obj2)))) { lstDiff.append(pId->getKey()); }

      long l = 0;
      qx::IxDataMember * p = NULL;
      while ((p = builder.nextData(l)))
      { if (p && (! p->isEqual((& obj1), (& obj2)))) { lstDiff.append(p->getKey()); } }
   }

};

template <class T>
struct QxDao_IsDirty_Container
{

   static void compare(const T & obj1, const T & obj2, QStringList & lstDiff)
   {
      if (qx::trait::generic_container<T>::size(obj1) <= 0) { return; }
      if (qx::trait::generic_container<T>::size(obj1) != qx::trait::generic_container<T>::size(obj2)) { lstDiff.append("*"); return; }

      long lCurrIndex = 0;
      typename T::const_iterator it2 = obj2.begin();

      for (typename T::const_iterator it1 = obj1.begin(); it1 != obj1.end(); ++it1)
      {
         QStringList lstDiffItem;
         qx::dao::detail::is_dirty((* it1), (* it2), lstDiffItem);
         if (lstDiffItem.count() > 0) { lstDiff.append(QString::number(lCurrIndex) + "|" + lstDiffItem.join("|")); }
         ++lCurrIndex; ++it2;
      }
   }

};

template <class T>
struct QxDao_IsDirty_Ptr
{

   static void compare(const T & obj1, const T & obj2, QStringList & lstDiff)
   { qx::dao::detail::is_dirty((* obj1), (* obj2), lstDiff); }

};

template <class T>
struct QxDao_IsDirty
{

   static void compare(const T & obj1, const T & obj2, QStringList & lstDiff)
   {
      typedef typename boost::mpl::if_c< boost::is_pointer<T>::value, qx::dao::detail::QxDao_IsDirty_Ptr<T>, qx::dao::detail::QxDao_IsDirty_Generic<T> >::type type_dao_1;
      typedef typename boost::mpl::if_c< qx::trait::is_smart_ptr<T>::value, qx::dao::detail::QxDao_IsDirty_Ptr<T>, type_dao_1 >::type type_dao_2;
      typedef typename boost::mpl::if_c< qx::trait::is_container<T>::value, qx::dao::detail::QxDao_IsDirty_Container<T>, type_dao_2 >::type type_dao_3;
      type_dao_3::compare(obj1, obj2, lstDiff);
   }

};

template <class T>
inline void is_dirty(const T & obj1, const T & obj2, QStringList & lstDiff)
{ return qx::dao::detail::QxDao_IsDirty<T>::compare(obj1, obj2, lstDiff); }

} // namespace detail
} // namespace dao
} // namespace qx

#endif // _QX_DAO_IS_DIRTY_H_
