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
#ifndef _QX_SERVICE_THREAD_POOL_H_
#define _QX_SERVICE_THREAD_POOL_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxThreadPool.h
 * \author Lionel Marty
 * \ingroup QxService
 * \brief Thread pool to manage list of threads for executing all transactions of QxService module
 */

#ifdef _QX_NO_PRECOMPILED_HEADER
#ifndef Q_MOC_RUN
#include <QxPrecompiled.h> // Need to include precompiled header for the generated moc file
#endif // Q_MOC_RUN
#endif // _QX_NO_PRECOMPILED_HEADER

#include <QtCore/qqueue.h>

#ifndef Q_MOC_RUN
#include <QxService/QxTransaction.h>
#include <QxService/QxServer.h>
#endif // Q_MOC_RUN

namespace qx {
namespace service {

class QxThread;

/*!
 * \ingroup QxService
 * \brief qx::service::QxThreadPool : thread-safe thread pool to manage list of threads for executing all transactions of QxService module
 *
 * <a href="http://www.qxorm.com/qxorm_en/tutorial_2.html" target="_blank">Click here to access to a tutorial to explain how to work with QxService module.</a>
 */
class QX_DLL_EXPORT QxThreadPool : public QThread
{

   Q_OBJECT

protected:

   QList<QxThread *> m_lstAllServices;       //!< List of all services created by 'QxThreadPool'
   QQueue<QxThread *> m_lstAvailable;        //!< List of services available to execute process
   bool m_bIsRunning;                        //!< Flag to indicate if thread is running
   QMutex m_mutex;                           //!< Mutex => 'QxThreadPool' is thread-safe

public:

   QxThreadPool() : QThread(), m_bIsRunning(false) { ; }
   virtual ~QxThreadPool() { if (isRunning()) { qDebug("[QxOrm] qx::service::QxThreadPool thread is running : %s", "quit and wait"); quit(); wait(); } }

   QxThread * getAvailable();
   void setAvailable(QxThread * p);
   void raiseError(const QString & err, QxTransaction_ptr transaction);

   void sleepThread(unsigned long msecs) { QThread::msleep(msecs); }

protected:

   virtual void run();

   void runServer();
   void initServices();
   void clearServices();

Q_SIGNALS:

   void error(const QString & err, qx::service::QxTransaction_ptr transaction);
   void transactionStarted(qx::service::QxTransaction_ptr transaction);
   void transactionFinished(qx::service::QxTransaction_ptr transaction);
   void serverIsRunning(bool bIsRunning, qx::service::QxServer * pServer);

};

typedef qx_shared_ptr<QxThreadPool> QxThreadPool_ptr;

} // namespace service
} // namespace qx

#endif // _QX_SERVICE_THREAD_POOL_H_
#endif // _QX_ENABLE_QT_NETWORK
