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

#include <QxPrecompiled.h>

#ifndef _QX_NO_JSON

#include <QxSerialize/QJson/QxSerializeQJson_QPoint.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace cvt {
namespace detail {

QJsonValue QxConvert_ToJson_Helper(const QPoint & t, const QString & format)
{
   Q_UNUSED(format);
   QJsonArray arr;
   arr.append(QJsonValue(t.x()));
   arr.append(QJsonValue(t.y()));
   return QJsonValue(arr);
}

qx_bool QxConvert_FromJson_Helper(const QJsonValue & j, QPoint & t, const QString & format)
{
   Q_UNUSED(format); t = QPoint();
   if (! j.isArray()) { return qx_bool(true); }
   QJsonArray arr = j.toArray();
   t.setX(qRound(arr.at(0).toDouble()));
   t.setY(qRound(arr.at(1).toDouble()));
   return qx_bool(true);
}

} // namespace detail
} // namespace cvt
} // namespace qx

#endif // _QX_NO_JSON
