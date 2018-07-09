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

#ifndef _QX_ARCHIVE_PRINTABLE_H_
#define _QX_ARCHIVE_PRINTABLE_H_

#ifdef _MSC_VER
#pragma once
#endif

#include "../../include/QxSerialize/boost/QxSerializeInclude.h"

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
