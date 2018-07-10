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
   static typename std::conditional<std::is_base_of<V, W>::value, char, int>::type removePtr(const volatile V * const volatile, const volatile W * const volatile);

   static int removePtr(...);
   static B b;
   static D d;

public:

   enum { value = (std::is_pointer<B>::value && std::is_pointer<D>::value && (sizeof(qx::trait::is_ptr_base_of<B, D>::removePtr(b, d)) == sizeof(char))) };

   typedef typename std::conditional<qx::trait::is_ptr_base_of<B, D>::value, std::true_type, std::false_type>::type type;

};

} // namespace trait
} // namespace qx

#endif // _QX_IS_PTR_BASE_OF_H_
