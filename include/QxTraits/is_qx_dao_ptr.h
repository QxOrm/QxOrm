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

#ifndef _QX_IS_QX_DAO_PTR_H_
#define _QX_IS_QX_DAO_PTR_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file is_qx_dao_ptr.h
 * \author Lionel Marty
 * \ingroup QxTraits
 * \brief qx::trait::is_qx_dao_ptr<T>::value : return true if T is a qx::dao::ptr<> smart-pointer of QxOrm library, otherwise return false
 */

#include <boost/mpl/if.hpp>
#include <boost/mpl/logical.hpp>

#include <QxDao/QxDaoPointer.h>

namespace qx {
namespace trait {

/*!
 * \ingroup QxTraits
 * \brief qx::trait::is_qx_dao_ptr<T>::value : return true if T is a qx::dao::ptr<> smart-pointer of QxOrm library, otherwise return false
 */
template <typename T>
struct is_qx_dao_ptr : public boost::mpl::false_ { ; };

template <typename T>
struct is_qx_dao_ptr< qx::dao::ptr<T> > : public boost::mpl::true_ { ; };

template <typename T>
struct is_qx_dao_ptr< qx::dao::ptr<T> & > : public boost::mpl::true_ { ; };

template <typename T>
struct is_qx_dao_ptr< const qx::dao::ptr<T> > : public boost::mpl::true_ { ; };

template <typename T>
struct is_qx_dao_ptr< const qx::dao::ptr<T> & > : public boost::mpl::true_ { ; };

} // namespace trait
} // namespace qx

#endif // _QX_IS_QX_DAO_PTR_H_
