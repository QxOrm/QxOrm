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

#ifndef _QX_XML_READER_H_
#define _QX_XML_READER_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QtCore/qhash.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qdatastream.h>

#if (QT_VERSION >= 0x040800)
#include <QtCore/QXmlStreamReader>
#else // (QT_VERSION >= 0x040800)
#include <QtXml/QXmlStreamReader>
#endif // (QT_VERSION >= 0x040800)

#include <QxXml/QxXmlWriter.h>

namespace qx {

class QX_DLL_EXPORT QxXmlReader : public QXmlStreamReader
{

public:

   typedef std::shared_ptr<QByteArray> type_byte_arr_ptr;
   typedef QHash<QString, type_byte_arr_ptr> type_hash_bin_data;
   typedef QHashIterator<QString, type_byte_arr_ptr> type_hash_bin_data_itr;

protected:

   type_hash_bin_data m_mapBinaryData;    // Collection of binary data associated with xml (<=> attached files)

public:

   QxXmlReader() : QXmlStreamReader() { ; }
   QxXmlReader(const QString & data) : QXmlStreamReader(data) { ; }
   virtual ~QxXmlReader() { ; }

   void addBinaryData(const type_hash_bin_data & other, bool bClear);
   void addBinaryData(const QString & sKey, type_byte_arr_ptr pData);
   void removeBinaryData(const QString & sKey);
   void removeAllBinaryData();

   bool isStartBinaryData() const;
   type_byte_arr_ptr readBinaryData();

};

} // namespace qx

QX_DLL_EXPORT QDataStream & operator >> (QDataStream & stream, qx::QxXmlReader & xmlReader);

#endif // _QX_XML_READER_H_
