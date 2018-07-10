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

#ifndef _QX_IS_PTR_TO_POD_H_
#define _QX_IS_PTR_TO_POD_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file is_ptr_to_pod.h
 * \author Lionel Marty
 * \ingroup QxTraits
 * \brief qx::trait::is_ptr_to_pod<T>::value : return true if T is a pointer to a POD type (char, int, long, etc.), otherwise return false
 */

#include <QxTraits/is_qx_pod.h>

namespace qx {
namespace trait {

/*!
 * \ingroup QxTraits
 * \brief qx::trait::is_ptr_to_pod<T>::value : return true if T is a pointer to a POD type (char, int, long, etc.), otherwise return false
 */
template <typename T>
class is_ptr_to_pod
{

private:

   template <typename U>
   static typename std::conditional<qx::trait::is_qx_pod<U>::value, char, int>::type removePtr(const volatile U * const volatile);

   static int removePtr(...);
   static T t;

public:

   enum { value = (std::is_pointer<T>::value && (sizeof(qx::trait::is_ptr_to_pod<T>::removePtr(t)) == sizeof(char))) };

   typedef typename std::conditional<qx::trait::is_ptr_to_pod<T>::value, std::true_type, std::false_type>::type type;

};

} // namespace trait
} // namespace qx

#endif // _QX_IS_PTR_TO_POD_H_
