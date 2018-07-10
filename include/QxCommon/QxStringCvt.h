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
