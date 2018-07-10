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

#if _QX_ENABLE_QT_NETWORK_DEPENDENCY
#ifndef _QX_SERVICE_CLIENT_ASYNC_H_
#define _QX_SERVICE_CLIENT_ASYNC_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxClientAsync.h
 * \author Lionel Marty
 * \ingroup QxService
 * \brief Provide a class helper to easily execute an asynchronous transaction using a multi-thread process
 */

#include <QxService/IxService.h>
#include <QxService/QxTransaction.h>

namespace qx {
namespace service {

/*!
 * \ingroup QxService
 * \brief qx::service::QxClientAsync : class helper to easily execute an asynchronous transaction using a multi-thread process
 *
 * <a href="http://www.qxorm.com/qxorm_en/tutorial_2.html" target="_blank">Click here to access to a tutorial to explain how to work with QxService module.</a>
 */
class QxClientAsync : public QThread
{

protected:

   IxService_ptr m_pService;     //!< Service to execute in thread
   QString m_sServiceMethod;     //!< Service method to call

public:

   QxClientAsync() : QThread() { ; }
   virtual ~QxClientAsync() { if (isRunning()) { qDebug("[QxOrm] qx::service::QxClientAsync thread is running : %s", "wait thread finished"); wait(); } }

   IxService_ptr getService() const                                  { return m_pService; }
   void setService(IxService_ptr service, const QString & method)    { qAssert(! isRunning()); m_pService = service; m_sServiceMethod = method; }

protected:

   virtual void run() { qx::service::execute_client(m_pService.get(), m_sServiceMethod); }

};

typedef boost::shared_ptr<QxClientAsync> QxClientAsync_ptr;

} // namespace service
} // namespace qx

#endif // _QX_SERVICE_CLIENT_ASYNC_H_
#endif // _QX_ENABLE_QT_NETWORK_DEPENDENCY
