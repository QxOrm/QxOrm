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

#ifdef Q_MOC_RUN
#include <QxCommon/QxConfig.h> // Need to include this file for the 'moc' process
#endif // Q_MOC_RUN

#ifdef _QX_ENABLE_QT_NETWORK
#ifndef _QX_HTTP_SERVER_H_
#define _QX_HTTP_SERVER_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxHttpServer.h
 * \author Lionel Marty
 * \ingroup QxHttpServer
 * \brief HTTP server which manages connections in a multi-threaded environment (support SSL/TLS, persistent connection, etc...) : https://www.qxorm.com/qxorm_en/manual.html#manual_96
 */

#ifdef _QX_NO_PRECOMPILED_HEADER
#ifndef Q_MOC_RUN
#include <QxPrecompiled.h> // Need to include precompiled header for the generated moc file
#endif // Q_MOC_RUN
#endif // _QX_NO_PRECOMPILED_HEADER

#include <QxHttpServer/QxHttpRequest.h>
#include <QxHttpServer/QxHttpResponse.h>
#include <QxHttpServer/QxHttpTransaction.h>

#ifndef Q_MOC_RUN
#include <QxService/QxTransaction.h>
#include <QxService/QxConnect.h>
#include <QxService/QxServer.h>
#endif // Q_MOC_RUN

#if (QT_VERSION >= 0x050000)
class QAbstractEventDispatcher;
#endif // (QT_VERSION >= 0x050000)

namespace qx {

/*!
 * \ingroup QxHttpServer
 * \brief qx::QxHttpServer : HTTP server which manages connections in a multi-threaded environment (support SSL/TLS, persistent connection, etc...) : https://www.qxorm.com/qxorm_en/manual.html#manual_96
 */
class QX_DLL_EXPORT QxHttpServer : public QObject
{

   Q_OBJECT

public:

   typedef std::function<void (qx::QxHttpRequest &, qx::QxHttpResponse &)> type_fct_custom_request_handler;

private:

   struct QxHttpServerImpl;
   std::unique_ptr<QxHttpServerImpl> m_pImpl; //!< Private implementation idiom

public:

   QxHttpServer(QObject * parent = NULL);
   virtual ~QxHttpServer();

   Q_INVOKABLE void startServer();
   Q_INVOKABLE void stopServer();

   void setCustomRequestHandler(type_fct_custom_request_handler fct);
   QxHttpServer & dispatch(const QString & command, const QString & path, type_fct_custom_request_handler fct, long position = -1);
   void beforeDispatching(type_fct_custom_request_handler fct);
   void afterDispatching(type_fct_custom_request_handler fct);
   void clearDispatcher();

#if (QT_VERSION >= 0x050000)
   void setEventDispatcher(QAbstractEventDispatcher * pEventDispatcher);
#endif // (QT_VERSION >= 0x050000)

   static void buildResponseStaticFile(qx::QxHttpRequest & request, qx::QxHttpResponse & response, const QString & serverPath, qlonglong chunkedSize = 0);
   static void buildResponseQxRestApi(qx::QxHttpRequest & request, qx::QxHttpResponse & response);

Q_SIGNALS:

   void error(const QString & err, qx::QxHttpTransaction_ptr transaction);
   void transactionStarted(qx::QxHttpTransaction_ptr transaction);
   void transactionFinished(qx::QxHttpTransaction_ptr transaction);
   void serverStatusChanged(bool bIsRunning);

private Q_SLOTS:

   void onError(const QString & err, qx::service::QxTransaction_ptr transaction);
   void onServerIsRunning(bool bIsRunning, qx::service::QxServer * pServer);
   void onTransactionStarted(qx::service::QxTransaction_ptr transaction);
   void onTransactionFinished(qx::service::QxTransaction_ptr transaction);
   void onCustomRequestHandler(qx::service::QxTransaction_ptr transaction);

};

typedef std::shared_ptr<QxHttpServer> QxHttpServer_ptr;

} // namespace qx

typedef qx::QxHttpServer qx_http_server;

#endif // _QX_HTTP_SERVER_H_
#endif // _QX_ENABLE_QT_NETWORK
