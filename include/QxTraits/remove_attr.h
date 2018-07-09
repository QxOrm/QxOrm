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

#ifndef _QX_REMOVE_ATTR_H_
#define _QX_REMOVE_ATTR_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/mpl/if.hpp>
#include <boost/mpl/logical.hpp>

#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_volatile.hpp>

namespace qx {
namespace trait {

template <typename T, bool bRemovePtr = true, bool bRemoveConst = true, bool bRemoveRef = true, bool bRemoveVolatile = true>
class remove_attr
{

private:

   typedef typename boost::mpl::if_c<bRemovePtr, typename boost::remove_pointer<T>::type, T>::type type_1;
   typedef typename boost::mpl::if_c<bRemoveConst, typename boost::remove_const<type_1>::type, type_1>::type type_2;
   typedef typename boost::mpl::if_c<bRemoveRef, typename boost::remove_reference<type_2>::type, type_2>::type type_3;
   typedef typename boost::mpl::if_c<bRemoveVolatile, typename boost::remove_volatile<type_3>::type, type_3>::type type_4;

public:

   typedef type_4 type;

};

} // namespace trait
} // namespace qx

#endif // _QX_REMOVE_ATTR_H_
