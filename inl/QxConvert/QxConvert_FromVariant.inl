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
#define QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT QX_CVT_DEFAULT_ARCHIVE::from_string(t, v.toString())
#else // _QX_ENABLE_BOOST_SERIALIZATION
#define QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT QX_CVT_DEFAULT_ARCHIVE::from_byte_array(t, v.toByteArray())
#endif // _QX_ENABLE_BOOST_SERIALIZATION

namespace qx {
namespace cvt {
namespace detail {

template <> struct QxConvert_FromVariant< qx::trait::no_type > {
static inline qx_bool fromVariant(const QVariant & v, qx::trait::no_type & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(v); Q_UNUSED(t); Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return qx_bool(true); } };

template <> struct QxConvert_FromVariant< bool > {
static inline qx_bool fromVariant(const QVariant & v, bool & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); t = v.toBool(); return qx_bool(true); } };

template <> struct QxConvert_FromVariant< short > {
static inline qx_bool fromVariant(const QVariant & v, short & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); bool bOk = false; t = static_cast<short>(v.toInt(& bOk)); return bOk; } };

template <> struct QxConvert_FromVariant< int > {
static inline qx_bool fromVariant(const QVariant & v, int & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); bool bOk = false; t = v.toInt(& bOk); return bOk; } };

template <> struct QxConvert_FromVariant< long > {
static inline qx_bool fromVariant(const QVariant & v, long & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); bool bOk = false; t = static_cast<long>(v.toLongLong(& bOk)); return bOk; } };

template <> struct QxConvert_FromVariant< long long > {
static inline qx_bool fromVariant(const QVariant & v, long long & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); bool bOk = false; t = static_cast<long long>(v.toLongLong(& bOk)); return bOk; } };

template <> struct QxConvert_FromVariant< float > {
static inline qx_bool fromVariant(const QVariant & v, float & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); bool bOk = false; t = static_cast<float>(v.toDouble(& bOk)); return bOk; } };

template <> struct QxConvert_FromVariant< double > {
static inline qx_bool fromVariant(const QVariant & v, double & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); bool bOk = false; t = v.toDouble(& bOk); return bOk; } };

template <> struct QxConvert_FromVariant< unsigned short > {
static inline qx_bool fromVariant(const QVariant & v, unsigned short & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); bool bOk = false; t = static_cast<unsigned short>(v.toUInt(& bOk)); return bOk; } };

template <> struct QxConvert_FromVariant< unsigned int > {
static inline qx_bool fromVariant(const QVariant & v, unsigned int & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); bool bOk = false; t = static_cast<unsigned int>(v.toUInt(& bOk)); return bOk; } };

template <> struct QxConvert_FromVariant< unsigned long > {
static inline qx_bool fromVariant(const QVariant & v, unsigned long & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); bool bOk = false; t = static_cast<unsigned long>(v.toULongLong(& bOk)); return bOk; } };

template <> struct QxConvert_FromVariant< unsigned long long > {
static inline qx_bool fromVariant(const QVariant & v, unsigned long long & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); bool bOk = false; t = static_cast<unsigned long long>(v.toULongLong(& bOk)); return bOk; } };

template <> struct QxConvert_FromVariant< QDate > {
static inline qx_bool fromVariant(const QVariant & v, QDate & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); t = v.toDate(); return t.isValid(); } };

template <> struct QxConvert_FromVariant< QTime > {
static inline qx_bool fromVariant(const QVariant & v, QTime & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); t = v.toTime(); return t.isValid(); } };

template <> struct QxConvert_FromVariant< QDateTime > {
static inline qx_bool fromVariant(const QVariant & v, QDateTime & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); t = v.toDateTime(); return t.isValid(); } };

template <> struct QxConvert_FromVariant< QByteArray > {
static inline qx_bool fromVariant(const QVariant & v, QByteArray & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); t = v.toByteArray(); return qx_bool(true); } };

template <> struct QxConvert_FromVariant< QString > {
static inline qx_bool fromVariant(const QVariant & v, QString & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); t = v.toString(); return qx_bool(true); } };

template <>
struct QxConvert_FromVariant< QVariant >
{
   static inline qx_bool fromVariant(const QVariant & v, QVariant & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   {
      if (ctx != qx::cvt::context::e_database) { t = v; return qx_bool(true); }
      QString s = v.toString(); if (! s.startsWith("$$JSON$$")) { t = v; return qx_bool(true); }
      return qx::cvt::detail::QxConvert_FromString< QVariant >::fromString(s, t, format, index, ctx);
   }
};

template <> struct QxConvert_FromVariant< QUuid > {
static inline qx_bool fromVariant(const QVariant & v, QUuid & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); t = QUuid(v.toString()); return qx_bool(true); } };

template <> struct QxConvert_FromVariant< qx::QxDateNeutral > {
static inline qx_bool fromVariant(const QVariant & v, qx::QxDateNeutral & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); t = qx::QxDateNeutral::fromNeutral(v.toString()); return qx_bool(true); } };

template <> struct QxConvert_FromVariant< qx::QxTimeNeutral > {
static inline qx_bool fromVariant(const QVariant & v, qx::QxTimeNeutral & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); t = qx::QxTimeNeutral::fromNeutral(v.toString()); return qx_bool(true); } };

template <> struct QxConvert_FromVariant< qx::QxDateTimeNeutral > {
static inline qx_bool fromVariant(const QVariant & v, qx::QxDateTimeNeutral & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); t = qx::QxDateTimeNeutral::fromNeutral(v.toString()); return qx_bool(true); } };

template <> struct QxConvert_FromVariant< std::string > {
static inline qx_bool fromVariant(const QVariant & v, std::string & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
#ifndef QT_NO_STL
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); t = v.toString().toStdString(); return qx_bool(true); } };
#else // QT_NO_STL
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); t = v.toString().toLatin1().constData(); return qx_bool(true); } };
#endif // QT_NO_STL

template <> struct QxConvert_FromVariant< std::wstring > {
static inline qx_bool fromVariant(const QVariant & v, std::wstring & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
#if ((! defined(QT_NO_STL)) && (! defined(QT_NO_STL_WCHAR)))
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); t = v.toString().toStdWString(); return qx_bool(true); } };
#else // ((! defined(QT_NO_STL)) && (! defined(QT_NO_STL_WCHAR)))
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); Q_UNUSED(t); Q_UNUSED(v); qAssert(false); /* Need STL compatibility ! */ return qx_bool(true); } };
#endif // ((! defined(QT_NO_STL)) && (! defined(QT_NO_STL_WCHAR)))

template <> struct QxConvert_FromVariant< qx_bool > {
static inline qx_bool fromVariant(const QVariant & v, qx_bool & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); QString s = v.toString(); t.fromString(s); return qx_bool(true); } };

template <typename T> struct QxConvert_FromVariant< boost::optional<T> > {
static inline qx_bool fromVariant(const QVariant & v, boost::optional<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{
   if (v.isNull()) { t = boost::none; return qx_bool(true); }
   else if (! t) { t = T(); }
   return qx::cvt::from_variant(v, (* t), format, index, ctx);
} };

template <typename T1, typename T2> struct QxConvert_FromVariant< std::pair<T1, T2> > {
static inline qx_bool fromVariant(const QVariant & v, std::pair<T1, T2> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename T1, typename T2> struct QxConvert_FromVariant< QPair<T1, T2> > {
static inline qx_bool fromVariant(const QVariant & v, QPair<T1, T2> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename T> struct QxConvert_FromVariant< std::vector<T> > {
static inline qx_bool fromVariant(const QVariant & v, std::vector<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename T> struct QxConvert_FromVariant< std::list<T> > {
static inline qx_bool fromVariant(const QVariant & v, std::list<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename T> struct QxConvert_FromVariant< std::set<T> > {
static inline qx_bool fromVariant(const QVariant & v, std::set<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename T> struct QxConvert_FromVariant< boost::unordered_set<T> > {
static inline qx_bool fromVariant(const QVariant & v, boost::unordered_set<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename T> struct QxConvert_FromVariant< boost::unordered_multiset<T> > {
static inline qx_bool fromVariant(const QVariant & v, boost::unordered_multiset<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

#ifdef _QX_CPP_11_CONTAINER
#ifndef BOOST_NO_CXX11_STD_UNORDERED

template <typename T> struct QxConvert_FromVariant< std::unordered_set<T> > {
static inline qx_bool fromVariant(const QVariant & v, std::unordered_set<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename T> struct QxConvert_FromVariant< std::unordered_multiset<T> > {
static inline qx_bool fromVariant(const QVariant & v, std::unordered_multiset<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

#endif // BOOST_NO_CXX11_STD_UNORDERED
#endif // _QX_CPP_11_CONTAINER

template <typename T> struct QxConvert_FromVariant< QVector<T> > {
static inline qx_bool fromVariant(const QVariant & v, QVector<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename T> struct QxConvert_FromVariant< QList<T> > {
static inline qx_bool fromVariant(const QVariant & v, QList<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename T> struct QxConvert_FromVariant< QLinkedList<T> > {
static inline qx_bool fromVariant(const QVariant & v, QLinkedList<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename T> struct QxConvert_FromVariant< QFlags<T> > {
static inline qx_bool fromVariant(const QVariant & v, QFlags<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); t = QFlags<T>(QFlag(v.toInt())); return true; } };

template <typename Key, typename Value> struct QxConvert_FromVariant< std::map<Key, Value> > {
static inline qx_bool fromVariant(const QVariant & v, std::map<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename Key, typename Value> struct QxConvert_FromVariant< boost::unordered_map<Key, Value> > {
static inline qx_bool fromVariant(const QVariant & v, boost::unordered_map<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename Key, typename Value> struct QxConvert_FromVariant< boost::unordered_multimap<Key, Value> > {
static inline qx_bool fromVariant(const QVariant & v, boost::unordered_multimap<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

#ifdef _QX_CPP_11_CONTAINER
#ifndef BOOST_NO_CXX11_STD_UNORDERED

template <typename Key, typename Value> struct QxConvert_FromVariant< std::unordered_map<Key, Value> > {
static inline qx_bool fromVariant(const QVariant & v, std::unordered_map<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename Key, typename Value> struct QxConvert_FromVariant< std::unordered_multimap<Key, Value> > {
static inline qx_bool fromVariant(const QVariant & v, std::unordered_multimap<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

#endif // BOOST_NO_CXX11_STD_UNORDERED
#endif // _QX_CPP_11_CONTAINER

template <typename Key, typename Value> struct QxConvert_FromVariant< QHash<Key, Value> > {
static inline qx_bool fromVariant(const QVariant & v, QHash<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename Key, typename Value> struct QxConvert_FromVariant< QMultiHash<Key, Value> > {
static inline qx_bool fromVariant(const QVariant & v, QMultiHash<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename Key, typename Value> struct QxConvert_FromVariant< QMap<Key, Value> > {
static inline qx_bool fromVariant(const QVariant & v, QMap<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename Key, typename Value> struct QxConvert_FromVariant< QMultiMap<Key, Value> > {
static inline qx_bool fromVariant(const QVariant & v, QMultiMap<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename Key, typename Value> struct QxConvert_FromVariant< qx::QxCollection<Key, Value> > {
static inline qx_bool fromVariant(const QVariant & v, qx::QxCollection<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename T1> struct QxConvert_FromVariant< boost::tuple<T1> > {
static inline qx_bool fromVariant(const QVariant & v, boost::tuple<T1> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename T1, typename T2> struct QxConvert_FromVariant< boost::tuple<T1, T2> > {
static inline qx_bool fromVariant(const QVariant & v, boost::tuple<T1, T2> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename T1, typename T2, typename T3> struct QxConvert_FromVariant< boost::tuple<T1, T2, T3> > {
static inline qx_bool fromVariant(const QVariant & v, boost::tuple<T1, T2, T3> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename T1, typename T2, typename T3, typename T4> struct QxConvert_FromVariant< boost::tuple<T1, T2, T3, T4> > {
static inline qx_bool fromVariant(const QVariant & v, boost::tuple<T1, T2, T3, T4> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename T1, typename T2, typename T3, typename T4, typename T5> struct QxConvert_FromVariant< boost::tuple<T1, T2, T3, T4, T5> > {
static inline qx_bool fromVariant(const QVariant & v, boost::tuple<T1, T2, T3, T4, T5> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> struct QxConvert_FromVariant< boost::tuple<T1, T2, T3, T4, T5, T6> > {
static inline qx_bool fromVariant(const QVariant & v, boost::tuple<T1, T2, T3, T4, T5, T6> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7> struct QxConvert_FromVariant< boost::tuple<T1, T2, T3, T4, T5, T6, T7> > {
static inline qx_bool fromVariant(const QVariant & v, boost::tuple<T1, T2, T3, T4, T5, T6, T7> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8> struct QxConvert_FromVariant< boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8> > {
static inline qx_bool fromVariant(const QVariant & v, boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9> struct QxConvert_FromVariant< boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> > {
static inline qx_bool fromVariant(const QVariant & v, boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

#ifdef _QX_CPP_11_TUPLE
#ifndef BOOST_NO_CXX11_HDR_TUPLE

template <typename T1> struct QxConvert_FromVariant< std::tuple<T1> > {
static inline qx_bool fromVariant(const QVariant & v, std::tuple<T1> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename T1, typename T2> struct QxConvert_FromVariant< std::tuple<T1, T2> > {
static inline qx_bool fromVariant(const QVariant & v, std::tuple<T1, T2> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename T1, typename T2, typename T3> struct QxConvert_FromVariant< std::tuple<T1, T2, T3> > {
static inline qx_bool fromVariant(const QVariant & v, std::tuple<T1, T2, T3> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename T1, typename T2, typename T3, typename T4> struct QxConvert_FromVariant< std::tuple<T1, T2, T3, T4> > {
static inline qx_bool fromVariant(const QVariant & v, std::tuple<T1, T2, T3, T4> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename T1, typename T2, typename T3, typename T4, typename T5> struct QxConvert_FromVariant< std::tuple<T1, T2, T3, T4, T5> > {
static inline qx_bool fromVariant(const QVariant & v, std::tuple<T1, T2, T3, T4, T5> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> struct QxConvert_FromVariant< std::tuple<T1, T2, T3, T4, T5, T6> > {
static inline qx_bool fromVariant(const QVariant & v, std::tuple<T1, T2, T3, T4, T5, T6> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7> struct QxConvert_FromVariant< std::tuple<T1, T2, T3, T4, T5, T6, T7> > {
static inline qx_bool fromVariant(const QVariant & v, std::tuple<T1, T2, T3, T4, T5, T6, T7> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8> struct QxConvert_FromVariant< std::tuple<T1, T2, T3, T4, T5, T6, T7, T8> > {
static inline qx_bool fromVariant(const QVariant & v, std::tuple<T1, T2, T3, T4, T5, T6, T7, T8> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9> struct QxConvert_FromVariant< std::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> > {
static inline qx_bool fromVariant(const QVariant & v, std::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_FROM_VARIANT; } };

#endif // BOOST_NO_CXX11_HDR_TUPLE
#endif // _QX_CPP_11_TUPLE

} // namespace detail
} // namespace cvt
} // namespace qx
