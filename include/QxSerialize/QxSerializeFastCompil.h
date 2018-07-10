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

#ifdef _QX_ENABLE_BOOST_SERIALIZATION
#ifndef _QX_SERIALIZE_FAST_COMPIL_H_
#define _QX_SERIALIZE_FAST_COMPIL_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QxCommon/QxConfig.h>

#include <QxSerialize/boost/QxSerializeInclude.h>
#include <QxSerialize/boost/QxExportDllMacroHpp.h>
#include <QxSerialize/boost/QxExportDllMacroCpp.h>
#include <QxSerialize/boost/QxImportDllBoostArchive.h>
#include <QxSerialize/QxBoostSerializeHelper/QxBoostSerializeRegisterHelper.h>

#if _QX_BUILDING_QX_ORM
#define QX_BOOST_EXPORT_SERIALIZATION_FAST_COMPIL_HPP(T) /* Nothing */
#define QX_BOOST_EXPORT_SERIALIZATION_FAST_COMPIL_CPP(T) QX_BOOST_EXPORT_SERIALIZATION_CPP(T)
#else // _QX_BUILDING_QX_ORM
#define QX_BOOST_EXPORT_SERIALIZATION_FAST_COMPIL_HPP(T) QX_BOOST_EXPORT_SERIALIZATION_HPP(T)
#define QX_BOOST_EXPORT_SERIALIZATION_FAST_COMPIL_CPP(T) /* Nothing */
#endif // _QX_BUILDING_QX_ORM

#define QX_SERIALIZE_FAST_COMPIL_SAVE_HPP(dllImportExport, Archive, className) \
dllImportExport void save(Archive & ar, const className & t, const unsigned int file_version);

#define QX_SERIALIZE_FAST_COMPIL_LOAD_HPP(dllImportExport, Archive, className) \
dllImportExport void load(Archive & ar, className & t, const unsigned int file_version);

#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_HPP(dllImportExport, Archive, className) \
dllImportExport void serialize(Archive & ar, className & t, const unsigned int file_version);

#define QX_SERIALIZE_FAST_COMPIL_SAVE_CPP(Archive, className) \
void save(Archive & ar, const className & t, const unsigned int file_version) \
{ qx_save(ar, t, file_version); }

#define QX_SERIALIZE_FAST_COMPIL_LOAD_CPP(Archive, className) \
void load(Archive & ar, className & t, const unsigned int file_version) \
{ qx_load(ar, t, file_version); }

#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_CPP(Archive, className) \
void serialize(Archive & ar, className & t, const unsigned int file_version) \
{ qx_serialize(ar, t, file_version); }

#if _QX_SERIALIZE_POLYMORPHIC
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_POLYMORPHIC_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_HPP(dllImportExport, boost::archive::polymorphic_oarchive, className) \
QX_SERIALIZE_FAST_COMPIL_LOAD_HPP(dllImportExport, boost::archive::polymorphic_iarchive, className)
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_POLYMORPHIC_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_HPP(dllImportExport, boost::archive::polymorphic_oarchive, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_HPP(dllImportExport, boost::archive::polymorphic_iarchive, className)
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_POLYMORPHIC_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_CPP(boost::archive::polymorphic_oarchive, className) \
QX_SERIALIZE_FAST_COMPIL_LOAD_CPP(boost::archive::polymorphic_iarchive, className)
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_POLYMORPHIC_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_CPP(boost::archive::polymorphic_oarchive, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_CPP(boost::archive::polymorphic_iarchive, className)
#else // _QX_SERIALIZE_POLYMORPHIC
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_POLYMORPHIC_HPP(dllImportExport, className) /* Nothing */
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_POLYMORPHIC_HPP(dllImportExport, className) /* Nothing */
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_POLYMORPHIC_CPP(className) /* Nothing */
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_POLYMORPHIC_CPP(className) /* Nothing */
#endif // _QX_SERIALIZE_POLYMORPHIC

#if _QX_SERIALIZE_BINARY
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_BINARY_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_HPP(dllImportExport, boost::archive::binary_oarchive, className) \
QX_SERIALIZE_FAST_COMPIL_LOAD_HPP(dllImportExport, boost::archive::binary_iarchive, className)
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_BINARY_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_HPP(dllImportExport, boost::archive::binary_oarchive, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_HPP(dllImportExport, boost::archive::binary_iarchive, className)
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_BINARY_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_CPP(boost::archive::binary_oarchive, className) \
QX_SERIALIZE_FAST_COMPIL_LOAD_CPP(boost::archive::binary_iarchive, className)
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_BINARY_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_CPP(boost::archive::binary_oarchive, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_CPP(boost::archive::binary_iarchive, className)
#else // _QX_SERIALIZE_BINARY
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_BINARY_HPP(dllImportExport, className) /* Nothing */
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_BINARY_HPP(dllImportExport, className) /* Nothing */
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_BINARY_CPP(className) /* Nothing */
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_BINARY_CPP(className) /* Nothing */
#endif // _QX_SERIALIZE_BINARY

#if _QX_SERIALIZE_TEXT
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_TEXT_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_HPP(dllImportExport, boost::archive::text_oarchive, className) \
QX_SERIALIZE_FAST_COMPIL_LOAD_HPP(dllImportExport, boost::archive::text_iarchive, className)
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_TEXT_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_HPP(dllImportExport, boost::archive::text_oarchive, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_HPP(dllImportExport, boost::archive::text_iarchive, className)
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_TEXT_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_CPP(boost::archive::text_oarchive, className) \
QX_SERIALIZE_FAST_COMPIL_LOAD_CPP(boost::archive::text_iarchive, className)
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_TEXT_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_CPP(boost::archive::text_oarchive, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_CPP(boost::archive::text_iarchive, className)
#else // _QX_SERIALIZE_TEXT
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_TEXT_HPP(dllImportExport, className) /* Nothing */
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_TEXT_HPP(dllImportExport, className) /* Nothing */
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_TEXT_CPP(className) /* Nothing */
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_TEXT_CPP(className) /* Nothing */
#endif // _QX_SERIALIZE_TEXT

#if _QX_SERIALIZE_XML
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_XML_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_HPP(dllImportExport, boost::archive::xml_oarchive, className) \
QX_SERIALIZE_FAST_COMPIL_LOAD_HPP(dllImportExport, boost::archive::xml_iarchive, className)
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_XML_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_HPP(dllImportExport, boost::archive::xml_oarchive, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_HPP(dllImportExport, boost::archive::xml_iarchive, className)
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_XML_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_CPP(boost::archive::xml_oarchive, className) \
QX_SERIALIZE_FAST_COMPIL_LOAD_CPP(boost::archive::xml_iarchive, className)
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_XML_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_CPP(boost::archive::xml_oarchive, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_CPP(boost::archive::xml_iarchive, className)
#else // _QX_SERIALIZE_XML
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_XML_HPP(dllImportExport, className) /* Nothing */
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_XML_HPP(dllImportExport, className) /* Nothing */
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_XML_CPP(className) /* Nothing */
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_XML_CPP(className) /* Nothing */
#endif // _QX_SERIALIZE_XML

#if _QX_SERIALIZE_PORTABLE_BINARY
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_PORTABLE_BINARY_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_HPP(dllImportExport, eos::portable_oarchive, className) \
QX_SERIALIZE_FAST_COMPIL_LOAD_HPP(dllImportExport, eos::portable_iarchive, className)
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_PORTABLE_BINARY_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_HPP(dllImportExport, eos::portable_oarchive, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_HPP(dllImportExport, eos::portable_iarchive, className)
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_PORTABLE_BINARY_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_CPP(eos::portable_oarchive, className) \
QX_SERIALIZE_FAST_COMPIL_LOAD_CPP(eos::portable_iarchive, className)
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_PORTABLE_BINARY_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_CPP(eos::portable_oarchive, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_CPP(eos::portable_iarchive, className)
#else // _QX_SERIALIZE_PORTABLE_BINARY
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_PORTABLE_BINARY_HPP(dllImportExport, className) /* Nothing */
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_PORTABLE_BINARY_HPP(dllImportExport, className) /* Nothing */
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_PORTABLE_BINARY_CPP(className) /* Nothing */
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_PORTABLE_BINARY_CPP(className) /* Nothing */
#endif // _QX_SERIALIZE_PORTABLE_BINARY

#if _QX_SERIALIZE_WIDE_BINARY
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_WIDE_BINARY_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_HPP(dllImportExport, boost::archive::binary_woarchive, className) \
QX_SERIALIZE_FAST_COMPIL_LOAD_HPP(dllImportExport, boost::archive::binary_wiarchive, className)
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_WIDE_BINARY_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_HPP(dllImportExport, boost::archive::binary_woarchive, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_HPP(dllImportExport, boost::archive::binary_wiarchive, className)
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_WIDE_BINARY_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_CPP(boost::archive::binary_woarchive, className) \
QX_SERIALIZE_FAST_COMPIL_LOAD_CPP(boost::archive::binary_wiarchive, className)
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_WIDE_BINARY_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_CPP(boost::archive::binary_woarchive, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_CPP(boost::archive::binary_wiarchive, className)
#else // _QX_SERIALIZE_WIDE_BINARY
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_WIDE_BINARY_HPP(dllImportExport, className) /* Nothing */
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_WIDE_BINARY_HPP(dllImportExport, className) /* Nothing */
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_WIDE_BINARY_CPP(className) /* Nothing */
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_WIDE_BINARY_CPP(className) /* Nothing */
#endif // _QX_SERIALIZE_WIDE_BINARY

#if _QX_SERIALIZE_WIDE_TEXT
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_WIDE_TEXT_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_HPP(dllImportExport, boost::archive::text_woarchive, className) \
QX_SERIALIZE_FAST_COMPIL_LOAD_HPP(dllImportExport, boost::archive::text_wiarchive, className)
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_WIDE_TEXT_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_HPP(dllImportExport, boost::archive::text_woarchive, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_HPP(dllImportExport, boost::archive::text_wiarchive, className)
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_WIDE_TEXT_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_CPP(boost::archive::text_woarchive, className) \
QX_SERIALIZE_FAST_COMPIL_LOAD_CPP(boost::archive::text_wiarchive, className)
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_WIDE_TEXT_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_CPP(boost::archive::text_woarchive, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_CPP(boost::archive::text_wiarchive, className)
#else // _QX_SERIALIZE_WIDE_TEXT
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_WIDE_TEXT_HPP(dllImportExport, className) /* Nothing */
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_WIDE_TEXT_HPP(dllImportExport, className) /* Nothing */
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_WIDE_TEXT_CPP(className) /* Nothing */
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_WIDE_TEXT_CPP(className) /* Nothing */
#endif // _QX_SERIALIZE_WIDE_TEXT

#if _QX_SERIALIZE_WIDE_XML
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_WIDE_XML_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_HPP(dllImportExport, boost::archive::xml_woarchive, className) \
QX_SERIALIZE_FAST_COMPIL_LOAD_HPP(dllImportExport, boost::archive::xml_wiarchive, className)
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_WIDE_XML_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_HPP(dllImportExport, boost::archive::xml_woarchive, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_HPP(dllImportExport, boost::archive::xml_wiarchive, className)
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_WIDE_XML_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_CPP(boost::archive::xml_woarchive, className) \
QX_SERIALIZE_FAST_COMPIL_LOAD_CPP(boost::archive::xml_wiarchive, className)
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_WIDE_XML_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_CPP(boost::archive::xml_woarchive, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_IMPL_CPP(boost::archive::xml_wiarchive, className)
#else // _QX_SERIALIZE_WIDE_XML
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_WIDE_XML_HPP(dllImportExport, className) /* Nothing */
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_WIDE_XML_HPP(dllImportExport, className) /* Nothing */
#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_WIDE_XML_CPP(className) /* Nothing */
#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_WIDE_XML_CPP(className) /* Nothing */
#endif // _QX_SERIALIZE_WIDE_XML

#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_HPP(dllImportExport, className) \
namespace boost { \
namespace serialization { \
\
QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_POLYMORPHIC_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_BINARY_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_TEXT_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_XML_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_PORTABLE_BINARY_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_WIDE_BINARY_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_WIDE_TEXT_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_WIDE_XML_HPP(dllImportExport, className) \
\
template <class Archive> \
inline void serialize(Archive & ar, className & t, const unsigned int file_version) \
{ boost::serialization::split_free(ar, t, file_version); } \
\
} } // namespace boost::serialization

#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_HPP(dllImportExport, className) \
namespace boost { \
namespace serialization { \
\
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_POLYMORPHIC_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_BINARY_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_TEXT_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_XML_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_PORTABLE_BINARY_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_WIDE_BINARY_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_WIDE_TEXT_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_WIDE_XML_HPP(dllImportExport, className) \
\
} } // namespace boost::serialization

#define QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_CPP(className) \
namespace boost { \
namespace serialization { \
\
QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_POLYMORPHIC_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_BINARY_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_TEXT_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_XML_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_PORTABLE_BINARY_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_WIDE_BINARY_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_WIDE_TEXT_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_WIDE_XML_CPP(className) \
\
} } // namespace boost::serialization

#define QX_SERIALIZE_FAST_COMPIL_SERIALIZE_CPP(className) \
namespace boost { \
namespace serialization { \
\
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_POLYMORPHIC_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_BINARY_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_TEXT_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_XML_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_PORTABLE_BINARY_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_WIDE_BINARY_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_WIDE_TEXT_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SERIALIZE_WIDE_XML_CPP(className) \
\
} } // namespace boost::serialization

#endif // _QX_SERIALIZE_FAST_COMPIL_H_
#endif // _QX_ENABLE_BOOST_SERIALIZATION
