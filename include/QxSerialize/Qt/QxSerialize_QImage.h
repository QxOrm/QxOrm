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

#if _QX_ENABLE_QT_GUI_DEPENDENCY
#ifndef _QX_SERIALIZE_QIMAGE_H_
#define _QX_SERIALIZE_QIMAGE_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/nvp.hpp>

#include <QtGui/qimage.h>

#include <QtCore/qbytearray.h>
#include <QtCore/qbuffer.h>

#include <QxSerialize/Qt/QxSerialize_QByteArray.h>
#include <QxSerialize/QxSerializeFastCompil.h>

BOOST_CLASS_VERSION(QImage, 0)

QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_HPP(QX_DLL_EXPORT, QImage)
QX_BOOST_EXPORT_SERIALIZATION_FAST_COMPIL_HPP(QImage)

#endif // _QX_SERIALIZE_QIMAGE_H_
#endif // _QX_ENABLE_QT_GUI_DEPENDENCY
