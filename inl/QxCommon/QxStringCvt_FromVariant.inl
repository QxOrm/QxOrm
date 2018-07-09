/****************************************************************************
**
** Copyright (C) 2010 QxOrm France and/or its subsidiary(-ies)
** Contact: QxOrm France Information (contact@qxorm.com)
**
** This file is part of the QxOrm library
**
** Commercial Usage
** Licensees holding valid QxOrm Commercial licenses may use this file in
** accordance with the QxOrm Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and QxOrm France
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file 'license.gpl3.txt' included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html
**
** If you are unsure which license is appropriate for your use, please
** contact the support department at support@qxorm.com
**
****************************************************************************/

namespace qx {
namespace cvt {
namespace detail {

template <> struct QxStringCvt_FromVariant< qx::trait::no_type > {
static inline qx_bool fromVariant(const QVariant & v, qx::trait::no_type & t, const QString & format)
{ Q_UNUSED(v); Q_UNUSED(t); Q_UNUSED(format); return qx_bool(true); } };

template <> struct QxStringCvt_FromVariant< bool > {
static inline qx_bool fromVariant(const QVariant & v, bool & t, const QString & format)
{ Q_UNUSED(format); t = v.toBool(); return qx_bool(true); } };

template <> struct QxStringCvt_FromVariant< short > {
static inline qx_bool fromVariant(const QVariant & v, short & t, const QString & format)
{ Q_UNUSED(format); bool bOk = false; t = static_cast<short>(v.toInt(& bOk)); return bOk; } };

template <> struct QxStringCvt_FromVariant< int > {
static inline qx_bool fromVariant(const QVariant & v, int & t, const QString & format)
{ Q_UNUSED(format); bool bOk = false; t = v.toInt(& bOk); return bOk; } };

template <> struct QxStringCvt_FromVariant< long > {
static inline qx_bool fromVariant(const QVariant & v, long & t, const QString & format)
{ Q_UNUSED(format); bool bOk = false; t = static_cast<long>(v.toLongLong(& bOk)); return bOk; } };

template <> struct QxStringCvt_FromVariant< long long > {
static inline qx_bool fromVariant(const QVariant & v, long long & t, const QString & format)
{ Q_UNUSED(format); bool bOk = false; t = static_cast<long long>(v.toLongLong(& bOk)); return bOk; } };

template <> struct QxStringCvt_FromVariant< float > {
static inline qx_bool fromVariant(const QVariant & v, float & t, const QString & format)
{ Q_UNUSED(format); bool bOk = false; t = static_cast<float>(v.toDouble(& bOk)); return bOk; } };

template <> struct QxStringCvt_FromVariant< double > {
static inline qx_bool fromVariant(const QVariant & v, double & t, const QString & format)
{ Q_UNUSED(format); bool bOk = false; t = v.toDouble(& bOk); return bOk; } };

template <> struct QxStringCvt_FromVariant< unsigned short > {
static inline qx_bool fromVariant(const QVariant & v, unsigned short & t, const QString & format)
{ Q_UNUSED(format); bool bOk = false; t = static_cast<unsigned short>(v.toUInt(& bOk)); return bOk; } };

template <> struct QxStringCvt_FromVariant< unsigned int > {
static inline qx_bool fromVariant(const QVariant & v, unsigned int & t, const QString & format)
{ Q_UNUSED(format); bool bOk = false; t = static_cast<unsigned int>(v.toUInt(& bOk)); return bOk; } };

template <> struct QxStringCvt_FromVariant< unsigned long > {
static inline qx_bool fromVariant(const QVariant & v, unsigned long & t, const QString & format)
{ Q_UNUSED(format); bool bOk = false; t = static_cast<unsigned long>(v.toULongLong(& bOk)); return bOk; } };

template <> struct QxStringCvt_FromVariant< unsigned long long > {
static inline qx_bool fromVariant(const QVariant & v, unsigned long long & t, const QString & format)
{ Q_UNUSED(format); bool bOk = false; t = static_cast<unsigned long long>(v.toULongLong(& bOk)); return bOk; } };

template <> struct QxStringCvt_FromVariant< QDate > {
static inline qx_bool fromVariant(const QVariant & v, QDate & t, const QString & format)
{ Q_UNUSED(format); t = v.toDate(); return t.isValid(); } };

template <> struct QxStringCvt_FromVariant< QTime > {
static inline qx_bool fromVariant(const QVariant & v, QTime & t, const QString & format)
{ Q_UNUSED(format); t = v.toTime(); return t.isValid(); } };

template <> struct QxStringCvt_FromVariant< QDateTime > {
static inline qx_bool fromVariant(const QVariant & v, QDateTime & t, const QString & format)
{ Q_UNUSED(format); t = v.toDateTime(); return t.isValid(); } };

template <> struct QxStringCvt_FromVariant< QByteArray > {
static inline qx_bool fromVariant(const QVariant & v, QByteArray & t, const QString & format)
{ Q_UNUSED(format); t = v.toByteArray(); return qx_bool(true); } };

template <> struct QxStringCvt_FromVariant< QString > {
static inline qx_bool fromVariant(const QVariant & v, QString & t, const QString & format)
{ Q_UNUSED(format); t = v.toString(); return qx_bool(true); } };

template <> struct QxStringCvt_FromVariant< std::string > {
static inline qx_bool fromVariant(const QVariant & v, std::string & t, const QString & format)
{ Q_UNUSED(format); t = v.toString().toStdString(); return qx_bool(true); } };

template <> struct QxStringCvt_FromVariant< std::wstring > {
static inline qx_bool fromVariant(const QVariant & v, std::wstring & t, const QString & format)
{ Q_UNUSED(format); t = v.toString().toStdWString(); return qx_bool(true); } };

template <> struct QxStringCvt_FromVariant< qx_bool > {
static inline qx_bool fromVariant(const QVariant & v, qx_bool & t, const QString & format)
{ Q_UNUSED(format); t = qx_bool(v.toBool()); return qx_bool(true); } };

} // namespace detail
} // namespace cvt
} // namespace qx
