/****************************************************************************
**
** Copyright (C) 2010 QxOrm France and/or its subsidiary(-ies)
** Contact: QxOrm France Information (contact@qxorm.com)
**
** This file is part of the QxOrm library
**
** Commercial Usage
** Licensees holding valid QxOrm Commercial licenses may use this file in
** accordance with the QxOrm Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and QxOrm France
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file 'license.gpl3.txt' included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html
**
** If you are unsure which license is appropriate for your use, please
** contact the support department at support@qxorm.com
**
****************************************************************************/

#include "../../include/QxPrecompiled.h"

#include "../../include/QxXml/QxXmlWriter.h"

#include "../../include/QxMemLeak/mem_leak.h"

namespace qx {

QString QxXmlWriter::writeBinaryData(const QString & namespaceUri, const QString & name, QxXmlWriter::type_byte_arr_ptr pData)
{
   QString sKey(getNextKeyBinaryData());
   m_mapBinaryData.insert(sKey, pData);

   writeStartElement(namespaceUri, name);
   writeAttribute(QX_XML_ATTRIBUTE_IS_BINARY_DATA, "1");
   writeCharacters(sKey);
   writeEndElement();

   return sKey;
}

QString QxXmlWriter::writeBinaryData(const QString & qualifiedName, QxXmlWriter::type_byte_arr_ptr pData)
{
   QString sKey(getNextKeyBinaryData());
   m_mapBinaryData.insert(sKey, pData);

   writeStartElement(qualifiedName);
   writeAttribute(QX_XML_ATTRIBUTE_IS_BINARY_DATA, "1");
   writeCharacters(sKey);
   writeEndElement();

   return sKey;
}

} // namespace qx

QDataStream & operator << (QDataStream & stream, const qx::QxXmlWriter & xmlWriter)
{
   stream << xmlWriter.getXml();
   stream << (qint32)(xmlWriter.getBinaryDataCount());

   qx::QxXmlWriter::type_hash_bin_data_itr itr = xmlWriter.getBinaryDataItr();

   while (itr.hasNext())
   {
      itr.next();
      stream << itr.key();
      stream << (* itr.value());
   }

   return stream;
}
