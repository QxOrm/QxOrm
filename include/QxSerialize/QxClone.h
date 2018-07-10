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

#ifndef _QX_CLONE_H_
#define _QX_CLONE_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxClone.h
 * \author Lionel Marty
 * \ingroup QxSerialize
 * \brief Clone all classes registered into QxOrm context using QxOrm library serialization engine
 */

#include <string>
#include <iostream>
#include <sstream>
#include <exception>

#ifdef _QX_ENABLE_BOOST_SERIALIZATION

#include <boost/archive/archive_exception.hpp>

#include <QxSerialize/boost/QxSerializeInclude.h>
#include <QxSerialize/QxBoostSerializeHelper/QxBoostSerializeRegisterHelperX.h>
#include <QxSerialize/QxSerializeInvoker.h>

#else // _QX_ENABLE_BOOST_SERIALIZATION

#include <QxSerialize/QxSerializeQDataStream.h>
#include <QxSerialize/QDataStream/QxSerializeQDataStream_all_include.h>

#endif // _QX_ENABLE_BOOST_SERIALIZATION

#define QX_STR_CLONE_SERIALIZATION_ERROR "[QxOrm] qx::clone() serialization error : '%s'"
#define QX_STR_CLONE_DESERIALIZATION_ERROR "[QxOrm] qx::clone() deserialization error : '%s'"

namespace qx {

#ifdef _QX_ENABLE_BOOST_SERIALIZATION

/*!
 * \ingroup QxSerialize
 * \brief qx::clone_to_nude_ptr(const T & obj) : return a nude pointer (be careful with memory leak) of a new instance of type T cloned from obj
 */
template <class T>
T * clone_to_nude_ptr(const T & obj)
{
   QX_CLONE_STRING_STREAM ioss(std::ios_base::binary | std::ios_base::in | std::ios_base::out);
   QX_CLONE_BINARY_OUTPUT_ARCHIVE oar(ioss, boost::archive::no_header);
   QxBoostSerializeRegisterHelperX::helper(oar);
   bool bSerializeOk = false;

   try { oar << obj; bSerializeOk = ioss.good(); }
   catch (const boost::archive::archive_exception & e) { qDebug(QX_STR_CLONE_SERIALIZATION_ERROR, e.what()); }
   catch (const std::exception & e) { qDebug(QX_STR_CLONE_SERIALIZATION_ERROR, e.what()); }
   catch (...) { qDebug(QX_STR_CLONE_SERIALIZATION_ERROR, "unknown error"); }
   if (! bSerializeOk) { qAssert(false); return NULL; }

   T * pClone = new T();
   QX_CLONE_BINARY_INPUT_ARCHIVE iar(ioss, boost::archive::no_header);
   QxBoostSerializeRegisterHelperX::helper(iar);
   bool bDeserializeOk = false;

   try { iar >> (* pClone); bDeserializeOk = ioss.good(); }
   catch (const boost::archive::archive_exception & e) { qDebug(QX_STR_CLONE_DESERIALIZATION_ERROR, e.what()); }
   catch (const std::exception & e) { qDebug(QX_STR_CLONE_DESERIALIZATION_ERROR, e.what()); }
   catch (...) { qDebug(QX_STR_CLONE_DESERIALIZATION_ERROR, "unknown error"); }
   qAssert(bDeserializeOk);

   return (bDeserializeOk ? pClone : NULL);
}

#else // _QX_ENABLE_BOOST_SERIALIZATION

/*!
 * \ingroup QxSerialize
 * \brief qx::clone_to_nude_ptr(const T & obj) : return a nude pointer (be careful with memory leak) of a new instance of type T cloned from obj (this is a limited clone version which uses Qt QDataStream engine compared to boost::serialization engine)
 */
template <class T>
T * clone_to_nude_ptr(const T & obj)
{
   QByteArray baClone = qx::serialization::qt::to_byte_array(obj);
   if (baClone.isEmpty()) { qAssertMsg(false, "[QxOrm] qx::clone_to_nude_ptr", "an error occurred during QDataStream serialization process"); return NULL; }
   T * pClone = new T();
   qx_bool bOk = qx::serialization::qt::from_byte_array((* pClone), baClone);
   return (bOk ? pClone : NULL);
}

#endif // _QX_ENABLE_BOOST_SERIALIZATION

/*!
 * \ingroup QxSerialize
 * \brief qx::clone(const T & obj) : return a boost smart-pointer (std::shared_ptr<T>) of a new instance of type T cloned from obj
 */
template <class T>
std::shared_ptr<T> clone(const T & obj)
{ T * ptr = qx::clone_to_nude_ptr<T>(obj); return std::shared_ptr<T>(ptr); }

#ifdef _QX_ENABLE_BOOST

/*!
 * \ingroup QxSerialize
 * \brief qx::clone_to_boost_shared_ptr(const T & obj) : return a boost smart-pointer (boost::shared_ptr<T>) of a new instance of type T cloned from obj
 */
template <class T>
boost::shared_ptr<T> clone_to_boost_shared_ptr(const T & obj)
{ T * ptr = qx::clone_to_nude_ptr<T>(obj); return boost::shared_ptr<T>(ptr); }

#endif // _QX_ENABLE_BOOST

/*!
 * \ingroup QxSerialize
 * \brief qx::clone_to_qt_shared_ptr(const T & obj) : return a Qt smart-pointer (QSharedPointer<T>) of a new instance of type T cloned from obj
 */
template <class T>
QSharedPointer<T> clone_to_qt_shared_ptr(const T & obj)
{ T * ptr = qx::clone_to_nude_ptr<T>(obj); return QSharedPointer<T>(ptr); }

/*!
 * \ingroup QxSerialize
 * \brief qx::clone_to_std_shared_ptr(const T & obj) : return a C++11 std smart-pointer (std::shared_ptr<T>) of a new instance of type T cloned from obj
 */
template <class T>
std::shared_ptr<T> clone_to_std_shared_ptr(const T & obj)
{ T * ptr = qx::clone_to_nude_ptr<T>(obj); return std::shared_ptr<T>(ptr); }

} // namespace qx

#endif // _QX_CLONE_H_
