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

#ifndef _QX_SERIALIZE_QDATASTREAM_QX_REGISTERED_CLASS_H_
#define _QX_SERIALIZE_QDATASTREAM_QX_REGISTERED_CLASS_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSerializeQDataStream_qx_registered_class.h
 * \author Lionel Marty
 * \ingroup QxSerialize
 * \brief Provide a generic Qt QDataStream serialization method (save/load) for classes registered into QxOrm context (void qx::register_class<MyClass>() function), it is possible to specialize qx::QxSerializeRegistered<T> template to implement your own serialization method for a specific class
 */

#include <QtCore/qdatastream.h>

#include <QxTraits/is_qx_registered.h>

#include <QxRegister/IxClass.h>
#include <QxRegister/QxClass.h>

namespace qx {

struct QX_DLL_EXPORT QxSerializeRegistered_Helper
{

   static QDataStream & save(QDataStream & stream, IxClass * pClass, const void * pOwner);
   static QDataStream & load(QDataStream & stream, IxClass * pClass, void * pOwner);

private:

   static void saveHelper(QDataStream & stream, IxClass * pClass, const void * pOwner);
   static void loadHelper(QDataStream & stream, IxClass * pClass, void * pOwner);

};

template <typename T>
struct QxSerializeRegistered
{

   enum { is_valid = qx::trait::is_qx_registered<T>::value };

   static QDataStream & save(QDataStream & stream, const T & t)
   {
      BOOST_STATIC_ASSERT(is_valid);
      return qx::QxSerializeRegistered_Helper::save(stream, qx::QxClass<T>::getSingleton(), (& t));
   }

   static QDataStream & load(QDataStream & stream, T & t)
   {
      BOOST_STATIC_ASSERT(is_valid);
      return qx::QxSerializeRegistered_Helper::load(stream, qx::QxClass<T>::getSingleton(), (& t));
   }

};

} // namespace qx

#endif // _QX_SERIALIZE_QDATASTREAM_QX_REGISTERED_CLASS_H_
