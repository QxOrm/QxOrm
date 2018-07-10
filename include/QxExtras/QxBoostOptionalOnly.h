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

#ifndef _QX_ENABLE_BOOST
#ifndef _QX_BOOST_OPTIONAL_ONLY_H_
#define _QX_BOOST_OPTIONAL_ONLY_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxBoostOptionalOnly.h
 * \author Lionel Marty
 * \ingroup QxExtras
 * \brief Provides support for boost::optional<T> to manage NULL values even if _QX_ENABLE_BOOST compilation option is not defined : so this header file enables just boost::optional feature and should be included just after <QxOrm.h> header file (ideally in a precompiled header)
 */

#include <boost/optional.hpp>
#include <boost/none.hpp>

#include <QxOrm.h>

#define _QX_ENABLE_BOOST
#include <QxSerialize/QDataStream/QxSerializeQDataStream_boost_optional.h>
#undef _QX_ENABLE_BOOST

#include <QxTraits/construct_null_qvariant.h>

QX_REGISTER_CLASS_NAME_TEMPLATE_1(boost::optional)

namespace qx {
namespace trait {

template <typename T>
struct get_sql_type< boost::optional<T> >
{ static inline const char * get() { return qx::trait::get_sql_type<T>::get(); } };

} // namespace trait
} // namespace qx

namespace qx {
namespace cvt {
namespace detail {

#ifndef _QX_NO_JSON

template <typename T> struct QxConvert_ToJson< boost::optional<T> > {
static inline QJsonValue toJson(const boost::optional<T> & t, const QString & format)
{ if (t) { return qx::cvt::to_json((* t), format); }; return QJsonValue(); } };

template <typename T> struct QxConvert_FromJson< boost::optional<T> > {
static inline qx_bool fromJson(const QJsonValue & j, boost::optional<T> & t, const QString & format)
{
   if (j.isNull()) { t = boost::none; return qx_bool(true); }
   else if (! t) { t = T(); }
   return qx::cvt::from_json(j, (* t), format);
} };

#endif // _QX_NO_JSON

template <typename T> struct QxConvert_ToString< boost::optional<T> > {
static inline QString toString(const boost::optional<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ if (t) { return qx::cvt::to_string((* t), format, index, ctx); }; return QString(); } };

template <typename T> struct QxConvert_FromString< boost::optional<T> > {
static inline qx_bool fromString(const QString & s, boost::optional<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ if (! t) { t = T(); }; return qx::cvt::from_string(s, (* t), format, index, ctx); } };

template <typename T> struct QxConvert_ToVariant< boost::optional<T> > {
static inline QVariant toVariant(const boost::optional<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ if (t) { return qx::cvt::to_variant((* t), format, index, ctx); }; return qx::trait::construct_null_qvariant<T>::get(); } };

template <typename T> struct QxConvert_FromVariant< boost::optional<T> > {
static inline qx_bool fromVariant(const QVariant & v, boost::optional<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{
   if (v.isNull()) { t = boost::none; return qx_bool(true); }
   else if (! t) { t = T(); }
   return qx::cvt::from_variant(v, (* t), format, index, ctx);
} };

} // namespace detail
} // namespace cvt
} // namespace qx

#endif // _QX_BOOST_OPTIONAL_ONLY_H_
#endif // _QX_ENABLE_BOOST
