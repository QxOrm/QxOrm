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

namespace qx {
namespace cvt {
namespace detail {

template <> struct QxConvert_ToString< qx::trait::no_type > {
static inline QString toString(const qx::trait::no_type & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(t); Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return ""; } };

template <> struct QxConvert_ToString< QString > {
static inline QString toString(const QString & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return t; } };

template <> struct QxConvert_ToString< QUuid > {
static inline QString toString(const QUuid & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return t.toString(); } };

template <> struct QxConvert_ToString< QDate > {
static inline QString toString(const QDate & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(index); Q_UNUSED(ctx); return t.toString(format.isEmpty() ? QString(QX_STR_CVT_QDATE_FORMAT) : format); } };

template <> struct QxConvert_ToString< QTime > {
static inline QString toString(const QTime & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(index); Q_UNUSED(ctx); return t.toString(format.isEmpty() ? QString(QX_STR_CVT_QTIME_FORMAT) : format); } };

template <> struct QxConvert_ToString< QDateTime > {
static inline QString toString(const QDateTime & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(index); Q_UNUSED(ctx); return t.toString(format.isEmpty() ? QString(QX_STR_CVT_QDATETIME_FORMAT) : format); } };

template <> struct QxConvert_ToString< QByteArray > {
static inline QString toString(const QByteArray & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QString(t); } };

template <>
struct QxConvert_ToString< QVariant >
{
   static inline QString toString(const QVariant & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
   {
      Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx);

#ifndef _QX_NO_JSON
      if (qx::cvt::detail::helper::checkConvertQVariantToString(t))
      {
         QString type = QString("%1").arg(static_cast<int>(t.type()), 6, 10, QChar('0'));
         QString val = "$$JSON$$" + type + "$$";
         QJsonValue json = QJsonValue::fromVariant(t);
         QJsonDocument doc = (json.isArray() ? QJsonDocument(json.toArray()) : QJsonDocument(json.toObject()));
         return (val + QString::fromUtf8(doc.toJson()));
      }
#endif // _QX_NO_JSON

      return t.toString();
   }
};

template <> struct QxConvert_ToString< qx_bool > {
static inline QString toString(const qx_bool & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return t.toString(); } };

template <> struct QxConvert_ToString< bool > {
static inline QString toString(const bool & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return (t ? "1" : "0"); } };

template <> struct QxConvert_ToString< char > {
static inline QString toString(const char & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QString(t); } };

template <> struct QxConvert_ToString< short > {
static inline QString toString(const short & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(index); Q_UNUSED(ctx); return (format.isEmpty() ? QString::number(t) : QString().sprintf(qPrintable(format), t)); } };

template <> struct QxConvert_ToString< int > {
static inline QString toString(const int & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(index); Q_UNUSED(ctx); return (format.isEmpty() ? QString::number(t) : QString().sprintf(qPrintable(format), t)); } };

template <> struct QxConvert_ToString< long > {
static inline QString toString(const long & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(index); Q_UNUSED(ctx); return (format.isEmpty() ? QString::number(t) : QString().sprintf(qPrintable(format), t)); } };

template <> struct QxConvert_ToString< long long > {
static inline QString toString(const long long & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(index); Q_UNUSED(ctx); return (format.isEmpty() ? QString::number(t) : QString().sprintf(qPrintable(format), t)); } };

template <> struct QxConvert_ToString< float > {
static inline QString toString(const float & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(index); Q_UNUSED(ctx); return (format.isEmpty() ? QString::number(t) : QString().sprintf(qPrintable(format), t)); } };

template <> struct QxConvert_ToString< double > {
static inline QString toString(const double & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(index); Q_UNUSED(ctx); return (format.isEmpty() ? QString::number(t) : QString().sprintf(qPrintable(format), t)); } };

template <> struct QxConvert_ToString< unsigned short > {
static inline QString toString(const unsigned short & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(index); Q_UNUSED(ctx); return (format.isEmpty() ? QString::number(t) : QString().sprintf(qPrintable(format), t)); } };

template <> struct QxConvert_ToString< unsigned int > {
static inline QString toString(const unsigned int & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(index); Q_UNUSED(ctx); return (format.isEmpty() ? QString::number(t) : QString().sprintf(qPrintable(format), t)); } };

template <> struct QxConvert_ToString< unsigned long > {
static inline QString toString(const unsigned long & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(index); Q_UNUSED(ctx); return (format.isEmpty() ? QString::number(t) : QString().sprintf(qPrintable(format), t)); } };

template <> struct QxConvert_ToString< unsigned long long > {
static inline QString toString(const unsigned long long & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(index); Q_UNUSED(ctx); return (format.isEmpty() ? QString::number(t) : QString().sprintf(qPrintable(format), t)); } };

template <> struct QxConvert_ToString< qx::QxDateNeutral > {
static inline QString toString(const qx::QxDateNeutral & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return t.toNeutral(); } };

template <> struct QxConvert_ToString< qx::QxTimeNeutral > {
static inline QString toString(const qx::QxTimeNeutral & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return t.toNeutral(); } };

template <> struct QxConvert_ToString< qx::QxDateTimeNeutral > {
static inline QString toString(const qx::QxDateTimeNeutral & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return t.toNeutral(); } };

template <> struct QxConvert_ToString< std::string > {
static inline QString toString(const std::string & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
#ifndef QT_NO_STL
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QString::fromStdString(t); } };
#else // QT_NO_STL
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QString::fromLatin1(t.data(), int(t.size())); } };
#endif // QT_NO_STL

template <> struct QxConvert_ToString< std::wstring > {
static inline QString toString(const std::wstring & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
#if ((! defined(QT_NO_STL)) && (! defined(QT_NO_STL_WCHAR)))
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QString::fromStdWString(t); } };
#else // ((! defined(QT_NO_STL)) && (! defined(QT_NO_STL_WCHAR)))
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); Q_UNUSED(t); qAssert(false); /* Need STL compatibility ! */ return QString(); } };
#endif // ((! defined(QT_NO_STL)) && (! defined(QT_NO_STL_WCHAR)))

template <typename T> struct QxConvert_ToString< boost::optional<T> > {
static inline QString toString(const boost::optional<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ if (t) { return qx::cvt::to_string((* t), format, index, ctx); }; return QString(); } };

template <typename T1, typename T2> struct QxConvert_ToString< std::pair<T1, T2> > {
static inline QString toString(const std::pair<T1, T2> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename T1, typename T2> struct QxConvert_ToString< QPair<T1, T2> > {
static inline QString toString(const QPair<T1, T2> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename T> struct QxConvert_ToString< std::vector<T> > {
static inline QString toString(const std::vector<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename T> struct QxConvert_ToString< std::list<T> > {
static inline QString toString(const std::list<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename T> struct QxConvert_ToString< std::set<T> > {
static inline QString toString(const std::set<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename T> struct QxConvert_ToString< boost::unordered_set<T> > {
static inline QString toString(const boost::unordered_set<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename T> struct QxConvert_ToString< boost::unordered_multiset<T> > {
static inline QString toString(const boost::unordered_multiset<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

#ifdef _QX_CPP_11_CONTAINER
#ifndef BOOST_NO_CXX11_STD_UNORDERED

template <typename T> struct QxConvert_ToString< std::unordered_set<T> > {
static inline QString toString(const std::unordered_set<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename T> struct QxConvert_ToString< std::unordered_multiset<T> > {
static inline QString toString(const std::unordered_multiset<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

#endif // BOOST_NO_CXX11_STD_UNORDERED
#endif // _QX_CPP_11_CONTAINER

template <typename T> struct QxConvert_ToString< QVector<T> > {
static inline QString toString(const QVector<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename T> struct QxConvert_ToString< QList<T> > {
static inline QString toString(const QList<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename T> struct QxConvert_ToString< QLinkedList<T> > {
static inline QString toString(const QLinkedList<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename T> struct QxConvert_ToString< QFlags<T> > {
static inline QString toString(const QFlags<T> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QString::number(static_cast<int>(t)); } };

template <typename Key, typename Value> struct QxConvert_ToString< std::map<Key, Value> > {
static inline QString toString(const std::map<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename Key, typename Value> struct QxConvert_ToString< boost::unordered_map<Key, Value> > {
static inline QString toString(const boost::unordered_map<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename Key, typename Value> struct QxConvert_ToString< boost::unordered_multimap<Key, Value> > {
static inline QString toString(const boost::unordered_multimap<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

#ifdef _QX_CPP_11_CONTAINER
#ifndef BOOST_NO_CXX11_STD_UNORDERED

template <typename Key, typename Value> struct QxConvert_ToString< std::unordered_map<Key, Value> > {
static inline QString toString(const std::unordered_map<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename Key, typename Value> struct QxConvert_ToString< std::unordered_multimap<Key, Value> > {
static inline QString toString(const std::unordered_multimap<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

#endif // BOOST_NO_CXX11_STD_UNORDERED
#endif // _QX_CPP_11_CONTAINER

template <typename Key, typename Value> struct QxConvert_ToString< QHash<Key, Value> > {
static inline QString toString(const QHash<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename Key, typename Value> struct QxConvert_ToString< QMultiHash<Key, Value> > {
static inline QString toString(const QMultiHash<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename Key, typename Value> struct QxConvert_ToString< QMap<Key, Value> > {
static inline QString toString(const QMap<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename Key, typename Value> struct QxConvert_ToString< QMultiMap<Key, Value> > {
static inline QString toString(const QMultiMap<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename Key, typename Value> struct QxConvert_ToString< qx::QxCollection<Key, Value> > {
static inline QString toString(const qx::QxCollection<Key, Value> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename T1> struct QxConvert_ToString< boost::tuple<T1> > {
static inline QString toString(const boost::tuple<T1> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename T1, typename T2> struct QxConvert_ToString< boost::tuple<T1, T2> > {
static inline QString toString(const boost::tuple<T1, T2> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename T1, typename T2, typename T3> struct QxConvert_ToString< boost::tuple<T1, T2, T3> > {
static inline QString toString(const boost::tuple<T1, T2, T3> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename T1, typename T2, typename T3, typename T4> struct QxConvert_ToString< boost::tuple<T1, T2, T3, T4> > {
static inline QString toString(const boost::tuple<T1, T2, T3, T4> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5> struct QxConvert_ToString< boost::tuple<T1, T2, T3, T4, T5> > {
static inline QString toString(const boost::tuple<T1, T2, T3, T4, T5> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> struct QxConvert_ToString< boost::tuple<T1, T2, T3, T4, T5, T6> > {
static inline QString toString(const boost::tuple<T1, T2, T3, T4, T5, T6> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7> struct QxConvert_ToString< boost::tuple<T1, T2, T3, T4, T5, T6, T7> > {
static inline QString toString(const boost::tuple<T1, T2, T3, T4, T5, T6, T7> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8> struct QxConvert_ToString< boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8> > {
static inline QString toString(const boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9> struct QxConvert_ToString< boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> > {
static inline QString toString(const boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

#ifdef _QX_CPP_11_TUPLE
#ifndef BOOST_NO_CXX11_HDR_TUPLE

template <typename T1> struct QxConvert_ToString< std::tuple<T1> > {
static inline QString toString(const std::tuple<T1> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename T1, typename T2> struct QxConvert_ToString< std::tuple<T1, T2> > {
static inline QString toString(const std::tuple<T1, T2> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename T1, typename T2, typename T3> struct QxConvert_ToString< std::tuple<T1, T2, T3> > {
static inline QString toString(const std::tuple<T1, T2, T3> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename T1, typename T2, typename T3, typename T4> struct QxConvert_ToString< std::tuple<T1, T2, T3, T4> > {
static inline QString toString(const std::tuple<T1, T2, T3, T4> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5> struct QxConvert_ToString< std::tuple<T1, T2, T3, T4, T5> > {
static inline QString toString(const std::tuple<T1, T2, T3, T4, T5> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> struct QxConvert_ToString< std::tuple<T1, T2, T3, T4, T5, T6> > {
static inline QString toString(const std::tuple<T1, T2, T3, T4, T5, T6> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7> struct QxConvert_ToString< std::tuple<T1, T2, T3, T4, T5, T6, T7> > {
static inline QString toString(const std::tuple<T1, T2, T3, T4, T5, T6, T7> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8> struct QxConvert_ToString< std::tuple<T1, T2, T3, T4, T5, T6, T7, T8> > {
static inline QString toString(const std::tuple<T1, T2, T3, T4, T5, T6, T7, T8> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9> struct QxConvert_ToString< std::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> > {
static inline QString toString(const std::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> & t, const QString & format, int index, qx::cvt::context::ctx_type ctx)
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(ctx); return QX_CVT_DEFAULT_ARCHIVE::to_string(t); } };

#endif // BOOST_NO_CXX11_HDR_TUPLE
#endif // _QX_CPP_11_TUPLE

} // namespace detail
} // namespace cvt
} // namespace qx
