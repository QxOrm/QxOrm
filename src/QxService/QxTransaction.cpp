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

#include <QxPrecompiled.h>

#include <QtCore/quuid.h>

#include <QtNetwork/qhostaddress.h>

#include <QxService/QxTransaction.h>
#include <QxService/QxConnect.h>
#include <QxService/QxTools.h>

#include <QxRegister/QxClassX.h>

#include <QxFactory/QxFactoryX.h>

#include <QxCommon/QxException.h>
#include <QxCommon/QxExceptionCode.h>

#include <QxSerialize/QxSerializeQJson.h>
#include <QxSerialize/QJson/QxSerializeQJson_QxTransaction.h>

#include <QxMemLeak/mem_leak.h>

QX_REGISTER_INTERNAL_HELPER_START_FILE_CPP(qx::service::QxTransaction)

namespace qx {
namespace service {

void QxTransaction::executeServer()
{
   if (m_sServiceName.isEmpty()) { m_bMessageReturn = qx_bool(QX_ERROR_SERVICE_NOT_SPECIFIED, "[QxOrm] empty service name => cannot instantiate service and execute process"); return; }
   if (m_sServiceMethod.isEmpty()) { m_bMessageReturn = qx_bool(QX_ERROR_SERVICE_NOT_SPECIFIED, "[QxOrm] empty service method => cannot execute process"); return; }

   qx::service::IxService * ptr = qx::create_nude_ptr<qx::service::IxService>(m_sServiceName);
   if (ptr == NULL) { m_bMessageReturn = qx_bool(QX_ERROR_SERVICE_INVALID, "[QxOrm] invalid service name => cannot instantiate service and execute process"); return; }
   m_pServiceInstance = IxService_ptr(ptr);
   m_pServiceInstance->registerClass();
   m_pServiceInstance->setInputParameter(m_pInputParameter);
   m_pServiceInstance->setServiceMethodName(m_sServiceMethod);

   try
   {
      m_pServiceInstance->onBeforeProcess();
      qx_bool bInvokeOk = qx::QxClassX::invoke(m_sServiceName, m_sServiceMethod, (* m_pServiceInstance));
      if (! bInvokeOk) { m_bMessageReturn = qx_bool(QX_ERROR_SERVICE_INVALID, "[QxOrm] invalid service method => cannot execute process"); return; }
      m_pOutputParameter = m_pServiceInstance->getOutputParameter_BaseClass();
      m_bMessageReturn = m_pServiceInstance->getMessageReturn();
      m_pServiceInstance->onAfterProcess();
   }
   catch (const qx::exception & x) { m_bMessageReturn = x.toQxBool(); }
   catch (const std::exception & e) { QString msg(e.what()); if (msg.isEmpty()) { msg = "[QxOrm] unexpected error occured executing service method"; }; m_bMessageReturn = qx_bool(QX_ERROR_UNKNOWN, msg); }
   catch (...) { m_bMessageReturn = qx_bool(QX_ERROR_UNKNOWN, "[QxOrm] unknown error occured executing service method"); }
   m_pServiceInstance.reset();
}

void QxTransaction::executeClient(IxService * pService, const QString & sMethod)
{
   if ((pService == NULL) || sMethod.isEmpty()) { qAssert(false); return; }
   if (pService->getServiceName().isEmpty()) { pService->setMessageReturn(qx_bool(QX_ERROR_SERVICE_NOT_SPECIFIED, "[QxOrm] empty service name")); return; }
   pService->registerClass();

   QTcpSocket socket;
   QString serverName = QxConnect::getSingleton()->getIp();
   long serverPort = QxConnect::getSingleton()->getPort();
   socket.connectToHost(serverName, serverPort);
   if (! socket.waitForConnected(QxConnect::getSingleton()->getMaxWait()))
   { pService->setMessageReturn(qx_bool(QX_ERROR_SERVER_NOT_FOUND, "[QxOrm] unable to connect to server")); return; }

   if (m_sTransactionId.isEmpty())
   { setTransactionId(QUuid::createUuid().toString()); }

   setIpSource(socket.localAddress().toString());
   setPortSource(socket.localPort());
   setIpTarget(serverName);
   setPortTarget(serverPort);
   setServiceName(pService->getServiceName());
   setServiceMethod(sMethod);
   setTransactionBegin(QDateTime::currentDateTime());
   setInputParameter(pService->getInputParameter_BaseClass());

   qx_bool bWriteOk = writeSocket(socket);
   if (! bWriteOk) { pService->setMessageReturn(qx_bool(QX_ERROR_SERVICE_WRITE_ERROR, QString("[QxOrm] unable to write request to socket : '") + bWriteOk.getDesc() + QString("'"))); return; }
   qx_bool bReadOk = readSocket(socket);
   if (! bReadOk) { pService->setMessageReturn(qx_bool(QX_ERROR_SERVICE_READ_ERROR, QString("[QxOrm] unable to read reply from socket : '") + bReadOk.getDesc() + QString("'"))); return; }

   pService->setOutputParameter(getOutputParameter());
   pService->setMessageReturn(getMessageReturn());
   setTransactionEnd(QDateTime::currentDateTime());
   socket.disconnectFromHost();
   if (socket.state() != QAbstractSocket::UnconnectedState)
   { socket.waitForDisconnected(QxConnect::getSingleton()->getMaxWait()); }
}

qx_bool QxTransaction::writeSocket(QTcpSocket & socket)
{
   quint32 uiTransactionSize = 0;
   qx_bool bWriteOk = QxTools::writeSocket(socket, (* this), uiTransactionSize);
   if (! bWriteOk) { return bWriteOk; }
   setTransactionRequestSent(QDateTime::currentDateTime());
   setInputTransactionSize(uiTransactionSize);
   return bWriteOk;
}

qx_bool QxTransaction::readSocket(QTcpSocket & socket)
{
   QxTransaction tmp;
   quint32 uiTransactionSize = 0;
   qx_bool bReadOk = QxTools::readSocket(socket, tmp, uiTransactionSize);
   if (! bReadOk) { return bReadOk; }
   setTransactionReplyReceived(QDateTime::currentDateTime());
   setTransactionRequestReceived(tmp.getTransactionRequestReceived());
   setTransactionReplySent(tmp.getTransactionReplySent());
   setOutputParameter(tmp.getOutputParameter());
   setMessageReturn(tmp.getMessageReturn());
   setOutputTransactionSize(uiTransactionSize);
   return bReadOk;
}

QString QxTransaction::getInfos() const
{
   QString infos;
#ifndef _QX_NO_JSON
   infos += "transaction_content (JSON format) :\n" + qx::serialization::json::to_string(* this) + "\n";
#else // _QX_NO_JSON
   infos += "transaction_id :\t\t" + m_sTransactionId + "\n";
   infos += "input_transaction_size :\t\t" + QString::number(m_uiInputTransactionSize) + "\n";
   infos += "output_transaction_size :\t\t" + QString::number(m_uiOutputTransactionSize) + "\n";
   infos += "dt_transaction_begin :\t\t" + m_dtTransactionBegin.toString("yyyyMMddhhmmsszzz") + "\n";
   infos += "dt_transaction_request_sent :\t\t" + m_dtTransactionRequestSent.toString("yyyyMMddhhmmsszzz") + "\n";
   infos += "dt_transaction_request_received :\t\t" + m_dtTransactionRequestReceived.toString("yyyyMMddhhmmsszzz") + "\n";
   infos += "dt_transaction_reply_sent :\t\t" + m_dtTransactionReplySent.toString("yyyyMMddhhmmsszzz") + "\n";
   infos += "dt_transaction_reply_received :\t\t" + m_dtTransactionReplyReceived.toString("yyyyMMddhhmmsszzz") + "\n";
   infos += "dt_transaction_end :\t\t" + m_dtTransactionEnd.toString("yyyyMMddhhmmsszzz") + "\n";
   infos += "ip_source :\t\t" + m_sIpSource + "\n";
   infos += "ip_target :\t\t" + m_sIpTarget + "\n";
   infos += "port_source :\t\t" + QString::number(m_lPortSource) + "\n";
   infos += "port_target :\t\t" + QString::number(m_lPortTarget) + "\n";
   infos += "service_name :\t\t" + m_sServiceName + "\n";
   infos += "service_method :\t\t" + m_sServiceMethod + "\n";
   infos += "message_return :\t\t" + (m_bMessageReturn ? QString("1") : QString("0")) + (m_bMessageReturn.getDesc().isEmpty() ? QString() : (QString(", ") + m_bMessageReturn.getDesc())) + ((m_bMessageReturn.getValue() == 0) ? QString() : (QString(", value=") + QString::number(m_bMessageReturn.getValue()))) + "\n";
#endif // _QX_NO_JSON
   return infos;
}

void execute_client(IxService * pService, const QString & sMethod)
{
   if (pService == NULL) { qAssert(false); return; }
   if (sMethod.isEmpty()) { qAssert(false); return; }
   QxTransaction_ptr pTransaction;
   pTransaction.reset(new QxTransaction());
   pService->setTransaction(pTransaction);
   pTransaction->executeClient(pService, sMethod);
   pTransaction->setMessageReturn(pService->getMessageReturn());
}

} // namespace service
} // namespace qx

#ifdef _QX_ENABLE_BOOST_SERIALIZATION

namespace boost {
namespace serialization {

template <class Archive>
inline void qx_save(Archive & ar, const qx::service::QxTransaction & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);

   QString sTransactionId = t.getTransactionId();
   quint32 uiInputTransactionSize = t.getInputTransactionSize();
   quint32 uiOutputTransactionSize = t.getOutputTransactionSize();
   QDateTime dtTransactionBegin = t.getTransactionBegin();
   QDateTime dtTransactionRequestSent = t.getTransactionRequestSent();
   QDateTime dtTransactionRequestReceived = t.getTransactionRequestReceived();
   QDateTime dtTransactionReplySent = t.getTransactionReplySent();
   QDateTime dtTransactionReplyReceived = t.getTransactionReplyReceived();
   QDateTime dtTransactionEnd = t.getTransactionEnd();
   QString sIpSource = t.getIpSource();
   QString sIpTarget = t.getIpTarget();
   long lPortSource = t.getPortSource();
   long lPortTarget = t.getPortTarget();
   QString sServiceName = t.getServiceName();
   QString sServiceMethod = t.getServiceMethod();
   qx_bool bMessageReturn = t.getMessageReturn();
   qx::service::IxParameter_ptr pInputParameter = t.getInputParameter();
   qx::service::IxParameter_ptr pOutputParameter = t.getOutputParameter();

   ar << boost::serialization::make_nvp("transaction_id", sTransactionId);
   ar << boost::serialization::make_nvp("input_transaction_size", uiInputTransactionSize);
   ar << boost::serialization::make_nvp("output_transaction_size", uiOutputTransactionSize);
   ar << boost::serialization::make_nvp("dt_transaction_begin", dtTransactionBegin);
   ar << boost::serialization::make_nvp("dt_transaction_request_sent", dtTransactionRequestSent);
   ar << boost::serialization::make_nvp("dt_transaction_request_received", dtTransactionRequestReceived);
   ar << boost::serialization::make_nvp("dt_transaction_reply_sent", dtTransactionReplySent);
   ar << boost::serialization::make_nvp("dt_transaction_reply_received", dtTransactionReplyReceived);
   ar << boost::serialization::make_nvp("dt_transaction_end", dtTransactionEnd);
   ar << boost::serialization::make_nvp("ip_source", sIpSource);
   ar << boost::serialization::make_nvp("ip_target", sIpTarget);
   ar << boost::serialization::make_nvp("port_source", lPortSource);
   ar << boost::serialization::make_nvp("port_target", lPortTarget);
   ar << boost::serialization::make_nvp("service_name", sServiceName);
   ar << boost::serialization::make_nvp("service_method", sServiceMethod);
   ar << boost::serialization::make_nvp("message_return", bMessageReturn);
   ar << boost::serialization::make_nvp("input_parameter", pInputParameter);
   ar << boost::serialization::make_nvp("output_parameter", pOutputParameter);
}

template <class Archive>
inline void qx_load(Archive & ar, qx::service::QxTransaction & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   QString sTransactionId; quint32 uiInputTransactionSize(0); quint32 uiOutputTransactionSize(0);
   QDateTime dtTransactionBegin; QDateTime dtTransactionRequestSent; QDateTime dtTransactionRequestReceived;
   QDateTime dtTransactionReplySent; QDateTime dtTransactionReplyReceived; QDateTime dtTransactionEnd;
   QString sIpSource; QString sIpTarget; long lPortSource(0); long lPortTarget(0);
   QString sServiceName; QString sServiceMethod; qx_bool bMessageReturn;
   qx::service::IxParameter_ptr pInputParameter; qx::service::IxParameter_ptr pOutputParameter;

   ar >> boost::serialization::make_nvp("transaction_id", sTransactionId);
   ar >> boost::serialization::make_nvp("input_transaction_size", uiInputTransactionSize);
   ar >> boost::serialization::make_nvp("output_transaction_size", uiOutputTransactionSize);
   ar >> boost::serialization::make_nvp("dt_transaction_begin", dtTransactionBegin);
   ar >> boost::serialization::make_nvp("dt_transaction_request_sent", dtTransactionRequestSent);
   ar >> boost::serialization::make_nvp("dt_transaction_request_received", dtTransactionRequestReceived);
   ar >> boost::serialization::make_nvp("dt_transaction_reply_sent", dtTransactionReplySent);
   ar >> boost::serialization::make_nvp("dt_transaction_reply_received", dtTransactionReplyReceived);
   ar >> boost::serialization::make_nvp("dt_transaction_end", dtTransactionEnd);
   ar >> boost::serialization::make_nvp("ip_source", sIpSource);
   ar >> boost::serialization::make_nvp("ip_target", sIpTarget);
   ar >> boost::serialization::make_nvp("port_source", lPortSource);
   ar >> boost::serialization::make_nvp("port_target", lPortTarget);
   ar >> boost::serialization::make_nvp("service_name", sServiceName);
   ar >> boost::serialization::make_nvp("service_method", sServiceMethod);
   ar >> boost::serialization::make_nvp("message_return", bMessageReturn);
   ar >> boost::serialization::make_nvp("input_parameter", pInputParameter);
   ar >> boost::serialization::make_nvp("output_parameter", pOutputParameter);

   t.setTransactionId(sTransactionId);
   t.setInputTransactionSize(uiInputTransactionSize);
   t.setOutputTransactionSize(uiOutputTransactionSize);
   t.setTransactionBegin(dtTransactionBegin);
   t.setTransactionRequestSent(dtTransactionRequestSent);
   t.setTransactionRequestReceived(dtTransactionRequestReceived);
   t.setTransactionReplySent(dtTransactionReplySent);
   t.setTransactionReplyReceived(dtTransactionReplyReceived);
   t.setTransactionEnd(dtTransactionEnd);
   t.setIpSource(sIpSource);
   t.setIpTarget(sIpTarget);
   t.setPortSource(lPortSource);
   t.setPortTarget(lPortTarget);
   t.setServiceName(sServiceName);
   t.setServiceMethod(sServiceMethod);
   t.setMessageReturn(bMessageReturn);
   t.setInputParameter(pInputParameter);
   t.setOutputParameter(pOutputParameter);
}

} // namespace serialization
} // namespace boost

#endif // _QX_ENABLE_BOOST_SERIALIZATION

QX_REGISTER_INTERNAL_HELPER_END_FILE_CPP(qx::service::QxTransaction)

QDataStream & operator<< (QDataStream & stream, const qx::service::QxTransaction & t)
{
   stream << t.m_sTransactionId;
   stream << t.m_uiInputTransactionSize;
   stream << t.m_uiOutputTransactionSize;
   stream << t.m_dtTransactionBegin;
   stream << t.m_dtTransactionRequestSent;
   stream << t.m_dtTransactionRequestReceived;
   stream << t.m_dtTransactionReplySent;
   stream << t.m_dtTransactionReplyReceived;
   stream << t.m_dtTransactionEnd;
   stream << t.m_sIpSource;
   stream << t.m_sIpTarget;
   stream << (qint64)(t.m_lPortSource);
   stream << (qint64)(t.m_lPortTarget);
   stream << t.m_sServiceName;
   stream << t.m_sServiceMethod;
   stream << t.m_bMessageReturn;

   qint16 iIsNull = (t.m_pInputParameter ? 0 : 1);
   stream << iIsNull;
   if (t.m_pInputParameter)
   {
      t.m_pInputParameter->registerClass();
      QString sClassName = t.m_pInputParameter->getClassName();
      stream << sClassName;
      t.m_pInputParameter->save(stream);
   }

   iIsNull = (t.m_pOutputParameter ? 0 : 1);
   stream << iIsNull;
   if (t.m_pOutputParameter)
   {
      t.m_pOutputParameter->registerClass();
      QString sClassName = t.m_pOutputParameter->getClassName();
      stream << sClassName;
      t.m_pOutputParameter->save(stream);
   }

   return stream;
}

QDataStream & operator>> (QDataStream & stream, qx::service::QxTransaction & t)
{
   qint64 iTemp = 0;
   stream >> t.m_sTransactionId;
   stream >> t.m_uiInputTransactionSize;
   stream >> t.m_uiOutputTransactionSize;
   stream >> t.m_dtTransactionBegin;
   stream >> t.m_dtTransactionRequestSent;
   stream >> t.m_dtTransactionRequestReceived;
   stream >> t.m_dtTransactionReplySent;
   stream >> t.m_dtTransactionReplyReceived;
   stream >> t.m_dtTransactionEnd;
   stream >> t.m_sIpSource;
   stream >> t.m_sIpTarget;
   stream >> iTemp; t.m_lPortSource = static_cast<long>(iTemp);
   stream >> iTemp; t.m_lPortTarget = static_cast<long>(iTemp);
   stream >> t.m_sServiceName;
   stream >> t.m_sServiceMethod;
   stream >> t.m_bMessageReturn;

   qint16 iIsNull = 0;
   stream >> iIsNull;
   if (iIsNull) { t.m_pInputParameter.reset(); }
   else
   {
      QString sClassName; stream >> sClassName;
      qx::service::IxParameter * ptr = qx::create_nude_ptr<qx::service::IxParameter>(sClassName);
      if (! ptr) { qAssertMsg(false, "[QxOrm] qx::service::QxTransaction, loading QDataStream", "unable to create nude pointer for input parameter"); }
      else { ptr->registerClass(); ptr->load(stream); }
      t.m_pInputParameter.reset(ptr);
   }

   iIsNull = 0;
   stream >> iIsNull;
   if (iIsNull) { t.m_pOutputParameter.reset(); }
   else
   {
      QString sClassName; stream >> sClassName;
      qx::service::IxParameter * ptr = qx::create_nude_ptr<qx::service::IxParameter>(sClassName);
      if (! ptr) { qAssertMsg(false, "[QxOrm] qx::service::QxTransaction, loading QDataStream", "unable to create nude pointer for output parameter"); }
      else { ptr->registerClass(); ptr->load(stream); }
      t.m_pOutputParameter.reset(ptr);
   }

   return stream;
}

#endif // _QX_ENABLE_QT_NETWORK
