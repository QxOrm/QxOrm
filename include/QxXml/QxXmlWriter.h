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

#ifndef _QX_XML_WRITER_H_
#define _QX_XML_WRITER_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QtCore/qhash.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qdatastream.h>

#if (QT_VERSION >= 0x040800)
#include <QtCore/QXmlStreamWriter>
#else // (QT_VERSION >= 0x040800)
#include <QtXml/QXmlStreamWriter>
#endif // (QT_VERSION >= 0x040800)

#define QX_XML_PREFIX_BINARY_DATA_KEY     "qx_binary_data_key_"
#define QX_XML_ATTRIBUTE_IS_BINARY_DATA   "qx_is_binary_data"

namespace qx {

class QX_DLL_EXPORT QxXmlWriter : public QXmlStreamWriter
{

public:

   typedef std::shared_ptr<QByteArray> type_byte_arr_ptr;
   typedef QHash<QString, type_byte_arr_ptr> type_hash_bin_data;
   typedef QHashIterator<QString, type_byte_arr_ptr> type_hash_bin_data_itr;

protected:

   type_hash_bin_data m_mapBinaryData;    // Collection of binary data associated with xml (<=> attached files)
   long m_lKeyBinaryData;                 // Current binary data key to write to xml
   QString m_pStringWriter;               // String containing xml to write

public:

   QxXmlWriter() : QXmlStreamWriter(& m_pStringWriter), m_lKeyBinaryData(0) { initQxXmlWriter(); }
   virtual ~QxXmlWriter() { ; }

   QString getXml() const                             { return m_pStringWriter; }
   type_hash_bin_data_itr getBinaryDataItr() const    { return type_hash_bin_data_itr(m_mapBinaryData); }
   long getBinaryDataCount() const                    { return m_mapBinaryData.count(); }

   QString writeBinaryData(const QString & namespaceUri, const QString & name, type_byte_arr_ptr pData);
   QString writeBinaryData(const QString & qualifiedName, type_byte_arr_ptr pData);

protected:

   inline QString getNextKeyBinaryData()  { return (QString(QX_XML_PREFIX_BINARY_DATA_KEY) + QString::number(++m_lKeyBinaryData)); }
   inline void initQxXmlWriter()          { setAutoFormatting(true); setAutoFormattingIndent(3); }

};

} // namespace qx

QX_DLL_EXPORT QDataStream & operator << (QDataStream & stream, const qx::QxXmlWriter & xmlWriter);

#endif // _QX_XML_WRITER_H_
