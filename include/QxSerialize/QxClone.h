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

#include "../../include/QxSerialize/boost/QxSerializeInclude.h"
#include "../../include/QxSerialize/QxBoostSerializeHelper/QxBoostSerializeRegisterHelperX.h"
#include "../../include/QxSerialize/QxSerializeInvoker.h"

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
