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

#include <QtCore/qsharedpointer.h>

#if (QT_VERSION >= 0x040600)
#include <QtCore/qscopedpointer.h>
#endif // (QT_VERSION >= 0x040600)

#include <QxTraits/is_qx_registered.h>
#include <QxTraits/get_primary_key.h>
#include <QxTraits/remove_attr.h>
#include <QxTraits/get_class_name_primitive.h>

#include <QxDao/QxDaoPointer.h>
#include <QxDao/QxDateNeutral.h>
#include <QxDao/QxTimeNeutral.h>
#include <QxDao/QxDateTimeNeutral.h>

#include <QxCommon/QxBool.h>

namespace qx {
namespace trait {
namespace detail {

template <typename T>
struct get_sql_type_helper
{

private:

   typedef typename qx::trait::remove_attr<T>::type type_1;
   typedef typename std::conditional< qx::trait::is_qx_registered<type_1>::value, typename qx::trait::get_primary_key<type_1>::type, type_1 >::type type_2;
   typedef typename std::conditional< std::is_enum<type_2>::value, long, type_2 >::type type_3;

public:

   typedef typename qx::trait::detail::get_sql_type_helper<T>::type_3 type;

};

template <typename T>
struct get_sql_type
{ static inline const char * get() { return ""; } };

/* Implemented into './src/QxRegister/QxClassX.cpp' file */
QX_DLL_EXPORT const char * get_sql_type_by_class_name(const char * sClassName, const char * sDefaultValue);

} // namespace detail

/*!
 * \ingroup QxTraits
 * \brief qx::trait::get_sql_type<T>::get() : return type name under const char * format used by database engine to map a C++ type T
 */
template <typename T>
struct get_sql_type
{
   typedef typename qx::trait::detail::get_sql_type_helper<T>::type type_sql;
   static inline const char * get() { return (std::is_same<T, type_sql>::value ? qx::trait::detail::get_sql_type<type_sql>::get() : qx::trait::get_sql_type<type_sql>::get()); }
};

#ifdef _QX_ENABLE_BOOST

template <typename T>
struct get_sql_type< boost::optional<T> >
{ static inline const char * get() { return qx::trait::get_sql_type<T>::get(); } };

template <typename T>
struct get_sql_type< boost::scoped_ptr<T> >
{ static inline const char * get() { return qx::trait::get_sql_type<T>::get(); } };

template <typename T>
struct get_sql_type< boost::shared_ptr<T> >
{ static inline const char * get() { return qx::trait::get_sql_type<T>::get(); } };

template <typename T>
struct get_sql_type< boost::intrusive_ptr<T> >
{ static inline const char * get() { return qx::trait::get_sql_type<T>::get(); } };

#endif // _QX_ENABLE_BOOST

template <typename T>
struct get_sql_type< QSharedPointer<T> >
{ static inline const char * get() { return qx::trait::get_sql_type<T>::get(); } };

#if (QT_VERSION >= 0x040600)
template <typename T>
struct get_sql_type< QScopedPointer<T> >
{ static inline const char * get() { return qx::trait::get_sql_type<T>::get(); } };
#endif // (QT_VERSION >= 0x040600)

template <typename T>
struct get_sql_type< std::unique_ptr<T> >
{ static inline const char * get() { return qx::trait::get_sql_type<T>::get(); } };

template <typename T>
struct get_sql_type< std::shared_ptr<T> >
{ static inline const char * get() { return qx::trait::get_sql_type<T>::get(); } };

template <typename T>
struct get_sql_type< qx::dao::ptr<T> >
{ static inline const char * get() { return qx::trait::get_sql_type<T>::get(); } };

template <typename T1, typename T2>
struct get_sql_type< std::pair<T1, T2> >
{ static inline const char * get() { static std::string s; s = (std::string(qx::trait::get_sql_type<T1>::get()) + "|" + std::string(qx::trait::get_sql_type<T2>::get())); return s.c_str(); } };

template <typename T1, typename T2>
struct get_sql_type< QPair<T1, T2> >
{ static inline const char * get() { static std::string s; s = (std::string(qx::trait::get_sql_type<T1>::get()) + "|" + std::string(qx::trait::get_sql_type<T2>::get())); return s.c_str(); } };

#ifdef _QX_ENABLE_BOOST

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

#endif // _QX_ENABLE_BOOST

template <typename T1, typename T2>
struct get_sql_type< std::tuple<T1, T2> >
{ static inline const char * get() { static std::string s; s = (std::string(qx::trait::get_sql_type<T1>::get()) + "|" + std::string(qx::trait::get_sql_type<T2>::get())); return s.c_str(); } };

template <typename T1, typename T2, typename T3>
struct get_sql_type< std::tuple<T1, T2, T3> >
{ static inline const char * get() { static std::string s; s = (std::string(qx::trait::get_sql_type<T1>::get()) + "|" + std::string(qx::trait::get_sql_type<T2>::get()) + "|" + std::string(qx::trait::get_sql_type<T3>::get())); return s.c_str(); } };

template <typename T1, typename T2, typename T3, typename T4>
struct get_sql_type< std::tuple<T1, T2, T3, T4> >
{ static inline const char * get() { static std::string s; s = (std::string(qx::trait::get_sql_type<T1>::get()) + "|" + std::string(qx::trait::get_sql_type<T2>::get()) + "|" + std::string(qx::trait::get_sql_type<T3>::get()) + "|" + std::string(qx::trait::get_sql_type<T4>::get())); return s.c_str(); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5>
struct get_sql_type< std::tuple<T1, T2, T3, T4, T5> >
{ static inline const char * get() { static std::string s; s = (std::string(qx::trait::get_sql_type<T1>::get()) + "|" + std::string(qx::trait::get_sql_type<T2>::get()) + "|" + std::string(qx::trait::get_sql_type<T3>::get()) + "|" + std::string(qx::trait::get_sql_type<T4>::get()) + "|" + std::string(qx::trait::get_sql_type<T5>::get())); return s.c_str(); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct get_sql_type< std::tuple<T1, T2, T3, T4, T5, T6> >
{ static inline const char * get() { static std::string s; s = (std::string(qx::trait::get_sql_type<T1>::get()) + "|" + std::string(qx::trait::get_sql_type<T2>::get()) + "|" + std::string(qx::trait::get_sql_type<T3>::get()) + "|" + std::string(qx::trait::get_sql_type<T4>::get()) + "|" + std::string(qx::trait::get_sql_type<T5>::get()) + "|" + std::string(qx::trait::get_sql_type<T6>::get())); return s.c_str(); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct get_sql_type< std::tuple<T1, T2, T3, T4, T5, T6, T7> >
{ static inline const char * get() { static std::string s; s = (std::string(qx::trait::get_sql_type<T1>::get()) + "|" + std::string(qx::trait::get_sql_type<T2>::get()) + "|" + std::string(qx::trait::get_sql_type<T3>::get()) + "|" + std::string(qx::trait::get_sql_type<T4>::get()) + "|" + std::string(qx::trait::get_sql_type<T5>::get()) + "|" + std::string(qx::trait::get_sql_type<T6>::get()) + "|" + std::string(qx::trait::get_sql_type<T7>::get())); return s.c_str(); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
struct get_sql_type< std::tuple<T1, T2, T3, T4, T5, T6, T7, T8> >
{ static inline const char * get() { static std::string s; s = (std::string(qx::trait::get_sql_type<T1>::get()) + "|" + std::string(qx::trait::get_sql_type<T2>::get()) + "|" + std::string(qx::trait::get_sql_type<T3>::get()) + "|" + std::string(qx::trait::get_sql_type<T4>::get()) + "|" + std::string(qx::trait::get_sql_type<T5>::get()) + "|" + std::string(qx::trait::get_sql_type<T6>::get()) + "|" + std::string(qx::trait::get_sql_type<T7>::get()) + "|" + std::string(qx::trait::get_sql_type<T8>::get())); return s.c_str(); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct get_sql_type< std::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> >
{ static inline const char * get() { static std::string s; s = (std::string(qx::trait::get_sql_type<T1>::get()) + "|" + std::string(qx::trait::get_sql_type<T2>::get()) + "|" + std::string(qx::trait::get_sql_type<T3>::get()) + "|" + std::string(qx::trait::get_sql_type<T4>::get()) + "|" + std::string(qx::trait::get_sql_type<T5>::get()) + "|" + std::string(qx::trait::get_sql_type<T6>::get()) + "|" + std::string(qx::trait::get_sql_type<T7>::get()) + "|" + std::string(qx::trait::get_sql_type<T8>::get()) + "|" + std::string(qx::trait::get_sql_type<T9>::get())); return s.c_str(); } };

} // namespace trait
} // namespace qx

#define QX_REGISTER_TRAIT_GET_SQL_TYPE(className, sqlType) \
namespace qx { namespace trait { namespace detail { \
template <> \
struct get_sql_type< className > \
{ static inline const char * get() { return get_sql_type_by_class_name(#className, sqlType); } }; }}}

QX_REGISTER_TRAIT_GET_SQL_TYPE(bool, "SMALLINT")
QX_REGISTER_TRAIT_GET_SQL_TYPE(qx_bool, "TEXT")
QX_REGISTER_TRAIT_GET_SQL_TYPE(char, "SMALLINT")
QX_REGISTER_TRAIT_GET_SQL_TYPE(short, "SMALLINT")
QX_REGISTER_TRAIT_GET_SQL_TYPE(int, "INTEGER")
QX_REGISTER_TRAIT_GET_SQL_TYPE(long, "INTEGER")
QX_REGISTER_TRAIT_GET_SQL_TYPE(long long, "INTEGER")
QX_REGISTER_TRAIT_GET_SQL_TYPE(float, "FLOAT")
QX_REGISTER_TRAIT_GET_SQL_TYPE(double, "FLOAT")
QX_REGISTER_TRAIT_GET_SQL_TYPE(long double, "FLOAT")
QX_REGISTER_TRAIT_GET_SQL_TYPE(unsigned short, "SMALLINT")
QX_REGISTER_TRAIT_GET_SQL_TYPE(unsigned int, "INTEGER")
QX_REGISTER_TRAIT_GET_SQL_TYPE(unsigned long, "INTEGER")
QX_REGISTER_TRAIT_GET_SQL_TYPE(unsigned long long, "INTEGER")
QX_REGISTER_TRAIT_GET_SQL_TYPE(std::string, "TEXT")
QX_REGISTER_TRAIT_GET_SQL_TYPE(std::wstring, "TEXT")
QX_REGISTER_TRAIT_GET_SQL_TYPE(QString, "TEXT")
QX_REGISTER_TRAIT_GET_SQL_TYPE(QVariant, "TEXT")
QX_REGISTER_TRAIT_GET_SQL_TYPE(QUuid, "TEXT")
QX_REGISTER_TRAIT_GET_SQL_TYPE(QDate, "DATE")
QX_REGISTER_TRAIT_GET_SQL_TYPE(QTime, "TIME")
QX_REGISTER_TRAIT_GET_SQL_TYPE(QDateTime, "TIMESTAMP")
QX_REGISTER_TRAIT_GET_SQL_TYPE(QByteArray, "BLOB")
QX_REGISTER_TRAIT_GET_SQL_TYPE(qx::QxDateNeutral, "TEXT")
QX_REGISTER_TRAIT_GET_SQL_TYPE(qx::QxTimeNeutral, "TEXT")
QX_REGISTER_TRAIT_GET_SQL_TYPE(qx::QxDateTimeNeutral, "TEXT")

#endif // _QX_GET_SQL_TYPE_H_
