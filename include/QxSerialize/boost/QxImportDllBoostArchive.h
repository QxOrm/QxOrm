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

#ifndef _QX_IMPORT_DLL_BOOST_ARCHIVE_H_
#define _QX_IMPORT_DLL_BOOST_ARCHIVE_H_

#ifdef _MSC_VER
#pragma once
#endif

#include "../../../include/QxCommon/QxConfig.h"

#if _QX_USE_EXPORT_DLL_BOOST_SERIALIZATION_SINGLETON

#if (BOOST_VERSION > 103800)
#define QX_BOOST_IMPORT_ARCHIVE_SERIALIZER_MAP_HPP(ArchiveIn, ArchiveOut) \
QX_DLL_EXPORT_TEMPLATE_T_P1_HPP(class, boost::archive::detail::archive_serializer_map, ArchiveIn) \
QX_DLL_EXPORT_TEMPLATE_T_P1_HPP(class, boost::archive::detail::archive_serializer_map, ArchiveOut)
#else // (BOOST_VERSION > 103800)
#define QX_BOOST_IMPORT_ARCHIVE_SERIALIZER_MAP_HPP(ArchiveIn, ArchiveOut) \
QX_DLL_EXPORT_TEMPLATE_T_P1_HPP(class, boost::archive::detail::archive_pointer_iserializer, ArchiveIn) \
QX_DLL_EXPORT_TEMPLATE_T_P1_HPP(class, boost::archive::detail::archive_pointer_oserializer, ArchiveOut)
#endif // (BOOST_VERSION > 103800)

#if _QX_SERIALIZE_POLYMORPHIC
   QX_BOOST_IMPORT_ARCHIVE_SERIALIZER_MAP_HPP(boost::archive::polymorphic_iarchive, boost::archive::polymorphic_oarchive)
#endif // _QX_SERIALIZE_POLYMORPHIC

#if _QX_SERIALIZE_BINARY
   QX_BOOST_IMPORT_ARCHIVE_SERIALIZER_MAP_HPP(boost::archive::binary_iarchive, boost::archive::binary_oarchive)
#endif // _QX_SERIALIZE_BINARY

#if _QX_SERIALIZE_TEXT
   QX_BOOST_IMPORT_ARCHIVE_SERIALIZER_MAP_HPP(boost::archive::text_iarchive, boost::archive::text_oarchive)
#endif // _QX_SERIALIZE_TEXT

#if _QX_SERIALIZE_XML
   QX_BOOST_IMPORT_ARCHIVE_SERIALIZER_MAP_HPP(boost::archive::xml_iarchive, boost::archive::xml_oarchive)
#endif // _QX_SERIALIZE_XML

#if _QX_SERIALIZE_WIDE_BINARY
   QX_BOOST_IMPORT_ARCHIVE_SERIALIZER_MAP_HPP(boost::archive::binary_wiarchive, boost::archive::binary_woarchive)
#endif // _QX_SERIALIZE_WIDE_BINARY

#if _QX_SERIALIZE_WIDE_TEXT
   QX_BOOST_IMPORT_ARCHIVE_SERIALIZER_MAP_HPP(boost::archive::text_wiarchive, boost::archive::text_woarchive)
#endif // _QX_SERIALIZE_WIDE_TEXT

#if _QX_SERIALIZE_WIDE_XML
   QX_BOOST_IMPORT_ARCHIVE_SERIALIZER_MAP_HPP(boost::archive::xml_wiarchive, boost::archive::xml_woarchive)
#endif // _QX_SERIALIZE_WIDE_XML

#endif // _QX_USE_EXPORT_DLL_BOOST_SERIALIZATION_SINGLETON
#endif // _QX_IMPORT_DLL_BOOST_ARCHIVE_H_
