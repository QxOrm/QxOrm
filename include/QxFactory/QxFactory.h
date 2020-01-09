/****************************************************************************
**
** https://www.qxorm.com/
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

#include <QtCore/qobject.h>

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

class IxPersistable;
template <class T> class QxClass;

#ifdef _QX_ENABLE_QT_NETWORK
namespace service {
class IxService;
class IxParameter;
} // namespace service
#endif // _QX_ENABLE_QT_NETWORK

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

#ifdef _QX_ENABLE_QT_NETWORK
   virtual qx::any createObject(bool bRawPointer = false) const
   { QxClass<T>::getSingleton(); return qxCreateInstance<std::is_abstract<T>::value, std::is_base_of<qx::IxPersistable, T>::value, std::is_base_of<qx::service::IxService, T>::value, std::is_base_of<qx::service::IxParameter, T>::value, std::is_base_of<QObject, T>::value, 0>::create(bRawPointer); }

   virtual void * createObjectNudePtr() const
   { QxClass<T>::getSingleton(); return qxCreateInstance<std::is_abstract<T>::value, std::is_base_of<qx::IxPersistable, T>::value, std::is_base_of<qx::service::IxService, T>::value, std::is_base_of<qx::service::IxParameter, T>::value, std::is_base_of<QObject, T>::value, 0>::createNudePtr(); }
#else // _QX_ENABLE_QT_NETWORK
   virtual qx::any createObject(bool bRawPointer = false) const
   { QxClass<T>::getSingleton(); return qxCreateInstance<std::is_abstract<T>::value, std::is_base_of<qx::IxPersistable, T>::value, false, false, std::is_base_of<QObject, T>::value, 0>::create(bRawPointer); }

   virtual void * createObjectNudePtr() const
   { QxClass<T>::getSingleton(); return qxCreateInstance<std::is_abstract<T>::value, std::is_base_of<qx::IxPersistable, T>::value, false, false, std::is_base_of<QObject, T>::value, 0>::createNudePtr(); }
#endif // _QX_ENABLE_QT_NETWORK

#ifndef _QX_NO_RTTI
   virtual const std::type_info & typeInfo() const
   { return typeid(T); }
#endif // _QX_NO_RTTI

private:

   template <bool bIsAbstract /* = false */, bool bIsIxPersistable /* = false */, bool bIsIxService /* = false */, bool bIsIxParameter /* = false */, bool bIsQObject /* = false */, int dummy>
   struct qxCreateInstance
   {
      static inline qx::any create(bool bRawPointer)  { if (bRawPointer) { T * p = new T(); return qx::any(p); }; std::shared_ptr<T> ptr = std::make_shared<T>(); return qx::any(ptr); }
      static inline void * createNudePtr()            { return static_cast<void *>(new T()); }
   };

   template <bool bIsIxPersistable, bool bIsIxService, bool bIsIxParameter, bool bIsQObject, int dummy>
   struct qxCreateInstance<true, bIsIxPersistable, bIsIxService, bIsIxParameter, bIsQObject, dummy>
   {
      static inline qx::any create(bool bRawPointer)  { Q_UNUSED(bRawPointer); qDebug(QX_STR_CANNOT_INSTANTIATE_ABSTRACT_CLASS, qx::trait::get_class_name<T>::get()); return qx::any(); }
      static inline void * createNudePtr()            { qDebug(QX_STR_CANNOT_INSTANTIATE_ABSTRACT_CLASS, qx::trait::get_class_name<T>::get()); return NULL; }
   };

   template <bool bIsQObject, int dummy>
   struct qxCreateInstance<false, true, false, false, bIsQObject, dummy>
   {
      static inline qx::any create(bool bRawPointer)  { if (bRawPointer) { T * p = new T(); return qx::any(p); }; std::shared_ptr<T> ptr = std::make_shared<T>(); return qx::any(ptr); }
      static inline void * createNudePtr()            { return static_cast<qx::IxPersistable *>(new T()); }
   };

#ifdef _QX_ENABLE_QT_NETWORK
   template <bool bIsQObject, int dummy>
   struct qxCreateInstance<false, false, true, false, bIsQObject, dummy>
   {
      static inline qx::any create(bool bRawPointer)  { if (bRawPointer) { T * p = new T(); return qx::any(p); }; std::shared_ptr<T> ptr = std::make_shared<T>(); return qx::any(ptr); }
      static inline void * createNudePtr()            { return static_cast<qx::service::IxService *>(new T()); }
   };

   template <bool bIsQObject, int dummy>
   struct qxCreateInstance<false, false, false, true, bIsQObject, dummy>
   {
      static inline qx::any create(bool bRawPointer)  { if (bRawPointer) { T * p = new T(); return qx::any(p); }; std::shared_ptr<T> ptr = std::make_shared<T>(); return qx::any(ptr); }
      static inline void * createNudePtr()            { return static_cast<qx::service::IxParameter *>(new T()); }
   };
#endif // _QX_ENABLE_QT_NETWORK

   template <int dummy>
   struct qxCreateInstance<false, false, false, false, true, dummy>
   {
      static inline qx::any create(bool bRawPointer)  { if (bRawPointer) { T * p = new T(); return qx::any(p); }; std::shared_ptr<T> ptr = std::make_shared<T>(); return qx::any(ptr); }
      static inline void * createNudePtr()            { return static_cast<QObject *>(new T()); }
   };

};

} // namespace qx

#include "../../inl/QxFactory/QxFactory.inl"

#endif // _QX_FACTORY_H_
