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
#ifndef _QX_SERVICE_CONNECT_H_
#define _QX_SERVICE_CONNECT_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxConnect.h
 * \author Lionel Marty
 * \ingroup QxService
 * \brief Define connection parameters used by QxService module of QxOrm library
 */

#include <QxSingleton/QxSingleton.h>

#if _QX_SERIALIZE_BINARY
#define QX_SERVICE_DEFAULT_SERIALIZATION_TYPE serialization_binary
#elif _QX_SERIALIZE_WIDE_BINARY
#define QX_SERVICE_DEFAULT_SERIALIZATION_TYPE serialization_wide_binary
#elif _QX_SERIALIZE_PORTABLE_BINARY
#define QX_SERVICE_DEFAULT_SERIALIZATION_TYPE serialization_portable_binary
#elif _QX_SERIALIZE_POLYMORPHIC
#define QX_SERVICE_DEFAULT_SERIALIZATION_TYPE serialization_polymorphic_binary
#elif _QX_SERIALIZE_TEXT
#define QX_SERVICE_DEFAULT_SERIALIZATION_TYPE serialization_text
#elif _QX_SERIALIZE_XML
#define QX_SERVICE_DEFAULT_SERIALIZATION_TYPE serialization_xml
#elif _QX_SERIALIZE_WIDE_TEXT
#define QX_SERVICE_DEFAULT_SERIALIZATION_TYPE serialization_wide_text
#elif _QX_SERIALIZE_WIDE_XML
#define QX_SERVICE_DEFAULT_SERIALIZATION_TYPE serialization_wide_xml
#endif // _QX_SERIALIZE_BINARY

#ifndef QX_SERVICE_DEFAULT_SERIALIZATION_TYPE
#define QX_SERVICE_DEFAULT_SERIALIZATION_TYPE serialization_qt
#endif // QX_SERVICE_DEFAULT_SERIALIZATION_TYPE

#define QX_SERVICE_DEFAULT_ENCRYPT_KEY Q_UINT64_C(0x0f2aac3b24358a1a)

namespace qx {
namespace service {

/*!
 * \ingroup QxService
 * \brief qx::service::QxConnect : define connection parameters used by QxService module of QxOrm library (this class is a singleton)
 *
 * <a href="http://www.qxorm.com/qxorm_en/tutorial_2.html" target="_blank">Click here to access to a tutorial to explain how to work with QxService module.</a>
 */
class QX_DLL_EXPORT QxConnect : public qx::QxSingleton<QxConnect>
{

   friend class qx::QxSingleton<QxConnect>;

public:

   enum serialization_type { serialization_binary, serialization_xml, serialization_text, serialization_portable_binary, 
                             serialization_wide_binary, serialization_wide_xml, serialization_wide_text, 
                             serialization_polymorphic_binary, serialization_polymorphic_xml, serialization_polymorphic_text, 
                             serialization_qt, serialization_json };

protected:

   QString              m_sIp;                  //!< Ip address
   long                 m_lPort;                //!< Port number
   serialization_type   m_eSerializationType;   //!< Serialization type to send data over network
   long                 m_lThreadCount;         //!< Thread count to execute all transactions (cf. 'QxThreadPool')
   int                  m_iMaxWait;             //!< Max wait in milliseconds for network processes
   bool                 m_bCompressData;        //!< Compress data over network
   bool                 m_bEncryptData;         //!< Encrypt data before transfering it over network
   quint64              m_uiEncryptKey;         //!< 64 bit key to encrypt/decrypt data

public:

   QxConnect() : qx::QxSingleton<QxConnect>("qx::service::QxConnect"), m_lPort(0), m_eSerializationType(QX_SERVICE_DEFAULT_SERIALIZATION_TYPE), m_lThreadCount(30), m_iMaxWait(30000), m_bCompressData(false), m_bEncryptData(false) { m_uiEncryptKey = QX_SERVICE_DEFAULT_ENCRYPT_KEY; }
   virtual ~QxConnect();

   QString getIp() const                              { return m_sIp; }
   long getPort() const                               { return m_lPort; }
   serialization_type getSerializationType() const    { return m_eSerializationType; }
   long getThreadCount() const                        { return m_lThreadCount; }
   int getMaxWait() const                             { return m_iMaxWait; }
   bool getCompressData() const                       { return m_bCompressData; }
   bool getEncryptData() const                        { return m_bEncryptData; }
   quint64 getEncryptKey() const                      { return m_uiEncryptKey; }

   void setIp(const QString & s)                      { m_sIp = s; }
   void setPort(long l)                               { m_lPort = l; }
   void setSerializationType(serialization_type e)    { m_eSerializationType = e; }
   void setThreadCount(long l)                        { qAssert(l > 0); m_lThreadCount = l; }
   void setMaxWait(int i)                             { qAssert(i > 0); m_iMaxWait = i; }
   void setCompressData(bool b)                       { m_bCompressData = b; }
   void setEncryptData(bool b, quint64 key = 0)       { m_bEncryptData = b; if (key != 0) { m_uiEncryptKey = key; } }

};

} // namespace service
} // namespace qx

QX_DLL_EXPORT_QX_SINGLETON_HPP(qx::service::QxConnect)

#endif // _QX_SERVICE_CONNECT_H_
#endif // _QX_ENABLE_QT_NETWORK
