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

#ifndef _QX_SERIALIZE_QPAIR_H_
#define _QX_SERIALIZE_QPAIR_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/nvp.hpp>

#include <QtCore/qpair.h>

namespace boost {
namespace serialization {

template <class Archive, typename T1, typename T2>
inline void serialize(Archive & ar, QPair<T1, T2> & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   ar & boost::serialization::make_nvp("first", t.first);
   ar & boost::serialization::make_nvp("second", t.second);
}

} // namespace boost
} // namespace serialization

#endif // _QX_SERIALIZE_QPAIR_H_
