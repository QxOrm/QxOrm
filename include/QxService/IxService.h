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
#ifndef _IX_SERVICE_H_
#define _IX_SERVICE_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file IxService.h
 * \author Lionel Marty
 * \ingroup QxService
 * \brief Common interface for all services defined with QxService module of QxOrm library
 */

#include <QxCommon/QxBool.h>

#include <QxRegister/QxRegisterInternalHelper.h>

#include <QxService/IxParameter.h>

namespace qx {
namespace service {

class QxTransaction;

/*!
 * \ingroup QxService
 * \brief qx::service::IxService : common interface for all services defined with QxService module of QxOrm library
 *
 * <a href="http://www.qxorm.com/qxorm_en/tutorial_2.html" target="_blank">Click here to access to a tutorial to explain how to work with QxService module.</a>
 */
class QX_DLL_EXPORT IxService
{

protected:

   QString m_sServiceName;                            //!< Service name <=> class name
   IxParameter_ptr m_pInputParameter;                 //!< List of input parameters (request)
   IxParameter_ptr m_pOutputParameter;                //!< List of output parameters (reply)
   qx_bool m_bMessageReturn;                          //!< Message return to indicate if an error occured
   boost::shared_ptr<QxTransaction> m_pTransaction;   //!< Current transaction after executing service method

public:

   IxService();
   IxService(const QString & sServiceName);
   virtual ~IxService();

   QString getServiceName() const                              { return m_sServiceName; }
   IxParameter_ptr getInputParameter_BaseClass() const         { return m_pInputParameter; }
   IxParameter_ptr getOutputParameter_BaseClass() const        { return m_pOutputParameter; }
   qx_bool getMessageReturn() const                            { return m_bMessageReturn; }
   boost::shared_ptr<QxTransaction> getTransaction() const;

   void setServiceName(const QString & s)                               { qAssert(! s.isEmpty()); m_sServiceName = s; }
   void setInputParameter(IxParameter_ptr p)                            { m_pInputParameter = p; }
   void setOutputParameter(IxParameter_ptr p)                           { m_pOutputParameter = p; }
   void setMessageReturn(const qx_bool & b)                             { m_bMessageReturn = b; }
   void setMessageReturn(long l, const QString & s)                     { m_bMessageReturn = qx_bool(l, s); }
   void setTransaction(const boost::shared_ptr<QxTransaction> & p);

   bool isValid() const             { return m_bMessageReturn.getValue(); }
   bool isValidWithOutput() const   { return (isValid() && (m_pOutputParameter.get() != NULL)); }

   virtual void registerClass() const { qDebug("[QxOrm] qx::service::IxService : %s", "need to override 'registerClass()' method"); qAssert(false); }

};

typedef boost::shared_ptr<IxService> IxService_ptr;

} // namespace service
} // namespace qx

QX_REGISTER_INTERNAL_HELPER_HPP(QX_DLL_EXPORT, qx::service::IxService, 0)

#endif // _IX_SERVICE_H_
#endif // _QX_ENABLE_QT_NETWORK_DEPENDENCY
