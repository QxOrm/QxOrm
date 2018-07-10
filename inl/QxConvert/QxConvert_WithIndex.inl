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
struct QxConvert_WithIndex_ToString
{ static inline QString toString(const T & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { return qx::cvt::detail::QxConvert_ToString<T>::toString(data, format, index, ctx); } };

template <typename T>
struct QxConvert_WithIndex_FromString
{ static inline qx_bool fromString(T & data, const QString & s, const QString & format, int index, qx::cvt::context::ctx_type ctx) { return qx::cvt::detail::QxConvert_FromString<T>::fromString(s, data, format, index, ctx); } };

template <typename T>
struct QxConvert_WithIndex_ToVariant
{ static inline QVariant toVariant(const T & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { return qx::cvt::detail::QxConvert_ToVariant<T>::toVariant(data, format, index, ctx); } };

template <typename T>
struct QxConvert_WithIndex_FromVariant
{ static inline qx_bool fromVariant(T & data, const QVariant & v, const QString & format, int index, qx::cvt::context::ctx_type ctx) { return qx::cvt::detail::QxConvert_FromVariant<T>::fromVariant(v, data, format, index, ctx); } };

template <typename T1, typename T2>
struct QxConvert_WithIndex_ToString< std::pair<T1, T2> >
{ static inline QString toString(const std::pair<T1, T2> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 2)); return ((index == 1) ? qx::cvt::to_string(data.second, format, -1, ctx) : ((index == 0) ? qx::cvt::to_string(data.first, format, -1, ctx) : qx::cvt::detail::QxConvert_ToString< std::pair<T1, T2> >::toString(data, format, -1, ctx))); } };

template <typename T1, typename T2>
struct QxConvert_WithIndex_FromString< std::pair<T1, T2> >
{ static inline qx_bool fromString(std::pair<T1, T2> & data, const QString & s, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 2)); return ((index == 1) ? qx::cvt::from_string(s, data.second, format, -1, ctx) : ((index == 0) ? qx::cvt::from_string(s, data.first, format, -1, ctx) : qx::cvt::detail::QxConvert_FromString< std::pair<T1, T2> >::fromString(s, data, format, -1, ctx))); } };

template <typename T1, typename T2>
struct QxConvert_WithIndex_ToVariant< std::pair<T1, T2> >
{ static inline QVariant toVariant(const std::pair<T1, T2> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 2)); return ((index == 1) ? qx::cvt::to_variant(data.second, format, -1, ctx) : ((index == 0) ? qx::cvt::to_variant(data.first, format, -1, ctx) : qx::cvt::detail::QxConvert_ToVariant< std::pair<T1, T2> >::toVariant(data, format, -1, ctx))); } };

template <typename T1, typename T2>
struct QxConvert_WithIndex_FromVariant< std::pair<T1, T2> >
{ static inline qx_bool fromVariant(std::pair<T1, T2> & data, const QVariant & v, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 2)); return ((index == 1) ? qx::cvt::from_variant(v, data.second, format, -1, ctx) : ((index == 0) ? qx::cvt::from_variant(v, data.first, format, -1, ctx) : qx::cvt::detail::QxConvert_FromVariant< std::pair<T1, T2> >::fromVariant(v, data, format, -1, ctx))); } };

template <typename T1, typename T2>
struct QxConvert_WithIndex_ToString< QPair<T1, T2> >
{ static inline QString toString(const QPair<T1, T2> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 2)); return ((index == 1) ? qx::cvt::to_string(data.second, format, -1, ctx) : ((index == 0) ? qx::cvt::to_string(data.first, format, -1, ctx) : qx::cvt::detail::QxConvert_ToString< QPair<T1, T2> >::toString(data, format, -1, ctx))); } };

template <typename T1, typename T2>
struct QxConvert_WithIndex_FromString< QPair<T1, T2> >
{ static inline qx_bool fromString(QPair<T1, T2> & data, const QString & s, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 2)); return ((index == 1) ? qx::cvt::from_string(s, data.second, format, -1, ctx) : ((index == 0) ? qx::cvt::from_string(s, data.first, format, -1, ctx) : qx::cvt::detail::QxConvert_FromString< QPair<T1, T2> >::fromString(s, data, format, -1, ctx))); } };

template <typename T1, typename T2>
struct QxConvert_WithIndex_ToVariant< QPair<T1, T2> >
{ static inline QVariant toVariant(const QPair<T1, T2> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 2)); return ((index == 1) ? qx::cvt::to_variant(data.second, format, -1, ctx) : ((index == 0) ? qx::cvt::to_variant(data.first, format, -1, ctx) : qx::cvt::detail::QxConvert_ToVariant< QPair<T1, T2> >::toVariant(data, format, -1, ctx))); } };

template <typename T1, typename T2>
struct QxConvert_WithIndex_FromVariant< QPair<T1, T2> >
{ static inline qx_bool fromVariant(QPair<T1, T2> & data, const QVariant & v, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 2)); return ((index == 1) ? qx::cvt::from_variant(v, data.second, format, -1, ctx) : ((index == 0) ? qx::cvt::from_variant(v, data.first, format, -1, ctx) : qx::cvt::detail::QxConvert_FromVariant< QPair<T1, T2> >::fromVariant(v, data, format, -1, ctx))); } };

template <typename T1, typename T2>
struct QxConvert_WithIndex_ToString< boost::tuple<T1, T2> >
{ static inline QString toString(const boost::tuple<T1, T2> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 2)); return ((index == 1) ? qx::cvt::to_string(boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_string(boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToString< boost::tuple<T1, T2> >::toString(data, format, -1, ctx))); } };

template <typename T1, typename T2>
struct QxConvert_WithIndex_FromString< boost::tuple<T1, T2> >
{ static inline qx_bool fromString(boost::tuple<T1, T2> & data, const QString & s, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 2)); return ((index == 1) ? qx::cvt::from_string(s, boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_string(s, boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromString< boost::tuple<T1, T2> >::fromString(s, data, format, -1, ctx))); } };

template <typename T1, typename T2>
struct QxConvert_WithIndex_ToVariant< boost::tuple<T1, T2> >
{ static inline QVariant toVariant(const boost::tuple<T1, T2> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 2)); return ((index == 1) ? qx::cvt::to_variant(boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_variant(boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToVariant< boost::tuple<T1, T2> >::toVariant(data, format, -1, ctx))); } };

template <typename T1, typename T2>
struct QxConvert_WithIndex_FromVariant< boost::tuple<T1, T2> >
{ static inline qx_bool fromVariant(boost::tuple<T1, T2> & data, const QVariant & v, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 2)); return ((index == 1) ? qx::cvt::from_variant(v, boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_variant(v, boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromVariant< boost::tuple<T1, T2> >::fromVariant(v, data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3>
struct QxConvert_WithIndex_ToString< boost::tuple<T1, T2, T3> >
{ static inline QString toString(const boost::tuple<T1, T2, T3> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 3)); return ((index == 2) ? qx::cvt::to_string(boost::tuples::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::to_string(boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_string(boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToString< boost::tuple<T1, T2, T3> >::toString(data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3>
struct QxConvert_WithIndex_FromString< boost::tuple<T1, T2, T3> >
{ static inline qx_bool fromString(boost::tuple<T1, T2, T3> & data, const QString & s, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 3)); return ((index == 2) ? qx::cvt::from_string(s, boost::tuples::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::from_string(s, boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_string(s, boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromString< boost::tuple<T1, T2, T3> >::fromString(s, data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3>
struct QxConvert_WithIndex_ToVariant< boost::tuple<T1, T2, T3> >
{ static inline QVariant toVariant(const boost::tuple<T1, T2, T3> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 3)); return ((index == 2) ? qx::cvt::to_variant(boost::tuples::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::to_variant(boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_variant(boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToVariant< boost::tuple<T1, T2, T3> >::toVariant(data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3>
struct QxConvert_WithIndex_FromVariant< boost::tuple<T1, T2, T3> >
{ static inline qx_bool fromVariant(boost::tuple<T1, T2, T3> & data, const QVariant & v, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 3)); return ((index == 2) ? qx::cvt::from_variant(v, boost::tuples::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::from_variant(v, boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_variant(v, boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromVariant< boost::tuple<T1, T2, T3> >::fromVariant(v, data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4>
struct QxConvert_WithIndex_ToString< boost::tuple<T1, T2, T3, T4> >
{ static inline QString toString(const boost::tuple<T1, T2, T3, T4> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 4)); return ((index == 3) ? qx::cvt::to_string(boost::tuples::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::to_string(boost::tuples::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::to_string(boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_string(boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToString< boost::tuple<T1, T2, T3, T4> >::toString(data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4>
struct QxConvert_WithIndex_FromString< boost::tuple<T1, T2, T3, T4> >
{ static inline qx_bool fromString(boost::tuple<T1, T2, T3, T4> & data, const QString & s, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 4)); return ((index == 3) ? qx::cvt::from_string(s, boost::tuples::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::from_string(s, boost::tuples::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::from_string(s, boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_string(s, boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromString< boost::tuple<T1, T2, T3, T4> >::fromString(s, data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4>
struct QxConvert_WithIndex_ToVariant< boost::tuple<T1, T2, T3, T4> >
{ static inline QVariant toVariant(const boost::tuple<T1, T2, T3, T4> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 4)); return ((index == 3) ? qx::cvt::to_variant(boost::tuples::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::to_variant(boost::tuples::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::to_variant(boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_variant(boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToVariant< boost::tuple<T1, T2, T3, T4> >::toVariant(data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4>
struct QxConvert_WithIndex_FromVariant< boost::tuple<T1, T2, T3, T4> >
{ static inline qx_bool fromVariant(boost::tuple<T1, T2, T3, T4> & data, const QVariant & v, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 4)); return ((index == 3) ? qx::cvt::from_variant(v, boost::tuples::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::from_variant(v, boost::tuples::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::from_variant(v, boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_variant(v, boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromVariant< boost::tuple<T1, T2, T3, T4> >::fromVariant(v, data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5>
struct QxConvert_WithIndex_ToString< boost::tuple<T1, T2, T3, T4, T5> >
{ static inline QString toString(const boost::tuple<T1, T2, T3, T4, T5> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 5)); return ((index == 4) ? qx::cvt::to_string(boost::tuples::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::to_string(boost::tuples::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::to_string(boost::tuples::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::to_string(boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_string(boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToString< boost::tuple<T1, T2, T3, T4, T5> >::toString(data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5>
struct QxConvert_WithIndex_FromString< boost::tuple<T1, T2, T3, T4, T5> >
{ static inline qx_bool fromString(boost::tuple<T1, T2, T3, T4, T5> & data, const QString & s, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 5)); return ((index == 4) ? qx::cvt::from_string(s, boost::tuples::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::from_string(s, boost::tuples::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::from_string(s, boost::tuples::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::from_string(s, boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_string(s, boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromString< boost::tuple<T1, T2, T3, T4, T5> >::fromString(s, data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5>
struct QxConvert_WithIndex_ToVariant< boost::tuple<T1, T2, T3, T4, T5> >
{ static inline QVariant toVariant(const boost::tuple<T1, T2, T3, T4, T5> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 5)); return ((index == 4) ? qx::cvt::to_variant(boost::tuples::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::to_variant(boost::tuples::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::to_variant(boost::tuples::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::to_variant(boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_variant(boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToVariant< boost::tuple<T1, T2, T3, T4, T5> >::toVariant(data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5>
struct QxConvert_WithIndex_FromVariant< boost::tuple<T1, T2, T3, T4, T5> >
{ static inline qx_bool fromVariant(boost::tuple<T1, T2, T3, T4, T5> & data, const QVariant & v, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 5)); return ((index == 4) ? qx::cvt::from_variant(v, boost::tuples::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::from_variant(v, boost::tuples::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::from_variant(v, boost::tuples::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::from_variant(v, boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_variant(v, boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromVariant< boost::tuple<T1, T2, T3, T4, T5> >::fromVariant(v, data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct QxConvert_WithIndex_ToString< boost::tuple<T1, T2, T3, T4, T5, T6> >
{ static inline QString toString(const boost::tuple<T1, T2, T3, T4, T5, T6> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 6)); return ((index == 5) ? qx::cvt::to_string(boost::tuples::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::to_string(boost::tuples::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::to_string(boost::tuples::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::to_string(boost::tuples::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::to_string(boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_string(boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToString< boost::tuple<T1, T2, T3, T4, T5, T6> >::toString(data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct QxConvert_WithIndex_FromString< boost::tuple<T1, T2, T3, T4, T5, T6> >
{ static inline qx_bool fromString(boost::tuple<T1, T2, T3, T4, T5, T6> & data, const QString & s, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 6)); return ((index == 5) ? qx::cvt::from_string(s, boost::tuples::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::from_string(s, boost::tuples::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::from_string(s, boost::tuples::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::from_string(s, boost::tuples::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::from_string(s, boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_string(s, boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromString< boost::tuple<T1, T2, T3, T4, T5, T6> >::fromString(s, data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct QxConvert_WithIndex_ToVariant< boost::tuple<T1, T2, T3, T4, T5, T6> >
{ static inline QVariant toVariant(const boost::tuple<T1, T2, T3, T4, T5, T6> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 6)); return ((index == 5) ? qx::cvt::to_variant(boost::tuples::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::to_variant(boost::tuples::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::to_variant(boost::tuples::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::to_variant(boost::tuples::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::to_variant(boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_variant(boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToVariant< boost::tuple<T1, T2, T3, T4, T5, T6> >::toVariant(data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct QxConvert_WithIndex_FromVariant< boost::tuple<T1, T2, T3, T4, T5, T6> >
{ static inline qx_bool fromVariant(boost::tuple<T1, T2, T3, T4, T5, T6> & data, const QVariant & v, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 6)); return ((index == 5) ? qx::cvt::from_variant(v, boost::tuples::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::from_variant(v, boost::tuples::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::from_variant(v, boost::tuples::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::from_variant(v, boost::tuples::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::from_variant(v, boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_variant(v, boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromVariant< boost::tuple<T1, T2, T3, T4, T5, T6> >::fromVariant(v, data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct QxConvert_WithIndex_ToString< boost::tuple<T1, T2, T3, T4, T5, T6, T7> >
{ static inline QString toString(const boost::tuple<T1, T2, T3, T4, T5, T6, T7> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 7)); return ((index == 6) ? qx::cvt::to_string(boost::tuples::get<6>(data), format, -1, ctx) : (index == 5) ? qx::cvt::to_string(boost::tuples::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::to_string(boost::tuples::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::to_string(boost::tuples::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::to_string(boost::tuples::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::to_string(boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_string(boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToString< boost::tuple<T1, T2, T3, T4, T5, T6, T7> >::toString(data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct QxConvert_WithIndex_FromString< boost::tuple<T1, T2, T3, T4, T5, T6, T7> >
{ static inline qx_bool fromString(boost::tuple<T1, T2, T3, T4, T5, T6, T7> & data, const QString & s, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 7)); return ((index == 6) ? qx::cvt::from_string(s, boost::tuples::get<6>(data), format, -1, ctx) : (index == 5) ? qx::cvt::from_string(s, boost::tuples::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::from_string(s, boost::tuples::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::from_string(s, boost::tuples::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::from_string(s, boost::tuples::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::from_string(s, boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_string(s, boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromString< boost::tuple<T1, T2, T3, T4, T5, T6, T7> >::fromString(s, data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct QxConvert_WithIndex_ToVariant< boost::tuple<T1, T2, T3, T4, T5, T6, T7> >
{ static inline QVariant toVariant(const boost::tuple<T1, T2, T3, T4, T5, T6, T7> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 7)); return ((index == 6) ? qx::cvt::to_variant(boost::tuples::get<6>(data), format, -1, ctx) : (index == 5) ? qx::cvt::to_variant(boost::tuples::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::to_variant(boost::tuples::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::to_variant(boost::tuples::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::to_variant(boost::tuples::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::to_variant(boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_variant(boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToVariant< boost::tuple<T1, T2, T3, T4, T5, T6, T7> >::toVariant(data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct QxConvert_WithIndex_FromVariant< boost::tuple<T1, T2, T3, T4, T5, T6, T7> >
{ static inline qx_bool fromVariant(boost::tuple<T1, T2, T3, T4, T5, T6, T7> & data, const QVariant & v, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 7)); return ((index == 6) ? qx::cvt::from_variant(v, boost::tuples::get<6>(data), format, -1, ctx) : (index == 5) ? qx::cvt::from_variant(v, boost::tuples::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::from_variant(v, boost::tuples::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::from_variant(v, boost::tuples::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::from_variant(v, boost::tuples::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::from_variant(v, boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_variant(v, boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromVariant< boost::tuple<T1, T2, T3, T4, T5, T6, T7> >::fromVariant(v, data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
struct QxConvert_WithIndex_ToString< boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8> >
{ static inline QString toString(const boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 8)); return ((index == 7) ? qx::cvt::to_string(boost::tuples::get<7>(data), format, -1, ctx) : (index == 6) ? qx::cvt::to_string(boost::tuples::get<6>(data), format, -1, ctx) : (index == 5) ? qx::cvt::to_string(boost::tuples::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::to_string(boost::tuples::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::to_string(boost::tuples::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::to_string(boost::tuples::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::to_string(boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_string(boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToString< boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8> >::toString(data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
struct QxConvert_WithIndex_FromString< boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8> >
{ static inline qx_bool fromString(boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8> & data, const QString & s, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 8)); return ((index == 7) ? qx::cvt::from_string(s, boost::tuples::get<7>(data), format, -1, ctx) : (index == 6) ? qx::cvt::from_string(s, boost::tuples::get<6>(data), format, -1, ctx) : (index == 5) ? qx::cvt::from_string(s, boost::tuples::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::from_string(s, boost::tuples::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::from_string(s, boost::tuples::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::from_string(s, boost::tuples::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::from_string(s, boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_string(s, boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromString< boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8> >::fromString(s, data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
struct QxConvert_WithIndex_ToVariant< boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8> >
{ static inline QVariant toVariant(const boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 8)); return ((index == 7) ? qx::cvt::to_variant(boost::tuples::get<7>(data), format, -1, ctx) : (index == 6) ? qx::cvt::to_variant(boost::tuples::get<6>(data), format, -1, ctx) : (index == 5) ? qx::cvt::to_variant(boost::tuples::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::to_variant(boost::tuples::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::to_variant(boost::tuples::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::to_variant(boost::tuples::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::to_variant(boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_variant(boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToVariant< boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8> >::toVariant(data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
struct QxConvert_WithIndex_FromVariant< boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8> >
{ static inline qx_bool fromVariant(boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8> & data, const QVariant & v, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 8)); return ((index == 7) ? qx::cvt::from_variant(v, boost::tuples::get<7>(data), format, -1, ctx) : (index == 6) ? qx::cvt::from_variant(v, boost::tuples::get<6>(data), format, -1, ctx) : (index == 5) ? qx::cvt::from_variant(v, boost::tuples::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::from_variant(v, boost::tuples::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::from_variant(v, boost::tuples::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::from_variant(v, boost::tuples::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::from_variant(v, boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_variant(v, boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromVariant< boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8> >::fromVariant(v, data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct QxConvert_WithIndex_ToString< boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> >
{ static inline QString toString(const boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 9)); return ((index == 8) ? qx::cvt::to_string(boost::tuples::get<8>(data), format, -1, ctx) : (index == 7) ? qx::cvt::to_string(boost::tuples::get<7>(data), format, -1, ctx) : (index == 6) ? qx::cvt::to_string(boost::tuples::get<6>(data), format, -1, ctx) : (index == 5) ? qx::cvt::to_string(boost::tuples::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::to_string(boost::tuples::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::to_string(boost::tuples::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::to_string(boost::tuples::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::to_string(boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_string(boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToString< boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> >::toString(data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct QxConvert_WithIndex_FromString< boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> >
{ static inline qx_bool fromString(boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> & data, const QString & s, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 9)); return ((index == 8) ? qx::cvt::from_string(s, boost::tuples::get<8>(data), format, -1, ctx) : (index == 7) ? qx::cvt::from_string(s, boost::tuples::get<7>(data), format, -1, ctx) : (index == 6) ? qx::cvt::from_string(s, boost::tuples::get<6>(data), format, -1, ctx) : (index == 5) ? qx::cvt::from_string(s, boost::tuples::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::from_string(s, boost::tuples::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::from_string(s, boost::tuples::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::from_string(s, boost::tuples::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::from_string(s, boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_string(s, boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromString< boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> >::fromString(s, data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct QxConvert_WithIndex_ToVariant< boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> >
{ static inline QVariant toVariant(const boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 9)); return ((index == 8) ? qx::cvt::to_variant(boost::tuples::get<8>(data), format, -1, ctx) : (index == 7) ? qx::cvt::to_variant(boost::tuples::get<7>(data), format, -1, ctx) : (index == 6) ? qx::cvt::to_variant(boost::tuples::get<6>(data), format, -1, ctx) : (index == 5) ? qx::cvt::to_variant(boost::tuples::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::to_variant(boost::tuples::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::to_variant(boost::tuples::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::to_variant(boost::tuples::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::to_variant(boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_variant(boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToVariant< boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> >::toVariant(data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct QxConvert_WithIndex_FromVariant< boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> >
{ static inline qx_bool fromVariant(boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> & data, const QVariant & v, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 9)); return ((index == 8) ? qx::cvt::from_variant(v, boost::tuples::get<8>(data), format, -1, ctx) : (index == 7) ? qx::cvt::from_variant(v, boost::tuples::get<7>(data), format, -1, ctx) : (index == 6) ? qx::cvt::from_variant(v, boost::tuples::get<6>(data), format, -1, ctx) : (index == 5) ? qx::cvt::from_variant(v, boost::tuples::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::from_variant(v, boost::tuples::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::from_variant(v, boost::tuples::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::from_variant(v, boost::tuples::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::from_variant(v, boost::tuples::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_variant(v, boost::tuples::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromVariant< boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> >::fromVariant(v, data, format, -1, ctx))); } };

#ifdef _QX_CPP_11_TUPLE
#ifndef BOOST_NO_CXX11_HDR_TUPLE

template <typename T1, typename T2>
struct QxConvert_WithIndex_ToString< std::tuple<T1, T2> >
{ static inline QString toString(const std::tuple<T1, T2> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 2)); return ((index == 1) ? qx::cvt::to_string(std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_string(std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToString< std::tuple<T1, T2> >::toString(data, format, -1, ctx))); } };

template <typename T1, typename T2>
struct QxConvert_WithIndex_FromString< std::tuple<T1, T2> >
{ static inline qx_bool fromString(std::tuple<T1, T2> & data, const QString & s, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 2)); return ((index == 1) ? qx::cvt::from_string(s, std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_string(s, std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromString< std::tuple<T1, T2> >::fromString(s, data, format, -1, ctx))); } };

template <typename T1, typename T2>
struct QxConvert_WithIndex_ToVariant< std::tuple<T1, T2> >
{ static inline QVariant toVariant(const std::tuple<T1, T2> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 2)); return ((index == 1) ? qx::cvt::to_variant(std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_variant(std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToVariant< std::tuple<T1, T2> >::toVariant(data, format, -1, ctx))); } };

template <typename T1, typename T2>
struct QxConvert_WithIndex_FromVariant< std::tuple<T1, T2> >
{ static inline qx_bool fromVariant(std::tuple<T1, T2> & data, const QVariant & v, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 2)); return ((index == 1) ? qx::cvt::from_variant(v, std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_variant(v, std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromVariant< std::tuple<T1, T2> >::fromVariant(v, data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3>
struct QxConvert_WithIndex_ToString< std::tuple<T1, T2, T3> >
{ static inline QString toString(const std::tuple<T1, T2, T3> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 3)); return ((index == 2) ? qx::cvt::to_string(std::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::to_string(std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_string(std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToString< std::tuple<T1, T2, T3> >::toString(data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3>
struct QxConvert_WithIndex_FromString< std::tuple<T1, T2, T3> >
{ static inline qx_bool fromString(std::tuple<T1, T2, T3> & data, const QString & s, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 3)); return ((index == 2) ? qx::cvt::from_string(s, std::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::from_string(s, std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_string(s, std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromString< std::tuple<T1, T2, T3> >::fromString(s, data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3>
struct QxConvert_WithIndex_ToVariant< std::tuple<T1, T2, T3> >
{ static inline QVariant toVariant(const std::tuple<T1, T2, T3> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 3)); return ((index == 2) ? qx::cvt::to_variant(std::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::to_variant(std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_variant(std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToVariant< std::tuple<T1, T2, T3> >::toVariant(data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3>
struct QxConvert_WithIndex_FromVariant< std::tuple<T1, T2, T3> >
{ static inline qx_bool fromVariant(std::tuple<T1, T2, T3> & data, const QVariant & v, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 3)); return ((index == 2) ? qx::cvt::from_variant(v, std::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::from_variant(v, std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_variant(v, std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromVariant< std::tuple<T1, T2, T3> >::fromVariant(v, data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4>
struct QxConvert_WithIndex_ToString< std::tuple<T1, T2, T3, T4> >
{ static inline QString toString(const std::tuple<T1, T2, T3, T4> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 4)); return ((index == 3) ? qx::cvt::to_string(std::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::to_string(std::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::to_string(std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_string(std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToString< std::tuple<T1, T2, T3, T4> >::toString(data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4>
struct QxConvert_WithIndex_FromString< std::tuple<T1, T2, T3, T4> >
{ static inline qx_bool fromString(std::tuple<T1, T2, T3, T4> & data, const QString & s, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 4)); return ((index == 3) ? qx::cvt::from_string(s, std::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::from_string(s, std::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::from_string(s, std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_string(s, std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromString< std::tuple<T1, T2, T3, T4> >::fromString(s, data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4>
struct QxConvert_WithIndex_ToVariant< std::tuple<T1, T2, T3, T4> >
{ static inline QVariant toVariant(const std::tuple<T1, T2, T3, T4> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 4)); return ((index == 3) ? qx::cvt::to_variant(std::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::to_variant(std::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::to_variant(std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_variant(std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToVariant< std::tuple<T1, T2, T3, T4> >::toVariant(data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4>
struct QxConvert_WithIndex_FromVariant< std::tuple<T1, T2, T3, T4> >
{ static inline qx_bool fromVariant(std::tuple<T1, T2, T3, T4> & data, const QVariant & v, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 4)); return ((index == 3) ? qx::cvt::from_variant(v, std::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::from_variant(v, std::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::from_variant(v, std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_variant(v, std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromVariant< std::tuple<T1, T2, T3, T4> >::fromVariant(v, data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5>
struct QxConvert_WithIndex_ToString< std::tuple<T1, T2, T3, T4, T5> >
{ static inline QString toString(const std::tuple<T1, T2, T3, T4, T5> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 5)); return ((index == 4) ? qx::cvt::to_string(std::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::to_string(std::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::to_string(std::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::to_string(std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_string(std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToString< std::tuple<T1, T2, T3, T4, T5> >::toString(data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5>
struct QxConvert_WithIndex_FromString< std::tuple<T1, T2, T3, T4, T5> >
{ static inline qx_bool fromString(std::tuple<T1, T2, T3, T4, T5> & data, const QString & s, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 5)); return ((index == 4) ? qx::cvt::from_string(s, std::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::from_string(s, std::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::from_string(s, std::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::from_string(s, std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_string(s, std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromString< std::tuple<T1, T2, T3, T4, T5> >::fromString(s, data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5>
struct QxConvert_WithIndex_ToVariant< std::tuple<T1, T2, T3, T4, T5> >
{ static inline QVariant toVariant(const std::tuple<T1, T2, T3, T4, T5> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 5)); return ((index == 4) ? qx::cvt::to_variant(std::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::to_variant(std::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::to_variant(std::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::to_variant(std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_variant(std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToVariant< std::tuple<T1, T2, T3, T4, T5> >::toVariant(data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5>
struct QxConvert_WithIndex_FromVariant< std::tuple<T1, T2, T3, T4, T5> >
{ static inline qx_bool fromVariant(std::tuple<T1, T2, T3, T4, T5> & data, const QVariant & v, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 5)); return ((index == 4) ? qx::cvt::from_variant(v, std::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::from_variant(v, std::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::from_variant(v, std::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::from_variant(v, std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_variant(v, std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromVariant< std::tuple<T1, T2, T3, T4, T5> >::fromVariant(v, data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct QxConvert_WithIndex_ToString< std::tuple<T1, T2, T3, T4, T5, T6> >
{ static inline QString toString(const std::tuple<T1, T2, T3, T4, T5, T6> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 6)); return ((index == 5) ? qx::cvt::to_string(std::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::to_string(std::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::to_string(std::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::to_string(std::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::to_string(std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_string(std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToString< std::tuple<T1, T2, T3, T4, T5, T6> >::toString(data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct QxConvert_WithIndex_FromString< std::tuple<T1, T2, T3, T4, T5, T6> >
{ static inline qx_bool fromString(std::tuple<T1, T2, T3, T4, T5, T6> & data, const QString & s, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 6)); return ((index == 5) ? qx::cvt::from_string(s, std::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::from_string(s, std::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::from_string(s, std::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::from_string(s, std::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::from_string(s, std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_string(s, std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromString< std::tuple<T1, T2, T3, T4, T5, T6> >::fromString(s, data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct QxConvert_WithIndex_ToVariant< std::tuple<T1, T2, T3, T4, T5, T6> >
{ static inline QVariant toVariant(const std::tuple<T1, T2, T3, T4, T5, T6> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 6)); return ((index == 5) ? qx::cvt::to_variant(std::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::to_variant(std::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::to_variant(std::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::to_variant(std::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::to_variant(std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_variant(std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToVariant< std::tuple<T1, T2, T3, T4, T5, T6> >::toVariant(data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct QxConvert_WithIndex_FromVariant< std::tuple<T1, T2, T3, T4, T5, T6> >
{ static inline qx_bool fromVariant(std::tuple<T1, T2, T3, T4, T5, T6> & data, const QVariant & v, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 6)); return ((index == 5) ? qx::cvt::from_variant(v, std::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::from_variant(v, std::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::from_variant(v, std::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::from_variant(v, std::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::from_variant(v, std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_variant(v, std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromVariant< std::tuple<T1, T2, T3, T4, T5, T6> >::fromVariant(v, data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct QxConvert_WithIndex_ToString< std::tuple<T1, T2, T3, T4, T5, T6, T7> >
{ static inline QString toString(const std::tuple<T1, T2, T3, T4, T5, T6, T7> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 7)); return ((index == 6) ? qx::cvt::to_string(std::get<6>(data), format, -1, ctx) : (index == 5) ? qx::cvt::to_string(std::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::to_string(std::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::to_string(std::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::to_string(std::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::to_string(std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_string(std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToString< std::tuple<T1, T2, T3, T4, T5, T6, T7> >::toString(data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct QxConvert_WithIndex_FromString< std::tuple<T1, T2, T3, T4, T5, T6, T7> >
{ static inline qx_bool fromString(std::tuple<T1, T2, T3, T4, T5, T6, T7> & data, const QString & s, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 7)); return ((index == 6) ? qx::cvt::from_string(s, std::get<6>(data), format, -1, ctx) : (index == 5) ? qx::cvt::from_string(s, std::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::from_string(s, std::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::from_string(s, std::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::from_string(s, std::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::from_string(s, std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_string(s, std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromString< std::tuple<T1, T2, T3, T4, T5, T6, T7> >::fromString(s, data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct QxConvert_WithIndex_ToVariant< std::tuple<T1, T2, T3, T4, T5, T6, T7> >
{ static inline QVariant toVariant(const std::tuple<T1, T2, T3, T4, T5, T6, T7> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 7)); return ((index == 6) ? qx::cvt::to_variant(std::get<6>(data), format, -1, ctx) : (index == 5) ? qx::cvt::to_variant(std::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::to_variant(std::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::to_variant(std::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::to_variant(std::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::to_variant(std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_variant(std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToVariant< std::tuple<T1, T2, T3, T4, T5, T6, T7> >::toVariant(data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct QxConvert_WithIndex_FromVariant< std::tuple<T1, T2, T3, T4, T5, T6, T7> >
{ static inline qx_bool fromVariant(std::tuple<T1, T2, T3, T4, T5, T6, T7> & data, const QVariant & v, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 7)); return ((index == 6) ? qx::cvt::from_variant(v, std::get<6>(data), format, -1, ctx) : (index == 5) ? qx::cvt::from_variant(v, std::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::from_variant(v, std::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::from_variant(v, std::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::from_variant(v, std::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::from_variant(v, std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_variant(v, std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromVariant< std::tuple<T1, T2, T3, T4, T5, T6, T7> >::fromVariant(v, data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
struct QxConvert_WithIndex_ToString< std::tuple<T1, T2, T3, T4, T5, T6, T7, T8> >
{ static inline QString toString(const std::tuple<T1, T2, T3, T4, T5, T6, T7, T8> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 8)); return ((index == 7) ? qx::cvt::to_string(std::get<7>(data), format, -1, ctx) : (index == 6) ? qx::cvt::to_string(std::get<6>(data), format, -1, ctx) : (index == 5) ? qx::cvt::to_string(std::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::to_string(std::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::to_string(std::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::to_string(std::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::to_string(std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_string(std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToString< std::tuple<T1, T2, T3, T4, T5, T6, T7, T8> >::toString(data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
struct QxConvert_WithIndex_FromString< std::tuple<T1, T2, T3, T4, T5, T6, T7, T8> >
{ static inline qx_bool fromString(std::tuple<T1, T2, T3, T4, T5, T6, T7, T8> & data, const QString & s, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 8)); return ((index == 7) ? qx::cvt::from_string(s, std::get<7>(data), format, -1, ctx) : (index == 6) ? qx::cvt::from_string(s, std::get<6>(data), format, -1, ctx) : (index == 5) ? qx::cvt::from_string(s, std::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::from_string(s, std::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::from_string(s, std::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::from_string(s, std::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::from_string(s, std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_string(s, std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromString< std::tuple<T1, T2, T3, T4, T5, T6, T7, T8> >::fromString(s, data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
struct QxConvert_WithIndex_ToVariant< std::tuple<T1, T2, T3, T4, T5, T6, T7, T8> >
{ static inline QVariant toVariant(const std::tuple<T1, T2, T3, T4, T5, T6, T7, T8> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 8)); return ((index == 7) ? qx::cvt::to_variant(std::get<7>(data), format, -1, ctx) : (index == 6) ? qx::cvt::to_variant(std::get<6>(data), format, -1, ctx) : (index == 5) ? qx::cvt::to_variant(std::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::to_variant(std::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::to_variant(std::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::to_variant(std::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::to_variant(std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_variant(std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToVariant< std::tuple<T1, T2, T3, T4, T5, T6, T7, T8> >::toVariant(data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
struct QxConvert_WithIndex_FromVariant< std::tuple<T1, T2, T3, T4, T5, T6, T7, T8> >
{ static inline qx_bool fromVariant(std::tuple<T1, T2, T3, T4, T5, T6, T7, T8> & data, const QVariant & v, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 8)); return ((index == 7) ? qx::cvt::from_variant(v, std::get<7>(data), format, -1, ctx) : (index == 6) ? qx::cvt::from_variant(v, std::get<6>(data), format, -1, ctx) : (index == 5) ? qx::cvt::from_variant(v, std::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::from_variant(v, std::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::from_variant(v, std::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::from_variant(v, std::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::from_variant(v, std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_variant(v, std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromVariant< std::tuple<T1, T2, T3, T4, T5, T6, T7, T8> >::fromVariant(v, data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct QxConvert_WithIndex_ToString< std::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> >
{ static inline QString toString(const std::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 9)); return ((index == 8) ? qx::cvt::to_string(std::get<8>(data), format, -1, ctx) : (index == 7) ? qx::cvt::to_string(std::get<7>(data), format, -1, ctx) : (index == 6) ? qx::cvt::to_string(std::get<6>(data), format, -1, ctx) : (index == 5) ? qx::cvt::to_string(std::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::to_string(std::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::to_string(std::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::to_string(std::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::to_string(std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_string(std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToString< std::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> >::toString(data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct QxConvert_WithIndex_FromString< std::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> >
{ static inline qx_bool fromString(std::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> & data, const QString & s, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 9)); return ((index == 8) ? qx::cvt::from_string(s, std::get<8>(data), format, -1, ctx) : (index == 7) ? qx::cvt::from_string(s, std::get<7>(data), format, -1, ctx) : (index == 6) ? qx::cvt::from_string(s, std::get<6>(data), format, -1, ctx) : (index == 5) ? qx::cvt::from_string(s, std::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::from_string(s, std::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::from_string(s, std::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::from_string(s, std::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::from_string(s, std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_string(s, std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromString< std::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> >::fromString(s, data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct QxConvert_WithIndex_ToVariant< std::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> >
{ static inline QVariant toVariant(const std::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> & data, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 9)); return ((index == 8) ? qx::cvt::to_variant(std::get<8>(data), format, -1, ctx) : (index == 7) ? qx::cvt::to_variant(std::get<7>(data), format, -1, ctx) : (index == 6) ? qx::cvt::to_variant(std::get<6>(data), format, -1, ctx) : (index == 5) ? qx::cvt::to_variant(std::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::to_variant(std::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::to_variant(std::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::to_variant(std::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::to_variant(std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::to_variant(std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_ToVariant< std::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> >::toVariant(data, format, -1, ctx))); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct QxConvert_WithIndex_FromVariant< std::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> >
{ static inline qx_bool fromVariant(std::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> & data, const QVariant & v, const QString & format, int index, qx::cvt::context::ctx_type ctx) { qAssert((index >= -1) && (index < 9)); return ((index == 8) ? qx::cvt::from_variant(v, std::get<8>(data), format, -1, ctx) : (index == 7) ? qx::cvt::from_variant(v, std::get<7>(data), format, -1, ctx) : (index == 6) ? qx::cvt::from_variant(v, std::get<6>(data), format, -1, ctx) : (index == 5) ? qx::cvt::from_variant(v, std::get<5>(data), format, -1, ctx) : (index == 4) ? qx::cvt::from_variant(v, std::get<4>(data), format, -1, ctx) : (index == 3) ? qx::cvt::from_variant(v, std::get<3>(data), format, -1, ctx) : (index == 2) ? qx::cvt::from_variant(v, std::get<2>(data), format, -1, ctx) : (index == 1) ? qx::cvt::from_variant(v, std::get<1>(data), format, -1, ctx) : ((index == 0) ? qx::cvt::from_variant(v, std::get<0>(data), format, -1, ctx) : qx::cvt::detail::QxConvert_FromVariant< std::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> >::fromVariant(v, data, format, -1, ctx))); } };

#endif // BOOST_NO_CXX11_HDR_TUPLE
#endif // _QX_CPP_11_TUPLE

} // namespace detail
} // namespace cvt
} // namespace qx
