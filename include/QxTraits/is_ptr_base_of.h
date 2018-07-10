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

#ifndef _QX_IS_PTR_BASE_OF_H_
#define _QX_IS_PTR_BASE_OF_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file is_ptr_base_of.h
 * \author Lionel Marty
 * \ingroup QxTraits
 * \brief qx::trait::is_ptr_base_of<B, D>::value : return true if B and D are pointer type and (*B) is a base class of (*D) or if B and D are same type, otherwise return false
 */

#include <boost/mpl/if.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/type_traits/is_pointer.hpp>

namespace qx {
namespace trait {

/*!
 * \ingroup QxTraits
 * \brief qx::trait::is_ptr_base_of<B, D>::value : return true if B and D are pointer type and (*B) is a base class of (*D) or if B and D are same type, otherwise return false
 */
template <typename B, typename D>
class is_ptr_base_of
{

private:

   template <typename V, typename W>
   static typename boost::mpl::if_c<boost::is_base_of<V, W>::value, char, int>::type removePtr(const volatile V * const volatile, const volatile W * const volatile);

   static int removePtr(...);
   static B b;
   static D d;

public:

   enum { value = (boost::is_pointer<B>::value && boost::is_pointer<D>::value && (sizeof(qx::trait::is_ptr_base_of<B, D>::removePtr(b, d)) == sizeof(char))) };

   typedef typename boost::mpl::if_c<qx::trait::is_ptr_base_of<B, D>::value, boost::mpl::true_, boost::mpl::false_>::type type;

};

} // namespace trait
} // namespace qx

#endif // _QX_IS_PTR_BASE_OF_H_
