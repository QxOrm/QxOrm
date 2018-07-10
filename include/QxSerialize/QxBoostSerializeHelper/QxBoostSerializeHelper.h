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

#ifndef _QX_BOOST_SERIALIZE_HELPER_H_
#define _QX_BOOST_SERIALIZE_HELPER_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/type_traits/is_same.hpp>
#include <boost/serialization/void_cast.hpp>

#include "../../../include/QxTraits/get_base_class.h"

#include "../../../include/QxSerialize/QxBoostSerializeHelper/QxBoostInitGuid.h"

namespace qx {

template <class T>
class QxBoostSerializeHelper
{

private:

   typedef T type_derived;
   typedef typename qx::trait::get_base_class<type_derived>::type type_base;

public:

   template <class Archive>
   static inline void register_type_helper(Archive & ar, const T * t)
   { Q_UNUSED(t); ar.template register_type<type_derived>(); }

   static inline void void_cast_register_helper(const T * t)
   { Q_UNUSED(t); QxBoostVoidCastRegisterHelper<boost::is_same<type_base, qx::trait::no_base_class_defined>::value, 0>::helper(); }

   static inline void init_guid(const T * t)
   { Q_UNUSED(t); QxBoostInitGuid<T>::init(); }

private:

   template <bool bNoBaseClass /* = false */, int dummy>
   struct QxBoostVoidCastRegisterHelper
   { static inline void helper() { boost::serialization::void_cast_register(static_cast<type_derived *>(NULL), static_cast<type_base *>(NULL)); } };

   template <int dummy>
   struct QxBoostVoidCastRegisterHelper<true, dummy>
   { static inline void helper() { /* Nothing */ ; } };

};

} // namespace qx

#endif // _QX_BOOST_SERIALIZE_HELPER_H_
