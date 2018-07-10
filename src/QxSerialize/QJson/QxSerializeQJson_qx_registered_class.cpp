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

#include <QxSerialize/QJson/QxSerializeQJson_qx_registered_class.h>
#include <QxSerialize/QxSerializeCheckInstance.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace cvt {
namespace detail {

QJsonValue QxSerializeJsonRegistered_Helper::save(IxClass * pClass, const void * pOwner, const QString & format)
{
   if (! pClass || ! pOwner) { qAssert(false); return QJsonValue(); }
   QJsonObject obj;

   if ((qx::serialization::helper::QxSerializeCheckInstance::contains(pOwner)) || (format == QX_JSON_SERIALIZE_ONLY_ID))
   {
      qx::IxDataMember * pId = pClass->getId(true);
      if (! pId) { return QJsonValue(); }
      QJsonValue val = pId->toJson(pOwner);
      obj.insert(pId->getKey(), val);
      return QJsonValue(obj);
   }
   qx::serialization::helper::QxSerializeCheckInstance checker(pOwner);
   Q_UNUSED(checker);

   do
   {
      qx::cvt::detail::QxSerializeJsonRegistered_Helper::saveHelper(obj, pClass, pOwner, format);
      pClass = pClass->getBaseClass();
   }
   while (pClass != NULL);

   return QJsonValue(obj);
}

qx_bool QxSerializeJsonRegistered_Helper::load(const QJsonValue & j, IxClass * pClass, void * pOwner, const QString & format)
{
   if (! pClass || ! pOwner) { qAssert(false); return qx_bool(true); }
   if (! j.isObject()) { return qx_bool(true); }
   QJsonObject obj = j.toObject();

   do
   {
      qx::cvt::detail::QxSerializeJsonRegistered_Helper::loadHelper(obj, pClass, pOwner, format);
      pClass = pClass->getBaseClass();
   }
   while (pClass != NULL);

   return qx_bool(true);
}

void QxSerializeJsonRegistered_Helper::saveHelper(QJsonObject & obj, IxClass * pClass, const void * pOwner, const QString & format)
{
   Q_UNUSED(format);
   qx::IxDataMemberX * pDataMemberX = (pClass ? pClass->getDataMemberX() : NULL);
   if (! pDataMemberX) { return; }

   for (long l = 0; l < pDataMemberX->count(); l++)
   {
      qx::IxDataMember * pDataMember = pDataMemberX->get(l);
      if (! pDataMember || ! pDataMember->getSerialize()) { continue; }
      QJsonValue val = pDataMember->toJson(pOwner);
      obj.insert(pDataMember->getKey(), val);
   }
}

void QxSerializeJsonRegistered_Helper::loadHelper(const QJsonObject & obj, IxClass * pClass, void * pOwner, const QString & format)
{
   Q_UNUSED(format);
   qx::IxDataMemberX * pDataMemberX = (pClass ? pClass->getDataMemberX() : NULL);
   if (! pDataMemberX) { return; }

   for (long l = 0; l < pDataMemberX->count(); l++)
   {
      qx::IxDataMember * pDataMember = pDataMemberX->get(l);
      if (! pDataMember || ! pDataMember->getSerialize()) { continue; }
      if (! obj.contains(pDataMember->getKey())) { continue; }
      pDataMember->fromJson(pOwner, obj.value(pDataMember->getKey()));
   }
}

} // namespace detail
} // namespace cvt
} // namespace qx

#endif // _QX_NO_JSON
