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

#ifndef _QX_GET_PRIMARY_KEY_H_
#define _QX_GET_PRIMARY_KEY_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file get_primary_key.h
 * \author Lionel Marty
 * \ingroup QxTraits
 * \brief qx::trait::get_primary_key<T>::type : return primary key type of T, by default primary key is long type, use QX_REGISTER_PRIMARY_KEY() macro to register another type (for example QX_REGISTER_PRIMARY_KEY(T, QString))
 */

namespace qx {
namespace trait {

/*!
 * \ingroup QxTraits
 * \brief qx::trait::get_primary_key<T>::type : return primary key type of T, by default primary key is long type, use QX_REGISTER_PRIMARY_KEY() macro to register another type (for example QX_REGISTER_PRIMARY_KEY(T, QString))
 */
template <class T>
class get_primary_key
{ public: typedef long type; };

} // namespace trait
} // namespace qx

#define QX_REGISTER_PRIMARY_KEY(daoClass, primaryKey) \
namespace qx { namespace trait { \
template <> \
class get_primary_key< daoClass > \
{ public: typedef primaryKey type; }; \
} } // namespace qx::trait

#endif // _QX_GET_PRIMARY_KEY_H_
