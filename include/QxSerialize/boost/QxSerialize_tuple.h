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

#ifndef _QX_SERIALIZE_BOOST_TUPLE_H_
#define _QX_SERIALIZE_BOOST_TUPLE_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/nvp.hpp>

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/tuple/tuple_io.hpp>

namespace boost {
namespace serialization {

template <class Archive, typename T0, typename T1>
inline void serialize(Archive & ar, boost::tuple<T0, T1> & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   ar & boost::serialization::make_nvp("tuple_1", boost::get<0>(t));
   ar & boost::serialization::make_nvp("tuple_2", boost::get<1>(t));
}

template <class Archive, typename T0, typename T1, typename T2>
inline void serialize(Archive & ar, boost::tuple<T0, T1, T2> & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   ar & boost::serialization::make_nvp("tuple_1", boost::get<0>(t));
   ar & boost::serialization::make_nvp("tuple_2", boost::get<1>(t));
   ar & boost::serialization::make_nvp("tuple_3", boost::get<2>(t));
}

template <class Archive, typename T0, typename T1, typename T2, typename T3>
inline void serialize(Archive & ar, boost::tuple<T0, T1, T2, T3> & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   ar & boost::serialization::make_nvp("tuple_1", boost::get<0>(t));
   ar & boost::serialization::make_nvp("tuple_2", boost::get<1>(t));
   ar & boost::serialization::make_nvp("tuple_3", boost::get<2>(t));
   ar & boost::serialization::make_nvp("tuple_4", boost::get<3>(t));
}

template <class Archive, typename T0, typename T1, typename T2, typename T3, typename T4>
inline void serialize(Archive & ar, boost::tuple<T0, T1, T2, T3, T4> & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   ar & boost::serialization::make_nvp("tuple_1", boost::get<0>(t));
   ar & boost::serialization::make_nvp("tuple_2", boost::get<1>(t));
   ar & boost::serialization::make_nvp("tuple_3", boost::get<2>(t));
   ar & boost::serialization::make_nvp("tuple_4", boost::get<3>(t));
   ar & boost::serialization::make_nvp("tuple_5", boost::get<4>(t));
}

template <class Archive, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
inline void serialize(Archive & ar, boost::tuple<T0, T1, T2, T3, T4, T5> & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   ar & boost::serialization::make_nvp("tuple_1", boost::get<0>(t));
   ar & boost::serialization::make_nvp("tuple_2", boost::get<1>(t));
   ar & boost::serialization::make_nvp("tuple_3", boost::get<2>(t));
   ar & boost::serialization::make_nvp("tuple_4", boost::get<3>(t));
   ar & boost::serialization::make_nvp("tuple_5", boost::get<4>(t));
   ar & boost::serialization::make_nvp("tuple_6", boost::get<5>(t));
}

template <class Archive, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
inline void serialize(Archive & ar, boost::tuple<T0, T1, T2, T3, T4, T5, T6> & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   ar & boost::serialization::make_nvp("tuple_1", boost::get<0>(t));
   ar & boost::serialization::make_nvp("tuple_2", boost::get<1>(t));
   ar & boost::serialization::make_nvp("tuple_3", boost::get<2>(t));
   ar & boost::serialization::make_nvp("tuple_4", boost::get<3>(t));
   ar & boost::serialization::make_nvp("tuple_5", boost::get<4>(t));
   ar & boost::serialization::make_nvp("tuple_6", boost::get<5>(t));
   ar & boost::serialization::make_nvp("tuple_7", boost::get<6>(t));
}

template <class Archive, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
inline void serialize(Archive & ar, boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7> & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   ar & boost::serialization::make_nvp("tuple_1", boost::get<0>(t));
   ar & boost::serialization::make_nvp("tuple_2", boost::get<1>(t));
   ar & boost::serialization::make_nvp("tuple_3", boost::get<2>(t));
   ar & boost::serialization::make_nvp("tuple_4", boost::get<3>(t));
   ar & boost::serialization::make_nvp("tuple_5", boost::get<4>(t));
   ar & boost::serialization::make_nvp("tuple_6", boost::get<5>(t));
   ar & boost::serialization::make_nvp("tuple_7", boost::get<6>(t));
   ar & boost::serialization::make_nvp("tuple_8", boost::get<7>(t));
}

template <class Archive, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
inline void serialize(Archive & ar, boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8> & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   ar & boost::serialization::make_nvp("tuple_1", boost::get<0>(t));
   ar & boost::serialization::make_nvp("tuple_2", boost::get<1>(t));
   ar & boost::serialization::make_nvp("tuple_3", boost::get<2>(t));
   ar & boost::serialization::make_nvp("tuple_4", boost::get<3>(t));
   ar & boost::serialization::make_nvp("tuple_5", boost::get<4>(t));
   ar & boost::serialization::make_nvp("tuple_6", boost::get<5>(t));
   ar & boost::serialization::make_nvp("tuple_7", boost::get<6>(t));
   ar & boost::serialization::make_nvp("tuple_8", boost::get<7>(t));
   ar & boost::serialization::make_nvp("tuple_9", boost::get<8>(t));
}

template <class Archive, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
inline void serialize(Archive & ar, boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   ar & boost::serialization::make_nvp("tuple_1", boost::get<0>(t));
   ar & boost::serialization::make_nvp("tuple_2", boost::get<1>(t));
   ar & boost::serialization::make_nvp("tuple_3", boost::get<2>(t));
   ar & boost::serialization::make_nvp("tuple_4", boost::get<3>(t));
   ar & boost::serialization::make_nvp("tuple_5", boost::get<4>(t));
   ar & boost::serialization::make_nvp("tuple_6", boost::get<5>(t));
   ar & boost::serialization::make_nvp("tuple_7", boost::get<6>(t));
   ar & boost::serialization::make_nvp("tuple_8", boost::get<7>(t));
   ar & boost::serialization::make_nvp("tuple_9", boost::get<8>(t));
   ar & boost::serialization::make_nvp("tuple_10", boost::get<9>(t));
}

} // namespace boost
} // namespace serialization

#endif // _QX_SERIALIZE_BOOST_TUPLE_H_
