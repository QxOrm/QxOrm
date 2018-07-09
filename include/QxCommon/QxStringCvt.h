/****************************************************************************
**
** Copyright (C) 2010 QxOrm France and/or its subsidiary(-ies)
** Contact: QxOrm France Information (contact@qxorm.com)
**
** This file is part of the QxOrm library
**
** Commercial Usage
** Licensees holding valid QxOrm Commercial licenses may use this file in
** accordance with the QxOrm Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and QxOrm France
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file 'license.gpl3.txt' included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html
**
** If you are unsure which license is appropriate for your use, please
** contact the support department at support@qxorm.com
**
****************************************************************************/

#ifndef _QX_STRING_CVT_H_
#define _QX_STRING_CVT_H_

#ifdef _MSC_VER
#pragma once
#endif

#include "../../include/QxCommon/QxBool.h"

namespace qx {
namespace cvt {
namespace detail {

template <typename T> struct QxStringCvt_ToString;
template <typename T> struct QxStringCvt_FromString;
template <typename T> struct QxStringCvt_ToVariant;
template <typename T> struct QxStringCvt_FromVariant;

} // namespace detail

template <typename T> inline QString to_string(const T & t, const QString & format)                   { return qx::cvt::detail::QxStringCvt_ToString<T>::toString(t, format); }
template <typename T> inline qx_bool from_string(const QString & s, T & t, const QString & format)    { return qx::cvt::detail::QxStringCvt_FromString<T>::fromString(s, t, format); }
template <typename T> inline QVariant to_variant(const T & t, const QString & format)                 { return qx::cvt::detail::QxStringCvt_ToVariant<T>::toVariant(t, format); }
template <typename T> inline qx_bool from_variant(const QVariant & v, T & t, const QString & format)  { return qx::cvt::detail::QxStringCvt_FromVariant<T>::fromVariant(v, t, format); }

template <typename T> inline QString to_string(const T & t)                   { return qx::cvt::detail::QxStringCvt_ToString<T>::toString(t, ""); }
template <typename T> inline qx_bool from_string(const QString & s, T & t)    { return qx::cvt::detail::QxStringCvt_FromString<T>::fromString(s, t, ""); }
template <typename T> inline QVariant to_variant(const T & t)                 { return qx::cvt::detail::QxStringCvt_ToVariant<T>::toVariant(t, ""); }
template <typename T> inline qx_bool from_variant(const QVariant & v, T & t)  { return qx::cvt::detail::QxStringCvt_FromVariant<T>::fromVariant(v, t, ""); }

} // namespace cvt
} // namespace qx

#endif // _QX_STRING_CVT_H_
