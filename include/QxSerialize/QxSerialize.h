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

#ifdef _QX_ENABLE_BOOST_SERIALIZATION
#ifndef _QX_SERIALIZE_H_
#define _QX_SERIALIZE_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSerialize.h
 * \author Lionel Marty
 * \ingroup QxSerialize
 * \brief Include all files necessary to serialize most used classes defined into stl, boost and Qt libraries
 */

#include <QxCommon/QxConfig.h>

#include <QxSerialize/QxSerializeFastCompil.h>
#include <QxSerialize/boost/QxSerializeInclude.h>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/extended_type_info_typeid.hpp>
#include <boost/serialization/type_info_implementation.hpp>
#include <boost/serialization/void_cast.hpp>
#include <boost/serialization/array.hpp>
#include <boost/serialization/complex.hpp>
#include <boost/serialization/deque.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/scoped_ptr.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/variant.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/optional.hpp>

#include <boost/ptr_container/serialize_ptr_array.hpp>
#include <boost/ptr_container/serialize_ptr_circular_buffer.hpp>
#include <boost/ptr_container/serialize_ptr_container.hpp>
#include <boost/ptr_container/serialize_ptr_deque.hpp>
#include <boost/ptr_container/serialize_ptr_list.hpp>
#include <boost/ptr_container/serialize_ptr_map.hpp>
#include <boost/ptr_container/serialize_ptr_set.hpp>
#include <boost/ptr_container/serialize_ptr_unordered_map.hpp>
#include <boost/ptr_container/serialize_ptr_unordered_set.hpp>
#include <boost/ptr_container/serialize_ptr_vector.hpp>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4189)
#endif // _MSC_VER

#include <QxSerialize/boost/QxExportDllMacroHpp.h>
#include <QxSerialize/boost/QxExportDllMacroCpp.h>
#include <QxSerialize/boost/QxExportDllBoostArchive.h>
#include <QxSerialize/boost/QxImportDllBoostArchive.h>
#include <QxSerialize/boost/QxSerialize_shared_ptr.h>
#include <QxSerialize/boost/QxSerialize_tuple.h>
#include <QxSerialize/boost/QxSerialize_unordered_map.h>
#include <QxSerialize/boost/QxSerialize_unordered_set.h>

#include <QxSerialize/Qt/QxSerialize_QBrush.h>
#include <QxSerialize/Qt/QxSerialize_QByteArray.h>
#include <QxSerialize/Qt/QxSerialize_QColor.h>
#include <QxSerialize/Qt/QxSerialize_QDate.h>
#include <QxSerialize/Qt/QxSerialize_QDateTime.h>
#include <QxSerialize/Qt/QxSerialize_QFont.h>
#include <QxSerialize/Qt/QxSerialize_QHash.h>
#include <QxSerialize/Qt/QxSerialize_QImage.h>
#include <QxSerialize/Qt/QxSerialize_QFlags.h>
#include <QxSerialize/Qt/QxSerialize_QLinkedList.h>
#include <QxSerialize/Qt/QxSerialize_QList.h>
#include <QxSerialize/Qt/QxSerialize_QMap.h>
#include <QxSerialize/Qt/QxSerialize_QMatrix.h>
#include <QxSerialize/Qt/QxSerialize_QObject.h>
#include <QxSerialize/Qt/QxSerialize_QPair.h>
#include <QxSerialize/Qt/QxSerialize_QPicture.h>
#include <QxSerialize/Qt/QxSerialize_QPixmap.h>
#include <QxSerialize/Qt/QxSerialize_QPoint.h>
#include <QxSerialize/Qt/QxSerialize_QRect.h>
#include <QxSerialize/Qt/QxSerialize_QRegExp.h>
#include <QxSerialize/Qt/QxSerialize_QRegion.h>
#include <QxSerialize/Qt/QxSerialize_QScopedPointer.h>
#include <QxSerialize/Qt/QxSerialize_QSharedPointer.h>
#include <QxSerialize/Qt/QxSerialize_QSize.h>
#include <QxSerialize/Qt/QxSerialize_QString.h>
#include <QxSerialize/Qt/QxSerialize_QStringList.h>
#include <QxSerialize/Qt/QxSerialize_QTime.h>
#include <QxSerialize/Qt/QxSerialize_QUrl.h>
#include <QxSerialize/Qt/QxSerialize_QUuid.h>
#include <QxSerialize/Qt/QxSerialize_QVariant.h>
#include <QxSerialize/Qt/QxSerialize_QVector.h>
#include <QxSerialize/Qt/QxSerialize_QWeakPointer.h>
#include <QxSerialize/Qt/QxSerialize_QMultiHash.h>
#include <QxSerialize/Qt/QxSerialize_QMultiMap.h>
#include <QxSerialize/Qt/QxSerialize_QSqlError.h>

#include <QxSerialize/Qx/QxSerialize_QxCollection.h>
#include <QxSerialize/Qx/QxSerialize_QxDaoPointer.h>

/*
#include <QxSerialize/Qx/QxSerialize_QxXmlReader.h>
#include <QxSerialize/Qx/QxSerialize_QxXmlWriter.h>
*/

#include <QxSerialize/std/QxSerialize_std_tuple.h>
#include <QxSerialize/std/QxSerialize_std_shared_ptr.h>
#include <QxSerialize/std/QxSerialize_std_unique_ptr.h>
#include <QxSerialize/std/QxSerialize_std_unordered_map.h>
#include <QxSerialize/std/QxSerialize_std_unordered_set.h>

#include <QxSerialize/QxBoostSerializeHelper/IxBoostSerializeRegisterHelper.h>
#include <QxSerialize/QxBoostSerializeHelper/QxBoostInitGuid.h>
#include <QxSerialize/QxBoostSerializeHelper/QxBoostSerializeHelper.h>
#include <QxSerialize/QxBoostSerializeHelper/QxBoostSerializeRegisterHelper.h>
#include <QxSerialize/QxBoostSerializeHelper/QxBoostSerializeRegisterHelperX.h>

#include <QxSerialize/QxArchive.h>
#include <QxSerialize/QxClone.h>
#include <QxSerialize/QxDump.h>
#include <QxSerialize/QxSerializeInvoker.h>

#ifdef _MSC_VER
#pragma warning(pop)
#endif // _MSC_VER

#endif // _QX_SERIALIZE_H_
#endif // _QX_ENABLE_BOOST_SERIALIZATION
