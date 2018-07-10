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

#ifndef _QX_SERIALIZE_QLIST_H_
#define _QX_SERIALIZE_QLIST_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/nvp.hpp>

#include <QtCore/qlist.h>

namespace boost {
namespace serialization {

template <class Archive, typename T>
inline void save(Archive & ar, const QList<T> & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   long lCount = t.count();
   ar << boost::serialization::make_nvp("count", lCount);

   for (long l = 0; l < lCount; l++)
      ar << boost::serialization::make_nvp("item", t.at(l));
}

template <class Archive, typename T>
inline void load(Archive & ar, QList<T> & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   long lCount = 0;
   ar >> boost::serialization::make_nvp("count", lCount);

   t.clear();
   T item;

   for (long l = 0; l < lCount; l++)
   {
      ar >> boost::serialization::make_nvp("item", item);
      t.append(item);
   }
}

template <class Archive, typename T>
inline void serialize(Archive & ar, QList<T> & t, const unsigned int file_version)
{
   boost::serialization::split_free(ar, t, file_version);
}

} // namespace boost
} // namespace serialization

#endif // _QX_SERIALIZE_QLIST_H_
