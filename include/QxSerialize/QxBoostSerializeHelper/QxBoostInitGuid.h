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

#ifdef _QX_ENABLE_BOOST_SERIALIZATION
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

#include <QxTraits/get_class_name_primitive.h>

namespace qx {

template <class T>
class QxBoostInitGuid
{

public:

   static inline void init()
   { boost::serialization::singleton< qx::QxBoostInitGuid<T> >::get_mutable_instance().guid(qx::trait::get_class_name<T>::get()); }

private:

   inline void guid(const char * key, std::false_type)
   { Q_UNUSED(key); /* boost::archive::detail::instantiate_ptr_serialization((T *)0, 0, boost::archive::detail::adl_tag()); */ }

   inline void guid(const char * key, std::true_type)
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
#endif // _QX_ENABLE_BOOST_SERIALIZATION
