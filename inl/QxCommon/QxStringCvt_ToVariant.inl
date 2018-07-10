/****************************************************************************
**
** http://www.qxorm.com/
** http://sourceforge.net/projects/qxorm/
** Original file by Lionel Marty
**
** This file is part of the QxOrm library
**
** This software is provided 'as-is', without any express or implied
** warranty. In no event will the authors be held liable for any
** damages arising from the use of this software.
**
** GNU Lesser General Public License Usage
** This file must be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file 'license.lgpl.txt' included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you have questions regarding the use of this file, please contact :
** contact@qxorm.com
**
****************************************************************************/

namespace qx {
namespace cvt {
namespace detail {

template <> struct QxStringCvt_ToVariant< qx::trait::no_type > {
static inline QVariant toVariant(const qx::trait::no_type & t, const QString & format, int index)
{ Q_UNUSED(t); Q_UNUSED(format); Q_UNUSED(index); return QVariant(); } };

template <> struct QxStringCvt_ToVariant< short > {
static inline QVariant toVariant(const short & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QVariant(static_cast<int>(t)); } };

template <> struct QxStringCvt_ToVariant< long > {
static inline QVariant toVariant(const long & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QVariant(static_cast<qlonglong>(t)); } };

template <> struct QxStringCvt_ToVariant< long long > {
static inline QVariant toVariant(const long long & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QVariant(static_cast<qlonglong>(t)); } };

template <> struct QxStringCvt_ToVariant< unsigned short > {
static inline QVariant toVariant(const unsigned short & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QVariant(static_cast<unsigned int>(t)); } };

template <> struct QxStringCvt_ToVariant< unsigned long > {
static inline QVariant toVariant(const unsigned long & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QVariant(static_cast<qulonglong>(t)); } };

template <> struct QxStringCvt_ToVariant< unsigned long long > {
static inline QVariant toVariant(const unsigned long long & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QVariant(static_cast<qulonglong>(t)); } };

template <> struct QxStringCvt_ToVariant< float > {
static inline QVariant toVariant(const float & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QVariant(static_cast<double>(t)); } };

template <> struct QxStringCvt_ToVariant< qx_bool > {
static inline QVariant toVariant(const qx_bool & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return (t ? QVariant(true) : QVariant(false)); } };

template <> struct QxStringCvt_ToVariant< qx::QxDateNeutral > {
static inline QVariant toVariant(const qx::QxDateNeutral & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QVariant(t.toNeutral()); } };

template <> struct QxStringCvt_ToVariant< qx::QxTimeNeutral > {
static inline QVariant toVariant(const qx::QxTimeNeutral & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QVariant(t.toNeutral()); } };

template <> struct QxStringCvt_ToVariant< qx::QxDateTimeNeutral > {
static inline QVariant toVariant(const qx::QxDateTimeNeutral & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QVariant(t.toNeutral()); } };

template <> struct QxStringCvt_ToVariant< std::string > {
static inline QVariant toVariant(const std::string & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QString::fromStdString(t); } };

template <> struct QxStringCvt_ToVariant< std::wstring > {
static inline QVariant toVariant(const std::wstring & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return QString::fromStdWString(t); } };

template <> struct QxStringCvt_ToVariant< QVariant > {
static inline QVariant toVariant(const QVariant & t, const QString & format, int index)
{ Q_UNUSED(format); Q_UNUSED(index); return t; } };

template <typename T> struct QxStringCvt_ToVariant< boost::optional<T> > {
static inline QVariant toVariant(const boost::optional<T> & t, const QString & format, int index)
{ if (t) { return qx::cvt::to_variant((* t), format, index); }; return QVariant(); } };

} // namespace detail
} // namespace cvt
} // namespace qx
