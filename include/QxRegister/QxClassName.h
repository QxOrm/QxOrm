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

#ifndef _QX_CLASS_NAME_H_
#define _QX_CLASS_NAME_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxClassName.h
 * \author Lionel Marty
 * \ingroup QxRegister
 * \brief Provide a class helper to retrieve the class name under const char * format
 */

#include <QxTraits/get_class_name.h>
#include <QxTraits/is_qx_registered.h>

#include <QxRegister/QxClass.h>

namespace qx {

/*!
 * \ingroup QxRegister
 * \brief qx::QxClassName<T> : class helper to retrieve the class name of type T under const char * format
 */
template <typename T>
class QxClassName
{

public:

   static inline const char * get() { return qxGetClassName<qx::trait::is_qx_registered<T>::value, 0>::get(); }
   static inline const char * get_xml_tag() { return qxGetClassName<qx::trait::is_qx_registered<T>::value, 0>::get_xml_tag(); }

private:

   template <bool bIsQxRegistered /* = false */, int dummy>
   struct qxGetClassName
   {
      static inline const char * get() { return QX_GET_CLASS_NAME_WITH_TYPENAME(T); }
      static inline const char * get_xml_tag() { return QX_GET_CLASS_NAME_XML_TAG_WITH_TYPENAME(T); }
   };

   template <int dummy>
   struct qxGetClassName<true, dummy>
   {
      static inline const char * get() { return qx::QxClass<T>::getSingleton()->getNamePtr(); }
      static inline const char * get_xml_tag() { return qx::QxClass<T>::getSingleton()->getNamePtr(); }
   };

};

} // namespace qx

#endif // _QX_CLASS_NAME_H_
