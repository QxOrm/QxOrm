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

#ifndef _QX_ARCHIVE_H_
#define _QX_ARCHIVE_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>

#include <boost/archive/archive_exception.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>

#include "../../include/QxTraits/archive_wide_traits.h"
#include "../../include/QxTraits/get_class_name.h"
#include "../../include/QxTraits/is_qx_registered.h"

#include "../../include/QxCommon/QxConfig.h"
#include "../../include/QxCommon/QxBool.h"

#include "../../include/QxRegister/QxClass.h"
#include "../../include/QxRegister/QxClassName.h"

#include "../../include/QxSerialize/QxSerializeMacro.h"
#include "../../include/QxSerialize/boost/QxSerializeInclude.h"
#include "../../include/QxSerialize/QxBoostSerializeHelper/QxBoostSerializeRegisterHelperX.h"

#define QX_STR_SERIALIZATION_ERROR "Serialization error : '%ERR%'"
#define QX_STR_DESERIALIZATION_ERROR "Deserialization error : '%ERR%'"

namespace qx {

template <class T, class ArchiveInput = QX_DEFAULT_ARCHIVE_INPUT, class ArchiveOutput = QX_DEFAULT_ARCHIVE_OUTPUT>
class QxArchive
{

public:

   static qx_bool toFile(const T & obj, const QString & sFileName, unsigned int flags = boost::archive::no_header);
   static qx_bool fromFile(T & obj, const QString & sFileName, unsigned int flags = boost::archive::no_header);

   static qx_bool toFileCompressed(const T & obj, const QString & sFileName, unsigned int flags = boost::archive::no_header, int iCompressionLevel = -1);
   static qx_bool fromFileCompressed(T & obj, const QString & sFileName, unsigned int flags = boost::archive::no_header);

   static QString toString(const T & obj, unsigned int flags = boost::archive::no_header);
   static qx_bool fromString(T & obj, const QString & sString, unsigned int flags = boost::archive::no_header);

   static qx_bool toNetwork(const T & obj, unsigned int flags = boost::archive::no_header);
   static qx_bool fromNetwork(T & obj, unsigned int flags = boost::archive::no_header);

   static qx_bool toNetworkCompressed(const T & obj, unsigned int flags = boost::archive::no_header);
   static qx_bool fromNetworkCompressed(T & obj, unsigned int flags = boost::archive::no_header);

};

} // namespace qx

#include "../../inl/QxSerialize/QxArchive.inl"

namespace qx {
namespace serialization {

QX_ARCHIVE_NAMESPACE_FCT_IMPL(T, QX_DEFAULT_ARCHIVE_INPUT, QX_DEFAULT_ARCHIVE_OUTPUT)

#if _QX_SERIALIZE_POLYMORPHIC
namespace polymorphic_binary {      QX_ARCHIVE_NAMESPACE_FCT_IMPL(T, boost::archive::polymorphic_binary_iarchive, boost::archive::polymorphic_binary_oarchive)
} // namespace polymorphic_binary
namespace polymorphic_text {        QX_ARCHIVE_NAMESPACE_FCT_IMPL(T, boost::archive::polymorphic_text_iarchive, boost::archive::polymorphic_text_oarchive)
} // namespace polymorphic_text
namespace polymorphic_xml {         QX_ARCHIVE_NAMESPACE_FCT_IMPL(T, boost::archive::polymorphic_xml_iarchive, boost::archive::polymorphic_xml_oarchive)
} // namespace polymorphic_xml
#endif // _QX_SERIALIZE_POLYMORPHIC

#if _QX_SERIALIZE_BINARY
namespace binary {            QX_ARCHIVE_NAMESPACE_FCT_IMPL(T, boost::archive::binary_iarchive, boost::archive::binary_oarchive)
} // namespace binary
#endif // _QX_SERIALIZE_BINARY

#if _QX_SERIALIZE_TEXT
namespace text {              QX_ARCHIVE_NAMESPACE_FCT_IMPL(T, boost::archive::text_iarchive, boost::archive::text_oarchive)
} // namespace text
#endif // _QX_SERIALIZE_TEXT

#if _QX_SERIALIZE_XML
namespace xml {               QX_ARCHIVE_NAMESPACE_FCT_IMPL(T, boost::archive::xml_iarchive, boost::archive::xml_oarchive)
} // namespace xml
#endif // _QX_SERIALIZE_XML

#if _QX_SERIALIZE_PORTABLE_BINARY
namespace portable_binary {   QX_ARCHIVE_NAMESPACE_FCT_IMPL(T, eos::portable_iarchive, eos::portable_oarchive)
} // namespace portable_binary
#endif // _QX_SERIALIZE_PORTABLE_BINARY

namespace wide {

#if _QX_SERIALIZE_WIDE_BINARY
namespace binary {            QX_ARCHIVE_NAMESPACE_FCT_IMPL(T, boost::archive::binary_wiarchive, boost::archive::binary_woarchive)
} // namespace binary
#endif // _QX_SERIALIZE_WIDE_BINARY

#if _QX_SERIALIZE_WIDE_TEXT
namespace text {              QX_ARCHIVE_NAMESPACE_FCT_IMPL(T, boost::archive::text_wiarchive, boost::archive::text_woarchive)
} // namespace text
#endif // _QX_SERIALIZE_WIDE_TEXT

#if _QX_SERIALIZE_WIDE_XML
namespace xml {               QX_ARCHIVE_NAMESPACE_FCT_IMPL(T, boost::archive::xml_wiarchive, boost::archive::xml_woarchive)
} // namespace xml
#endif // _QX_SERIALIZE_WIDE_XML

} // namespace wide
} // namespace serialization
} // namespace qx

#endif // _QX_ARCHIVE_H_
