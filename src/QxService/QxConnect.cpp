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

#include <QxPrecompiled.h>

#include <QxService/QxConnect.h>

#include <QxMemLeak/mem_leak.h>

#if _QX_SERIALIZE_BINARY
#define QX_SERVICE_DEFAULT_SERIALIZATION_TYPE QxConnect::serialization_binary
#elif _QX_SERIALIZE_WIDE_BINARY
#define QX_SERVICE_DEFAULT_SERIALIZATION_TYPE QxConnect::serialization_wide_binary
#elif _QX_SERIALIZE_PORTABLE_BINARY
#define QX_SERVICE_DEFAULT_SERIALIZATION_TYPE QxConnect::serialization_portable_binary
#elif _QX_SERIALIZE_POLYMORPHIC
#define QX_SERVICE_DEFAULT_SERIALIZATION_TYPE QxConnect::serialization_polymorphic_binary
#elif _QX_SERIALIZE_TEXT
#define QX_SERVICE_DEFAULT_SERIALIZATION_TYPE QxConnect::serialization_text
#elif _QX_SERIALIZE_XML
#define QX_SERVICE_DEFAULT_SERIALIZATION_TYPE QxConnect::serialization_xml
#elif _QX_SERIALIZE_WIDE_TEXT
#define QX_SERVICE_DEFAULT_SERIALIZATION_TYPE QxConnect::serialization_wide_text
#elif _QX_SERIALIZE_WIDE_XML
#define QX_SERVICE_DEFAULT_SERIALIZATION_TYPE QxConnect::serialization_wide_xml
#endif // _QX_SERIALIZE_BINARY

#ifndef QX_SERVICE_DEFAULT_SERIALIZATION_TYPE
#define QX_SERVICE_DEFAULT_SERIALIZATION_TYPE QxConnect::serialization_qt
#endif // QX_SERVICE_DEFAULT_SERIALIZATION_TYPE

#define QX_SERVICE_DEFAULT_ENCRYPT_KEY Q_UINT64_C(0x0f2aac3b24358a1a)

#ifndef QT_NO_SSL
#define QX_CONSTRUCT_QX_SERVICE_CONNECT_SSL() \
, m_sslEnabled(false), m_sslProtocol(QSsl::SecureProtocols), m_sslPeerVerifyMode(QSslSocket::VerifyNone), m_sslPeerVerifyDepth(0)
#else // QT_NO_SSL
#define QX_CONSTRUCT_QX_SERVICE_CONNECT_SSL() /* Nothing */
#endif // QT_NO_SSL

#define QX_CONSTRUCT_QX_SERVICE_CONNECT() \
m_lPort(7832), m_eSerializationType(QX_SERVICE_DEFAULT_SERIALIZATION_TYPE), m_lThreadCount(30), \
m_iMaxWait(30000), m_bCompressData(false), m_bEncryptData(false), m_lKeepAlive(0), m_bModeHTTP(false), m_lSessionTimeOut(86400000) \
QX_CONSTRUCT_QX_SERVICE_CONNECT_SSL()

QX_DLL_EXPORT_QX_SINGLETON_CPP(qx::service::QxConnect)

namespace qx {
namespace service {

struct Q_DECL_HIDDEN QxConnect::QxConnectImpl
{

   QMutex                           m_mutex;                   //!< Mutex => 'QxConnect' is thread-safe
   QString                          m_sIp;                     //!< Ip address
   long                             m_lPort;                   //!< Port number
   QxConnect::serialization_type    m_eSerializationType;      //!< Serialization type to send data over network
   long                             m_lThreadCount;            //!< Thread count to execute all transactions (cf. 'QxThreadPool')
   int                              m_iMaxWait;                //!< Max wait in milliseconds for network processes
   bool                             m_bCompressData;           //!< Compress data over network
   bool                             m_bEncryptData;            //!< Encrypt data before transfering it over network
   quint64                          m_uiEncryptKey;            //!< 64 bit key to encrypt/decrypt data
   long                             m_lKeepAlive;              //!< Keep socket opened during X milliseconds (-1 means never disconnect)
   bool                             m_bModeHTTP;               //!< Put QxService module in mode HTTP (see QxHttpServer module)
   qlonglong                        m_lSessionTimeOut;         //!< HTTP session time-out (expiration) in milliseconds

#ifndef QT_NO_SSL
   bool                             m_sslEnabled;              //!< Is secure connection enabled
   QSslConfiguration                m_sslConfig;               //!< Global SSL configuration
   QList<QSslCertificate>           m_sslCACertificates;       //!< CA certificates
   QSslCertificate                  m_sslLocalCertificate;     //!< Server certificate (public part)
   QSslKey                          m_sslPrivateKey;           //!< Server certificate private key
   QList<QSslError>                 m_sslIgnoreErrors;         //!< List of SSL errors to ignore
   QSsl::SslProtocol                m_sslProtocol;             //!< List of supported protocols (SSL, TLS)
   QString                          m_sslPeerVerifyName;       //!< Peer name for certificate validation
   QSslSocket::PeerVerifyMode       m_sslPeerVerifyMode;       //!< Peer mode for certificate validation
   int                              m_sslPeerVerifyDepth;      //!< Peer depth level for certificate validation
#endif // QT_NO_SSL

   QxConnectImpl() : QX_CONSTRUCT_QX_SERVICE_CONNECT() { m_uiEncryptKey = QX_SERVICE_DEFAULT_ENCRYPT_KEY; ignoreAllSSLErrors(); }
   ~QxConnectImpl() { ; }

   void ignoreAllSSLErrors()
   {
#ifndef QT_NO_SSL
      QSslError err = QSslError(QSslError::UnableToGetIssuerCertificate); m_sslIgnoreErrors.append(err);
      err = QSslError(QSslError::UnableToDecryptCertificateSignature); m_sslIgnoreErrors.append(err);
      err = QSslError(QSslError::UnableToDecodeIssuerPublicKey); m_sslIgnoreErrors.append(err);
      err = QSslError(QSslError::CertificateSignatureFailed); m_sslIgnoreErrors.append(err);
      err = QSslError(QSslError::CertificateNotYetValid); m_sslIgnoreErrors.append(err);
      err = QSslError(QSslError::CertificateExpired); m_sslIgnoreErrors.append(err);
      err = QSslError(QSslError::InvalidNotBeforeField); m_sslIgnoreErrors.append(err);
      err = QSslError(QSslError::InvalidNotAfterField); m_sslIgnoreErrors.append(err);
      err = QSslError(QSslError::SelfSignedCertificate); m_sslIgnoreErrors.append(err);
      err = QSslError(QSslError::SelfSignedCertificateInChain); m_sslIgnoreErrors.append(err);
      err = QSslError(QSslError::UnableToGetLocalIssuerCertificate); m_sslIgnoreErrors.append(err);
      err = QSslError(QSslError::UnableToVerifyFirstCertificate); m_sslIgnoreErrors.append(err);
      err = QSslError(QSslError::CertificateRevoked); m_sslIgnoreErrors.append(err);
      err = QSslError(QSslError::InvalidCaCertificate); m_sslIgnoreErrors.append(err);
      err = QSslError(QSslError::PathLengthExceeded); m_sslIgnoreErrors.append(err);
      err = QSslError(QSslError::InvalidPurpose); m_sslIgnoreErrors.append(err);
      err = QSslError(QSslError::CertificateUntrusted); m_sslIgnoreErrors.append(err);
      err = QSslError(QSslError::CertificateRejected); m_sslIgnoreErrors.append(err);
      err = QSslError(QSslError::SubjectIssuerMismatch); m_sslIgnoreErrors.append(err);
      err = QSslError(QSslError::AuthorityIssuerSerialNumberMismatch); m_sslIgnoreErrors.append(err);
      err = QSslError(QSslError::NoPeerCertificate); m_sslIgnoreErrors.append(err);
      err = QSslError(QSslError::HostNameMismatch); m_sslIgnoreErrors.append(err);
      err = QSslError(QSslError::UnspecifiedError); m_sslIgnoreErrors.append(err);
      err = QSslError(QSslError::NoSslSupport); m_sslIgnoreErrors.append(err);
      err = QSslError(QSslError::CertificateBlacklisted); m_sslIgnoreErrors.append(err);
#endif // QT_NO_SSL
   }

};

QxConnect::QxConnect() : qx::QxSingleton<QxConnect>("qx::service::QxConnect"), m_pImpl(new QxConnectImpl()) { ; }

QxConnect::~QxConnect() { ; }

QString QxConnect::getIp()
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   return m_pImpl->m_sIp;
}

long QxConnect::getPort()
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   return m_pImpl->m_lPort;
}

QxConnect::serialization_type QxConnect::getSerializationType()
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   return m_pImpl->m_eSerializationType;
}

long QxConnect::getThreadCount()
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   return m_pImpl->m_lThreadCount;
}

int QxConnect::getMaxWait()
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   return m_pImpl->m_iMaxWait;
}

bool QxConnect::getCompressData()
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   return m_pImpl->m_bCompressData;
}

bool QxConnect::getEncryptData()
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   return m_pImpl->m_bEncryptData;
}

quint64 QxConnect::getEncryptKey()
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   return m_pImpl->m_uiEncryptKey;
}

long QxConnect::getKeepAlive()
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   return m_pImpl->m_lKeepAlive;
}

bool QxConnect::getModeHTTP()
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   return m_pImpl->m_bModeHTTP;
}

qlonglong QxConnect::getSessionTimeOut()
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   return m_pImpl->m_lSessionTimeOut;
}

#ifndef QT_NO_SSL

bool QxConnect::getSSLEnabled()
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   return m_pImpl->m_sslEnabled;
}

QSslConfiguration QxConnect::getSSLConfiguration()
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   return m_pImpl->m_sslConfig;
}

QList<QSslCertificate> QxConnect::getSSLCACertificates()
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   return m_pImpl->m_sslCACertificates;
}

QSslCertificate QxConnect::getSSLLocalCertificate()
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   return m_pImpl->m_sslLocalCertificate;
}

QSslKey QxConnect::getSSLPrivateKey()
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   return m_pImpl->m_sslPrivateKey;
}

QList<QSslError> QxConnect::getSSLIgnoreErrors()
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   return m_pImpl->m_sslIgnoreErrors;
}

QSsl::SslProtocol QxConnect::getSSLProtocol()
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   return m_pImpl->m_sslProtocol;
}

QString QxConnect::getSSLPeerVerifyName()
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   return m_pImpl->m_sslPeerVerifyName;
}

QSslSocket::PeerVerifyMode QxConnect::getSSLPeerVerifyMode()
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   return m_pImpl->m_sslPeerVerifyMode;
}

int QxConnect::getSSLPeerVerifyDepth()
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   return m_pImpl->m_sslPeerVerifyDepth;
}

#endif // QT_NO_SSL

void QxConnect::setIp(const QString & s)
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   m_pImpl->m_sIp = s;
}

void QxConnect::setPort(long l)
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   m_pImpl->m_lPort = l;
}

void QxConnect::setSerializationType(QxConnect::serialization_type e)
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   m_pImpl->m_eSerializationType = e;
}

void QxConnect::setThreadCount(long l)
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   m_pImpl->m_lThreadCount = l;
   qAssert(l > 0);
}

void QxConnect::setMaxWait(int i)
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   m_pImpl->m_iMaxWait = i;
   qAssert(i > 0);
}

void QxConnect::setCompressData(bool b)
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   m_pImpl->m_bCompressData = b;
}

void QxConnect::setEncryptData(bool b, quint64 key /* = 0 */)
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   m_pImpl->m_bEncryptData = b;
   if (key != 0) { m_pImpl->m_uiEncryptKey = key; }
}

void QxConnect::setKeepAlive(long l)
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   m_pImpl->m_lKeepAlive = l;
}

void QxConnect::setModeHTTP(bool b)
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   m_pImpl->m_bModeHTTP = b;
}

void QxConnect::setSessionTimeOut(qlonglong l)
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   m_pImpl->m_lSessionTimeOut = l;
}

#ifndef QT_NO_SSL

void QxConnect::setSSLEnabled(bool b)
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   m_pImpl->m_sslEnabled = b;
}

void QxConnect::setSSLConfiguration(QSslConfiguration cfg)
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   m_pImpl->m_sslConfig = cfg;
}

void QxConnect::setSSLCACertificates(QList<QSslCertificate> lst)
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   m_pImpl->m_sslCACertificates = lst;
}

void QxConnect::setSSLLocalCertificate(QSslCertificate cert)
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   m_pImpl->m_sslLocalCertificate = cert;
}

void QxConnect::setSSLPrivateKey(QSslKey key)
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   m_pImpl->m_sslPrivateKey = key;
}

void QxConnect::setSSLIgnoreErrors(QList<QSslError> lst)
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   m_pImpl->m_sslIgnoreErrors = lst;
}

void QxConnect::setSSLProtocol(QSsl::SslProtocol e)
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   m_pImpl->m_sslProtocol = e;
}

void QxConnect::setSSLPeerVerifyName(const QString & s)
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   m_pImpl->m_sslPeerVerifyName = s;
}

void QxConnect::setSSLPeerVerifyMode(QSslSocket::PeerVerifyMode e)
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   m_pImpl->m_sslPeerVerifyMode = e;
}

void QxConnect::setSSLPeerVerifyDepth(int i)
{
   QMutexLocker locker(& m_pImpl->m_mutex);
   m_pImpl->m_sslPeerVerifyDepth = i;
}

#endif // QT_NO_SSL

} // namespace service
} // namespace qx

#endif // _QX_ENABLE_QT_NETWORK
