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

#ifndef _QX_SERIALIZE_QDATASTREAM_BOOST_TUPLE_H_
#define _QX_SERIALIZE_QDATASTREAM_BOOST_TUPLE_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSerializeQDataStream_boost_tuple.h
 * \author Lionel Marty
 * \ingroup QxSerialize
 * \brief Provide a Qt QDataStream serialization method (save/load) for type boost::tuple<T0, T1, ..., T9>
 */

#include <QtCore/qdatastream.h>

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/tuple/tuple_io.hpp>

template <typename T0, typename T1>
QDataStream & operator<< (QDataStream & stream, const boost::tuple<T0, T1> & t)
{
   stream << boost::get<0>(t);
   stream << boost::get<1>(t);
   return stream;
}

template <typename T0, typename T1, typename T2>
QDataStream & operator<< (QDataStream & stream, const boost::tuple<T0, T1, T2> & t)
{
   stream << boost::get<0>(t);
   stream << boost::get<1>(t);
   stream << boost::get<2>(t);
   return stream;
}

template <typename T0, typename T1, typename T2, typename T3>
QDataStream & operator<< (QDataStream & stream, const boost::tuple<T0, T1, T2, T3> & t)
{
   stream << boost::get<0>(t);
   stream << boost::get<1>(t);
   stream << boost::get<2>(t);
   stream << boost::get<3>(t);
   return stream;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4>
QDataStream & operator<< (QDataStream & stream, const boost::tuple<T0, T1, T2, T3, T4> & t)
{
   stream << boost::get<0>(t);
   stream << boost::get<1>(t);
   stream << boost::get<2>(t);
   stream << boost::get<3>(t);
   stream << boost::get<4>(t);
   return stream;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
QDataStream & operator<< (QDataStream & stream, const boost::tuple<T0, T1, T2, T3, T4, T5> & t)
{
   stream << boost::get<0>(t);
   stream << boost::get<1>(t);
   stream << boost::get<2>(t);
   stream << boost::get<3>(t);
   stream << boost::get<4>(t);
   stream << boost::get<5>(t);
   return stream;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
QDataStream & operator<< (QDataStream & stream, const boost::tuple<T0, T1, T2, T3, T4, T5, T6> & t)
{
   stream << boost::get<0>(t);
   stream << boost::get<1>(t);
   stream << boost::get<2>(t);
   stream << boost::get<3>(t);
   stream << boost::get<4>(t);
   stream << boost::get<5>(t);
   stream << boost::get<6>(t);
   return stream;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
QDataStream & operator<< (QDataStream & stream, const boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7> & t)
{
   stream << boost::get<0>(t);
   stream << boost::get<1>(t);
   stream << boost::get<2>(t);
   stream << boost::get<3>(t);
   stream << boost::get<4>(t);
   stream << boost::get<5>(t);
   stream << boost::get<6>(t);
   stream << boost::get<7>(t);
   return stream;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
QDataStream & operator<< (QDataStream & stream, const boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8> & t)
{
   stream << boost::get<0>(t);
   stream << boost::get<1>(t);
   stream << boost::get<2>(t);
   stream << boost::get<3>(t);
   stream << boost::get<4>(t);
   stream << boost::get<5>(t);
   stream << boost::get<6>(t);
   stream << boost::get<7>(t);
   stream << boost::get<8>(t);
   return stream;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
QDataStream & operator<< (QDataStream & stream, const boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> & t)
{
   stream << boost::get<0>(t);
   stream << boost::get<1>(t);
   stream << boost::get<2>(t);
   stream << boost::get<3>(t);
   stream << boost::get<4>(t);
   stream << boost::get<5>(t);
   stream << boost::get<6>(t);
   stream << boost::get<7>(t);
   stream << boost::get<8>(t);
   stream << boost::get<9>(t);
   return stream;
}

template <typename T0, typename T1>
QDataStream & operator>> (QDataStream & stream, boost::tuple<T0, T1> & t)
{
   stream >> boost::get<0>(t);
   stream >> boost::get<1>(t);
   return stream;
}

template <typename T0, typename T1, typename T2>
QDataStream & operator>> (QDataStream & stream, boost::tuple<T0, T1, T2> & t)
{
   stream >> boost::get<0>(t);
   stream >> boost::get<1>(t);
   stream >> boost::get<2>(t);
   return stream;
}

template <typename T0, typename T1, typename T2, typename T3>
QDataStream & operator>> (QDataStream & stream, boost::tuple<T0, T1, T2, T3> & t)
{
   stream >> boost::get<0>(t);
   stream >> boost::get<1>(t);
   stream >> boost::get<2>(t);
   stream >> boost::get<3>(t);
   return stream;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4>
QDataStream & operator>> (QDataStream & stream, boost::tuple<T0, T1, T2, T3, T4> & t)
{
   stream >> boost::get<0>(t);
   stream >> boost::get<1>(t);
   stream >> boost::get<2>(t);
   stream >> boost::get<3>(t);
   stream >> boost::get<4>(t);
   return stream;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
QDataStream & operator>> (QDataStream & stream, boost::tuple<T0, T1, T2, T3, T4, T5> & t)
{
   stream >> boost::get<0>(t);
   stream >> boost::get<1>(t);
   stream >> boost::get<2>(t);
   stream >> boost::get<3>(t);
   stream >> boost::get<4>(t);
   stream >> boost::get<5>(t);
   return stream;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
QDataStream & operator>> (QDataStream & stream, boost::tuple<T0, T1, T2, T3, T4, T5, T6> & t)
{
   stream >> boost::get<0>(t);
   stream >> boost::get<1>(t);
   stream >> boost::get<2>(t);
   stream >> boost::get<3>(t);
   stream >> boost::get<4>(t);
   stream >> boost::get<5>(t);
   stream >> boost::get<6>(t);
   return stream;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
QDataStream & operator>> (QDataStream & stream, boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7> & t)
{
   stream >> boost::get<0>(t);
   stream >> boost::get<1>(t);
   stream >> boost::get<2>(t);
   stream >> boost::get<3>(t);
   stream >> boost::get<4>(t);
   stream >> boost::get<5>(t);
   stream >> boost::get<6>(t);
   stream >> boost::get<7>(t);
   return stream;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
QDataStream & operator>> (QDataStream & stream, boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8> & t)
{
   stream >> boost::get<0>(t);
   stream >> boost::get<1>(t);
   stream >> boost::get<2>(t);
   stream >> boost::get<3>(t);
   stream >> boost::get<4>(t);
   stream >> boost::get<5>(t);
   stream >> boost::get<6>(t);
   stream >> boost::get<7>(t);
   stream >> boost::get<8>(t);
   return stream;
}

template <typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
QDataStream & operator>> (QDataStream & stream, boost::tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> & t)
{
   stream >> boost::get<0>(t);
   stream >> boost::get<1>(t);
   stream >> boost::get<2>(t);
   stream >> boost::get<3>(t);
   stream >> boost::get<4>(t);
   stream >> boost::get<5>(t);
   stream >> boost::get<6>(t);
   stream >> boost::get<7>(t);
   stream >> boost::get<8>(t);
   stream >> boost::get<9>(t);
   return stream;
}

#endif // _QX_SERIALIZE_QDATASTREAM_BOOST_TUPLE_H_
