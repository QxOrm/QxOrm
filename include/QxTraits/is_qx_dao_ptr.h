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
class is_qx_dao_ptr
{

private:

   template <typename V> static char isSmartPtr(qx::dao::ptr<V>);
   static int isSmartPtr(...);
   static T t;

public:

   enum { value = (sizeof(qx::trait::is_qx_dao_ptr<T>::isSmartPtr(t)) == sizeof(char)) };

   typedef typename boost::mpl::if_c<qx::trait::is_qx_dao_ptr<T>::value, 
                                     boost::mpl::true_, 
                                     boost::mpl::false_>::type type;

};

} // namespace trait
} // namespace qx

#endif // _QX_IS_QX_DAO_PTR_H_
