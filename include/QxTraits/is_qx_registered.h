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

#ifndef _QX_IS_QX_REGISTERED_H_
#define _QX_IS_QX_REGISTERED_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file is_qx_registered.h
 * \author Lionel Marty
 * \ingroup QxTraits
 * \brief qx::trait::is_qx_registered<T>::value : return true if T is registered into QxOrm context to provide persitence (ORM), serialization and introspection features
 */

namespace qx {
namespace trait {

/*!
 * \ingroup QxTraits
 * \brief qx::trait::is_qx_registered<T>::value : return true if T is registered into QxOrm context to provide persitence (ORM), serialization and introspection features
 */
template <typename T>
struct is_qx_registered { enum { value = false }; };

} // namespace trait
} // namespace qx

#define QX_SET_REGISTERED(className) \
namespace qx { namespace trait { \
template <> \
struct is_qx_registered< className > { enum { value = true }; }; \
} } // namespace qx::trait

#endif // _QX_IS_QX_REGISTERED_H_
