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
#define QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT QX_CVT_DEFAULT_ARCHIVE::to_string(t)
#else // _QX_ENABLE_BOOST_SERIALIZATION
#define QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT QX_CVT_DEFAULT_ARCHIVE::to_byte_array(t)
#endif // _QX_ENABLE_BOOST_SERIALIZATION

namespace qx {
namespace cvt {
namespace detail {

template <> struct QxConvert_ToVariant< qx::trait::no_type > {
static inline QVariant toVariant(const qx::trait::no_type & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(t); Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QVariant(); } };

template <> struct QxConvert_ToVariant< bool > {
static inline QVariant toVariant(const bool & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QVariant(t); } };

template <> struct QxConvert_ToVariant< short > {
static inline QVariant toVariant(const short & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QVariant(static_cast<int>(t)); } };

template <> struct QxConvert_ToVariant< int > {
static inline QVariant toVariant(const int & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QVariant(t); } };

template <> struct QxConvert_ToVariant< long > {
static inline QVariant toVariant(const long & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QVariant(static_cast<qlonglong>(t)); } };

template <> struct QxConvert_ToVariant< long long > {
static inline QVariant toVariant(const long long & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QVariant(static_cast<qlonglong>(t)); } };

template <> struct QxConvert_ToVariant< float > {
static inline QVariant toVariant(const float & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QVariant(static_cast<double>(t)); } };

template <> struct QxConvert_ToVariant< double > {
static inline QVariant toVariant(const double & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QVariant(t); } };

template <> struct QxConvert_ToVariant< unsigned short > {
static inline QVariant toVariant(const unsigned short & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QVariant(static_cast<unsigned int>(t)); } };

template <> struct QxConvert_ToVariant< unsigned int > {
static inline QVariant toVariant(const unsigned int & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QVariant(t); } };

template <> struct QxConvert_ToVariant< unsigned long > {
static inline QVariant toVariant(const unsigned long & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QVariant(static_cast<qulonglong>(t)); } };

template <> struct QxConvert_ToVariant< unsigned long long > {
static inline QVariant toVariant(const unsigned long long & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QVariant(static_cast<qulonglong>(t)); } };

template <> struct QxConvert_ToVariant< QDate > {
static inline QVariant toVariant(const QDate & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QVariant(t); } };

template <> struct QxConvert_ToVariant< QTime > {
static inline QVariant toVariant(const QTime & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QVariant(t); } };

template <> struct QxConvert_ToVariant< QDateTime > {
static inline QVariant toVariant(const QDateTime & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QVariant(t); } };

template <> struct QxConvert_ToVariant< QByteArray > {
static inline QVariant toVariant(const QByteArray & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QVariant(t); } };

template <> struct QxConvert_ToVariant< QString > {
static inline QVariant toVariant(const QString & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QVariant(t); } };

template <>
struct QxConvert_ToVariant< QVariant >
{
   static inline QVariant toVariant(const QVariant & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   {
      if (ctx != qx::cvt::context::e_database) { return t; }
      if (! qx::cvt::detail::helper::checkConvertQVariantToString(t)) { return t; }
      return QVariant(qx::cvt::detail::QxConvert_ToString< QVariant >::toString(t, format, index, ctx));
   }
};

template <> struct QxConvert_ToVariant< QUuid > {
static inline QVariant toVariant(const QUuid & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QVariant(t.toString()); } };

template <> struct QxConvert_ToVariant< qx::QxDateNeutral > {
static inline QVariant toVariant(const qx::QxDateNeutral & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QVariant(t.toNeutral()); } };

template <> struct QxConvert_ToVariant< qx::QxTimeNeutral > {
static inline QVariant toVariant(const qx::QxTimeNeutral & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QVariant(t.toNeutral()); } };

template <> struct QxConvert_ToVariant< qx::QxDateTimeNeutral > {
static inline QVariant toVariant(const qx::QxDateTimeNeutral & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QVariant(t.toNeutral()); } };

template <> struct QxConvert_ToVariant< std::string > {
static inline QVariant toVariant(const std::string & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
#ifndef QT_NO_STL
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QString::fromStdString(t); } };
#else // QT_NO_STL
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QString::fromLatin1(t.data(), int(t.size())); } };
#endif // QT_NO_STL

template <> struct QxConvert_ToVariant< std::wstring > {
static inline QVariant toVariant(const std::wstring & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
#if ((! defined(QT_NO_STL)) && (! defined(QT_NO_STL_WCHAR)))
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QString::fromStdWString(t); } };
#else // ((! defined(QT_NO_STL)) && (! defined(QT_NO_STL_WCHAR)))
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); Q_UNUSED(t); qAssert(false); /* Need STL compatibility ! */ return QVariant(); } };
#endif // ((! defined(QT_NO_STL)) && (! defined(QT_NO_STL_WCHAR)))

template <> struct QxConvert_ToVariant< qx_bool > {
static inline QVariant toVariant(const qx_bool & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return t.toString(); } };

template <typename T> struct QxConvert_ToVariant< boost::optional<T> > {
static inline QVariant toVariant(const boost::optional<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ if (t) { return qx::cvt::to_variant((* t), format, index, ctx); }; return QVariant(); } };

template <typename T1, typename T2> struct QxConvert_ToVariant< std::pair<T1, T2> > {
static inline QVariant toVariant(const std::pair<T1, T2> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename T1, typename T2> struct QxConvert_ToVariant< QPair<T1, T2> > {
static inline QVariant toVariant(const QPair<T1, T2> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename T> struct QxConvert_ToVariant< std::vector<T> > {
static inline QVariant toVariant(const std::vector<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename T> struct QxConvert_ToVariant< std::list<T> > {
static inline QVariant toVariant(const std::list<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename T> struct QxConvert_ToVariant< std::set<T> > {
static inline QVariant toVariant(const std::set<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename T> struct QxConvert_ToVariant< boost::unordered_set<T> > {
static inline QVariant toVariant(const boost::unordered_set<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename T> struct QxConvert_ToVariant< boost::unordered_multiset<T> > {
static inline QVariant toVariant(const boost::unordered_multiset<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

#ifdef _QX_CPP_11_CONTAINER
#ifndef BOOST_NO_CXX11_STD_UNORDERED

template <typename T> struct QxConvert_ToVariant< std::unordered_set<T> > {
static inline QVariant toVariant(const std::unordered_set<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename T> struct QxConvert_ToVariant< std::unordered_multiset<T> > {
static inline QVariant toVariant(const std::unordered_multiset<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

#endif // BOOST_NO_CXX11_STD_UNORDERED
#endif // _QX_CPP_11_CONTAINER

template <typename T> struct QxConvert_ToVariant< QVector<T> > {
static inline QVariant toVariant(const QVector<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename T> struct QxConvert_ToVariant< QList<T> > {
static inline QVariant toVariant(const QList<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename T> struct QxConvert_ToVariant< QLinkedList<T> > {
static inline QVariant toVariant(const QLinkedList<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename T> struct QxConvert_ToVariant< QFlags<T> > {
static inline QVariant toVariant(const QFlags<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QString::number(static_cast<int>(t)); } };

template <typename Key, typename Value> struct QxConvert_ToVariant< std::map<Key, Value> > {
static inline QVariant toVariant(const std::map<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename Key, typename Value> struct QxConvert_ToVariant< boost::unordered_map<Key, Value> > {
static inline QVariant toVariant(const boost::unordered_map<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename Key, typename Value> struct QxConvert_ToVariant< boost::unordered_multimap<Key, Value> > {
static inline QVariant toVariant(const boost::unordered_multimap<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

#ifdef _QX_CPP_11_CONTAINER
#ifndef BOOST_NO_CXX11_STD_UNORDERED

template <typename Key, typename Value> struct QxConvert_ToVariant< std::unordered_map<Key, Value> > {
static inline QVariant toVariant(const std::unordered_map<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename Key, typename Value> struct QxConvert_ToVariant< std::unordered_multimap<Key, Value> > {
static inline QVariant toVariant(const std::unordered_multimap<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

#endif // BOOST_NO_CXX11_STD_UNORDERED
#endif // _QX_CPP_11_CONTAINER

template <typename Key, typename Value> struct QxConvert_ToVariant< QHash<Key, Value> > {
static inline QVariant toVariant(const QHash<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename Key, typename Value> struct QxConvert_ToVariant< QMultiHash<Key, Value> > {
static inline QVariant toVariant(const QMultiHash<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename Key, typename Value> struct QxConvert_ToVariant< QMap<Key, Value> > {
static inline QVariant toVariant(const QMap<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename Key, typename Value> struct QxConvert_ToVariant< QMultiMap<Key, Value> > {
static inline QVariant toVariant(const QMultiMap<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename Key, typename Value> struct QxConvert_ToVariant< qx::QxCollection<Key, Value> > {
static inline QVariant toVariant(const qx::QxCollection<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename T1> struct QxConvert_ToVariant< boost::tuple<T1> > {
static inline QVariant toVariant(const boost::tuple<T1> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename T1, typename T2> struct QxConvert_ToVariant< boost::tuple<T1, T2> > {
static inline QVariant toVariant(const boost::tuple<T1, T2> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename T1, typename T2, typename T3> struct QxConvert_ToVariant< boost::tuple<T1, T2, T3> > {
static inline QVariant toVariant(const boost::tuple<T1, T2, T3> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename T1, typename T2, typename T3, typename T4> struct QxConvert_ToVariant< boost::tuple<T1, T2, T3, T4> > {
static inline QVariant toVariant(const boost::tuple<T1, T2, T3, T4> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename T1, typename T2, typename T3, typename T4, typename T5> struct QxConvert_ToVariant< boost::tuple<T1, T2, T3, T4, T5> > {
static inline QVariant toVariant(const boost::tuple<T1, T2, T3, T4, T5> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> struct QxConvert_ToVariant< boost::tuple<T1, T2, T3, T4, T5, T6> > {
static inline QVariant toVariant(const boost::tuple<T1, T2, T3, T4, T5, T6> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7> struct QxConvert_ToVariant< boost::tuple<T1, T2, T3, T4, T5, T6, T7> > {
static inline QVariant toVariant(const boost::tuple<T1, T2, T3, T4, T5, T6, T7> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8> struct QxConvert_ToVariant< boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8> > {
static inline QVariant toVariant(const boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9> struct QxConvert_ToVariant< boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> > {
static inline QVariant toVariant(const boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

#ifdef _QX_CPP_11_TUPLE
#ifndef BOOST_NO_CXX11_HDR_TUPLE

template <typename T1> struct QxConvert_ToVariant< std::tuple<T1> > {
static inline QVariant toVariant(const std::tuple<T1> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename T1, typename T2> struct QxConvert_ToVariant< std::tuple<T1, T2> > {
static inline QVariant toVariant(const std::tuple<T1, T2> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename T1, typename T2, typename T3> struct QxConvert_ToVariant< std::tuple<T1, T2, T3> > {
static inline QVariant toVariant(const std::tuple<T1, T2, T3> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename T1, typename T2, typename T3, typename T4> struct QxConvert_ToVariant< std::tuple<T1, T2, T3, T4> > {
static inline QVariant toVariant(const std::tuple<T1, T2, T3, T4> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename T1, typename T2, typename T3, typename T4, typename T5> struct QxConvert_ToVariant< std::tuple<T1, T2, T3, T4, T5> > {
static inline QVariant toVariant(const std::tuple<T1, T2, T3, T4, T5> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> struct QxConvert_ToVariant< std::tuple<T1, T2, T3, T4, T5, T6> > {
static inline QVariant toVariant(const std::tuple<T1, T2, T3, T4, T5, T6> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7> struct QxConvert_ToVariant< std::tuple<T1, T2, T3, T4, T5, T6, T7> > {
static inline QVariant toVariant(const std::tuple<T1, T2, T3, T4, T5, T6, T7> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8> struct QxConvert_ToVariant< std::tuple<T1, T2, T3, T4, T5, T6, T7, T8> > {
static inline QVariant toVariant(const std::tuple<T1, T2, T3, T4, T5, T6, T7, T8> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9> struct QxConvert_ToVariant< std::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> > {
static inline QVariant toVariant(const std::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE_TO_VARIANT; } };

#endif // BOOST_NO_CXX11_HDR_TUPLE
#endif // _QX_CPP_11_TUPLE

} // namespace detail
} // namespace cvt
} // namespace qx
