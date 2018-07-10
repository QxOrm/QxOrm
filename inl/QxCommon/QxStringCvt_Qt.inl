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

#ifndef _QX_STRING_CVT_QT_H_
#define _QX_STRING_CVT_QT_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QxCommon/QxStringCvt.h>
#include <QxCommon/QxStringCvt_Impl.h>

QX_STR_CVT_BY_USING_ARCHIVE_IMPL(QObject)
QX_STR_CVT_BY_USING_ARCHIVE_IMPL(QPoint)
QX_STR_CVT_BY_USING_ARCHIVE_IMPL(QRect)
QX_STR_CVT_BY_USING_ARCHIVE_IMPL(QRegExp)
QX_STR_CVT_BY_USING_ARCHIVE_IMPL(QSize)
QX_STR_CVT_BY_USING_ARCHIVE_IMPL(QStringList)
QX_STR_CVT_BY_USING_ARCHIVE_IMPL(QUrl)
QX_STR_CVT_BY_USING_ARCHIVE_IMPL(QSqlError)

#if _QX_ENABLE_QT_GUI_DEPENDENCY
QX_STR_CVT_BY_USING_ARCHIVE_IMPL(QBrush)
QX_STR_CVT_BY_USING_ARCHIVE_IMPL(QColor)
QX_STR_CVT_BY_USING_ARCHIVE_IMPL(QFont)
QX_STR_CVT_BY_USING_ARCHIVE_IMPL(QMatrix)
QX_STR_CVT_BY_USING_ARCHIVE_IMPL(QRegion)
QX_STR_CVT_BY_USING_ARCHIVE_IMPL(QImage)
QX_STR_CVT_BY_USING_ARCHIVE_IMPL(QPicture)
QX_STR_CVT_BY_USING_ARCHIVE_IMPL(QPixmap)
#endif // _QX_ENABLE_QT_GUI_DEPENDENCY

QX_STR_CVT_BY_USING_ARCHIVE_IMPL(qx::QxSqlQuery)
QX_STR_CVT_BY_USING_ARCHIVE_IMPL(qx::QxInvalidValue)
QX_STR_CVT_BY_USING_ARCHIVE_IMPL(qx::QxInvalidValueX)

#endif // _QX_STRING_CVT_QT_H_
