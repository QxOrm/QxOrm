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
#ifndef _QX_SERVICE_TRANSACTION_H_
#define _QX_SERVICE_TRANSACTION_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxTransaction.h
 * \author Lionel Marty
 * \ingroup QxService
 * \brief Transaction of QxService module (contains request from client and reply from server)
 */

#ifdef _QX_NO_PRECOMPILED_HEADER
#ifndef Q_MOC_RUN
#include <QxPrecompiled.h> // Need to include precompiled header for the generated moc file
#endif // Q_MOC_RUN
#endif // _QX_NO_PRECOMPILED_HEADER

#include <QtCore/qdatastream.h>

#ifndef _QX_NO_JSON
#include <QtCore/qjsonvalue.h>
#endif // _QX_NO_JSON

#include <QtNetwork/qtcpsocket.h>

#ifndef QT_NO_SSL
#include <QtNetwork/qsslsocket.h>
#include <QtNetwork/qsslconfiguration.h>
#include <QtNetwork/qsslcertificate.h>
#include <QtNetwork/qsslerror.h>
#include <QtNetwork/qsslkey.h>
#endif // QT_NO_SSL

#ifndef Q_MOC_RUN
#include <QxCommon/QxBool.h>
#include <QxRegister/QxRegisterInternalHelper.h>
#include <QxService/IxService.h>
#include <QxService/IxParameter.h>
#include <QxConvert/QxConvert.h>
#endif // Q_MOC_RUN

namespace qx {
namespace service {
class QxTransaction;
} // namespace service
} // namespace qx

QX_DLL_EXPORT QDataStream & operator<< (QDataStream & stream, const qx::service::QxTransaction & t) QX_USED;
QX_DLL_EXPORT QDataStream & operator>> (QDataStream & stream, qx::service::QxTransaction & t) QX_USED;

#ifndef _QX_NO_JSON
namespace qx {
namespace cvt {
namespace detail {
template <> struct QxConvert_ToJson< qx::service::QxTransaction >;
template <> struct QxConvert_FromJson< qx::service::QxTransaction >;
QX_DLL_EXPORT QJsonValue QxConvert_ToJson_Helper(const qx::service::QxTransaction & t, const QString & format) QX_USED;
QX_DLL_EXPORT qx_bool QxConvert_FromJson_Helper(const QJsonValue & j, qx::service::QxTransaction & t, const QString & format) QX_USED;
} // namespace detail
} // namespace cvt
} // namespace qx
#endif // _QX_NO_JSON

namespace qx {
namespace service {

/*!
 * \ingroup QxService
 * \brief qx::service::QxTransaction : transaction of QxService module (contains request from client and reply from server)
 *
 * <a href="https://www.qxorm.com/qxorm_en/tutorial_2.html" target="_blank">Click here to access to a tutorial to explain how to work with QxService module.</a>
 */
class QX_DLL_EXPORT QxTransaction : public QObject
{

   Q_OBJECT
   QX_REGISTER_FRIEND_CLASS(qx::service::QxTransaction)

   friend QX_DLL_EXPORT QDataStream & ::operator<< (QDataStream & stream, const qx::service::QxTransaction & t);
   friend QX_DLL_EXPORT QDataStream & ::operator>> (QDataStream & stream, qx::service::QxTransaction & t);

#ifndef _QX_NO_JSON
   friend struct qx::cvt::detail::QxConvert_ToJson< qx::service::QxTransaction >;
   friend struct qx::cvt::detail::QxConvert_FromJson< qx::service::QxTransaction >;
   friend QX_DLL_EXPORT QJsonValue qx::cvt::detail::QxConvert_ToJson_Helper(const qx::service::QxTransaction & t, const QString & format);
   friend QX_DLL_EXPORT qx_bool qx::cvt::detail::QxConvert_FromJson_Helper(const QJsonValue & j, qx::service::QxTransaction & t, const QString & format);
#endif // _QX_NO_JSON

public:

   enum connection_status { conn_none, conn_keep_alive, conn_close };

protected:

   QString              m_sTransactionId;                   //!< Transaction id (GUID)
   quint32              m_uiInputTransactionSize;           //!< Input transaction size
   quint32              m_uiOutputTransactionSize;          //!< Output transaction size
   QDateTime            m_dtTransactionBegin;               //!< Date-time transaction begin
   QDateTime            m_dtTransactionRequestSent;         //!< Date-time transaction request sent
   QDateTime            m_dtTransactionRequestReceived;     //!< Date-time transaction request received
   QDateTime            m_dtTransactionReplySent;           //!< Date-time transaction reply sent
   QDateTime            m_dtTransactionReplyReceived;       //!< Date-time transaction reply received
   QDateTime            m_dtTransactionEnd;                 //!< Date-time transaction end
   QString              m_sIpSource;                        //!< Ip address source (request)
   QString              m_sIpTarget;                        //!< Ip address target (reply)
   long                 m_lPortSource;                      //!< Port number source (request)
   long                 m_lPortTarget;                      //!< Port number target (reply)
   QString              m_sServiceName;                     //!< Service name to create using 'QxFactory'
   QString              m_sServiceMethod;                   //!< Service method to call to execute transaction
   qx_bool              m_bMessageReturn;                   //!< Message return to indicate if an error occured
   IxParameter_ptr      m_pInputParameter;                  //!< List of input parameters (request)
   IxParameter_ptr      m_pOutputParameter;                 //!< List of output parameters (reply)
   IxService_ptr        m_pServiceInstance;                 //!< Service instance created by 'm_sServiceName' property
   connection_status    m_eForceConnectionStatus;           //!< Sometimes we have to force connection status

public:

   QxTransaction() : QObject(), m_uiInputTransactionSize(0), m_uiOutputTransactionSize(0), m_lPortSource(0), m_lPortTarget(0), m_eForceConnectionStatus(conn_none) { ; }
   virtual ~QxTransaction() { ; }
   virtual void clear();

   QString getTransactionId() const                      { return m_sTransactionId; }
   quint32 getInputTransactionSize() const               { return m_uiInputTransactionSize; }
   quint32 getOutputTransactionSize() const              { return m_uiOutputTransactionSize; }
   QDateTime getTransactionBegin() const                 { return m_dtTransactionBegin; }
   QDateTime getTransactionRequestSent() const           { return m_dtTransactionRequestSent; }
   QDateTime getTransactionRequestReceived() const       { return m_dtTransactionRequestReceived; }
   QDateTime getTransactionReplySent() const             { return m_dtTransactionReplySent; }
   QDateTime getTransactionReplyReceived() const         { return m_dtTransactionReplyReceived; }
   QDateTime getTransactionEnd() const                   { return m_dtTransactionEnd; }
   QString getIpSource() const                           { return m_sIpSource; }
   QString getIpTarget() const                           { return m_sIpTarget; }
   long getPortSource() const                            { return m_lPortSource; }
   long getPortTarget() const                            { return m_lPortTarget; }
   QString getServiceName() const                        { return m_sServiceName; }
   QString getServiceMethod() const                      { return m_sServiceMethod; }
   qx_bool getMessageReturn() const                      { return m_bMessageReturn; }
   IxParameter_ptr getInputParameter() const             { return m_pInputParameter; }
   IxParameter_ptr getOutputParameter() const            { return m_pOutputParameter; }
   connection_status getForceConnectionStatus() const    { return m_eForceConnectionStatus; }

   void setTransactionId(const QString & s)                    { m_sTransactionId = s; }
   void setInputTransactionSize(quint32 ui)                    { m_uiInputTransactionSize = ui; }
   void setOutputTransactionSize(quint32 ui)                   { m_uiOutputTransactionSize = ui; }
   void setTransactionBegin(const QDateTime & dt)              { m_dtTransactionBegin = dt; }
   void setTransactionRequestSent(const QDateTime & dt)        { m_dtTransactionRequestSent = dt; }
   void setTransactionRequestReceived(const QDateTime & dt)    { m_dtTransactionRequestReceived = dt; }
   void setTransactionReplySent(const QDateTime & dt)          { m_dtTransactionReplySent = dt; }
   void setTransactionReplyReceived(const QDateTime & dt)      { m_dtTransactionReplyReceived = dt; }
   void setTransactionEnd(const QDateTime & dt)                { m_dtTransactionEnd = dt; }
   void setIpSource(const QString & s)                         { m_sIpSource = s; }
   void setIpTarget(const QString & s)                         { m_sIpTarget = s; }
   void setPortSource(long l)                                  { m_lPortSource = l; }
   void setPortTarget(long l)                                  { m_lPortTarget = l; }
   void setServiceName(const QString & s)                      { m_sServiceName = s; }
   void setServiceMethod(const QString & s)                    { m_sServiceMethod = s; }
   void setMessageReturn(const qx_bool & b)                    { m_bMessageReturn = b; }
   void setInputParameter(IxParameter_ptr p)                   { m_pInputParameter = p; }
   void setOutputParameter(IxParameter_ptr p)                  { m_pOutputParameter = p; }
   void setForceConnectionStatus(connection_status e)          { m_eForceConnectionStatus = e; }

   virtual void executeServer();
   virtual qx_bool writeSocketServer(QTcpSocket & socket);
   virtual qx_bool readSocketServer(QTcpSocket & socket);

   virtual void executeClient(IxService * pService, const QString & sMethod);
   virtual qx_bool writeSocketClient(QTcpSocket & socket);
   virtual qx_bool readSocketClient(QTcpSocket & socket);

   QString getInfos() const;

protected:

#ifndef QT_NO_SSL
   QSslSocket * initSocketSSL();
   bool checkSocketSSLEncrypted(QTcpSocket * socket);
#endif // QT_NO_SSL

Q_SIGNALS:

   void onCustomRequestHandler();

};

typedef std::shared_ptr<QxTransaction> QxTransaction_ptr;
QX_DLL_EXPORT void execute_client(IxService * pService, const QString & sMethod);

} // namespace service
} // namespace qx

QX_REGISTER_INTERNAL_HELPER_HPP(QX_DLL_EXPORT, qx::service::QxTransaction, 0)

#endif // _QX_SERVICE_TRANSACTION_H_
#endif // _QX_ENABLE_QT_NETWORK
