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

#include <QxPrecompiled.h>

#if _QX_ENABLE_QT_NETWORK_DEPENDENCY

#include <QtCore/quuid.h>

#include <QtNetwork/qhostaddress.h>

#include <QxService/QxTransaction.h>
#include <QxService/QxConnect.h>
#include <QxService/QxTools.h>

#include <QxRegister/QxClassX.h>

#include <QxFactory/QxFactoryX.h>

#include <QxMemLeak/mem_leak.h>

QX_REGISTER_INTERNAL_HELPER_START_FILE_CPP(qx::service::QxTransaction)

namespace qx {
namespace service {

void QxTransaction::executeServer()
{
   if (m_sServiceName.isEmpty()) { m_bMessageReturn = qx_bool(0, "[QxOrm] empty service name => cannot instantiate service and execute process"); return; }
   if (m_sServiceMethod.isEmpty()) { m_bMessageReturn = qx_bool(0, "[QxOrm] empty service method => cannot execute process"); return; }

   qx::service::IxService * ptr = qx::create_nude_ptr<qx::service::IxService>(m_sServiceName);
   if (ptr == NULL) { m_bMessageReturn = qx_bool(0, "[QxOrm] invalid service name => cannot instantiate service and execute process"); return; }
   m_pServiceInstance = IxService_ptr(ptr);
   m_pServiceInstance->registerClass();
   m_pServiceInstance->setInputParameter(m_pInputParameter);

   try
   {
      qx_bool bInvokeOk = qx::QxClassX::invoke(m_sServiceName, m_sServiceMethod, (* m_pServiceInstance));
      if (! bInvokeOk) { m_bMessageReturn = qx_bool(0, "[QxOrm] invalid service method => cannot execute process"); return; }
      m_pOutputParameter = m_pServiceInstance->getOutputParameter_BaseClass();
      m_bMessageReturn = m_pServiceInstance->getMessageReturn();
   }
   catch (const std::exception & e) { QString msg(e.what()); if (msg.isEmpty()) { msg = "[QxOrm] unexpected error occured executing service method"; }; m_bMessageReturn = qx_bool(0, msg); }
   catch (...) { m_bMessageReturn = qx_bool(0, "[QxOrm] unknown error occured executing service method"); }
   m_pServiceInstance.reset();
}

void QxTransaction::executeClient(IxService * pService, const QString & sMethod)
{
   if ((pService == NULL) || sMethod.isEmpty()) { qAssert(false); return; }
   if (pService->getServiceName().isEmpty()) { pService->setMessageReturn(qx_bool(0, "[QxOrm] empty service name")); return; }
   pService->registerClass();

   QTcpSocket socket;
   QString serverName = QxConnect::getSingleton()->getIp();
   long serverPort = QxConnect::getSingleton()->getPort();
   socket.connectToHost(serverName, serverPort);
   if (! socket.waitForConnected(QxConnect::getSingleton()->getMaxWait()))
   { pService->setMessageReturn(qx_bool(0, "[QxOrm] unable to connect to server")); return; }

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
   if (! bWriteOk) { pService->setMessageReturn(qx_bool(0, QString("[QxOrm] unable to write request to socket : '") + bWriteOk.getDesc() + QString("'"))); return; }
   qx_bool bReadOk = readSocket(socket);
   if (! bReadOk) { pService->setMessageReturn(qx_bool(0, QString("[QxOrm] unable to read reply from socket : '") + bReadOk.getDesc() + QString("'"))); return; }

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

} // namespace boost
} // namespace serialization

QX_REGISTER_INTERNAL_HELPER_END_FILE_CPP(qx::service::QxTransaction)

#endif // _QX_ENABLE_QT_NETWORK_DEPENDENCY
