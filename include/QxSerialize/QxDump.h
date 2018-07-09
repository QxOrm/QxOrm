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
