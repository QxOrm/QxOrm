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

#include <QxSerialize/QJson/QxSerializeQJson_QxInvalidValue.h>
#include <QxSerialize/QJson/QxSerializeQJson_QHash.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace cvt {
namespace detail {

QJsonValue QxConvert_ToJson_Helper(const qx::QxInvalidValue & t, const QString & format)
{
   QJsonObject obj;
   obj.insert("message", t.m_sMessage);
   if (! t.m_sPropertyName.isEmpty()) { obj.insert("property_name", t.m_sPropertyName); }
   if (! t.m_sPath.isEmpty()) { obj.insert("path", t.m_sPath); }
   if ((t.m_lstPropertyBag) && (t.m_lstPropertyBag->count() > 0)) { obj.insert("property_bag", qx::cvt::to_json(t.m_lstPropertyBag, format)); }
   return obj;
}

qx_bool QxConvert_FromJson_Helper(const QJsonValue & j, qx::QxInvalidValue & t, const QString & format)
{
   t = qx::QxInvalidValue();

   if (j.isArray())
   {
      QJsonArray arr = j.toArray();
      t.m_sMessage = arr.at(0).toString();
      t.m_sPropertyName = arr.at(1).toString();
      t.m_sPath = arr.at(2).toString();
      qx::cvt::from_json(arr.at(3), t.m_lstPropertyBag, format);
   }
   else if (j.isObject())
   {
      QJsonObject obj = j.toObject();
      t.m_sMessage = obj.value("message").toString();
      t.m_sPropertyName = obj.value("property_name").toString();
      t.m_sPath = obj.value("path").toString();
      qx::cvt::from_json(obj.value("property_bag"), t.m_lstPropertyBag, format);
   }

   return qx_bool(true);
}

} // namespace detail
} // namespace cvt
} // namespace qx

#endif // _QX_NO_JSON
