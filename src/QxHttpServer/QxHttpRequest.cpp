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

#include <QtCore/quuid.h>

#include <QxHttpServer/QxHttpRequest.h>
#include <QxHttpServer/QxHttpTransaction.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

struct Q_DECL_HIDDEN QxHttpRequest::QxHttpRequestImpl
{

   QUrl m_url;                                  //!< HTTP request path
   QString m_command;                           //!< HTTP request method : GET, POST, HEAD, PUT, DELETE, etc...
   QString m_version;                           //!< HTTP request version
   QByteArray m_data;                           //!< HTTP request body content
   QHash<QByteArray, QByteArray> m_headers;     //!< HTTP request headers
   QHash<QByteArray, QxHttpCookie> m_cookies;   //!< HTTP request cookies
   QHash<QString, QVariant> m_dispatchParams;   //!< HTTP request dynamic URL parameters from server dispatcher
   QHash<QString, QString> m_params;            //!< HTTP request parameters (from URL and from body if content-type is 'application/x-www-form-urlencoded', which means web-form submit)
   QString m_address;                           //!< HTTP client IP address
   long m_port;                                 //!< HTTP client port
   QxHttpTransaction * m_transaction;           //!< HTTP transaction
   QString m_guid;                              //!< HTTP request internal GUID (can be used for logging for example)

   QxHttpRequestImpl(QxHttpTransaction * transaction) : m_port(0), m_transaction(transaction) { qAssert(m_transaction != NULL); m_guid = QUuid::createUuid().toString(); }
   ~QxHttpRequestImpl() { ; }

};

QxHttpRequest::QxHttpRequest(QxHttpTransaction * transaction) : m_pImpl(new QxHttpRequestImpl(transaction)) { ; }

QxHttpRequest::~QxHttpRequest() { ; }

QUrl & QxHttpRequest::url() { return m_pImpl->m_url; }

QString & QxHttpRequest::command() { return m_pImpl->m_command; }

QString & QxHttpRequest::version() { return m_pImpl->m_version; }

QByteArray & QxHttpRequest::data() { return m_pImpl->m_data; }

QHash<QByteArray, QByteArray> & QxHttpRequest::headers() { return m_pImpl->m_headers; }

QByteArray QxHttpRequest::header(const QByteArray & key)
{
   QHashIterator<QByteArray, QByteArray> itr(m_pImpl->m_headers);
   while (itr.hasNext()) { itr.next(); if (itr.key().trimmed().toLower() == key.trimmed().toLower()) { return itr.value(); } }
   return QByteArray();
}

QHash<QByteArray, QxHttpCookie> & QxHttpRequest::cookies() { return m_pImpl->m_cookies; }

QxHttpCookie QxHttpRequest::cookie(const QByteArray & name) { return m_pImpl->m_cookies.value(name); }

QHash<QString, QVariant> & QxHttpRequest::dispatchParams() { return m_pImpl->m_dispatchParams; }

QHash<QString, QString> & QxHttpRequest::params() { return m_pImpl->m_params; }

QString QxHttpRequest::param(const QString & key) { return m_pImpl->m_params.value(key); }

QString & QxHttpRequest::sourceAddress() { return m_pImpl->m_address; }

long & QxHttpRequest::sourcePort() { return m_pImpl->m_port; }

QString QxHttpRequest::guid() const { return m_pImpl->m_guid; }

} // namespace qx

#endif // _QX_ENABLE_QT_NETWORK
