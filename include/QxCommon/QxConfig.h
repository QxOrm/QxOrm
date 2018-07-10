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

#define QX_VERSION   0x010108 // QxOrm version 1.1.8

#define _QX_SERIALIZE_POLYMORPHIC            0

#define _QX_SERIALIZE_BINARY                 (! _QX_SERIALIZE_POLYMORPHIC && 1)
#define _QX_SERIALIZE_TEXT                   (! _QX_SERIALIZE_POLYMORPHIC && 0)
#define _QX_SERIALIZE_XML                    (! _QX_SERIALIZE_POLYMORPHIC && 1)
#define _QX_SERIALIZE_PORTABLE_BINARY        (! _QX_SERIALIZE_POLYMORPHIC && 0)

/* -- Link error with VC++ 9.0 => Qt uses "-Zc:wchar_t-" option to compile and boost serialization library is compiled without this option -- */
#define _QX_SERIALIZE_WIDE_BINARY            (! _QX_SERIALIZE_POLYMORPHIC && 0)
#define _QX_SERIALIZE_WIDE_TEXT              (! _QX_SERIALIZE_POLYMORPHIC && 0)
#define _QX_SERIALIZE_WIDE_XML               (! _QX_SERIALIZE_POLYMORPHIC && 0)

#define _QX_USE_MEM_LEAK_DETECTION                                      0
#define _QX_USE_EXPORT_DLL_BOOST_SERIALIZATION_SINGLETON                1
#define _QX_USE_BOOST_SERIALIZE_REGISTER_HELPER                         0
#define _QX_USE_MODIFY_BOOST_SERIALIZATION_EXPORT_HPP                   0
#define _QX_USE_TRACE_CONSTRUCTOR_DESTRUCTOR                            0
#define _QX_WRITE_BOOST_CLASS_EXPORT_IN_HPP_FILE                        0
#define _QX_WRITE_BOOST_CLASS_EXPORT_IN_CPP_FILE                        1
#define _QX_INCLUDE_BOOST_SERIALIZE_EXPORT_HPP_INTO_QX_MEM_LEAK_HPP     1
#define _QX_INCLUDE_BOOST_SERIALIZE_ARCHIVE_IMPL_IPP                    0
#define _QX_MEM_LEAK_ONLY_KNOWN_SRC_FILE                                1
#define _QX_SUPPORT_BOOST_SERIALIZE_SHARED_PTR_132                      0
#define _QX_USE_QX_STRING_CVT_EXPORT                                    0
#define _QX_USE_GCC_EXPORT_ALL_SYMBOLS                                  1
#define _QX_USE_GCC_VISIBILITY                                          0
#define _QX_USE_ASSERT                                                  1
#define _QX_ENABLE_QT_GUI_DEPENDENCY                                    1
#define _QX_ENABLE_QT_NETWORK_DEPENDENCY                                1

#ifdef _MSC_VER
/* -- Link error with VC++ 9.0 => Qt uses "-Zc:wchar_t-" option to compile and boost serialization library is compiled without this option -- */
#define _QX_USE_SERIALIZE_POLYMORPHIC_PATCH  (_QX_SERIALIZE_POLYMORPHIC && 1)
#else // _MSC_VER
#define _QX_USE_SERIALIZE_POLYMORPHIC_PATCH  0
#endif // _MSC_VER

#endif // _QX_CONFIG_H_
