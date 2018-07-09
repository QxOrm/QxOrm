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
inline qx_bool to_network(const T & obj, unsigned int flags = boost::archive::no_header) { return qx::QxArchive<T, INPUT, OUTPUT>::toNetwork(obj, flags); }; \
\
template <class T> \
inline qx_bool from_network(T & obj, unsigned int flags = boost::archive::no_header) { return qx::QxArchive<T, INPUT, OUTPUT>::fromNetwork(obj, flags); }; \
\
template <class T> \
inline qx_bool to_network_compressed(const T & obj, unsigned int flags = boost::archive::no_header) { return qx::QxArchive<T, INPUT, OUTPUT>::toNetworkCompressed(obj, flags); }; \
\
template <class T> \
inline qx_bool from_network_compressed(T & obj, unsigned int flags = boost::archive::no_header) { return qx::QxArchive<T, INPUT, OUTPUT>::fromNetworkCompressed(obj, flags); }; \
\

#endif // _QX_SERIALIZE_MACRO_H_
