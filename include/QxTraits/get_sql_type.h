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

#ifndef _QX_GET_SQL_TYPE_H_
#define _QX_GET_SQL_TYPE_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file get_sql_type.h
 * \author Lionel Marty
 * \ingroup QxTraits
 * \brief qx::trait::get_sql_type<T>::get() : return type name under const char * format used by database engine to map a C++ type T
 */

#include <boost/mpl/if.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <boost/type_traits/is_same.hpp>

#include <QtCore/qsharedpointer.h>

#if (QT_VERSION >= 0x040600)
#include <QtCore/qscopedpointer.h>
#endif // (QT_VERSION >= 0x040600)

#include <QxDao/QxDaoPointer.h>

#include <QxTraits/is_qx_registered.h>
#include <QxTraits/get_primary_key.h>
#include <QxTraits/remove_attr.h>
#include <QxTraits/get_class_name_primitive.h>

#include <QxCommon/QxBool.h>

namespace qx {
namespace trait {
namespace detail {

template <typename T>
struct get_sql_type_helper
{

private:

   typedef typename qx::trait::remove_attr<T>::type type_1;
   typedef typename boost::mpl::if_c< qx::trait::is_qx_registered<type_1>::value, typename qx::trait::get_primary_key<type_1>::type, type_1 >::type type_2;
   typedef typename boost::mpl::if_c< boost::is_enum<type_2>::value, long, type_2 >::type type_3;

public:

   typedef typename qx::trait::detail::get_sql_type_helper<T>::type_3 type;

};

template <typename T>
struct get_sql_type
{ static inline const char * get() { return ""; } };

} // namespace detail

/*!
 * \ingroup QxTraits
 * \brief qx::trait::get_sql_type<T>::get() : return type name under const char * format used by database engine to map a C++ type T
 */
template <typename T>
struct get_sql_type
{
   typedef typename qx::trait::detail::get_sql_type_helper<T>::type type_sql;
   static inline const char * get() { return (boost::is_same<T, type_sql>::value ? qx::trait::detail::get_sql_type<type_sql>::get() : qx::trait::get_sql_type<type_sql>::get()); }
};

template <typename T>
struct get_sql_type< boost::scoped_ptr<T> >
{ static inline const char * get() { return qx::trait::get_sql_type<T>::get(); } };

template <typename T>
struct get_sql_type< boost::shared_ptr<T> >
{ static inline const char * get() { return qx::trait::get_sql_type<T>::get(); } };

template <typename T>
struct get_sql_type< boost::intrusive_ptr<T> >
{ static inline const char * get() { return qx::trait::get_sql_type<T>::get(); } };

template <typename T>
struct get_sql_type< QSharedPointer<T> >
{ static inline const char * get() { return qx::trait::get_sql_type<T>::get(); } };

#if (QT_VERSION >= 0x040600)
template <typename T>
struct get_sql_type< QScopedPointer<T> >
{ static inline const char * get() { return qx::trait::get_sql_type<T>::get(); } };
#endif // (QT_VERSION >= 0x040600)

template <typename T>
struct get_sql_type< qx::dao::ptr<T> >
{ static inline const char * get() { return qx::trait::get_sql_type<T>::get(); } };

template <typename T1, typename T2>
struct get_sql_type< std::pair<T1, T2> >
{ static inline const char * get() { static std::string s; s = (std::string(qx::trait::get_sql_type<T1>::get()) + "|" + std::string(qx::trait::get_sql_type<T2>::get())); return s.c_str(); } };

template <typename T1, typename T2>
struct get_sql_type< QPair<T1, T2> >
{ static inline const char * get() { static std::string s; s = (std::string(qx::trait::get_sql_type<T1>::get()) + "|" + std::string(qx::trait::get_sql_type<T2>::get())); return s.c_str(); } };

template <typename T1, typename T2>
struct get_sql_type< boost::tuple<T1, T2> >
{ static inline const char * get() { static std::string s; s = (std::string(qx::trait::get_sql_type<T1>::get()) + "|" + std::string(qx::trait::get_sql_type<T2>::get())); return s.c_str(); } };

template <typename T1, typename T2, typename T3>
struct get_sql_type< boost::tuple<T1, T2, T3> >
{ static inline const char * get() { static std::string s; s = (std::string(qx::trait::get_sql_type<T1>::get()) + "|" + std::string(qx::trait::get_sql_type<T2>::get()) + "|" + std::string(qx::trait::get_sql_type<T3>::get())); return s.c_str(); } };

template <typename T1, typename T2, typename T3, typename T4>
struct get_sql_type< boost::tuple<T1, T2, T3, T4> >
{ static inline const char * get() { static std::string s; s = (std::string(qx::trait::get_sql_type<T1>::get()) + "|" + std::string(qx::trait::get_sql_type<T2>::get()) + "|" + std::string(qx::trait::get_sql_type<T3>::get()) + "|" + std::string(qx::trait::get_sql_type<T4>::get())); return s.c_str(); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5>
struct get_sql_type< boost::tuple<T1, T2, T3, T4, T5> >
{ static inline const char * get() { static std::string s; s = (std::string(qx::trait::get_sql_type<T1>::get()) + "|" + std::string(qx::trait::get_sql_type<T2>::get()) + "|" + std::string(qx::trait::get_sql_type<T3>::get()) + "|" + std::string(qx::trait::get_sql_type<T4>::get()) + "|" + std::string(qx::trait::get_sql_type<T5>::get())); return s.c_str(); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct get_sql_type< boost::tuple<T1, T2, T3, T4, T5, T6> >
{ static inline const char * get() { static std::string s; s = (std::string(qx::trait::get_sql_type<T1>::get()) + "|" + std::string(qx::trait::get_sql_type<T2>::get()) + "|" + std::string(qx::trait::get_sql_type<T3>::get()) + "|" + std::string(qx::trait::get_sql_type<T4>::get()) + "|" + std::string(qx::trait::get_sql_type<T5>::get()) + "|" + std::string(qx::trait::get_sql_type<T6>::get())); return s.c_str(); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct get_sql_type< boost::tuple<T1, T2, T3, T4, T5, T6, T7> >
{ static inline const char * get() { static std::string s; s = (std::string(qx::trait::get_sql_type<T1>::get()) + "|" + std::string(qx::trait::get_sql_type<T2>::get()) + "|" + std::string(qx::trait::get_sql_type<T3>::get()) + "|" + std::string(qx::trait::get_sql_type<T4>::get()) + "|" + std::string(qx::trait::get_sql_type<T5>::get()) + "|" + std::string(qx::trait::get_sql_type<T6>::get()) + "|" + std::string(qx::trait::get_sql_type<T7>::get())); return s.c_str(); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
struct get_sql_type< boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8> >
{ static inline const char * get() { static std::string s; s = (std::string(qx::trait::get_sql_type<T1>::get()) + "|" + std::string(qx::trait::get_sql_type<T2>::get()) + "|" + std::string(qx::trait::get_sql_type<T3>::get()) + "|" + std::string(qx::trait::get_sql_type<T4>::get()) + "|" + std::string(qx::trait::get_sql_type<T5>::get()) + "|" + std::string(qx::trait::get_sql_type<T6>::get()) + "|" + std::string(qx::trait::get_sql_type<T7>::get()) + "|" + std::string(qx::trait::get_sql_type<T8>::get())); return s.c_str(); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct get_sql_type< boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> >
{ static inline const char * get() { static std::string s; s = (std::string(qx::trait::get_sql_type<T1>::get()) + "|" + std::string(qx::trait::get_sql_type<T2>::get()) + "|" + std::string(qx::trait::get_sql_type<T3>::get()) + "|" + std::string(qx::trait::get_sql_type<T4>::get()) + "|" + std::string(qx::trait::get_sql_type<T5>::get()) + "|" + std::string(qx::trait::get_sql_type<T6>::get()) + "|" + std::string(qx::trait::get_sql_type<T7>::get()) + "|" + std::string(qx::trait::get_sql_type<T8>::get()) + "|" + std::string(qx::trait::get_sql_type<T9>::get())); return s.c_str(); } };

namespace detail {

template <>
struct get_sql_type< bool >
{ static inline const char * get() { return "SMALLINT"; } };

template <>
struct get_sql_type< qx_bool >
{ static inline const char * get() { return "SMALLINT"; } };

template <>
struct get_sql_type< short >
{ static inline const char * get() { return "SMALLINT"; } };

template <>
struct get_sql_type< int >
{ static inline const char * get() { return "INTEGER"; } };

template <>
struct get_sql_type< long >
{ static inline const char * get() { return "INTEGER"; } };

template <>
struct get_sql_type< long long >
{ static inline const char * get() { return "INTEGER"; } };

template <>
struct get_sql_type< float >
{ static inline const char * get() { return "FLOAT"; } };

template <>
struct get_sql_type< double >
{ static inline const char * get() { return "FLOAT"; } };

template <>
struct get_sql_type< long double >
{ static inline const char * get() { return "FLOAT"; } };

template <>
struct get_sql_type< unsigned short >
{ static inline const char * get() { return "SMALLINT"; } };

template <>
struct get_sql_type< unsigned int >
{ static inline const char * get() { return "INTEGER"; } };

template <>
struct get_sql_type< unsigned long >
{ static inline const char * get() { return "INTEGER"; } };

template <>
struct get_sql_type< unsigned long long >
{ static inline const char * get() { return "INTEGER"; } };

template <>
struct get_sql_type< std::string >
{ static inline const char * get() { return "TEXT"; } };

template <>
struct get_sql_type< std::wstring >
{ static inline const char * get() { return "TEXT"; } };

template <>
struct get_sql_type< QString >
{ static inline const char * get() { return "TEXT"; } };

template <>
struct get_sql_type< QVariant >
{ static inline const char * get() { return "TEXT"; } };

template <>
struct get_sql_type< QDate >
{ static inline const char * get() { return "DATE"; } };

template <>
struct get_sql_type< QTime >
{ static inline const char * get() { return "TIME"; } };

template <>
struct get_sql_type< QDateTime >
{ static inline const char * get() { return "TIMESTAMP"; } };

template <>
struct get_sql_type< QByteArray >
{ static inline const char * get() { return "BLOB"; } };

} // namespace detail
} // namespace trait
} // namespace qx

#endif // _QX_GET_SQL_TYPE_H_
