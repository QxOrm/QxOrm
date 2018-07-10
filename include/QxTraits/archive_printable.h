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

#ifndef _QX_ARCHIVE_PRINTABLE_H_
#define _QX_ARCHIVE_PRINTABLE_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file archive_printable.h
 * \author Lionel Marty
 * \ingroup QxTraits
 * \brief qx::trait::is_archive_printable<T>::value : define if a boost::archive type is readable by a human (for example XML archive) or not (for example binary archive)
 */

#include <QxSerialize/boost/QxSerializeInclude.h>

namespace qx {
namespace trait {

/*!
 * \ingroup QxTraits
 * \brief qx::trait::is_archive_printable<T>::value : define if a boost::archive type is readable by a human (for example XML archive) or not (for example binary archive)
 */
template <typename T> struct is_archive_printable  { enum { value = false }; };

#ifdef _QX_ENABLE_BOOST_SERIALIZATION

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

#endif // _QX_ENABLE_BOOST_SERIALIZATION

} // namespace trait
} // namespace qx

#endif // _QX_ARCHIVE_PRINTABLE_H_
