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

#ifndef _QX_CONVERT_IMPL_H_
#define _QX_CONVERT_IMPL_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/mpl/if.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <boost/static_assert.hpp>

#include <QxConvert/QxConvert.h>
#include <QxCommon/QxBool.h>

#include <QxDao/QxDateNeutral.h>
#include <QxDao/QxTimeNeutral.h>
#include <QxDao/QxDateTimeNeutral.h>
#include <QxDao/QxSqlQuery.h>

#include <QxCollection/QxCollection.h>

#include <QxRegister/QxClass.h>

#include <QxSerialize/QxArchive.h>
#include <QxSerialize/QxSerializeQDataStream.h>
#include <QxSerialize/QDataStream/QxSerializeQDataStream_all_include.h>
#include <QxSerialize/QJson/QxSerializeQJson_qx_registered_class.h>

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

#ifdef _QX_ENABLE_BOOST_SERIALIZATION
#if _QX_SERIALIZE_POLYMORPHIC
#define QX_CVT_DEFAULT_ARCHIVE         qx::serialization::polymorphic_xml
#elif _QX_SERIALIZE_XML
#define QX_CVT_DEFAULT_ARCHIVE         qx::serialization::xml
#elif _QX_SERIALIZE_TEXT
#define QX_CVT_DEFAULT_ARCHIVE         qx::serialization::text
#elif _QX_SERIALIZE_BINARY
#define QX_CVT_DEFAULT_ARCHIVE         qx::serialization::binary
#endif // _QX_SERIALIZE_XML
#else // _QX_ENABLE_BOOST_SERIALIZATION
#define QX_CVT_DEFAULT_ARCHIVE         qx::serialization::qt
#endif // _QX_ENABLE_BOOST_SERIALIZATION

#define QX_CVT_USING_ARCHIVE_IMPL(className) \
namespace qx { namespace cvt { namespace detail { \
template <> struct QxConvert_ToString< className > { \
static inline QString toString(const className & t, const QString & format, int index, qx::cvt::context::ctx_type ctx) \
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } }; \
template <> struct QxConvert_FromString< className > { \
static inline qx_bool fromString(const QString & s, className & t, const QString & format, int index, qx::cvt::context::ctx_type ctx) \
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::from_string(t, s); } }; \
template <> struct QxConvert_ToVariant< className > { \
static inline QVariant toVariant(const className & t, const QString & format, int index, qx::cvt::context::ctx_type ctx) \
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } }; \
template <> struct QxConvert_FromVariant< className > { \
static inline qx_bool fromVariant(const QVariant & v, className & t, const QString & format, int index, qx::cvt::context::ctx_type ctx) \
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); QString s = v.toString(); return QX_CVT_DEFAULT_ARCHIVE::from_string(t, s); } }; \
} } } // namespace qx::cvt::detail

namespace qx {
namespace cvt {
namespace detail {
namespace helper {

struct QxConvertHelper_Generic { };
struct QxConvertHelper_Ptr { };
struct QxConvertHelper_Registered { };
struct QxConvertHelper_Container { };
struct QxConvertHelper_Enum { };

inline bool checkConvertQVariantToString(const QVariant & v) { return ((v.type() == QVariant::List) || (v.type() == QVariant::Map) || (v.type() == QVariant::Hash) || (v.type() == QVariant::StringList)); }

} // namespace helper

template <typename T, typename H>
struct QxConvertHelper_ToString
{
   static inline QString toString(const T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   { qAssertMsg(false, "qx::cvt::detail::QxConvertHelper_ToString", "template must be specialized"); Q_UNUSED(t); Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QString(); }
};

template <typename T, typename H>
struct QxConvertHelper_FromString
{
   static inline qx_bool fromString(const QString & s, T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   { qAssertMsg(false, "qx::cvt::detail::QxConvertHelper_FromString", "template must be specialized"); Q_UNUSED(s); Q_UNUSED(t); Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return qx_bool(); }
};

template <typename T, typename H>
struct QxConvertHelper_ToVariant
{
   static inline QVariant toVariant(const T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   { qAssertMsg(false, "qx::cvt::detail::QxConvertHelper_ToVariant", "template must be specialized"); Q_UNUSED(t); Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QVariant(); }
};

template <typename T, typename H>
struct QxConvertHelper_FromVariant
{
   static inline qx_bool fromVariant(const QVariant & v, T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   { qAssertMsg(false, "qx::cvt::detail::QxConvertHelper_FromVariant", "template must be specialized"); Q_UNUSED(v); Q_UNUSED(t); Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return qx_bool(); }
};

#ifndef _QX_NO_JSON

template <typename T, typename H>
struct QxConvertHelper_ToJson
{
   static inline QJsonValue toJson(const T & t, const QString & format)
   { qAssertMsg(false, "qx::cvt::detail::QxConvertHelper_ToJson", "template must be specialized"); Q_UNUSED(t); Q_UNUSED(format); return QJsonValue(); }
};

template <typename T, typename H>
struct QxConvertHelper_FromJson
{
   static inline qx_bool fromJson(const QJsonValue & j, T & t, const QString & format)
   { qAssertMsg(false, "qx::cvt::detail::QxConvertHelper_FromJson", "template must be specialized"); Q_UNUSED(j); Q_UNUSED(t); Q_UNUSED(format); return qx_bool(); }
};

#endif // _QX_NO_JSON

template <typename T>
struct QxConvertHelper_ToString<T, qx::cvt::detail::helper::QxConvertHelper_Generic>
{

   enum { qx_need_to_specialize_template_convert_to_string_from_string = 0 };

   static inline QString toString(const T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   {
      Q_UNUSED(t); Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx);
      BOOST_STATIC_ASSERT(qx_need_to_specialize_template_convert_to_string_from_string); // If a compilation error occurred here : you have to specialize template 'qx::cvt::detail::QxConvert_ToString< MyType >'
      return QString();

      /*
      std::string s;
      try { s = boost::lexical_cast<std::string>(t); }
      catch (...) { qDebug("[QxOrm] %s", "'QxConvertHelper_ToString::toString()' unknown error calling 'boost::lexical_cast<std::string>()'"); s = ""; }
#ifndef QT_NO_STL
      return QString::fromStdString(s);
#else // QT_NO_STL
      return QString::fromLatin1(s.data(), int(s.size()));
#endif // QT_NO_STL
      */
   }

};

template <typename T>
struct QxConvertHelper_FromString<T, qx::cvt::detail::helper::QxConvertHelper_Generic>
{

   enum { qx_need_to_specialize_template_convert_to_string_from_string = 0 };

   static inline qx_bool fromString(const QString & s, T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   {
      Q_UNUSED(s); Q_UNUSED(t); Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx);
      BOOST_STATIC_ASSERT(qx_need_to_specialize_template_convert_to_string_from_string); // If a compilation error occurred here : you have to specialize template 'qx::cvt::detail::QxConvert_FromString< MyType >'
      return qx_bool(true);

      /*
#ifndef QT_NO_STL
      try { t = boost::lexical_cast<T>(s.toStdString()); }
#else // QT_NO_STL
      try { std::string tmp(s.toLatin1().constData()); t = boost::lexical_cast<T>(tmp); }
#endif // QT_NO_STL
      catch (...) { qDebug("[QxOrm] %s", "'QxConvertHelper_FromString::fromString()' unknown error calling 'boost::lexical_cast<T>()'"); return qx_bool(false); }
      return qx_bool(true);
      */
   }

};

template <typename T>
struct QxConvertHelper_ToVariant<T, qx::cvt::detail::helper::QxConvertHelper_Generic>
{

   static inline QVariant toVariant(const T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   { return cvtQVariant<qx::trait::is_qt_variant_compatible<T>::value, 0>::toVariant(t, format, index, ctx); }

private:

   template <bool isQVariantCompatible /* = false */, int dummy>
   struct cvtQVariant
   { static inline QVariant toVariant(const T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx) { return qx::cvt::to_string(t, format, index, ctx); }; };

   template <int dummy>
   struct cvtQVariant<true, dummy>
   { static inline QVariant toVariant(const T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx) { Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QVariant(t); }; };

};

template <typename T>
struct QxConvertHelper_FromVariant<T, qx::cvt::detail::helper::QxConvertHelper_Generic>
{

   static inline qx_bool fromVariant(const QVariant & v, T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   { return cvtQVariant<qx::trait::is_qt_variant_compatible<T>::value, 0>::fromVariant(v, t, format, index, ctx); }

private:

   template <bool isQVariantCompatible /* = false */, int dummy>
   struct cvtQVariant
   { static inline qx_bool fromVariant(const QVariant & v, T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx) { return qx::cvt::from_string(v.toString(), t, format, index, ctx); }; };

   template <int dummy>
   struct cvtQVariant<true, dummy>
   { static inline qx_bool fromVariant(const QVariant & v, T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx) { Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); t = v.value<T>(); return qx_bool(true); }; };

};

#ifndef _QX_NO_JSON

template <typename T>
struct QxConvertHelper_ToJson<T, qx::cvt::detail::helper::QxConvertHelper_Generic>
{
   static inline QJsonValue toJson(const T & t, const QString & format)
   { return QJsonValue::fromVariant(qx::cvt::detail::QxConvertHelper_ToVariant<T, qx::cvt::detail::helper::QxConvertHelper_Generic>::toVariant(t, format, -1, qx::cvt::context::e_no_context)); }
};

template <typename T>
struct QxConvertHelper_FromJson<T, qx::cvt::detail::helper::QxConvertHelper_Generic>
{
   static inline qx_bool fromJson(const QJsonValue & j, T & t, const QString & format)
   { QVariant v = j.toVariant(); return qx::cvt::detail::QxConvertHelper_FromVariant<T, qx::cvt::detail::helper::QxConvertHelper_Generic>::fromVariant(v, t, format, -1, qx::cvt::context::e_no_context); }
};

#endif // _QX_NO_JSON

template <typename T>
struct QxConvertHelper_ToString<T, qx::cvt::detail::helper::QxConvertHelper_Ptr>
{
   static inline QString toString(const T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   { return (t ? qx::cvt::to_string((* t), format, index, ctx) : ""); }
};

template <typename T>
struct QxConvertHelper_FromString<T, qx::cvt::detail::helper::QxConvertHelper_Ptr>
{
   static inline qx_bool fromString(const QString & s, T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   { if (! t) { qx::trait::construct_ptr<T>::get(t); }; return (t ? qx::cvt::from_string(s, (* t), format, index, ctx) : qx_bool(false)); }
};

template <typename T>
struct QxConvertHelper_ToVariant<T, qx::cvt::detail::helper::QxConvertHelper_Ptr>
{
   static inline QVariant toVariant(const T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   { return (t ? qx::cvt::to_variant((* t), format, index, ctx) : QVariant()); }
};

template <typename T>
struct QxConvertHelper_FromVariant<T, qx::cvt::detail::helper::QxConvertHelper_Ptr>
{
   static inline qx_bool fromVariant(const QVariant & v, T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   { if (! t && ! v.isNull()) { qx::trait::construct_ptr<T>::get(t); }; return (t ? qx::cvt::from_variant(v, (* t), format, index, ctx) : qx_bool(false)); }
};

#ifndef _QX_NO_JSON

template <typename T>
struct QxConvertHelper_ToJson<T, qx::cvt::detail::helper::QxConvertHelper_Ptr>
{
   static inline QJsonValue toJson(const T & t, const QString & format)
   { return (t ? qx::cvt::to_json((* t), format) : QJsonValue()); }
};

template <typename T>
struct QxConvertHelper_FromJson<T, qx::cvt::detail::helper::QxConvertHelper_Ptr>
{
   static inline qx_bool fromJson(const QJsonValue & j, T & t, const QString & format)
   { if (! t && ! j.isNull()) { qx::trait::construct_ptr<T>::get(t); }; return (t ? qx::cvt::from_json(j, (* t), format) : qx_bool(false)); }
};

#endif // _QX_NO_JSON

template <typename T>
struct QxConvertHelper_ToString<T, qx::cvt::detail::helper::QxConvertHelper_Registered>
{
   static inline QString toString(const T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   {
      if (ctx != qx::cvt::context::e_serialize_registered)
      { qx::IxDataMember * pId = qx::QxClass<T>::getSingleton()->getDataMemberX()->getId_WithDaoStrategy(); return (pId ? pId->toVariant((& t), format, index, ctx).toString() : QString()); }
      return qx::serialization::qt::to_string<T>(t);
   }
};

template <typename T>
struct QxConvertHelper_FromString<T, qx::cvt::detail::helper::QxConvertHelper_Registered>
{
   static inline qx_bool fromString(const QString & s, T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   {
      if (ctx != qx::cvt::context::e_serialize_registered)
      { qx::IxDataMember * pId = qx::QxClass<T>::getSingleton()->getDataMemberX()->getId_WithDaoStrategy(); QVariant tmp(s); return (pId ? pId->fromVariant((& t), tmp, format, index, ctx) : qx_bool(false)); }
      return qx::serialization::qt::from_string<T>(t, s);
   }
};

template <typename T>
struct QxConvertHelper_ToVariant<T, qx::cvt::detail::helper::QxConvertHelper_Registered>
{
   static inline QVariant toVariant(const T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   {
      if (ctx != qx::cvt::context::e_serialize_registered)
      { qx::IxDataMember * pId = qx::QxClass<T>::getSingleton()->getDataMemberX()->getId_WithDaoStrategy(); return (pId ? pId->toVariant((& t), format, index, ctx) : QVariant()); }
      return qx::serialization::qt::to_byte_array<T>(t);
   }
};

template <typename T>
struct QxConvertHelper_FromVariant<T, qx::cvt::detail::helper::QxConvertHelper_Registered>
{
   static inline qx_bool fromVariant(const QVariant & v, T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   {
      if (ctx != qx::cvt::context::e_serialize_registered)
      { qx::IxDataMember * pId = qx::QxClass<T>::getSingleton()->getDataMemberX()->getId_WithDaoStrategy(); return (pId ? pId->fromVariant((& t), v, format, index, ctx) : qx_bool(false)); }
      return qx::serialization::qt::from_byte_array<T>(t, v.toByteArray());
   }
};

#ifndef _QX_NO_JSON

template <typename T>
struct QxConvertHelper_ToJson<T, qx::cvt::detail::helper::QxConvertHelper_Registered>
{
   static inline QJsonValue toJson(const T & t, const QString & format)
   { return qx::cvt::detail::QxSerializeJsonRegistered<T>::save(t, format); }
};

template <typename T>
struct QxConvertHelper_FromJson<T, qx::cvt::detail::helper::QxConvertHelper_Registered>
{
   static inline qx_bool fromJson(const QJsonValue & j, T & t, const QString & format)
   { return qx::cvt::detail::QxSerializeJsonRegistered<T>::load(j, t, format); }
};

#endif // _QX_NO_JSON

template <typename T>
struct QxConvertHelper_ToString<T, qx::cvt::detail::helper::QxConvertHelper_Container>
{
   static inline QString toString(const T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   { Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); }
};

template <typename T>
struct QxConvertHelper_FromString<T, qx::cvt::detail::helper::QxConvertHelper_Container>
{
   static inline qx_bool fromString(const QString & s, T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   { Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::from_string(t, s); }
};

template <typename T>
struct QxConvertHelper_ToVariant<T, qx::cvt::detail::helper::QxConvertHelper_Container>
{
   static inline QVariant toVariant(const T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   { Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); }
};

template <typename T>
struct QxConvertHelper_FromVariant<T, qx::cvt::detail::helper::QxConvertHelper_Container>
{
   static inline qx_bool fromVariant(const QVariant & v, T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   { Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::from_string(t, v.toString()); }
};

#ifndef _QX_NO_JSON

template <typename T>
struct QxConvertHelper_ToJson<T, qx::cvt::detail::helper::QxConvertHelper_Container>
{
   static inline QJsonValue toJson(const T & t, const QString & format)
   { return QJsonValue::fromVariant(qx::cvt::detail::QxConvertHelper_ToVariant<T, qx::cvt::detail::helper::QxConvertHelper_Container>::toVariant(t, format, -1, qx::cvt::context::e_no_context)); }
};

template <typename T>
struct QxConvertHelper_FromJson<T, qx::cvt::detail::helper::QxConvertHelper_Container>
{
   static inline qx_bool fromJson(const QJsonValue & j, T & t, const QString & format)
   { QVariant v = j.toVariant(); return qx::cvt::detail::QxConvertHelper_FromVariant<T, qx::cvt::detail::helper::QxConvertHelper_Container>::fromVariant(v, t, format, -1, qx::cvt::context::e_no_context); }
};

#endif // _QX_NO_JSON

template <typename T>
struct QxConvertHelper_ToString<T, qx::cvt::detail::helper::QxConvertHelper_Enum>
{
   static inline QString toString(const T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   { Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QString::number(static_cast<long>(t)); }
};

template <typename T>
struct QxConvertHelper_FromString<T, qx::cvt::detail::helper::QxConvertHelper_Enum>
{
   static inline qx_bool fromString(const QString & s, T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   { Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); bool bOk = false; t = static_cast<T>(static_cast<long>(s.toLongLong(& bOk))); return bOk; }
};

template <typename T>
struct QxConvertHelper_ToVariant<T, qx::cvt::detail::helper::QxConvertHelper_Enum>
{
   static inline QVariant toVariant(const T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   { Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QVariant(static_cast<qlonglong>(t)); }
};

template <typename T>
struct QxConvertHelper_FromVariant<T, qx::cvt::detail::helper::QxConvertHelper_Enum>
{
   static inline qx_bool fromVariant(const QVariant & v, T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   { Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); bool bOk = false; t = static_cast<T>(static_cast<long>(v.toLongLong(& bOk))); return bOk; }
};

#ifndef _QX_NO_JSON

template <typename T>
struct QxConvertHelper_ToJson<T, qx::cvt::detail::helper::QxConvertHelper_Enum>
{
   static inline QJsonValue toJson(const T & t, const QString & format)
   { Q_UNUSED(format); return QJsonValue(static_cast<int>(t)); }
};

template <typename T>
struct QxConvertHelper_FromJson<T, qx::cvt::detail::helper::QxConvertHelper_Enum>
{
   static inline qx_bool fromJson(const QJsonValue & j, T & t, const QString & format)
   { Q_UNUSED(format); t = static_cast<T>(static_cast<long>(qRound(j.toDouble()))); return qx_bool(true); }
};

#endif // _QX_NO_JSON

template <typename T>
struct QxConvertHelper
{

private:

   typedef typename boost::mpl::if_c< boost::is_pointer<T>::value, qx::cvt::detail::helper::QxConvertHelper_Ptr, qx::cvt::detail::helper::QxConvertHelper_Generic >::type type_str_cvt_helper_1;
   typedef typename boost::mpl::if_c< qx::trait::is_smart_ptr<T>::value, qx::cvt::detail::helper::QxConvertHelper_Ptr, type_str_cvt_helper_1 >::type type_str_cvt_helper_2;
   typedef typename boost::mpl::if_c< qx::trait::is_container<T>::value, qx::cvt::detail::helper::QxConvertHelper_Container, type_str_cvt_helper_2 >::type type_str_cvt_helper_3;
   typedef typename boost::mpl::if_c< qx::trait::is_qx_registered<T>::value, qx::cvt::detail::helper::QxConvertHelper_Registered, type_str_cvt_helper_3 >::type type_str_cvt_helper_4;
   typedef typename boost::mpl::if_c< boost::is_enum<T>::value, qx::cvt::detail::helper::QxConvertHelper_Enum, type_str_cvt_helper_4 >::type type_str_cvt_helper_5;

public:

   typedef typename QxConvertHelper<T>::type_str_cvt_helper_5 type;

};

template <typename T>
struct QxConvert_ToString
{
   static inline QString toString(const T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   { return qx::cvt::detail::QxConvertHelper_ToString<T, typename qx::cvt::detail::QxConvertHelper<T>::type>::toString(t, format, index, ctx); }
};

template <typename T>
struct QxConvert_FromString
{
   static inline qx_bool fromString(const QString & s, T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   { return qx::cvt::detail::QxConvertHelper_FromString<T, typename qx::cvt::detail::QxConvertHelper<T>::type>::fromString(s, t, format, index, ctx); }
};

template <typename T>
struct QxConvert_ToVariant
{
   static inline QVariant toVariant(const T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   { return qx::cvt::detail::QxConvertHelper_ToVariant<T, typename qx::cvt::detail::QxConvertHelper<T>::type>::toVariant(t, format, index, ctx); }
};

template <typename T>
struct QxConvert_FromVariant
{
   static inline qx_bool fromVariant(const QVariant & v, T & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   { return qx::cvt::detail::QxConvertHelper_FromVariant<T, typename qx::cvt::detail::QxConvertHelper<T>::type>::fromVariant(v, t, format, index, ctx); }
};

#ifndef _QX_NO_JSON

template <typename T>
struct QxConvert_ToJson
{
   static inline QJsonValue toJson(const T & t, const QString & format)
   { return qx::cvt::detail::QxConvertHelper_ToJson<T, typename qx::cvt::detail::QxConvertHelper<T>::type>::toJson(t, format); }
};

template <typename T>
struct QxConvert_FromJson
{
   static inline qx_bool fromJson(const QJsonValue & j, T & t, const QString & format)
   { return qx::cvt::detail::QxConvertHelper_FromJson<T, typename qx::cvt::detail::QxConvertHelper<T>::type>::fromJson(j, t, format); }
};

#endif // _QX_NO_JSON

} // namespace detail
} // namespace cvt
} // namespace qx

#include "../../inl/QxConvert/QxConvert_WithIndex.inl"
#include "../../inl/QxConvert/QxConvert_ToString.inl"
#include "../../inl/QxConvert/QxConvert_FromString.inl"
#include "../../inl/QxConvert/QxConvert_ToVariant.inl"
#include "../../inl/QxConvert/QxConvert_FromVariant.inl"
#include "../../inl/QxConvert/QxConvert_ToJson.inl"
#include "../../inl/QxConvert/QxConvert_FromJson.inl"
#include "../../inl/QxConvert/QxConvert_Qt.inl"

#endif // _QX_CONVERT_IMPL_H_
