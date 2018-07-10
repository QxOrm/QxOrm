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

#ifndef _QX_SERIALIZE_MACRO_H_
#define _QX_SERIALIZE_MACRO_H_

#ifdef _MSC_VER
#pragma once
#endif

#define QX_ARCHIVE_NAMESPACE_FCT_IMPL(T, INPUT, OUTPUT) \
\
template <class T> \
inline qx_bool to_file(const T & obj, const QString & sFileName, unsigned int flags = boost::archive::no_header) { return qx::QxArchive<T, INPUT, OUTPUT>::toFile(obj, sFileName, flags); }; \
\
template <class T> \
inline qx_bool from_file(T & obj, const QString & sFileName, unsigned int flags = boost::archive::no_header) { return qx::QxArchive<T, INPUT, OUTPUT>::fromFile(obj, sFileName, flags); }; \
\
template <class T> \
inline qx_bool to_file_compressed(const T & obj, const QString & sFileName, unsigned int flags = boost::archive::no_header, int iCompressionLevel = -1) { return qx::QxArchive<T, INPUT, OUTPUT>::toFileCompressed(obj, sFileName, flags, iCompressionLevel); }; \
\
template <class T> \
inline qx_bool from_file_compressed(T & obj, const QString & sFileName, unsigned int flags = boost::archive::no_header) { return qx::QxArchive<T, INPUT, OUTPUT>::fromFileCompressed(obj, sFileName, flags); }; \
\
template <class T> \
inline QString to_string(const T & obj, unsigned int flags = boost::archive::no_header) { return qx::QxArchive<T, INPUT, OUTPUT>::toString(obj, flags); }; \
\
template <class T> \
inline qx_bool from_string(T & obj, const QString & sString, unsigned int flags = boost::archive::no_header) { return qx::QxArchive<T, INPUT, OUTPUT>::fromString(obj, sString, flags); }; \
\
template <class T> \
inline QByteArray to_byte_array(const T & obj, typename qx::trait::archive_wide_traits< INPUT >::type_string * owner = NULL, unsigned int flags = boost::archive::no_header) { return qx::QxArchive<T, INPUT, OUTPUT>::toByteArray(obj, owner, flags); }; \
\
template <class T> \
inline qx_bool from_byte_array(T & obj, const QByteArray & data, unsigned int flags = boost::archive::no_header) { return qx::QxArchive<T, INPUT, OUTPUT>::fromByteArray(obj, data, flags); }; \
\

#endif // _QX_SERIALIZE_MACRO_H_
