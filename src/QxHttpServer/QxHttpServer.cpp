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

#include <QtCore/qfile.h>
#include <QtCore/qdir.h>

#if (QT_VERSION >= 0x050000)
#include <QtCore/qmimetype.h>
#include <QtCore/qmimedata.h>
#include <QtCore/qmimedatabase.h>
#endif // (QT_VERSION >= 0x050000)

#include <QxHttpServer/QxHttpServer.h>

#include <QxService/QxThreadPool.h>
#include <QxService/QxConnect.h>

#include <QxCommon/QxException.h>
#include <QxCommon/QxExceptionCode.h>

#include <QxRestApi/QxRestApi.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

struct QxHttpServer::QxHttpServerImpl
{

   qx::service::QxThreadPool_ptr m_pThreadPool;                               //!< HTTP server is managed by a thread pool
   QxHttpServer::type_fct_custom_request_handler m_fctCustomRequestHandler;   //!< Callback to manage requests and build responses (executed in its dedicated thread)

   QxHttpServerImpl() { ; }
   ~QxHttpServerImpl() { ; }

};

QxHttpServer::QxHttpServer() : QObject(), m_pImpl(new QxHttpServerImpl())
{
   qRegisterMetaType<qx::QxHttpTransaction_ptr>("qx::QxHttpTransaction_ptr");
   qRegisterMetaType<qx::QxHttpTransaction_ptr>("QxHttpTransaction_ptr");
}

QxHttpServer::~QxHttpServer() { stopServer(); }

void QxHttpServer::startServer()
{
   if (m_pImpl->m_pThreadPool) { stopServer(); }
   qx::service::QxConnect::getSingleton()->setModeHTTP(true);

   m_pImpl->m_pThreadPool.reset(new qx::service::QxThreadPool());
   QObject::connect(m_pImpl->m_pThreadPool.get(), SIGNAL(error(const QString &, qx::service::QxTransaction_ptr)), this, SLOT(onError(const QString &, qx::service::QxTransaction_ptr)));
   QObject::connect(m_pImpl->m_pThreadPool.get(), SIGNAL(serverIsRunning(bool, qx::service::QxServer *)), this, SLOT(onServerIsRunning(bool, qx::service::QxServer *)));
   QObject::connect(m_pImpl->m_pThreadPool.get(), SIGNAL(transactionStarted(qx::service::QxTransaction_ptr)), this, SLOT(onTransactionStarted(qx::service::QxTransaction_ptr)));
   QObject::connect(m_pImpl->m_pThreadPool.get(), SIGNAL(transactionFinished(qx::service::QxTransaction_ptr)), this, SLOT(onTransactionFinished(qx::service::QxTransaction_ptr)));
   QObject::connect(m_pImpl->m_pThreadPool.get(), SIGNAL(customRequestHandler(qx::service::QxTransaction_ptr)), this, SLOT(onCustomRequestHandler(qx::service::QxTransaction_ptr)), Qt::DirectConnection);
   m_pImpl->m_pThreadPool->start();
}

void QxHttpServer::stopServer()
{
   if (! m_pImpl->m_pThreadPool) { return; }
   m_pImpl->m_pThreadPool.reset();
   Q_EMIT serverStatusChanged(false);
}

void QxHttpServer::setCustomRequestHandler(QxHttpServer::type_fct_custom_request_handler fct)
{
   m_pImpl->m_fctCustomRequestHandler = fct;
}

void QxHttpServer::onError(const QString & err, qx::service::QxTransaction_ptr transaction)
{
   qx::QxHttpTransaction_ptr httpTransaction = std::dynamic_pointer_cast<qx::QxHttpTransaction>(transaction);
   if (transaction && (! httpTransaction)) { qAssertMsg(false, "[QxOrm] qx::QxHttpServer::onError", "unable to get HTTP transaction using std::dynamic_pointer_cast"); }
   Q_EMIT error(err, httpTransaction);
}

void QxHttpServer::onServerIsRunning(bool bIsRunning, qx::service::QxServer * pServer)
{
   Q_UNUSED(pServer);
   if (bIsRunning) { QString msg = "port : " + QString::number(qx::service::QxConnect::getSingleton()->getPort()); qDebug("[QxOrm] HTTP server is running (%s)", qPrintable(msg)); }
   else { qDebug("[QxOrm] %s", "HTTP server has been stopped"); }
   Q_EMIT serverStatusChanged(bIsRunning);
}

void QxHttpServer::onTransactionStarted(qx::service::QxTransaction_ptr transaction)
{
   qx::QxHttpTransaction_ptr httpTransaction = std::dynamic_pointer_cast<qx::QxHttpTransaction>(transaction);
   if (transaction && (! httpTransaction)) { qAssertMsg(false, "[QxOrm] qx::QxHttpServer::onTransactionStarted", "unable to get HTTP transaction using std::dynamic_pointer_cast"); }
   Q_EMIT transactionStarted(httpTransaction);
}

void QxHttpServer::onTransactionFinished(qx::service::QxTransaction_ptr transaction)
{
   qx::QxHttpTransaction_ptr httpTransaction = std::dynamic_pointer_cast<qx::QxHttpTransaction>(transaction);
   if (transaction && (! httpTransaction)) { qAssertMsg(false, "[QxOrm] qx::QxHttpServer::onTransactionFinished", "unable to get HTTP transaction using std::dynamic_pointer_cast"); }
   Q_EMIT transactionFinished(httpTransaction);
}

void QxHttpServer::onCustomRequestHandler(qx::service::QxTransaction_ptr transaction)
{
   qx::QxHttpTransaction_ptr httpTransaction = std::dynamic_pointer_cast<qx::QxHttpTransaction>(transaction);
   if (transaction && (! httpTransaction)) { qAssertMsg(false, "[QxOrm] qx::QxHttpServer::onCustomRequestHandler", "unable to get HTTP transaction using std::dynamic_pointer_cast"); return; }
   if (! httpTransaction) { qAssertMsg(false, "[QxOrm] qx::QxHttpServer::onCustomRequestHandler", "HTTP transaction is empty"); return; }
   if (! m_pImpl->m_fctCustomRequestHandler) { httpTransaction->setMessageReturn(qx_bool(501, "[QxOrm] Not implemented : you must provide a custom request handler (callback) using qx::QxHttpServer::setCustomRequestHandler() method")); return; }

   qx::QxHttpRequest & request = httpTransaction->request();
   qx::QxHttpResponse & response = httpTransaction->response();
   try { m_pImpl->m_fctCustomRequestHandler(request, response); }
   catch (const qx::exception & x) { qx_bool xb = x.toQxBool(); httpTransaction->setMessageReturn(xb); }
   catch (const std::exception & e) { httpTransaction->setMessageReturn(qx_bool(500, e.what())); }
   catch (...) { httpTransaction->setMessageReturn(qx_bool(500, "[QxOrm] Unknown server error")); }
}

void QxHttpServer::buildResponseStaticFile(qx::QxHttpRequest & request, qx::QxHttpResponse & response, const QString & serverPath)
{
   // Check HTTP method GET
   QByteArray requestPath = request.url().path().toLatin1();
   if (request.command() != "GET")
   {
      response.status() = 400;
      response.data() = "Unknown command '" + request.command().toLatin1() + "' to get server static file '" + requestPath + "'";
      return;
   }

   // Check root server path to deliver static files
   QDir dirServerPath(serverPath);
   if (! dirServerPath.exists())
   {
      response.status() = 404;
      response.data() = "Server path for static files not found : " + serverPath.toLatin1();
      return;
   }

   // Check if requested static file exists on server
   QString filePath = dirServerPath.filePath(requestPath.right(requestPath.size() - 1));
   if (! QFile::exists(filePath))
   {
      response.status() = 404;
      response.data() = "Server static file not found : " + requestPath;
      return;
   }

   // Check if requested static file is inside root server path (to avoid ../)
   QDir dirFilePath(filePath);
   QString canonicalServerPath = dirServerPath.canonicalPath();
   QString canonicalFilePath = dirFilePath.canonicalPath();
   if (! canonicalFilePath.startsWith(canonicalServerPath))
   {
      response.status() = 403;
      response.data() = "Cannot access to server static file : " + requestPath;
      return;
   }

   // Try to open static file in read-only mode
   QFile file(filePath);
   if (! file.open(QFile::ReadOnly))
   {
      response.status() = 403;
      response.data() = "Cannot open server static file : " + requestPath;
      return;
   }

#if (QT_VERSION >= 0x050000)
   QMimeDatabase mimeDatabase;
   QMimeType mimeType = mimeDatabase.mimeTypeForFile(filePath);
   response.headers().insert("Content-Type", mimeType.name().toLatin1());
#endif // (QT_VERSION >= 0x050000)

   // Read file content
   response.data() = file.readAll();
   file.close();
}

void QxHttpServer::buildResponseQxRestApi(qx::QxHttpRequest & request, qx::QxHttpResponse & response)
{
   qx::QxRestApi api;
   QString result = api.processRequest(request.data());
   response.headers().insert("Content-Type", "application/json; charset=utf-8");
   response.data() = result.toUtf8();
}

} // namespace qx

#endif // _QX_ENABLE_QT_NETWORK
