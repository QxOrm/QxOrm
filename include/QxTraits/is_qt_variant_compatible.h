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

#ifndef _QX_IS_QT_VARIANT_COMPATIBLE_H_
#define _QX_IS_QT_VARIANT_COMPATIBLE_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file is_qt_variant_compatible.h
 * \author Lionel Marty
 * \ingroup QxTraits
 * \brief qx::trait::is_qt_variant_compatible<T>::value : return true if T can be host into a QVariant object of Qt library, otherwise return false
 */

#include <boost/type_traits/is_enum.hpp>

#include <QtCore/qvariant.h>

namespace qx {
namespace trait {

/*!
 * \ingroup QxTraits
 * \brief qx::trait::is_qt_variant_compatible<T>::value : return true if T can be host into a QVariant object of Qt library, otherwise return false
 */
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
template <> struct is_qt_variant_compatible<QVariant>             { enum { value = true }; };

template <> struct is_qt_variant_compatible< QList<QVariant> >             { enum { value = true }; };
template <> struct is_qt_variant_compatible< QMap<QString, QVariant> >     { enum { value = true }; };
template <> struct is_qt_variant_compatible< QHash<QString, QVariant> >    { enum { value = true }; };

} // namespace trait
} // namespace qx

#endif // _QX_IS_QT_VARIANT_COMPATIBLE_H_
