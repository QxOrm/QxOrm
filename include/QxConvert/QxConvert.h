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

#ifndef _QX_CONVERT_H_
#define _QX_CONVERT_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxConvert.h
 * \author Lionel Marty
 * \ingroup QxConvert
 * \brief qx::cvt : namespace to provide global functions to convert any kind of objects to/from QString and QVariant format
 */

#ifndef _QX_NO_JSON
#include <QtCore/qjsonvalue.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsondocument.h>
#endif // _QX_NO_JSON

#include <QxCommon/QxBool.h>

namespace qx {
namespace cvt {
namespace detail {

template <typename T> struct QxConvert_ToString;
template <typename T> struct QxConvert_FromString;
template <typename T> struct QxConvert_ToVariant;
template <typename T> struct QxConvert_FromVariant;
template <typename T> struct QxConvert_WithIndex_ToString;
template <typename T> struct QxConvert_WithIndex_FromString;
template <typename T> struct QxConvert_WithIndex_ToVariant;
template <typename T> struct QxConvert_WithIndex_FromVariant;

#ifndef _QX_NO_JSON
template <typename T> struct QxConvert_ToJson;
template <typename T> struct QxConvert_FromJson;
#endif // _QX_NO_JSON

} // namespace detail

struct context { enum ctx_type { e_no_context, e_database, e_serialize_registered }; };

template <typename T> inline QString to_string(const T & t, const QString & format = QString(), int index = -1, qx::cvt::context::ctx_type ctx = qx::cvt::context::e_no_context)                   { return qx::cvt::detail::QxConvert_WithIndex_ToString<T>::toString(t, format, index, ctx); }
template <typename T> inline qx_bool from_string(const QString & s, T & t, const QString & format = QString(), int index = -1, qx::cvt::context::ctx_type ctx = qx::cvt::context::e_no_context)    { return qx::cvt::detail::QxConvert_WithIndex_FromString<T>::fromString(t, s, format, index, ctx); }
template <typename T> inline QVariant to_variant(const T & t, const QString & format = QString(), int index = -1, qx::cvt::context::ctx_type ctx = qx::cvt::context::e_no_context)                 { return qx::cvt::detail::QxConvert_WithIndex_ToVariant<T>::toVariant(t, format, index, ctx); }
template <typename T> inline qx_bool from_variant(const QVariant & v, T & t, const QString & format = QString(), int index = -1, qx::cvt::context::ctx_type ctx = qx::cvt::context::e_no_context)  { return qx::cvt::detail::QxConvert_WithIndex_FromVariant<T>::fromVariant(t, v, format, index, ctx); }

#ifndef _QX_NO_JSON
template <typename T> inline QJsonValue to_json(const T & t, const QString & format = QString())                  { return qx::cvt::detail::QxConvert_ToJson<T>::toJson(t, format); }
template <typename T> inline qx_bool from_json(const QJsonValue & j, T & t, const QString & format = QString())   { return qx::cvt::detail::QxConvert_FromJson<T>::fromJson(j, t, format); }
#endif // _QX_NO_JSON

} // namespace cvt
} // namespace qx

#endif // _QX_CONVERT_H_
