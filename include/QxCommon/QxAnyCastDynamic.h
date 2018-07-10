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

#ifndef _QX_ANY_CAST_DYNAMIC_H_
#define _QX_ANY_CAST_DYNAMIC_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxAnyCastDynamic.h
 * \author Lionel Marty
 * \ingroup QxCommon
 * \brief qx::any_cast_dynamic<T>::get() : provides a tool to use qx::any_cast and polymorphism
 */

#include <QtCore/qsharedpointer.h>

#include <QxCommon/QxAny.h>

#include <QxDao/QxDaoPointer.h>

namespace qx {

template <typename T>
struct any_cast_dynamic
{ static T get(const qx::any & a) { return qx::any_cast<T>(a); } };

template <typename T>
struct any_cast_dynamic<T *>
{
   static T * get(const qx::any & a)
   {
      if (a.empty()) { return NULL; }
      qx::any * b = const_cast<qx::any *>(& a);
      T ** t = qx::unsafe_any_cast<T *>(b);
      if (! t) { return NULL; }
      return (* t);
   }
};

#ifdef _QX_ENABLE_BOOST

template <typename T>
struct any_cast_dynamic< boost::shared_ptr<T> >
{
   static boost::shared_ptr<T> get(const qx::any & a)
   {
      if (a.empty()) { return boost::shared_ptr<T>(); }
      qx::any * b = const_cast<qx::any *>(& a);
      boost::shared_ptr<T> * t = qx::unsafe_any_cast< boost::shared_ptr<T> >(b);
      if (! t) { return boost::shared_ptr<T>(); }
      return (* t);
   }
};

#endif // _QX_ENABLE_BOOST

template <typename T>
struct any_cast_dynamic< QSharedPointer<T> >
{
   static QSharedPointer<T> get(const qx::any & a)
   {
      if (a.empty()) { return QSharedPointer<T>(); }
      qx::any * b = const_cast<qx::any *>(& a);
      QSharedPointer<T> * t = qx::unsafe_any_cast< QSharedPointer<T> >(b);
      if (! t) { return QSharedPointer<T>(); }
      return (* t);
   }
};

template <typename T>
struct any_cast_dynamic< qx::dao::ptr<T> >
{
   static qx::dao::ptr<T> get(const qx::any & a)
   {
      if (a.empty()) { return qx::dao::ptr<T>(); }
      qx::any * b = const_cast<qx::any *>(& a);
      qx::dao::ptr<T> * t = qx::unsafe_any_cast< qx::dao::ptr<T> >(b);
      if (! t) { return qx::dao::ptr<T>(); }
      return (* t);
   }
};

template <typename T>
struct any_cast_dynamic< std::shared_ptr<T> >
{
   static std::shared_ptr<T> get(const qx::any & a)
   {
      if (a.empty()) { return std::shared_ptr<T>(); }
      qx::any * b = const_cast<qx::any *>(& a);
      std::shared_ptr<T> * t = qx::unsafe_any_cast< std::shared_ptr<T> >(b);
      if (! t) { return std::shared_ptr<T>(); }
      return (* t);
   }
};

} // namespace qx

#endif // _QX_ANY_CAST_DYNAMIC_H_
