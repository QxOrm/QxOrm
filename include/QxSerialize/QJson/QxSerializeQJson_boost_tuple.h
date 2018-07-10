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

#ifndef _QX_NO_JSON
#ifndef _QX_SERIALIZE_QJSON_BOOST_TUPLE_H_
#define _QX_SERIALIZE_QJSON_BOOST_TUPLE_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSerializeQJson_boost_tuple.h
 * \author Lionel Marty
 * \ingroup QxSerialize
 * \brief Provide a Qt QJson serialization method (save/load) for type boost::tuple<T0, T1, ..., T9>
 */

#include <QtCore/qjsonvalue.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qjsonarray.h>

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/tuple/tuple_io.hpp>

#include <QxConvert/QxConvert.h>
#include <QxConvert/QxConvert_Impl.h>

namespace qx {
namespace cvt {
namespace detail {

template <typename T0, typename T1>
struct QxConvert_ToJson< boost::tuple<T0, T1> >
{
   static inline QJsonValue toJson(const boost::tuple<T0, T1> & t, const QString & format)
   {
      QJsonArray arr; QJsonValue val;
      val = qx::cvt::to_json(boost::get<0>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<1>(t), format); arr.append(val);
      return QJsonValue(arr);
   }
};

template <typename T0, typename T1, typename T2>
struct QxConvert_ToJson< boost::tuple<T0, T1, T2> >
{
   static inline QJsonValue toJson(const boost::tuple<T0, T1, T2> & t, const QString & format)
   {
      QJsonArray arr; QJsonValue val;
      val = qx::cvt::to_json(boost::get<0>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<1>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<2>(t), format); arr.append(val);
      return QJsonValue(arr);
   }
};

template <typename T0, typename T1, typename T2, typename T3>
struct QxConvert_ToJson< boost::tuple<T0, T1, T2, T3> >
{
   static inline QJsonValue toJson(const boost::tuple<T0, T1, T2, T3> & t, const QString & format)
   {
      QJsonArray arr; QJsonValue val;
      val = qx::cvt::to_json(boost::get<0>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<1>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<2>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<3>(t), format); arr.append(val);
      return QJsonValue(arr);
   }
};

template <typename T0, typename T1, typename T2, typename T3, typename T4>
struct QxConvert_ToJson< boost::tuple<T0, T1, T2, T3, T4> >
{
   static inline QJsonValue toJson(const boost::tuple<T0, T1, T2, T3, T4> & t, const QString & format)
   {
      QJsonArray arr; QJsonValue val;
      val = qx::cvt::to_json(boost::get<0>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<1>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<2>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<3>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<4>(t), format); arr.append(val);
      return QJsonValue(arr);
   }
};

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
struct QxConvert_ToJson< boost::tuple<T0, T1, T2, T3, T4, T5> >
{
   static inline QJsonValue toJson(const boost::tuple<T0, T1, T2, T3, T4, T5> & t, const QString & format)
   {
      QJsonArray arr; QJsonValue val;
      val = qx::cvt::to_json(boost::get<0>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<1>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<2>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<3>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<4>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<5>(t), format); arr.append(val);
      return QJsonValue(arr);
   }
};

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct QxConvert_ToJson< boost::tuple<T0, T1, T2, T3, T4, T5, T6> >
{
   static inline QJsonValue toJson(const boost::tuple<T0, T1, T2, T3, T4, T5, T6> & t, const QString & format)
   {
      QJsonArray arr; QJsonValue val;
      val = qx::cvt::to_json(boost::get<0>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<1>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<2>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<3>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<4>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<5>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<6>(t), format); arr.append(val);
      return QJsonValue(arr);
   }
};

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct QxConvert_ToJson< boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7> >
{
   static inline QJsonValue toJson(const boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7> & t, const QString & format)
   {
      QJsonArray arr; QJsonValue val;
      val = qx::cvt::to_json(boost::get<0>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<1>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<2>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<3>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<4>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<5>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<6>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<7>(t), format); arr.append(val);
      return QJsonValue(arr);
   }
};

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
struct QxConvert_ToJson< boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8> >
{
   static inline QJsonValue toJson(const boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8> & t, const QString & format)
   {
      QJsonArray arr; QJsonValue val;
      val = qx::cvt::to_json(boost::get<0>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<1>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<2>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<3>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<4>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<5>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<6>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<7>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<8>(t), format); arr.append(val);
      return QJsonValue(arr);
   }
};

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct QxConvert_ToJson< boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> >
{
   static inline QJsonValue toJson(const boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> & t, const QString & format)
   {
      QJsonArray arr; QJsonValue val;
      val = qx::cvt::to_json(boost::get<0>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<1>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<2>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<3>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<4>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<5>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<6>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<7>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<8>(t), format); arr.append(val);
      val = qx::cvt::to_json(boost::get<9>(t), format); arr.append(val);
      return QJsonValue(arr);
   }
};

template <typename T0, typename T1>
struct QxConvert_FromJson< boost::tuple<T0, T1> >
{
   static inline qx_bool fromJson(const QJsonValue & j, boost::tuple<T0, T1> & t, const QString & format)
   {
      if (! j.isArray()) { return qx_bool(true); }
      QJsonArray arr = j.toArray();
      qx::cvt::from_json(arr.at(0), boost::get<0>(t), format);
      qx::cvt::from_json(arr.at(1), boost::get<1>(t), format);
      return qx_bool(true);
   }
};

template <typename T0, typename T1, typename T2>
struct QxConvert_FromJson< boost::tuple<T0, T1, T2> >
{
   static inline qx_bool fromJson(const QJsonValue & j, boost::tuple<T0, T1, T2> & t, const QString & format)
   {
      if (! j.isArray()) { return qx_bool(true); }
      QJsonArray arr = j.toArray();
      qx::cvt::from_json(arr.at(0), boost::get<0>(t), format);
      qx::cvt::from_json(arr.at(1), boost::get<1>(t), format);
      qx::cvt::from_json(arr.at(2), boost::get<2>(t), format);
      return qx_bool(true);
   }
};

template <typename T0, typename T1, typename T2, typename T3>
struct QxConvert_FromJson< boost::tuple<T0, T1, T2, T3> >
{
   static inline qx_bool fromJson(const QJsonValue & j, boost::tuple<T0, T1, T2, T3> & t, const QString & format)
   {
      if (! j.isArray()) { return qx_bool(true); }
      QJsonArray arr = j.toArray();
      qx::cvt::from_json(arr.at(0), boost::get<0>(t), format);
      qx::cvt::from_json(arr.at(1), boost::get<1>(t), format);
      qx::cvt::from_json(arr.at(2), boost::get<2>(t), format);
      qx::cvt::from_json(arr.at(3), boost::get<3>(t), format);
      return qx_bool(true);
   }
};

template <typename T0, typename T1, typename T2, typename T3, typename T4>
struct QxConvert_FromJson< boost::tuple<T0, T1, T2, T3, T4> >
{
   static inline qx_bool fromJson(const QJsonValue & j, boost::tuple<T0, T1, T2, T3, T4> & t, const QString & format)
   {
      if (! j.isArray()) { return qx_bool(true); }
      QJsonArray arr = j.toArray();
      qx::cvt::from_json(arr.at(0), boost::get<0>(t), format);
      qx::cvt::from_json(arr.at(1), boost::get<1>(t), format);
      qx::cvt::from_json(arr.at(2), boost::get<2>(t), format);
      qx::cvt::from_json(arr.at(3), boost::get<3>(t), format);
      qx::cvt::from_json(arr.at(4), boost::get<4>(t), format);
      return qx_bool(true);
   }
};

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
struct QxConvert_FromJson< boost::tuple<T0, T1, T2, T3, T4, T5> >
{
   static inline qx_bool fromJson(const QJsonValue & j, boost::tuple<T0, T1, T2, T3, T4, T5> & t, const QString & format)
   {
      if (! j.isArray()) { return qx_bool(true); }
      QJsonArray arr = j.toArray();
      qx::cvt::from_json(arr.at(0), boost::get<0>(t), format);
      qx::cvt::from_json(arr.at(1), boost::get<1>(t), format);
      qx::cvt::from_json(arr.at(2), boost::get<2>(t), format);
      qx::cvt::from_json(arr.at(3), boost::get<3>(t), format);
      qx::cvt::from_json(arr.at(4), boost::get<4>(t), format);
      qx::cvt::from_json(arr.at(5), boost::get<5>(t), format);
      return qx_bool(true);
   }
};

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct QxConvert_FromJson< boost::tuple<T0, T1, T2, T3, T4, T5, T6> >
{
   static inline qx_bool fromJson(const QJsonValue & j, boost::tuple<T0, T1, T2, T3, T4, T5, T6> & t, const QString & format)
   {
      if (! j.isArray()) { return qx_bool(true); }
      QJsonArray arr = j.toArray();
      qx::cvt::from_json(arr.at(0), boost::get<0>(t), format);
      qx::cvt::from_json(arr.at(1), boost::get<1>(t), format);
      qx::cvt::from_json(arr.at(2), boost::get<2>(t), format);
      qx::cvt::from_json(arr.at(3), boost::get<3>(t), format);
      qx::cvt::from_json(arr.at(4), boost::get<4>(t), format);
      qx::cvt::from_json(arr.at(5), boost::get<5>(t), format);
      qx::cvt::from_json(arr.at(6), boost::get<6>(t), format);
      return qx_bool(true);
   }
};

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct QxConvert_FromJson< boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7> >
{
   static inline qx_bool fromJson(const QJsonValue & j, boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7> & t, const QString & format)
   {
      if (! j.isArray()) { return qx_bool(true); }
      QJsonArray arr = j.toArray();
      qx::cvt::from_json(arr.at(0), boost::get<0>(t), format);
      qx::cvt::from_json(arr.at(1), boost::get<1>(t), format);
      qx::cvt::from_json(arr.at(2), boost::get<2>(t), format);
      qx::cvt::from_json(arr.at(3), boost::get<3>(t), format);
      qx::cvt::from_json(arr.at(4), boost::get<4>(t), format);
      qx::cvt::from_json(arr.at(5), boost::get<5>(t), format);
      qx::cvt::from_json(arr.at(6), boost::get<6>(t), format);
      qx::cvt::from_json(arr.at(7), boost::get<7>(t), format);
      return qx_bool(true);
   }
};

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
struct QxConvert_FromJson< boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8> >
{
   static inline qx_bool fromJson(const QJsonValue & j, boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8> & t, const QString & format)
   {
      if (! j.isArray()) { return qx_bool(true); }
      QJsonArray arr = j.toArray();
      qx::cvt::from_json(arr.at(0), boost::get<0>(t), format);
      qx::cvt::from_json(arr.at(1), boost::get<1>(t), format);
      qx::cvt::from_json(arr.at(2), boost::get<2>(t), format);
      qx::cvt::from_json(arr.at(3), boost::get<3>(t), format);
      qx::cvt::from_json(arr.at(4), boost::get<4>(t), format);
      qx::cvt::from_json(arr.at(5), boost::get<5>(t), format);
      qx::cvt::from_json(arr.at(6), boost::get<6>(t), format);
      qx::cvt::from_json(arr.at(7), boost::get<7>(t), format);
      qx::cvt::from_json(arr.at(8), boost::get<8>(t), format);
      return qx_bool(true);
   }
};

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct QxConvert_FromJson< boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> >
{
   static inline qx_bool fromJson(const QJsonValue & j, boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> & t, const QString & format)
   {
      if (! j.isArray()) { return qx_bool(true); }
      QJsonArray arr = j.toArray();
      qx::cvt::from_json(arr.at(0), boost::get<0>(t), format);
      qx::cvt::from_json(arr.at(1), boost::get<1>(t), format);
      qx::cvt::from_json(arr.at(2), boost::get<2>(t), format);
      qx::cvt::from_json(arr.at(3), boost::get<3>(t), format);
      qx::cvt::from_json(arr.at(4), boost::get<4>(t), format);
      qx::cvt::from_json(arr.at(5), boost::get<5>(t), format);
      qx::cvt::from_json(arr.at(6), boost::get<6>(t), format);
      qx::cvt::from_json(arr.at(7), boost::get<7>(t), format);
      qx::cvt::from_json(arr.at(8), boost::get<8>(t), format);
      qx::cvt::from_json(arr.at(9), boost::get<9>(t), format);
      return qx_bool(true);
   }
};

} // namespace detail
} // namespace cvt
} // namespace qx

#endif // _QX_SERIALIZE_QJSON_BOOST_TUPLE_H_
#endif // _QX_NO_JSON
