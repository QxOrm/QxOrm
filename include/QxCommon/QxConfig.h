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

#ifndef _QX_CONFIG_H_
#define _QX_CONFIG_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxConfig.h
 * \author Lionel Marty
 * \ingroup QxCommon
 * \brief List of parameters to compile and build QxOrm library
 */

#define QX_VERSION         0x010404
#define QX_VERSION_STR     "1.4.4"

#ifndef _QX_MODE_DEBUG
#ifndef _QX_MODE_RELEASE
#ifdef QT_NO_DEBUG
#define _QX_MODE_RELEASE
#else // QT_NO_DEBUG
#define _QX_MODE_DEBUG
#endif // QT_NO_DEBUG
#endif // _QX_MODE_RELEASE
#endif // _QX_MODE_DEBUG

#ifndef _QX_ENABLE_BOOST_SERIALIZATION_BINARY
#ifndef _QX_ENABLE_BOOST_SERIALIZATION_XML
#ifndef _QX_ENABLE_BOOST_SERIALIZATION_POLYMORPHIC
#ifndef _QX_ENABLE_BOOST_SERIALIZATION_TEXT
#ifndef _QX_ENABLE_BOOST_SERIALIZATION_PORTABLE_BINARY
#ifndef _QX_ENABLE_BOOST_SERIALIZATION_WIDE_BINARY
#ifndef _QX_ENABLE_BOOST_SERIALIZATION_WIDE_TEXT
#ifndef _QX_ENABLE_BOOST_SERIALIZATION_WIDE_XML
#define _QX_ENABLE_BOOST_SERIALIZATION_BINARY
#define _QX_ENABLE_BOOST_SERIALIZATION_XML
#endif // _QX_ENABLE_BOOST_SERIALIZATION_WIDE_XML
#endif // _QX_ENABLE_BOOST_SERIALIZATION_WIDE_TEXT
#endif // _QX_ENABLE_BOOST_SERIALIZATION_WIDE_BINARY
#endif // _QX_ENABLE_BOOST_SERIALIZATION_PORTABLE_BINARY
#endif // _QX_ENABLE_BOOST_SERIALIZATION_TEXT
#endif // _QX_ENABLE_BOOST_SERIALIZATION_POLYMORPHIC
#endif // _QX_ENABLE_BOOST_SERIALIZATION_XML
#endif // _QX_ENABLE_BOOST_SERIALIZATION_BINARY

#ifndef _QX_ENABLE_BOOST_SERIALIZATION
#ifdef _QX_ENABLE_BOOST_SERIALIZATION_BINARY
#undef _QX_ENABLE_BOOST_SERIALIZATION_BINARY
#endif // _QX_ENABLE_BOOST_SERIALIZATION_BINARY
#ifdef _QX_ENABLE_BOOST_SERIALIZATION_XML
#undef _QX_ENABLE_BOOST_SERIALIZATION_XML
#endif // _QX_ENABLE_BOOST_SERIALIZATION_XML
#ifdef _QX_ENABLE_BOOST_SERIALIZATION_POLYMORPHIC
#undef _QX_ENABLE_BOOST_SERIALIZATION_POLYMORPHIC
#endif // _QX_ENABLE_BOOST_SERIALIZATION_POLYMORPHIC
#ifdef _QX_ENABLE_BOOST_SERIALIZATION_TEXT
#undef _QX_ENABLE_BOOST_SERIALIZATION_TEXT
#endif // _QX_ENABLE_BOOST_SERIALIZATION_TEXT
#ifdef _QX_ENABLE_BOOST_SERIALIZATION_PORTABLE_BINARY
#undef _QX_ENABLE_BOOST_SERIALIZATION_PORTABLE_BINARY
#endif // _QX_ENABLE_BOOST_SERIALIZATION_PORTABLE_BINARY
#ifdef _QX_ENABLE_BOOST_SERIALIZATION_WIDE_BINARY
#undef _QX_ENABLE_BOOST_SERIALIZATION_WIDE_BINARY
#endif // _QX_ENABLE_BOOST_SERIALIZATION_WIDE_BINARY
#ifdef _QX_ENABLE_BOOST_SERIALIZATION_WIDE_TEXT
#undef _QX_ENABLE_BOOST_SERIALIZATION_WIDE_TEXT
#endif // _QX_ENABLE_BOOST_SERIALIZATION_WIDE_TEXT
#ifdef _QX_ENABLE_BOOST_SERIALIZATION_WIDE_XML
#undef _QX_ENABLE_BOOST_SERIALIZATION_WIDE_XML
#endif // _QX_ENABLE_BOOST_SERIALIZATION_WIDE_XML
#endif // _QX_ENABLE_BOOST_SERIALIZATION

#ifdef _QX_ENABLE_BOOST_SERIALIZATION_POLYMORPHIC
#define _QX_SERIALIZE_POLYMORPHIC            1
#else // _QX_ENABLE_BOOST_SERIALIZATION_POLYMORPHIC
#define _QX_SERIALIZE_POLYMORPHIC            0
#endif // _QX_ENABLE_BOOST_SERIALIZATION_POLYMORPHIC

#ifdef _QX_ENABLE_BOOST_SERIALIZATION_BINARY
#define _QX_SERIALIZE_BINARY                 (! _QX_SERIALIZE_POLYMORPHIC && 1)
#else // _QX_ENABLE_BOOST_SERIALIZATION_BINARY
#define _QX_SERIALIZE_BINARY                 (! _QX_SERIALIZE_POLYMORPHIC && 0)
#endif // _QX_ENABLE_BOOST_SERIALIZATION_BINARY

#ifdef _QX_ENABLE_BOOST_SERIALIZATION_TEXT
#define _QX_SERIALIZE_TEXT                   (! _QX_SERIALIZE_POLYMORPHIC && 1)
#else // _QX_ENABLE_BOOST_SERIALIZATION_TEXT
#define _QX_SERIALIZE_TEXT                   (! _QX_SERIALIZE_POLYMORPHIC && 0)
#endif // _QX_ENABLE_BOOST_SERIALIZATION_TEXT

#ifdef _QX_ENABLE_BOOST_SERIALIZATION_XML
#define _QX_SERIALIZE_XML                    (! _QX_SERIALIZE_POLYMORPHIC && 1)
#else // _QX_ENABLE_BOOST_SERIALIZATION_XML
#define _QX_SERIALIZE_XML                    (! _QX_SERIALIZE_POLYMORPHIC && 0)
#endif // _QX_ENABLE_BOOST_SERIALIZATION_XML

#ifdef _QX_ENABLE_BOOST_SERIALIZATION_PORTABLE_BINARY
#define _QX_SERIALIZE_PORTABLE_BINARY        (! _QX_SERIALIZE_POLYMORPHIC && 1)
#else // _QX_ENABLE_BOOST_SERIALIZATION_PORTABLE_BINARY
#define _QX_SERIALIZE_PORTABLE_BINARY        (! _QX_SERIALIZE_POLYMORPHIC && 0)
#endif // _QX_ENABLE_BOOST_SERIALIZATION_PORTABLE_BINARY

#ifdef _QX_ENABLE_BOOST_SERIALIZATION_WIDE_BINARY
#define _QX_SERIALIZE_WIDE_BINARY            (! _QX_SERIALIZE_POLYMORPHIC && 1)
#else // _QX_ENABLE_BOOST_SERIALIZATION_WIDE_BINARY
#define _QX_SERIALIZE_WIDE_BINARY            (! _QX_SERIALIZE_POLYMORPHIC && 0)
#endif // _QX_ENABLE_BOOST_SERIALIZATION_WIDE_BINARY

#ifdef _QX_ENABLE_BOOST_SERIALIZATION_WIDE_TEXT
#define _QX_SERIALIZE_WIDE_TEXT              (! _QX_SERIALIZE_POLYMORPHIC && 1)
#else // _QX_ENABLE_BOOST_SERIALIZATION_WIDE_TEXT
#define _QX_SERIALIZE_WIDE_TEXT              (! _QX_SERIALIZE_POLYMORPHIC && 0)
#endif // _QX_ENABLE_BOOST_SERIALIZATION_WIDE_TEXT

#ifdef _QX_ENABLE_BOOST_SERIALIZATION_WIDE_XML
#define _QX_SERIALIZE_WIDE_XML               (! _QX_SERIALIZE_POLYMORPHIC && 1)
#else // _QX_ENABLE_BOOST_SERIALIZATION_WIDE_XML
#define _QX_SERIALIZE_WIDE_XML               (! _QX_SERIALIZE_POLYMORPHIC && 0)
#endif // _QX_ENABLE_BOOST_SERIALIZATION_WIDE_XML

#define _QX_AUTO_REGISTER_REPOSITORY                                    0
#define _QX_USE_MEM_LEAK_DETECTION                                      0
#define _QX_USE_EXPORT_DLL_BOOST_SERIALIZATION_SINGLETON                1
#define _QX_USE_BOOST_SERIALIZE_REGISTER_HELPER                         0
#define _QX_USE_MODIFY_BOOST_SERIALIZATION_EXPORT_HPP                   0
#define _QX_WRITE_BOOST_CLASS_EXPORT_IN_HPP_FILE                        0
#define _QX_WRITE_BOOST_CLASS_EXPORT_IN_CPP_FILE                        1
#define _QX_INCLUDE_BOOST_SERIALIZE_EXPORT_HPP_INTO_QX_MEM_LEAK_HPP     1
#define _QX_INCLUDE_BOOST_SERIALIZE_ARCHIVE_IMPL_IPP                    0
#define _QX_MEM_LEAK_ONLY_KNOWN_SRC_FILE                                1
#define _QX_SUPPORT_BOOST_SERIALIZE_SHARED_PTR_132                      0
#define _QX_USE_QX_CONVERT_EXPORT                                       0
#define _QX_USE_GCC_EXPORT_ALL_SYMBOLS                                  1
#define _QX_USE_GCC_VISIBILITY                                          0
#define _QX_USE_ASSERT                                                  1
#define _QX_SUPPORT_COVARIANT_RETURN_TYPE                               1
#define _QX_USE_QX_SINGLETON_X                                          1

#ifdef _MSC_VER
/* -- Link error with VC++ 9.0 => Qt uses "-Zc:wchar_t-" option to compile and boost serialization library is compiled without this option -- */
#define _QX_USE_SERIALIZE_POLYMORPHIC_PATCH  (_QX_SERIALIZE_POLYMORPHIC && 1)
#else // _MSC_VER
#define _QX_USE_SERIALIZE_POLYMORPHIC_PATCH  0
#endif // _MSC_VER

#if (QT_VERSION < 0x050000)
#ifndef _QX_NO_JSON
#define _QX_NO_JSON
#endif // _QX_NO_JSON
#endif // (QT_VERSION < 0x050000)

#endif // _QX_CONFIG_H_
