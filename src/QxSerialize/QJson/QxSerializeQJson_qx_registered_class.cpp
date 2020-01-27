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

#include <QxDao/QxSqlRelationLinked.h>

#include <QxTraits/is_valid_primary_key.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace cvt {
namespace detail {

void QxSerializeJsonRegistered_saveHelper(QJsonObject & obj, IxClass * pClass, const void * pOwner, const QString & format);
void QxSerializeJsonRegistered_saveHelper_MongoDB(QJsonObject & obj, IxClass * pClass, const void * pOwner, const QString & format);
void QxSerializeJsonRegistered_saveHelper_WithFilter(QJsonObject & obj, IxClass * pClass, const void * pOwner, const QString & format);

void QxSerializeJsonRegistered_loadHelper(const QJsonObject & obj, IxClass * pClass, void * pOwner, const QString & format);
void QxSerializeJsonRegistered_loadHelper_MongoDB(const QJsonObject & obj, IxClass * pClass, void * pOwner, const QString & format);
void QxSerializeJsonRegistered_loadHelper_WithFilter(const QJsonObject & obj, IxClass * pClass, void * pOwner, const QString & format);

qx_bool QxSerializeJsonRegistered_initHierarchy_WithFilter(IxClass * pClass, const void * pOwner, const QString & format);

QJsonValue QxSerializeJsonRegistered_Helper::save(IxClass * pClass, const void * pOwner, const QString & format)
{
   if (! pClass || ! pOwner) { qAssert(false); return QJsonValue(); }
   bool bOnlyId = ((! format.isEmpty()) && ((format == QX_JSON_SERIALIZE_ONLY_ID) || (format == "mongodb:only_id") || (format == "mongodb:relation_id")));
   bool bCheckInstance = qx::serialization::helper::QxSerializeCheckInstance::contains(pOwner, pClass);
   QJsonObject obj;

   if (bCheckInstance || bOnlyId)
   {
      qx::IxDataMember * pId = pClass->getId(true); if (! pId) { return QJsonValue(); }
      QString key = ((format == "mongodb:only_id") ? QString("_id") : pId->getKey());
      QJsonValue val = pId->toJson(pOwner, format);
      if (format == "mongodb:relation_id") { return val; }
      obj.insert(key, val); return QJsonValue(obj);
   }

   bool bMongoDB = format.startsWith("mongodb");
   bool bWithFilter = format.startsWith("filter:");
   qx_bool bHierarchyOk = (bWithFilter ? QxSerializeJsonRegistered_initHierarchy_WithFilter(pClass, pOwner, format) : qx_bool(true));
   if (! bHierarchyOk) { obj.insert("error", bHierarchyOk.getDesc()); return QJsonValue(obj); }
   qx::serialization::helper::QxSerializeCheckInstance checker(pOwner, pClass);
   Q_UNUSED(checker);

   do
   {
      if (bMongoDB) { qx::cvt::detail::QxSerializeJsonRegistered_saveHelper_MongoDB(obj, pClass, pOwner, format); }
      else if (bWithFilter) { qx::cvt::detail::QxSerializeJsonRegistered_saveHelper_WithFilter(obj, pClass, pOwner, format); break; }
      else { qx::cvt::detail::QxSerializeJsonRegistered_saveHelper(obj, pClass, pOwner, format); }
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

   bool bMongoDB = format.startsWith("mongodb");
   bool bWithFilter = format.startsWith("filter:");
   QJsonObject obj = j.toObject();

   do
   {
      if (bMongoDB) { qx::cvt::detail::QxSerializeJsonRegistered_loadHelper_MongoDB(obj, pClass, pOwner, format); }
      else if (bWithFilter) { qx::cvt::detail::QxSerializeJsonRegistered_loadHelper_WithFilter(obj, pClass, pOwner, format); break; }
      else { qx::cvt::detail::QxSerializeJsonRegistered_loadHelper(obj, pClass, pOwner, format); }
      pClass = pClass->getBaseClass();
   }
   while (pClass != NULL);

   return qx_bool(true);
}

qx_bool QxSerializeJsonRegistered_initHierarchy_WithFilter(IxClass * pClass, const void * pOwner, const QString & format)
{
   qx_bool bHierarchyOk(true); Q_UNUSED(pOwner);
   if (! qx::serialization::helper::QxSerializeCheckInstance::isRoot()) { return bHierarchyOk; }
   std::shared_ptr<qx::QxSqlRelationLinked> pRelationLinked = qx::QxSqlRelationLinked::getHierarchy(pClass, format.right(format.size() - 7).split("|"), bHierarchyOk);
   if (! bHierarchyOk || ! pRelationLinked) { return qx_bool(false, bHierarchyOk.getDesc()); }

   QString empty;
   qx::serialization::helper::QxSerializeCheckInstance::type_hierarchy hierarchy = qMakePair(pRelationLinked, empty);
   qx::serialization::helper::QxSerializeCheckInstance::setHierarchy(hierarchy);
   return bHierarchyOk;
}

void QxSerializeJsonRegistered_saveHelper(QJsonObject & obj, IxClass * pClass, const void * pOwner, const QString & format)
{
   qx::IxDataMemberX * pDataMemberX = (pClass ? pClass->getDataMemberX() : NULL); if (! pDataMemberX) { return; }

   for (long l = 0; l < pDataMemberX->count(); l++)
   {
      qx::IxDataMember * pDataMember = pDataMemberX->get(l);
      if (! pDataMember || ! pDataMember->getSerialize()) { continue; }
      QJsonValue val = pDataMember->toJson(pOwner, format);
      obj.insert(pDataMember->getKey(), val);
   }
}

void QxSerializeJsonRegistered_saveHelper_MongoDB(QJsonObject & obj, IxClass * pClass, const void * pOwner, const QString & format)
{
   qx::IxDataMemberX * pDataMemberX = (pClass ? pClass->getDataMemberX() : NULL); if (! pDataMemberX) { return; }
   bool bMongoDBColumns = (format.contains(":columns{") && format.contains("}"));
   bool bMongoDBChild = format.startsWith("mongodb:child");

   for (long l = 0; l < pDataMemberX->count(); l++)
   {
      qx::IxDataMember * pDataMember = pDataMemberX->get(l);
      if (! pDataMember || ! pDataMember->getSerialize() || ! pDataMember->getDao()) { continue; }
      if (bMongoDBColumns && ! pDataMember->getIsPrimaryKey() && ! format.contains("," + pDataMember->getKey() + ",")) { continue; }
      qx::IxSqlRelation * pRelation = pDataMember->getSqlRelation();
      qx::IxSqlRelation::relation_type eRelationType = (pRelation ? pRelation->getRelationType() : qx::IxSqlRelation::no_relation);
      if ((eRelationType == qx::IxSqlRelation::one_to_many) || (eRelationType == qx::IxSqlRelation::many_to_many)) { continue; }
      QString key = ((! bMongoDBChild && pDataMember->getIsPrimaryKey()) ? QString("_id") : pDataMember->getKey());
      QString formatTmp = (pRelation ? QString("mongodb:relation_id") : (QString("mongodb:child:") + format));
      if (pDataMember->getIsPrimaryKey()) { QVariant id = pDataMember->toVariant(pOwner); if (! qx::trait::is_valid_primary_key(id)) { continue; } }
      QJsonValue val = pDataMember->toJson(pOwner, formatTmp);
      obj.insert(key, val);
   }
}

void QxSerializeJsonRegistered_saveHelper_WithFilter(QJsonObject & obj, IxClass * pClass, const void * pOwner, const QString & format)
{
   qx::serialization::helper::QxSerializeCheckInstance::type_hierarchy currHierarchy = qx::serialization::helper::QxSerializeCheckInstance::getHierarchy();
   std::shared_ptr<qx::QxSqlRelationLinked> pRelationLinked = currHierarchy.first;
   QString sRelation = currHierarchy.second;

   if (! pRelationLinked || ! pClass) { QString msg = ("hierarchy (relations linked) not found : " + sRelation); qAssertMsg(false, "QxSerializeJsonRegistered_saveHelper_WithFilter", qPrintable(msg)); return; }
   qx::QxSqlRelationLinked::type_lst_relation pRelations = pRelationLinked->getRelationX();

   qx::IxDataMember * pDataMemberId = pClass->getId(true);
   if (pDataMemberId) { QJsonValue val = pDataMemberId->toJson(pOwner, format); obj.insert(pDataMemberId->getKey(), val); }

   if (pRelationLinked->isRoot() && sRelation.isEmpty())
   {
      std::shared_ptr<qx::QxCollection<QString, qx::IxDataMember *> > pDataMemberX = pClass->getSqlDataMemberX(); if (! pDataMemberX) { return; }
      for (long l = 0; l < pDataMemberX->count(); l++)
      {
         qx::IxDataMember * pDataMember = pDataMemberX->getByIndex(l);
         if (! pDataMember || ! pDataMember->getSerialize()) { continue; }
         if (! pRelationLinked->checkRootColumns(pDataMember->getKey())) { continue; }
         QJsonValue val = pDataMember->toJson(pOwner, format);
         obj.insert(pDataMember->getKey(), val);
      }

      for (auto itr = pRelations.begin(); itr != pRelations.end(); ++itr)
      {
         const qx::QxSqlRelationLinked::type_relation & item = itr->second;
         qx::IxSqlRelation * pRelation = std::get<1>(item); if (! pRelation) { continue; }
         qx::IxDataMember * pDataMember = pRelation->getDataMember(); if (! pDataMember || ! pDataMember->getSerialize()) { continue; }
         qx::serialization::helper::QxSerializeCheckInstance::type_hierarchy nextHierarchy = qMakePair(pRelationLinked, itr->first);
         qx::serialization::helper::QxSerializeCheckInstance::setHierarchy(nextHierarchy);
         QJsonValue val = pDataMember->toJson(pOwner, format);
         obj.insert(pDataMember->getKey(), val);
      }

      std::shared_ptr<qx::QxSqlRelationLinked> pNullRelationLinked; QString empty;
      qx::serialization::helper::QxSerializeCheckInstance::type_hierarchy nullHierarchy = qMakePair(pNullRelationLinked, empty);
      qx::serialization::helper::QxSerializeCheckInstance::setHierarchy(nullHierarchy);
   }
   else if (pRelations.exist(sRelation))
   {
      const qx::QxSqlRelationLinked::type_relation & currRelation = pRelations.getByKey(sRelation);
      qx::IxSqlRelation * pRelation = std::get<1>(currRelation); if (! pRelation) { return; }
      QSet<QString> columns = std::get<2>(currRelation).first;
      long l = 0; qx::IxDataMember * pDataMember = NULL;
      while ((pDataMember = pRelation->nextData(l)))
      {
         if (! pDataMember || ! pDataMember->getSerialize()) { continue; }
         if ((columns.count() > 0) && (! columns.contains(pDataMember->getKey()))) { continue; }
         QJsonValue val = pDataMember->toJson(pOwner, format);
         obj.insert(pDataMember->getKey(), val);
      }

      qx::QxSqlRelationLinked::type_lst_relation_linked allSubRelationsLinked = pRelationLinked->getRelationLinkedX();
      qx::QxSqlRelationLinked::type_ptr pSubRelationLinked = allSubRelationsLinked.value(pRelation->getKey()); if (! pSubRelationLinked) { return; }
      qx::QxSqlRelationLinked::type_lst_relation pSubRelations = pSubRelationLinked->getRelationX();
      for (auto itr = pSubRelations.begin(); itr != pSubRelations.end(); ++itr)
      {
         const qx::QxSqlRelationLinked::type_relation & item = itr->second;
         qx::IxSqlRelation * pSubRelation = std::get<1>(item); if (! pSubRelation) { continue; }
         pDataMember = pSubRelation->getDataMember(); if (! pDataMember || ! pDataMember->getSerialize()) { continue; }
         qx::serialization::helper::QxSerializeCheckInstance::type_hierarchy nextHierarchy = qMakePair(pSubRelationLinked, itr->first);
         qx::serialization::helper::QxSerializeCheckInstance::setHierarchy(nextHierarchy);
         QJsonValue val = pDataMember->toJson(pOwner, format);
         obj.insert(pDataMember->getKey(), val);
         qx::serialization::helper::QxSerializeCheckInstance::setHierarchy(currHierarchy);
      }
   }
   else
   {
      qAssertMsg(false, "QxSerializeJsonRegistered_saveHelper_WithFilter", "unknown error");
   }
}

void QxSerializeJsonRegistered_loadHelper(const QJsonObject & obj, IxClass * pClass, void * pOwner, const QString & format)
{
   qx::IxDataMemberX * pDataMemberX = (pClass ? pClass->getDataMemberX() : NULL); if (! pDataMemberX) { return; }

   for (long l = 0; l < pDataMemberX->count(); l++)
   {
      qx::IxDataMember * pDataMember = pDataMemberX->get(l);
      if (! pDataMember || ! pDataMember->getSerialize()) { continue; }
      QString key = pDataMember->getKey();
      if (obj.contains(key)) { pDataMember->fromJson(pOwner, obj.value(key), format); }
   }
}

void QxSerializeJsonRegistered_loadHelper_MongoDB(const QJsonObject & obj, IxClass * pClass, void * pOwner, const QString & format)
{
   qx::IxDataMemberX * pDataMemberX = (pClass ? pClass->getDataMemberX() : NULL); if (! pDataMemberX) { return; }
   bool bMongoDBColumns = (format.contains(":columns{") && format.contains("}"));
   bool bMongoDBChild = format.startsWith("mongodb:child");

   for (long l = 0; l < pDataMemberX->count(); l++)
   {
      qx::IxDataMember * pDataMember = pDataMemberX->get(l);
      if (! pDataMember || ! pDataMember->getSerialize() || ! pDataMember->getDao()) { continue; }
      if (bMongoDBColumns && ! pDataMember->getIsPrimaryKey() && ! format.contains("," + pDataMember->getKey() + ",")) { continue; }
      QString key = ((! bMongoDBChild && pDataMember->getIsPrimaryKey()) ? QString("_id") : pDataMember->getKey());
      key = ((bMongoDBChild && pDataMember->getIsPrimaryKey() && (! obj.contains(key))) ? QString("_id") : key);
      if (obj.contains(key)) { pDataMember->fromJson(pOwner, obj.value(key), (QString("mongodb:child:") + format)); }
   }
}

void QxSerializeJsonRegistered_loadHelper_WithFilter(const QJsonObject & obj, IxClass * pClass, void * pOwner, const QString & format)
{
   qx_bool bHierarchyOk = QxSerializeJsonRegistered_initHierarchy_WithFilter(pClass, pOwner, format);
   if (! bHierarchyOk) { QString msg = bHierarchyOk.getDesc(); qDebug("[QxOrm] !!! Error in QxSerializeJsonRegistered_loadHelper_WithFilter !!! : '%s'", qPrintable(msg)); return; }
   qx::serialization::helper::QxSerializeCheckInstance checker(pOwner, pClass);
   Q_UNUSED(checker);

   qx::serialization::helper::QxSerializeCheckInstance::type_hierarchy currHierarchy = qx::serialization::helper::QxSerializeCheckInstance::getHierarchy();
   std::shared_ptr<qx::QxSqlRelationLinked> pRelationLinked = currHierarchy.first;
   QString sRelation = currHierarchy.second;

   if (! pRelationLinked || ! pClass) { QString msg = ("hierarchy (relations linked) not found : " + sRelation); qAssertMsg(false, "QxSerializeJsonRegistered_loadHelper_WithFilter", qPrintable(msg)); return; }
   qx::QxSqlRelationLinked::type_lst_relation pRelations = pRelationLinked->getRelationX();

   qx::IxDataMember * pDataMemberId = pClass->getId(true);
   if (pDataMemberId && obj.contains(pDataMemberId->getKey())) { pDataMemberId->fromJson(pOwner, obj.value(pDataMemberId->getKey()), format); }

   if (pRelationLinked->isRoot() && sRelation.isEmpty())
   {
      std::shared_ptr<qx::QxCollection<QString, qx::IxDataMember *> > pDataMemberX = pClass->getSqlDataMemberX(); if (! pDataMemberX) { return; }
      for (long l = 0; l < pDataMemberX->count(); l++)
      {
         qx::IxDataMember * pDataMember = pDataMemberX->getByIndex(l);
         if (! pDataMember || ! pDataMember->getSerialize()) { continue; }
         if (! pRelationLinked->checkRootColumns(pDataMember->getKey())) { continue; }
         if (obj.contains(pDataMember->getKey())) { pDataMember->fromJson(pOwner, obj.value(pDataMember->getKey()), format); }
      }

      for (auto itr = pRelations.begin(); itr != pRelations.end(); ++itr)
      {
         const qx::QxSqlRelationLinked::type_relation & item = itr->second;
         qx::IxSqlRelation * pRelation = std::get<1>(item); if (! pRelation) { continue; }
         qx::IxDataMember * pDataMember = pRelation->getDataMember(); if (! pDataMember || ! pDataMember->getSerialize()) { continue; }
         qx::serialization::helper::QxSerializeCheckInstance::type_hierarchy nextHierarchy = qMakePair(pRelationLinked, itr->first);
         qx::serialization::helper::QxSerializeCheckInstance::setHierarchy(nextHierarchy);
         if (obj.contains(pDataMember->getKey())) { pDataMember->fromJson(pOwner, obj.value(pDataMember->getKey()), format); }
      }

      std::shared_ptr<qx::QxSqlRelationLinked> pNullRelationLinked; QString empty;
      qx::serialization::helper::QxSerializeCheckInstance::type_hierarchy nullHierarchy = qMakePair(pNullRelationLinked, empty);
      qx::serialization::helper::QxSerializeCheckInstance::setHierarchy(nullHierarchy);
   }
   else if (pRelations.exist(sRelation))
   {
      const qx::QxSqlRelationLinked::type_relation & currRelation = pRelations.getByKey(sRelation);
      qx::IxSqlRelation * pRelation = std::get<1>(currRelation); if (! pRelation) { return; }
      QSet<QString> columns = std::get<2>(currRelation).first;
      long l = 0; qx::IxDataMember * pDataMember = NULL;
      while ((pDataMember = pRelation->nextData(l)))
      {
         if (! pDataMember || ! pDataMember->getSerialize()) { continue; }
         if ((columns.count() > 0) && (! columns.contains(pDataMember->getKey()))) { continue; }
         if (obj.contains(pDataMember->getKey())) { pDataMember->fromJson(pOwner, obj.value(pDataMember->getKey()), format); }
      }

      qx::QxSqlRelationLinked::type_lst_relation_linked allSubRelationsLinked = pRelationLinked->getRelationLinkedX();
      qx::QxSqlRelationLinked::type_ptr pSubRelationLinked = allSubRelationsLinked.value(pRelation->getKey()); if (! pSubRelationLinked) { return; }
      qx::QxSqlRelationLinked::type_lst_relation pSubRelations = pSubRelationLinked->getRelationX();
      for (auto itr = pSubRelations.begin(); itr != pSubRelations.end(); ++itr)
      {
         const qx::QxSqlRelationLinked::type_relation & item = itr->second;
         qx::IxSqlRelation * pSubRelation = std::get<1>(item); if (! pSubRelation) { continue; }
         pDataMember = pSubRelation->getDataMember(); if (! pDataMember || ! pDataMember->getSerialize()) { continue; }
         qx::serialization::helper::QxSerializeCheckInstance::type_hierarchy nextHierarchy = qMakePair(pSubRelationLinked, itr->first);
         qx::serialization::helper::QxSerializeCheckInstance::setHierarchy(nextHierarchy);
         if (obj.contains(pDataMember->getKey())) { pDataMember->fromJson(pOwner, obj.value(pDataMember->getKey()), format); }
         qx::serialization::helper::QxSerializeCheckInstance::setHierarchy(currHierarchy);
      }
   }
   else
   {
      qAssertMsg(false, "QxSerializeJsonRegistered_loadHelper_WithFilter", "unknown error");
   }
}

} // namespace detail
} // namespace cvt
} // namespace qx

#endif // _QX_NO_JSON
