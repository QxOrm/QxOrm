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

#ifndef _QX_DUMP_H_
#define _QX_DUMP_H_

#ifdef _MSC_VER
#pragma once
#endif

#include "../../include/QxCommon/QxConfig.h"

#include "../../include/QxSerialize/QxSerializeInvoker.h"
#include "../../include/QxSerialize/QxArchive.h"

#include "../../include/QxRegister/QxClassName.h"

namespace qx {

template <class T>
void dump(const T & t)
{
#if _QX_SERIALIZE_POLYMORPHIC
   QString sDump = qx::serialization::polymorphic_xml::to_string(t);
#elif _QX_SERIALIZE_XML
   QString sDump = qx::serialization::xml::to_string(t);
#elif _QX_SERIALIZE_WIDE_XML
   QString sDump = qx::serialization::wide::xml::to_string(t);
#else // _QX_SERIALIZE_POLYMORPHIC
   QString sDump = "Unable to dump element : you must activate '_QX_SERIALIZE_XML' or '_QX_SERIALIZE_WIDE_XML' parameter in 'QxConfig.h' file";
#endif // _QX_SERIALIZE_POLYMORPHIC

   QString sName = qx::QxClassName<T>::get();
   qDebug("[QxOrm] start dump '%s'", qPrintable(sName));
   qDebug("%s", qPrintable(sDump));
   qDebug("[QxOrm] end dump '%s'", qPrintable(sName));
}

} // namespace qx

#endif // _QX_DUMP_H_
