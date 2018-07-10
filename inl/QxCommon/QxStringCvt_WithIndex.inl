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

namespace qx {
namespace cvt {
namespace detail {

template <typename T>
struct QxStringCvt_WithIndex
{
   static inline QString toString(const T & data, const QString & format, int index)                     { return qx::cvt::detail::QxStringCvt_ToString<T>::toString(data, format, index); }
   static inline qx_bool fromString(T & data, const QString & s, const QString & format, int index)      { return qx::cvt::detail::QxStringCvt_FromString<T>::fromString(s, data, format, index); }
   static inline QVariant toVariant(const T & data, const QString & format, int index)                   { return qx::cvt::detail::QxStringCvt_ToVariant<T>::toVariant(data, format, index); }
   static inline qx_bool fromVariant(T & data, const QVariant & v, const QString & format, int index)    { return qx::cvt::detail::QxStringCvt_FromVariant<T>::fromVariant(v, data, format, index); }
};

template <typename T1, typename T2>
struct QxStringCvt_WithIndex< std::pair<T1, T2> >
{
   typedef std::pair<T1, T2> T;
   static inline QString toString(const T & data, const QString & format, int index)                     { verifyIndex(index); return ((index == 1) ? qx::cvt::to_string(data.second, format) : ((index == 0) ? qx::cvt::to_string(data.first, format) : qx::cvt::to_string(data, format))); }
   static inline qx_bool fromString(T & data, const QString & s, const QString & format, int index)      { verifyIndex(index); return ((index == 1) ? qx::cvt::from_string(s, data.second, format) : ((index == 0) ? qx::cvt::from_string(s, data.first, format) : qx::cvt::from_string(s, data, format))); }
   static inline QVariant toVariant(const T & data, const QString & format, int index)                   { verifyIndex(index); return ((index == 1) ? qx::cvt::to_variant(data.second, format) : ((index == 0) ? qx::cvt::to_variant(data.first, format) : qx::cvt::to_variant(data, format))); }
   static inline qx_bool fromVariant(T & data, const QVariant & v, const QString & format, int index)    { verifyIndex(index); return ((index == 1) ? qx::cvt::from_variant(v, data.second, format) : ((index == 0) ? qx::cvt::from_variant(v, data.first, format) : qx::cvt::from_variant(v, data, format))); }
private:
   static inline void verifyIndex(int index) { Q_UNUSED(index); qAssert((index >= -1) && (index < 2)); }
};

template <typename T1, typename T2>
struct QxStringCvt_WithIndex< QPair<T1, T2> >
{
   typedef QPair<T1, T2> T;
   static inline QString toString(const T & data, const QString & format, int index)                     { verifyIndex(index); return ((index == 1) ? qx::cvt::to_string(data.second, format) : ((index == 0) ? qx::cvt::to_string(data.first, format) : qx::cvt::to_string(data, format))); }
   static inline qx_bool fromString(T & data, const QString & s, const QString & format, int index)      { verifyIndex(index); return ((index == 1) ? qx::cvt::from_string(s, data.second, format) : ((index == 0) ? qx::cvt::from_string(s, data.first, format) : qx::cvt::from_string(s, data, format))); }
   static inline QVariant toVariant(const T & data, const QString & format, int index)                   { verifyIndex(index); return ((index == 1) ? qx::cvt::to_variant(data.second, format) : ((index == 0) ? qx::cvt::to_variant(data.first, format) : qx::cvt::to_variant(data, format))); }
   static inline qx_bool fromVariant(T & data, const QVariant & v, const QString & format, int index)    { verifyIndex(index); return ((index == 1) ? qx::cvt::from_variant(v, data.second, format) : ((index == 0) ? qx::cvt::from_variant(v, data.first, format) : qx::cvt::from_variant(v, data, format))); }
private:
   static inline void verifyIndex(int index) { Q_UNUSED(index); qAssert((index >= -1) && (index < 2)); }
};

template <typename T1, typename T2>
struct QxStringCvt_WithIndex< boost::tuple<T1, T2> >
{
   typedef boost::tuple<T1, T2> T;
   static inline QString toString(const T & data, const QString & format, int index)                     { verifyIndex(index); return ((index == 1) ? qx::cvt::to_string(boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::to_string(boost::tuples::get<0>(data), format) : qx::cvt::to_string(data, format))); }
   static inline qx_bool fromString(T & data, const QString & s, const QString & format, int index)      { verifyIndex(index); return ((index == 1) ? qx::cvt::from_string(s, boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::from_string(s, boost::tuples::get<0>(data), format) : qx::cvt::from_string(s, data, format))); }
   static inline QVariant toVariant(const T & data, const QString & format, int index)                   { verifyIndex(index); return ((index == 1) ? qx::cvt::to_variant(boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::to_variant(boost::tuples::get<0>(data), format) : qx::cvt::to_variant(data, format))); }
   static inline qx_bool fromVariant(T & data, const QVariant & v, const QString & format, int index)    { verifyIndex(index); return ((index == 1) ? qx::cvt::from_variant(v, boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::from_variant(v, boost::tuples::get<0>(data), format) : qx::cvt::from_variant(v, data, format))); }
private:
   static inline void verifyIndex(int index) { Q_UNUSED(index); qAssert((index >= -1) && (index < 2)); }
};

template <typename T1, typename T2, typename T3>
struct QxStringCvt_WithIndex< boost::tuple<T1, T2, T3> >
{
   typedef boost::tuple<T1, T2, T3> T;
   static inline QString toString(const T & data, const QString & format, int index)                     { verifyIndex(index); return ((index == 2) ? qx::cvt::to_string(boost::tuples::get<2>(data), format) : (index == 1) ? qx::cvt::to_string(boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::to_string(boost::tuples::get<0>(data), format) : qx::cvt::to_string(data, format))); }
   static inline qx_bool fromString(T & data, const QString & s, const QString & format, int index)      { verifyIndex(index); return ((index == 2) ? qx::cvt::from_string(s, boost::tuples::get<2>(data), format) : (index == 1) ? qx::cvt::from_string(s, boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::from_string(s, boost::tuples::get<0>(data), format) : qx::cvt::from_string(s, data, format))); }
   static inline QVariant toVariant(const T & data, const QString & format, int index)                   { verifyIndex(index); return ((index == 2) ? qx::cvt::to_variant(boost::tuples::get<2>(data), format) : (index == 1) ? qx::cvt::to_variant(boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::to_variant(boost::tuples::get<0>(data), format) : qx::cvt::to_variant(data, format))); }
   static inline qx_bool fromVariant(T & data, const QVariant & v, const QString & format, int index)    { verifyIndex(index); return ((index == 2) ? qx::cvt::from_variant(v, boost::tuples::get<2>(data), format) : (index == 1) ? qx::cvt::from_variant(v, boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::from_variant(v, boost::tuples::get<0>(data), format) : qx::cvt::from_variant(v, data, format))); }
private:
   static inline void verifyIndex(int index) { Q_UNUSED(index); qAssert((index >= -1) && (index < 3)); }
};

template <typename T1, typename T2, typename T3, typename T4>
struct QxStringCvt_WithIndex< boost::tuple<T1, T2, T3, T4> >
{
   typedef boost::tuple<T1, T2, T3, T4> T;
   static inline QString toString(const T & data, const QString & format, int index)                     { verifyIndex(index); return ((index == 3) ? qx::cvt::to_string(boost::tuples::get<3>(data), format) : (index == 2) ? qx::cvt::to_string(boost::tuples::get<2>(data), format) : (index == 1) ? qx::cvt::to_string(boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::to_string(boost::tuples::get<0>(data), format) : qx::cvt::to_string(data, format))); }
   static inline qx_bool fromString(T & data, const QString & s, const QString & format, int index)      { verifyIndex(index); return ((index == 3) ? qx::cvt::from_string(s, boost::tuples::get<3>(data), format) : (index == 2) ? qx::cvt::from_string(s, boost::tuples::get<2>(data), format) : (index == 1) ? qx::cvt::from_string(s, boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::from_string(s, boost::tuples::get<0>(data), format) : qx::cvt::from_string(s, data, format))); }
   static inline QVariant toVariant(const T & data, const QString & format, int index)                   { verifyIndex(index); return ((index == 3) ? qx::cvt::to_variant(boost::tuples::get<3>(data), format) : (index == 2) ? qx::cvt::to_variant(boost::tuples::get<2>(data), format) : (index == 1) ? qx::cvt::to_variant(boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::to_variant(boost::tuples::get<0>(data), format) : qx::cvt::to_variant(data, format))); }
   static inline qx_bool fromVariant(T & data, const QVariant & v, const QString & format, int index)    { verifyIndex(index); return ((index == 3) ? qx::cvt::from_variant(v, boost::tuples::get<3>(data), format) : (index == 2) ? qx::cvt::from_variant(v, boost::tuples::get<2>(data), format) : (index == 1) ? qx::cvt::from_variant(v, boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::from_variant(v, boost::tuples::get<0>(data), format) : qx::cvt::from_variant(v, data, format))); }
private:
   static inline void verifyIndex(int index) { Q_UNUSED(index); qAssert((index >= -1) && (index < 4)); }
};

template <typename T1, typename T2, typename T3, typename T4, typename T5>
struct QxStringCvt_WithIndex< boost::tuple<T1, T2, T3, T4, T5> >
{
   typedef boost::tuple<T1, T2, T3, T4, T5> T;
   static inline QString toString(const T & data, const QString & format, int index)                     { verifyIndex(index); return ((index == 4) ? qx::cvt::to_string(boost::tuples::get<4>(data), format) : (index == 3) ? qx::cvt::to_string(boost::tuples::get<3>(data), format) : (index == 2) ? qx::cvt::to_string(boost::tuples::get<2>(data), format) : (index == 1) ? qx::cvt::to_string(boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::to_string(boost::tuples::get<0>(data), format) : qx::cvt::to_string(data, format))); }
   static inline qx_bool fromString(T & data, const QString & s, const QString & format, int index)      { verifyIndex(index); return ((index == 4) ? qx::cvt::from_string(s, boost::tuples::get<4>(data), format) : (index == 3) ? qx::cvt::from_string(s, boost::tuples::get<3>(data), format) : (index == 2) ? qx::cvt::from_string(s, boost::tuples::get<2>(data), format) : (index == 1) ? qx::cvt::from_string(s, boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::from_string(s, boost::tuples::get<0>(data), format) : qx::cvt::from_string(s, data, format))); }
   static inline QVariant toVariant(const T & data, const QString & format, int index)                   { verifyIndex(index); return ((index == 4) ? qx::cvt::to_variant(boost::tuples::get<4>(data), format) : (index == 3) ? qx::cvt::to_variant(boost::tuples::get<3>(data), format) : (index == 2) ? qx::cvt::to_variant(boost::tuples::get<2>(data), format) : (index == 1) ? qx::cvt::to_variant(boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::to_variant(boost::tuples::get<0>(data), format) : qx::cvt::to_variant(data, format))); }
   static inline qx_bool fromVariant(T & data, const QVariant & v, const QString & format, int index)    { verifyIndex(index); return ((index == 4) ? qx::cvt::from_variant(v, boost::tuples::get<4>(data), format) : (index == 3) ? qx::cvt::from_variant(v, boost::tuples::get<3>(data), format) : (index == 2) ? qx::cvt::from_variant(v, boost::tuples::get<2>(data), format) : (index == 1) ? qx::cvt::from_variant(v, boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::from_variant(v, boost::tuples::get<0>(data), format) : qx::cvt::from_variant(v, data, format))); }
private:
   static inline void verifyIndex(int index) { Q_UNUSED(index); qAssert((index >= -1) && (index < 5)); }
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct QxStringCvt_WithIndex< boost::tuple<T1, T2, T3, T4, T5, T6> >
{
   typedef boost::tuple<T1, T2, T3, T4, T5, T6> T;
   static inline QString toString(const T & data, const QString & format, int index)                     { verifyIndex(index); return ((index == 5) ? qx::cvt::to_string(boost::tuples::get<5>(data), format) : (index == 4) ? qx::cvt::to_string(boost::tuples::get<4>(data), format) : (index == 3) ? qx::cvt::to_string(boost::tuples::get<3>(data), format) : (index == 2) ? qx::cvt::to_string(boost::tuples::get<2>(data), format) : (index == 1) ? qx::cvt::to_string(boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::to_string(boost::tuples::get<0>(data), format) : qx::cvt::to_string(data, format))); }
   static inline qx_bool fromString(T & data, const QString & s, const QString & format, int index)      { verifyIndex(index); return ((index == 5) ? qx::cvt::from_string(s, boost::tuples::get<5>(data), format) : (index == 4) ? qx::cvt::from_string(s, boost::tuples::get<4>(data), format) : (index == 3) ? qx::cvt::from_string(s, boost::tuples::get<3>(data), format) : (index == 2) ? qx::cvt::from_string(s, boost::tuples::get<2>(data), format) : (index == 1) ? qx::cvt::from_string(s, boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::from_string(s, boost::tuples::get<0>(data), format) : qx::cvt::from_string(s, data, format))); }
   static inline QVariant toVariant(const T & data, const QString & format, int index)                   { verifyIndex(index); return ((index == 5) ? qx::cvt::to_variant(boost::tuples::get<5>(data), format) : (index == 4) ? qx::cvt::to_variant(boost::tuples::get<4>(data), format) : (index == 3) ? qx::cvt::to_variant(boost::tuples::get<3>(data), format) : (index == 2) ? qx::cvt::to_variant(boost::tuples::get<2>(data), format) : (index == 1) ? qx::cvt::to_variant(boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::to_variant(boost::tuples::get<0>(data), format) : qx::cvt::to_variant(data, format))); }
   static inline qx_bool fromVariant(T & data, const QVariant & v, const QString & format, int index)    { verifyIndex(index); return ((index == 5) ? qx::cvt::from_variant(v, boost::tuples::get<5>(data), format) : (index == 4) ? qx::cvt::from_variant(v, boost::tuples::get<4>(data), format) : (index == 3) ? qx::cvt::from_variant(v, boost::tuples::get<3>(data), format) : (index == 2) ? qx::cvt::from_variant(v, boost::tuples::get<2>(data), format) : (index == 1) ? qx::cvt::from_variant(v, boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::from_variant(v, boost::tuples::get<0>(data), format) : qx::cvt::from_variant(v, data, format))); }
private:
   static inline void verifyIndex(int index) { Q_UNUSED(index); qAssert((index >= -1) && (index < 6)); }
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct QxStringCvt_WithIndex< boost::tuple<T1, T2, T3, T4, T5, T6, T7> >
{
   typedef boost::tuple<T1, T2, T3, T4, T5, T6, T7> T;
   static inline QString toString(const T & data, const QString & format, int index)                     { verifyIndex(index); return ((index == 6) ? qx::cvt::to_string(boost::tuples::get<6>(data), format) : (index == 5) ? qx::cvt::to_string(boost::tuples::get<5>(data), format) : (index == 4) ? qx::cvt::to_string(boost::tuples::get<4>(data), format) : (index == 3) ? qx::cvt::to_string(boost::tuples::get<3>(data), format) : (index == 2) ? qx::cvt::to_string(boost::tuples::get<2>(data), format) : (index == 1) ? qx::cvt::to_string(boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::to_string(boost::tuples::get<0>(data), format) : qx::cvt::to_string(data, format))); }
   static inline qx_bool fromString(T & data, const QString & s, const QString & format, int index)      { verifyIndex(index); return ((index == 6) ? qx::cvt::from_string(s, boost::tuples::get<6>(data), format) : (index == 5) ? qx::cvt::from_string(s, boost::tuples::get<5>(data), format) : (index == 4) ? qx::cvt::from_string(s, boost::tuples::get<4>(data), format) : (index == 3) ? qx::cvt::from_string(s, boost::tuples::get<3>(data), format) : (index == 2) ? qx::cvt::from_string(s, boost::tuples::get<2>(data), format) : (index == 1) ? qx::cvt::from_string(s, boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::from_string(s, boost::tuples::get<0>(data), format) : qx::cvt::from_string(s, data, format))); }
   static inline QVariant toVariant(const T & data, const QString & format, int index)                   { verifyIndex(index); return ((index == 6) ? qx::cvt::to_variant(boost::tuples::get<6>(data), format) : (index == 5) ? qx::cvt::to_variant(boost::tuples::get<5>(data), format) : (index == 4) ? qx::cvt::to_variant(boost::tuples::get<4>(data), format) : (index == 3) ? qx::cvt::to_variant(boost::tuples::get<3>(data), format) : (index == 2) ? qx::cvt::to_variant(boost::tuples::get<2>(data), format) : (index == 1) ? qx::cvt::to_variant(boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::to_variant(boost::tuples::get<0>(data), format) : qx::cvt::to_variant(data, format))); }
   static inline qx_bool fromVariant(T & data, const QVariant & v, const QString & format, int index)    { verifyIndex(index); return ((index == 6) ? qx::cvt::from_variant(v, boost::tuples::get<6>(data), format) : (index == 5) ? qx::cvt::from_variant(v, boost::tuples::get<5>(data), format) : (index == 4) ? qx::cvt::from_variant(v, boost::tuples::get<4>(data), format) : (index == 3) ? qx::cvt::from_variant(v, boost::tuples::get<3>(data), format) : (index == 2) ? qx::cvt::from_variant(v, boost::tuples::get<2>(data), format) : (index == 1) ? qx::cvt::from_variant(v, boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::from_variant(v, boost::tuples::get<0>(data), format) : qx::cvt::from_variant(v, data, format))); }
private:
   static inline void verifyIndex(int index) { Q_UNUSED(index); qAssert((index >= -1) && (index < 7)); }
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
struct QxStringCvt_WithIndex< boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8> >
{
   typedef boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8> T;
   static inline QString toString(const T & data, const QString & format, int index)                     { verifyIndex(index); return ((index == 7) ? qx::cvt::to_string(boost::tuples::get<7>(data), format) : (index == 6) ? qx::cvt::to_string(boost::tuples::get<6>(data), format) : (index == 5) ? qx::cvt::to_string(boost::tuples::get<5>(data), format) : (index == 4) ? qx::cvt::to_string(boost::tuples::get<4>(data), format) : (index == 3) ? qx::cvt::to_string(boost::tuples::get<3>(data), format) : (index == 2) ? qx::cvt::to_string(boost::tuples::get<2>(data), format) : (index == 1) ? qx::cvt::to_string(boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::to_string(boost::tuples::get<0>(data), format) : qx::cvt::to_string(data, format))); }
   static inline qx_bool fromString(T & data, const QString & s, const QString & format, int index)      { verifyIndex(index); return ((index == 7) ? qx::cvt::from_string(s, boost::tuples::get<7>(data), format) : (index == 6) ? qx::cvt::from_string(s, boost::tuples::get<6>(data), format) : (index == 5) ? qx::cvt::from_string(s, boost::tuples::get<5>(data), format) : (index == 4) ? qx::cvt::from_string(s, boost::tuples::get<4>(data), format) : (index == 3) ? qx::cvt::from_string(s, boost::tuples::get<3>(data), format) : (index == 2) ? qx::cvt::from_string(s, boost::tuples::get<2>(data), format) : (index == 1) ? qx::cvt::from_string(s, boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::from_string(s, boost::tuples::get<0>(data), format) : qx::cvt::from_string(s, data, format))); }
   static inline QVariant toVariant(const T & data, const QString & format, int index)                   { verifyIndex(index); return ((index == 7) ? qx::cvt::to_variant(boost::tuples::get<7>(data), format) : (index == 6) ? qx::cvt::to_variant(boost::tuples::get<6>(data), format) : (index == 5) ? qx::cvt::to_variant(boost::tuples::get<5>(data), format) : (index == 4) ? qx::cvt::to_variant(boost::tuples::get<4>(data), format) : (index == 3) ? qx::cvt::to_variant(boost::tuples::get<3>(data), format) : (index == 2) ? qx::cvt::to_variant(boost::tuples::get<2>(data), format) : (index == 1) ? qx::cvt::to_variant(boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::to_variant(boost::tuples::get<0>(data), format) : qx::cvt::to_variant(data, format))); }
   static inline qx_bool fromVariant(T & data, const QVariant & v, const QString & format, int index)    { verifyIndex(index); return ((index == 7) ? qx::cvt::from_variant(v, boost::tuples::get<7>(data), format) : (index == 6) ? qx::cvt::from_variant(v, boost::tuples::get<6>(data), format) : (index == 5) ? qx::cvt::from_variant(v, boost::tuples::get<5>(data), format) : (index == 4) ? qx::cvt::from_variant(v, boost::tuples::get<4>(data), format) : (index == 3) ? qx::cvt::from_variant(v, boost::tuples::get<3>(data), format) : (index == 2) ? qx::cvt::from_variant(v, boost::tuples::get<2>(data), format) : (index == 1) ? qx::cvt::from_variant(v, boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::from_variant(v, boost::tuples::get<0>(data), format) : qx::cvt::from_variant(v, data, format))); }
private:
   static inline void verifyIndex(int index) { Q_UNUSED(index); qAssert((index >= -1) && (index < 8)); }
};

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct QxStringCvt_WithIndex< boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> >
{
   typedef boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> T;
   static inline QString toString(const T & data, const QString & format, int index)                     { verifyIndex(index); return ((index == 8) ? qx::cvt::to_string(boost::tuples::get<8>(data), format) : (index == 7) ? qx::cvt::to_string(boost::tuples::get<7>(data), format) : (index == 6) ? qx::cvt::to_string(boost::tuples::get<6>(data), format) : (index == 5) ? qx::cvt::to_string(boost::tuples::get<5>(data), format) : (index == 4) ? qx::cvt::to_string(boost::tuples::get<4>(data), format) : (index == 3) ? qx::cvt::to_string(boost::tuples::get<3>(data), format) : (index == 2) ? qx::cvt::to_string(boost::tuples::get<2>(data), format) : (index == 1) ? qx::cvt::to_string(boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::to_string(boost::tuples::get<0>(data), format) : qx::cvt::to_string(data, format))); }
   static inline qx_bool fromString(T & data, const QString & s, const QString & format, int index)      { verifyIndex(index); return ((index == 8) ? qx::cvt::from_string(s, boost::tuples::get<8>(data), format) : (index == 7) ? qx::cvt::from_string(s, boost::tuples::get<7>(data), format) : (index == 6) ? qx::cvt::from_string(s, boost::tuples::get<6>(data), format) : (index == 5) ? qx::cvt::from_string(s, boost::tuples::get<5>(data), format) : (index == 4) ? qx::cvt::from_string(s, boost::tuples::get<4>(data), format) : (index == 3) ? qx::cvt::from_string(s, boost::tuples::get<3>(data), format) : (index == 2) ? qx::cvt::from_string(s, boost::tuples::get<2>(data), format) : (index == 1) ? qx::cvt::from_string(s, boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::from_string(s, boost::tuples::get<0>(data), format) : qx::cvt::from_string(s, data, format))); }
   static inline QVariant toVariant(const T & data, const QString & format, int index)                   { verifyIndex(index); return ((index == 8) ? qx::cvt::to_variant(boost::tuples::get<8>(data), format) : (index == 7) ? qx::cvt::to_variant(boost::tuples::get<7>(data), format) : (index == 6) ? qx::cvt::to_variant(boost::tuples::get<6>(data), format) : (index == 5) ? qx::cvt::to_variant(boost::tuples::get<5>(data), format) : (index == 4) ? qx::cvt::to_variant(boost::tuples::get<4>(data), format) : (index == 3) ? qx::cvt::to_variant(boost::tuples::get<3>(data), format) : (index == 2) ? qx::cvt::to_variant(boost::tuples::get<2>(data), format) : (index == 1) ? qx::cvt::to_variant(boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::to_variant(boost::tuples::get<0>(data), format) : qx::cvt::to_variant(data, format))); }
   static inline qx_bool fromVariant(T & data, const QVariant & v, const QString & format, int index)    { verifyIndex(index); return ((index == 8) ? qx::cvt::from_variant(v, boost::tuples::get<8>(data), format) : (index == 7) ? qx::cvt::from_variant(v, boost::tuples::get<7>(data), format) : (index == 6) ? qx::cvt::from_variant(v, boost::tuples::get<6>(data), format) : (index == 5) ? qx::cvt::from_variant(v, boost::tuples::get<5>(data), format) : (index == 4) ? qx::cvt::from_variant(v, boost::tuples::get<4>(data), format) : (index == 3) ? qx::cvt::from_variant(v, boost::tuples::get<3>(data), format) : (index == 2) ? qx::cvt::from_variant(v, boost::tuples::get<2>(data), format) : (index == 1) ? qx::cvt::from_variant(v, boost::tuples::get<1>(data), format) : ((index == 0) ? qx::cvt::from_variant(v, boost::tuples::get<0>(data), format) : qx::cvt::from_variant(v, data, format))); }
private:
   static inline void verifyIndex(int index) { Q_UNUSED(index); qAssert((index >= -1) && (index < 9)); }
};

} // namespace detail
} // namespace cvt
} // namespace qx
