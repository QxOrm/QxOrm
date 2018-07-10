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

#ifndef _QX_FACTORY_H_
#define _QX_FACTORY_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxFactory.h
 * \author Lionel Marty
 * \ingroup QxFactory
 * \brief Concrete factory class to create object dynamically using the class name
 */

#include <QxFactory/IxFactory.h>

#include <QxTraits/get_base_class.h>
#include <QxTraits/get_class_name.h>
#include <QxTraits/get_primary_key.h>

#define QX_STR_CANNOT_INSTANTIATE_ABSTRACT_CLASS "[QxOrm] qx::QxFactory<T> ---> cannot instantiate abstract class '%s'"

#if _QX_AUTO_REGISTER_REPOSITORY
#define QX_AUTO_REGISTER_REPOSITORY(className, sKey) qx::register_repository< className >(sKey);
#else // _QX_AUTO_REGISTER_REPOSITORY
#define QX_AUTO_REGISTER_REPOSITORY(className, sKey) /* Nothing */
#endif // _QX_AUTO_REGISTER_REPOSITORY

namespace qx {

template <class T>
class QxClass;

#if _QX_AUTO_REGISTER_REPOSITORY
template <class T>
inline void register_repository(const QString & sKey);
#endif // _QX_AUTO_REGISTER_REPOSITORY

/*!
 * \ingroup QxFactory
 * \brief qx::QxFactory<T> : concrete factory class to create object of type T dynamically using the class name
 */
template <class T>
class QxFactory : public IxFactory
{

public:

   QxFactory(const QString & sKey) : IxFactory(sKey) { QX_AUTO_REGISTER_REPOSITORY(T, sKey); }
   virtual ~QxFactory() { ; }

   virtual qx::any createObject() const
   { QxClass<T>::getSingleton(); return qxCreateInstance<std::is_abstract<T>::value, 0>::create(); }

   virtual void * createObjectNudePtr() const
   { QxClass<T>::getSingleton(); return qxCreateInstance<std::is_abstract<T>::value, 0>::createNudePtr(); }

#ifndef _QX_NO_RTTI
   virtual const std::type_info & typeInfo() const
   { return typeid(T); }
#endif // _QX_NO_RTTI

private:

   template <bool bIsAbstract /* = false */, int dummy>
   struct qxCreateInstance
   {
      static inline qx::any create()      { std::shared_ptr<T> ptr; ptr.reset(new T()); return qx::any(ptr); }
      static inline void * createNudePtr()   { return static_cast<void *>(new T()); }
   };

   template <int dummy>
   struct qxCreateInstance<true, dummy>
   {
      static inline qx::any create()      { qDebug(QX_STR_CANNOT_INSTANTIATE_ABSTRACT_CLASS, qx::trait::get_class_name<T>::get()); return qx::any(); }
      static inline void * createNudePtr()   { qDebug(QX_STR_CANNOT_INSTANTIATE_ABSTRACT_CLASS, qx::trait::get_class_name<T>::get()); return NULL; }
   };

};

} // namespace qx

#include "../../inl/QxFactory/QxFactory.inl"

#endif // _QX_FACTORY_H_
