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
#ifndef _QX_ARCHIVE_H_
#define _QX_ARCHIVE_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxArchive.h
 * \author Lionel Marty
 * \ingroup QxSerialize
 * \brief Provide some tools to serialize a class registered into QxOrm context into/from binary/XML archive (file, string, etc.)
 */

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>

#include <boost/archive/archive_exception.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>

#include <QxTraits/archive_wide_traits.h>
#include <QxTraits/get_class_name.h>
#include <QxTraits/is_qx_registered.h>

#include <QxCommon/QxConfig.h>
#include <QxCommon/QxBool.h>

#include <QxRegister/QxClass.h>
#include <QxRegister/QxClassName.h>

#include <QxSerialize/QxSerializeMacro.h>
#include <QxSerialize/boost/QxSerializeInclude.h>
#include <QxSerialize/QxBoostSerializeHelper/QxBoostSerializeRegisterHelperX.h>

#define QX_STR_SERIALIZATION_ERROR "Serialization error : '%ERR%'"
#define QX_STR_DESERIALIZATION_ERROR "Deserialization error : '%ERR%'"

namespace qx {

/*!
 * \ingroup QxSerialize
 * \brief qx::QxArchive_ToFile : provide some tools to serialize a class registered into QxOrm context into/from binary/text/XML archives (file, string, etc.)
 */
template <class T, class ArchiveInput = QX_DEFAULT_ARCHIVE_INPUT, class ArchiveOutput = QX_DEFAULT_ARCHIVE_OUTPUT>
class QxArchive_ToFile
{ public: static qx_bool toFile(const T & obj, const QString & sFileName, unsigned int flags = boost::archive::no_header); };

/*!
 * \ingroup QxSerialize
 * \brief qx::QxArchive_FromFile : provide some tools to serialize a class registered into QxOrm context into/from binary/text/XML archives (file, string, etc.)
 */
template <class T, class ArchiveInput = QX_DEFAULT_ARCHIVE_INPUT, class ArchiveOutput = QX_DEFAULT_ARCHIVE_OUTPUT>
class QxArchive_FromFile
{ public: static qx_bool fromFile(T & obj, const QString & sFileName, unsigned int flags = boost::archive::no_header); };

/*!
 * \ingroup QxSerialize
 * \brief qx::QxArchive_ToFileCompressed : provide some tools to serialize a class registered into QxOrm context into/from binary/text/XML archives (file, string, etc.)
 */
template <class T, class ArchiveInput = QX_DEFAULT_ARCHIVE_INPUT, class ArchiveOutput = QX_DEFAULT_ARCHIVE_OUTPUT>
class QxArchive_ToFileCompressed
{ public: static qx_bool toFileCompressed(const T & obj, const QString & sFileName, unsigned int flags = boost::archive::no_header, int iCompressionLevel = -1); };

/*!
 * \ingroup QxSerialize
 * \brief qx::QxArchive_FromFileCompressed : provide some tools to serialize a class registered into QxOrm context into/from binary/text/XML archives (file, string, etc.)
 */
template <class T, class ArchiveInput = QX_DEFAULT_ARCHIVE_INPUT, class ArchiveOutput = QX_DEFAULT_ARCHIVE_OUTPUT>
class QxArchive_FromFileCompressed
{ public: static qx_bool fromFileCompressed(T & obj, const QString & sFileName, unsigned int flags = boost::archive::no_header); };

/*!
 * \ingroup QxSerialize
 * \brief qx::QxArchive_ToString : provide some tools to serialize a class registered into QxOrm context into/from binary/text/XML archives (file, string, etc.)
 */
template <class T, class ArchiveInput = QX_DEFAULT_ARCHIVE_INPUT, class ArchiveOutput = QX_DEFAULT_ARCHIVE_OUTPUT>
class QxArchive_ToString
{ public: static QString toString(const T & obj, unsigned int flags = boost::archive::no_header); };

/*!
 * \ingroup QxSerialize
 * \brief qx::QxArchive_FromString : provide some tools to serialize a class registered into QxOrm context into/from binary/text/XML archives (file, string, etc.)
 */
template <class T, class ArchiveInput = QX_DEFAULT_ARCHIVE_INPUT, class ArchiveOutput = QX_DEFAULT_ARCHIVE_OUTPUT>
class QxArchive_FromString
{ public: static qx_bool fromString(T & obj, const QString & sString, unsigned int flags = boost::archive::no_header); };

/*!
 * \ingroup QxSerialize
 * \brief qx::QxArchive_ToByteArray : provide some tools to serialize a class registered into QxOrm context into/from binary/text/XML archives (file, string, etc.)
 */
template <class T, class ArchiveInput = QX_DEFAULT_ARCHIVE_INPUT, class ArchiveOutput = QX_DEFAULT_ARCHIVE_OUTPUT>
class QxArchive_ToByteArray
{ public: typedef typename qx::trait::archive_wide_traits<ArchiveInput>::type_string type_string; static QByteArray toByteArray(const T & obj, type_string * owner = NULL, unsigned int flags = boost::archive::no_header); };

/*!
 * \ingroup QxSerialize
 * \brief qx::QxArchive_FromByteArray : provide some tools to serialize a class registered into QxOrm context into/from binary/text/XML archives (file, string, etc.)
 */
template <class T, class ArchiveInput = QX_DEFAULT_ARCHIVE_INPUT, class ArchiveOutput = QX_DEFAULT_ARCHIVE_OUTPUT>
class QxArchive_FromByteArray
{ public: static qx_bool fromByteArray(T & obj, const QByteArray & data, unsigned int flags = boost::archive::no_header); };

} // namespace qx

#include "../../inl/QxSerialize/QxArchive.inl"

namespace qx {
namespace serialization {

QX_ARCHIVE_NAMESPACE_FCT_IMPL(T, QX_DEFAULT_ARCHIVE_INPUT, QX_DEFAULT_ARCHIVE_OUTPUT)

#if _QX_SERIALIZE_POLYMORPHIC

/*!
 * \ingroup QxSerialize
 * \brief serialize a class registered into QxOrm context into/from polymorphic_binary archive (file, string, etc.) : enable this feature defining _QX_ENABLE_BOOST_SERIALIZATION and _QX_ENABLE_BOOST_SERIALIZATION_POLYMORPHIC compilation options in QxOrm.pri configuration file
 */
namespace polymorphic_binary {      QX_ARCHIVE_NAMESPACE_FCT_IMPL(T, boost::archive::polymorphic_binary_iarchive, boost::archive::polymorphic_binary_oarchive)
} // namespace polymorphic_binary

/*!
 * \ingroup QxSerialize
 * \brief serialize a class registered into QxOrm context into/from polymorphic_text archive (file, string, etc.) : enable this feature defining _QX_ENABLE_BOOST_SERIALIZATION and _QX_ENABLE_BOOST_SERIALIZATION_POLYMORPHIC compilation options in QxOrm.pri configuration file
 */
namespace polymorphic_text {        QX_ARCHIVE_NAMESPACE_FCT_IMPL(T, boost::archive::polymorphic_text_iarchive, boost::archive::polymorphic_text_oarchive)
} // namespace polymorphic_text

/*!
 * \ingroup QxSerialize
 * \brief serialize a class registered into QxOrm context into/from polymorphic_xml archive (file, string, etc.) : enable this feature defining _QX_ENABLE_BOOST_SERIALIZATION and _QX_ENABLE_BOOST_SERIALIZATION_POLYMORPHIC compilation options in QxOrm.pri configuration file
 */
namespace polymorphic_xml {         QX_ARCHIVE_NAMESPACE_FCT_IMPL(T, boost::archive::polymorphic_xml_iarchive, boost::archive::polymorphic_xml_oarchive)
} // namespace polymorphic_xml

#endif // _QX_SERIALIZE_POLYMORPHIC

#if _QX_SERIALIZE_BINARY

/*!
 * \ingroup QxSerialize
 * \brief serialize a class registered into QxOrm context into/from binary archive (file, string, etc.) : enable this feature defining _QX_ENABLE_BOOST_SERIALIZATION and _QX_ENABLE_BOOST_SERIALIZATION_BINARY compilation options in QxOrm.pri configuration file
 */
namespace binary {            QX_ARCHIVE_NAMESPACE_FCT_IMPL(T, boost::archive::binary_iarchive, boost::archive::binary_oarchive)
} // namespace binary

#endif // _QX_SERIALIZE_BINARY

#if _QX_SERIALIZE_TEXT

/*!
 * \ingroup QxSerialize
 * \brief serialize a class registered into QxOrm context into/from text archive (file, string, etc.) : enable this feature defining _QX_ENABLE_BOOST_SERIALIZATION and _QX_ENABLE_BOOST_SERIALIZATION_TEXT compilation options in QxOrm.pri configuration file
 */
namespace text {              QX_ARCHIVE_NAMESPACE_FCT_IMPL(T, boost::archive::text_iarchive, boost::archive::text_oarchive)
} // namespace text

#endif // _QX_SERIALIZE_TEXT

#if _QX_SERIALIZE_XML

/*!
 * \ingroup QxSerialize
 * \brief serialize a class registered into QxOrm context into/from XML archive (file, string, etc.) : enable this feature defining _QX_ENABLE_BOOST_SERIALIZATION and _QX_ENABLE_BOOST_SERIALIZATION_XML compilation options in QxOrm.pri configuration file
 */
namespace xml {               QX_ARCHIVE_NAMESPACE_FCT_IMPL(T, boost::archive::xml_iarchive, boost::archive::xml_oarchive)
} // namespace xml

#endif // _QX_SERIALIZE_XML

#if _QX_SERIALIZE_PORTABLE_BINARY

/*!
 * \ingroup QxSerialize
 * \brief serialize a class registered into QxOrm context into/from portable_binary archive (file, string, etc.) : enable this feature defining _QX_ENABLE_BOOST_SERIALIZATION and _QX_ENABLE_BOOST_SERIALIZATION_PORTABLE_BINARY compilation options in QxOrm.pri configuration file
 */
namespace portable_binary {   QX_ARCHIVE_NAMESPACE_FCT_IMPL(T, eos::portable_iarchive, eos::portable_oarchive)
} // namespace portable_binary

#endif // _QX_SERIALIZE_PORTABLE_BINARY

namespace wide {

#if _QX_SERIALIZE_WIDE_BINARY

/*!
 * \ingroup QxSerialize
 * \brief serialize a class registered into QxOrm context into/from wide binary archive (file, string, etc.) : enable this feature defining _QX_ENABLE_BOOST_SERIALIZATION and _QX_ENABLE_BOOST_SERIALIZATION_WIDE_BINARY compilation options in QxOrm.pri configuration file
 */
namespace binary {            QX_ARCHIVE_NAMESPACE_FCT_IMPL(T, boost::archive::binary_wiarchive, boost::archive::binary_woarchive)
} // namespace binary

#endif // _QX_SERIALIZE_WIDE_BINARY

#if _QX_SERIALIZE_WIDE_TEXT

/*!
 * \ingroup QxSerialize
 * \brief serialize a class registered into QxOrm context into/from wide text archive (file, string, etc.) : enable this feature defining _QX_ENABLE_BOOST_SERIALIZATION and _QX_ENABLE_BOOST_SERIALIZATION_WIDE_TEXT compilation options in QxOrm.pri configuration file
 */
namespace text {              QX_ARCHIVE_NAMESPACE_FCT_IMPL(T, boost::archive::text_wiarchive, boost::archive::text_woarchive)
} // namespace text

#endif // _QX_SERIALIZE_WIDE_TEXT

#if _QX_SERIALIZE_WIDE_XML

/*!
 * \ingroup QxSerialize
 * \brief serialize a class registered into QxOrm context into/from wide XML archive (file, string, etc.) : enable this feature defining _QX_ENABLE_BOOST_SERIALIZATION and _QX_ENABLE_BOOST_SERIALIZATION_WIDE_XML compilation options in QxOrm.pri configuration file
 */
namespace xml {               QX_ARCHIVE_NAMESPACE_FCT_IMPL(T, boost::archive::xml_wiarchive, boost::archive::xml_woarchive)
} // namespace xml

#endif // _QX_SERIALIZE_WIDE_XML

} // namespace wide
} // namespace serialization
} // namespace qx

#endif // _QX_ARCHIVE_H_
#endif // _QX_ENABLE_BOOST_SERIALIZATION
