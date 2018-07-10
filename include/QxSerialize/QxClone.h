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

#ifndef _QX_CLONE_H_
#define _QX_CLONE_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <string>
#include <iostream>
#include <sstream>
#include <exception>

#include <boost/archive/archive_exception.hpp>

#include <QxSerialize/boost/QxSerializeInclude.h>
#include <QxSerialize/QxBoostSerializeHelper/QxBoostSerializeRegisterHelperX.h>
#include <QxSerialize/QxSerializeInvoker.h>

#define QX_STR_CLONE_SERIALIZATION_ERROR "[QxOrm] qx::clone() serialization error : '%s'"
#define QX_STR_CLONE_DESERIALIZATION_ERROR "[QxOrm] qx::clone() deserialization error : '%s'"

namespace qx {

template <class T>
boost::shared_ptr<T> clone(const T & obj)
{
   QX_CLONE_STRING_STREAM ioss(std::ios_base::binary | std::ios_base::in | std::ios_base::out);
   QX_CLONE_BINARY_OUTPUT_ARCHIVE oar(ioss, boost::archive::no_header);
   QxBoostSerializeRegisterHelperX::helper(oar);
   bool bSerializeOk = false;

   try { oar << obj; bSerializeOk = ioss.good(); }
   catch (const boost::archive::archive_exception & e) { qDebug(QX_STR_CLONE_SERIALIZATION_ERROR, e.what()); }
   catch (const std::exception & e) { qDebug(QX_STR_CLONE_SERIALIZATION_ERROR, e.what()); }
   catch (...) { qDebug(QX_STR_CLONE_SERIALIZATION_ERROR, "unknown error"); }
   if (! bSerializeOk) { qAssert(false); return boost::shared_ptr<T>(); }

   boost::shared_ptr<T> pClone; pClone.reset(new T());
   QX_CLONE_BINARY_INPUT_ARCHIVE iar(ioss, boost::archive::no_header);
   QxBoostSerializeRegisterHelperX::helper(iar);
   bool bDeserializeOk = false;

   try { iar >> (* pClone); bDeserializeOk = ioss.good(); }
   catch (const boost::archive::archive_exception & e) { qDebug(QX_STR_CLONE_DESERIALIZATION_ERROR, e.what()); }
   catch (const std::exception & e) { qDebug(QX_STR_CLONE_DESERIALIZATION_ERROR, e.what()); }
   catch (...) { qDebug(QX_STR_CLONE_DESERIALIZATION_ERROR, "unknown error"); }
   qAssert(bDeserializeOk);

   return (bDeserializeOk ? pClone : boost::shared_ptr<T>());
}

} // namespace qx

#endif // _QX_CLONE_H_
