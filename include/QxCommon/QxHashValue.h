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

#ifndef _QX_HASH_VALUE_H_
#define _QX_HASH_VALUE_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxHashValue.h
 * \author Lionel Marty
 * \ingroup QxCommon
 * \brief Specialize hash_value function for some Qt and boost types (used for example by qx::QxCollection<Key, Value> container)
 */

#include <QtCore/qstring.h>
#include <QtCore/qdatetime.h>
#include <QtCore/qvariant.h>
#include <QtCore/qpair.h>

#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
#define qx_hash_result uint
#else // (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
#define qx_hash_result std::size_t
#endif // (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))

inline std::size_t hash_value(const QString & s)      { return qHash(s); }
inline std::size_t hash_value(const QVariant & v)     { return qHash(v.toString()); }
inline std::size_t hash_value(const QDate & d)        { return qHash(d.toJulianDay()); }
inline std::size_t hash_value(const QTime & t)        { return qHash(t.toString()); }
inline std::size_t hash_value(const QDateTime & dt)   { return qHash(dt.toString()); }

inline qx_hash_result qHash(const QVariant & v)       { return static_cast<qx_hash_result>(hash_value(v)); }

#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
inline qx_hash_result qHash(const QDate & d)          { return static_cast<qx_hash_result>(hash_value(d)); }
inline qx_hash_result qHash(const QTime & t)          { return static_cast<qx_hash_result>(hash_value(t)); }
inline qx_hash_result qHash(const QDateTime & dt)     { return static_cast<qx_hash_result>(hash_value(dt)); }
#endif // (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))

namespace qx {
template <class T>
inline void hash_combine(std::size_t & seed, const T & t)
{ seed ^= qHash(t) + 0x9e3779b9 + (seed << 6) + (seed >> 2); }
} // namespace qx

template <typename T0, typename T1>
inline std::size_t hash_value(const QPair<T0, T1> & p)
{
   std::size_t seed = 0;
   qx::hash_combine(seed, p.first);
   qx::hash_combine(seed, p.second);
   return seed;
}

#ifdef _QX_ENABLE_BOOST

namespace boost {
namespace tuples {

template <typename T0, typename T1>
inline std::size_t hash_value(const boost::tuple<T0, T1> & tu)
{
   std::size_t seed = 0;
   qx::hash_combine(seed, boost::get<0>(tu));
   qx::hash_combine(seed, boost::get<1>(tu));
   return seed;
}

template <typename T0, class T1, typename T2>
inline std::size_t hash_value(const boost::tuple<T0, T1, T2> & tu)
{
   std::size_t seed = 0;
   qx::hash_combine(seed, boost::get<0>(tu));
   qx::hash_combine(seed, boost::get<1>(tu));
   qx::hash_combine(seed, boost::get<2>(tu));
   return seed;
}

template <typename T0, typename T1, typename T2, typename T3>
inline std::size_t hash_value(const boost::tuple<T0, T1, T2, T3> & tu)
{
   std::size_t seed = 0;
   qx::hash_combine(seed, boost::get<0>(tu));
   qx::hash_combine(seed, boost::get<1>(tu));
   qx::hash_combine(seed, boost::get<2>(tu));
   qx::hash_combine(seed, boost::get<3>(tu));
   return seed;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4>
inline std::size_t hash_value(const boost::tuple<T0, T1, T2, T3, T4> & tu)
{
   std::size_t seed = 0;
   qx::hash_combine(seed, boost::get<0>(tu));
   qx::hash_combine(seed, boost::get<1>(tu));
   qx::hash_combine(seed, boost::get<2>(tu));
   qx::hash_combine(seed, boost::get<3>(tu));
   qx::hash_combine(seed, boost::get<4>(tu));
   return seed;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
inline std::size_t hash_value(const boost::tuple<T0, T1, T2, T3, T4, T5> & tu)
{
   std::size_t seed = 0;
   qx::hash_combine(seed, boost::get<0>(tu));
   qx::hash_combine(seed, boost::get<1>(tu));
   qx::hash_combine(seed, boost::get<2>(tu));
   qx::hash_combine(seed, boost::get<3>(tu));
   qx::hash_combine(seed, boost::get<4>(tu));
   qx::hash_combine(seed, boost::get<5>(tu));
   return seed;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
inline std::size_t hash_value(const boost::tuple<T0, T1, T2, T3, T4, T5, T6> & tu)
{
   std::size_t seed = 0;
   qx::hash_combine(seed, boost::get<0>(tu));
   qx::hash_combine(seed, boost::get<1>(tu));
   qx::hash_combine(seed, boost::get<2>(tu));
   qx::hash_combine(seed, boost::get<3>(tu));
   qx::hash_combine(seed, boost::get<4>(tu));
   qx::hash_combine(seed, boost::get<5>(tu));
   qx::hash_combine(seed, boost::get<6>(tu));
   return seed;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
inline std::size_t hash_value(const boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7> & tu)
{
   std::size_t seed = 0;
   qx::hash_combine(seed, boost::get<0>(tu));
   qx::hash_combine(seed, boost::get<1>(tu));
   qx::hash_combine(seed, boost::get<2>(tu));
   qx::hash_combine(seed, boost::get<3>(tu));
   qx::hash_combine(seed, boost::get<4>(tu));
   qx::hash_combine(seed, boost::get<5>(tu));
   qx::hash_combine(seed, boost::get<6>(tu));
   qx::hash_combine(seed, boost::get<7>(tu));
   return seed;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
inline std::size_t hash_value(const boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8> & tu)
{
   std::size_t seed = 0;
   qx::hash_combine(seed, boost::get<0>(tu));
   qx::hash_combine(seed, boost::get<1>(tu));
   qx::hash_combine(seed, boost::get<2>(tu));
   qx::hash_combine(seed, boost::get<3>(tu));
   qx::hash_combine(seed, boost::get<4>(tu));
   qx::hash_combine(seed, boost::get<5>(tu));
   qx::hash_combine(seed, boost::get<6>(tu));
   qx::hash_combine(seed, boost::get<7>(tu));
   qx::hash_combine(seed, boost::get<8>(tu));
   return seed;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
inline std::size_t hash_value(const boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> & tu)
{
   std::size_t seed = 0;
   qx::hash_combine(seed, boost::get<0>(tu));
   qx::hash_combine(seed, boost::get<1>(tu));
   qx::hash_combine(seed, boost::get<2>(tu));
   qx::hash_combine(seed, boost::get<3>(tu));
   qx::hash_combine(seed, boost::get<4>(tu));
   qx::hash_combine(seed, boost::get<5>(tu));
   qx::hash_combine(seed, boost::get<6>(tu));
   qx::hash_combine(seed, boost::get<7>(tu));
   qx::hash_combine(seed, boost::get<8>(tu));
   qx::hash_combine(seed, boost::get<9>(tu));
   return seed;
}

template <typename T0, typename T1>
inline qx_hash_result qHash(const boost::tuple<T0, T1> & tu)
{ return static_cast<qx_hash_result>(hash_value(tu)); }

template <typename T0, class T1, typename T2>
inline qx_hash_result qHash(const boost::tuple<T0, T1, T2> & tu)
{ return static_cast<qx_hash_result>(hash_value(tu)); }

template <typename T0, typename T1, typename T2, typename T3>
inline qx_hash_result qHash(const boost::tuple<T0, T1, T2, T3> & tu)
{ return static_cast<qx_hash_result>(hash_value(tu)); }

template <typename T0, typename T1, typename T2, typename T3, typename T4>
inline qx_hash_result qHash(const boost::tuple<T0, T1, T2, T3, T4> & tu)
{ return static_cast<qx_hash_result>(hash_value(tu)); }

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
inline qx_hash_result qHash(const boost::tuple<T0, T1, T2, T3, T4, T5> & tu)
{ return static_cast<qx_hash_result>(hash_value(tu)); }

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
inline qx_hash_result qHash(const boost::tuple<T0, T1, T2, T3, T4, T5, T6> & tu)
{ return static_cast<qx_hash_result>(hash_value(tu)); }

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
inline qx_hash_result qHash(const boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7> & tu)
{ return static_cast<qx_hash_result>(hash_value(tu)); }

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
inline qx_hash_result qHash(const boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8> & tu)
{ return static_cast<qx_hash_result>(hash_value(tu)); }

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
inline qx_hash_result qHash(const boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> & tu)
{ return static_cast<qx_hash_result>(hash_value(tu)); }

} // namespace tuples
} // namespace boost

#endif // _QX_ENABLE_BOOST

// Compilation option '_QX_HASH_NO_STD_NAMESPACE'
// Try to avoid compilation error, something like : error: no matching function for call to 'qHash(const std::tuple<...>&)'
// This is due to C++ ADL to resolve specialized functions : qHash(T) should be implemented in the same namespace as T
// For 'std' classes, it should be NOT allowed : the behavior of a C++ program is undefined if it adds declarations or definitions to namespace std or to a namespace within namespace std
// More details here : https://www.kdab.com/how-to-declare-a-qhash-overload/
// And here : https://stackoverflow.com/questions/47460098/using-standard-library-types-as-keys-in-qhash-or-qset
#ifndef _QX_HASH_NO_STD_NAMESPACE
namespace std {
#endif // _QX_HASH_NO_STD_NAMESPACE

#ifndef QT_NO_STL
inline qx_hash_result qHash(const std::string & s)     { QString tmp = QString::fromStdString(s); return qHash(tmp); }
inline qx_hash_result qHash(const std::wstring & s)    { QString tmp = QString::fromStdWString(s); return qHash(tmp); }
#else // QT_NO_STL
inline qx_hash_result qHash(const std::string & s)     { QString tmp = QString::fromLatin1(s.data(), int(s.size())); return qHash(tmp); }
inline qx_hash_result qHash(const std::wstring & s)    { qAssert(false); /* Need STL compatibility ! */ return 0; }
#endif // QT_NO_STL

template <typename T0, typename T1>
inline std::size_t hash_value(const std::tuple<T0, T1> & tu)
{
   std::size_t seed = 0;
   qx::hash_combine(seed, std::get<0>(tu));
   qx::hash_combine(seed, std::get<1>(tu));
   return seed;
}

template <typename T0, class T1, typename T2>
inline std::size_t hash_value(const std::tuple<T0, T1, T2> & tu)
{
   std::size_t seed = 0;
   qx::hash_combine(seed, std::get<0>(tu));
   qx::hash_combine(seed, std::get<1>(tu));
   qx::hash_combine(seed, std::get<2>(tu));
   return seed;
}

template <typename T0, typename T1, typename T2, typename T3>
inline std::size_t hash_value(const std::tuple<T0, T1, T2, T3> & tu)
{
   std::size_t seed = 0;
   qx::hash_combine(seed, std::get<0>(tu));
   qx::hash_combine(seed, std::get<1>(tu));
   qx::hash_combine(seed, std::get<2>(tu));
   qx::hash_combine(seed, std::get<3>(tu));
   return seed;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4>
inline std::size_t hash_value(const std::tuple<T0, T1, T2, T3, T4> & tu)
{
   std::size_t seed = 0;
   qx::hash_combine(seed, std::get<0>(tu));
   qx::hash_combine(seed, std::get<1>(tu));
   qx::hash_combine(seed, std::get<2>(tu));
   qx::hash_combine(seed, std::get<3>(tu));
   qx::hash_combine(seed, std::get<4>(tu));
   return seed;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
inline std::size_t hash_value(const std::tuple<T0, T1, T2, T3, T4, T5> & tu)
{
   std::size_t seed = 0;
   qx::hash_combine(seed, std::get<0>(tu));
   qx::hash_combine(seed, std::get<1>(tu));
   qx::hash_combine(seed, std::get<2>(tu));
   qx::hash_combine(seed, std::get<3>(tu));
   qx::hash_combine(seed, std::get<4>(tu));
   qx::hash_combine(seed, std::get<5>(tu));
   return seed;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
inline std::size_t hash_value(const std::tuple<T0, T1, T2, T3, T4, T5, T6> & tu)
{
   std::size_t seed = 0;
   qx::hash_combine(seed, std::get<0>(tu));
   qx::hash_combine(seed, std::get<1>(tu));
   qx::hash_combine(seed, std::get<2>(tu));
   qx::hash_combine(seed, std::get<3>(tu));
   qx::hash_combine(seed, std::get<4>(tu));
   qx::hash_combine(seed, std::get<5>(tu));
   qx::hash_combine(seed, std::get<6>(tu));
   return seed;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
inline std::size_t hash_value(const std::tuple<T0, T1, T2, T3, T4, T5, T6, T7> & tu)
{
   std::size_t seed = 0;
   qx::hash_combine(seed, std::get<0>(tu));
   qx::hash_combine(seed, std::get<1>(tu));
   qx::hash_combine(seed, std::get<2>(tu));
   qx::hash_combine(seed, std::get<3>(tu));
   qx::hash_combine(seed, std::get<4>(tu));
   qx::hash_combine(seed, std::get<5>(tu));
   qx::hash_combine(seed, std::get<6>(tu));
   qx::hash_combine(seed, std::get<7>(tu));
   return seed;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
inline std::size_t hash_value(const std::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8> & tu)
{
   std::size_t seed = 0;
   qx::hash_combine(seed, std::get<0>(tu));
   qx::hash_combine(seed, std::get<1>(tu));
   qx::hash_combine(seed, std::get<2>(tu));
   qx::hash_combine(seed, std::get<3>(tu));
   qx::hash_combine(seed, std::get<4>(tu));
   qx::hash_combine(seed, std::get<5>(tu));
   qx::hash_combine(seed, std::get<6>(tu));
   qx::hash_combine(seed, std::get<7>(tu));
   qx::hash_combine(seed, std::get<8>(tu));
   return seed;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
inline std::size_t hash_value(const std::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> & tu)
{
   std::size_t seed = 0;
   qx::hash_combine(seed, std::get<0>(tu));
   qx::hash_combine(seed, std::get<1>(tu));
   qx::hash_combine(seed, std::get<2>(tu));
   qx::hash_combine(seed, std::get<3>(tu));
   qx::hash_combine(seed, std::get<4>(tu));
   qx::hash_combine(seed, std::get<5>(tu));
   qx::hash_combine(seed, std::get<6>(tu));
   qx::hash_combine(seed, std::get<7>(tu));
   qx::hash_combine(seed, std::get<8>(tu));
   qx::hash_combine(seed, std::get<9>(tu));
   return seed;
}

#if ((QT_VERSION < QT_VERSION_CHECK(5, 7, 0)) || ((QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)) && (QT_VERSION < QT_VERSION_CHECK(6, 2, 0))))
template <typename T0, typename T1>
inline qx_hash_result qHash(const std::pair<T0, T1> & p)
{
   std::size_t seed = 0;
   qx::hash_combine(seed, p.first);
   qx::hash_combine(seed, p.second);
   return static_cast<qx_hash_result>(seed);
}
#endif // ((QT_VERSION < QT_VERSION_CHECK(5, 7, 0)) || ((QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)) && (QT_VERSION < QT_VERSION_CHECK(6, 2, 0))))

template <typename T0, typename T1>
inline qx_hash_result qHash(const std::tuple<T0, T1> & tu)
{ return static_cast<qx_hash_result>(hash_value(tu)); }

template <typename T0, class T1, typename T2>
inline qx_hash_result qHash(const std::tuple<T0, T1, T2> & tu)
{ return static_cast<qx_hash_result>(hash_value(tu)); }

template <typename T0, typename T1, typename T2, typename T3>
inline qx_hash_result qHash(const std::tuple<T0, T1, T2, T3> & tu)
{ return static_cast<qx_hash_result>(hash_value(tu)); }

template <typename T0, typename T1, typename T2, typename T3, typename T4>
inline qx_hash_result qHash(const std::tuple<T0, T1, T2, T3, T4> & tu)
{ return static_cast<qx_hash_result>(hash_value(tu)); }

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
inline qx_hash_result qHash(const std::tuple<T0, T1, T2, T3, T4, T5> & tu)
{ return static_cast<qx_hash_result>(hash_value(tu)); }

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
inline qx_hash_result qHash(const std::tuple<T0, T1, T2, T3, T4, T5, T6> & tu)
{ return static_cast<qx_hash_result>(hash_value(tu)); }

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
inline qx_hash_result qHash(const std::tuple<T0, T1, T2, T3, T4, T5, T6, T7> & tu)
{ return static_cast<qx_hash_result>(hash_value(tu)); }

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
inline qx_hash_result qHash(const std::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8> & tu)
{ return static_cast<qx_hash_result>(hash_value(tu)); }

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
inline qx_hash_result qHash(const std::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> & tu)
{ return static_cast<qx_hash_result>(hash_value(tu)); }

#ifndef _QX_HASH_NO_STD_NAMESPACE
} // namespace std
#endif // _QX_HASH_NO_STD_NAMESPACE

#endif // _QX_HASH_VALUE_H_
