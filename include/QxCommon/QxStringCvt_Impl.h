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

#ifndef _QX_STRING_CVT_IMPL_H_
#define _QX_STRING_CVT_IMPL_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/lexical_cast.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_enum.hpp>

#include <QxCommon/QxStringCvt.h>
#include <QxCommon/QxBool.h>

#include <QxDao/QxDateNeutral.h>
#include <QxDao/QxTimeNeutral.h>
#include <QxDao/QxDateTimeNeutral.h>
#include <QxDao/QxSqlQuery.h>

#include <QxCollection/QxCollection.h>

#include <QxRegister/QxClass.h>

#include <QxSerialize/QxArchive.h>

#include <QxValidator/QxInvalidValue.h>
#include <QxValidator/QxInvalidValueX.h>

#include <QxTraits/is_smart_ptr.h>
#include <QxTraits/is_container.h>
#include <QxTraits/is_qx_registered.h>
#include <QxTraits/is_qt_variant_compatible.h>
#include <QxTraits/get_class_name_primitive.h>
#include <QxTraits/construct_ptr.h>
#include <QxTraits/generic_container.h>

#define QX_STR_CVT_QDATE_FORMAT        "yyyyMMdd"
#define QX_STR_CVT_QTIME_FORMAT        "hhmmsszzz"
#define QX_STR_CVT_QDATETIME_FORMAT    "yyyyMMddhhmmsszzz"

#if _QX_SERIALIZE_POLYMORPHIC
#define QX_STR_CVT_DEFAULT_ARCHIVE     qx::serialization::polymorphic_xml
#elif _QX_SERIALIZE_XML
#define QX_STR_CVT_DEFAULT_ARCHIVE     qx::serialization::xml
#elif _QX_SERIALIZE_TEXT
#define QX_STR_CVT_DEFAULT_ARCHIVE     qx::serialization::text
#elif _QX_SERIALIZE_BINARY
#define QX_STR_CVT_DEFAULT_ARCHIVE     qx::serialization::binary
#endif // _QX_SERIALIZE_XML

#define QX_STR_CVT_BY_USING_ARCHIVE_IMPL(className) \
namespace qx { namespace cvt { namespace detail { \
template <> struct QxStringCvt_ToString< className > { \
static inline QString toString(const className & t, const QString & format, int index) \
{ Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::to_string(t); } }; \
template <> struct QxStringCvt_FromString< className > { \
static inline qx_bool fromString(const QString & s, className & t, const QString & format, int index) \
{ Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, s); } }; \
} } } // namespace qx::cvt::detail

namespace qx {
namespace cvt {
namespace detail {

template <typename T>
struct QxStringCvtGeneric
{

   static inline QString toString(const T & t, const QString & format, int index)
   {
      Q_UNUSED(format); Q_UNUSED(index); std::string s;
      try { s = boost::lexical_cast<std::string>(t); }
      catch (...) { qDebug("[QxOrm] %s", "'QxStringCvtGeneric::toString()' unknown error calling 'boost::lexical_cast<std::string>()'"); s = ""; }
#ifndef QT_NO_STL
      return QString::fromStdString(s);
#else // QT_NO_STL
      return QString::fromLatin1(s.data(), int(s.size()));
#endif // QT_NO_STL
   }

   static inline qx_bool fromString(const QString & s, T & t, const QString & format, int index)
   {
      Q_UNUSED(format); Q_UNUSED(index);
#ifndef QT_NO_STL
      try { t = boost::lexical_cast<T>(s.toStdString()); }
#else // QT_NO_STL
      try { std::string tmp(s.toLatin1().constData()); t = boost::lexical_cast<T>(tmp); }
#endif // QT_NO_STL
      catch (...) { qDebug("[QxOrm] %s", "'QxStringCvtGeneric::fromString()' unknown error calling 'boost::lexical_cast<T>()'"); return qx_bool(false); }
      return qx_bool(true);
   }

   static inline QVariant toVariant(const T & t, const QString & format, int index)
   { return cvtQVariant<qx::trait::is_qt_variant_compatible<T>::value, 0>::toVariant(t, format, index); }

   static inline qx_bool fromVariant(const QVariant & v, T & t, const QString & format, int index)
   { return cvtQVariant<qx::trait::is_qt_variant_compatible<T>::value, 0>::fromVariant(v, t, format, index); }

private:

   template <bool isQVariantCompatible /* = false */, int dummy>
   struct cvtQVariant
   {
      static inline QVariant toVariant(const T & t, const QString & format, int index)                { return qx::cvt::to_string(t, format, index); };
      static inline qx_bool fromVariant(const QVariant & v, T & t, const QString & format, int index) { return qx::cvt::from_string(v.toString(), t, format, index); };
   };

   template <int dummy>
   struct cvtQVariant<true, dummy>
   {
      static inline QVariant toVariant(const T & t, const QString & format, int index)                { Q_UNUSED(format); Q_UNUSED(index); return QVariant(t); };
      static inline qx_bool fromVariant(const QVariant & v, T & t, const QString & format, int index) { Q_UNUSED(format); Q_UNUSED(index); t = v.value<T>(); return qx_bool(true); };
   };

};

template <typename T>
struct QxStringCvtPtr
{

   static inline QString toString(const T & t, const QString & format, int index)
   { return (t ? qx::cvt::to_string((* t), format, index) : ""); }

   static inline qx_bool fromString(const QString & s, T & t, const QString & format, int index)
   { if (! t) { qx::trait::construct_ptr<T>::get(t); }; return (t ? qx::cvt::from_string(s, (* t), format, index) : qx_bool(false)); }

   static inline QVariant toVariant(const T & t, const QString & format, int index)
   { return (t ? qx::cvt::to_variant((* t), format, index) : QVariant()); }

   static inline qx_bool fromVariant(const QVariant & v, T & t, const QString & format, int index)
   { if (! t && ! v.isNull()) { qx::trait::construct_ptr<T>::get(t); }; return (t ? qx::cvt::from_variant(v, (* t), format, index) : qx_bool(false)); }

};

template <typename T>
struct QxStringCvtRegistered
{

   static inline QString toString(const T & t, const QString & format, int index)
   { return (getId() ? getId()->toString((& t), format, index) : ""); }

   static inline qx_bool fromString(const QString & s, T & t, const QString & format, int index)
   { return (getId() ? getId()->fromString((& t), s, format, index) : qx_bool(false)); }

   static inline QVariant toVariant(const T & t, const QString & format, int index)
   { return (getId() ? getId()->toVariant((& t), format, index) : QVariant()); }

   static inline qx_bool fromVariant(const QVariant & v, T & t, const QString & format, int index)
   { return (getId() ? getId()->fromVariant((& t), v, format, index) : qx_bool(false)); }

private:

   static inline qx::IxDataMember * getId()
   { return qx::QxClass<T>::getSingleton()->getDataMemberX()->getId_WithDaoStrategy(); }

};

template <typename T>
struct QxStringCvtContainer
{

   static inline QString toString(const T & t, const QString & format, int index)
   { Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::to_string(t); }

   static inline qx_bool fromString(const QString & s, T & t, const QString & format, int index)
   { Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, s); }

   static inline QVariant toVariant(const T & t, const QString & format, int index)
   { Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::to_string(t); }

   static inline qx_bool fromVariant(const QVariant & v, T & t, const QString & format, int index)
   { Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, v.toString()); }

};

template <typename T>
struct QxStringCvtEnum
{

   static inline QString toString(const T & t, const QString & format, int index)
   { Q_UNUSED(format); Q_UNUSED(index); return QString::number(static_cast<long>(t)); }

   static inline qx_bool fromString(const QString & s, T & t, const QString & format, int index)
   { Q_UNUSED(format); Q_UNUSED(index); bool bOk = false; t = static_cast<T>(static_cast<long>(s.toLongLong(& bOk))); return bOk; }

   static inline QVariant toVariant(const T & t, const QString & format, int index)
   { Q_UNUSED(format); Q_UNUSED(index); return QVariant(static_cast<qlonglong>(t)); }

   static inline qx_bool fromVariant(const QVariant & v, T & t, const QString & format, int index)
   { Q_UNUSED(format); Q_UNUSED(index); bool bOk = false; t = static_cast<T>(static_cast<long>(v.toLongLong(& bOk))); return bOk; }

};

template <typename T>
struct QxStringCvtHelper
{

private:

   typedef typename boost::mpl::if_c< boost::is_pointer<T>::value, qx::cvt::detail::QxStringCvtPtr<T>, qx::cvt::detail::QxStringCvtGeneric<T> >::type type_str_cvt_helper_1;
   typedef typename boost::mpl::if_c< qx::trait::is_smart_ptr<T>::value, qx::cvt::detail::QxStringCvtPtr<T>, type_str_cvt_helper_1 >::type type_str_cvt_helper_2;
   typedef typename boost::mpl::if_c< qx::trait::is_container<T>::value, qx::cvt::detail::QxStringCvtContainer<T>, type_str_cvt_helper_2 >::type type_str_cvt_helper_3;
   typedef typename boost::mpl::if_c< qx::trait::is_qx_registered<T>::value, qx::cvt::detail::QxStringCvtRegistered<T>, type_str_cvt_helper_3 >::type type_str_cvt_helper_4;
   typedef typename boost::mpl::if_c< boost::is_enum<T>::value, qx::cvt::detail::QxStringCvtEnum<T>, type_str_cvt_helper_4 >::type type_str_cvt_helper_5;

public:

   typedef typename QxStringCvtHelper<T>::type_str_cvt_helper_5 type;

};

template <typename T>
struct QxStringCvt_ToString {
static inline QString toString(const T & t, const QString & format, int index)
{ return qx::cvt::detail::QxStringCvtHelper<T>::type::toString(t, format, index); } };

template <typename T>
struct QxStringCvt_FromString {
static inline qx_bool fromString(const QString & s, T & t, const QString & format, int index)
{ return qx::cvt::detail::QxStringCvtHelper<T>::type::fromString(s, t, format, index); } };

template <typename T>
struct QxStringCvt_ToVariant {
static inline QVariant toVariant(const T & t, const QString & format, int index)
{ return qx::cvt::detail::QxStringCvtHelper<T>::type::toVariant(t, format, index); } };

template <typename T>
struct QxStringCvt_FromVariant {
static inline qx_bool fromVariant(const QVariant & v, T & t, const QString & format, int index)
{ return qx::cvt::detail::QxStringCvtHelper<T>::type::fromVariant(v, t, format, index); } };

} // namespace detail
} // namespace cvt
} // namespace qx

#include "../../inl/QxCommon/QxStringCvt_WithIndex.inl"
#include "../../inl/QxCommon/QxStringCvt_ToString.inl"
#include "../../inl/QxCommon/QxStringCvt_FromString.inl"
#include "../../inl/QxCommon/QxStringCvt_ToVariant.inl"
#include "../../inl/QxCommon/QxStringCvt_FromVariant.inl"
#include "../../inl/QxCommon/QxStringCvt_Qt.inl"

#endif // _QX_STRING_CVT_IMPL_H_
