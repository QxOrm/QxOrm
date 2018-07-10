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

QxDataMember_QObject::QxDataMember_QObject(const QMetaObject * pMetaObject, const QString & sKey) : IxDataMember(sKey), m_metaObject(pMetaObject)
{
   m_bAccessDataPointer = false;
   if (! m_metaObject) { qAssert(false); return; }
   int index = m_metaObject->indexOfProperty(qPrintable(sKey));
   if (index == -1) { qAssert(false); return; }
   m_metaProperty = m_metaObject->property(index);
   m_sSqlType = QxClassX::getSqlTypeByClassName(m_metaProperty.typeName());
}

bool QxDataMember_QObject::isEqual(const void * pOwner1, const void * pOwner2) const
{
   if ((pOwner1 == NULL) || (pOwner2 == NULL)) { return false; }
   if (pOwner1 == pOwner2) { return true; }
   QVariant var1 = m_metaProperty.read(static_cast<const QObject *>(pOwner1));
   QVariant var2 = m_metaProperty.read(static_cast<const QObject *>(pOwner2));
   return (var1 == var2);
}

QString QxDataMember_QObject::toString(const void * pOwner, const QString & sFormat, int iIndexName /* = -1 */) const
{
   Q_UNUSED(sFormat); Q_UNUSED(iIndexName);
   return m_metaProperty.read(static_cast<const QObject *>(pOwner)).toString();
}

qx_bool QxDataMember_QObject::fromString(void * pOwner, const QString & s, const QString & sFormat, int iIndexName /* = -1 */)
{
   Q_UNUSED(sFormat); Q_UNUSED(iIndexName);
   return m_metaProperty.write(static_cast<QObject *>(pOwner), QVariant::fromValue(s));
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

#ifndef _QX_NO_JSON

QJsonValue QxDataMember_QObject::toJson(const void * pOwner, const QString & sFormat) const
{
   Q_UNUSED(sFormat);
   return QJsonValue::fromVariant(m_metaProperty.read(static_cast<const QObject *>(pOwner)));
}

qx_bool QxDataMember_QObject::fromJson(void * pOwner, const QJsonValue & j, const QString & sFormat)
{
   Q_UNUSED(sFormat);
   return m_metaProperty.write(static_cast<QObject *>(pOwner), j.toVariant());
}

#endif // _QX_NO_JSON

boost::any QxDataMember_QObject::getDataPtr(const void * pOwner) const
{
   Q_UNUSED(pOwner);
   qDebug("[QxOrm] qx::QxDataMember_QObject::getDataPtr() : '%s'", "cannot access to the data-member pointer with Qt introspection engine");
   qAssert(false);
   return boost::any();
}

boost::any QxDataMember_QObject::getDataPtr(void * pOwner)
{
   Q_UNUSED(pOwner);
   qDebug("[QxOrm] qx::QxDataMember_QObject::getDataPtr() : '%s'", "cannot access to the data-member pointer with Qt introspection engine");
   qAssert(false);
   return boost::any();
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
