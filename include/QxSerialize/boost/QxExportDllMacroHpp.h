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
#ifndef _QX_EXPORT_DLL_MACRO_HPP_H_
#define _QX_EXPORT_DLL_MACRO_HPP_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QxCommon/QxConfig.h>

#include <QxSerialize/boost/QxSerialize_shared_ptr.h>

#include <QxTraits/get_base_class.h>

#if _QX_USE_EXPORT_DLL_BOOST_SERIALIZATION_SINGLETON

#if _QX_SUPPORT_BOOST_SERIALIZE_SHARED_PTR_132
#if (BOOST_VERSION >= 104100)
#define QX_BOOST_132_SHARED_PTR_HELPER(T) \
boost_132::detail::sp_counted_base_impl< T *, boost::serialization::null_deleter >
#else // (BOOST_VERSION >= 104100)
#define QX_BOOST_132_SHARED_PTR_HELPER(T) \
boost_132::detail::sp_counted_base_impl< T *, boost_132::serialization::detail::null_deleter >
#endif // (BOOST_VERSION >= 104100)
#endif // _QX_SUPPORT_BOOST_SERIALIZE_SHARED_PTR_132

#define QX_BOOST_EXPORT_SERIALIZATION_IMPL_POINTER_ISERIALIZER_HPP(ArchiveIn, ArchiveOut, T) \
QX_DLL_EXPORT_TEMPLATE_T_P1_P2_HPP(class, boost::archive::detail::pointer_iserializer, ArchiveIn, T) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_P2_HPP(class, boost::serialization::singleton, boost::archive::detail::pointer_iserializer, ArchiveIn, T)

#define QX_BOOST_EXPORT_SERIALIZATION_IMPL_POINTER_OSERIALIZER_HPP(ArchiveIn, ArchiveOut, T) \
QX_DLL_EXPORT_TEMPLATE_T_P1_P2_HPP(class, boost::archive::detail::pointer_oserializer, ArchiveOut, T) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_P2_HPP(class, boost::serialization::singleton, boost::archive::detail::pointer_oserializer, ArchiveOut, T)

#if _QX_SUPPORT_BOOST_SERIALIZE_SHARED_PTR_132
#define QX_BOOST_EXPORT_SERIALIZATION_IMPL_POINTER_ISERIALIZER_BOOST_132_HELPER_HPP(ArchiveIn, ArchiveOut, T) \
QX_DLL_EXPORT_TEMPLATE_T_P1_P2_HPP(class, boost::archive::detail::pointer_iserializer, ArchiveIn, QX_BOOST_132_SHARED_PTR_HELPER(T)) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_P2_HPP(class, boost::serialization::singleton, boost::archive::detail::pointer_iserializer, ArchiveIn, QX_BOOST_132_SHARED_PTR_HELPER(T))
#else // _QX_SUPPORT_BOOST_SERIALIZE_SHARED_PTR_132
#define QX_BOOST_EXPORT_SERIALIZATION_IMPL_POINTER_ISERIALIZER_BOOST_132_HELPER_HPP(ArchiveIn, ArchiveOut, T) /* Nothing */
#endif // _QX_SUPPORT_BOOST_SERIALIZE_SHARED_PTR_132

#if _QX_SUPPORT_BOOST_SERIALIZE_SHARED_PTR_132
#define QX_BOOST_EXPORT_SERIALIZATION_IMPL_POINTER_OSERIALIZER_BOOST_132_HELPER_HPP(ArchiveIn, ArchiveOut, T) \
QX_DLL_EXPORT_TEMPLATE_T_P1_P2_HPP(class, boost::archive::detail::pointer_oserializer, ArchiveOut, QX_BOOST_132_SHARED_PTR_HELPER(T)) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_P2_HPP(class, boost::serialization::singleton, boost::archive::detail::pointer_oserializer, ArchiveOut, QX_BOOST_132_SHARED_PTR_HELPER(T))
#else // _QX_SUPPORT_BOOST_SERIALIZE_SHARED_PTR_132
#define QX_BOOST_EXPORT_SERIALIZATION_IMPL_POINTER_OSERIALIZER_BOOST_132_HELPER_HPP(ArchiveIn, ArchiveOut, T) /* Nothing */
#endif // _QX_SUPPORT_BOOST_SERIALIZE_SHARED_PTR_132

#define QX_BOOST_EXPORT_SERIALIZATION_IMPL_ISERIALIZER_HPP(ArchiveIn, ArchiveOut, T) \
QX_DLL_EXPORT_TEMPLATE_T_P1_P2_HPP(class, boost::archive::detail::iserializer, ArchiveIn, T) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_P2_HPP(class, boost::serialization::singleton, boost::archive::detail::iserializer, ArchiveIn, T)

#define QX_BOOST_EXPORT_SERIALIZATION_IMPL_OSERIALIZER_HPP(ArchiveIn, ArchiveOut, T) \
QX_DLL_EXPORT_TEMPLATE_T_P1_P2_HPP(class, boost::archive::detail::oserializer, ArchiveOut, T) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_P2_HPP(class, boost::serialization::singleton, boost::archive::detail::oserializer, ArchiveOut, T)

#define QX_BOOST_EXPORT_SERIALIZATION_IMPL_EXTENDED_TYPE_ID_HPP(T) \
QX_DLL_EXPORT_TEMPLATE_T_P1_HPP(class, boost::serialization::extended_type_info_typeid, T) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_HPP(class, boost::serialization::singleton, boost::serialization::extended_type_info_typeid, T)

#define QX_BOOST_EXPORT_SERIALIZATION_IMPL_VOID_CAST_PRIMITIVE_HPP(T) \
QX_DLL_EXPORT_TEMPLATE_T_P1_P2_HPP(class, boost::serialization::void_cast_detail::void_caster_primitive, T, QX_GET_BASE_CLASS_2(T)) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_P2_HPP(class, boost::serialization::singleton, boost::serialization::void_cast_detail::void_caster_primitive, T, QX_GET_BASE_CLASS_2(T))

#define QX_BOOST_EXPORT_SERIALIZATION_IMPL_TYPE_INFO_IMPL_HPP(T) \
QX_DLL_EXPORT_TEMPLATE_T_P1_HPP(struct, boost::serialization::type_info_implementation, T) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_HPP(class, boost::serialization::singleton, boost::serialization::type_info_implementation, T)

#if (BOOST_VERSION < 104100)
#define QX_BOOST_EXPORT_SERIALIZATION_SAVE_POINTER_TYPE_HPP(ArchiveIn, ArchiveOut, T) \
QX_DLL_EXPORT_TEMPLATE_T_P1_P2_HPP(struct, boost::archive::detail::save_pointer_type, ArchiveOut, T *) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_P2_HPP(class, boost::serialization::singleton, boost::archive::detail::save_pointer_type, ArchiveOut, T *)
#else // (BOOST_VERSION < 104100)
#define QX_BOOST_EXPORT_SERIALIZATION_SAVE_POINTER_TYPE_HPP(ArchiveIn, ArchiveOut, T) /* Nothing */
#endif // (BOOST_VERSION < 104100)

#if (BOOST_VERSION < 104100)
#define QX_BOOST_EXPORT_SERIALIZATION_SAVE_NON_POINTER_TYPE_HPP(ArchiveIn, ArchiveOut, T) \
QX_DLL_EXPORT_TEMPLATE_T_P1_P2_HPP(struct, boost::archive::detail::save_non_pointer_type, ArchiveOut, T) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_P2_HPP(class, boost::serialization::singleton, boost::archive::detail::save_non_pointer_type, ArchiveOut, T)
#else // (BOOST_VERSION < 104100)
#define QX_BOOST_EXPORT_SERIALIZATION_SAVE_NON_POINTER_TYPE_HPP(ArchiveIn, ArchiveOut, T) /* Nothing */
#endif // (BOOST_VERSION < 104100)

#if (BOOST_VERSION < 104100)
#define QX_BOOST_EXPORT_SERIALIZATION_SAVE_ENUM_TYPE_HPP(ArchiveIn, ArchiveOut, T) \
QX_DLL_EXPORT_TEMPLATE_T_P1_P2_HPP(struct, boost::archive::detail::save_enum_type, ArchiveOut, T) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_P2_HPP(class, boost::serialization::singleton, boost::archive::detail::save_enum_type, ArchiveOut, T)
#else // (BOOST_VERSION < 104100)
#define QX_BOOST_EXPORT_SERIALIZATION_SAVE_ENUM_TYPE_HPP(ArchiveIn, ArchiveOut, T) /* Nothing */
#endif // (BOOST_VERSION < 104100)

#if (BOOST_VERSION < 104100)
#define QX_BOOST_EXPORT_SERIALIZATION_SAVE_ARRAY_TYPE_HPP(ArchiveIn, ArchiveOut, T) \
QX_DLL_EXPORT_TEMPLATE_T_P1_P2_HPP(struct, boost::archive::detail::save_array_type, ArchiveOut, T) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_P2_HPP(class, boost::serialization::singleton, boost::archive::detail::save_array_type, ArchiveOut, T)
#else // (BOOST_VERSION < 104100)
#define QX_BOOST_EXPORT_SERIALIZATION_SAVE_ARRAY_TYPE_HPP(ArchiveIn, ArchiveOut, T) /* Nothing */
#endif // (BOOST_VERSION < 104100)

#if (BOOST_VERSION < 104100)
#define QX_BOOST_EXPORT_SERIALIZATION_LOAD_POINTER_TYPE_HPP(ArchiveIn, ArchiveOut, T) \
QX_DLL_EXPORT_TEMPLATE_T_P1_P2_HPP(struct, boost::archive::detail::load_pointer_type, ArchiveIn, T *) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_P2_HPP(class, boost::serialization::singleton, boost::archive::detail::load_pointer_type, ArchiveIn, T *)
#else // (BOOST_VERSION < 104100)
#define QX_BOOST_EXPORT_SERIALIZATION_LOAD_POINTER_TYPE_HPP(ArchiveIn, ArchiveOut, T) /* Nothing */
#endif // (BOOST_VERSION < 104100)

#if (BOOST_VERSION < 104100)
#define QX_BOOST_EXPORT_SERIALIZATION_LOAD_NON_POINTER_TYPE_HPP(ArchiveIn, ArchiveOut, T) \
QX_DLL_EXPORT_TEMPLATE_T_P1_P2_HPP(struct, boost::archive::detail::load_non_pointer_type, ArchiveIn, T) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_P2_HPP(class, boost::serialization::singleton, boost::archive::detail::load_non_pointer_type, ArchiveIn, T)
#else // (BOOST_VERSION < 104100)
#define QX_BOOST_EXPORT_SERIALIZATION_LOAD_NON_POINTER_TYPE_HPP(ArchiveIn, ArchiveOut, T) /* Nothing */
#endif // (BOOST_VERSION < 104100)

#if (BOOST_VERSION < 104100)
#define QX_BOOST_EXPORT_SERIALIZATION_LOAD_ENUM_TYPE_HPP(ArchiveIn, ArchiveOut, T) \
QX_DLL_EXPORT_TEMPLATE_T_P1_P2_HPP(struct, boost::archive::detail::load_enum_type, ArchiveIn, T) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_P2_HPP(class, boost::serialization::singleton, boost::archive::detail::load_enum_type, ArchiveIn, T)
#else // (BOOST_VERSION < 104100)
#define QX_BOOST_EXPORT_SERIALIZATION_LOAD_ENUM_TYPE_HPP(ArchiveIn, ArchiveOut, T) /* Nothing */
#endif // (BOOST_VERSION < 104100)

#if (BOOST_VERSION < 104100)
#define QX_BOOST_EXPORT_SERIALIZATION_LOAD_ARRAY_TYPE_HPP(ArchiveIn, ArchiveOut, T) \
QX_DLL_EXPORT_TEMPLATE_T_P1_P2_HPP(struct, boost::archive::detail::load_array_type, ArchiveIn, T) \
QX_DLL_EXPORT_TEMPLATE_T_U_P1_P2_HPP(class, boost::serialization::singleton, boost::archive::detail::load_array_type, ArchiveIn, T)
#else // (BOOST_VERSION < 104100)
#define QX_BOOST_EXPORT_SERIALIZATION_LOAD_ARRAY_TYPE_HPP(ArchiveIn, ArchiveOut, T) /* Nothing */
#endif // (BOOST_VERSION < 104100)

#define QX_BOOST_EXPORT_SERIALIZATION_IMPL_WITH_ARCHIVE_HPP(ArchiveIn, ArchiveOut, T) \
QX_BOOST_EXPORT_SERIALIZATION_IMPL_ISERIALIZER_HPP(ArchiveIn, ArchiveOut, T) \
QX_BOOST_EXPORT_SERIALIZATION_IMPL_OSERIALIZER_HPP(ArchiveIn, ArchiveOut, T) \
QX_BOOST_EXPORT_SERIALIZATION_IMPL_POINTER_ISERIALIZER_HPP(ArchiveIn, ArchiveOut, T) \
QX_BOOST_EXPORT_SERIALIZATION_IMPL_POINTER_OSERIALIZER_HPP(ArchiveIn, ArchiveOut, T) \
QX_BOOST_EXPORT_SERIALIZATION_IMPL_POINTER_ISERIALIZER_BOOST_132_HELPER_HPP(ArchiveIn, ArchiveOut, T) \
QX_BOOST_EXPORT_SERIALIZATION_IMPL_POINTER_OSERIALIZER_BOOST_132_HELPER_HPP(ArchiveIn, ArchiveOut, T) \
QX_BOOST_EXPORT_SERIALIZATION_SAVE_POINTER_TYPE_HPP(ArchiveIn, ArchiveOut, T) \
QX_BOOST_EXPORT_SERIALIZATION_LOAD_POINTER_TYPE_HPP(ArchiveIn, ArchiveOut, T)

#define QX_BOOST_EXPORT_SERIALIZATION_IMPL_HPP(T) \
QX_BOOST_EXPORT_SERIALIZATION_IMPL_EXTENDED_TYPE_ID_HPP(T) \
/*
QX_BOOST_EXPORT_SERIALIZATION_IMPL_VOID_CAST_PRIMITIVE_HPP(T) \
QX_BOOST_EXPORT_SERIALIZATION_IMPL_TYPE_INFO_IMPL_HPP(T)
*/

#if _QX_SERIALIZE_POLYMORPHIC
#define QX_BOOST_EXPORT_SERIALIZATION_POLYMORPHIC_HPP(T) \
QX_BOOST_EXPORT_SERIALIZATION_IMPL_WITH_ARCHIVE_HPP(boost::archive::polymorphic_iarchive, boost::archive::polymorphic_oarchive, T)
#else // _QX_SERIALIZE_POLYMORPHIC
#define QX_BOOST_EXPORT_SERIALIZATION_POLYMORPHIC_HPP(T) /* Nothing */
#endif // _QX_SERIALIZE_POLYMORPHIC

#if _QX_SERIALIZE_BINARY
#define QX_BOOST_EXPORT_SERIALIZATION_BINARY_HPP(T) \
QX_BOOST_EXPORT_SERIALIZATION_IMPL_WITH_ARCHIVE_HPP(boost::archive::binary_iarchive, boost::archive::binary_oarchive, T)
#else // _QX_SERIALIZE_BINARY
#define QX_BOOST_EXPORT_SERIALIZATION_BINARY_HPP(T) /* Nothing */
#endif // _QX_SERIALIZE_BINARY

#if _QX_SERIALIZE_TEXT
#define QX_BOOST_EXPORT_SERIALIZATION_TEXT_HPP(T) \
QX_BOOST_EXPORT_SERIALIZATION_IMPL_WITH_ARCHIVE_HPP(boost::archive::text_iarchive, boost::archive::text_oarchive, T)
#else // _QX_SERIALIZE_TEXT
#define QX_BOOST_EXPORT_SERIALIZATION_TEXT_HPP(T) /* Nothing */
#endif // _QX_SERIALIZE_TEXT

#if _QX_SERIALIZE_XML
#define QX_BOOST_EXPORT_SERIALIZATION_XML_HPP(T) \
QX_BOOST_EXPORT_SERIALIZATION_IMPL_WITH_ARCHIVE_HPP(boost::archive::xml_iarchive, boost::archive::xml_oarchive, T)
#else // _QX_SERIALIZE_XML
#define QX_BOOST_EXPORT_SERIALIZATION_XML_HPP(T) /* Nothing */
#endif // _QX_SERIALIZE_XML

#if _QX_SERIALIZE_PORTABLE_BINARY
#define QX_BOOST_EXPORT_SERIALIZATION_PORTABLE_BINARY_HPP(T) \
QX_BOOST_EXPORT_SERIALIZATION_IMPL_WITH_ARCHIVE_HPP(eos::portable_iarchive, eos::portable_oarchive, T)
#else // _QX_SERIALIZE_PORTABLE_BINARY
#define QX_BOOST_EXPORT_SERIALIZATION_PORTABLE_BINARY_HPP(T) /* Nothing */
#endif // _QX_SERIALIZE_PORTABLE_BINARY

#if _QX_SERIALIZE_WIDE_BINARY
#define QX_BOOST_EXPORT_SERIALIZATION_WIDE_BINARY_HPP(T) \
QX_BOOST_EXPORT_SERIALIZATION_IMPL_WITH_ARCHIVE_HPP(boost::archive::binary_wiarchive, boost::archive::binary_woarchive, T)
#else // _QX_SERIALIZE_WIDE_BINARY
#define QX_BOOST_EXPORT_SERIALIZATION_WIDE_BINARY_HPP(T) /* Nothing */
#endif // _QX_SERIALIZE_WIDE_BINARY

#if _QX_SERIALIZE_WIDE_TEXT
#define QX_BOOST_EXPORT_SERIALIZATION_WIDE_TEXT_HPP(T) \
QX_BOOST_EXPORT_SERIALIZATION_IMPL_WITH_ARCHIVE_HPP(boost::archive::text_wiarchive, boost::archive::text_woarchive, T)
#else // _QX_SERIALIZE_WIDE_TEXT
#define QX_BOOST_EXPORT_SERIALIZATION_WIDE_TEXT_HPP(T) /* Nothing */
#endif // _QX_SERIALIZE_WIDE_TEXT

#if _QX_SERIALIZE_WIDE_XML
#define QX_BOOST_EXPORT_SERIALIZATION_WIDE_XML_HPP(T) \
QX_BOOST_EXPORT_SERIALIZATION_IMPL_WITH_ARCHIVE_HPP(boost::archive::xml_wiarchive, boost::archive::xml_woarchive, T)
#else // _QX_SERIALIZE_WIDE_XML
#define QX_BOOST_EXPORT_SERIALIZATION_WIDE_XML_HPP(T) /* Nothing */
#endif // _QX_SERIALIZE_WIDE_XML

#define QX_BOOST_EXPORT_SERIALIZATION_HPP(T) \
QX_BOOST_EXPORT_SERIALIZATION_IMPL_HPP(T) \
QX_BOOST_EXPORT_SERIALIZATION_POLYMORPHIC_HPP(T) \
QX_BOOST_EXPORT_SERIALIZATION_BINARY_HPP(T) \
QX_BOOST_EXPORT_SERIALIZATION_TEXT_HPP(T) \
QX_BOOST_EXPORT_SERIALIZATION_XML_HPP(T) \
QX_BOOST_EXPORT_SERIALIZATION_PORTABLE_BINARY_HPP(T) \
QX_BOOST_EXPORT_SERIALIZATION_WIDE_BINARY_HPP(T) \
QX_BOOST_EXPORT_SERIALIZATION_WIDE_TEXT_HPP(T) \
QX_BOOST_EXPORT_SERIALIZATION_WIDE_XML_HPP(T)

#else // _QX_USE_EXPORT_DLL_BOOST_SERIALIZATION_SINGLETON

#define QX_BOOST_EXPORT_SERIALIZATION_HPP(T) /* Nothing */

#endif // _QX_USE_EXPORT_DLL_BOOST_SERIALIZATION_SINGLETON
#endif // _QX_EXPORT_DLL_MACRO_HPP_H_
#endif // _QX_ENABLE_BOOST_SERIALIZATION
