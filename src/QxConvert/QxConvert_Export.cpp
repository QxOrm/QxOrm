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

#include <QxPrecompiled.h>

#if _QX_USE_QX_CONVERT_EXPORT

#include <QxOrm.h>

#include <QxConvert/QxConvert_Export.h>

#include <QxMemLeak/mem_leak.h>

QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, qx::trait::no_type)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, QString)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, QDate)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, QTime)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, QDateTime)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, QByteArray)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, QVariant)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, qx_bool)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, bool)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, char)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, short)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, int)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, long)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, long long)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, float)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, double)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, unsigned short)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, unsigned int)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, unsigned long)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, unsigned long long)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, std::string)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, std::wstring)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, QBrush)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, QColor)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, QFont)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, QMatrix)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, QObject)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, QPoint)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, QRect)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, QRegExp)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, QRegion)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, QSize)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, QStringList)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, QUrl)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, QImage)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, QPicture)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, QPixmap)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, QUuid)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, qx::QxDateNeutral)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, qx::QxTimeNeutral)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToString, qx::QxDateTimeNeutral)

QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, qx::trait::no_type)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, QString)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, QDate)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, QTime)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, QDateTime)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, QByteArray)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, QVariant)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, qx_bool)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, bool)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, char)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, short)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, int)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, long)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, long long)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, float)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, double)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, unsigned short)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, unsigned int)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, unsigned long)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, unsigned long long)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, std::string)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, std::wstring)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, QBrush)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, QColor)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, QFont)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, QMatrix)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, QObject)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, QPoint)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, QRect)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, QRegExp)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, QRegion)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, QSize)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, QStringList)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, QUrl)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, QImage)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, QPicture)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, QPixmap)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, QUuid)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, qx::QxDateNeutral)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, qx::QxTimeNeutral)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromString, qx::QxDateTimeNeutral)

QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, qx::trait::no_type)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, QString)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, QDate)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, QTime)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, QDateTime)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, QByteArray)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, QVariant)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, qx_bool)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, bool)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, char)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, short)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, int)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, long)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, long long)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, float)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, double)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, unsigned short)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, unsigned int)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, unsigned long)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, unsigned long long)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, std::string)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, std::wstring)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, QBrush)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, QColor)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, QFont)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, QMatrix)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, QObject)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, QPoint)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, QRect)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, QRegExp)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, QRegion)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, QSize)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, QStringList)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, QUrl)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, QImage)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, QPicture)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, QPixmap)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, QUuid)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, qx::QxDateNeutral)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, qx::QxTimeNeutral)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_ToVariant, qx::QxDateTimeNeutral)

QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, qx::trait::no_type)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, QString)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, QDate)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, QTime)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, QDateTime)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, QByteArray)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, QVariant)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, qx_bool)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, bool)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, char)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, short)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, int)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, long)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, long long)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, float)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, double)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, unsigned short)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, unsigned int)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, unsigned long)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, unsigned long long)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, std::string)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, std::wstring)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, QBrush)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, QColor)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, QFont)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, QMatrix)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, QObject)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, QPoint)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, QRect)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, QRegExp)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, QRegion)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, QSize)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, QStringList)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, QUrl)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, QImage)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, QPicture)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, QPixmap)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, QUuid)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, qx::QxDateNeutral)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, qx::QxTimeNeutral)
QX_DLL_EXPORT_TEMPLATE_T_P1_CPP(struct, qx::cvt::detail::QxConvert_FromVariant, qx::QxDateTimeNeutral)

#endif // _QX_USE_QX_CONVERT_EXPORT
