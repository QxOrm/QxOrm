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

template <> struct QxStringCvt_ToVariant< qx::trait::no_type > {
static inline QVariant toVariant(const qx::trait::no_type & t, const QString & format)
{ Q_UNUSED(t); Q_UNUSED(format); return QVariant(); } };

template <> struct QxStringCvt_ToVariant< short > {
static inline QVariant toVariant(const short & t, const QString & format)
{ Q_UNUSED(format); return QVariant(static_cast<int>(t)); } };

template <> struct QxStringCvt_ToVariant< long > {
static inline QVariant toVariant(const long & t, const QString & format)
{ Q_UNUSED(format); return QVariant(static_cast<qlonglong>(t)); } };

template <> struct QxStringCvt_ToVariant< long long > {
static inline QVariant toVariant(const long long & t, const QString & format)
{ Q_UNUSED(format); return QVariant(static_cast<qlonglong>(t)); } };

template <> struct QxStringCvt_ToVariant< unsigned short > {
static inline QVariant toVariant(const unsigned short & t, const QString & format)
{ Q_UNUSED(format); return QVariant(static_cast<unsigned int>(t)); } };

template <> struct QxStringCvt_ToVariant< unsigned long > {
static inline QVariant toVariant(const unsigned long & t, const QString & format)
{ Q_UNUSED(format); return QVariant(static_cast<qulonglong>(t)); } };

template <> struct QxStringCvt_ToVariant< unsigned long long > {
static inline QVariant toVariant(const unsigned long long & t, const QString & format)
{ Q_UNUSED(format); return QVariant(static_cast<qulonglong>(t)); } };

template <> struct QxStringCvt_ToVariant< float > {
static inline QVariant toVariant(const float & t, const QString & format)
{ Q_UNUSED(format); return QVariant(static_cast<double>(t)); } };

template <> struct QxStringCvt_ToVariant< qx_bool > {
static inline QVariant toVariant(const qx_bool & t, const QString & format)
{ Q_UNUSED(format); return (t ? QVariant(true) : QVariant(false)); } };

template <> struct QxStringCvt_ToVariant< std::string > {
static inline QVariant toVariant(const std::string & t, const QString & format)
{ Q_UNUSED(format); return QString::fromStdString(t); } };

template <> struct QxStringCvt_ToVariant< std::wstring > {
static inline QVariant toVariant(const std::wstring & t, const QString & format)
{ Q_UNUSED(format); return QString::fromStdWString(t); } };

} // namespace detail
} // namespace cvt
} // namespace qx
