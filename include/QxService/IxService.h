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

#ifdef _QX_ENABLE_QT_NETWORK
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

#include <QtCore/qdatastream.h>

#ifndef _QX_NO_JSON
#include <QtCore/qjsonvalue.h>
#endif // _QX_NO_JSON

#include <QxCommon/QxBool.h>

#include <QxRegister/QxRegisterInternalHelper.h>

#include <QxService/IxParameter.h>

#include <QxConvert/QxConvert.h>

namespace qx {
namespace service {
class QxTransaction;
class IxService;
} // namespace service
} // namespace qx

QX_DLL_EXPORT QDataStream & operator<< (QDataStream & stream, const qx::service::IxService & t) BOOST_USED;
QX_DLL_EXPORT QDataStream & operator>> (QDataStream & stream, qx::service::IxService & t) BOOST_USED;

#ifndef _QX_NO_JSON
namespace qx {
namespace cvt {
namespace detail {
template <> struct QxConvert_ToJson< qx::service::IxService >;
template <> struct QxConvert_FromJson< qx::service::IxService >;
QX_DLL_EXPORT QJsonValue QxConvert_ToJson_Helper(const qx::service::IxService & t, const QString & format) BOOST_USED;
QX_DLL_EXPORT qx_bool QxConvert_FromJson_Helper(const QJsonValue & j, qx::service::IxService & t, const QString & format) BOOST_USED;
} // namespace detail
} // namespace cvt
} // namespace qx
#endif // _QX_NO_JSON

namespace qx {
namespace service {

/*!
 * \ingroup QxService
 * \brief qx::service::IxService : common interface for all services defined with QxService module of QxOrm library
 *
 * <a href="http://www.qxorm.com/qxorm_en/tutorial_2.html" target="_blank">Click here to access to a tutorial to explain how to work with QxService module.</a>
 */
class QX_DLL_EXPORT IxService
{

   friend QDataStream & ::operator<< (QDataStream & stream, const qx::service::IxService & t);
   friend QDataStream & ::operator>> (QDataStream & stream, qx::service::IxService & t);

#ifndef _QX_NO_JSON
   friend struct qx::cvt::detail::QxConvert_ToJson< qx::service::IxService >;
   friend struct qx::cvt::detail::QxConvert_FromJson< qx::service::IxService >;
   friend QJsonValue qx::cvt::detail::QxConvert_ToJson_Helper(const qx::service::IxService & t, const QString & format);
   friend qx_bool qx::cvt::detail::QxConvert_FromJson_Helper(const QJsonValue & j, qx::service::IxService & t, const QString & format);
#endif // _QX_NO_JSON

protected:

   QString m_sServiceName;                            //!< Service name <=> class name
   QString m_sServiceMethodName;                      //!< Service method name to call
   IxParameter_ptr m_pInputParameter;                 //!< List of input parameters (request)
   IxParameter_ptr m_pOutputParameter;                //!< List of output parameters (reply)
   qx_bool m_bMessageReturn;                          //!< Message return to indicate if an error occured
   qx_shared_ptr<QxTransaction> m_pTransaction;       //!< Current transaction after executing service method

public:

   IxService();
   IxService(const QString & sServiceName);
   virtual ~IxService();

   QString getServiceName() const                              { return m_sServiceName; }
   QString getServiceMethodName() const                        { return m_sServiceMethodName; }
   IxParameter_ptr getInputParameter_BaseClass() const         { return m_pInputParameter; }
   IxParameter_ptr getOutputParameter_BaseClass() const        { return m_pOutputParameter; }
   qx_bool getMessageReturn() const                            { return m_bMessageReturn; }
   qx_shared_ptr<QxTransaction> getTransaction() const;

   void setServiceName(const QString & s)                               { qAssert(! s.isEmpty()); m_sServiceName = s; }
   void setServiceMethodName(const QString & s)                         { qAssert(! s.isEmpty()); m_sServiceMethodName = s; }
   void setInputParameter(IxParameter_ptr p)                            { m_pInputParameter = p; }
   void setOutputParameter(IxParameter_ptr p)                           { m_pOutputParameter = p; }
   void setMessageReturn(const qx_bool & b)                             { m_bMessageReturn = b; }
   void setMessageReturn(long l, const QString & s)                     { m_bMessageReturn = qx_bool(l, s); }
   void setTransaction(const qx_shared_ptr<QxTransaction> & p);

   bool isValid() const             { return m_bMessageReturn.getValue(); }
   bool isValidWithOutput() const   { return (isValid() && (m_pOutputParameter.get() != NULL)); }

   virtual void registerClass() const  { qDebug("[QxOrm] qx::service::IxService : %s", "need to override 'registerClass()' method"); qAssert(false); }
   virtual void onBeforeProcess()      { ; }
   virtual void onAfterProcess()       { ; }

};

typedef qx_shared_ptr<IxService> IxService_ptr;

} // namespace service
} // namespace qx

QX_REGISTER_INTERNAL_HELPER_HPP(QX_DLL_EXPORT, qx::service::IxService, 0)

#endif // _IX_SERVICE_H_
#endif // _QX_ENABLE_QT_NETWORK
