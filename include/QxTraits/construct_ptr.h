/****************************************************************************
**
** Copyright (C) 2010 QxOrm France and/or its subsidiary(-ies)
** Contact: QxOrm France Information (contact@qxorm.com)
**
** This file is part of the QxOrm library
**
** Commercial Usage
** Licensees holding valid QxOrm Commercial licenses may use this file in
** accordance with the QxOrm Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and QxOrm France
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file 'license.gpl3.txt' included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html
**
** If you are unsure which license is appropriate for your use, please
** contact the support department at support@qxorm.com
**
****************************************************************************/

#ifndef _QX_CONSTRUCT_PTR_H_
#define _QX_CONSTRUCT_PTR_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/type_traits/is_abstract.hpp>
#include <boost/type_traits/remove_pointer.hpp>

#include <QtCore/qsharedpointer.h>

#if (QT_VERSION >= 0x040600)
#include <QtCore/qscopedpointer.h>
#endif // (QT_VERSION >= 0x040600)

namespace qx {
namespace trait {

template <typename T>
struct construct_ptr
{

private:

   typedef typename boost::remove_pointer<T>::type type_ptr;

public:

   static inline void get(T & t)
   { qx::trait::construct_ptr<T>::new_ptr<boost::is_abstract<type_ptr>::value, 0>::get(t); }

private:

   template <bool isAbstract /* = false */, int dummy>
   struct new_ptr
   { static inline void get(T & t) { t = new type_ptr(); } };

   template <int dummy>
   struct new_ptr<true, dummy>
   { static inline void get(T & t) { Q_UNUSED(t); qDebug("[QxOrm] qx::trait::construct_ptr<T> : %s", "cannot instantiate abstract class"); } };

};

template <typename T>
struct construct_ptr< boost::scoped_ptr<T> >
{ static inline void get(boost::scoped_ptr<T> & t) { t.reset(new T()); } };

template <typename T>
struct construct_ptr< boost::shared_ptr<T> >
{ static inline void get(boost::shared_ptr<T> & t) { t.reset(new T()); } };

template <typename T>
struct construct_ptr< boost::intrusive_ptr<T> >
{ static inline void get(boost::intrusive_ptr<T> & t) { t.reset(new T()); } };

template <typename T>
struct construct_ptr< QSharedPointer<T> >
{ static inline void get(QSharedPointer<T> & t) { t = QSharedPointer<T>(new T()); } };

#if (QT_VERSION >= 0x040600)
template <typename T>
struct construct_ptr< QScopedPointer<T> >
{ static inline void get(QScopedPointer<T> & t) { t = QScopedPointer<T>(new T()); } };
#endif // (QT_VERSION >= 0x040600)

} // namespace trait
} // namespace qx

#endif // _QX_CONSTRUCT_PTR_H_
