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
#ifndef _QX_SERIALIZE_QJSON_QX_REGISTERED_CLASS_H_
#define _QX_SERIALIZE_QJSON_QX_REGISTERED_CLASS_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSerializeQJson_qx_registered_class.h
 * \author Lionel Marty
 * \ingroup QxSerialize
 * \brief Provide a generic Qt QJson serialization method (save/load) for classes registered into QxOrm context (void qx::register_class<MyClass>() function), it is possible to specialize qx::cvt::detail::QxSerializeJsonRegistered<T> template to implement your own serialization method for a specific class
 */

#include <QtCore/qjsonvalue.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qjsonarray.h>

#include <QxTraits/is_qx_registered.h>

#include <QxRegister/IxClass.h>
#include <QxRegister/QxClass.h>

namespace qx {
namespace cvt {
namespace detail {

struct QX_DLL_EXPORT QxSerializeJsonRegistered_Helper
{

   static QJsonValue save(IxClass * pClass, const void * pOwner, const QString & format);
   static qx_bool load(const QJsonValue & j, IxClass * pClass, void * pOwner, const QString & format);

private:

   static void saveHelper(QJsonObject & obj, IxClass * pClass, const void * pOwner, const QString & format);
   static void loadHelper(const QJsonObject & obj, IxClass * pClass, void * pOwner, const QString & format);

};

template <typename T>
struct QxSerializeJsonRegistered
{

   enum { is_valid = qx::trait::is_qx_registered<T>::value };

   static QJsonValue save(const T & t, const QString & format)
   {
      BOOST_STATIC_ASSERT(is_valid);
      return qx::cvt::detail::QxSerializeJsonRegistered_Helper::save(qx::QxClass<T>::getSingleton(), (& t), format);
   }

   static qx_bool load(const QJsonValue & j, T & t, const QString & format)
   {
      BOOST_STATIC_ASSERT(is_valid);
      return qx::cvt::detail::QxSerializeJsonRegistered_Helper::load(j, qx::QxClass<T>::getSingleton(), (& t), format);
   }

};

} // namespace detail
} // namespace cvt
} // namespace qx

#define QX_JSON_SERIALIZE_ONLY_ID "QX_JSON_SERIALIZE_ONLY_ID"

#endif // _QX_SERIALIZE_QJSON_QX_REGISTERED_CLASS_H_
#endif // _QX_NO_JSON
