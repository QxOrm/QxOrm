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

#include <QtCore/qcoreapplication.h>

#include <QxService/QxThread.h>
#include <QxService/QxThreadPool.h>
#include <QxService/QxTools.h>
#include <QxService/QxConnect.h>

#include <QxHttpServer/QxHttpTransaction.h>

#include <QxCommon/QxException.h>
#include <QxCommon/QxExceptionCode.h>

#include <QxMemLeak/mem_leak.h>

#ifndef QT_NO_SSL
#ifndef QT_NO_OPENSSL
#define QX_THREAD_SSL
#endif // QT_NO_OPENSSL
#endif // QT_NO_SSL
#ifndef QX_THREAD_SSL
#define QX_THREAD_NO_SSL
#endif // QX_THREAD_SSL

namespace qx {
namespace service {

void QxThread::init()
{
   QObject::connect(this, SIGNAL(incomingConnection()), this, SLOT(onIncomingConnection()));
}

bool QxThread::isAvailable()
{
   QMutexLocker locker(& m_mutex);
   return ((m_pTransaction.get() == NULL) && (m_iSocketDescriptor == 0));
}

void QxThread::stop()
{
   QMutexLocker locker(& m_mutex);
   m_bIsStopped = true;
   if (m_iSocketDescriptor == 0) { quit(); }
}

void QxThread::wait()
{
   if (m_pThread) { m_pThread->wait(); }
}

void QxThread::quit()
{
   Q_EMIT finished();
   if (m_pThread) { m_pThread->quit(); }
}

bool QxThread::hasBeenStopped()
{
   QMutexLocker locker(& m_mutex);
   return m_bIsStopped;
}

void QxThread::execute(QX_TYPE_SOCKET_DESC socketDescriptor)
{
   QMutexLocker locker(& m_mutex);
   if (m_bIsStopped) { return; }
   if (m_iSocketDescriptor != 0) { qAssert(false); return; }
   m_iSocketDescriptor = socketDescriptor;
   if (m_iSocketDescriptor != 0) { Q_EMIT incomingConnection(); }
}

QX_TYPE_SOCKET_DESC QxThread::getSocketDescriptor()
{
   QMutexLocker locker(& m_mutex);
   return m_iSocketDescriptor;
}

void QxThread::onIncomingConnection()
{
   if (getSocketDescriptor() == 0) { qAssert(false); return; }
   if (hasBeenStopped()) { quit(); return; }
   std::unique_ptr<QTcpSocket> socket;
   m_bIsDisconnected = false;

#ifndef QX_THREAD_NO_SSL
   bool bSSLEnabled = QxConnect::getSingleton()->getSSLEnabled();
   if (bSSLEnabled) { socket.reset(initSocketSSL()); }
   else { socket.reset(new QTcpSocket()); }
#else // QX_THREAD_NO_SSL
   socket.reset(new QTcpSocket());
#endif // QX_THREAD_NO_SSL

   QObject::connect(socket.get(), SIGNAL(disconnected()), this, SLOT(onSocketDisconnected()));
   QObject::connect(socket.get(), SIGNAL(readyRead()), this, SLOT(onSocketReadyRead()));

   if (socket->setSocketDescriptor(getSocketDescriptor()))
   {
#ifndef QX_THREAD_NO_SSL
      if ((! bSSLEnabled) || (checkSocketSSLEncrypted(socket.get())))
      {
#endif // QX_THREAD_NO_SSL
         do { doProcess(* socket); }
         while (checkKeepAlive(* socket) && (! hasBeenStopped()) && (! m_bIsDisconnected));
         socket->disconnectFromHost();
         if ((! m_bIsDisconnected) && (socket->state() != QAbstractSocket::UnconnectedState))
         { socket->waitForDisconnected(QxConnect::getSingleton()->getMaxWait()); }
#ifndef QX_THREAD_NO_SSL
      }
      else { Q_EMIT error("[QxOrm] SSL socket encrypted error : " + socket->errorString(), QxTransaction_ptr()); }
#endif // QX_THREAD_NO_SSL
   }
   else { Q_EMIT error("[QxOrm] invalid socket descriptor : cannot start transaction (" + socket->errorString() + ")", QxTransaction_ptr()); }

   clearData();
   if (m_pThreadPool) { m_pThreadPool->setAvailable(this); }
   if (hasBeenStopped()) { quit(); }
}

bool QxThread::checkKeepAlive(QTcpSocket & socket)
{
   if (m_pTransaction && (m_pTransaction->getForceConnectionStatus() == qx::service::QxTransaction::conn_close)) { return false; }
   long lKeepAlive = QxConnect::getSingleton()->getKeepAlive();
   if (lKeepAlive == 0) { return false; }

   long lCurrRetry = 0;
   long lMaxRetry = lKeepAlive;
   do
   {
      if (socket.waitForReadyRead(1)) { return true; }
      if (socket.bytesAvailable() > 0) { return true; }
      if (hasBeenStopped() || m_bIsDisconnected) { return false; }
      QCoreApplication::processEvents();
      lCurrRetry++;
   }
   while ((lMaxRetry == -1) || (lCurrRetry < lMaxRetry));
   return false;
}

#ifndef QX_THREAD_NO_SSL

bool QxThread::checkSocketSSLEncrypted(QTcpSocket * socket)
{
   if (! QxConnect::getSingleton()->getSSLEnabled()) { qAssert(false); return false; }
   QSslSocket * ssl = static_cast<QSslSocket *>(socket);
   ssl->startServerEncryption();
   return ssl->waitForEncrypted(QxConnect::getSingleton()->getMaxWait());
}

QSslSocket * QxThread::initSocketSSL()
{
   QSslSocket * socket = new QSslSocket();
   QxConnect * settings = QxConnect::getSingleton();
   QSslConfiguration config = settings->getSSLConfiguration();
   if (config.isNull()) { config = QSslConfiguration::defaultConfiguration(); }
   QList<QSslCertificate> allCACertificates = settings->getSSLCACertificates();
   config.setCaCertificates(allCACertificates); // because QSslSocket::setCaCertificates() is obsolete

   QObject::connect(socket, SIGNAL(encrypted()), this, SLOT(onSocketSSLEncrypted()));
   QObject::connect(socket, SIGNAL(sslErrors(const QList<QSslError> &)), this, SLOT(onSocketSSLErrors(const QList<QSslError> &)));
   QObject::connect(socket, SIGNAL(peerVerifyError(const QSslError &)), this, SLOT(onSocketSSLPeerVerifyError(const QSslError &)));

   socket->setSslConfiguration(config);
   socket->ignoreSslErrors(settings->getSSLIgnoreErrors());
   socket->setProtocol(settings->getSSLProtocol());
   socket->setPeerVerifyName(settings->getSSLPeerVerifyName());
   socket->setPeerVerifyMode(settings->getSSLPeerVerifyMode());
   socket->setPeerVerifyDepth(settings->getSSLPeerVerifyDepth());
   socket->setPrivateKey(settings->getSSLPrivateKey());
   socket->setLocalCertificate(settings->getSSLLocalCertificate());

   return socket;
}

#endif // QX_THREAD_NO_SSL

void QxThread::clearData()
{
   QMutexLocker locker(& m_mutex);
   m_pTransaction.reset();
   m_iSocketDescriptor = 0;
   m_bIsDisconnected = false;
}

void QxThread::doProcess(QTcpSocket & socket)
{
   long lMaxWait = QxConnect::getSingleton()->getMaxWait();
   bool bModeHTTP = QxConnect::getSingleton()->getModeHTTP();
   if (bModeHTTP) { m_pTransaction = std::make_shared<qx::QxHttpTransaction>(); }
   else { m_pTransaction = std::make_shared<QxTransaction>(); }
   QObject::connect(m_pTransaction.get(), SIGNAL(onCustomRequestHandler()), this, SLOT(onCustomRequestHandler()), Qt::DirectConnection);

   qx_bool bReadOk = m_pTransaction->readSocketServer(socket);
   if (! bReadOk) { Q_EMIT error(QString("[QxOrm] unable to read request from socket : '") + bReadOk.getDesc() + QString("'"), QxTransaction_ptr()); return; }
   if (hasBeenStopped() || m_bIsDisconnected) { return; }
   socket.readAll();

   Q_EMIT transactionStarted(m_pTransaction);
   try { m_pTransaction->executeServer(); }
   catch (const qx::exception & x) { qx_bool xb = x.toQxBool(); m_pTransaction->setMessageReturn(xb); }
   catch (const std::exception & e) { m_pTransaction->setMessageReturn(qx_bool(QX_ERROR_UNKNOWN, e.what())); }
   catch (...) { m_pTransaction->setMessageReturn(qx_bool(QX_ERROR_UNKNOWN, "unknown error")); }
   if (hasBeenStopped() || m_bIsDisconnected) { return; }

   qx_bool bWriteOk = m_pTransaction->writeSocketServer(socket);
   if (! bWriteOk) { Q_EMIT error(QString("[QxOrm] unable to write reply to socket : '") + bWriteOk.getDesc() + QString("'"), m_pTransaction); }

   long lCurrRetry = 0;
   while ((socket.bytesToWrite() > 0) && ((lMaxWait == -1) || (lCurrRetry < lMaxWait)) && (! hasBeenStopped()) && (! m_bIsDisconnected))
   { socket.waitForBytesWritten(1); QCoreApplication::processEvents(); lCurrRetry++; }
   Q_EMIT transactionFinished(m_pTransaction);
}

void QxThread::onCustomRequestHandler()
{
   if (m_pTransaction) { Q_EMIT customRequestHandler(m_pTransaction); }
   else { qAssert(false); }
}

void QxThread::onSocketDisconnected()
{
   m_bIsDisconnected = true;
}

void QxThread::onSocketReadyRead()
{
   /* Nothing here */
}

#ifndef QX_THREAD_NO_SSL

void QxThread::onSocketSSLEncrypted()
{
   /* Nothing here */
}

void QxThread::onSocketSSLErrors(const QList<QSslError> & errors)
{
   for (int i = 0; i < errors.count(); i++)
   {
      QSslError err = errors.at(i); QString msg = err.errorString();
      qDebug("[QxOrm] qx::service::QxThread::onSocketSSLErrors() : %s", qPrintable(msg));
   }
}

void QxThread::onSocketSSLPeerVerifyError(const QSslError & error)
{
   QString msg = error.errorString();
   qDebug("[QxOrm] qx::service::QxThread::onSocketSSLPeerVerifyError() : %s", qPrintable(msg));
}

#endif // QX_THREAD_NO_SSL

} // namespace service
} // namespace qx

#endif // _QX_ENABLE_QT_NETWORK
