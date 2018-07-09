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
