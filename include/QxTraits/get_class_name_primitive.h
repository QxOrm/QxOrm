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

#ifndef _QX_GET_CLASS_NAME_PRIMITIVE_H_
#define _QX_GET_CLASS_NAME_PRIMITIVE_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file get_class_name_primitive.h
 * \author Lionel Marty
 * \ingroup QxTraits
 * \brief Register all primitive and useful types of stl, boost and Qt libraries using QX_REGISTER_CLASS_NAME(T) macro
 */

#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>

#include <QtCore/qglobal.h>
#include <QtCore/qobject.h>
#include <QtCore/qstring.h>
#include <QtCore/qstringlist.h>
#include <QtCore/qvector.h>
#include <QtCore/qlist.h>
#include <QtCore/qmap.h>
#include <QtCore/qset.h>
#include <QtCore/qhash.h>
#include <QtCore/qdatetime.h>
#include <QtCore/qvariant.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qlinkedlist.h>
#include <QtCore/qpair.h>
#include <QtCore/qpoint.h>
#include <QtCore/qrect.h>
#include <QtCore/qregexp.h>
#include <QtCore/qsharedpointer.h>
#include <QtCore/qsize.h>
#include <QtCore/qurl.h>
#include <QtCore/quuid.h>
#include <QtCore/QWeakPointer>

#include <QtSql/qsqlerror.h>

#ifdef _QX_ENABLE_QT_GUI
#include <QtGui/qcolor.h>
#include <QtGui/qfont.h>
#include <QtGui/qimage.h>
#include <QtGui/qbrush.h>
#include <QtGui/qmatrix.h>
#include <QtGui/qpicture.h>
#include <QtGui/qpixmap.h>
#include <QtGui/qregion.h>
#endif // _QX_ENABLE_QT_GUI

#if (QT_VERSION >= 0x040600)
#include <QtCore/qscopedpointer.h>
#endif // (QT_VERSION >= 0x040600)

#include <QxDao/QxDaoPointer.h>

#include <QxTraits/get_class_name.h>

QX_REGISTER_CLASS_NAME(void)
QX_REGISTER_CLASS_NAME(bool)
QX_REGISTER_CLASS_NAME(int)
QX_REGISTER_CLASS_NAME(short)
QX_REGISTER_CLASS_NAME(long)
QX_REGISTER_CLASS_NAME(float)
QX_REGISTER_CLASS_NAME(double)
QX_REGISTER_CLASS_NAME(long double)
QX_REGISTER_CLASS_NAME(char)
QX_REGISTER_CLASS_NAME(unsigned int)
QX_REGISTER_CLASS_NAME(unsigned short)
QX_REGISTER_CLASS_NAME(unsigned long)
QX_REGISTER_CLASS_NAME(unsigned char)

QX_REGISTER_CLASS_NAME(std::string)
QX_REGISTER_CLASS_NAME(std::wstring)

QX_REGISTER_CLASS_NAME(QObject)
QX_REGISTER_CLASS_NAME(QString)
QX_REGISTER_CLASS_NAME(QStringList)
QX_REGISTER_CLASS_NAME(QByteArray)
QX_REGISTER_CLASS_NAME(QDate)
QX_REGISTER_CLASS_NAME(QDateTime)
QX_REGISTER_CLASS_NAME(QPoint)
QX_REGISTER_CLASS_NAME(QRect)
QX_REGISTER_CLASS_NAME(QRegExp)
QX_REGISTER_CLASS_NAME(QSize)
QX_REGISTER_CLASS_NAME(QTime)
QX_REGISTER_CLASS_NAME(QUrl)
QX_REGISTER_CLASS_NAME(QVariant)
QX_REGISTER_CLASS_NAME(QUuid)
QX_REGISTER_CLASS_NAME(QSqlError)

#ifdef _QX_ENABLE_QT_GUI
QX_REGISTER_CLASS_NAME(QColor)
QX_REGISTER_CLASS_NAME(QFont)
QX_REGISTER_CLASS_NAME(QImage)
QX_REGISTER_CLASS_NAME(QBrush)
QX_REGISTER_CLASS_NAME(QMatrix)
QX_REGISTER_CLASS_NAME(QPicture)
QX_REGISTER_CLASS_NAME(QPixmap)
QX_REGISTER_CLASS_NAME(QRegion)
#endif // _QX_ENABLE_QT_GUI

QX_REGISTER_CLASS_NAME_TEMPLATE_1(std::allocator)
QX_REGISTER_CLASS_NAME_TEMPLATE_1(std::vector)
QX_REGISTER_CLASS_NAME_TEMPLATE_1(std::list)
QX_REGISTER_CLASS_NAME_TEMPLATE_1(std::set)

#ifdef _QX_ENABLE_BOOST

QX_REGISTER_CLASS_NAME_TEMPLATE_1(boost::shared_ptr)
QX_REGISTER_CLASS_NAME_TEMPLATE_1(boost::scoped_ptr)
QX_REGISTER_CLASS_NAME_TEMPLATE_1(boost::weak_ptr)
QX_REGISTER_CLASS_NAME_TEMPLATE_1(boost::optional)

#endif // _QX_ENABLE_BOOST

QX_REGISTER_CLASS_NAME_TEMPLATE_1(QVector)
QX_REGISTER_CLASS_NAME_TEMPLATE_1(QList)
QX_REGISTER_CLASS_NAME_TEMPLATE_1(QLinkedList)
QX_REGISTER_CLASS_NAME_TEMPLATE_1(QSharedPointer)
QX_REGISTER_CLASS_NAME_TEMPLATE_1(QWeakPointer)
QX_REGISTER_CLASS_NAME_TEMPLATE_1(QFlags)
QX_REGISTER_CLASS_NAME_TEMPLATE_1(QSet)

QX_REGISTER_CLASS_NAME_TEMPLATE_1(qx::dao::ptr)

QX_REGISTER_CLASS_NAME_TEMPLATE_1(std::unique_ptr)
QX_REGISTER_CLASS_NAME_TEMPLATE_1(std::shared_ptr)
QX_REGISTER_CLASS_NAME_TEMPLATE_1(std::weak_ptr)

QX_REGISTER_CLASS_NAME_TEMPLATE_2(std::pair)
QX_REGISTER_CLASS_NAME_TEMPLATE_2(std::map)

#ifdef _QX_ENABLE_BOOST
QX_REGISTER_CLASS_NAME_TEMPLATE_2(boost::unordered_map)
QX_REGISTER_CLASS_NAME_TEMPLATE_2(boost::unordered_multimap)
QX_REGISTER_CLASS_NAME_TEMPLATE_1(boost::unordered_set)
QX_REGISTER_CLASS_NAME_TEMPLATE_1(boost::unordered_multiset)
#endif // _QX_ENABLE_BOOST

QX_REGISTER_CLASS_NAME_TEMPLATE_2(std::unordered_map)
QX_REGISTER_CLASS_NAME_TEMPLATE_2(std::unordered_multimap)
QX_REGISTER_CLASS_NAME_TEMPLATE_1(std::unordered_set)
QX_REGISTER_CLASS_NAME_TEMPLATE_1(std::unordered_multiset)

QX_REGISTER_CLASS_NAME_TEMPLATE_2(QPair)
QX_REGISTER_CLASS_NAME_TEMPLATE_2(QHash)
QX_REGISTER_CLASS_NAME_TEMPLATE_2(QMultiHash)
QX_REGISTER_CLASS_NAME_TEMPLATE_2(QMap)
QX_REGISTER_CLASS_NAME_TEMPLATE_2(QMultiMap)

#ifdef _QX_ENABLE_BOOST
QX_REGISTER_CLASS_NAME_TEMPLATE_1(boost::tuple)
QX_REGISTER_CLASS_NAME_TEMPLATE_2(boost::tuple)
QX_REGISTER_CLASS_NAME_TEMPLATE_3(boost::tuple)
QX_REGISTER_CLASS_NAME_TEMPLATE_4(boost::tuple)
QX_REGISTER_CLASS_NAME_TEMPLATE_5(boost::tuple)
QX_REGISTER_CLASS_NAME_TEMPLATE_6(boost::tuple)
QX_REGISTER_CLASS_NAME_TEMPLATE_7(boost::tuple)
QX_REGISTER_CLASS_NAME_TEMPLATE_8(boost::tuple)
QX_REGISTER_CLASS_NAME_TEMPLATE_9(boost::tuple)
#endif // _QX_ENABLE_BOOST

QX_REGISTER_CLASS_NAME_TEMPLATE_1(std::tuple)
QX_REGISTER_CLASS_NAME_TEMPLATE_2(std::tuple)
QX_REGISTER_CLASS_NAME_TEMPLATE_3(std::tuple)
QX_REGISTER_CLASS_NAME_TEMPLATE_4(std::tuple)
QX_REGISTER_CLASS_NAME_TEMPLATE_5(std::tuple)
QX_REGISTER_CLASS_NAME_TEMPLATE_6(std::tuple)
QX_REGISTER_CLASS_NAME_TEMPLATE_7(std::tuple)
QX_REGISTER_CLASS_NAME_TEMPLATE_8(std::tuple)
QX_REGISTER_CLASS_NAME_TEMPLATE_9(std::tuple)

#if (QT_VERSION >= 0x040600)
QX_REGISTER_CLASS_NAME_TEMPLATE_1(QScopedPointer)
#endif // (QT_VERSION >= 0x040600)

#endif // _QX_GET_CLASS_NAME_PRIMITIVE_H_
