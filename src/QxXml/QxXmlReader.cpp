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

#include <QxXml/QxXmlReader.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

void QxXmlReader::addBinaryData(const QxXmlReader::type_hash_bin_data & other, bool bClear)
{
   if (bClear) { m_mapBinaryData.clear(); }
   QxXmlReader::type_hash_bin_data_itr itr(other);

   while (itr.hasNext())
   {
      itr.next();
      addBinaryData(itr.key(), itr.value());
   }
}

void QxXmlReader::addBinaryData(const QString & sKey, QxXmlReader::type_byte_arr_ptr pData)
{
   if (sKey.isEmpty()) { return; }
   if (m_mapBinaryData.contains(sKey)) { qAssert(false); return; }

   m_mapBinaryData.insert(sKey, pData);
}

void QxXmlReader::removeBinaryData(const QString & sKey)
{
   m_mapBinaryData.remove(sKey);
}

void QxXmlReader::removeAllBinaryData()
{
   m_mapBinaryData.clear();
}

bool QxXmlReader::isStartBinaryData() const
{
   if (! isStartElement()) { return false; }
   if (! attributes().hasAttribute(QX_XML_ATTRIBUTE_IS_BINARY_DATA)) { return false; }
   if (attributes().value(QX_XML_ATTRIBUTE_IS_BINARY_DATA) != "1") { return false; }

   return true;
}

QxXmlReader::type_byte_arr_ptr QxXmlReader::readBinaryData()
{
   if (! isStartBinaryData()) { return QxXmlReader::type_byte_arr_ptr(); }

   QString sKey = readElementText();
   if (sKey.isEmpty() || ! m_mapBinaryData.contains(sKey)) { return QxXmlReader::type_byte_arr_ptr(); }

   return m_mapBinaryData.value(sKey);
}

} // namespace qx

QDataStream & operator >> (QDataStream & stream, qx::QxXmlReader & xmlReader)
{
   QString sXml;           stream >> sXml;
   qint32 lBinDataCount;   stream >> lBinDataCount;

   xmlReader.addData(sXml);

   for (qint32 l = 0; l < lBinDataCount; l++)
   {
      QString sKey;        stream >> sKey;
      QByteArray pBuff;    stream >> pBuff;

      qx::QxXmlReader::type_byte_arr_ptr pBinData;
      pBinData.reset(new QByteArray(pBuff));
      xmlReader.addBinaryData(sKey, pBinData);
   }

   return stream;
}
