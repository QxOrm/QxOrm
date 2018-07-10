/****************************************************************************
**
** http://www.qxorm.com/
** http://sourceforge.net/projects/qxorm/
** Original file by Lionel Marty
**
** This file is part of the QxOrm library
**
** This software is provided 'as-is', without any express or implied
** warranty. In no event will the authors be held liable for any
** damages arising from the use of this software.
**
** GNU Lesser General Public License Usage
** This file must be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file 'license.lgpl.txt' included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you have questions regarding the use of this file, please contact :
** contact@qxorm.com
**
****************************************************************************/

#include <QxCommon/QxConfig.h> // Need to include this file for the 'moc' process

#if _QX_ENABLE_QT_NETWORK_DEPENDENCY
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

#include <QtCore/qqueue.h>

#include <QxService/QxTransaction.h>
#include <QxService/QxServer.h>

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
{ Q_OBJECT

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

typedef boost::shared_ptr<QxThreadPool> QxThreadPool_ptr;

} // namespace service
} // namespace qx

#endif // _QX_SERVICE_THREAD_POOL_H_
#endif // _QX_ENABLE_QT_NETWORK_DEPENDENCY
