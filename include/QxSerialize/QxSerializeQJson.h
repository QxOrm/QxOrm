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

#ifndef _QX_NO_JSON
#ifndef _QX_SERIALIZE_QJSON_H_
#define _QX_SERIALIZE_QJSON_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSerializeQJson.h
 * \author Lionel Marty
 * \ingroup QxSerialize
 * \brief Provide a serialization engine with Qt QJson classes (this feature requires Qt5)
 */

#include <QtCore/qjsonvalue.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/qfile.h>

#include <QxCommon/QxBool.h>

#include <QxConvert/QxConvert.h>

namespace qx {
namespace serialization {

/*!
 * \ingroup QxSerialize
 * \brief serialize a class registered into QxOrm context using Qt QJson serialization engine (this feature requires Qt5)
 */
namespace json {

template <class T>
inline QByteArray to_byte_array(const T & obj, void * owner = NULL, unsigned int flags = 1 /* boost::archive::no_header */)
{
   Q_UNUSED(flags); Q_UNUSED(owner);
   QJsonValue val = qx::cvt::to_json(obj);
   QJsonDocument doc = (val.isArray() ? QJsonDocument(val.toArray()) : QJsonDocument(val.toObject()));
   return doc.toJson();
}

template <class T>
inline qx_bool from_byte_array(T & obj, const QByteArray & data, unsigned int flags = 1 /* boost::archive::no_header */)
{
   Q_UNUSED(flags);
   QJsonParseError err;
   QJsonDocument doc = QJsonDocument::fromJson(data, (& err));
   if (err.error != QJsonParseError::NoError)
   { return qx_bool(false, static_cast<long>(err.error), err.errorString()); }
   QJsonValue val = (doc.isArray() ? QJsonValue(doc.array()) : QJsonValue(doc.object()));
   return qx::cvt::from_json(val, obj);
}

template <class T>
inline QString to_string(const T & obj, unsigned int flags = 1 /* boost::archive::no_header */)
{ return QString::fromUtf8(qx::serialization::json::to_byte_array(obj, NULL, flags)); }

template <class T>
inline qx_bool from_string(T & obj, const QString & sString, unsigned int flags = 1 /* boost::archive::no_header */)
{ return qx::serialization::json::from_byte_array(obj, sString.toUtf8(), flags); }

template <class T>
inline qx_bool to_file(const T & obj, const QString & sFileName, unsigned int flags = 1 /* boost::archive::no_header */)
{
   QByteArray data = qx::serialization::json::to_byte_array(obj, NULL, flags);
   QFile file(sFileName);
   if (! file.open(QIODevice::WriteOnly | QIODevice::Truncate))
   { return qx_bool(false, "cannot open file : " + sFileName); }
   file.write(data); file.close();
   return qx_bool(true);
}

template <class T>
inline qx_bool from_file(T & obj, const QString & sFileName, unsigned int flags = 1 /* boost::archive::no_header */)
{
   QFile file(sFileName);
   if (! file.open(QIODevice::ReadOnly))
   { return qx_bool(false, "cannot open file : " + sFileName); }
   QByteArray data = file.readAll(); file.close();
   return qx::serialization::json::from_byte_array(obj, data, flags);
}

template <class T>
inline qx_bool to_file_compressed(const T & obj, const QString & sFileName, unsigned int flags = 1 /* boost::archive::no_header */, int iCompressionLevel = -1)
{
   QByteArray data = qx::serialization::json::to_byte_array(obj, NULL, flags);
   QByteArray compressed = qCompress(data, iCompressionLevel);
   QFile file(sFileName);
   if (! file.open(QIODevice::WriteOnly | QIODevice::Truncate))
   { return qx_bool(false, "cannot open file : " + sFileName); }
   file.write(compressed); file.close();
   return qx_bool(true);
}

template <class T>
inline qx_bool from_file_compressed(T & obj, const QString & sFileName, unsigned int flags = 1 /* boost::archive::no_header */)
{
   QFile file(sFileName);
   if (! file.open(QIODevice::ReadOnly))
   { return qx_bool(false, "cannot open file : " + sFileName); }
   QByteArray data = file.readAll(); file.close();
   QByteArray uncompressed = qUncompress(data);
   return qx::serialization::json::from_byte_array(obj, uncompressed, flags);
}

} // namespace json
} // namespace serialization
} // namespace qx

#endif // _QX_SERIALIZE_QJSON_H_
#endif // _QX_NO_JSON
