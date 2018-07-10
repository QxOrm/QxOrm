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
#ifdef _QX_CPP_11_TUPLE
#ifndef BOOST_NO_CXX11_HDR_TUPLE
#ifndef _QX_SERIALIZE_STD_TUPLE_H_
#define _QX_SERIALIZE_STD_TUPLE_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/nvp.hpp>

#include <tuple>

namespace boost {
namespace serialization {

template <class Archive, typename T0, typename T1>
inline void serialize(Archive & ar, std::tuple<T0, T1> & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   ar & boost::serialization::make_nvp("tuple_1", std::get<0>(t));
   ar & boost::serialization::make_nvp("tuple_2", std::get<1>(t));
}

template <class Archive, typename T0, typename T1, typename T2>
inline void serialize(Archive & ar, std::tuple<T0, T1, T2> & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   ar & boost::serialization::make_nvp("tuple_1", std::get<0>(t));
   ar & boost::serialization::make_nvp("tuple_2", std::get<1>(t));
   ar & boost::serialization::make_nvp("tuple_3", std::get<2>(t));
}

template <class Archive, typename T0, typename T1, typename T2, typename T3>
inline void serialize(Archive & ar, std::tuple<T0, T1, T2, T3> & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   ar & boost::serialization::make_nvp("tuple_1", std::get<0>(t));
   ar & boost::serialization::make_nvp("tuple_2", std::get<1>(t));
   ar & boost::serialization::make_nvp("tuple_3", std::get<2>(t));
   ar & boost::serialization::make_nvp("tuple_4", std::get<3>(t));
}

template <class Archive, typename T0, typename T1, typename T2, typename T3, typename T4>
inline void serialize(Archive & ar, std::tuple<T0, T1, T2, T3, T4> & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   ar & boost::serialization::make_nvp("tuple_1", std::get<0>(t));
   ar & boost::serialization::make_nvp("tuple_2", std::get<1>(t));
   ar & boost::serialization::make_nvp("tuple_3", std::get<2>(t));
   ar & boost::serialization::make_nvp("tuple_4", std::get<3>(t));
   ar & boost::serialization::make_nvp("tuple_5", std::get<4>(t));
}

template <class Archive, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
inline void serialize(Archive & ar, std::tuple<T0, T1, T2, T3, T4, T5> & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   ar & boost::serialization::make_nvp("tuple_1", std::get<0>(t));
   ar & boost::serialization::make_nvp("tuple_2", std::get<1>(t));
   ar & boost::serialization::make_nvp("tuple_3", std::get<2>(t));
   ar & boost::serialization::make_nvp("tuple_4", std::get<3>(t));
   ar & boost::serialization::make_nvp("tuple_5", std::get<4>(t));
   ar & boost::serialization::make_nvp("tuple_6", std::get<5>(t));
}

template <class Archive, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
inline void serialize(Archive & ar, std::tuple<T0, T1, T2, T3, T4, T5, T6> & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   ar & boost::serialization::make_nvp("tuple_1", std::get<0>(t));
   ar & boost::serialization::make_nvp("tuple_2", std::get<1>(t));
   ar & boost::serialization::make_nvp("tuple_3", std::get<2>(t));
   ar & boost::serialization::make_nvp("tuple_4", std::get<3>(t));
   ar & boost::serialization::make_nvp("tuple_5", std::get<4>(t));
   ar & boost::serialization::make_nvp("tuple_6", std::get<5>(t));
   ar & boost::serialization::make_nvp("tuple_7", std::get<6>(t));
}

template <class Archive, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
inline void serialize(Archive & ar, std::tuple<T0, T1, T2, T3, T4, T5, T6, T7> & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   ar & boost::serialization::make_nvp("tuple_1", std::get<0>(t));
   ar & boost::serialization::make_nvp("tuple_2", std::get<1>(t));
   ar & boost::serialization::make_nvp("tuple_3", std::get<2>(t));
   ar & boost::serialization::make_nvp("tuple_4", std::get<3>(t));
   ar & boost::serialization::make_nvp("tuple_5", std::get<4>(t));
   ar & boost::serialization::make_nvp("tuple_6", std::get<5>(t));
   ar & boost::serialization::make_nvp("tuple_7", std::get<6>(t));
   ar & boost::serialization::make_nvp("tuple_8", std::get<7>(t));
}

template <class Archive, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
inline void serialize(Archive & ar, std::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8> & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   ar & boost::serialization::make_nvp("tuple_1", std::get<0>(t));
   ar & boost::serialization::make_nvp("tuple_2", std::get<1>(t));
   ar & boost::serialization::make_nvp("tuple_3", std::get<2>(t));
   ar & boost::serialization::make_nvp("tuple_4", std::get<3>(t));
   ar & boost::serialization::make_nvp("tuple_5", std::get<4>(t));
   ar & boost::serialization::make_nvp("tuple_6", std::get<5>(t));
   ar & boost::serialization::make_nvp("tuple_7", std::get<6>(t));
   ar & boost::serialization::make_nvp("tuple_8", std::get<7>(t));
   ar & boost::serialization::make_nvp("tuple_9", std::get<8>(t));
}

template <class Archive, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
inline void serialize(Archive & ar, std::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   ar & boost::serialization::make_nvp("tuple_1", std::get<0>(t));
   ar & boost::serialization::make_nvp("tuple_2", std::get<1>(t));
   ar & boost::serialization::make_nvp("tuple_3", std::get<2>(t));
   ar & boost::serialization::make_nvp("tuple_4", std::get<3>(t));
   ar & boost::serialization::make_nvp("tuple_5", std::get<4>(t));
   ar & boost::serialization::make_nvp("tuple_6", std::get<5>(t));
   ar & boost::serialization::make_nvp("tuple_7", std::get<6>(t));
   ar & boost::serialization::make_nvp("tuple_8", std::get<7>(t));
   ar & boost::serialization::make_nvp("tuple_9", std::get<8>(t));
   ar & boost::serialization::make_nvp("tuple_10", std::get<9>(t));
}

} // namespace boost
} // namespace serialization

#endif // _QX_SERIALIZE_STD_TUPLE_H_
#endif // BOOST_NO_CXX11_HDR_TUPLE
#endif // _QX_CPP_11_TUPLE
#endif // _QX_ENABLE_BOOST_SERIALIZATION
