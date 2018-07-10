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

#ifndef _QX_REMOVE_SMART_PTR_H_
#define _QX_REMOVE_SMART_PTR_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file remove_smart_ptr.h
 * \author Lionel Marty
 * \ingroup QxTraits
 * \brief qx::trait::remove_smart_ptr<T>::type : return a type without smart-pointer attribute from boost, Qt or QxOrm library
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
 * \brief qx::trait::remove_smart_ptr<T>::type : return a type without smart-pointer attribute from boost, Qt or QxOrm library
 */
template <typename T>
struct remove_smart_ptr { typedef T type; };

#ifdef _QX_ENABLE_BOOST

template <typename T>
struct remove_smart_ptr< boost::scoped_ptr<T> > { typedef T type; };

template <typename T>
struct remove_smart_ptr< boost::shared_ptr<T> > { typedef T type; };

template <typename T>
struct remove_smart_ptr< boost::intrusive_ptr<T> > { typedef T type; };

#endif // _QX_ENABLE_BOOST

template <typename T>
struct remove_smart_ptr< QSharedPointer<T> > { typedef T type; };

#if (QT_VERSION >= 0x040600)
template <typename T>
struct remove_smart_ptr< QScopedPointer<T> > { typedef T type; };
#endif // (QT_VERSION >= 0x040600)

template <typename T>
struct remove_smart_ptr< qx::dao::ptr<T> > { typedef T type; };

template <typename T>
struct remove_smart_ptr< std::unique_ptr<T> > { typedef T type; };

template <typename T>
struct remove_smart_ptr< std::shared_ptr<T> > { typedef T type; };

} // namespace trait
} // namespace qx

#endif // _QX_REMOVE_SMART_PTR_H_
