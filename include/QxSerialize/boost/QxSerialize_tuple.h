/****************************************************************************
**
** Copyright (C) 2010 QxOrm France and/or its subsidiary(-ies)
** Contact: QxOrm France Information (contact@qxorm.com)
**
** This file is part of the QxOrm library
**
** Commercial Usage
** Licensees holding valid QxOrm Commercial licenses may use this file in
** accordance with the QxOrm Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and QxOrm France
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file 'license.gpl3.txt' included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html
**
** If you are unsure which license is appropriate for your use, please
** contact the support department at support@qxorm.com
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
