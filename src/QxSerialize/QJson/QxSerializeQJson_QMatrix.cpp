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
#ifdef _QX_ENABLE_QT_GUI

#include <QxSerialize/QJson/QxSerializeQJson_QMatrix.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace cvt {
namespace detail {

QJsonValue QxConvert_ToJson_Helper(const QMatrix & t, const QString & format)
{
   Q_UNUSED(format);
   QJsonArray arr;
   double m11(t.m11()), m12(t.m12()), m21(t.m21()), m22(t.m22()), dx(t.dx()), dy(t.dy());
   arr.append(QJsonValue(m11));
   arr.append(QJsonValue(m12));
   arr.append(QJsonValue(m21));
   arr.append(QJsonValue(m22));
   arr.append(QJsonValue(dx));
   arr.append(QJsonValue(dy));
   return QJsonValue(arr);
}

qx_bool QxConvert_FromJson_Helper(const QJsonValue & j, QMatrix & t, const QString & format)
{
   Q_UNUSED(format); t = QMatrix();
   if (! j.isArray()) { return qx_bool(true); }
   QJsonArray arr = j.toArray();
   double m11(arr.at(0).toDouble());
   double m12(arr.at(1).toDouble());
   double m21(arr.at(2).toDouble());
   double m22(arr.at(3).toDouble());
   double dx(arr.at(4).toDouble());
   double dy(arr.at(5).toDouble());
   t.setMatrix(m11, m12, m21, m22, dx, dy);
   return qx_bool(true);
}

} // namespace detail
} // namespace cvt
} // namespace qx

#endif // _QX_ENABLE_QT_GUI
#endif // _QX_NO_JSON
