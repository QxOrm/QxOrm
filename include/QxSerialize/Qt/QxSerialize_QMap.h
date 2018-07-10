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

#ifndef _QX_SERIALIZE_QMAP_H_
#define _QX_SERIALIZE_QMAP_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/utility.hpp>

#include <QtCore/qmap.h>

namespace boost {
namespace serialization {

template <class Archive, typename Key, typename Value>
inline void save(Archive & ar, const QMap<Key, Value> & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   long lCount = t.count();
   ar << boost::serialization::make_nvp("count", lCount);

   QMapIterator<Key, Value> itr(t);
   while (itr.hasNext())
   {
      itr.next();
      std::pair<Key, Value> pair_key_value = std::make_pair(itr.key(), itr.value());
      ar << boost::serialization::make_nvp("item", pair_key_value);
   }
}

template <class Archive, typename Key, typename Value>
inline void load(Archive & ar, QMap<Key, Value> & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   long lCount = 0;
   ar >> boost::serialization::make_nvp("count", lCount);

   t.clear();
   std::pair<Key, Value> pair_key_value;

   for (long l = 0; l < lCount; l++)
   {
      ar >> boost::serialization::make_nvp("item", pair_key_value);
      t.insert(pair_key_value.first, pair_key_value.second);
   }
}

template <class Archive, typename Key, typename Value>
inline void serialize(Archive & ar, QMap<Key, Value> & t, const unsigned int file_version)
{
   boost::serialization::split_free(ar, t, file_version);
}

} // namespace boost
} // namespace serialization

#endif // _QX_SERIALIZE_QMAP_H_
