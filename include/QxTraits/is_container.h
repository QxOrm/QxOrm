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

#ifndef _QX_IS_CONTAINER_H_
#define _QX_IS_CONTAINER_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file is_container.h
 * \author Lionel Marty
 * \ingroup QxTraits
 * \brief qx::trait::is_container<T>::value : return true if T is a container from stl, boost, Qt or QxOrm library, otherwise return false
 */

#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/logical.hpp>

#include <QxTraits/is_boost_unordered_map.h>
#include <QxTraits/is_boost_unordered_set.h>
#include <QxTraits/is_qt_hash.h>
#include <QxTraits/is_qt_linked_list.h>
#include <QxTraits/is_qt_list.h>
#include <QxTraits/is_qt_map.h>
#include <QxTraits/is_qt_multi_hash.h>
#include <QxTraits/is_qt_multi_map.h>
#include <QxTraits/is_qt_set.h>
#include <QxTraits/is_qt_vector.h>
#include <QxTraits/is_qx_collection.h>
#include <QxTraits/is_std_list.h>
#include <QxTraits/is_std_map.h>
#include <QxTraits/is_std_set.h>
#include <QxTraits/is_std_vector.h>

namespace qx {
namespace trait {

/*!
 * \ingroup QxTraits
 * \brief qx::trait::is_container<T>::value : return true if T is a container from stl, boost, Qt or QxOrm library, otherwise return false
 */
template <typename T>
class is_container
{

private:

   typedef typename boost::mpl::or_< qx::trait::is_boost_unordered_map<T>, 
                                     qx::trait::is_boost_unordered_set<T>, 
                                     qx::trait::is_qt_hash<T>, 
                                     qx::trait::is_qt_linked_list<T> >::type cond_is_container_1;

   typedef typename boost::mpl::or_< typename qx::trait::is_container<T>::cond_is_container_1, 
                                     qx::trait::is_qt_list<T>, 
                                     qx::trait::is_qt_map<T>, 
                                     qx::trait::is_qt_multi_hash<T> >::type cond_is_container_2;

   typedef typename boost::mpl::or_< typename qx::trait::is_container<T>::cond_is_container_2, 
                                     qx::trait::is_qt_multi_map<T>, 
                                     qx::trait::is_qt_set<T>, 
                                     qx::trait::is_qt_vector<T> >::type cond_is_container_3;

   typedef typename boost::mpl::or_< typename qx::trait::is_container<T>::cond_is_container_3, 
                                     qx::trait::is_qx_collection<T>, 
                                     qx::trait::is_std_list<T>, 
                                     qx::trait::is_std_map<T> >::type cond_is_container_4;

   typedef typename boost::mpl::or_< typename qx::trait::is_container<T>::cond_is_container_4, 
                                     qx::trait::is_std_set<T>, 
                                     qx::trait::is_std_vector<T> >::type cond_is_container_5;

   typedef typename boost::mpl::if_< typename qx::trait::is_container<T>::cond_is_container_5, 
                                     boost::mpl::true_, 
                                     boost::mpl::false_ >::type type_is_container;

public:

   enum { value = qx::trait::is_container<T>::type_is_container::value };

   typedef typename qx::trait::is_container<T>::type_is_container type;

};

} // namespace trait
} // namespace qx

#endif // _QX_IS_CONTAINER_H_
