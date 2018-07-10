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

#ifndef _QX_IS_SMART_PTR_H_
#define _QX_IS_SMART_PTR_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file is_smart_ptr.h
 * \author Lionel Marty
 * \ingroup QxTraits
 * \brief qx::trait::is_smart_ptr<T>::value : return true if T is a smart-pointer of boost, Qt or QxOrm libraries, otherwise return false
 */

#include <QxTraits/is_boost_intrusive_ptr.h>
#include <QxTraits/is_boost_scoped_ptr.h>
#include <QxTraits/is_boost_shared_ptr.h>
#include <QxTraits/is_boost_weak_ptr.h>
#include <QxTraits/is_qt_shared_data_ptr.h>
#include <QxTraits/is_qt_scoped_ptr.h>
#include <QxTraits/is_qt_shared_ptr.h>
#include <QxTraits/is_qt_weak_ptr.h>
#include <QxTraits/is_qx_dao_ptr.h>
#include <QxTraits/is_std_unique_ptr.h>
#include <QxTraits/is_std_shared_ptr.h>
#include <QxTraits/is_std_weak_ptr.h>

namespace qx {
namespace trait {

/*!
 * \ingroup QxTraits
 * \brief qx::trait::is_smart_ptr<T>::value : return true if T is a smart-pointer of boost, Qt or QxOrm libraries, otherwise return false
 */
template <typename T>
struct is_smart_ptr : public std::false_type { ; };

#ifdef _QX_ENABLE_BOOST

template <typename T>
struct is_smart_ptr< boost::shared_ptr<T> > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< boost::shared_ptr<T> & > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< const boost::shared_ptr<T> > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< const boost::shared_ptr<T> & > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< boost::intrusive_ptr<T> > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< boost::intrusive_ptr<T> & > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< const boost::intrusive_ptr<T> > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< const boost::intrusive_ptr<T> & > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< boost::scoped_ptr<T> > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< boost::scoped_ptr<T> & > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< const boost::scoped_ptr<T> > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< const boost::scoped_ptr<T> & > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< boost::weak_ptr<T> > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< boost::weak_ptr<T> & > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< const boost::weak_ptr<T> > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< const boost::weak_ptr<T> & > : public std::true_type { ; };

#endif // _QX_ENABLE_BOOST

#if (QT_VERSION >= 0x040600)

template <typename T>
struct is_smart_ptr< QScopedPointer<T> > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< QScopedPointer<T> & > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< const QScopedPointer<T> > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< const QScopedPointer<T> & > : public std::true_type { ; };

#endif // (QT_VERSION >= 0x040600)

template <typename T>
struct is_smart_ptr< QSharedDataPointer<T> > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< QSharedDataPointer<T> & > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< const QSharedDataPointer<T> > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< const QSharedDataPointer<T> & > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< QSharedPointer<T> > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< QSharedPointer<T> & > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< const QSharedPointer<T> > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< const QSharedPointer<T> & > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< QWeakPointer<T> > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< QWeakPointer<T> & > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< const QWeakPointer<T> > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< const QWeakPointer<T> & > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< qx::dao::ptr<T> > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< qx::dao::ptr<T> & > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< const qx::dao::ptr<T> > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< const qx::dao::ptr<T> & > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< std::shared_ptr<T> > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< std::shared_ptr<T> & > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< const std::shared_ptr<T> > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< const std::shared_ptr<T> & > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< std::unique_ptr<T> > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< std::unique_ptr<T> & > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< const std::unique_ptr<T> > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< const std::unique_ptr<T> & > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< std::weak_ptr<T> > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< std::weak_ptr<T> & > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< const std::weak_ptr<T> > : public std::true_type { ; };

template <typename T>
struct is_smart_ptr< const std::weak_ptr<T> & > : public std::true_type { ; };

} // namespace trait
} // namespace qx

#endif // _QX_IS_SMART_PTR_H_
