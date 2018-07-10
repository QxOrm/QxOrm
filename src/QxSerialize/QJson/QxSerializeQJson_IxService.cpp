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
#ifdef _QX_ENABLE_QT_NETWORK

#include <QxSerialize/QJson/QxSerializeQJson_IxService.h>

#include <QxFactory/QxFactoryX.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace cvt {
namespace detail {

QJsonValue QxConvert_ToJson_Helper(const qx::service::IxService & t, const QString & format)
{
   QJsonObject obj;
   obj.insert("service_name", QJsonValue(t.m_sServiceName));
   obj.insert("service_method", QJsonValue(t.m_sServiceMethodName));
   obj.insert("message_return", qx::cvt::to_json(t.m_bMessageReturn, format));

   QJsonValue input;
   if (t.m_pInputParameter)
   {
      t.m_pInputParameter->registerClass();
      QString sClassName = t.m_pInputParameter->getClassName();
      obj.insert("input_parameter_class_name", sClassName);
      input = t.m_pInputParameter->saveToJson();
   }
   obj.insert("input_parameter", input);

   QJsonValue output;
   if (t.m_pOutputParameter)
   {
      t.m_pOutputParameter->registerClass();
      QString sClassName = t.m_pOutputParameter->getClassName();
      obj.insert("output_parameter_class_name", sClassName);
      output = t.m_pOutputParameter->saveToJson();
   }
   obj.insert("output_parameter", output);

   return QJsonValue(obj);
}

qx_bool QxConvert_FromJson_Helper(const QJsonValue & j, qx::service::IxService & t, const QString & format)
{
   t = qx::service::IxService();
   if (! j.isObject()) { return qx_bool(true); }
   QJsonObject obj = j.toObject();
   t.m_sServiceName = obj.value("service_name").toString();
   t.m_sServiceMethodName = obj.value("service_method").toString();
   qx::cvt::from_json(obj.value("message_return"), t.m_bMessageReturn, format);

   t.m_pInputParameter.reset();
   if (obj.contains("input_parameter_class_name"))
   {
      QString sClassName = obj.value("input_parameter_class_name").toString();
      qx::service::IxParameter * ptr = qx::create_nude_ptr<qx::service::IxParameter>(sClassName);
      if (! ptr) { qAssertMsg(false, "[QxOrm] qx::cvt::detail::QxConvert_FromJson< qx::service::IxService >, loading QJson", "unable to create nude pointer for input parameter"); }
      else { ptr->registerClass(); ptr->loadFromJson(obj.value("input_parameter")); }
      t.m_pInputParameter.reset(ptr);
   }

   t.m_pOutputParameter.reset();
   if (obj.contains("output_parameter_class_name"))
   {
      QString sClassName = obj.value("output_parameter_class_name").toString();
      qx::service::IxParameter * ptr = qx::create_nude_ptr<qx::service::IxParameter>(sClassName);
      if (! ptr) { qAssertMsg(false, "[QxOrm] qx::cvt::detail::QxConvert_FromJson< qx::service::IxService >, loading QJson", "unable to create nude pointer for output parameter"); }
      else { ptr->registerClass(); ptr->loadFromJson(obj.value("output_parameter")); }
      t.m_pOutputParameter.reset(ptr);
   }

   return qx_bool(true);
}

} // namespace detail
} // namespace cvt
} // namespace qx

#endif // _QX_ENABLE_QT_NETWORK
#endif // _QX_NO_JSON
