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

#ifndef _QX_CONSTRUCT_PTR_H_
#define _QX_CONSTRUCT_PTR_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file construct_ptr.h
 * \author Lionel Marty
 * \ingroup QxTraits
 * \brief qx::trait::construct_ptr<T>::get(T & t) : instantiate a new pointer, support both nude-pointer and smart-pointer of boost, Qt and QxOrm libraries
 */

#include <QtCore/qsharedpointer.h>

#if (QT_VERSION >= 0x040600)
#include <QtCore/qscopedpointer.h>
#endif // (QT_VERSION >= 0x040600)

#include <QxDao/QxDaoPointer.h>

namespace qx {
namespace trait {

/*!
 * \ingroup QxTraits
 * \brief qx::trait::construct_ptr<T>::get(T & t) : instantiate a new pointer, support both nude-pointer and smart-pointer of boost, Qt and QxOrm libraries
 */
template <typename T>
struct construct_ptr
{

private:

   typedef typename std::remove_pointer<T>::type type_ptr;

public:

   static inline void get(T & t)
   { new_ptr<std::is_abstract<type_ptr>::value, 0>::get(t); }

private:

   template <bool isAbstract /* = false */, int dummy>
   struct new_ptr
   { static inline void get(T & t) { t = new type_ptr(); } };

   template <int dummy>
   struct new_ptr<true, dummy>
   { static inline void get(T & t) { Q_UNUSED(t); qDebug("[QxOrm] qx::trait::construct_ptr<T> : %s", "cannot instantiate abstract class"); } };

};

#ifdef _QX_ENABLE_BOOST

template <typename T>
struct construct_ptr< boost::scoped_ptr<T> >
{ static inline void get(boost::scoped_ptr<T> & t) { t.reset(new T()); } };

template <typename T>
struct construct_ptr< boost::shared_ptr<T> >
{ static inline void get(boost::shared_ptr<T> & t) { t.reset(new T()); } };

template <typename T>
struct construct_ptr< boost::intrusive_ptr<T> >
{ static inline void get(boost::intrusive_ptr<T> & t) { t.reset(new T()); } };

#endif // _QX_ENABLE_BOOST

template <typename T>
struct construct_ptr< QSharedPointer<T> >
{ static inline void get(QSharedPointer<T> & t) { t = QSharedPointer<T>(new T()); } };

#if (QT_VERSION >= 0x040600)
template <typename T>
struct construct_ptr< QScopedPointer<T> >
{ static inline void get(QScopedPointer<T> & t) { t = QScopedPointer<T>(new T()); } };
#endif // (QT_VERSION >= 0x040600)

template <typename T>
struct construct_ptr< qx::dao::ptr<T> >
{ static inline void get(qx::dao::ptr<T> & t) { t = qx::dao::ptr<T>(new T()); } };

template <typename T>
struct construct_ptr< std::unique_ptr<T> >
{ static inline void get(std::unique_ptr<T> & t) { t.reset(new T()); } };

template <typename T>
struct construct_ptr< std::shared_ptr<T> >
{ static inline void get(std::shared_ptr<T> & t) { t.reset(new T()); } };

} // namespace trait
} // namespace qx

#endif // _QX_CONSTRUCT_PTR_H_
