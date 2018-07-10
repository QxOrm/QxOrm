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
#ifndef _QX_SERIALIZE_QJSON_BOOST_UNORDERED_MAP_H_
#define _QX_SERIALIZE_QJSON_BOOST_UNORDERED_MAP_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSerializeQJson_boost_unordered_map.h
 * \author Lionel Marty
 * \ingroup QxSerialize
 * \brief Provide a Qt QJson serialization method (save/load) for type boost::unordered_map<Key, Value> and boost::unordered_multimap<Key, Value>
 */

#include <QtCore/qjsonvalue.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qjsonarray.h>

#include <boost/unordered_map.hpp>

#include <QxConvert/QxConvert.h>
#include <QxConvert/QxConvert_Impl.h>

namespace qx {
namespace cvt {
namespace detail {

template <typename Key, typename Value>
struct QxConvert_ToJson< boost::unordered_map<Key, Value> >
{
   static inline QJsonValue toJson(const boost::unordered_map<Key, Value> & t, const QString & format)
   {
      typedef typename boost::unordered_map<Key, Value>::const_iterator type_itr;
      QJsonArray arr; QJsonValue val;

      for (type_itr itr = t.begin(); itr != t.end(); ++itr)
      {
         QJsonObject obj;
         val = qx::cvt::to_json(itr->first, format); obj.insert("key", val);
         val = qx::cvt::to_json(itr->second, format); obj.insert("value", val);
         arr.append(obj);
      }

      return QJsonValue(arr);
   }
};

template <typename Key, typename Value>
struct QxConvert_FromJson< boost::unordered_map<Key, Value> >
{
   static inline qx_bool fromJson(const QJsonValue & j, boost::unordered_map<Key, Value> & t, const QString & format)
   {
      t.clear();
      if (! j.isArray()) { return qx_bool(true); }
      QJsonArray arr = j.toArray(); QJsonValue val; QJsonObject obj;
      t.reserve(static_cast<typename boost::unordered_map<Key, Value>::size_type>(arr.count()));

      for (int i = 0; i < arr.count(); i++)
      {
         val = arr.at(i); if (! val.isObject()) { continue; }
         obj = val.toObject(); Key key; Value value;
         qx::cvt::from_json(obj.value("key"), key, format);
         qx::cvt::from_json(obj.value("value"), value, format);
         t.insert(std::make_pair(key, value));
      }

      return qx_bool(true);
   }
};

template <typename Key, typename Value>
struct QxConvert_ToJson< boost::unordered_multimap<Key, Value> >
{
   static inline QJsonValue toJson(const boost::unordered_multimap<Key, Value> & t, const QString & format)
   {
      typedef typename boost::unordered_multimap<Key, Value>::const_iterator type_itr;
      QJsonArray arr; QJsonValue val;

      for (type_itr itr = t.begin(); itr != t.end(); ++itr)
      {
         QJsonObject obj;
         val = qx::cvt::to_json(itr->first, format); obj.insert("key", val);
         val = qx::cvt::to_json(itr->second, format); obj.insert("value", val);
         arr.append(obj);
      }

      return QJsonValue(arr);
   }
};

template <typename Key, typename Value>
struct QxConvert_FromJson< boost::unordered_multimap<Key, Value> >
{
   static inline qx_bool fromJson(const QJsonValue & j, boost::unordered_multimap<Key, Value> & t, const QString & format)
   {
      t.clear();
      if (! j.isArray()) { return qx_bool(true); }
      QJsonArray arr = j.toArray(); QJsonValue val; QJsonObject obj;
      t.reserve(static_cast<typename boost::unordered_multimap<Key, Value>::size_type>(arr.count()));

      for (int i = 0; i < arr.count(); i++)
      {
         val = arr.at(i); if (! val.isObject()) { continue; }
         obj = val.toObject(); Key key; Value value;
         qx::cvt::from_json(obj.value("key"), key, format);
         qx::cvt::from_json(obj.value("value"), value, format);
         t.insert(std::make_pair(key, value));
      }

      return qx_bool(true);
   }
};

template <typename Value>
struct QxConvert_ToJson< boost::unordered_map<QString, Value> >
{
   static inline QJsonValue toJson(const boost::unordered_map<QString, Value> & t, const QString & format)
   {
      typedef typename boost::unordered_map<QString, Value>::const_iterator type_itr;
      QJsonObject obj; QJsonValue val;

      for (type_itr itr = t.begin(); itr != t.end(); ++itr)
      {
         val = qx::cvt::to_json(itr->second, format);
         obj.insert(itr->first, val);
      }

      return QJsonValue(obj);
   }
};

template <typename Value>
struct QxConvert_FromJson< boost::unordered_map<QString, Value> >
{
   static inline qx_bool fromJson(const QJsonValue & j, boost::unordered_map<QString, Value> & t, const QString & format)
   {
      t.clear();
      if (! j.isObject()) { return qx_bool(true); }
      QJsonObject obj = j.toObject(); QJsonValue val;
      t.reserve(static_cast<typename boost::unordered_map<QString, Value>::size_type>(obj.count()));

      for (QJsonObject::const_iterator itr = obj.constBegin(); itr != obj.constEnd(); ++itr)
      {
         QString key = itr.key(); Value value;
         qx::cvt::from_json(itr.value(), value, format);
         t.insert(std::make_pair(key, value));
      }

      return qx_bool(true);
   }
};

template <typename Value>
struct QxConvert_ToJson< boost::unordered_map<std::string, Value> >
{
   static inline QJsonValue toJson(const boost::unordered_map<std::string, Value> & t, const QString & format)
   {
      typedef typename boost::unordered_map<std::string, Value>::const_iterator type_itr;
      QJsonObject obj; QJsonValue val;

      for (type_itr itr = t.begin(); itr != t.end(); ++itr)
      {
#ifndef QT_NO_STL
         QString key = QString::fromStdString(itr->first);
#else // QT_NO_STL
         QString key = QString::fromLatin1(itr->first.data(), int(itr->first.size()));
#endif // QT_NO_STL

         val = qx::cvt::to_json(itr->second, format);
         obj.insert(key, val);
      }

      return QJsonValue(obj);
   }
};

template <typename Value>
struct QxConvert_FromJson< boost::unordered_map<std::string, Value> >
{
   static inline qx_bool fromJson(const QJsonValue & j, boost::unordered_map<std::string, Value> & t, const QString & format)
   {
      t.clear();
      if (! j.isObject()) { return qx_bool(true); }
      QJsonObject obj = j.toObject(); QJsonValue val;
      t.reserve(static_cast<typename boost::unordered_map<std::string, Value>::size_type>(obj.count()));

      for (QJsonObject::const_iterator itr = obj.constBegin(); itr != obj.constEnd(); ++itr)
      {
         QString key = itr.key(); Value value;
         qx::cvt::from_json(itr.value(), value, format);

#ifndef QT_NO_STL
         std::string s = key.toStdString();
#else // QT_NO_STL
         std::string s = key.toLatin1().constData();
#endif // QT_NO_STL

         t.insert(std::make_pair(s, value));
      }

      return qx_bool(true);
   }
};

#if ((! defined(QT_NO_STL)) && (! defined(QT_NO_STL_WCHAR)))

template <typename Value>
struct QxConvert_ToJson< boost::unordered_map<std::wstring, Value> >
{
   static inline QJsonValue toJson(const boost::unordered_map<std::wstring, Value> & t, const QString & format)
   {
      typedef typename boost::unordered_map<std::wstring, Value>::const_iterator type_itr;
      QJsonObject obj; QJsonValue val;

      for (type_itr itr = t.begin(); itr != t.end(); ++itr)
      {
         val = qx::cvt::to_json(itr->second, format);
         obj.insert(QString::fromStdWString(itr->first), val);
      }

      return QJsonValue(obj);
   }
};

template <typename Value>
struct QxConvert_FromJson< boost::unordered_map<std::wstring, Value> >
{
   static inline qx_bool fromJson(const QJsonValue & j, boost::unordered_map<std::wstring, Value> & t, const QString & format)
   {
      t.clear();
      if (! j.isObject()) { return qx_bool(true); }
      QJsonObject obj = j.toObject(); QJsonValue val;
      t.reserve(static_cast<typename boost::unordered_map<std::wstring, Value>::size_type>(obj.count()));

      for (QJsonObject::const_iterator itr = obj.constBegin(); itr != obj.constEnd(); ++itr)
      {
         QString key = itr.key(); Value value;
         qx::cvt::from_json(itr.value(), value, format);
         t.insert(std::make_pair(key.toStdWString(), value));
      }

      return qx_bool(true);
   }
};

#endif // ((! defined(QT_NO_STL)) && (! defined(QT_NO_STL_WCHAR)))

} // namespace detail
} // namespace cvt
} // namespace qx

#endif // _QX_SERIALIZE_QJSON_BOOST_UNORDERED_MAP_H_
#endif // _QX_NO_JSON
