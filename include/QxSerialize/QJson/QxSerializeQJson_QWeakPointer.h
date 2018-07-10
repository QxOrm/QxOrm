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
#ifndef _QX_SERIALIZE_QJSON_QWEAKPOINTER_H_
#define _QX_SERIALIZE_QJSON_QWEAKPOINTER_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSerializeQJson_QWeakPointer.h
 * \author Lionel Marty
 * \ingroup QxSerialize
 * \brief Provide a Qt QJson serialization method (save/load) for type QWeakPointer<T>
 */

#include <QtCore/qjsonvalue.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qjsonarray.h>
#include <QtCore/QWeakPointer>

#include <QxConvert/QxConvert.h>
#include <QxConvert/QxConvert_Impl.h>

#include <QxSerialize/QJson/QxSerializeQJson_QSharedPointer.h>

namespace qx {
namespace cvt {
namespace detail {

template <typename T>
struct QxConvert_ToJson< QWeakPointer<T> >
{
   static inline QJsonValue toJson(const QWeakPointer<T> & t, const QString & format)
   {
      QSharedPointer<T> ptr = t.toStrongRef();
      return qx::cvt::to_json(ptr, format);
   }
};

template <typename T>
struct QxConvert_FromJson< QWeakPointer<T> >
{
   static inline qx_bool fromJson(const QJsonValue & j, QWeakPointer<T> & t, const QString & format)
   {
      QSharedPointer<T> ptr;
      qx::cvt::from_json(j, ptr, format);
      t = QWeakPointer<T>(ptr);
      return qx_bool(true);
   }
};

} // namespace detail
} // namespace cvt
} // namespace qx

#endif // _QX_SERIALIZE_QJSON_QWEAKPOINTER_H_
#endif // _QX_NO_JSON
