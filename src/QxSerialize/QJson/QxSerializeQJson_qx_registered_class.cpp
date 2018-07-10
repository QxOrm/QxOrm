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

#include <QxSerialize/QJson/QxSerializeQJson_qx_registered_class.h>
#include <QxSerialize/QxSerializeCheckInstance.h>

#include <QxTraits/is_valid_primary_key.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace cvt {
namespace detail {

QJsonValue QxSerializeJsonRegistered_Helper::save(IxClass * pClass, const void * pOwner, const QString & format)
{
   if (! pClass || ! pOwner) { qAssert(false); return QJsonValue(); }
   bool bOnlyId = ((! format.isEmpty()) && ((format == QX_JSON_SERIALIZE_ONLY_ID) || (format == "mongodb:only_id") || (format == "mongodb:relation_id")));
   bool bCheckInstance = qx::serialization::helper::QxSerializeCheckInstance::contains(pOwner);
   QJsonObject obj;

   if (bCheckInstance || bOnlyId)
   {
      qx::IxDataMember * pId = pClass->getId(true); if (! pId) { return QJsonValue(); }
      QString key = ((format == "mongodb:only_id") ? QString("_id") : pId->getKey());
      QJsonValue val = pId->toJson(pOwner, format);
      if (format == "mongodb:relation_id") { return val; }
      obj.insert(key, val); return QJsonValue(obj);
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
   if (! j.isObject())
   {
      qx::IxDataMember * pId = pClass->getId(true); if (! pId) { return qx_bool(true); }
      return pId->fromJson(pOwner, j, format);
   }

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
   qx::IxDataMemberX * pDataMemberX = (pClass ? pClass->getDataMemberX() : NULL); if (! pDataMemberX) { return; }
   bool bMongoDB = (format.left(7) == "mongodb");
   bool bMongoDBColumns = (bMongoDB && format.contains(":columns{") && format.contains("}"));
   bool bMongoDBChild = (bMongoDB && (format.left(13) == "mongodb:child"));

   for (long l = 0; l < pDataMemberX->count(); l++)
   {
      qx::IxDataMember * pDataMember = pDataMemberX->get(l);
      if (! pDataMember || ! pDataMember->getSerialize()) { continue; }
      if (bMongoDB && ! pDataMember->getDao()) { continue; }
      if (bMongoDBColumns && ! pDataMember->getIsPrimaryKey() && ! format.contains("," + pDataMember->getKey() + ",")) { continue; }
      qx::IxSqlRelation * pRelation = pDataMember->getSqlRelation();
      qx::IxSqlRelation::relation_type eRelationType = (pRelation ? pRelation->getRelationType() : qx::IxSqlRelation::no_relation);
      if (bMongoDB && ((eRelationType == qx::IxSqlRelation::one_to_many) || (eRelationType == qx::IxSqlRelation::many_to_many))) { continue; }
      QString key = ((bMongoDB && ! bMongoDBChild && pDataMember->getIsPrimaryKey()) ? QString("_id") : pDataMember->getKey());
      QString formatTmp = ((bMongoDB && pRelation) ? QString("mongodb:relation_id") : (bMongoDB ? (QString("mongodb:child:") + format) : QString(format)));
      if (bMongoDB && pDataMember->getIsPrimaryKey()) { QVariant id = pDataMember->toVariant(pOwner); if (! qx::trait::is_valid_primary_key(id)) { continue; } }
      QJsonValue val = pDataMember->toJson(pOwner, formatTmp);
      obj.insert(key, val);
   }
}

void QxSerializeJsonRegistered_Helper::loadHelper(const QJsonObject & obj, IxClass * pClass, void * pOwner, const QString & format)
{
   qx::IxDataMemberX * pDataMemberX = (pClass ? pClass->getDataMemberX() : NULL); if (! pDataMemberX) { return; }
   bool bMongoDB = (format.left(7) == "mongodb");
   bool bMongoDBColumns = (bMongoDB && format.contains(":columns{") && format.contains("}"));
   bool bMongoDBChild = (bMongoDB && (format.left(13) == "mongodb:child"));

   for (long l = 0; l < pDataMemberX->count(); l++)
   {
      qx::IxDataMember * pDataMember = pDataMemberX->get(l);
      if (! pDataMember || ! pDataMember->getSerialize()) { continue; }
      if (bMongoDB && ! pDataMember->getDao()) { continue; }
      if (bMongoDBColumns && ! pDataMember->getIsPrimaryKey() && ! format.contains("," + pDataMember->getKey() + ",")) { continue; }
      QString key = ((bMongoDB && ! bMongoDBChild && pDataMember->getIsPrimaryKey()) ? QString("_id") : pDataMember->getKey());
      key = ((bMongoDB && bMongoDBChild && pDataMember->getIsPrimaryKey() && (! obj.contains(key))) ? QString("_id") : key);
      QString formatTmp = (bMongoDB ? (QString("mongodb:child:") + format) : QString(format));
      if (obj.contains(key)) { pDataMember->fromJson(pOwner, obj.value(key), formatTmp); }
   }
}

} // namespace detail
} // namespace cvt
} // namespace qx

#endif // _QX_NO_JSON
