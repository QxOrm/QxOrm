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

#ifndef _QX_ARCHIVE_PRINTABLE_H_
#define _QX_ARCHIVE_PRINTABLE_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QxSerialize/boost/QxSerializeInclude.h>

namespace qx {
namespace trait {

template <typename T> struct is_archive_printable  { enum { value = false }; };

#if _QX_SERIALIZE_POLYMORPHIC
template <> struct is_archive_printable<boost::archive::polymorphic_iarchive> { enum { value = true }; };
template <> struct is_archive_printable<boost::archive::polymorphic_oarchive> { enum { value = true }; };
#endif // _QX_SERIALIZE_POLYMORPHIC

#if _QX_SERIALIZE_TEXT
template <> struct is_archive_printable<boost::archive::text_iarchive>  { enum { value = true }; };
template <> struct is_archive_printable<boost::archive::text_oarchive>  { enum { value = true }; };
#endif // _QX_SERIALIZE_TEXT

#if _QX_SERIALIZE_XML
template <> struct is_archive_printable<boost::archive::xml_iarchive>   { enum { value = true }; };
template <> struct is_archive_printable<boost::archive::xml_oarchive>   { enum { value = true }; };
#endif // _QX_SERIALIZE_XML

#if _QX_SERIALIZE_WIDE_TEXT
template <> struct is_archive_printable<boost::archive::text_wiarchive> { enum { value = true }; };
template <> struct is_archive_printable<boost::archive::text_woarchive> { enum { value = true }; };
#endif // _QX_SERIALIZE_WIDE_TEXT

#if _QX_SERIALIZE_WIDE_XML
template <> struct is_archive_printable<boost::archive::xml_wiarchive>  { enum { value = true }; };
template <> struct is_archive_printable<boost::archive::xml_woarchive>  { enum { value = true }; };
#endif // _QX_SERIALIZE_WIDE_XML

} // namespace trait
} // namespace qx

#endif // _QX_ARCHIVE_PRINTABLE_H_
