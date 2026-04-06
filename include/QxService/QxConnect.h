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
#ifndef _QX_SERVICE_CONNECT_H_
#define _QX_SERVICE_CONNECT_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxConnect.h
 * \author Lionel Marty
 * \ingroup QxService
 * \brief Define connection parameters used by QxService module and QxHttpServer module of QxOrm library
 */

#ifndef QT_NO_SSL
#include <QtNetwork/qsslsocket.h>
#include <QtNetwork/qsslconfiguration.h>
#include <QtNetwork/qsslcertificate.h>
#include <QtNetwork/qsslerror.h>
#include <QtNetwork/qsslkey.h>
#endif // QT_NO_SSL

#ifndef Q_MOC_RUN
#include <QxSingleton/QxSingleton.h>
#endif // Q_MOC_RUN

namespace qx {
namespace service {

/*!
 * \ingroup QxService
 * \brief qx::service::IxConnect : interface to define connection parameters used by QxService module and QxHttpServer module of QxOrm library
 *
 * <ul>
 * <li><a href="https://www.qxorm.com/qxorm_en/tutorial_2.html" target="_blank">Click here to access to a tutorial to explain how to work with QxService module.</a></li>
 * <li><a href="https://www.qxorm.com/qxorm_en/manual.html#manual_96" target="_blank">Click here to access to the QxHttpServer module documentation.</a></li>
 * </ul>
 */
class QX_DLL_EXPORT IxConnect
{

public:

   enum serialization_type { serialization_binary, serialization_xml, serialization_text, serialization_portable_binary, 
                             serialization_wide_binary, serialization_wide_xml, serialization_wide_text, 
                             serialization_polymorphic_binary, serialization_polymorphic_xml, serialization_polymorphic_text, 
                             serialization_qt, serialization_json };

protected:

   struct IxConnectImpl;
   std::unique_ptr<IxConnectImpl> m_pImpl; //!< Private implementation idiom

   IxConnect();
   virtual ~IxConnect() = 0;

public:

   QString getIp();
   long getPort();
   serialization_type getSerializationType();
   long getThreadCount();
   int getMaxWait();
   bool getCompressData();
   bool getEncryptData();
   quint64 getEncryptKey();
   long getKeepAlive();
   bool getModeHTTP();
   qlonglong getSessionTimeOut();

#ifndef QT_NO_SSL
   bool getSSLEnabled();
   QSslConfiguration getSSLConfiguration();
   QList<QSslCertificate> getSSLCACertificates();
   QSslCertificate getSSLLocalCertificate();
   QSslKey getSSLPrivateKey();
   QList<QSslError> getSSLIgnoreErrors();
   QSsl::SslProtocol getSSLProtocol();
   QString getSSLPeerVerifyName();
   QSslSocket::PeerVerifyMode getSSLPeerVerifyMode();
   int getSSLPeerVerifyDepth();
#else // QT_NO_SSL
   bool getSSLEnabled() { return false; }
#endif // QT_NO_SSL

   void setIp(const QString & s);
   void setPort(long l);
   void setSerializationType(serialization_type e);
   void setThreadCount(long l);
   void setMaxWait(int i);
   void setCompressData(bool b);
   void setEncryptData(bool b, quint64 key = 0);
   void setKeepAlive(long l);
   void setModeHTTP(bool b);
   void setSessionTimeOut(qlonglong l);

#ifndef QT_NO_SSL
   void setSSLEnabled(bool b);
   void setSSLConfiguration(QSslConfiguration cfg);
   void setSSLCACertificates(QList<QSslCertificate> lst);
   void setSSLLocalCertificate(QSslCertificate cert);
   void setSSLPrivateKey(QSslKey key);
   void setSSLIgnoreErrors(QList<QSslError> lst);
   void setSSLProtocol(QSsl::SslProtocol e);
   void setSSLPeerVerifyName(const QString & s);
   void setSSLPeerVerifyMode(QSslSocket::PeerVerifyMode e);
   void setSSLPeerVerifyDepth(int i);
#endif // QT_NO_SSL

};

/*!
 * \ingroup QxService
 * \brief qx::service::QxConnect : define default connection parameters used by QxService module and QxHttpServer module of QxOrm library (this class is a singleton)
 *
 * <ul>
 * <li><a href="https://www.qxorm.com/qxorm_en/tutorial_2.html" target="_blank">Click here to access to a tutorial to explain how to work with QxService module.</a></li>
 * <li><a href="https://www.qxorm.com/qxorm_en/manual.html#manual_96" target="_blank">Click here to access to the QxHttpServer module documentation.</a></li>
 * </ul>
 */
class QX_DLL_EXPORT QxConnect : public IxConnect, public qx::QxSingleton<QxConnect>
{

   friend class qx::QxSingleton<QxConnect>;

private:

   QxConnect();
   virtual ~QxConnect();

};

/*!
 * \ingroup QxService
 * \brief qx::service::QxConnectOther : define other connection parameters used by QxService module and QxHttpServer module of QxOrm library
 *
 * qx::service::QxConnectOther class can be used to create several servers, for example :
 * <ul>
 * <li>Server A listening on port X which uses QxService module to handle requests/responses.</li>
 * <li>Server B listening on port Y which uses QxHttpServer module to handle requests/responses.</li>
 * </ul>
 *
 * <ul>
 * <li><a href="https://www.qxorm.com/qxorm_en/tutorial_2.html" target="_blank">Click here to access to a tutorial to explain how to work with QxService module.</a></li>
 * <li><a href="https://www.qxorm.com/qxorm_en/manual.html#manual_96" target="_blank">Click here to access to the QxHttpServer module documentation.</a></li>
 * </ul>
 */
class QX_DLL_EXPORT QxConnectOther : public IxConnect
{

public:

   QxConnectOther();
   virtual ~QxConnectOther();

};

} // namespace service
} // namespace qx

QX_DLL_EXPORT_QX_SINGLETON_HPP(qx::service::QxConnect)

#endif // _QX_SERVICE_CONNECT_H_
#endif // _QX_ENABLE_QT_NETWORK
