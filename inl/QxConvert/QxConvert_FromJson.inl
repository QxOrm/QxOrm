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

template <> struct QxConvert_FromJson< qx::trait::no_type > {
static inline qx_bool fromJson(const QJsonValue & j, qx::trait::no_type & t, const QString & format)
{ Q_UNUSED(j); Q_UNUSED(t); Q_UNUSED(format); return qx_bool(true); } };

template <> struct QxConvert_FromJson< bool > {
static inline qx_bool fromJson(const QJsonValue & j, bool & t, const QString & format)
{ Q_UNUSED(format); t = j.toBool(); return qx_bool(true); } };

template <> struct QxConvert_FromJson< short > {
static inline qx_bool fromJson(const QJsonValue & j, short & t, const QString & format)
{ Q_UNUSED(format); t = static_cast<short>(qRound(j.toDouble())); return qx_bool(true); } };

template <> struct QxConvert_FromJson< int > {
static inline qx_bool fromJson(const QJsonValue & j, int & t, const QString & format)
{ Q_UNUSED(format); t = qRound(j.toDouble()); return qx_bool(true); } };

template <> struct QxConvert_FromJson< long > {
static inline qx_bool fromJson(const QJsonValue & j, long & t, const QString & format)
{ Q_UNUSED(format); t = static_cast<long>(qRound64(j.toDouble())); return qx_bool(true); } };

template <> struct QxConvert_FromJson< long long > {
static inline qx_bool fromJson(const QJsonValue & j, long long & t, const QString & format)
{ Q_UNUSED(format); t = static_cast<long long>(qRound64(j.toDouble())); return qx_bool(true); } };

template <> struct QxConvert_FromJson< float > {
static inline qx_bool fromJson(const QJsonValue & j, float & t, const QString & format)
{ Q_UNUSED(format); t = static_cast<float>(j.toDouble()); return qx_bool(true); } };

template <> struct QxConvert_FromJson< double > {
static inline qx_bool fromJson(const QJsonValue & j, double & t, const QString & format)
{ Q_UNUSED(format); t = j.toDouble(); return qx_bool(true); } };

template <> struct QxConvert_FromJson< unsigned short > {
static inline qx_bool fromJson(const QJsonValue & j, unsigned short & t, const QString & format)
{ Q_UNUSED(format); t = static_cast<unsigned short>(qRound(j.toDouble())); return qx_bool(true); } };

template <> struct QxConvert_FromJson< unsigned int > {
static inline qx_bool fromJson(const QJsonValue & j, unsigned int & t, const QString & format)
{ Q_UNUSED(format); t = static_cast<unsigned int>(qRound(j.toDouble())); return qx_bool(true); } };

template <> struct QxConvert_FromJson< unsigned long > {
static inline qx_bool fromJson(const QJsonValue & j, unsigned long & t, const QString & format)
{ Q_UNUSED(format); t = static_cast<unsigned long>(qRound64(j.toDouble())); return qx_bool(true); } };

template <> struct QxConvert_FromJson< unsigned long long > {
static inline qx_bool fromJson(const QJsonValue & j, unsigned long long & t, const QString & format)
{ Q_UNUSED(format); t = static_cast<unsigned long long>(qRound64(j.toDouble())); return qx_bool(true); } };

template <> struct QxConvert_FromJson< QDate > {
static inline qx_bool fromJson(const QJsonValue & j, QDate & t, const QString & format)
{ Q_UNUSED(format); t = (j.isNull() ? QDate() : QDate::fromString(j.toString(), Qt::ISODate)); return qx_bool(true); } };

template <> struct QxConvert_FromJson< QTime > {
static inline qx_bool fromJson(const QJsonValue & j, QTime & t, const QString & format)
{ Q_UNUSED(format); t = (j.isNull() ? QTime() : QTime::fromString(j.toString(), Qt::ISODate)); return qx_bool(true); } };

template <> struct QxConvert_FromJson< QDateTime > {
static inline qx_bool fromJson(const QJsonValue & j, QDateTime & t, const QString & format)
{ Q_UNUSED(format); t = (j.isNull() ? QDateTime() : QDateTime::fromString(j.toString(), Qt::ISODate)); return qx_bool(true); } };

template <> struct QxConvert_FromJson< QByteArray > {
static inline qx_bool fromJson(const QJsonValue & j, QByteArray & t, const QString & format)
{ Q_UNUSED(format); t = QByteArray::fromBase64(j.toString().toLatin1()); return qx_bool(true); } };

template <> struct QxConvert_FromJson< QString > {
static inline qx_bool fromJson(const QJsonValue & j, QString & t, const QString & format)
{ Q_UNUSED(format); t = j.toString(); return qx_bool(true); } };

template <> struct QxConvert_FromJson< QVariant > {
static inline qx_bool fromJson(const QJsonValue & j, QVariant & t, const QString & format)
{ Q_UNUSED(format); t = j.toVariant(); return qx_bool(true); } };

template <> struct QxConvert_FromJson< QUuid > {
static inline qx_bool fromJson(const QJsonValue & j, QUuid & t, const QString & format)
{ Q_UNUSED(format); t = QUuid(j.toString()); return qx_bool(true); } };

template <> struct QxConvert_FromJson< qx::QxDateNeutral > {
static inline qx_bool fromJson(const QJsonValue & j, qx::QxDateNeutral & t, const QString & format)
{ Q_UNUSED(format); t = qx::QxDateNeutral::fromNeutral(j.toString()); return qx_bool(true); } };

template <> struct QxConvert_FromJson< qx::QxTimeNeutral > {
static inline qx_bool fromJson(const QJsonValue & j, qx::QxTimeNeutral & t, const QString & format)
{ Q_UNUSED(format); t = qx::QxTimeNeutral::fromNeutral(j.toString()); return qx_bool(true); } };

template <> struct QxConvert_FromJson< qx::QxDateTimeNeutral > {
static inline qx_bool fromJson(const QJsonValue & j, qx::QxDateTimeNeutral & t, const QString & format)
{ Q_UNUSED(format); t = qx::QxDateTimeNeutral::fromNeutral(j.toString()); return qx_bool(true); } };

template <> struct QxConvert_FromJson< std::string > {
static inline qx_bool fromJson(const QJsonValue & j, std::string & t, const QString & format)
#ifndef QT_NO_STL
{ Q_UNUSED(format); t = j.toString().toStdString(); return qx_bool(true); } };
#else // QT_NO_STL
{ Q_UNUSED(format); t = j.toString().toLatin1().constData(); return qx_bool(true); } };
#endif // QT_NO_STL

template <> struct QxConvert_FromJson< std::wstring > {
static inline qx_bool fromJson(const QJsonValue & j, std::wstring & t, const QString & format)
#if ((! defined(QT_NO_STL)) && (! defined(QT_NO_STL_WCHAR)))
{ Q_UNUSED(format); t = j.toString().toStdWString(); return qx_bool(true); } };
#else // ((! defined(QT_NO_STL)) && (! defined(QT_NO_STL_WCHAR)))
{ Q_UNUSED(format); Q_UNUSED(t); Q_UNUSED(j); qAssert(false); /* Need STL compatibility ! */ return qx_bool(true); } };
#endif // ((! defined(QT_NO_STL)) && (! defined(QT_NO_STL_WCHAR)))

template <> struct QxConvert_FromJson< qx_bool > {
static inline qx_bool fromJson(const QJsonValue & j, qx_bool & t, const QString & format)
{
   Q_UNUSED(format);
   t = qx_bool();
   if (j.isObject())
   {
      QJsonObject obj = j.toObject();
      t.setValue(obj["value"].toBool());
      t.setCode(static_cast<long>(qRound64(obj["code"].toDouble())));
      t.setDesc(obj["desc"].toString());
   }
   return qx_bool(true);
} };

template <typename T> struct QxConvert_FromJson< boost::optional<T> > {
static inline qx_bool fromJson(const QJsonValue & j, boost::optional<T> & t, const QString & format)
{
   if (j.isNull()) { t = boost::none; return qx_bool(true); }
   else if (! t) { t = T(); }
   return qx::cvt::from_json(j, (* t), format);
} };

} // namespace detail
} // namespace cvt
} // namespace qx

#endif // _QX_NO_JSON
