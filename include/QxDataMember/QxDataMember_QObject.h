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

#ifndef _QX_DATA_MEMBER_QOBJECT_H_
#define _QX_DATA_MEMBER_QOBJECT_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxDataMember_QObject.h
 * \author Lionel Marty
 * \ingroup QxDataMember
 * \brief Connect Qt introspection engine (based on QObject class, with QMetaObject type) to QxOrm library introspection engine
 */

#include <QtCore/qmetaobject.h>
#include <QtCore/qmetatype.h>

#include <QxDataMember/IxDataMember.h>

#include <QxSerialize/Qt/QxSerialize_QString.h>
#include <QxSerialize/Qt/QxSerialize_QVariant.h>

#define QX_DATA_MEMBER_QOBJECT_IMPL_VIRTUAL_ARCHIVE_HPP(ArchiveInput, ArchiveOutput) \
virtual void toArchive(const void * pOwner, ArchiveOutput & ar) const; \
virtual void fromArchive(void * pOwner, ArchiveInput & ar);

namespace qx {

/*!
 * \ingroup QxDataMember
 * \brief qx::QxDataMember_QObject : connect Qt introspection engine (based on QObject class, with QMetaObject type) to QxOrm library introspection engine
 */
class QX_DLL_EXPORT QxDataMember_QObject : public IxDataMember
{

protected:

   const QMetaObject *  m_metaObject;    //!< Meta-object from introspection engine of Qt library (& MyQObject::staticMetaObject)
   QMetaProperty        m_metaProperty;  //!< Meta-property from introspection engine of Qt library

public:

   QxDataMember_QObject(const QMetaObject * pMetaObject, const QString & sKey);
   virtual ~QxDataMember_QObject() { ; }

   virtual bool isEqual(const void * pOwner1, const void * pOwner2) const;
   virtual QString toString(const void * pOwner, const QString & sFormat, int iIndexName = -1) const;
   virtual qx_bool fromString(void * pOwner, const QString & s, const QString & sFormat, int iIndexName = -1);
   virtual QVariant toVariant(const void * pOwner, const QString & sFormat, int iIndexName = -1, qx::cvt::context::ctx_type ctx = qx::cvt::context::e_no_context) const;
   virtual qx_bool fromVariant(void * pOwner, const QVariant & v, const QString & sFormat, int iIndexName = -1, qx::cvt::context::ctx_type ctx = qx::cvt::context::e_no_context);

#ifndef _QX_NO_JSON
   virtual QJsonValue toJson(const void * pOwner, const QString & sFormat) const;
   virtual qx_bool fromJson(void * pOwner, const QJsonValue & j, const QString & sFormat);
#endif // _QX_NO_JSON

public:

#ifdef _QX_ENABLE_BOOST_SERIALIZATION

#if _QX_SERIALIZE_POLYMORPHIC
   QX_DATA_MEMBER_QOBJECT_IMPL_VIRTUAL_ARCHIVE_HPP(boost::archive::polymorphic_iarchive, boost::archive::polymorphic_oarchive)
#endif // _QX_SERIALIZE_POLYMORPHIC

#if _QX_SERIALIZE_BINARY
   QX_DATA_MEMBER_QOBJECT_IMPL_VIRTUAL_ARCHIVE_HPP(boost::archive::binary_iarchive, boost::archive::binary_oarchive)
#endif // _QX_SERIALIZE_BINARY

#if _QX_SERIALIZE_TEXT
   QX_DATA_MEMBER_QOBJECT_IMPL_VIRTUAL_ARCHIVE_HPP(boost::archive::text_iarchive, boost::archive::text_oarchive)
#endif // _QX_SERIALIZE_TEXT

#if _QX_SERIALIZE_XML
   QX_DATA_MEMBER_QOBJECT_IMPL_VIRTUAL_ARCHIVE_HPP(boost::archive::xml_iarchive, boost::archive::xml_oarchive)
#endif // _QX_SERIALIZE_XML

#if _QX_SERIALIZE_PORTABLE_BINARY
   QX_DATA_MEMBER_QOBJECT_IMPL_VIRTUAL_ARCHIVE_HPP(eos::portable_iarchive, eos::portable_oarchive)
#endif // _QX_SERIALIZE_PORTABLE_BINARY

#if _QX_SERIALIZE_WIDE_BINARY
   QX_DATA_MEMBER_QOBJECT_IMPL_VIRTUAL_ARCHIVE_HPP(boost::archive::binary_wiarchive, boost::archive::binary_woarchive)
#endif // _QX_SERIALIZE_WIDE_BINARY

#if _QX_SERIALIZE_WIDE_TEXT
   QX_DATA_MEMBER_QOBJECT_IMPL_VIRTUAL_ARCHIVE_HPP(boost::archive::text_wiarchive, boost::archive::text_woarchive)
#endif // _QX_SERIALIZE_WIDE_TEXT

#if _QX_SERIALIZE_WIDE_XML
   QX_DATA_MEMBER_QOBJECT_IMPL_VIRTUAL_ARCHIVE_HPP(boost::archive::xml_wiarchive, boost::archive::xml_woarchive)
#endif // _QX_SERIALIZE_WIDE_XML

#endif // _QX_ENABLE_BOOST_SERIALIZATION

protected:

   virtual boost::any getDataPtr(const void * pOwner) const;
   virtual boost::any getDataPtr(void * pOwner);
   virtual void * getDataVoidPtr(const void * pOwner) const;
   virtual void * getDataVoidPtr(void * pOwner);

};

} // namespace qx

#endif // _QX_DATA_MEMBER_QOBJECT_H_
