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

template <> struct QxStringCvt_FromString< qx::trait::no_type > {
static inline qx_bool fromString(const QString & s, qx::trait::no_type & t, const QString & format, int index)
{ Q_UNUSED(s); Q_UNUSED(t); Q_UNUSED(format); Q_UNUSED(index); return qx_bool(true); } };

template <> struct QxStringCvt_FromString< QString > {
static inline qx_bool fromString(const QString & s, QString & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); t = s; return qx_bool(true); } };

template <> struct QxStringCvt_FromString< QUuid > {
static inline qx_bool fromString(const QString & s, QUuid & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); t = QUuid(s); return qx_bool(true); } };

template <> struct QxStringCvt_FromString< QDate > {
static inline qx_bool fromString(const QString & s, QDate & t, const QString & format, int index)
{ Q_UNUSED(index); t = QDate::fromString(s, (format.isEmpty() ? QX_STR_CVT_QDATE_FORMAT : format)); return t.isValid(); } };

template <> struct QxStringCvt_FromString< QTime > {
static inline qx_bool fromString(const QString & s, QTime & t, const QString & format, int index)
{ Q_UNUSED(index); t = QTime::fromString(s, (format.isEmpty() ? QX_STR_CVT_QTIME_FORMAT : format)); return t.isValid(); } };

template <> struct QxStringCvt_FromString< QDateTime > {
static inline qx_bool fromString(const QString & s, QDateTime & t, const QString & format, int index)
{ Q_UNUSED(index); t = QDateTime::fromString(s, (format.isEmpty() ? QX_STR_CVT_QDATETIME_FORMAT : format)); return t.isValid(); } };

template <> struct QxStringCvt_FromString< QByteArray > {
static inline qx_bool fromString(const QString & s, QByteArray & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); t = s.toLatin1(); return qx_bool(true); } };

template <> struct QxStringCvt_FromString< QVariant > {
static inline qx_bool fromString(const QString & s, QVariant & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); t = QVariant(s); return qx_bool(true); } };

template <> struct QxStringCvt_FromString< qx_bool > {
static inline qx_bool fromString(const QString & s, qx_bool & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); t = (((s == "0") || s.trimmed().isEmpty()) ? false : true); return qx_bool(true); } };

template <> struct QxStringCvt_FromString< bool > {
static inline qx_bool fromString(const QString & s, bool & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); t = (((s == "0") || s.trimmed().isEmpty()) ? false : true); return qx_bool(true); } };

template <> struct QxStringCvt_FromString< char > {
static inline qx_bool fromString(const QString & s, char & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); t = (s.isEmpty() ? ' ' : s.toLatin1().at(0)); return (! s.isEmpty()); } };

template <> struct QxStringCvt_FromString< short > {
static inline qx_bool fromString(const QString & s, short & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); bool bOk = false; t = s.toShort(& bOk); return bOk; } };

template <> struct QxStringCvt_FromString< int > {
static inline qx_bool fromString(const QString & s, int & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); bool bOk = false; t = s.toInt(& bOk); return bOk; } };

template <> struct QxStringCvt_FromString< long > {
static inline qx_bool fromString(const QString & s, long & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); bool bOk = false; t = static_cast<long>(s.toLongLong(& bOk)); return bOk; } };

template <> struct QxStringCvt_FromString< long long > {
static inline qx_bool fromString(const QString & s, long long & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); bool bOk = false; t = static_cast<long long>(s.toLongLong(& bOk)); return bOk; } };

template <> struct QxStringCvt_FromString< float > {
static inline qx_bool fromString(const QString & s, float & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); bool bOk = false; t = static_cast<float>(s.toDouble(& bOk)); return bOk; } };

template <> struct QxStringCvt_FromString< double > {
static inline qx_bool fromString(const QString & s, double & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); bool bOk = false; t = s.toDouble(& bOk); return bOk; } };

template <> struct QxStringCvt_FromString< unsigned short > {
static inline qx_bool fromString(const QString & s, unsigned short & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); bool bOk = false; t = static_cast<unsigned short>(s.toUShort(& bOk)); return bOk; } };

template <> struct QxStringCvt_FromString< unsigned int > {
static inline qx_bool fromString(const QString & s, unsigned int & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); bool bOk = false; t = static_cast<unsigned int>(s.toUInt(& bOk)); return bOk; } };

template <> struct QxStringCvt_FromString< unsigned long > {
static inline qx_bool fromString(const QString & s, unsigned long & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); bool bOk = false; t = static_cast<unsigned long>(s.toULongLong(& bOk)); return bOk; } };

template <> struct QxStringCvt_FromString< unsigned long long > {
static inline qx_bool fromString(const QString & s, unsigned long long & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); bool bOk = false; t = static_cast<unsigned long long>(s.toULongLong(& bOk)); return bOk; } };

template <> struct QxStringCvt_FromString< qx::QxDateNeutral > {
static inline qx_bool fromString(const QString & s, qx::QxDateNeutral & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); t = qx::QxDateNeutral::fromNeutral(s); return qx_bool(true); } };

template <> struct QxStringCvt_FromString< qx::QxTimeNeutral > {
static inline qx_bool fromString(const QString & s, qx::QxTimeNeutral & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); t = qx::QxTimeNeutral::fromNeutral(s); return qx_bool(true); } };

template <> struct QxStringCvt_FromString< qx::QxDateTimeNeutral > {
static inline qx_bool fromString(const QString & s, qx::QxDateTimeNeutral & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); t = qx::QxDateTimeNeutral::fromNeutral(s); return qx_bool(true); } };

template <> struct QxStringCvt_FromString< std::string > {
static inline qx_bool fromString(const QString & s, std::string & t, const QString & format, int index)
#ifndef QT_NO_STL
{ Q_UNUSED(format); Q_UNUSED(index); t = s.toStdString(); return qx_bool(true); } };
#else // QT_NO_STL
{ Q_UNUSED(format); Q_UNUSED(index); t = s.toLatin1().constData(); return qx_bool(true); } };
#endif // QT_NO_STL

template <> struct QxStringCvt_FromString< std::wstring > {
static inline qx_bool fromString(const QString & s, std::wstring & t, const QString & format, int index)
#if ((! defined(QT_NO_STL)) && (! defined(QT_NO_STL_WCHAR)))
{ Q_UNUSED(format); Q_UNUSED(index); t = s.toStdWString(); return qx_bool(true); } };
#else // ((! defined(QT_NO_STL)) && (! defined(QT_NO_STL_WCHAR)))
{ Q_UNUSED(format); Q_UNUSED(index); Q_UNUSED(t); Q_UNUSED(s); qAssert(false); /* Need STL compatibility ! */ return qx_bool(true); } };
#endif // ((! defined(QT_NO_STL)) && (! defined(QT_NO_STL_WCHAR)))

template <typename T> struct QxStringCvt_FromString< boost::optional<T> > {
static inline qx_bool fromString(const QString & s, boost::optional<T> & t, const QString & format, int index)
{ if (! t) { t = T(); }; return qx::cvt::from_string(s, (* t), format, index); } };

template <typename T1, typename T2> struct QxStringCvt_FromString< std::pair<T1, T2> > {
static inline qx_bool fromString(const QString & s, std::pair<T1, T2> & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, s); } };

template <typename T1, typename T2> struct QxStringCvt_FromString< QPair<T1, T2> > {
static inline qx_bool fromString(const QString & s, QPair<T1, T2> & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, s); } };

template <typename T> struct QxStringCvt_FromString< std::vector<T> > {
static inline qx_bool fromString(const QString & s, std::vector<T> & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, s); } };

template <typename T> struct QxStringCvt_FromString< std::list<T> > {
static inline qx_bool fromString(const QString & s, std::list<T> & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, s); } };

template <typename T> struct QxStringCvt_FromString< std::set<T> > {
static inline qx_bool fromString(const QString & s, std::set<T> & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, s); } };

template <typename T> struct QxStringCvt_FromString< boost::unordered_set<T> > {
static inline qx_bool fromString(const QString & s, boost::unordered_set<T> & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, s); } };

template <typename T> struct QxStringCvt_FromString< boost::unordered_multiset<T> > {
static inline qx_bool fromString(const QString & s, boost::unordered_multiset<T> & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, s); } };

template <typename T> struct QxStringCvt_FromString< QVector<T> > {
static inline qx_bool fromString(const QString & s, QVector<T> & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, s); } };

template <typename T> struct QxStringCvt_FromString< QList<T> > {
static inline qx_bool fromString(const QString & s, QList<T> & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, s); } };

template <typename T> struct QxStringCvt_FromString< QLinkedList<T> > {
static inline qx_bool fromString(const QString & s, QLinkedList<T> & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, s); } };

template <typename T> struct QxStringCvt_FromString< QFlags<T> > {
static inline qx_bool fromString(const QString & s, QFlags<T> & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); t = QFlags<T>(QFlag(s.toInt())); return true; } };

template <typename Key, typename Value> struct QxStringCvt_FromString< std::map<Key, Value> > {
static inline qx_bool fromString(const QString & s, std::map<Key, Value> & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, s); } };

template <typename Key, typename Value> struct QxStringCvt_FromString< boost::unordered_map<Key, Value> > {
static inline qx_bool fromString(const QString & s, boost::unordered_map<Key, Value> & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, s); } };

template <typename Key, typename Value> struct QxStringCvt_FromString< boost::unordered_multimap<Key, Value> > {
static inline qx_bool fromString(const QString & s, boost::unordered_multimap<Key, Value> & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, s); } };

template <typename Key, typename Value> struct QxStringCvt_FromString< QHash<Key, Value> > {
static inline qx_bool fromString(const QString & s, QHash<Key, Value> & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, s); } };

template <typename Key, typename Value> struct QxStringCvt_FromString< QMultiHash<Key, Value> > {
static inline qx_bool fromString(const QString & s, QMultiHash<Key, Value> & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, s); } };

template <typename Key, typename Value> struct QxStringCvt_FromString< QMap<Key, Value> > {
static inline qx_bool fromString(const QString & s, QMap<Key, Value> & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, s); } };

template <typename Key, typename Value> struct QxStringCvt_FromString< QMultiMap<Key, Value> > {
static inline qx_bool fromString(const QString & s, QMultiMap<Key, Value> & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, s); } };

template <typename Key, typename Value> struct QxStringCvt_FromString< qx::QxCollection<Key, Value> > {
static inline qx_bool fromString(const QString & s, qx::QxCollection<Key, Value> & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, s); } };

template <typename T1> struct QxStringCvt_FromString< boost::tuple<T1> > {
static inline qx_bool fromString(const QString & s, boost::tuple<T1> & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, s); } };

template <typename T1, typename T2> struct QxStringCvt_FromString< boost::tuple<T1, T2> > {
static inline qx_bool fromString(const QString & s, boost::tuple<T1, T2> & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, s); } };

template <typename T1, typename T2, typename T3> struct QxStringCvt_FromString< boost::tuple<T1, T2, T3> > {
static inline qx_bool fromString(const QString & s, boost::tuple<T1, T2, T3> & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, s); } };

template <typename T1, typename T2, typename T3, typename T4> struct QxStringCvt_FromString< boost::tuple<T1, T2, T3, T4> > {
static inline qx_bool fromString(const QString & s, boost::tuple<T1, T2, T3, T4> & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, s); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5> struct QxStringCvt_FromString< boost::tuple<T1, T2, T3, T4, T5> > {
static inline qx_bool fromString(const QString & s, boost::tuple<T1, T2, T3, T4, T5> & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, s); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6> struct QxStringCvt_FromString< boost::tuple<T1, T2, T3, T4, T5, T6> > {
static inline qx_bool fromString(const QString & s, boost::tuple<T1, T2, T3, T4, T5, T6> & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, s); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7> struct QxStringCvt_FromString< boost::tuple<T1, T2, T3, T4, T5, T6, T7> > {
static inline qx_bool fromString(const QString & s, boost::tuple<T1, T2, T3, T4, T5, T6, T7> & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, s); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8> struct QxStringCvt_FromString< boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8> > {
static inline qx_bool fromString(const QString & s, boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8> & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, s); } };

template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9> struct QxStringCvt_FromString< boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> > {
static inline qx_bool fromString(const QString & s, boost::tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9> & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QX_STR_CVT_DEFAULT_ARCHIVE::from_string(t, s); } };

} // namespace detail
} // namespace cvt
} // namespace qx
