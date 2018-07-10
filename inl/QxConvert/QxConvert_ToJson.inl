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

#ifndef _QX_NO_JSON

namespace qx {
namespace cvt {
namespace detail {

template <> struct QxConvert_ToJson< qx::trait::no_type > {
static inline QJsonValue toJson(const qx::trait::no_type & t, const QString & format)
{ Q_UNUSED(t); Q_UNUSED(format); return QJsonValue(); } };

template <> struct QxConvert_ToJson< bool > {
static inline QJsonValue toJson(const bool & t, const QString & format)
{ Q_UNUSED(format); return QJsonValue(t); } };

template <> struct QxConvert_ToJson< short > {
static inline QJsonValue toJson(const short & t, const QString & format)
{ Q_UNUSED(format); return QJsonValue(static_cast<int>(t)); } };

template <> struct QxConvert_ToJson< int > {
static inline QJsonValue toJson(const int & t, const QString & format)
{ Q_UNUSED(format); return QJsonValue(t); } };

template <> struct QxConvert_ToJson< long > {
static inline QJsonValue toJson(const long & t, const QString & format)
{ Q_UNUSED(format); return QJsonValue(static_cast<double>(t)); } };

template <> struct QxConvert_ToJson< long long > {
static inline QJsonValue toJson(const long long & t, const QString & format)
{ Q_UNUSED(format); return QJsonValue(static_cast<double>(t)); } };

template <> struct QxConvert_ToJson< float > {
static inline QJsonValue toJson(const float & t, const QString & format)
{ Q_UNUSED(format); return QJsonValue(static_cast<double>(t)); } };

template <> struct QxConvert_ToJson< double > {
static inline QJsonValue toJson(const double & t, const QString & format)
{ Q_UNUSED(format); return QJsonValue(t); } };

template <> struct QxConvert_ToJson< unsigned short > {
static inline QJsonValue toJson(const unsigned short & t, const QString & format)
{ Q_UNUSED(format); return QJsonValue(static_cast<int>(t)); } };

template <> struct QxConvert_ToJson< unsigned int > {
static inline QJsonValue toJson(const unsigned int & t, const QString & format)
{ Q_UNUSED(format); return QJsonValue(static_cast<int>(t)); } };

template <> struct QxConvert_ToJson< unsigned long > {
static inline QJsonValue toJson(const unsigned long & t, const QString & format)
{ Q_UNUSED(format); return QJsonValue(static_cast<double>(t)); } };

template <> struct QxConvert_ToJson< unsigned long long > {
static inline QJsonValue toJson(const unsigned long long & t, const QString & format)
{ Q_UNUSED(format); return QJsonValue(static_cast<double>(t)); } };

template <> struct QxConvert_ToJson< QDate > {
static inline QJsonValue toJson(const QDate & t, const QString & format)
{ Q_UNUSED(format); if (t.isValid()) { return QJsonValue(t.toString(Qt::ISODate)); }; return QJsonValue(); } };

template <> struct QxConvert_ToJson< QTime > {
static inline QJsonValue toJson(const QTime & t, const QString & format)
{ Q_UNUSED(format); if (t.isValid()) { return QJsonValue(t.toString(Qt::ISODate)); }; return QJsonValue(); } };

template <> struct QxConvert_ToJson< QDateTime > {
static inline QJsonValue toJson(const QDateTime & t, const QString & format)
{ Q_UNUSED(format); if (t.isValid()) { return QJsonValue(t.toString(Qt::ISODate)); }; return QJsonValue(); } };

template <> struct QxConvert_ToJson< QByteArray > {
static inline QJsonValue toJson(const QByteArray & t, const QString & format)
{ Q_UNUSED(format); QString s = t.toBase64(); return QJsonValue(s); } };

template <> struct QxConvert_ToJson< QString > {
static inline QJsonValue toJson(const QString & t, const QString & format)
{ Q_UNUSED(format); return QJsonValue(t); } };

template <> struct QxConvert_ToJson< QVariant > {
static inline QJsonValue toJson(const QVariant & t, const QString & format)
{ Q_UNUSED(format); return QJsonValue::fromVariant(t); } };

template <> struct QxConvert_ToJson< QUuid > {
static inline QJsonValue toJson(const QUuid & t, const QString & format)
{ Q_UNUSED(format); return QJsonValue(t.toString()); } };

template <> struct QxConvert_ToJson< qx::QxDateNeutral > {
static inline QJsonValue toJson(const qx::QxDateNeutral & t, const QString & format)
{ Q_UNUSED(format); return QJsonValue(t.toNeutral()); } };

template <> struct QxConvert_ToJson< qx::QxTimeNeutral > {
static inline QJsonValue toJson(const qx::QxTimeNeutral & t, const QString & format)
{ Q_UNUSED(format); return QJsonValue(t.toNeutral()); } };

template <> struct QxConvert_ToJson< qx::QxDateTimeNeutral > {
static inline QJsonValue toJson(const qx::QxDateTimeNeutral & t, const QString & format)
{ Q_UNUSED(format); return QJsonValue(t.toNeutral()); } };

template <> struct QxConvert_ToJson< std::string > {
static inline QJsonValue toJson(const std::string & t, const QString & format)
#ifndef QT_NO_STL
{ Q_UNUSED(format); return QJsonValue(QString::fromStdString(t)); } };
#else // QT_NO_STL
{ Q_UNUSED(format); return QJsonValue(QString::fromLatin1(t.data(), int(t.size()))); } };
#endif // QT_NO_STL

template <> struct QxConvert_ToJson< std::wstring > {
static inline QJsonValue toJson(const std::wstring & t, const QString & format)
#if ((! defined(QT_NO_STL)) && (! defined(QT_NO_STL_WCHAR)))
{ Q_UNUSED(format); return QJsonValue(QString::fromStdWString(t)); } };
#else // ((! defined(QT_NO_STL)) && (! defined(QT_NO_STL_WCHAR)))
{ Q_UNUSED(format); Q_UNUSED(t); qAssert(false); /* Need STL compatibility ! */ return QJsonValue(); } };
#endif // ((! defined(QT_NO_STL)) && (! defined(QT_NO_STL_WCHAR)))

template <> struct QxConvert_ToJson< qx_bool > {
static inline QJsonValue toJson(const qx_bool & t, const QString & format)
{ Q_UNUSED(format); QJsonObject obj; obj["value"] = t.getValue(); obj["code"] = static_cast<double>(t.getCode()); obj["desc"] = t.getDesc(); return QJsonValue(obj); } };

template <typename T> struct QxConvert_ToJson< boost::optional<T> > {
static inline QJsonValue toJson(const boost::optional<T> & t, const QString & format)
{ if (t) { return qx::cvt::to_json((* t), format); }; return QJsonValue(); } };

} // namespace detail
} // namespace cvt
} // namespace qx

#endif // _QX_NO_JSON
