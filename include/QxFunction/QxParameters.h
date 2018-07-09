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

#ifndef _QX_PARAMETERS_H_
#define _QX_PARAMETERS_H_

#ifdef _MSC_VER
#pragma once
#endif

#include "../../include/QxFunction/IxFunction.h"

namespace qx {
namespace function {
namespace detail {

template <class T, typename P>
inline qx_bool get_param_1(const T & params, P & p, const qx::IxFunction * qx_fct) { QX_FUNCTION_GET_PARAM_TYPE_ANY(1); }

template <class T, typename P>
inline qx_bool get_param_2(const T & params, P & p, const qx::IxFunction * qx_fct) { QX_FUNCTION_GET_PARAM_TYPE_ANY(2); }

template <class T, typename P>
inline qx_bool get_param_3(const T & params, P & p, const qx::IxFunction * qx_fct) { QX_FUNCTION_GET_PARAM_TYPE_ANY(3); }

template <class T, typename P>
inline qx_bool get_param_4(const T & params, P & p, const qx::IxFunction * qx_fct) { QX_FUNCTION_GET_PARAM_TYPE_ANY(4); }

template <class T, typename P>
inline qx_bool get_param_5(const T & params, P & p, const qx::IxFunction * qx_fct) { QX_FUNCTION_GET_PARAM_TYPE_ANY(5); }

template <class T, typename P>
inline qx_bool get_param_6(const T & params, P & p, const qx::IxFunction * qx_fct) { QX_FUNCTION_GET_PARAM_TYPE_ANY(6); }

template <class T, typename P>
inline qx_bool get_param_7(const T & params, P & p, const qx::IxFunction * qx_fct) { QX_FUNCTION_GET_PARAM_TYPE_ANY(7); }

template <class T, typename P>
inline qx_bool get_param_8(const T & params, P & p, const qx::IxFunction * qx_fct) { QX_FUNCTION_GET_PARAM_TYPE_ANY(8); }

template <class T, typename P>
inline qx_bool get_param_9(const T & params, P & p, const qx::IxFunction * qx_fct) { QX_FUNCTION_GET_PARAM_TYPE_ANY(9); }

template <typename P>
inline qx_bool get_param_1(const QString & params, P & p, const qx::IxFunction * qx_fct) { QX_FUNCTION_GET_PARAM_TYPE_STRING(1); }

template <typename P>
inline qx_bool get_param_2(const QString & params, P & p, const qx::IxFunction * qx_fct) { QX_FUNCTION_GET_PARAM_TYPE_STRING(2); }

template <typename P>
inline qx_bool get_param_3(const QString & params, P & p, const qx::IxFunction * qx_fct) { QX_FUNCTION_GET_PARAM_TYPE_STRING(3); }

template <typename P>
inline qx_bool get_param_4(const QString & params, P & p, const qx::IxFunction * qx_fct) { QX_FUNCTION_GET_PARAM_TYPE_STRING(4); }

template <typename P>
inline qx_bool get_param_5(const QString & params, P & p, const qx::IxFunction * qx_fct) { QX_FUNCTION_GET_PARAM_TYPE_STRING(5); }

template <typename P>
inline qx_bool get_param_6(const QString & params, P & p, const qx::IxFunction * qx_fct) { QX_FUNCTION_GET_PARAM_TYPE_STRING(6); }

template <typename P>
inline qx_bool get_param_7(const QString & params, P & p, const qx::IxFunction * qx_fct) { QX_FUNCTION_GET_PARAM_TYPE_STRING(7); }

template <typename P>
inline qx_bool get_param_8(const QString & params, P & p, const qx::IxFunction * qx_fct) { QX_FUNCTION_GET_PARAM_TYPE_STRING(8); }

template <typename P>
inline qx_bool get_param_9(const QString & params, P & p, const qx::IxFunction * qx_fct) { QX_FUNCTION_GET_PARAM_TYPE_STRING(9); }

template <>
inline qx_bool get_param_1(const QString & params, QString & p, const qx::IxFunction * qx_fct) { QX_FUNCTION_GET_PARAM_TYPE_STRING_TO_QSTRING(1); }

template <>
inline qx_bool get_param_2(const QString & params, QString & p, const qx::IxFunction * qx_fct) { QX_FUNCTION_GET_PARAM_TYPE_STRING_TO_QSTRING(2); }

template <>
inline qx_bool get_param_3(const QString & params, QString & p, const qx::IxFunction * qx_fct) { QX_FUNCTION_GET_PARAM_TYPE_STRING_TO_QSTRING(3); }

template <>
inline qx_bool get_param_4(const QString & params, QString & p, const qx::IxFunction * qx_fct) { QX_FUNCTION_GET_PARAM_TYPE_STRING_TO_QSTRING(4); }

template <>
inline qx_bool get_param_5(const QString & params, QString & p, const qx::IxFunction * qx_fct) { QX_FUNCTION_GET_PARAM_TYPE_STRING_TO_QSTRING(5); }

template <>
inline qx_bool get_param_6(const QString & params, QString & p, const qx::IxFunction * qx_fct) { QX_FUNCTION_GET_PARAM_TYPE_STRING_TO_QSTRING(6); }

template <>
inline qx_bool get_param_7(const QString & params, QString & p, const qx::IxFunction * qx_fct) { QX_FUNCTION_GET_PARAM_TYPE_STRING_TO_QSTRING(7); }

template <>
inline qx_bool get_param_8(const QString & params, QString & p, const qx::IxFunction * qx_fct) { QX_FUNCTION_GET_PARAM_TYPE_STRING_TO_QSTRING(8); }

template <>
inline qx_bool get_param_9(const QString & params, QString & p, const qx::IxFunction * qx_fct) { QX_FUNCTION_GET_PARAM_TYPE_STRING_TO_QSTRING(9); }

} // namespace detail
} // namespace function
} // namespace qx

#endif // _QX_PARAMETERS_H_
