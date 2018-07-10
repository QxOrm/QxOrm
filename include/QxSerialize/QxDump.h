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

#ifndef _QX_DUMP_H_
#define _QX_DUMP_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxDump.h
 * \author Lionel Marty
 * \ingroup QxSerialize
 * \brief Dump all classes registered into QxOrm context using XML and JSON serialization engine
 */

#include <QxCommon/QxConfig.h>

#include <QxSerialize/QxSerializeInvoker.h>
#include <QxSerialize/QxSerializeQJson.h>
#include <QxSerialize/QxArchive.h>

#include <QxRegister/QxClassName.h>

#ifdef _QX_ENABLE_BOOST_SERIALIZATION

namespace qx {

/*!
 * \ingroup QxSerialize
 * \brief qx::dump(const T & t, bool bJsonFormat) : dump class of type T registered into QxOrm context using XML and JSON serialization engine
 */
template <class T>
void dump(const T & t, bool bJsonFormat = false)
{
   QString sDump;

   if (bJsonFormat)
   {
#ifndef _QX_NO_JSON
      sDump = qx::serialization::json::to_string(t);
#else // _QX_NO_JSON
      sDump = "Unable to dump element in JSON format : you must work with Qt5 and not define _QX_NO_JSON compilation option in 'QxOrm.pri' configuration file";
#endif // _QX_NO_JSON
   }
   else
   {
#if _QX_SERIALIZE_POLYMORPHIC
      sDump = qx::serialization::polymorphic_xml::to_string(t);
#elif _QX_SERIALIZE_XML
      sDump = qx::serialization::xml::to_string(t);
#elif _QX_SERIALIZE_WIDE_XML
      sDump = qx::serialization::wide::xml::to_string(t);
#else // _QX_SERIALIZE_POLYMORPHIC
      sDump = "Unable to dump element : you must define '_QX_ENABLE_BOOST_SERIALIZATION' and '_QX_ENABLE_BOOST_SERIALIZATION_XML' (or '_QX_ENABLE_BOOST_SERIALIZATION_WIDE_XML') compilation options in 'QxOrm.pri' configuration file";
#endif // _QX_SERIALIZE_POLYMORPHIC
   }

   QString sName = qx::QxClassName<T>::get();
   qDebug("[QxOrm] start dump '%s'", qPrintable(sName));
   qDebug("%s", qPrintable(sDump));
   qDebug("[QxOrm] end dump '%s'", qPrintable(sName));
}

} // namespace qx

#else // _QX_ENABLE_BOOST_SERIALIZATION

namespace qx {

template <class T>
void dump(const T & t, bool bJsonFormat = true)
{
#ifdef _QX_NO_JSON
   qDebug("[QxOrm] qx::dump() : %s", "not implemented when _QX_ENABLE_BOOST_SERIALIZATION compilation option is not defined (XML format) and _QX_NO_JSON compilation option is defined (JSON format)");
   Q_UNUSED(t); Q_UNUSED(bJsonFormat);
#else // _QX_NO_JSON
   if (! bJsonFormat) { return; }
   QString sDump = qx::serialization::json::to_string(t);
   QString sName = qx::QxClassName<T>::get();
   qDebug("[QxOrm] start dump '%s'", qPrintable(sName));
   qDebug("%s", qPrintable(sDump));
   qDebug("[QxOrm] end dump '%s'", qPrintable(sName));
#endif // _QX_NO_JSON
}

} // namespace qx

#endif // _QX_ENABLE_BOOST_SERIALIZATION
#endif // _QX_DUMP_H_
