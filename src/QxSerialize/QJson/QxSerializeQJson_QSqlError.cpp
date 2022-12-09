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

#include <QxPrecompiled.h>

#ifndef _QX_NO_JSON

#include <QxSerialize/QJson/QxSerializeQJson_QSqlError.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace cvt {
namespace detail {

QJsonValue QxConvert_ToJson_Helper(const QSqlError & t, const QString & format)
{
   Q_UNUSED(format);
   QJsonArray arr;
   arr.append(QJsonValue(t.databaseText()));
   arr.append(QJsonValue(t.driverText()));
#if (QT_VERSION >= 0x050300)
   arr.append(QJsonValue(t.nativeErrorCode()));
#else // (QT_VERSION >= 0x050300)
   arr.append(QJsonValue(t.number()));
#endif // (QT_VERSION >= 0x050300)
   arr.append(QJsonValue(static_cast<int>(t.type())));
   return QJsonValue(arr);
}

qx_bool QxConvert_FromJson_Helper(const QJsonValue & j, QSqlError & t, const QString & format)
{
   Q_UNUSED(format); t = QSqlError();
   if (! j.isArray()) { return qx_bool(true); }
   QJsonArray arr = j.toArray();
#if (QT_VERSION >= 0x050300)
   t = QSqlError(arr.at(1).toString(), arr.at(0).toString(), static_cast<QSqlError::ErrorType>(qRound(arr.at(3).toDouble())), arr.at(2).toString());
#else // (QT_VERSION >= 0x050300)
   t.setDatabaseText(arr.at(0).toString());
   t.setDriverText(arr.at(1).toString());
   t.setNumber(qRound(arr.at(2).toDouble()));
   t.setType(static_cast<QSqlError::ErrorType>(qRound(arr.at(3).toDouble())));
#endif // (QT_VERSION >= 0x050300)
   return qx_bool(true);
}

} // namespace detail
} // namespace cvt
} // namespace qx

#endif // _QX_NO_JSON
