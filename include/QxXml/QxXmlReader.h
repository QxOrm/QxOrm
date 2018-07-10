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

#ifndef _QX_XML_READER_H_
#define _QX_XML_READER_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QtCore/qhash.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qdatastream.h>

#include <QtXml/QXmlStreamReader>

#include "../../include/QxXml/QxXmlWriter.h"

namespace qx {

class QX_DLL_EXPORT QxXmlReader : public QXmlStreamReader
{

public:

   typedef boost::shared_ptr<QByteArray> type_byte_arr_ptr;
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
