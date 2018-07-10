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

#ifndef _QX_FACTORY_X_H_
#define _QX_FACTORY_X_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxFactoryX.h
 * \author Lionel Marty
 * \ingroup QxFactory
 * \brief List of all classes registered with QxOrm library factory pattern to create object instance dynamically using the class name
 */

#include <QtCore/qhash.h>
#include <QtCore/qmutex.h>

#include <QxFactory/IxFactory.h>

#include <QxSingleton/QxSingleton.h>

namespace qx {

inline qx::any create(const QString & sKey);
template <typename T> inline T * create_nude_ptr(const QString & sKey);
inline void * create_void_ptr(const QString & sKey);

class QxClassX;

/*!
 * \ingroup QxFactory
 * \brief qx::QxFactoryX : list of all classes registered with QxOrm library factory pattern to create object instance dynamically using the class name
 */
class QX_DLL_EXPORT QxFactoryX : public QxSingleton<QxFactoryX>
{

   friend class QxClassX;
   friend class IxFactory;
   friend class QxSingleton<QxFactoryX>;
   friend inline qx::any create(const QString & sKey);
   template <typename T> friend inline T * create_nude_ptr(const QString & sKey);
   friend inline void * create_void_ptr(const QString & sKey);

protected:

   QHash<QString, IxFactory *> m_mapFactoryX;   //!< Collection of all 'IxFactory' pointer
   QMutex m_oMutexFactoryX;                     //!< Mutex -> 'QxFactoryX' is thread-safe

private:

   QxFactoryX() : QxSingleton<QxFactoryX>("qx::QxFactoryX") { ; }
   virtual ~QxFactoryX() { ; }

   QHash<QString, IxFactory *> * getAllFactory() { return (& m_mapFactoryX); }

   void registerFactory(const QString & sKey, IxFactory * pFactory);
   void unregisterFactory(const QString & sKey);

   qx::any createObject(const QString & sKey) const;
   void * createObjectNudePtr(const QString & sKey) const;

#ifndef _QX_NO_RTTI
   const std::type_info & typeInfo(const QString & sKey) const;
#endif // _QX_NO_RTTI

   static inline qx::any createInstance(const QString & sKey)           { return QxFactoryX::getSingleton()->createObject(sKey); }
   static inline void * createInstanceNudePtr(const QString & sKey)        { return QxFactoryX::getSingleton()->createObjectNudePtr(sKey); }

#ifndef _QX_NO_RTTI
   static inline const std::type_info & getTypeInfo(const QString & sKey)  { return QxFactoryX::getSingleton()->typeInfo(sKey); }
#endif // _QX_NO_RTTI

};

/*!
 * \ingroup QxFactory
 * \brief Return a smart-pointer new instance of object (std::shared_ptr<T>) associated by key sKey using qx::any type (for example : qx::create("drug") return a new instance of smart-pointer drug class into qx::any type)
 */
inline qx::any create(const QString & sKey)
{ return qx::QxFactoryX::createInstance(sKey); }

/*!
 * \ingroup QxFactory
 * \brief Return a nude pointer (be careful with memory leak) of type T associated by key sKey, or return NULL if sKey is not registered into factory engine
 */
template <typename T>
inline T * create_nude_ptr(const QString & sKey)
#ifdef _QX_NO_RTTI
{ return static_cast<T *>(qx::QxFactoryX::createInstanceNudePtr(sKey)); }
#else // _QX_NO_RTTI
{ return dynamic_cast<T *>(static_cast<T *>(qx::QxFactoryX::createInstanceNudePtr(sKey))); }
#endif // _QX_NO_RTTI

/*!
 * \ingroup QxFactory
 * \brief Return a void * pointer (be careful with memory leak) associated by key sKey, or return NULL if sKey is not registered into factory engine
 */
inline void * create_void_ptr(const QString & sKey)
{ return qx::QxFactoryX::createInstanceNudePtr(sKey); }

} // namespace qx

QX_DLL_EXPORT_QX_SINGLETON_HPP(qx::QxFactoryX)

#endif // _QX_FACTORY_X_H_
