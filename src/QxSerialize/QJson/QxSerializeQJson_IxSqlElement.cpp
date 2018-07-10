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

#include <QxSerialize/QJson/QxSerializeQJson_IxSqlElement.h>
#include <QxSerialize/QJson/QxSerializeQJson_QStringList.h>
#include <QxSerialize/QJson/QxSerializeQJson_QList.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace cvt {
namespace detail {

QJsonValue QxConvert_ToJson_Helper(const qx::dao::detail::IxSqlElement & t, const QString & format)
{
   QJsonObject obj;
   obj.insert("index", QJsonValue(t.m_iIndex));
   obj.insert("list_columns", qx::cvt::to_json(t.m_lstColumns, format));
   obj.insert("list_keys", qx::cvt::to_json(t.m_lstKeys, format));
   obj.insert("list_values", qx::cvt::to_json(t.m_lstValues, format));
   obj.insert("extra_settings", QJsonValue(t.getExtraSettings()));
   return QJsonValue(obj);
}

qx_bool QxConvert_FromJson_Helper(const QJsonValue & j, qx::dao::detail::IxSqlElement & t, const QString & format)
{
   if (! j.isObject()) { return qx_bool(true); }
   QJsonObject obj = j.toObject();
   t.m_iIndex = qRound(obj.value("index").toDouble());
   qx::cvt::from_json(obj.value("list_columns"), t.m_lstColumns, format);
   qx::cvt::from_json(obj.value("list_keys"), t.m_lstKeys, format);
   qx::cvt::from_json(obj.value("list_values"), t.m_lstValues, format);
   t.setExtraSettings(obj.value("extra_settings").toString());
   return qx_bool(true);
}

} // namespace detail
} // namespace cvt
} // namespace qx

#endif // _QX_NO_JSON
