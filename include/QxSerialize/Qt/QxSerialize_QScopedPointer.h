/****************************************************************************
**
** https://www.qxorm.com/
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
#if (QT_VERSION >= 0x040600)
#ifndef _QX_SERIALIZE_QSCOPEDPOINTER_H_
#define _QX_SERIALIZE_QSCOPEDPOINTER_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/nvp.hpp>

#include <QtCore/qscopedpointer.h>

namespace boost {
namespace serialization {

template <class Archive, typename T>
inline void save(Archive & ar, const QScopedPointer<T> & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   const T * ptr = t.data();
   ar << boost::serialization::make_nvp("qt_scoped_ptr", ptr);
}

template <class Archive, typename T>
inline void load(Archive & ar, QScopedPointer<T> & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   T * ptr = NULL;
   ar >> boost::serialization::make_nvp("qt_scoped_ptr", ptr);
   t.reset(ptr);
}

template <class Archive, typename T>
inline void serialize(Archive & ar, QScopedPointer<T> & t, const unsigned int file_version)
{
   boost::serialization::split_free(ar, t, file_version);
}

} // namespace boost
} // namespace serialization

#endif // _QX_SERIALIZE_QSCOPEDPOINTER_H_
#endif // (QT_VERSION >= 0x040600)
#endif // _QX_ENABLE_BOOST_SERIALIZATION
