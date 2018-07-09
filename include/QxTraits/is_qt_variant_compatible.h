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

#ifndef _QX_IS_QT_VARIANT_COMPATIBLE_H_
#define _QX_IS_QT_VARIANT_COMPATIBLE_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/type_traits/is_enum.hpp>

#include <QtCore/qvariant.h>

namespace qx {
namespace trait {

template <typename T>
struct is_qt_variant_compatible
{ enum { value = boost::is_enum<T>::value }; };

template <> struct is_qt_variant_compatible<bool>                 { enum { value = true }; };
template <> struct is_qt_variant_compatible<short>                { enum { value = true }; };
template <> struct is_qt_variant_compatible<int>                  { enum { value = true }; };
template <> struct is_qt_variant_compatible<long>                 { enum { value = true }; };
template <> struct is_qt_variant_compatible<long long>            { enum { value = true }; };
template <> struct is_qt_variant_compatible<float>                { enum { value = true }; };
template <> struct is_qt_variant_compatible<double>               { enum { value = true }; };
template <> struct is_qt_variant_compatible<long double>          { enum { value = true }; };
template <> struct is_qt_variant_compatible<unsigned short>       { enum { value = true }; };
template <> struct is_qt_variant_compatible<unsigned int>         { enum { value = true }; };
template <> struct is_qt_variant_compatible<unsigned long>        { enum { value = true }; };
template <> struct is_qt_variant_compatible<unsigned long long>   { enum { value = true }; };
template <> struct is_qt_variant_compatible<QString>              { enum { value = true }; };
template <> struct is_qt_variant_compatible<QDate>                { enum { value = true }; };
template <> struct is_qt_variant_compatible<QTime>                { enum { value = true }; };
template <> struct is_qt_variant_compatible<QDateTime>            { enum { value = true }; };
template <> struct is_qt_variant_compatible<QBitArray>            { enum { value = true }; };
template <> struct is_qt_variant_compatible<QByteArray>           { enum { value = true }; };
template <> struct is_qt_variant_compatible<QLatin1String>        { enum { value = true }; };
template <> struct is_qt_variant_compatible<QStringList>          { enum { value = true }; };
template <> struct is_qt_variant_compatible<QChar>                { enum { value = true }; };
template <> struct is_qt_variant_compatible<QRegExp>              { enum { value = true }; };
template <> struct is_qt_variant_compatible<QLocale>              { enum { value = true }; };
template <> struct is_qt_variant_compatible<QSize>                { enum { value = true }; };
template <> struct is_qt_variant_compatible<QSizeF>               { enum { value = true }; };
template <> struct is_qt_variant_compatible<QPoint>               { enum { value = true }; };
template <> struct is_qt_variant_compatible<QPointF>              { enum { value = true }; };
template <> struct is_qt_variant_compatible<QLine>                { enum { value = true }; };
template <> struct is_qt_variant_compatible<QLineF>               { enum { value = true }; };
template <> struct is_qt_variant_compatible<QRect>                { enum { value = true }; };
template <> struct is_qt_variant_compatible<QRectF>               { enum { value = true }; };
template <> struct is_qt_variant_compatible<QUrl>                 { enum { value = true }; };

template <> struct is_qt_variant_compatible< QList<QVariant> >             { enum { value = true }; };
template <> struct is_qt_variant_compatible< QMap<QString, QVariant> >     { enum { value = true }; };
template <> struct is_qt_variant_compatible< QHash<QString, QVariant> >    { enum { value = true }; };

} // namespace trait
} // namespace qx

#endif // _QX_IS_QT_VARIANT_COMPATIBLE_H_
