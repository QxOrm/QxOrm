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

#ifdef _QX_ENABLE_QT_NETWORK

#include <QxPrecompiled.h>

#include <QxService/QxTools.h>
#include <QxService/QxConnect.h>

#include <QxCommon/QxSimpleCrypt.h>
#include <QxCommon/QxExceptionCode.h>

#include <QxSerialize/QxSerializeQDataStream.h>
#include <QxSerialize/QxSerializeQJson.h>
#include <QxSerialize/QJson/QxSerializeQJson_QxTransaction.h>

#include <QxMemLeak/mem_leak.h>

#define QX_SERVICE_TOOLS_HEADER_SIZE (sizeof(quint32) + sizeof(quint16) + sizeof(quint16) + sizeof(quint16)) // (serialized data size) + (serialization type) + (compress data) + (encrypt data)
#define QX_SERVICE_MIN_SIZE_TO_COMPRESS_DATA 2000

namespace qx {
namespace service {

qx_bool QxTools::readSocket(QTcpSocket & socket, QxTransaction & transaction, quint32 & size)
{
   while (socket.bytesAvailable() < (qint64)(QX_SERVICE_TOOLS_HEADER_SIZE))
   { if (! socket.waitForReadyRead(QxConnect::getSingleton()->getMaxWait())) { return qx_bool(QX_ERROR_SERVICE_READ_ERROR, "invalid bytes count available to retrieve transaction header"); } }

   quint32 uiSerializedSize = 0;
   quint16 uiSerializationType(0), uiCompressData(0), uiEncryptData(0);
   QByteArray dataHeader = socket.read((qint64)(QX_SERVICE_TOOLS_HEADER_SIZE));
   qAssert(dataHeader.size() == (int)(QX_SERVICE_TOOLS_HEADER_SIZE));
   QDataStream in(& dataHeader, QIODevice::ReadOnly);
   in.setVersion(QDataStream::Qt_4_5);
   in >> uiSerializedSize;
   in >> uiSerializationType;
   in >> uiCompressData;
   in >> uiEncryptData;

   while (socket.bytesAvailable() < (qint64)(uiSerializedSize))
   { if (! socket.waitForReadyRead(QxConnect::getSingleton()->getMaxWait())) { return qx_bool(QX_ERROR_SERVICE_READ_ERROR, "invalid bytes count available to retrieve transaction serialized data"); } }

   QByteArray dataSerialized = socket.read((qint64)(uiSerializedSize));
   qAssert(dataSerialized.size() == (int)(uiSerializedSize));
   size = (quint32)(QX_SERVICE_TOOLS_HEADER_SIZE + uiSerializedSize);

   if (uiEncryptData != 0)
   {
      QxSimpleCrypt crypto(QxConnect::getSingleton()->getEncryptKey());
      QByteArray decrypted = crypto.decryptToByteArray(dataSerialized);
      if ((crypto.lastError() != QxSimpleCrypt::ErrorNoError) || decrypted.isEmpty()) { return qx_bool(QX_ERROR_UNKNOWN, "an error occured during decryption of data"); }
      dataSerialized = decrypted;
   }

   if (uiCompressData != 0)
   { QByteArray uncompressed = qUncompress(dataSerialized); if (! uncompressed.isEmpty()) { dataSerialized = uncompressed; } }

   qx_bool bDeserializeOk;
   switch (static_cast<QxConnect::serialization_type>(uiSerializationType))
   {
#if _QX_SERIALIZE_BINARY
      case QxConnect::serialization_binary:                 bDeserializeOk = qx::serialization::binary::from_byte_array(transaction, dataSerialized); break;
#endif // _QX_SERIALIZE_BINARY
#if _QX_SERIALIZE_XML
      case QxConnect::serialization_xml:                    bDeserializeOk = qx::serialization::xml::from_byte_array(transaction, dataSerialized); break;
#endif // _QX_SERIALIZE_XML
#if _QX_SERIALIZE_TEXT
      case QxConnect::serialization_text:                   bDeserializeOk = qx::serialization::text::from_byte_array(transaction, dataSerialized); break;
#endif // _QX_SERIALIZE_TEXT
#if _QX_SERIALIZE_PORTABLE_BINARY
      case QxConnect::serialization_portable_binary:        bDeserializeOk = qx::serialization::portable_binary::from_byte_array(transaction, dataSerialized, 0); break;
#endif // _QX_SERIALIZE_PORTABLE_BINARY
#if _QX_SERIALIZE_WIDE_BINARY
      case QxConnect::serialization_wide_binary:            bDeserializeOk = qx::serialization::wide::binary::from_byte_array(transaction, dataSerialized); break;
#endif // _QX_SERIALIZE_WIDE_BINARY
#if _QX_SERIALIZE_WIDE_XML
      case QxConnect::serialization_wide_xml:               bDeserializeOk = qx::serialization::wide::xml::from_byte_array(transaction, dataSerialized); break;
#endif // _QX_SERIALIZE_WIDE_XML
#if _QX_SERIALIZE_WIDE_TEXT
      case QxConnect::serialization_wide_text:              bDeserializeOk = qx::serialization::wide::text::from_byte_array(transaction, dataSerialized); break;
#endif // _QX_SERIALIZE_WIDE_TEXT
#if _QX_SERIALIZE_POLYMORPHIC
      case QxConnect::serialization_polymorphic_binary:     bDeserializeOk = qx::serialization::polymorphic_binary::from_byte_array(transaction, dataSerialized); break;
      case QxConnect::serialization_polymorphic_xml:        bDeserializeOk = qx::serialization::polymorphic_xml::from_byte_array(transaction, dataSerialized); break;
      case QxConnect::serialization_polymorphic_text:       bDeserializeOk = qx::serialization::polymorphic_text::from_byte_array(transaction, dataSerialized); break;
#endif // _QX_SERIALIZE_POLYMORPHIC
      case QxConnect::serialization_qt:                     bDeserializeOk = qx::serialization::qt::from_byte_array(transaction, dataSerialized); break;
#ifndef _QX_NO_JSON
      case QxConnect::serialization_json:                   bDeserializeOk = qx::serialization::json::from_byte_array(transaction, dataSerialized); break;
#endif // _QX_NO_JSON
      default:                                              return qx_bool(QX_ERROR_UNKNOWN, "unknown serialization type to read data from socket");
   }

   return bDeserializeOk;
}

qx_bool QxTools::writeSocket(QTcpSocket & socket, QxTransaction & transaction, quint32 & size)
{
   QByteArray dataSerialized;
   std::string owner; Q_UNUSED(owner);
   std::wstring w_owner; Q_UNUSED(w_owner);
   switch (QxConnect::getSingleton()->getSerializationType())
   {
#if _QX_SERIALIZE_BINARY
      case QxConnect::serialization_binary:                 dataSerialized = qx::serialization::binary::to_byte_array(transaction, (& owner)); break;
#endif // _QX_SERIALIZE_BINARY
#if _QX_SERIALIZE_XML
      case QxConnect::serialization_xml:                    dataSerialized = qx::serialization::xml::to_byte_array(transaction, (& owner)); break;
#endif // _QX_SERIALIZE_XML
#if _QX_SERIALIZE_TEXT
      case QxConnect::serialization_text:                   dataSerialized = qx::serialization::text::to_byte_array(transaction, (& owner)); break;
#endif // _QX_SERIALIZE_TEXT
#if _QX_SERIALIZE_PORTABLE_BINARY
      case QxConnect::serialization_portable_binary:        dataSerialized = qx::serialization::portable_binary::to_byte_array(transaction, (& owner), 0); break;
#endif // _QX_SERIALIZE_PORTABLE_BINARY
#if _QX_SERIALIZE_WIDE_BINARY
      case QxConnect::serialization_wide_binary:            dataSerialized = qx::serialization::wide::binary::to_byte_array(transaction, (& w_owner)); break;
#endif // _QX_SERIALIZE_WIDE_BINARY
#if _QX_SERIALIZE_WIDE_XML
      case QxConnect::serialization_wide_xml:               dataSerialized = qx::serialization::wide::xml::to_byte_array(transaction, (& w_owner)); break;
#endif // _QX_SERIALIZE_WIDE_XML
#if _QX_SERIALIZE_WIDE_TEXT
      case QxConnect::serialization_wide_text:              dataSerialized = qx::serialization::wide::text::to_byte_array(transaction, (& w_owner)); break;
#endif // _QX_SERIALIZE_WIDE_TEXT
#if _QX_SERIALIZE_POLYMORPHIC
      case QxConnect::serialization_polymorphic_binary:     dataSerialized = qx::serialization::polymorphic_binary::to_byte_array(transaction, (& owner)); break;
      case QxConnect::serialization_polymorphic_xml:        dataSerialized = qx::serialization::polymorphic_xml::to_byte_array(transaction, (& owner)); break;
      case QxConnect::serialization_polymorphic_text:       dataSerialized = qx::serialization::polymorphic_text::to_byte_array(transaction, (& owner)); break;
#endif // _QX_SERIALIZE_POLYMORPHIC
      case QxConnect::serialization_qt:                     dataSerialized = qx::serialization::qt::to_byte_array(transaction, (& owner)); break;
#ifndef _QX_NO_JSON
      case QxConnect::serialization_json:                   dataSerialized = qx::serialization::json::to_byte_array(transaction, (& owner)); break;
#endif // _QX_NO_JSON
      default:                                              return qx_bool(QX_ERROR_UNKNOWN, "unknown serialization type to write data to socket");
   }

   if (dataSerialized.isEmpty())
   { return qx_bool(QX_ERROR_UNKNOWN, "an error occured during serialization of data"); }

   quint16 uiCompressData = 0;
   if (QxConnect::getSingleton()->getCompressData() && (dataSerialized.size() > QX_SERVICE_MIN_SIZE_TO_COMPRESS_DATA))
   { QByteArray compressed = qCompress(dataSerialized, -1); if (! compressed.isEmpty()) { dataSerialized = compressed; uiCompressData = 1; } }

   quint16 uiEncryptData = 0;
   if (QxConnect::getSingleton()->getEncryptData())
   {
      QxSimpleCrypt crypto(QxConnect::getSingleton()->getEncryptKey());
      crypto.setCompressionMode(QxSimpleCrypt::CompressionNever);
      crypto.setIntegrityProtectionMode(QxSimpleCrypt::ProtectionChecksum);
      QByteArray encrypted = crypto.encryptToByteArray(dataSerialized);
      if ((crypto.lastError() != QxSimpleCrypt::ErrorNoError) || encrypted.isEmpty()) { return qx_bool(QX_ERROR_UNKNOWN, "an error occured during encryption of data"); }
      dataSerialized = encrypted;
      uiEncryptData = 1;
   }

   QByteArray dataHeader;
   QDataStream out(& dataHeader, QIODevice::WriteOnly);
   out.setVersion(QDataStream::Qt_4_5);
   out << (quint32)(dataSerialized.size());
   out << (quint16)(QxConnect::getSingleton()->getSerializationType());
   out << (quint16)(uiCompressData);
   out << (quint16)(uiEncryptData);
   qAssert(dataHeader.size() == (int)(QX_SERVICE_TOOLS_HEADER_SIZE));

   qint64 iTotalWritten = 0;
   qint64 iTotalToWrite = (qint64)(dataHeader.size());
   const char * pDataHeader = dataHeader.constData();
   while (iTotalWritten < iTotalToWrite)
   {
      qint64 iWritten = socket.write((pDataHeader + iTotalWritten), (iTotalToWrite - iTotalWritten));
      if (iWritten == -1) { break; }
      iTotalWritten += iWritten;
   }

   if (iTotalWritten != iTotalToWrite)
   { return qx_bool(QX_ERROR_SERVICE_WRITE_ERROR, "unable to write all data bytes (header) to socket"); }

   iTotalWritten = 0;
   iTotalToWrite = (qint64)(dataSerialized.size());
   const char * pDataSerialized = dataSerialized.constData();
   while (iTotalWritten < iTotalToWrite)
   {
      qint64 iWritten = socket.write((pDataSerialized + iTotalWritten), (iTotalToWrite - iTotalWritten));
      if (iWritten == -1) { break; }
      iTotalWritten += iWritten;
   }

   size = (quint32)(dataHeader.size() + dataSerialized.size());
   return ((iTotalWritten == iTotalToWrite) ? qx_bool(true) : qx_bool(QX_ERROR_SERVICE_WRITE_ERROR, "unable to write all data bytes (serialized data) to socket"));
}

} // namespace service
} // namespace qx

#endif // _QX_ENABLE_QT_NETWORK
