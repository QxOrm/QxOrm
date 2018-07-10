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

#include <QxCommon/QxConfig.h> // Need to include this file for the 'moc' process

#ifdef _QX_ENABLE_QT_NETWORK
#ifndef _QX_SERVICE_THREAD_H_
#define _QX_SERVICE_THREAD_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxThread.h
 * \author Lionel Marty
 * \ingroup QxService
 * \brief Thread to execute a transaction of QxService module
 */

#ifdef _QX_NO_PRECOMPILED_HEADER
#ifndef Q_MOC_RUN
#include <QxPrecompiled.h> // Need to include precompiled header for the generated moc file
#endif // Q_MOC_RUN
#endif // _QX_NO_PRECOMPILED_HEADER

#include <QtNetwork/qtcpsocket.h>

#ifndef Q_MOC_RUN
#include <QxService/QxTransaction.h>
#endif // Q_MOC_RUN

#if (QT_VERSION >= 0x050000)
#define QX_TYPE_SOCKET_DESC qintptr
#else // (QT_VERSION >= 0x050000)
#define QX_TYPE_SOCKET_DESC int
#endif // (QT_VERSION >= 0x050000)

namespace qx {
namespace service {

class QxThreadPool;

/*!
 * \ingroup QxService
 * \brief qx::service::QxThread : thread to execute a transaction of QxService module
 *
 * <a href="http://www.qxorm.com/qxorm_en/tutorial_2.html" target="_blank">Click here to access to a tutorial to explain how to work with QxService module.</a>
 */
class QX_DLL_EXPORT QxThread : public QThread
{

   Q_OBJECT

protected:

   QX_TYPE_SOCKET_DESC m_iSocketDescriptor;     //!< Socket descriptor to retrieve 'QTcpSocket'
   QxThreadPool * m_pThreadPool;                //!< Parent thread pool to set available
   QxTransaction_ptr m_pTransaction;            //!< Current service transaction
   bool m_bIsRunning;                           //!< Set this flag to 'false' to terminate thread
   QMutex m_mutex;                              //!< Mutex => 'QxThread' is thread-safe

public:

   QxThread(QxThreadPool * pool) : QThread(), m_iSocketDescriptor(0), m_pThreadPool(pool), m_bIsRunning(false) { qAssert(m_pThreadPool); }
   virtual ~QxThread() { clearData(); }

   bool isAvailable();
   void stop();
   void execute(QX_TYPE_SOCKET_DESC socketDescriptor);

   static void sleepCurrentThread(unsigned long msecs) { QThread::msleep(msecs); }

protected:

   virtual void run();

   void clearData();
   void doProcess(QTcpSocket & socket);
   qx_bool readSocket(QTcpSocket & socket);
   qx_bool writeSocket(QTcpSocket & socket);

Q_SIGNALS:

   void error(const QString & err, qx::service::QxTransaction_ptr transaction);
   void transactionStarted(qx::service::QxTransaction_ptr transaction);
   void transactionFinished(qx::service::QxTransaction_ptr transaction);

};

} // namespace service
} // namespace qx

#endif // _QX_SERVICE_THREAD_H_
#endif // _QX_ENABLE_QT_NETWORK
