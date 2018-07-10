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

#endif // _QX_STRING_CVT_QT_H_
