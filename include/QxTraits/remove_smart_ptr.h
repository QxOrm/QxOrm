/****************************************************************************
**
** http://www.qxorm.com/
** http://sourceforge.net/projects/qxorm/
** Original file by Lionel Marty
**
** This file is part of the QxOrm library
**
** This software is provided 'as-is', without any express or implied
** warranty. In no event will the authors be held liable for any
** damages arising from the use of this software.
**
** GNU Lesser General Public License Usage
** This file must be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file 'license.lgpl.txt' included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you have questions regarding the use of this file, please contact :
** contact@qxorm.com
**
****************************************************************************/

#ifndef _QX_REMOVE_SMART_PTR_H_
#define _QX_REMOVE_SMART_PTR_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/intrusive_ptr.hpp>

#include <QtCore/qsharedpointer.h>

#if (QT_VERSION >= 0x040600)
#include <QtCore/qscopedpointer.h>
#endif // (QT_VERSION >= 0x040600)

namespace qx {
namespace trait {

template <typename T>
struct remove_smart_ptr { typedef T type; };

template <typename T>
struct remove_smart_ptr< boost::scoped_ptr<T> > { typedef T type; };

template <typename T>
struct remove_smart_ptr< boost::shared_ptr<T> > { typedef T type; };

template <typename T>
struct remove_smart_ptr< boost::intrusive_ptr<T> > { typedef T type; };

template <typename T>
struct remove_smart_ptr< QSharedPointer<T> > { typedef T type; };

#if (QT_VERSION >= 0x040600)
template <typename T>
struct remove_smart_ptr< QScopedPointer<T> > { typedef T type; };
#endif // (QT_VERSION >= 0x040600)

} // namespace trait
} // namespace qx

#endif // _QX_REMOVE_SMART_PTR_H_
