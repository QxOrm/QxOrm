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

#if (QT_VERSION < 0x060000)
#ifndef _QX_NO_JSON
#ifdef _QX_ENABLE_QT_GUI
#ifndef _QX_SERIALIZE_QJSON_QMATRIX_H_
#define _QX_SERIALIZE_QJSON_QMATRIX_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSerializeQJson_QMatrix.h
 * \author Lionel Marty
 * \ingroup QxSerialize
 * \brief Provide a Qt QJson serialization method (save/load) for type QMatrix
 */

#include <QtCore/qjsonvalue.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qjsonarray.h>

#include <QtGui/qmatrix.h>

#include <QxConvert/QxConvert.h>
#include <QxConvert/QxConvert_Impl.h>

namespace qx {
namespace cvt {
namespace detail {

QX_DLL_EXPORT QJsonValue QxConvert_ToJson_Helper(const QMatrix & t, const QString & format) QX_USED;
QX_DLL_EXPORT qx_bool QxConvert_FromJson_Helper(const QJsonValue & j, QMatrix & t, const QString & format) QX_USED;

template <>
struct QxConvert_ToJson< QMatrix >
{
   static inline QJsonValue toJson(const QMatrix & t, const QString & format)
   { return QxConvert_ToJson_Helper(t, format); }
};

template <>
struct QxConvert_FromJson< QMatrix >
{
   static inline qx_bool fromJson(const QJsonValue & j, QMatrix & t, const QString & format)
   { return QxConvert_FromJson_Helper(j, t, format); }
};

} // namespace detail
} // namespace cvt
} // namespace qx

#endif // _QX_SERIALIZE_QJSON_QMATRIX_H_
#endif // _QX_ENABLE_QT_GUI
#endif // _QX_NO_JSON
#endif // (QT_VERSION < 0x060000)
