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

#ifndef _QX_IS_VALID_PRIMARY_KEY_H_
#define _QX_IS_VALID_PRIMARY_KEY_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file is_valid_primary_key.h
 * \author Lionel Marty
 * \ingroup QxTraits
 * \brief qx::trait::is_valid_primary_key<T>(const T & t) : return true if t can be a valid primary key to be inserted into a database, otherwise return false
 */

namespace qx {
namespace trait {
namespace detail {

/*!
 * \ingroup QxTraits
 * \brief qx::trait::is_valid_primary_key<T>(const T & t) : return true if t can be a valid primary key to be inserted into a database, otherwise return false
 */
template <typename T>
struct is_valid_primary_key
{ static inline bool get(const T & t) { Q_UNUSED(t); qAssert(false); return false; } };

template <>
struct is_valid_primary_key<short>
{ static inline bool get(const short & t) { return (t != 0); } };

template <>
struct is_valid_primary_key<int>
{ static inline bool get(const int & t) { return (t != 0); } };

template <>
struct is_valid_primary_key<long>
{ static inline bool get(const long & t) { return (t != 0); } };

template <>
struct is_valid_primary_key<long long>
{ static inline bool get(const long long & t) { return (t != 0); } };

template <>
struct is_valid_primary_key<QString>
{ static inline bool get(const QString & t) { return (! t.isEmpty()); } };

template <>
struct is_valid_primary_key<QByteArray>
{ static inline bool get(const QByteArray & t) { return (! t.isEmpty()); } };

template <>
struct is_valid_primary_key<std::string>
{ static inline bool get(const std::string & t) { return (! t.empty()); } };

template <>
struct is_valid_primary_key<std::wstring>
{ static inline bool get(const std::wstring & t) { return (! t.empty()); } };

template <>
struct is_valid_primary_key<QVariant>
{
   static inline bool get(const QVariant & t)
   {
      if (t.type() == QVariant::ByteArray) { return qx::trait::detail::is_valid_primary_key<QByteArray>::get(t.toByteArray()); }
      if (t.type() == QVariant::String) { return qx::trait::detail::is_valid_primary_key<QString>::get(t.toString()); }
      return (! t.isNull() && (t.toLongLong() != 0));
   }
};

} // namespace detail

template <typename T>
inline bool is_valid_primary_key(const T & t)
{ return qx::trait::detail::is_valid_primary_key<T>::get(t); }

} // namespace trait
} // namespace qx

#endif // _QX_IS_VALID_PRIMARY_KEY_H_
