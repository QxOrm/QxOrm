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

#ifndef _QX_SERIALIZE_INVOKER_H_
#define _QX_SERIALIZE_INVOKER_H_

#ifdef _MSC_VER
#pragma once
#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4996)
#pragma warning(disable:4094)
#endif // _MSC_VER

#include <boost/mpl/if.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/static_assert.hpp>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/nvp.hpp>

#include <QxTraits/get_base_class.h>
#include <QxTraits/is_qx_registered.h>

#include <QxRegister/QxClass.h>

namespace qx {
namespace serialization {
namespace detail {

template <class Base>
struct base_class
{
   template <class Archive, class T>
   static inline void save(Archive & ar, const T & t, const unsigned int file_version)
   {
      Q_UNUSED(file_version);
      BOOST_STATIC_ASSERT(qx::trait::is_qx_registered<T>::value);
      const char * sTag = QxClass<Base>::getSingleton()->getNamePtr();
      ar << boost::serialization::make_nvp(sTag, boost::serialization::base_object<const Base>(t));
   }
   template <class Archive, class T>
   static inline void load(Archive & ar, T & t, const unsigned int file_version)
   {
      Q_UNUSED(file_version);
      BOOST_STATIC_ASSERT(qx::trait::is_qx_registered<T>::value);
      const char * sTag = QxClass<Base>::getSingleton()->getNamePtr();
      ar >> boost::serialization::make_nvp(sTag, boost::serialization::base_object<Base>(t));
   }
};

template <>
struct base_class<qx::trait::no_base_class_defined>
{
   template <class Archive, class T>
   static inline void save(Archive & ar, const T & t, const unsigned int file_version)
   { Q_UNUSED(ar); Q_UNUSED(t); Q_UNUSED(file_version); }
   template <class Archive, class T>
   static inline void load(Archive & ar, T & t, const unsigned int file_version)
   { Q_UNUSED(ar); Q_UNUSED(t); Q_UNUSED(file_version); }
};

template <class Archive, class T>
void save(Archive & ar, const T & t, const unsigned int file_version)
{
   typedef typename qx::trait::get_base_class<T>::type qx_type_base_class_tmp;
   qx::serialization::detail::base_class<qx_type_base_class_tmp>::save(ar, t, file_version);
   QxClass<T>::getSingleton()->dataMemberX()->toArchive(& t, ar, file_version);
}

template <class Archive, class T>
void load(Archive & ar, T & t, const unsigned int file_version)
{
   typedef typename qx::trait::get_base_class<T>::type qx_type_base_class_tmp;
   qx::serialization::detail::base_class<qx_type_base_class_tmp>::load(ar, t, file_version);
   QxClass<T>::getSingleton()->dataMemberX()->fromArchive(& t, ar, file_version);
}

template <class Archive, class T>
struct saver
{
   static inline void invoke(Archive & ar, const T & t, const unsigned int file_version)
   { qx::serialization::detail::save(ar, t, file_version); }
};

template <class Archive, class T>
struct loader
{
   static inline void invoke(Archive & ar, T & t, const unsigned int file_version)
   { qx::serialization::detail::load(ar, t, file_version); }
};

} // namespace detail
} // namespace serialization
} // namespace qx

#include "../../inl/QxSerialize/QxSerializeInvoker.inl"

#ifdef _MSC_VER
#pragma warning(pop)
#endif // _MSC_VER

#endif // _QX_SERIALIZE_INVOKER_H_
