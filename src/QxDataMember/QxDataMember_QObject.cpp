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

#include <QxDataMember/QxDataMember_QObject.h>

#include <QxRegister/QxClassX.h>

#include <QxConvert/QxConvert.h>
#include <QxConvert/QxConvert_Impl.h>

#include <QxMemLeak/mem_leak.h>

#define QX_DATA_MEMBER_QOBJECT_IMPL_VIRTUAL_ARCHIVE_CPP(ArchiveInput, ArchiveOutput) \
namespace qx { \
void QxDataMember_QObject::toArchive(const void * pOwner, ArchiveOutput & ar) const \
{ QVariant v = m_metaProperty.read(static_cast<const QObject *>(pOwner)); ar << boost::serialization::make_nvp(getNamePtr(), v); } \
void QxDataMember_QObject::fromArchive(void * pOwner, ArchiveInput & ar) \
{ QVariant v; ar >> boost::serialization::make_nvp(getNamePtr(), v); m_metaProperty.write(static_cast<QObject *>(pOwner), v); } }

namespace qx {

QxDataMember_QObject::QxDataMember_QObject(const QMetaObject * pMetaObject, const QString & sKey) : IxDataMember(sKey, 0, true, true, NULL), m_metaObject(pMetaObject)
{
   setAccessDataPointer(false);
   if (! m_metaObject) { qAssert(false); return; }
   int index = m_metaObject->indexOfProperty(qPrintable(sKey));
   if (index == -1) { qAssert(false); return; }
   m_metaProperty = m_metaObject->property(index);
   setSqlType(QxClassX::getSqlTypeByClassName(m_metaProperty.typeName()));
}

bool QxDataMember_QObject::isEqual(const void * pOwner1, const void * pOwner2) const
{
   if ((pOwner1 == NULL) || (pOwner2 == NULL)) { return false; }
   if (pOwner1 == pOwner2) { return true; }
   QVariant var1 = m_metaProperty.read(static_cast<const QObject *>(pOwner1));
   QVariant var2 = m_metaProperty.read(static_cast<const QObject *>(pOwner2));
   return (var1 == var2);
}

QVariant QxDataMember_QObject::toVariant(const void * pOwner, const QString & sFormat, int iIndexName /* = -1 */, qx::cvt::context::ctx_type ctx /* = qx::cvt::context::e_no_context */) const
{
   Q_UNUSED(sFormat); Q_UNUSED(iIndexName); Q_UNUSED(ctx);
   return m_metaProperty.read(static_cast<const QObject *>(pOwner));
}

qx_bool QxDataMember_QObject::fromVariant(void * pOwner, const QVariant & v, const QString & sFormat, int iIndexName /* = -1 */, qx::cvt::context::ctx_type ctx /* = qx::cvt::context::e_no_context */)
{
   Q_UNUSED(sFormat); Q_UNUSED(iIndexName); Q_UNUSED(ctx);
   return m_metaProperty.write(static_cast<QObject *>(pOwner), v);
}

QString QxDataMember_QObject::getType() const
{
   return QString(m_metaProperty.typeName());
}

#ifndef _QX_NO_JSON

QJsonValue QxDataMember_QObject::toJson(const void * pOwner, const QString & sFormat) const
{
   Q_UNUSED(sFormat);
   QVariant val = m_metaProperty.read(static_cast<const QObject *>(pOwner));

#ifdef _QX_ENABLE_MONGODB
   if (getIsPrimaryKey() && sFormat.startsWith("mongodb"))
   {
      QString tmp = val.toString();
      if (tmp.startsWith("qx_oid:")) { QJsonObject obj; obj.insert("$oid", QJsonValue(tmp.right(tmp.size() - 7))); return QJsonValue(obj); }
   }
#endif // _QX_ENABLE_MONGODB

   return QJsonValue::fromVariant(val);
}

qx_bool QxDataMember_QObject::fromJson(void * pOwner, const QJsonValue & j, const QString & sFormat)
{
   Q_UNUSED(sFormat);
   QVariant val = j.toVariant();

#ifdef _QX_ENABLE_MONGODB
   if (getIsPrimaryKey() && val.toString().isEmpty() && j.isObject() && sFormat.startsWith("mongodb"))
   {
      QJsonObject obj = j.toObject(); QString tmp;
      if (obj.contains("$oid")) { tmp = obj.value("$oid").toString(); }
      if (! tmp.isEmpty()) { tmp = ("qx_oid:" + tmp); val = tmp; }
   }
#endif // _QX_ENABLE_MONGODB

   return m_metaProperty.write(static_cast<QObject *>(pOwner), val);
}

#endif // _QX_NO_JSON

qx::any QxDataMember_QObject::getDataPtr(const void * pOwner) const
{
   Q_UNUSED(pOwner);
   qDebug("[QxOrm] qx::QxDataMember_QObject::getDataPtr() : '%s'", "cannot access to the data-member pointer with Qt introspection engine");
   qAssert(false);
   return qx::any();
}

qx::any QxDataMember_QObject::getDataPtr(void * pOwner)
{
   Q_UNUSED(pOwner);
   qDebug("[QxOrm] qx::QxDataMember_QObject::getDataPtr() : '%s'", "cannot access to the data-member pointer with Qt introspection engine");
   qAssert(false);
   return qx::any();
}

void * QxDataMember_QObject::getDataVoidPtr(const void * pOwner) const
{
   Q_UNUSED(pOwner);
   qDebug("[QxOrm] qx::QxDataMember_QObject::getDataVoidPtr() : '%s'", "cannot access to the data-member pointer with Qt introspection engine");
   qAssert(false);
   return NULL;
}

void * QxDataMember_QObject::getDataVoidPtr(void * pOwner)
{
   Q_UNUSED(pOwner);
   qDebug("[QxOrm] qx::QxDataMember_QObject::getDataVoidPtr() : '%s'", "cannot access to the data-member pointer with Qt introspection engine");
   qAssert(false);
   return NULL;
}

} // namespace qx

#ifdef _QX_ENABLE_BOOST_SERIALIZATION

#if _QX_SERIALIZE_POLYMORPHIC
   QX_DATA_MEMBER_QOBJECT_IMPL_VIRTUAL_ARCHIVE_CPP(boost::archive::polymorphic_iarchive, boost::archive::polymorphic_oarchive)
#endif // _QX_SERIALIZE_POLYMORPHIC

#if _QX_SERIALIZE_BINARY
   QX_DATA_MEMBER_QOBJECT_IMPL_VIRTUAL_ARCHIVE_CPP(boost::archive::binary_iarchive, boost::archive::binary_oarchive)
#endif // _QX_SERIALIZE_BINARY

#if _QX_SERIALIZE_TEXT
   QX_DATA_MEMBER_QOBJECT_IMPL_VIRTUAL_ARCHIVE_CPP(boost::archive::text_iarchive, boost::archive::text_oarchive)
#endif // _QX_SERIALIZE_TEXT

#if _QX_SERIALIZE_XML
   QX_DATA_MEMBER_QOBJECT_IMPL_VIRTUAL_ARCHIVE_CPP(boost::archive::xml_iarchive, boost::archive::xml_oarchive)
#endif // _QX_SERIALIZE_XML

#if _QX_SERIALIZE_PORTABLE_BINARY
   QX_DATA_MEMBER_QOBJECT_IMPL_VIRTUAL_ARCHIVE_CPP(eos::portable_iarchive, eos::portable_oarchive)
#endif // _QX_SERIALIZE_PORTABLE_BINARY

#if _QX_SERIALIZE_WIDE_BINARY
   QX_DATA_MEMBER_QOBJECT_IMPL_VIRTUAL_ARCHIVE_CPP(boost::archive::binary_wiarchive, boost::archive::binary_woarchive)
#endif // _QX_SERIALIZE_WIDE_BINARY

#if _QX_SERIALIZE_WIDE_TEXT
   QX_DATA_MEMBER_QOBJECT_IMPL_VIRTUAL_ARCHIVE_CPP(boost::archive::text_wiarchive, boost::archive::text_woarchive)
#endif // _QX_SERIALIZE_WIDE_TEXT

#if _QX_SERIALIZE_WIDE_XML
   QX_DATA_MEMBER_QOBJECT_IMPL_VIRTUAL_ARCHIVE_CPP(boost::archive::xml_wiarchive, boost::archive::xml_woarchive)
#endif // _QX_SERIALIZE_WIDE_XML

#endif // _QX_ENABLE_BOOST_SERIALIZATION
