/****************************************************************************
**
** https://www.qxorm.com/
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

#include <QtNetwork/qhostaddress.h>

#include <QxHttpServer/QxHttpTransaction.h>

#include <QxService/QxConnect.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

namespace compress {
QByteArray to_gzip(const QByteArray & data);
quint32 crc32(const QByteArray & data);
} // namespace compress

struct Q_DECL_HIDDEN QxHttpTransaction::QxHttpTransactionImpl
{

   qx::QxHttpRequest m_request;        //!< HTTP transaction request
   qx::QxHttpResponse m_response;      //!< HTTP transaction response
   QTcpSocket * m_socket;              //!< HTTP transaction socket
   bool m_headersWritten;              //!< HTTP response headers already written (used to write chunked data)
   bool m_chunkAllowed;                //!< If we receive a HTTP 1.0 request, then chunked responses are not supported by client

   QxHttpTransactionImpl(QxHttpTransaction * parent) : m_request(parent), m_response(parent), m_socket(NULL), m_headersWritten(false), m_chunkAllowed(true) { qAssert(parent != NULL); }
   ~QxHttpTransactionImpl() { ; }

   bool waitForReadSocket(QTcpSocket & socket)
   {
      if (socket.bytesAvailable() > 0) { return true; }
      long lMaxWait = qx::service::QxConnect::getSingleton()->getMaxWait();
      long lCurrRetry = 0;
      do
      {
         if (socket.waitForReadyRead(1)) { return true; }
         if (socket.bytesAvailable() > 0) { return true; }
         QCoreApplication::processEvents();
         lCurrRetry++;
      }
      while ((lMaxWait == -1) || (lCurrRetry < lMaxWait));
      return false;
   }

   bool writeToSocket(QTcpSocket & socket, const QByteArray & data)
   {
      if (data.isEmpty()) { return true; }
      const char * pData = data.constData();
      qint64 iTotalWritten = 0; qint64 iTotalToWrite = static_cast<qint64>(data.count());
      while (iTotalWritten < iTotalToWrite)
      {
         qint64 iWritten = socket.write((pData + iTotalWritten), (iTotalToWrite - iTotalWritten));
         if (iWritten == -1) { break; }
         iTotalWritten += iWritten;
      }
      return (iTotalWritten == iTotalToWrite);
   }

   qx_bool writeHeaders(QTcpSocket & socket)
   {
      // Check if headers/cookies has already been written
      if (m_headersWritten) { return qx_bool(true); }
      m_headersWritten = true;

      // HTTP response first line
      QByteArray line = "HTTP/1.1 " + QByteArray::number(m_response.status()) + " " + m_response.statusDesc() + "\r\n";
      if (! writeToSocket(socket, line)) { return qx_bool(500, "Internal server error : cannot write to socket HTTP response first line '" + line + "' (" + socket.errorString() + ")"); }

      // HTTP response headers
      QHashIterator<QByteArray, QByteArray> itrHeaders(m_response.headers());
      while (itrHeaders.hasNext())
      {
         itrHeaders.next();
         if (itrHeaders.key().trimmed().isEmpty()) { continue; }
         line = itrHeaders.key() + ": " + itrHeaders.value() + "\r\n";
         if (! writeToSocket(socket, line)) { return qx_bool(500, "Internal server error : cannot write to socket HTTP response header '" + line + "' (" + socket.errorString() + ")"); }
      }

      // HTTP response cookies
      QHashIterator<QByteArray, QxHttpCookie> itrCookies(m_response.cookies());
      while (itrCookies.hasNext())
      {
         itrCookies.next();
         if (itrCookies.value().name.trimmed().isEmpty()) { continue; }
         line = "Set-Cookie: " + itrCookies.value().toString() + "\r\n";
         if (! writeToSocket(socket, line)) { return qx_bool(500, "Internal server error : cannot write to socket HTTP response cookie '" + line + "' (" + socket.errorString() + ")"); }
      }

      // Empty line : means end of headers/cookies
      if (! writeToSocket(socket, "\r\n")) { return qx_bool(500, "Internal server error : cannot write to socket HTTP response header end line (" + socket.errorString() + ")"); }
      return qx_bool(true);
   }

};

QxHttpTransaction::QxHttpTransaction() : qx::service::QxTransaction(), m_pImpl(new QxHttpTransactionImpl(this)) { ; }

QxHttpTransaction::~QxHttpTransaction() { ; }

void QxHttpTransaction::clear() { qx::service::QxTransaction::clear(); m_pImpl.reset(new QxHttpTransactionImpl(this)); }

qx::QxHttpRequest & QxHttpTransaction::request() { return m_pImpl->m_request; }

qx::QxHttpResponse & QxHttpTransaction::response() { return m_pImpl->m_response; }

void QxHttpTransaction::executeServer()
{
   if (getMessageReturn()) { Q_EMIT onCustomRequestHandler(); }
}

qx_bool QxHttpTransaction::writeSocketServer(QTcpSocket & socket)
{
   // Check HTTP transaction message return
   qx_bool bTransactionMsg = getMessageReturn();
   if (! bTransactionMsg)
   {
      m_pImpl->m_response.headers().insert("Content-Type", "text/plain; charset=utf-8");
      m_pImpl->m_response.status() = static_cast<int>(bTransactionMsg.getCode());
      m_pImpl->m_response.data() = bTransactionMsg.getDesc().toUtf8();
   }

   // Check if we can compress response data
   bool chunked = (m_pImpl->m_response.isChunked() && m_pImpl->m_chunkAllowed);
   bool compress = qx::service::QxConnect::getSingleton()->getCompressData();
   QString contentType = m_pImpl->m_response.header("Content-Type").toLower();
   compress = (compress && (contentType.startsWith("text/") || contentType.startsWith("application/json") || contentType.startsWith("application/javascript")));
   compress = (compress && (m_pImpl->m_request.header("Accept-Encoding").toLower().contains("gzip")));
   compress = (compress && (m_pImpl->m_response.data().size() > 99));
   compress = (compress && (m_pImpl->m_response.status() == 200));
   compress = (compress && (! chunked));

   // Compress response data
   if (compress)
   {
      m_pImpl->m_response.headers().insert("Content-Encoding", "gzip");
      m_pImpl->m_response.data() = qx::compress::to_gzip(m_pImpl->m_response.data());
   }

   // Insert 'Content-Length' header
   QByteArray & body = m_pImpl->m_response.data();
   QByteArray contentLength = QByteArray::number(body.count());
   if (! chunked) { m_pImpl->m_response.headers().insert("Content-Length", contentLength); }

   // Check if we have to force to close connection
   if (m_pImpl->m_request.header("Connection").toLower() == "close")
   { setForceConnectionStatus(qx::service::QxTransaction::conn_close); }

   // HTTP response headers and cookies
   qx_bool bWriteHeaders = m_pImpl->writeHeaders(socket);
   if (! bWriteHeaders) { return bWriteHeaders; }

   // HTTP response body content
   if (chunked) { if (! m_pImpl->writeToSocket(socket, "0\r\n\r\n")) { return qx_bool(500, "Internal server error : cannot write to socket HTTP last empty chunked data (" + socket.errorString() + ")"); } }
   else if (! m_pImpl->writeToSocket(socket, body)) { return qx_bool(500, "Internal server error : cannot write to socket HTTP response body content of " + QString::number(body.count()) + " bytes (" + socket.errorString() + ")"); }
   return qx_bool(true);
}

qx_bool QxHttpTransaction::readSocketServer(QTcpSocket & socket)
{
   // Fetch source client details
   setIpSource(socket.peerAddress().toString());
   setPortSource(static_cast<long>(socket.peerPort()));
   m_pImpl->m_request.sourceAddress() = socket.peerAddress().toString();
   m_pImpl->m_request.sourcePort() = static_cast<long>(socket.peerPort());
   m_pImpl->m_socket = (& socket);

   // HTTP request first line
   setMessageReturn(qx_bool(true));
   if (! m_pImpl->waitForReadSocket(socket)) { setMessageReturn(qx_bool(500, "Internal server error : cannot read socket to parse HTTP request first line (" + socket.errorString() + ")")); return qx_bool(true); }
   QByteArray line = socket.readLine().trimmed();
   QStringList lst = QString::fromUtf8(line).split(" ");
   if (lst.count() < 3) { setMessageReturn(qx_bool(400, "Bad request : invalid HTTP request first line : " + line)); return qx_bool(true); }
   if (! lst.at(2).contains("HTTP")) { setMessageReturn(qx_bool(400, "Bad request : invalid HTTP request first line, third parameter must contain 'HTTP' : " + line)); return qx_bool(true); }
   m_pImpl->m_request.command() = lst.at(0).toUpper();
   m_pImpl->m_request.url() = QUrl(lst.at(1));
   m_pImpl->m_request.version() = lst.at(2);

   // HTTP request headers and cookies
   int iContentLength = 0;
   do
   {
      if (! m_pImpl->waitForReadSocket(socket)) { setMessageReturn(qx_bool(500, "Internal server error : cannot read socket to parse HTTP headers (" + socket.errorString() + ")")); return qx_bool(true); }
      line = socket.readLine().trimmed(); if (line.isEmpty()) { break; }
      int pos = line.indexOf(':'); if (pos <= 0) { setMessageReturn(qx_bool(400, "Bad request : invalid HTTP header : " + line)); return qx_bool(true); }
      QByteArray key = line.left(pos).trimmed();
      QByteArray value = line.mid(pos + 1).trimmed();
#if (QT_VERSION >= 0x060000)
      if (key.toLower() == "cookie") { m_pImpl->m_request.cookies().insert(QxHttpCookie::parse(value)); }
#else // (QT_VERSION >= 0x060000)
      if (key.toLower() == "cookie") { m_pImpl->m_request.cookies().unite(QxHttpCookie::parse(value)); }
#endif // (QT_VERSION >= 0x060000)
      else { m_pImpl->m_request.headers().insert(key, value); }
      if (key.toLower() == "content-length") { iContentLength = value.toInt(); }
   }
   while (1);

   // Check HTTP 1.0 compatibility
   if (m_pImpl->m_request.version().contains("1.0"))
   {
      m_pImpl->m_chunkAllowed = false;
      if (m_pImpl->m_request.header("Connection").toLower() != "keep-alive")
      { setForceConnectionStatus(qx::service::QxTransaction::conn_close); }
   }

   QByteArray body;
   if (iContentLength > 0)
   {
      // HTTP request body content
      body.reserve(iContentLength);
      do
      {
         if (! m_pImpl->waitForReadSocket(socket)) { setMessageReturn(qx_bool(500, "Internal server error : cannot read socket to get HTTP body content (" + socket.errorString() + ")")); return qx_bool(true); }
         body += socket.readAll();
      }
      while (body.count() < iContentLength);
      m_pImpl->m_request.data() = body;
   }

#if (QT_VERSION >= 0x050000)
   QByteArray params = m_pImpl->m_request.url().query(QUrl::FullyEncoded).toLatin1();
#else // (QT_VERSION >= 0x050000)
   QByteArray params = m_pImpl->m_request.url().encodedQuery();
#endif // (QT_VERSION >= 0x050000)

   // HTTP request parameters (from URL and from body if content-type is 'application/x-www-form-urlencoded', which means web-form submit)
   if ((! body.isEmpty()) && (m_pImpl->m_request.header("content-type").toLower() == "application/x-www-form-urlencoded"))
   { params += (params.isEmpty() ? QByteArray() : QByteArray("&")) + body; }
   QList<QByteArray> listParams = params.split('&');
   Q_FOREACH(QByteArray param, listParams)
   {
      int pos = param.indexOf('=');
      if (pos > 0) { QByteArray key = param.left(pos).trimmed(); QByteArray value = param.mid(pos + 1).trimmed(); m_pImpl->m_request.params().insert(QUrl::fromPercentEncoding(key), QUrl::fromPercentEncoding(value)); }
      else if (! param.isEmpty()) { m_pImpl->m_request.params().insert(QUrl::fromPercentEncoding(param), ""); }
   }

   return qx_bool(true);
}

qx_bool QxHttpTransaction::writeChunked(const QByteArray & data)
{
   // Check input data
   if (data.isEmpty()) { return qx_bool(true); }
   if (! m_pImpl->m_socket) { return qx_bool(false, "No socket to write HTTP chunked data"); }
   if (! m_pImpl->m_chunkAllowed) { m_pImpl->m_response.data() += data; return qx_bool(true); }

   // HTTP response headers and cookies
   if (! m_pImpl->m_headersWritten)
   {
      m_pImpl->m_response.headers().insert("Transfer-Encoding", "chunked");
      qx_bool bWriteHeaders = m_pImpl->writeHeaders(* m_pImpl->m_socket);
      if (! bWriteHeaders) { return bWriteHeaders; }
   }

   // Write chunked data
   QByteArray chunked = (QByteArray::number(data.count(), 16) + "\r\n" + data + "\r\n");
   if (! m_pImpl->writeToSocket((* m_pImpl->m_socket), chunked)) { return qx_bool(500, "Internal server error : cannot write to socket HTTP chunked data of " + QString::number(data.count()) + " bytes (" + m_pImpl->m_socket->errorString() + ")"); }
   return qx_bool(true);
}

namespace compress {

// Code from : https://stackoverflow.com/questions/20734831/compress-string-with-gzip-using-qcompress
QByteArray to_gzip(const QByteArray & data)
{
   QByteArray compressedData = qCompress(data);
   compressedData.remove(0, 6);
   compressedData.chop(4);

   QByteArray header;
   QDataStream ds1(& header, QIODevice::WriteOnly);
   ds1 << quint16(0x1f8b) << quint16(0x0800) << quint16(0x0000) << quint16(0x0000) << quint16(0x000b);

   QByteArray footer;
   QDataStream ds2(& footer, QIODevice::WriteOnly);
   ds2.setByteOrder(QDataStream::LittleEndian);
   ds2 << qx::compress::crc32(data) << quint32(data.size());

   return (header + compressedData + footer);
}

static const quint32 crc32_tab[] = { /* CRC polynomial 0xedb88320 */
   0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
   0xe963a535, 0x9e6495a3, 0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
   0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
   0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
   0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9,
   0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
   0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b, 0x35b5a8fa, 0x42b2986c,
   0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
   0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
   0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
   0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d, 0x76dc4190, 0x01db7106,
   0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
   0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
   0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
   0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
   0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
   0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
   0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
   0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
   0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
   0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
   0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
   0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
   0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
   0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
   0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
   0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
   0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
   0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
   0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
   0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
   0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
   0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
   0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
   0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
   0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
   0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
   0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
   0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
   0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
   0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
   0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
   0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

quint32 update_crc32(unsigned char ch, quint32 crc)
{
   return (crc32_tab[((crc) ^ ((quint8)ch)) & 0xff] ^ ((crc) >> 8));
}

quint32 crc32(const QByteArray & data)
{
   quint32 crc = 0xFFFFFFFFL;
   for (int i = 0; i < data.size(); i++) { crc = update_crc32(data[i], crc); }
   return ~crc;
}

} // namespace compress
} // namespace qx

#endif // _QX_ENABLE_QT_NETWORK
