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

#ifndef _QX_BOOST_INIT_GUID_H_
#define _QX_BOOST_INIT_GUID_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/serialization/singleton.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/type_info_implementation.hpp>
#include <boost/archive/detail/register_archive.hpp>
#include <boost/mpl/bool.hpp>

#include "../../../include/QxTraits/get_class_name_primitive.h"

namespace qx {

template <class T>
class QxBoostInitGuid
{

public:

   static inline void init()
   { boost::serialization::singleton< qx::QxBoostInitGuid<T> >::get_mutable_instance().guid(qx::trait::get_class_name<T>::get()); }

private:

   inline void guid(const char * key, boost::mpl::false_)
   { Q_UNUSED(key); /* boost::archive::detail::instantiate_ptr_serialization((T *)0, 0, boost::archive::detail::adl_tag()); */ }

   inline void guid(const char * key, boost::mpl::true_)
   { Q_UNUSED(key); }

   inline void guid(const char * key)
   {
      qAssert(NULL != key);
      boost::serialization::singleton< typename boost::serialization::type_info_implementation<T>::type >::get_mutable_instance().key_register(key);
      guid(key, boost::serialization::is_abstract<T>());
   }

};

} // namespace qx

#endif // _QX_BOOST_INIT_GUID_H_
