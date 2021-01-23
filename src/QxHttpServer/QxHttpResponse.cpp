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

#include <QxHttpServer/QxHttpResponse.h>
#include <QxHttpServer/QxHttpTransaction.h>

#include <QxService/QxConnect.h>

#include <QxMemLeak/mem_leak.h>

#ifndef QByteArrayLiteral
#define QByteArrayLiteral QByteArray
#endif // QByteArrayLiteral

namespace qx {

struct Q_DECL_HIDDEN QxHttpResponse::QxHttpResponseImpl
{

   int m_status;                                   //!< HTTP response status (200 OK, 400 Bad Request, 401 Unauthorized, 500 Internal Server Error, etc...)
   QByteArray m_data;                              //!< HTTP response body content
   QHash<QByteArray, QByteArray> m_headers;        //!< HTTP response headers
   QHash<QByteArray, QxHttpCookie> m_cookies;      //!< HTTP response cookies
   QxHttpTransaction * m_transaction;              //!< HTTP transaction
   bool m_isChunked;                               //!< HTTP response is chunked (useful for streaming for example)

   QxHttpResponseImpl(QxHttpTransaction * transaction) : m_status(200), m_transaction(transaction), m_isChunked(false) { qAssert(m_transaction != NULL); initHeaders(); }
   ~QxHttpResponseImpl() { ; }

   void initHeaders()
   {
      m_headers.insert("Server", "QxOrm HTTP server");
      m_headers.insert("Date", currentDateTimeGMT());
      m_headers.insert("Content-Type", "text/plain; charset=iso-8859-1");
      if (qx::service::QxConnect::getSingleton()->getKeepAlive() != 0) { m_headers.insert("Connection", "keep-alive"); }
      else { m_headers.insert("Connection", "close"); }
   }

   qx_bool writeChunked(const QByteArray & data)
   {
      if (data.isEmpty()) { return qx_bool(true); }
      if (! m_transaction) { qAssert(false); return qx_bool(false, "No HTTP transaction associated to the response"); }
      qx_bool bWriteChunked = m_transaction->writeChunked(data);
      if (bWriteChunked) { m_isChunked = true; }
      return bWriteChunked;
   }

   QByteArray currentDateTimeGMT()
   {
      QByteArray day, month;
      QDateTime dt = QDateTime::currentDateTimeUtc();
      switch (dt.date().dayOfWeek())
      {
         case 1: day = QByteArrayLiteral("Mon"); break;
         case 2: day = QByteArrayLiteral("Tue"); break;
         case 3: day = QByteArrayLiteral("Wed"); break;
         case 4: day = QByteArrayLiteral("Thu"); break;
         case 5: day = QByteArrayLiteral("Fri"); break;
         case 6: day = QByteArrayLiteral("Sat"); break;
         case 7: day = QByteArrayLiteral("Sun"); break;
         default: qAssert(false); break;
      }
      switch (dt.date().month())
      {
         case  1: month = QByteArrayLiteral("Jan"); break;
         case  2: month = QByteArrayLiteral("Feb"); break;
         case  3: month = QByteArrayLiteral("Mar"); break;
         case  4: month = QByteArrayLiteral("Apr"); break;
         case  5: month = QByteArrayLiteral("May"); break;
         case  6: month = QByteArrayLiteral("Jun"); break;
         case  7: month = QByteArrayLiteral("Jul"); break;
         case  8: month = QByteArrayLiteral("Aug"); break;
         case  9: month = QByteArrayLiteral("Sep"); break;
         case 10: month = QByteArrayLiteral("Oct"); break;
         case 11: month = QByteArrayLiteral("Nov"); break;
         case 12: month = QByteArrayLiteral("Dec"); break;
         default: qAssert(false); break;
      }
      QByteArray day_ = QString("%1").arg(dt.date().day(), 2, 10, QChar('0')).toLatin1();
      QByteArray year = QString("%1").arg(dt.date().year(), 4, 10, QChar('0')).toLatin1();
      QByteArray hour = QString("%1").arg(dt.time().hour(), 2, 10, QChar('0')).toLatin1();
      QByteArray minute = QString("%1").arg(dt.time().minute(), 2, 10, QChar('0')).toLatin1();
      QByteArray second = QString("%1").arg(dt.time().second(), 2, 10, QChar('0')).toLatin1();
      return (day + ", " + day_ + " " + month + " " + year + " " + hour + ":" + minute + ":" + second + " GMT");
   }

};

QxHttpResponse::QxHttpResponse(QxHttpTransaction * transaction) : m_pImpl(new QxHttpResponseImpl(transaction)) { ; }

QxHttpResponse::~QxHttpResponse() { ; }

int & QxHttpResponse::status() { return m_pImpl->m_status; }

QByteArray & QxHttpResponse::data() { return m_pImpl->m_data; }

QHash<QByteArray, QByteArray> & QxHttpResponse::headers() { return m_pImpl->m_headers; }

QByteArray QxHttpResponse::header(const QByteArray & key)
{
   QHashIterator<QByteArray, QByteArray> itr(m_pImpl->m_headers);
   while (itr.hasNext()) { itr.next(); if (itr.key().trimmed().toLower() == key.trimmed().toLower()) { return itr.value(); } }
   return QByteArray();
}

QHash<QByteArray, QxHttpCookie> & QxHttpResponse::cookies() { return m_pImpl->m_cookies; }

QxHttpCookie QxHttpResponse::cookie(const QByteArray & name) { return m_pImpl->m_cookies.value(name); }

qx_bool QxHttpResponse::writeChunked(const QByteArray & data) { return m_pImpl->writeChunked(data); }

bool QxHttpResponse::isChunked() const { return m_pImpl->m_isChunked; }

QByteArray QxHttpResponse::statusDesc()
{
   QByteArray desc;
   switch (m_pImpl->m_status)
   {
      case 100: desc = QByteArrayLiteral("Continue"); break;
      case 101: desc = QByteArrayLiteral("Switching Protocols"); break;
      case 102: desc = QByteArrayLiteral("Processing"); break;
      case 103: desc = QByteArrayLiteral("Early Hints"); break;
      case 200: desc = QByteArrayLiteral("OK"); break;
      case 201: desc = QByteArrayLiteral("Created"); break;
      case 202: desc = QByteArrayLiteral("Accepted"); break;
      case 203: desc = QByteArrayLiteral("Non-Authoritative Information"); break;
      case 204: desc = QByteArrayLiteral("No Content"); break;
      case 205: desc = QByteArrayLiteral("Reset Content"); break;
      case 206: desc = QByteArrayLiteral("Partial Content"); break;
      case 207: desc = QByteArrayLiteral("Multi-Status"); break;
      case 208: desc = QByteArrayLiteral("Already Reported"); break;
      case 210: desc = QByteArrayLiteral("Content Different"); break;
      case 226: desc = QByteArrayLiteral("IM Used"); break;
      case 300: desc = QByteArrayLiteral("Multiple Choices"); break;
      case 301: desc = QByteArrayLiteral("Moved Permanently"); break;
      case 302: desc = QByteArrayLiteral("Found"); break;
      case 303: desc = QByteArrayLiteral("See Other"); break;
      case 304: desc = QByteArrayLiteral("Not Modified"); break;
      case 305: desc = QByteArrayLiteral("Use Proxy"); break;
      case 306: desc = QByteArrayLiteral("Switch Proxy"); break;
      case 307: desc = QByteArrayLiteral("Temporary Redirect"); break;
      case 308: desc = QByteArrayLiteral("Permanent Redirect"); break;
      case 310: desc = QByteArrayLiteral("Too many Redirects"); break;
      case 400: desc = QByteArrayLiteral("Bad Request"); break;
      case 401: desc = QByteArrayLiteral("Unauthorized"); break;
      case 402: desc = QByteArrayLiteral("Payment Required"); break;
      case 403: desc = QByteArrayLiteral("Forbidden"); break;
      case 404: desc = QByteArrayLiteral("Not Found"); break;
      case 405: desc = QByteArrayLiteral("Method Not Allowed"); break;
      case 406: desc = QByteArrayLiteral("Not Acceptable"); break;
      case 407: desc = QByteArrayLiteral("Proxy Authentication Required"); break;
      case 408: desc = QByteArrayLiteral("Request Time-out"); break;
      case 409: desc = QByteArrayLiteral("Conflict"); break;
      case 410: desc = QByteArrayLiteral("Gone"); break;
      case 411: desc = QByteArrayLiteral("Length Required"); break;
      case 412: desc = QByteArrayLiteral("Precondition Failed"); break;
      case 413: desc = QByteArrayLiteral("Request Entity Too Large"); break;
      case 414: desc = QByteArrayLiteral("Request-URI Too Long"); break;
      case 415: desc = QByteArrayLiteral("Unsupported Media Type"); break;
      case 416: desc = QByteArrayLiteral("Requested range unsatisfiable"); break;
      case 417: desc = QByteArrayLiteral("Expectation failed"); break;
      case 418: desc = QByteArrayLiteral("I’m a teapot"); break;
      case 421: desc = QByteArrayLiteral("Bad mapping / Misdirected Request"); break;
      case 422: desc = QByteArrayLiteral("Unprocessable entity"); break;
      case 423: desc = QByteArrayLiteral("Locked"); break;
      case 424: desc = QByteArrayLiteral("Method failure"); break;
      case 425: desc = QByteArrayLiteral("Unordered Collection"); break;
      case 426: desc = QByteArrayLiteral("Upgrade Required"); break;
      case 428: desc = QByteArrayLiteral("Precondition Required"); break;
      case 429: desc = QByteArrayLiteral("Too Many Requests"); break;
      case 431: desc = QByteArrayLiteral("Request Header Fields Too Large"); break;
      case 449: desc = QByteArrayLiteral("Retry With"); break;
      case 450: desc = QByteArrayLiteral("Blocked by Windows Parental Controls"); break;
      case 451: desc = QByteArrayLiteral("Unavailable For Legal Reasons"); break;
      case 456: desc = QByteArrayLiteral("Unrecoverable Error"); break;
      case 444: desc = QByteArrayLiteral("No Response"); break;
      case 495: desc = QByteArrayLiteral("SSL Certificate Error"); break;
      case 496: desc = QByteArrayLiteral("SSL Certificate Required"); break;
      case 497: desc = QByteArrayLiteral("HTTP Request Sent to HTTPS Port"); break;
      case 498: desc = QByteArrayLiteral("Token expired/invalid"); break;
      case 499: desc = QByteArrayLiteral("Client Closed Request"); break;
      case 500: desc = QByteArrayLiteral("Internal Server Error"); break;
      case 501: desc = QByteArrayLiteral("Not Implemented"); break;
      case 502: desc = QByteArrayLiteral("Bad Gateway ou Proxy Error"); break;
      case 503: desc = QByteArrayLiteral("Service Unavailable"); break;
      case 504: desc = QByteArrayLiteral("Gateway Time-out"); break;
      case 505: desc = QByteArrayLiteral("HTTP Version not supported"); break;
      case 506: desc = QByteArrayLiteral("Variant Also Negotiates"); break;
      case 507: desc = QByteArrayLiteral("Insufficient storage"); break;
      case 508: desc = QByteArrayLiteral("Loop detected"); break;
      case 509: desc = QByteArrayLiteral("Bandwidth Limit Exceeded"); break;
      case 510: desc = QByteArrayLiteral("Not extended"); break;
      case 511: desc = QByteArrayLiteral("Network authentication required"); break;
      case 520: desc = QByteArrayLiteral("Unknown Error"); break;
      case 521: desc = QByteArrayLiteral("Web Server Is Down"); break;
      case 522: desc = QByteArrayLiteral("Connection Timed Out"); break;
      case 523: desc = QByteArrayLiteral("Origin Is Unreachable"); break;
      case 524: desc = QByteArrayLiteral("A Timeout Occurred"); break;
      case 525: desc = QByteArrayLiteral("SSL Handshake Failed"); break;
      case 526: desc = QByteArrayLiteral("Invalid SSL Certificate"); break;
      case 527: desc = QByteArrayLiteral("Railgun Error"); break;
      default:  desc = QByteArrayLiteral("Unknown status code"); break;
   }
   return desc;
}

} // namespace qx

#endif // _QX_ENABLE_QT_NETWORK
