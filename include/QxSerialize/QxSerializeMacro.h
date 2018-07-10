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
#ifndef _QX_SERIALIZE_MACRO_H_
#define _QX_SERIALIZE_MACRO_H_

#ifdef _MSC_VER
#pragma once
#endif

#define QX_ARCHIVE_NAMESPACE_FCT_IMPL(T, INPUT, OUTPUT) \
\
template <class T> \
inline qx_bool to_file(const T & obj, const QString & sFileName, unsigned int flags = boost::archive::no_header) { return qx::QxArchive_ToFile<T, INPUT, OUTPUT>::toFile(obj, sFileName, flags); }; \
\
template <class T> \
inline qx_bool from_file(T & obj, const QString & sFileName, unsigned int flags = boost::archive::no_header) { return qx::QxArchive_FromFile<T, INPUT, OUTPUT>::fromFile(obj, sFileName, flags); }; \
\
template <class T> \
inline qx_bool to_file_compressed(const T & obj, const QString & sFileName, unsigned int flags = boost::archive::no_header, int iCompressionLevel = -1) { return qx::QxArchive_ToFileCompressed<T, INPUT, OUTPUT>::toFileCompressed(obj, sFileName, flags, iCompressionLevel); }; \
\
template <class T> \
inline qx_bool from_file_compressed(T & obj, const QString & sFileName, unsigned int flags = boost::archive::no_header) { return qx::QxArchive_FromFileCompressed<T, INPUT, OUTPUT>::fromFileCompressed(obj, sFileName, flags); }; \
\
template <class T> \
inline QString to_string(const T & obj, unsigned int flags = boost::archive::no_header) { return qx::QxArchive_ToString<T, INPUT, OUTPUT>::toString(obj, flags); }; \
\
template <class T> \
inline qx_bool from_string(T & obj, const QString & sString, unsigned int flags = boost::archive::no_header) { return qx::QxArchive_FromString<T, INPUT, OUTPUT>::fromString(obj, sString, flags); }; \
\
template <class T> \
inline QByteArray to_byte_array(const T & obj, typename qx::trait::archive_wide_traits< INPUT >::type_string * owner = NULL, unsigned int flags = boost::archive::no_header) { return qx::QxArchive_ToByteArray<T, INPUT, OUTPUT>::toByteArray(obj, owner, flags); }; \
\
template <class T> \
inline qx_bool from_byte_array(T & obj, const QByteArray & data, unsigned int flags = boost::archive::no_header) { return qx::QxArchive_FromByteArray<T, INPUT, OUTPUT>::fromByteArray(obj, data, flags); }; \
\

#endif // _QX_SERIALIZE_MACRO_H_
#endif // _QX_ENABLE_BOOST_SERIALIZATION
