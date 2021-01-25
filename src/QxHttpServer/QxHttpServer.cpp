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

#include <QtCore/qdir.h>
#include <QtCore/qfile.h>
#include <QtCore/qmutex.h>
#include <QtCore/qabstracteventdispatcher.h>

#if (QT_VERSION >= 0x050000)
#include <QtCore/qregularexpression.h>
#else // (QT_VERSION >= 0x050000)
#include <QtCore/qregexp.h>
#endif // (QT_VERSION >= 0x050000)

#if (QT_VERSION >= 0x050000)
#include <QtCore/qmimetype.h>
#include <QtCore/qmimedata.h>
#include <QtCore/qmimedatabase.h>
#endif // (QT_VERSION >= 0x050000)

#include <QxHttpServer/QxHttpServer.h>

#include <QxService/QxThreadPool.h>
#include <QxService/QxConnect.h>

#include <QxCollection/QxCollection.h>
#include <QxCollection/QxCollectionIterator.h>

#include <QxCommon/QxException.h>
#include <QxCommon/QxExceptionCode.h>

#include <QxRestApi/QxRestApi.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

struct QxHttpServerDispatchSegment
{

   enum type_segment { _static, _variable, _variable_and_type, _variable_and_regexp, _wildcard };

   type_segment m_type;             //!< HTTP server dispatcher segment type
   QString m_path;                  //!< HTTP server dispatcher segment path (part of item path splitted by '/' character)
   qx_hash_result m_pathHash;       //!< HTTP server dispatcher segment path hash (for optimization)
   QString m_varName;               //!< HTTP server dispatcher segment variable name
   QString m_varType;               //!< HTTP server dispatcher segment variable type (or regular expression)

#if (QT_VERSION >= 0x050000)
   QRegularExpression m_regExp;     //!< HTTP server dispatcher segment regular expression
#else // (QT_VERSION >= 0x050000)
   QRegExp m_regExp;                //!< HTTP server dispatcher segment regular expression (Qt4 version)
#endif // (QT_VERSION >= 0x050000)

   QxHttpServerDispatchSegment() : m_type(_static), m_pathHash(0) { ; }
   ~QxHttpServerDispatchSegment() { ; }

   bool parse();
   bool check(const QString & path, qx_hash_result hash) const;
   void fillParam(const QString & path, QHash<QString, QVariant> & parameters) const;

};

struct QxHttpServerDispatchItem
{

   QString m_command;                                                   //!< HTTP server dispatcher item command (GET, POST, DELETE, PUT, etc...)
   qx_hash_result m_commandHash;                                        //!< HTTP server dispatcher item command hash (for optimization)
   bool m_commandWildcard;                                              //!< HTTP server dispatcher item wildcard command (means accept all commands)
   QString m_path;                                                      //!< HTTP server dispatcher item path (example : /foo/bar/<var1>/<var2:int>/*)
   QList<std::shared_ptr<QxHttpServerDispatchSegment> > m_segments;     //!< HTTP server dispatcher item list of segments (path splitted by '/' character)
   QxHttpServer::type_fct_custom_request_handler m_fct;                 //!< HTTP server dispatcher item callback (executed in its dedicated thread)

   QxHttpServerDispatchItem() : m_commandHash(0), m_commandWildcard(false) { ; }
   ~QxHttpServerDispatchItem() { ; }

   bool parse();

};

struct QxHttpServerDispatcher
{

   qx::QxCollection<QString, std::shared_ptr<QxHttpServerDispatchItem> > m_lstDispatchItems;    //!< HTTP server dispatcher items (associate url to callback)

   QxHttpServerDispatcher() { ; }
   ~QxHttpServerDispatcher() { ; }

   void dispatch(const QString & command, const QString & path, QxHttpServer::type_fct_custom_request_handler fct, long position);
   std::shared_ptr<QxHttpServerDispatchItem> find(qx::QxHttpRequest & request) const;

};

struct Q_DECL_HIDDEN QxHttpServer::QxHttpServerImpl
{

   typedef std::shared_ptr<QxHttpServer::type_fct_custom_request_handler> type_fct_ptr;

   QMutex m_mutex;                                          //!< Mutex => 'QxHttpServer' is thread-safe (callbacks can be changed even if server is running)
   qx::service::QxThreadPool_ptr m_pThreadPool;             //!< HTTP server is managed by a thread pool
   type_fct_ptr m_fctCustomRequestHandler;                  //!< Callback to manage requests and build responses (executed in its dedicated thread)
   std::unique_ptr<QxHttpServerDispatcher> m_pDispatcher;   //!< HTTP server dispatcher (each callback is executed in its dedicated thread)
   type_fct_ptr m_fctBeforeDispatching;                     //!< Callback function called before handling the request (executed in its dedicated thread), can be used for logging for example
   type_fct_ptr m_fctAfterDispatching;                      //!< Callback function called after handling the request and generating the response (executed in its dedicated thread), can be used for logging for example
   QAbstractEventDispatcher * m_pEventDispatcher;           //!< Can be used to optimize socket implementation (using epoll on Linux for example), for example : https://github.com/sjinks/qt_eventdispatcher_epoll or https://github.com/connectedtable/qeventdispatcher_epoll

   QxHttpServerImpl() : m_pDispatcher(new QxHttpServerDispatcher()), m_pEventDispatcher(NULL) { ; }
   ~QxHttpServerImpl() { ; }

};

QxHttpServer::QxHttpServer(QObject * parent /* = NULL */) : QObject(parent), m_pImpl(new QxHttpServerImpl())
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

#if (QT_VERSION >= 0x050000)
   if (m_pImpl->m_pEventDispatcher) { m_pImpl->m_pThreadPool->setEventDispatcher(m_pImpl->m_pEventDispatcher); }
#endif // (QT_VERSION >= 0x050000)

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
   QMutexLocker locker(& m_pImpl->m_mutex);
   if (! fct) { m_pImpl->m_fctCustomRequestHandler.reset(); return; }
   m_pImpl->m_fctCustomRequestHandler = std::make_shared<QxHttpServer::type_fct_custom_request_handler>();
   (* m_pImpl->m_fctCustomRequestHandler) = fct;
}

QxHttpServer & QxHttpServer::dispatch(const QString & command, const QString & path, QxHttpServer::type_fct_custom_request_handler fct, long position /* = -1 */)
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   m_pImpl->m_pDispatcher->dispatch(command.toUpper(), path, fct, position);
   return (* this);
}

void QxHttpServer::beforeDispatching(QxHttpServer::type_fct_custom_request_handler fct)
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   if (! fct) { m_pImpl->m_fctBeforeDispatching.reset(); return; }
   m_pImpl->m_fctBeforeDispatching = std::make_shared<QxHttpServer::type_fct_custom_request_handler>();
   (* m_pImpl->m_fctBeforeDispatching) = fct;
}

void QxHttpServer::afterDispatching(QxHttpServer::type_fct_custom_request_handler fct)
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   if (! fct) { m_pImpl->m_fctAfterDispatching.reset(); return; }
   m_pImpl->m_fctAfterDispatching = std::make_shared<QxHttpServer::type_fct_custom_request_handler>();
   (* m_pImpl->m_fctAfterDispatching) = fct;
}

void QxHttpServer::clearDispatcher()
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   m_pImpl->m_pDispatcher.reset(new QxHttpServerDispatcher());
}

#if (QT_VERSION >= 0x050000)
void QxHttpServer::setEventDispatcher(QAbstractEventDispatcher * pEventDispatcher)
{
   m_pImpl->m_pEventDispatcher = pEventDispatcher;
}
#endif // (QT_VERSION >= 0x050000)

void QxHttpServer::onError(const QString & err, qx::service::QxTransaction_ptr transaction)
{
   qx::QxHttpTransaction_ptr httpTransaction = std::dynamic_pointer_cast<qx::QxHttpTransaction>(transaction);
   if (transaction && (! httpTransaction)) { qAssertMsg(false, "[QxOrm] qx::QxHttpServer::onError", "unable to get HTTP transaction using std::dynamic_pointer_cast"); }
   Q_EMIT error(err, httpTransaction);
}

void QxHttpServer::onServerIsRunning(bool bIsRunning, qx::service::QxServer * pServer)
{
   Q_UNUSED(pServer);
   if (bIsRunning)
   {
      qx::service::QxConnect * serverSettings = qx::service::QxConnect::getSingleton();
      QString msg = "HTTP server is running (";
      msg += "port: " + QString::number(serverSettings->getPort());
      msg += ", threads: " + QString::number(serverSettings->getThreadCount());
#ifndef QT_NO_SSL
      msg += ", SSL: " + (serverSettings->getSSLEnabled() ? QString("enabled") : QString("disabled"));
#else // QT_NO_SSL
      msg += ", SSL: disabled";
#endif // QT_NO_SSL
      msg += ")";
      qDebug("[QxOrm] %s", qPrintable(msg));
   }
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
   // Check if transaction is valid
   qx::QxHttpTransaction_ptr httpTransaction = std::dynamic_pointer_cast<qx::QxHttpTransaction>(transaction);
   if (transaction && (! httpTransaction)) { qAssertMsg(false, "[QxOrm] qx::QxHttpServer::onCustomRequestHandler", "unable to get HTTP transaction using std::dynamic_pointer_cast"); return; }
   if (! httpTransaction) { qAssertMsg(false, "[QxOrm] qx::QxHttpServer::onCustomRequestHandler", "HTTP transaction is empty"); return; }

   // Get request and response instances
   qx::QxHttpRequest & request = httpTransaction->request();
   qx::QxHttpResponse & response = httpTransaction->response();

   // Get custom request handler + before/after dispatching callbacks (thread-safe)
   std::shared_ptr<QxHttpServer::type_fct_custom_request_handler> fctCustomHandler;
   std::shared_ptr<QxHttpServer::type_fct_custom_request_handler> fctBeforeDispatching;
   std::shared_ptr<QxHttpServer::type_fct_custom_request_handler> fctAfterDispatching;
   {
      QMutexLocker locker(& m_pImpl->m_mutex);
      fctCustomHandler = m_pImpl->m_fctCustomRequestHandler;
      fctBeforeDispatching = m_pImpl->m_fctBeforeDispatching;
      fctAfterDispatching = m_pImpl->m_fctAfterDispatching;
   }

   // Execute before dispatching callback
   if (fctBeforeDispatching && (* fctBeforeDispatching))
   {
      try { (* fctBeforeDispatching)(request, response); }
      catch (const qx::exception & x) { qx_bool xb = x.toQxBool(); httpTransaction->setMessageReturn(xb); }
      catch (const std::exception & e) { httpTransaction->setMessageReturn(qx_bool(500, e.what())); }
      catch (...) { httpTransaction->setMessageReturn(qx_bool(500, "[QxOrm] Unknown server error (before dispatching)")); }
   }

   // Get dispatcher item callback (thread-safe)
   std::shared_ptr<QxHttpServerDispatchItem> itemDispatch;
   {
      QMutexLocker locker(& m_pImpl->m_mutex);
      itemDispatch = m_pImpl->m_pDispatcher->find(request);
   }

   try
   {
      // Execute dispatcher item callback or custom request handler
      if (itemDispatch && itemDispatch->m_fct) { itemDispatch->m_fct(request, response); }
      else if (fctCustomHandler && (* fctCustomHandler)) { (* fctCustomHandler)(request, response); }
      else { httpTransaction->setMessageReturn(qx_bool(501, "[QxOrm] Not implemented : no route found for URL (" + request.command() + " - " + request.url().path() + ") : you must provide a request handler (callback) using qx::QxHttpServer::dispatch() or qx::QxHttpServer::setCustomRequestHandler() method")); }
   }
   catch (const qx::exception & x) { qx_bool xb = x.toQxBool(); httpTransaction->setMessageReturn(xb); }
   catch (const std::exception & e) { httpTransaction->setMessageReturn(qx_bool(500, e.what())); }
   catch (...) { httpTransaction->setMessageReturn(qx_bool(500, "[QxOrm] Unknown server error")); }

   // Execute after dispatching callback
   if (fctAfterDispatching && (* fctAfterDispatching))
   {
      try { (* fctAfterDispatching)(request, response); }
      catch (const qx::exception & x) { qx_bool xb = x.toQxBool(); httpTransaction->setMessageReturn(xb); }
      catch (const std::exception & e) { httpTransaction->setMessageReturn(qx_bool(500, e.what())); }
      catch (...) { httpTransaction->setMessageReturn(qx_bool(500, "[QxOrm] Unknown server error (after dispatching)")); }
   }
}

void QxHttpServerDispatcher::dispatch(const QString & command, const QString & path, QxHttpServer::type_fct_custom_request_handler fct, long position)
{
   QString key = command + "|" + path;
   if (m_lstDispatchItems.exist(key)) { m_lstDispatchItems.removeByKey(key); }
   if ((! fct) || (path.isEmpty()) || (command.isEmpty())) { return; }

   std::shared_ptr<QxHttpServerDispatchItem> item = std::make_shared<QxHttpServerDispatchItem>();
   item->m_command = command; item->m_path = ((path == "/") ? QString("/*") : path); item->m_fct = fct;
   if (! item->parse()) { qAssert(false); return; }
   if (item->m_segments.count() <= 0) { return; }
   if (position < 0) { m_lstDispatchItems.insert(key, item); }
   else { m_lstDispatchItems.insert(position, key, item); }
}

std::shared_ptr<QxHttpServerDispatchItem> QxHttpServerDispatcher::find(qx::QxHttpRequest & request) const
{
   // Check and prepare input data
   if (m_lstDispatchItems.count() <= 0) { return std::shared_ptr<QxHttpServerDispatchItem>(); }
   QString requestCommand = request.command().toUpper();
   qx_hash_result requestCommandHash = qHash(requestCommand);
   QString requestPath = request.url().path(); if (requestPath == "/") { requestPath = "/*"; }
#if (QT_VERSION >= 0x051400)
   QStringList requestSegments = requestPath.split("/", Qt::SkipEmptyParts);
#else // (QT_VERSION >= 0x051400)
   QStringList requestSegments = requestPath.split("/", QString::SkipEmptyParts);
#endif // (QT_VERSION >= 0x051400)
   QList<qx_hash_result> requestSegmentsHash; requestSegmentsHash.reserve(requestSegments.count());
   Q_FOREACH(QString data, requestSegments) { requestSegmentsHash.append(qHash(data)); }
   if (requestSegments.count() <= 0) { return std::shared_ptr<QxHttpServerDispatchItem>(); }

   // Iterate over all dispatcher items
   qx::QxCollectionIterator<QString, std::shared_ptr<QxHttpServerDispatchItem> > itr(m_lstDispatchItems);
   while (itr.next())
   {
      // Check dispatcher item command and segments count
      const std::shared_ptr<QxHttpServerDispatchItem> & item = itr.value(); if (! item) { qAssert(false); continue; }
      if ((item->m_commandHash != requestCommandHash) && (! item->m_commandWildcard)) { continue; }
      if (item->m_segments.count() > requestSegments.count()) { continue; }
      if (! item->m_fct) { continue; }

      // Iterate over all dispatcher item segments to check if everything matched
      bool bAllSegmentsOk = true;
      for (int i = 0; i < item->m_segments.count(); i++)
      {
         const std::shared_ptr<QxHttpServerDispatchSegment> & segment = item->m_segments.at(i); if (! segment) { qAssert(false); continue; }
         if (! segment->check(requestSegments.at(i), requestSegmentsHash.at(i))) { bAllSegmentsOk = false; break; }
      }
      if (! bAllSegmentsOk) { continue; }

      // Iterate over all dispatcher item segments to fill URL parameters
      QHash<QString, QVariant> parameters;
      for (int i = 0; i < item->m_segments.count(); i++)
      {
         const std::shared_ptr<QxHttpServerDispatchSegment> & segment = item->m_segments.at(i); if (! segment) { qAssert(false); continue; }
         segment->fillParam(requestSegments.at(i), parameters);
      }

      // We have found our dispatcher item
      request.dispatchParams() = parameters;
      return item;
   }
   return std::shared_ptr<QxHttpServerDispatchItem>();
}

bool QxHttpServerDispatchItem::parse()
{
   m_segments.clear();
   m_commandHash = qHash(m_command);
   m_commandWildcard = (m_command == "*");
#if (QT_VERSION >= 0x051400)
   QStringList segments = m_path.split("/", Qt::SkipEmptyParts);
#else // (QT_VERSION >= 0x051400)
   QStringList segments = m_path.split("/", QString::SkipEmptyParts);
#endif // (QT_VERSION >= 0x051400)
   Q_FOREACH(QString data, segments)
   {
      data = data.trimmed(); if (data.isEmpty()) { continue; }
      std::shared_ptr<QxHttpServerDispatchSegment> segment = std::make_shared<QxHttpServerDispatchSegment>();
      segment->m_path = data; if (! segment->parse()) { qAssert(false); return false; }
      m_segments.append(segment);
   }
   return true;
}

bool QxHttpServerDispatchSegment::parse()
{
   if (m_path.isEmpty()) { return true; }
   if (m_path.startsWith("<") && m_path.endsWith(">"))
   {
      QString path = m_path;
      path.remove(0, 1); path.chop(1);
      int pos = path.indexOf(":");
      if (pos >= 0)
      {
         m_varName = path.left(pos).trimmed();
         m_varType = path.mid(pos + 1).trimmed();
         m_type = QxHttpServerDispatchSegment::_variable_and_type;
         if (m_varType.startsWith("{") && m_varType.endsWith("}"))
         {
            m_varType.remove(0, 1); m_varType.chop(1);
            m_regExp.setPattern(m_varType);
            m_type = QxHttpServerDispatchSegment::_variable_and_regexp;
         }
      }
      else
      {
         m_varName = path.trimmed();
         m_type = QxHttpServerDispatchSegment::_variable;
      }
   }
   else if (m_path == "*")
   {
      m_type = QxHttpServerDispatchSegment::_wildcard;
   }
   else
   {
      m_type = QxHttpServerDispatchSegment::_static;
      m_pathHash = qHash(m_path);
   }
   return true;
}

bool QxHttpServerDispatchSegment::check(const QString & path, qx_hash_result hash) const
{
   bool result = false;
   switch (m_type)
   {
      case QxHttpServerDispatchSegment::_static:
         qAssert((hash != 0) && (m_pathHash != 0));
         result = (hash == m_pathHash);
         break;
      case QxHttpServerDispatchSegment::_variable:
         qAssert(! m_varName.isEmpty());
         result = (! path.isEmpty());
         break;
      case QxHttpServerDispatchSegment::_variable_and_type:
         qAssert(! m_varName.isEmpty() && ! m_varType.isEmpty());
         if ((m_varType == "int") || (m_varType == "long")) { qlonglong val = path.toLongLong(& result, 10); Q_UNUSED(val); }
         if ((m_varType == "float") || (m_varType == "double")) { double val = path.toDouble(& result); Q_UNUSED(val); }
         else if (m_varType == "string") { result = (! path.isEmpty()); }
         break;
      case QxHttpServerDispatchSegment::_variable_and_regexp:
         qAssert(! m_varName.isEmpty() && ! m_varType.isEmpty());
#if (QT_VERSION >= 0x050000)
         result = ((! path.isEmpty()) && (m_regExp.match(path).hasMatch()));
#else // (QT_VERSION >= 0x050000)
         result = ((! path.isEmpty()) && (m_regExp.exactMatch(path)));
#endif // (QT_VERSION >= 0x050000)
         break;
      case QxHttpServerDispatchSegment::_wildcard:
         result = true;
         break;
      default: break;
   }
   return result;
}

void QxHttpServerDispatchSegment::fillParam(const QString & path, QHash<QString, QVariant> & parameters) const
{
   QVariant vParamValue;
   bool bAddParam = true;
   switch (m_type)
   {
      case QxHttpServerDispatchSegment::_variable:             vParamValue = QVariant(path); break;
      case QxHttpServerDispatchSegment::_variable_and_type:    vParamValue = QVariant(path); break;
      case QxHttpServerDispatchSegment::_variable_and_regexp:  vParamValue = QVariant(path); break;
      default:                                                 bAddParam = false; break;
   }
   if ((bAddParam) && (! m_varName.isEmpty()))
   { parameters.insert(m_varName, vParamValue); }
}

void QxHttpServer::buildResponseStaticFile(qx::QxHttpRequest & request, qx::QxHttpResponse & response, const QString & serverPath, qlonglong chunkedSize /* = 0 */)
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
   if (chunkedSize > 0) { while (! file.atEnd()) { if (! response.writeChunked(file.read(chunkedSize))) { return; } } }
   else { response.data() = file.readAll(); }
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
