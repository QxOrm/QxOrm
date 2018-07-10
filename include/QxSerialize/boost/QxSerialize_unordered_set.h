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
#ifndef _QX_SERIALIZATION_BOOST_UNORDERED_SET_H_
#define _QX_SERIALIZATION_BOOST_UNORDERED_SET_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/collections_save_imp.hpp>
#include <boost/serialization/collections_load_imp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/nvp.hpp>

namespace boost {
namespace serialization {

#if (BOOST_VERSION > 105700)

template <class Archive, class Key>
inline void save(Archive & ar, const boost::unordered_set<Key> & t, const unsigned int /* file_version */)
{
   long lSize = static_cast<long>(t.size());
   ar << boost::serialization::make_nvp("size", lSize);

   typedef typename boost::unordered_set<Key>::const_iterator type_itr;
   for (type_itr itr = t.begin(); itr != t.end(); ++itr)
   { ar << boost::serialization::make_nvp("item", (* itr)); }
}

template <class Archive, class Key>
inline void load(Archive & ar, boost::unordered_set<Key> & t, const unsigned int /* file_version */)
{
   long lSize = 0;
   ar >> boost::serialization::make_nvp("size", lSize);

   t.clear();
   t.reserve(lSize);

   for (long l = 0; l < lSize; l++)
   {
      Key item;
      ar >> boost::serialization::make_nvp("item", item);
      t.insert(item);
   }
}

#else // (BOOST_VERSION > 105700)

template <class Archive, class Key>
inline void save(Archive & ar, const boost::unordered_set<Key> & t, const unsigned int /* file_version */)
{
   boost::serialization::stl::save_collection< Archive, boost::unordered_set<Key> >(ar, t);
}

template <class Archive, class Key>
inline void load(Archive & ar, boost::unordered_set<Key> & t, const unsigned int /* file_version */)
{
   boost::serialization::stl::load_collection< Archive, boost::unordered_set<Key>,
      boost::serialization::stl::archive_input_set< Archive, boost::unordered_set<Key> >,
      boost::serialization::stl::no_reserve_imp<boost::unordered_set< Key > > >(ar, t);
}

#endif // (BOOST_VERSION > 105700)

template <class Archive, class Key>
inline void serialize(Archive & ar, boost::unordered_set<Key> & t, const unsigned int file_version)
{
   boost::serialization::split_free(ar, t, file_version);
}

#if (BOOST_VERSION > 105700)

template <class Archive, class Key>
inline void save(Archive & ar, const boost::unordered_multiset<Key> & t, const unsigned int /* file_version */)
{
   long lSize = static_cast<long>(t.size());
   ar << boost::serialization::make_nvp("size", lSize);

   typedef typename boost::unordered_multiset<Key>::const_iterator type_itr;
   for (type_itr itr = t.begin(); itr != t.end(); ++itr)
   { ar << boost::serialization::make_nvp("item", (* itr)); }
}

template <class Archive, class Key>
inline void load(Archive & ar, boost::unordered_multiset<Key> & t, const unsigned int /* file_version */)
{
   long lSize = 0;
   ar >> boost::serialization::make_nvp("size", lSize);

   t.clear();
   t.reserve(lSize);

   for (long l = 0; l < lSize; l++)
   {
      Key item;
      ar >> boost::serialization::make_nvp("item", item);
      t.insert(item);
   }
}

#else // (BOOST_VERSION > 105700)

template <class Archive, class Key>
inline void save(Archive & ar, const boost::unordered_multiset<Key> & t, const unsigned int /* file_version */)
{
   boost::serialization::stl::save_collection< Archive, boost::unordered_multiset<Key> >(ar, t);
}

template <class Archive, class Key>
inline void load(Archive & ar, boost::unordered_multiset<Key> & t, const unsigned int /* file_version */)
{
#if (BOOST_VERSION >= 104200)
   boost::serialization::stl::load_collection< Archive, boost::unordered_multiset<Key>,
      boost::serialization::stl::archive_input_set< Archive, boost::unordered_multiset<Key> >,
      boost::serialization::stl::no_reserve_imp< boost::unordered_multiset<Key> > >(ar, t);
#else // (BOOST_VERSION >= 104200)
   boost::serialization::stl::load_collection< Archive, boost::unordered_multiset<Key>,
      boost::serialization::stl::archive_input_multiset< Archive, boost::unordered_multiset<Key> >,
      boost::serialization::stl::no_reserve_imp< boost::unordered_multiset<Key> > >(ar, t);
#endif // (BOOST_VERSION >= 104200)
}

#endif // (BOOST_VERSION > 105700)

template <class Archive, class Key>
inline void serialize(Archive & ar, boost::unordered_multiset<Key> & t, const unsigned int file_version)
{
   boost::serialization::split_free(ar, t, file_version);
}

} // namespace serialization
} // namespace boost

#endif // _QX_SERIALIZATION_BOOST_UNORDERED_SET_H_
#endif // _QX_ENABLE_BOOST_SERIALIZATION
