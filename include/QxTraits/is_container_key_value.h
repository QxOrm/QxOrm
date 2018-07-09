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

#ifndef _QX_IS_CONTAINER_KEY_VALUE_H_
#define _QX_IS_CONTAINER_KEY_VALUE_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/logical.hpp>

#include "../../include/QxTraits/is_container.h"

namespace qx {
namespace trait {

template <typename T>
class is_container_key_value
{

private:

   typedef typename boost::mpl::or_< qx::trait::is_boost_unordered_map<T>, 
                                     qx::trait::is_std_map<T>, 
                                     qx::trait::is_qt_map<T>, 
                                     qx::trait::is_qt_hash<T> >::type cond_is_container_key_value_1;

   typedef typename boost::mpl::or_< typename qx::trait::is_container_key_value<T>::cond_is_container_key_value_1, 
                                     qx::trait::is_qt_multi_map<T>, 
                                     qx::trait::is_qt_multi_hash<T>, 
                                     qx::trait::is_qx_collection<T> >::type cond_is_container_key_value_2;

   typedef typename boost::mpl::if_< typename qx::trait::is_container_key_value<T>::cond_is_container_key_value_2, 
                                     boost::mpl::true_, 
                                     boost::mpl::false_ >::type type_is_container_key_value;

public:

   enum { value = (qx::trait::is_container<T>::value && qx::trait::is_container_key_value<T>::type_is_container_key_value::value) };

   typedef typename boost::mpl::if_c<qx::trait::is_container_key_value<T>::value, boost::mpl::true_, boost::mpl::false_>::type type;

};

} // namespace trait
} // namespace qx

#endif // _QX_IS_CONTAINER_KEY_VALUE_H_
