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
#ifndef _QX_SERIALIZE_INCLUDE_H_
#define _QX_SERIALIZE_INCLUDE_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QxCommon/QxConfig.h>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4189)
#pragma warning(disable:4996)
#endif // _MSC_VER

#if _QX_SERIALIZE_POLYMORPHIC
#include <boost/archive/polymorphic_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>
#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>
#include <boost/archive/polymorphic_xml_iarchive.hpp>
#include <boost/archive/polymorphic_xml_oarchive.hpp>
#endif // _QX_SERIALIZE_POLYMORPHIC

#if _QX_SERIALIZE_BINARY
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#endif // _QX_SERIALIZE_BINARY

#if _QX_SERIALIZE_TEXT
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#endif // _QX_SERIALIZE_TEXT

#if _QX_SERIALIZE_XML
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#endif // _QX_SERIALIZE_XML

#if _QX_SERIALIZE_PORTABLE_BINARY
#include <QxSerialize/boost/portable_binary/portable_iarchive.hpp>
#include <QxSerialize/boost/portable_binary/portable_oarchive.hpp>
#endif // _QX_SERIALIZE_PORTABLE_BINARY

#if _QX_SERIALIZE_WIDE_BINARY
#include <boost/archive/binary_wiarchive.hpp>
#include <boost/archive/binary_woarchive.hpp>
#endif // _QX_SERIALIZE_WIDE_BINARY

#if _QX_SERIALIZE_WIDE_TEXT
#include <boost/archive/text_wiarchive.hpp>
#include <boost/archive/text_woarchive.hpp>
#endif // _QX_SERIALIZE_WIDE_TEXT

#if _QX_SERIALIZE_WIDE_XML
#include <boost/archive/xml_wiarchive.hpp>
#include <boost/archive/xml_woarchive.hpp>
#endif // _QX_SERIALIZE_WIDE_XML

#ifndef _QX_BOOST_ARCHIVE_SERIALIZER_IMPL_DEFINED_
#define _QX_BOOST_ARCHIVE_SERIALIZER_IMPL_DEFINED_
#if (BOOST_VERSION > 103800)
#include <boost/archive/impl/archive_serializer_map.ipp>
#else // (BOOST_VERSION > 103800)
#include <boost/archive/impl/archive_pointer_oserializer.ipp>
#include <boost/archive/impl/archive_pointer_iserializer.ipp>
#endif // (BOOST_VERSION > 103800)
#include <boost/archive/impl/basic_binary_oprimitive.ipp>
#include <boost/archive/impl/basic_binary_iprimitive.ipp>
#include <boost/archive/impl/basic_binary_oarchive.ipp>
#include <boost/archive/impl/basic_binary_iarchive.ipp>
#if _QX_SERIALIZE_TEXT
#include <boost/archive/impl/basic_text_oprimitive.ipp>
#include <boost/archive/impl/basic_text_iprimitive.ipp>
#include <boost/archive/impl/basic_text_oarchive.ipp>
#include <boost/archive/impl/basic_text_iarchive.ipp>
#endif // _QX_SERIALIZE_TEXT
#if (BOOST_VERSION > 103800)
#else // (BOOST_VERSION > 103800)
#if _QX_INCLUDE_BOOST_SERIALIZE_ARCHIVE_IMPL_IPP
#if _QX_SERIALIZE_TEXT
#include <boost/archive/impl/text_oarchive_impl.ipp>
#include <boost/archive/impl/text_iarchive_impl.ipp>
#endif // _QX_SERIALIZE_TEXT
#if _QX_SERIALIZE_XML
#include <boost/archive/impl/xml_oarchive_impl.ipp>
#include <boost/archive/impl/xml_iarchive_impl.ipp>
#endif // _QX_SERIALIZE_XML
#if _QX_SERIALIZE_WIDE_TEXT
#include <boost/archive/impl/text_woarchive_impl.ipp>
#include <boost/archive/impl/text_wiarchive_impl.ipp>
#endif // _QX_SERIALIZE_WIDE_TEXT
#if _QX_SERIALIZE_WIDE_XML
#include <boost/archive/impl/xml_woarchive_impl.ipp>
#include <boost/archive/impl/xml_wiarchive_impl.ipp>
#endif // _QX_SERIALIZE_WIDE_XML
#endif // _QX_INCLUDE_BOOST_SERIALIZE_ARCHIVE_IMPL_IPP
#endif // (BOOST_VERSION > 103800)
#endif // _QX_BOOST_ARCHIVE_SERIALIZER_IMPL_DEFINED_

#ifdef _MSC_VER
#pragma warning(pop)
#endif // _MSC_VER

#ifndef QX_DEFAULT_ARCHIVE_INPUT // && QX_DEFAULT_ARCHIVE_OUTPUT
#if _QX_SERIALIZE_POLYMORPHIC
#define QX_DEFAULT_ARCHIVE_INPUT boost::archive::polymorphic_binary_iarchive
#define QX_DEFAULT_ARCHIVE_OUTPUT boost::archive::polymorphic_binary_oarchive
#elif _QX_SERIALIZE_BINARY
#define QX_DEFAULT_ARCHIVE_INPUT boost::archive::binary_iarchive
#define QX_DEFAULT_ARCHIVE_OUTPUT boost::archive::binary_oarchive
#elif _QX_SERIALIZE_TEXT
#define QX_DEFAULT_ARCHIVE_INPUT boost::archive::text_iarchive
#define QX_DEFAULT_ARCHIVE_OUTPUT boost::archive::text_oarchive
#elif _QX_SERIALIZE_XML
#define QX_DEFAULT_ARCHIVE_INPUT boost::archive::xml_iarchive
#define QX_DEFAULT_ARCHIVE_OUTPUT boost::archive::xml_oarchive
#elif _QX_SERIALIZE_PORTABLE_BINARY
#define QX_DEFAULT_ARCHIVE_INPUT eos::portable_iarchive
#define QX_DEFAULT_ARCHIVE_OUTPUT eos::portable_oarchive
#elif _QX_SERIALIZE_WIDE_BINARY
#define QX_DEFAULT_ARCHIVE_INPUT boost::archive::binary_wiarchive
#define QX_DEFAULT_ARCHIVE_OUTPUT boost::archive::binary_woarchive
#elif _QX_SERIALIZE_WIDE_TEXT
#define QX_DEFAULT_ARCHIVE_INPUT boost::archive::text_wiarchive
#define QX_DEFAULT_ARCHIVE_OUTPUT boost::archive::text_woarchive
#elif _QX_SERIALIZE_WIDE_XML
#define QX_DEFAULT_ARCHIVE_INPUT boost::archive::xml_wiarchive
#define QX_DEFAULT_ARCHIVE_OUTPUT boost::archive::xml_woarchive
#endif // _QX_SERIALIZE_BINARY
#endif // QX_DEFAULT_ARCHIVE_INPUT

#ifndef QX_CLONE_STRING_STREAM // && QX_CLONE_BINARY_OUTPUT_ARCHIVE && QX_CLONE_BINARY_INPUT_ARCHIVE
#if _QX_SERIALIZE_POLYMORPHIC
#define QX_CLONE_STRING_STREAM std::stringstream
#define QX_CLONE_BINARY_OUTPUT_ARCHIVE boost::archive::polymorphic_binary_oarchive
#define QX_CLONE_BINARY_INPUT_ARCHIVE boost::archive::polymorphic_binary_iarchive
#elif _QX_SERIALIZE_WIDE_BINARY
#define QX_CLONE_STRING_STREAM std::wstringstream
#define QX_CLONE_BINARY_OUTPUT_ARCHIVE boost::archive::binary_woarchive
#define QX_CLONE_BINARY_INPUT_ARCHIVE boost::archive::binary_wiarchive
#elif _QX_SERIALIZE_BINARY
#define QX_CLONE_STRING_STREAM std::stringstream
#define QX_CLONE_BINARY_OUTPUT_ARCHIVE boost::archive::binary_oarchive
#define QX_CLONE_BINARY_INPUT_ARCHIVE boost::archive::binary_iarchive
#elif _QX_SERIALIZE_PORTABLE_BINARY
#define QX_CLONE_STRING_STREAM std::stringstream
#define QX_CLONE_BINARY_OUTPUT_ARCHIVE eos::portable_oarchive
#define QX_CLONE_BINARY_INPUT_ARCHIVE eos::portable_iarchive
#endif // _QX_SERIALIZE_WIDE_BINARY
#else
#define QX_CLONE_NEED_BINARY_TO_INCREASE_PERFORMANCE "qx::clone() need binary archive for best performance"
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__DMC__)
#  pragma message (QX_CLONE_NEED_BINARY_TO_INCREASE_PERFORMANCE)
#elif defined(__GNUC__) || defined(__HP_aCC) || defined(__SUNPRO_CC) || defined(__IBMCPP__)
#  warning QX_CLONE_NEED_BINARY_TO_INCREASE_PERFORMANCE
#endif // defined(_MSC_VER) || defined(__BORLANDC__) || defined(__DMC__)
#endif // QX_CLONE_STRING_STREAM

#endif // _QX_SERIALIZE_INCLUDE_H_
#endif // _QX_ENABLE_BOOST_SERIALIZATION
