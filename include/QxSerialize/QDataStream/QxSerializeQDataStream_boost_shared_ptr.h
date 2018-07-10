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

#ifndef _QX_SERIALIZE_QDATASTREAM_BOOST_SHARED_PTR_H_
#define _QX_SERIALIZE_QDATASTREAM_BOOST_SHARED_PTR_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSerializeQDataStream_boost_shared_ptr.h
 * \author Lionel Marty
 * \ingroup QxSerialize
 * \brief Provide a Qt QDataStream serialization method (save/load) for type boost::shared_ptr<T>
 */

#include <QtCore/qdatastream.h>

#include <boost/shared_ptr.hpp>

template <typename T>
QDataStream & operator<< (QDataStream & stream, const boost::shared_ptr<T> & t)
{
   qint8 iIsNull = (t ? 0 : 1);
   stream << iIsNull;
   if (t) { stream << (* t); }
   return stream;
}

template <typename T>
QDataStream & operator>> (QDataStream & stream, boost::shared_ptr<T> & t)
{
   qint8 iIsNull = 0;
   stream >> iIsNull;
   if (! iIsNull) { t.reset(new T()); stream >> (* t); }
   else { t.reset(); }
   return stream;
}

#endif // _QX_SERIALIZE_QDATASTREAM_BOOST_SHARED_PTR_H_
