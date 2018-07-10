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

#ifndef _QX_ARCHIVE_WIDE_TRAITS_H_
#define _QX_ARCHIVE_WIDE_TRAITS_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include <boost/mpl/if.hpp>
#include <boost/mpl/logical.hpp>

#include <QtCore/qstring.h>

#include "../../include/QxSerialize/boost/QxSerializeInclude.h"

namespace qx {
namespace trait {

template <typename T> struct is_archive_wide { enum { value = false }; };

#if _QX_SERIALIZE_WIDE_BINARY
template <> struct is_archive_wide<boost::archive::binary_wiarchive> { enum { value = true }; };
template <> struct is_archive_wide<boost::archive::binary_woarchive> { enum { value = true }; };
#endif // _QX_SERIALIZE_WIDE_BINARY

#if _QX_SERIALIZE_WIDE_TEXT
template <> struct is_archive_wide<boost::archive::text_wiarchive>   { enum { value = true }; };
template <> struct is_archive_wide<boost::archive::text_woarchive>   { enum { value = true }; };
#endif // _QX_SERIALIZE_WIDE_TEXT

#if _QX_SERIALIZE_WIDE_XML
template <> struct is_archive_wide<boost::archive::xml_wiarchive>    { enum { value = true }; };
template <> struct is_archive_wide<boost::archive::xml_woarchive>    { enum { value = true }; };
#endif // _QX_SERIALIZE_WIDE_XML

template <typename T>
class archive_wide_traits
{

public:

   enum { is_wide = qx::trait::is_archive_wide<T>::value };

   typedef typename boost::mpl::if_c<is_wide, wchar_t, char>::type type_char;
   typedef typename boost::mpl::if_c<is_wide, std::wstring, std::string>::type type_string;

   typedef typename boost::mpl::if_c<is_wide, std::wistream, std::istream>::type type_istream;
   typedef typename boost::mpl::if_c<is_wide, std::wostream, std::ostream>::type type_ostream;

   typedef typename boost::mpl::if_c<is_wide, std::wstringstream, std::stringstream>::type type_stringstream;
   typedef typename boost::mpl::if_c<is_wide, std::wistringstream, std::istringstream>::type type_istringstream;
   typedef typename boost::mpl::if_c<is_wide, std::wostringstream, std::ostringstream>::type type_ostringstream;

   typedef typename boost::mpl::if_c<is_wide, std::wfstream, std::fstream>::type type_fstream;
   typedef typename boost::mpl::if_c<is_wide, std::wifstream, std::ifstream>::type type_ifstream;
   typedef typename boost::mpl::if_c<is_wide, std::wofstream, std::ofstream>::type type_ofstream;

   static inline QString toQString(const type_string & str)    { return qx::trait::archive_wide_traits<T>::cvtQString<is_wide, 0>::toQString(str); };
   static inline type_string fromQString(const QString & str)  { return qx::trait::archive_wide_traits<T>::cvtQString<is_wide, 0>::fromQString(str); };

private:

   template <bool isWide /* = false */, int dummy>
   struct cvtQString
   {
      static inline QString toQString(const std::string & str)    { return QString::fromStdString(str); };
      static inline std::string fromQString(const QString & str)  { return str.toStdString(); };
   };

   template <int dummy>
   struct cvtQString<true, dummy>
   {
      static inline QString toQString(const std::wstring & str)      { return QString::fromStdWString(str); };
      static inline std::wstring fromQString(const QString & str)    { return str.toStdWString(); };
   };

};

} // namespace trait
} // namespace qx

#endif // _QX_ARCHIVE_WIDE_TRAITS_H_
