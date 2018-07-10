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

#ifndef _QX_SERIALIZE_QX_DAO_POINTER_H_
#define _QX_SERIALIZE_QX_DAO_POINTER_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/nvp.hpp>

#include <QxDao/QxDaoPointer.h>

namespace boost {
namespace serialization {

template <class Archive, typename T>
inline void save(Archive & ar, const qx::dao::ptr<T> & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   const T * ptr = t.data();
   const T * original = t.dataOriginal();
   ar << boost::serialization::make_nvp("qx_dao_ptr", ptr);
   ar << boost::serialization::make_nvp("qx_dao_ptr_original", original);
}

template <class Archive, typename T>
inline void load(Archive & ar, qx::dao::ptr<T> & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   T * ptr = NULL; T * original = NULL;
   ar >> boost::serialization::make_nvp("qx_dao_ptr", ptr);
   ar >> boost::serialization::make_nvp("qx_dao_ptr_original", original);
   t = qx::dao::ptr<T>(ptr, original);
}

template <class Archive, typename T>
inline void serialize(Archive & ar, qx::dao::ptr<T> & t, const unsigned int file_version)
{
   boost::serialization::split_free(ar, t, file_version);
}

} // namespace boost
} // namespace serialization

#endif // _QX_SERIALIZE_QX_DAO_POINTER_H_
