/****************************************************************************
**
** https://www.qxorm.com/
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

#ifndef _QX_CONSTRUCT_NULL_QVARIANT_H_
#define _QX_CONSTRUCT_NULL_QVARIANT_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file construct_null_qvariant.h
 * \author Lionel Marty
 * \ingroup QxTraits
 * \brief qx::trait::construct_null_qvariant<T>::get() : create a NULL QVariant which matches QVariant::Type with type T
 */

#include <QtCore/qvariant.h>

#include <QxDao/QxDateNeutral.h>
#include <QxDao/QxTimeNeutral.h>
#include <QxDao/QxDateTimeNeutral.h>

namespace qx {
namespace trait {

/*!
 * \ingroup QxTraits
 * \brief qx::trait::construct_null_qvariant<T>::get() : create a NULL QVariant which matches QVariant::Type with type T
 */
template <typename T>
struct construct_null_qvariant { static inline QVariant get() { return QVariant(); } };

template <> struct construct_null_qvariant<QBitArray> { static inline QVariant get() { return QVariant(QVariant::BitArray); } };
template <> struct construct_null_qvariant<QBitArray &> { static inline QVariant get() { return QVariant(QVariant::BitArray); } };
template <> struct construct_null_qvariant<const QBitArray> { static inline QVariant get() { return QVariant(QVariant::BitArray); } };
template <> struct construct_null_qvariant<const QBitArray &> { static inline QVariant get() { return QVariant(QVariant::BitArray); } };

template <> struct construct_null_qvariant<QByteArray> { static inline QVariant get() { return QVariant(QVariant::ByteArray); } };
template <> struct construct_null_qvariant<QByteArray &> { static inline QVariant get() { return QVariant(QVariant::ByteArray); } };
template <> struct construct_null_qvariant<const QByteArray> { static inline QVariant get() { return QVariant(QVariant::ByteArray); } };
template <> struct construct_null_qvariant<const QByteArray &> { static inline QVariant get() { return QVariant(QVariant::ByteArray); } };

template <> struct construct_null_qvariant<bool> { static inline QVariant get() { return QVariant(QVariant::Bool); } };
template <> struct construct_null_qvariant<bool &> { static inline QVariant get() { return QVariant(QVariant::Bool); } };
template <> struct construct_null_qvariant<const bool> { static inline QVariant get() { return QVariant(QVariant::Bool); } };
template <> struct construct_null_qvariant<const bool &> { static inline QVariant get() { return QVariant(QVariant::Bool); } };

template <> struct construct_null_qvariant<short> { static inline QVariant get() { return QVariant(QVariant::Int); } };
template <> struct construct_null_qvariant<short &> { static inline QVariant get() { return QVariant(QVariant::Int); } };
template <> struct construct_null_qvariant<const short> { static inline QVariant get() { return QVariant(QVariant::Int); } };
template <> struct construct_null_qvariant<const short &> { static inline QVariant get() { return QVariant(QVariant::Int); } };

template <> struct construct_null_qvariant<int> { static inline QVariant get() { return QVariant(QVariant::Int); } };
template <> struct construct_null_qvariant<int &> { static inline QVariant get() { return QVariant(QVariant::Int); } };
template <> struct construct_null_qvariant<const int> { static inline QVariant get() { return QVariant(QVariant::Int); } };
template <> struct construct_null_qvariant<const int &> { static inline QVariant get() { return QVariant(QVariant::Int); } };

template <> struct construct_null_qvariant<long> { static inline QVariant get() { return QVariant(QVariant::LongLong); } };
template <> struct construct_null_qvariant<long &> { static inline QVariant get() { return QVariant(QVariant::LongLong); } };
template <> struct construct_null_qvariant<const long> { static inline QVariant get() { return QVariant(QVariant::LongLong); } };
template <> struct construct_null_qvariant<const long &> { static inline QVariant get() { return QVariant(QVariant::LongLong); } };

template <> struct construct_null_qvariant<long long> { static inline QVariant get() { return QVariant(QVariant::LongLong); } };
template <> struct construct_null_qvariant<long long &> { static inline QVariant get() { return QVariant(QVariant::LongLong); } };
template <> struct construct_null_qvariant<const long long> { static inline QVariant get() { return QVariant(QVariant::LongLong); } };
template <> struct construct_null_qvariant<const long long &> { static inline QVariant get() { return QVariant(QVariant::LongLong); } };

template <> struct construct_null_qvariant<float> { static inline QVariant get() { return QVariant(QVariant::Double); } };
template <> struct construct_null_qvariant<float &> { static inline QVariant get() { return QVariant(QVariant::Double); } };
template <> struct construct_null_qvariant<const float> { static inline QVariant get() { return QVariant(QVariant::Double); } };
template <> struct construct_null_qvariant<const float &> { static inline QVariant get() { return QVariant(QVariant::Double); } };

template <> struct construct_null_qvariant<double> { static inline QVariant get() { return QVariant(QVariant::Double); } };
template <> struct construct_null_qvariant<double &> { static inline QVariant get() { return QVariant(QVariant::Double); } };
template <> struct construct_null_qvariant<const double> { static inline QVariant get() { return QVariant(QVariant::Double); } };
template <> struct construct_null_qvariant<const double &> { static inline QVariant get() { return QVariant(QVariant::Double); } };

template <> struct construct_null_qvariant<unsigned short> { static inline QVariant get() { return QVariant(QVariant::UInt); } };
template <> struct construct_null_qvariant<unsigned short &> { static inline QVariant get() { return QVariant(QVariant::UInt); } };
template <> struct construct_null_qvariant<const unsigned short> { static inline QVariant get() { return QVariant(QVariant::UInt); } };
template <> struct construct_null_qvariant<const unsigned short &> { static inline QVariant get() { return QVariant(QVariant::UInt); } };

template <> struct construct_null_qvariant<unsigned int> { static inline QVariant get() { return QVariant(QVariant::UInt); } };
template <> struct construct_null_qvariant<unsigned int &> { static inline QVariant get() { return QVariant(QVariant::UInt); } };
template <> struct construct_null_qvariant<const unsigned int> { static inline QVariant get() { return QVariant(QVariant::UInt); } };
template <> struct construct_null_qvariant<const unsigned int &> { static inline QVariant get() { return QVariant(QVariant::UInt); } };

template <> struct construct_null_qvariant<unsigned long> { static inline QVariant get() { return QVariant(QVariant::ULongLong); } };
template <> struct construct_null_qvariant<unsigned long &> { static inline QVariant get() { return QVariant(QVariant::ULongLong); } };
template <> struct construct_null_qvariant<const unsigned long> { static inline QVariant get() { return QVariant(QVariant::ULongLong); } };
template <> struct construct_null_qvariant<const unsigned long &> { static inline QVariant get() { return QVariant(QVariant::ULongLong); } };

template <> struct construct_null_qvariant<unsigned long long> { static inline QVariant get() { return QVariant(QVariant::ULongLong); } };
template <> struct construct_null_qvariant<unsigned long long &> { static inline QVariant get() { return QVariant(QVariant::ULongLong); } };
template <> struct construct_null_qvariant<const unsigned long long> { static inline QVariant get() { return QVariant(QVariant::ULongLong); } };
template <> struct construct_null_qvariant<const unsigned long long &> { static inline QVariant get() { return QVariant(QVariant::ULongLong); } };

template <> struct construct_null_qvariant<QString> { static inline QVariant get() { return QVariant(QVariant::String); } };
template <> struct construct_null_qvariant<QString &> { static inline QVariant get() { return QVariant(QVariant::String); } };
template <> struct construct_null_qvariant<const QString> { static inline QVariant get() { return QVariant(QVariant::String); } };
template <> struct construct_null_qvariant<const QString &> { static inline QVariant get() { return QVariant(QVariant::String); } };

template <> struct construct_null_qvariant<QStringList> { static inline QVariant get() { return QVariant(QVariant::StringList); } };
template <> struct construct_null_qvariant<QStringList &> { static inline QVariant get() { return QVariant(QVariant::StringList); } };
template <> struct construct_null_qvariant<const QStringList> { static inline QVariant get() { return QVariant(QVariant::StringList); } };
template <> struct construct_null_qvariant<const QStringList &> { static inline QVariant get() { return QVariant(QVariant::StringList); } };

template <> struct construct_null_qvariant<QDate> { static inline QVariant get() { return QVariant(QVariant::Date); } };
template <> struct construct_null_qvariant<QDate &> { static inline QVariant get() { return QVariant(QVariant::Date); } };
template <> struct construct_null_qvariant<const QDate> { static inline QVariant get() { return QVariant(QVariant::Date); } };
template <> struct construct_null_qvariant<const QDate &> { static inline QVariant get() { return QVariant(QVariant::Date); } };

template <> struct construct_null_qvariant<QDateTime> { static inline QVariant get() { return QVariant(QVariant::DateTime); } };
template <> struct construct_null_qvariant<QDateTime &> { static inline QVariant get() { return QVariant(QVariant::DateTime); } };
template <> struct construct_null_qvariant<const QDateTime> { static inline QVariant get() { return QVariant(QVariant::DateTime); } };
template <> struct construct_null_qvariant<const QDateTime &> { static inline QVariant get() { return QVariant(QVariant::DateTime); } };

template <> struct construct_null_qvariant<QTime> { static inline QVariant get() { return QVariant(QVariant::Time); } };
template <> struct construct_null_qvariant<QTime &> { static inline QVariant get() { return QVariant(QVariant::Time); } };
template <> struct construct_null_qvariant<const QTime> { static inline QVariant get() { return QVariant(QVariant::Time); } };
template <> struct construct_null_qvariant<const QTime &> { static inline QVariant get() { return QVariant(QVariant::Time); } };

template <> struct construct_null_qvariant<QUuid> { static inline QVariant get() { return QVariant(QVariant::String); } };
template <> struct construct_null_qvariant<QUuid &> { static inline QVariant get() { return QVariant(QVariant::String); } };
template <> struct construct_null_qvariant<const QUuid> { static inline QVariant get() { return QVariant(QVariant::String); } };
template <> struct construct_null_qvariant<const QUuid &> { static inline QVariant get() { return QVariant(QVariant::String); } };

template <> struct construct_null_qvariant<qx::QxDateNeutral> { static inline QVariant get() { return QVariant(QVariant::String); } };
template <> struct construct_null_qvariant<qx::QxDateNeutral &> { static inline QVariant get() { return QVariant(QVariant::String); } };
template <> struct construct_null_qvariant<const qx::QxDateNeutral> { static inline QVariant get() { return QVariant(QVariant::String); } };
template <> struct construct_null_qvariant<const qx::QxDateNeutral &> { static inline QVariant get() { return QVariant(QVariant::String); } };

template <> struct construct_null_qvariant<qx::QxTimeNeutral> { static inline QVariant get() { return QVariant(QVariant::String); } };
template <> struct construct_null_qvariant<qx::QxTimeNeutral &> { static inline QVariant get() { return QVariant(QVariant::String); } };
template <> struct construct_null_qvariant<const qx::QxTimeNeutral> { static inline QVariant get() { return QVariant(QVariant::String); } };
template <> struct construct_null_qvariant<const qx::QxTimeNeutral &> { static inline QVariant get() { return QVariant(QVariant::String); } };

template <> struct construct_null_qvariant<qx::QxDateTimeNeutral> { static inline QVariant get() { return QVariant(QVariant::String); } };
template <> struct construct_null_qvariant<qx::QxDateTimeNeutral &> { static inline QVariant get() { return QVariant(QVariant::String); } };
template <> struct construct_null_qvariant<const qx::QxDateTimeNeutral> { static inline QVariant get() { return QVariant(QVariant::String); } };
template <> struct construct_null_qvariant<const qx::QxDateTimeNeutral &> { static inline QVariant get() { return QVariant(QVariant::String); } };

template <> struct construct_null_qvariant<std::string> { static inline QVariant get() { return QVariant(QVariant::String); } };
template <> struct construct_null_qvariant<std::string &> { static inline QVariant get() { return QVariant(QVariant::String); } };
template <> struct construct_null_qvariant<const std::string> { static inline QVariant get() { return QVariant(QVariant::String); } };
template <> struct construct_null_qvariant<const std::string &> { static inline QVariant get() { return QVariant(QVariant::String); } };

template <> struct construct_null_qvariant<std::wstring> { static inline QVariant get() { return QVariant(QVariant::String); } };
template <> struct construct_null_qvariant<std::wstring &> { static inline QVariant get() { return QVariant(QVariant::String); } };
template <> struct construct_null_qvariant<const std::wstring> { static inline QVariant get() { return QVariant(QVariant::String); } };
template <> struct construct_null_qvariant<const std::wstring &> { static inline QVariant get() { return QVariant(QVariant::String); } };

#ifdef _QX_ENABLE_QT_GUI

template <> struct construct_null_qvariant<QBrush> { static inline QVariant get() { return QVariant(QVariant::Brush); } };
template <> struct construct_null_qvariant<QBrush &> { static inline QVariant get() { return QVariant(QVariant::Brush); } };
template <> struct construct_null_qvariant<const QBrush> { static inline QVariant get() { return QVariant(QVariant::Brush); } };
template <> struct construct_null_qvariant<const QBrush &> { static inline QVariant get() { return QVariant(QVariant::Brush); } };

template <> struct construct_null_qvariant<QColor> { static inline QVariant get() { return QVariant(QVariant::Color); } };
template <> struct construct_null_qvariant<QColor &> { static inline QVariant get() { return QVariant(QVariant::Color); } };
template <> struct construct_null_qvariant<const QColor> { static inline QVariant get() { return QVariant(QVariant::Color); } };
template <> struct construct_null_qvariant<const QColor &> { static inline QVariant get() { return QVariant(QVariant::Color); } };

template <> struct construct_null_qvariant<QFont> { static inline QVariant get() { return QVariant(QVariant::Font); } };
template <> struct construct_null_qvariant<QFont &> { static inline QVariant get() { return QVariant(QVariant::Font); } };
template <> struct construct_null_qvariant<const QFont> { static inline QVariant get() { return QVariant(QVariant::Font); } };
template <> struct construct_null_qvariant<const QFont &> { static inline QVariant get() { return QVariant(QVariant::Font); } };

#if (QT_VERSION < 0x060000)
template <> struct construct_null_qvariant<QMatrix> { static inline QVariant get() { return QVariant(QVariant::Matrix); } };
template <> struct construct_null_qvariant<QMatrix &> { static inline QVariant get() { return QVariant(QVariant::Matrix); } };
template <> struct construct_null_qvariant<const QMatrix> { static inline QVariant get() { return QVariant(QVariant::Matrix); } };
template <> struct construct_null_qvariant<const QMatrix &> { static inline QVariant get() { return QVariant(QVariant::Matrix); } };
#endif // (QT_VERSION < 0x060000)

template <> struct construct_null_qvariant<QRegion> { static inline QVariant get() { return QVariant(QVariant::Region); } };
template <> struct construct_null_qvariant<QRegion &> { static inline QVariant get() { return QVariant(QVariant::Region); } };
template <> struct construct_null_qvariant<const QRegion> { static inline QVariant get() { return QVariant(QVariant::Region); } };
template <> struct construct_null_qvariant<const QRegion &> { static inline QVariant get() { return QVariant(QVariant::Region); } };

template <> struct construct_null_qvariant<QImage> { static inline QVariant get() { return QVariant(QVariant::Image); } };
template <> struct construct_null_qvariant<QImage &> { static inline QVariant get() { return QVariant(QVariant::Image); } };
template <> struct construct_null_qvariant<const QImage> { static inline QVariant get() { return QVariant(QVariant::Image); } };
template <> struct construct_null_qvariant<const QImage &> { static inline QVariant get() { return QVariant(QVariant::Image); } };

template <> struct construct_null_qvariant<QPixmap> { static inline QVariant get() { return QVariant(QVariant::Pixmap); } };
template <> struct construct_null_qvariant<QPixmap &> { static inline QVariant get() { return QVariant(QVariant::Pixmap); } };
template <> struct construct_null_qvariant<const QPixmap> { static inline QVariant get() { return QVariant(QVariant::Pixmap); } };
template <> struct construct_null_qvariant<const QPixmap &> { static inline QVariant get() { return QVariant(QVariant::Pixmap); } };

#endif // _QX_ENABLE_QT_GUI

} // namespace trait
} // namespace qx

#endif // _QX_CONSTRUCT_NULL_QVARIANT_H_
