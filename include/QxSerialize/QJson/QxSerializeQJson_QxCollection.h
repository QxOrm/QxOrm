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
#ifndef _QX_SERIALIZE_QJSON_QX_COLLECTION_H_
#define _QX_SERIALIZE_QJSON_QX_COLLECTION_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSerializeQJson_QxCollection.h
 * \author Lionel Marty
 * \ingroup QxSerialize
 * \brief Provide a Qt QJson serialization method (save/load) for type qx::QxCollection<Key, Value>
 */

#include <QtCore/qjsonvalue.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qjsonarray.h>

#include <QxCollection/QxCollection.h>

#include <QxConvert/QxConvert.h>
#include <QxConvert/QxConvert_Impl.h>

namespace qx {
namespace cvt {
namespace detail {

template <typename Key, typename Value>
struct QxConvert_ToJson< qx::QxCollection<Key, Value> >
{
   static inline QJsonValue toJson(const qx::QxCollection<Key, Value> & t, const QString & format)
   {
      QJsonArray arr; QJsonValue val;

      for (long l = 0; l < t.count(); l++)
      {
         QJsonObject obj;
         val = qx::cvt::to_json(t.getKeyByIndex(l), format); obj.insert("key", val);
         val = qx::cvt::to_json(t.getByIndex(l), format); obj.insert("value", val);
         arr.append(obj);
      }

      return QJsonValue(arr);
   }
};

template <typename Key, typename Value>
struct QxConvert_FromJson< qx::QxCollection<Key, Value> >
{
   static inline qx_bool fromJson(const QJsonValue & j, qx::QxCollection<Key, Value> & t, const QString & format)
   {
      t.clear();
      if (! j.isArray()) { return qx_bool(true); }
      QJsonArray arr = j.toArray(); QJsonValue val; QJsonObject obj;
      t.reserve(static_cast<long>(arr.count()));

      for (int i = 0; i < arr.count(); i++)
      {
         val = arr.at(i); if (! val.isObject()) { continue; }
         obj = val.toObject(); Key key; Value value;
         qx::cvt::from_json(obj.value("key"), key, format);
         qx::cvt::from_json(obj.value("value"), value, format);
         t.insert(key, value);
      }

      return qx_bool(true);
   }
};

template <typename Value>
struct QxConvert_ToJson< qx::QxCollection<QString, Value> >
{
   static inline QJsonValue toJson(const qx::QxCollection<QString, Value> & t, const QString & format)
   {
      QJsonObject obj; QJsonValue val;

      for (long l = 0; l < t.count(); l++)
      {
         val = qx::cvt::to_json(t.getByIndex(l), format);
         obj.insert(t.getKeyByIndex(l), val);
      }

      return QJsonValue(obj);
   }
};

template <typename Value>
struct QxConvert_FromJson< qx::QxCollection<QString, Value> >
{
   static inline qx_bool fromJson(const QJsonValue & j, qx::QxCollection<QString, Value> & t, const QString & format)
   {
      t.clear();
      if (! j.isObject()) { return qx_bool(true); }
      QJsonObject obj = j.toObject(); QJsonValue val;
      t.reserve(static_cast<long>(obj.count()));

      for (QJsonObject::const_iterator itr = obj.constBegin(); itr != obj.constEnd(); ++itr)
      {
         QString key = itr.key(); Value value;
         qx::cvt::from_json(itr.value(), value, format);
         t.insert(key, value);
      }

      return qx_bool(true);
   }
};

template <typename Value>
struct QxConvert_ToJson< qx::QxCollection<std::string, Value> >
{
   static inline QJsonValue toJson(const qx::QxCollection<std::string, Value> & t, const QString & format)
   {
      QJsonObject obj; QJsonValue val;

      for (long l = 0; l < t.count(); l++)
      {
#ifndef QT_NO_STL
         QString key = QString::fromStdString(t.getKeyByIndex(l));
#else // QT_NO_STL
         std::string s = t.getKeyByIndex(l);
         QString key = QString::fromLatin1(s.data(), int(s.size()));
#endif // QT_NO_STL

         val = qx::cvt::to_json(t.getByIndex(l), format);
         obj.insert(key, val);
      }

      return QJsonValue(obj);
   }
};

template <typename Value>
struct QxConvert_FromJson< qx::QxCollection<std::string, Value> >
{
   static inline qx_bool fromJson(const QJsonValue & j, qx::QxCollection<std::string, Value> & t, const QString & format)
   {
      t.clear();
      if (! j.isObject()) { return qx_bool(true); }
      QJsonObject obj = j.toObject(); QJsonValue val;
      t.reserve(static_cast<long>(obj.count()));

      for (QJsonObject::const_iterator itr = obj.constBegin(); itr != obj.constEnd(); ++itr)
      {
         QString key = itr.key(); Value value;
         qx::cvt::from_json(itr.value(), value, format);

#ifndef QT_NO_STL
         std::string s = key.toStdString();
#else // QT_NO_STL
         std::string s = key.toLatin1().constData();
#endif // QT_NO_STL

         t.insert(s, value);
      }

      return qx_bool(true);
   }
};

#if ((! defined(QT_NO_STL)) && (! defined(QT_NO_STL_WCHAR)))

template <typename Value>
struct QxConvert_ToJson< qx::QxCollection<std::wstring, Value> >
{
   static inline QJsonValue toJson(const qx::QxCollection<std::wstring, Value> & t, const QString & format)
   {
      QJsonObject obj; QJsonValue val;

      for (long l = 0; l < t.count(); l++)
      {
         val = qx::cvt::to_json(t.getByIndex(l), format);
         obj.insert(QString::fromStdWString(t.getKeyByIndex(l)), val);
      }

      return QJsonValue(obj);
   }
};

template <typename Value>
struct QxConvert_FromJson< qx::QxCollection<std::wstring, Value> >
{
   static inline qx_bool fromJson(const QJsonValue & j, qx::QxCollection<std::wstring, Value> & t, const QString & format)
   {
      t.clear();
      if (! j.isObject()) { return qx_bool(true); }
      QJsonObject obj = j.toObject(); QJsonValue val;
      t.reserve(static_cast<long>(obj.count()));

      for (QJsonObject::const_iterator itr = obj.constBegin(); itr != obj.constEnd(); ++itr)
      {
         QString key = itr.key(); Value value;
         qx::cvt::from_json(itr.value(), value, format);
         t.insert(key.toStdWString(), value);
      }

      return qx_bool(true);
   }
};

#endif // ((! defined(QT_NO_STL)) && (! defined(QT_NO_STL_WCHAR)))

} // namespace detail
} // namespace cvt
} // namespace qx

#endif // _QX_SERIALIZE_QJSON_QX_COLLECTION_H_
#endif // _QX_NO_JSON
