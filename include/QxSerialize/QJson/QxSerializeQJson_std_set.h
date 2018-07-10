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
#ifndef _QX_SERIALIZE_QJSON_STD_SET_H_
#define _QX_SERIALIZE_QJSON_STD_SET_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSerializeQJson_std_set.h
 * \author Lionel Marty
 * \ingroup QxSerialize
 * \brief Provide a Qt QJson serialization method (save/load) for type std::set<T>
 */

#include <QtCore/qjsonvalue.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qjsonarray.h>

#include <set>

#include <QxConvert/QxConvert.h>
#include <QxConvert/QxConvert_Impl.h>

namespace qx {
namespace cvt {
namespace detail {

template <typename T>
struct QxConvert_ToJson< std::set<T> >
{
   static inline QJsonValue toJson(const std::set<T> & t, const QString & format)
   {
      QJsonArray arr;
      typedef typename std::set<T>::const_iterator type_itr;
      for (type_itr itr = t.begin(); itr != t.end(); ++itr)
      { arr.append(qx::cvt::to_json((* itr), format)); }
      return QJsonValue(arr);
   }
};

template <typename T>
struct QxConvert_FromJson< std::set<T> >
{
   static inline qx_bool fromJson(const QJsonValue & j, std::set<T> & t, const QString & format)
   {
      t.clear();
      if (! j.isArray()) { return qx_bool(true); }
      QJsonArray arr = j.toArray();
      for (int i = 0; i < arr.count(); i++)
      { T tmp; qx::cvt::from_json(arr.at(i), tmp, format); t.insert(tmp); }
      return qx_bool(true);
   }
};

} // namespace detail
} // namespace cvt
} // namespace qx

#endif // _QX_SERIALIZE_QJSON_STD_SET_H_
#endif // _QX_NO_JSON
