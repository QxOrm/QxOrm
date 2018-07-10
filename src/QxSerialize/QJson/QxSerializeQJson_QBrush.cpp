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

#include <QxSerialize/QJson/QxSerializeQJson_QBrush.h>
#include <QxSerialize/QJson/QxSerializeQJson_QColor.h>
#include <QxSerialize/QJson/QxSerializeQJson_QPixmap.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace cvt {
namespace detail {

QJsonValue QxConvert_ToJson_Helper(const QBrush & t, const QString & format)
{
   QJsonObject obj;
   int iStyle = static_cast<int>(t.style());    obj.insert("style", qx::cvt::to_json(iStyle, format));
   QColor color(t.color());                     obj.insert("color", qx::cvt::to_json(color, format));
   QPixmap texture(t.texture());                obj.insert("texture", qx::cvt::to_json(texture, format));
   return QJsonValue(obj);
}

qx_bool QxConvert_FromJson_Helper(const QJsonValue & j, QBrush & t, const QString & format)
{
   t = QBrush();
   if (! j.isObject()) { return qx_bool(true); }
   QJsonObject obj = j.toObject(); int iStyle = 0; QColor color; QPixmap texture;
   qx::cvt::from_json(obj.value("style"), iStyle, format);
   qx::cvt::from_json(obj.value("color"), color, format);
   qx::cvt::from_json(obj.value("texture"), texture, format);
   t.setStyle(static_cast<Qt::BrushStyle>(iStyle));
   ((iStyle == Qt::TexturePattern) ? t.setTexture(texture) : t.setColor(color));
   return qx_bool(true);
}

} // namespace detail
} // namespace cvt
} // namespace qx

#endif // _QX_ENABLE_QT_GUI
#endif // _QX_NO_JSON
