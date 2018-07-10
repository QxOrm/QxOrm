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

#include <QxSerialize/QDataStream/QxSerializeQDataStream_qx_registered_class.h>
#include <QxSerialize/QxSerializeCheckInstance.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

QDataStream & QxSerializeRegistered_Helper::save(QDataStream & stream, IxClass * pClass, const void * pOwner)
{
   if (! pClass || ! pOwner) { qAssert(false); return stream; }
   stream << (quint32)(13939);
   bool bJustId = false;

   if (qx::serialization::helper::QxSerializeCheckInstance::contains(pOwner))
   {
      bJustId = true; stream << bJustId;
      qx::IxDataMember * pId = pClass->getId(true); if (! pId) { return stream; }
      QVariant val = pId->toVariant(pOwner); stream << val;
      return stream;
   }
   qx::serialization::helper::QxSerializeCheckInstance checker(pOwner);
   stream << bJustId; Q_UNUSED(checker);

   do
   {
      qx::QxSerializeRegistered_Helper::saveHelper(stream, pClass, pOwner);
      pClass = pClass->getBaseClass();
   }
   while (pClass != NULL);

   return stream;
}

QDataStream & QxSerializeRegistered_Helper::load(QDataStream & stream, IxClass * pClass, void * pOwner)
{
   if (! pClass || ! pOwner) { qAssert(false); return stream; }

   bool bJustId = false;
   quint32 magic = 0; stream >> magic;
   if ((magic != 13937) && (magic != 13939))
   { qDebug("[QxOrm] qx::QxSerializeRegistered_Helper::load() : %s", "input binary data is not valid"); return stream; }
   if (magic > 13937) { stream >> bJustId; }

   if (bJustId)
   {
      qx::IxDataMember * pId = pClass->getId(true); if (! pId) { return stream; }
      QVariant val; stream >> val; pId->fromVariant(pOwner, val);
      return stream;
   }

   do
   {
      qx::QxSerializeRegistered_Helper::loadHelper(stream, pClass, pOwner);
      pClass = pClass->getBaseClass();
   }
   while (pClass != NULL);

   return stream;
}

void QxSerializeRegistered_Helper::saveHelper(QDataStream & stream, IxClass * pClass, const void * pOwner)
{
   IxDataMemberX * pDataMemberX = (pClass ? pClass->getDataMemberX() : NULL); if (! pDataMemberX) { return; }
   qint16 iVersion = static_cast<qint16>(pClass->getVersion());
   stream << iVersion;

   for (long l = 0; l < pDataMemberX->count(); l++)
   {
      IxDataMember * pDataMember = pDataMemberX->get(l);
      if (! pDataMember || ! pDataMember->getSerialize()) { continue; }
      if (pDataMember->getVersion() > static_cast<long>(iVersion)) { qAssert(false); continue; }
      QVariant vValue = pDataMember->toVariant(pOwner, -1, qx::cvt::context::e_serialize_registered);
      stream << vValue;
   }
}

void QxSerializeRegistered_Helper::loadHelper(QDataStream & stream, IxClass * pClass, void * pOwner)
{
   IxDataMemberX * pDataMemberX = (pClass ? pClass->getDataMemberX() : NULL); if (! pDataMemberX) { return; }
   qint16 iVersion = 0; stream >> iVersion;

   for (long l = 0; l < pDataMemberX->count(); l++)
   {
      IxDataMember * pDataMember = pDataMemberX->get(l);
      if (! pDataMember || ! pDataMember->getSerialize()) { continue; }
      if (pDataMember->getVersion() > static_cast<long>(iVersion)) { continue; }
      QVariant vValue; stream >> vValue;
      pDataMember->fromVariant(pOwner, vValue, -1, qx::cvt::context::e_serialize_registered);
   }
}

} // namespace qx
