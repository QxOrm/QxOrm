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

#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/logical.hpp>

#include <QxTraits/is_boost_intrusive_ptr.h>
#include <QxTraits/is_boost_scoped_ptr.h>
#include <QxTraits/is_boost_shared_ptr.h>
#include <QxTraits/is_boost_weak_ptr.h>
#include <QxTraits/is_qt_shared_data_ptr.h>
#include <QxTraits/is_qt_scoped_ptr.h>
#include <QxTraits/is_qt_shared_ptr.h>
#include <QxTraits/is_qt_weak_ptr.h>
#include <QxTraits/is_qx_dao_ptr.h>

namespace qx {
namespace trait {

/*!
 * \ingroup QxTraits
 * \brief qx::trait::is_smart_ptr<T>::value : return true if T is a smart-pointer of boost, Qt or QxOrm libraries, otherwise return false
 */
template <typename T>
class is_smart_ptr
{

private:

   typedef typename boost::mpl::or_< qx::trait::is_qx_dao_ptr<T>, 
                                     qx::trait::is_boost_intrusive_ptr<T>, 
                                     qx::trait::is_boost_scoped_ptr<T>, 
                                     qx::trait::is_boost_shared_ptr<T>, 
                                     qx::trait::is_boost_weak_ptr<T> >::type cond_is_boost_smart_ptr;

   typedef typename boost::mpl::or_< typename qx::trait::is_smart_ptr<T>::cond_is_boost_smart_ptr, 
                                     qx::trait::is_qt_scoped_ptr<T>, 
                                     qx::trait::is_qt_shared_ptr<T>, 
                                     qx::trait::is_qt_weak_ptr<T>, 
                                     qx::trait::is_qt_shared_data_ptr<T> >::type cond_is_smart_ptr;

   typedef typename boost::mpl::if_< typename qx::trait::is_smart_ptr<T>::cond_is_smart_ptr, 
                                     boost::mpl::true_, 
                                     boost::mpl::false_ >::type type_is_smart_ptr;

public:

   enum { value = qx::trait::is_smart_ptr<T>::type_is_smart_ptr::value };

   typedef typename qx::trait::is_smart_ptr<T>::type_is_smart_ptr type;

};

} // namespace trait
} // namespace qx

#endif // _QX_IS_SMART_PTR_H_
