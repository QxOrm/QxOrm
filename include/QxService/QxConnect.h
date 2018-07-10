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

#ifndef _QX_SERVICE_CONNECT_H_
#define _QX_SERVICE_CONNECT_H_

#ifdef _MSC_VER
#pragma once
#endif

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

namespace qx {
namespace service {

class QX_DLL_EXPORT QxConnect : public qx::QxSingleton<QxConnect>
{

   friend class qx::QxSingleton<QxConnect>;

public:

   enum serialization_type { serialization_binary, serialization_xml, serialization_text, serialization_portable_binary, 
                             serialization_wide_binary, serialization_wide_xml, serialization_wide_text, 
                             serialization_polymorphic_binary, serialization_polymorphic_xml, serialization_polymorphic_text };

protected:

   QString              m_sIp;                  // Ip address
   long                 m_lPort;                // Port number
   serialization_type   m_eSerializationType;   // Serialization type to send data over network
   long                 m_lThreadCount;         // Thread count to execute all transactions (cf. 'QxThreadPool')
   int                  m_iMaxWait;             // Max wait in milliseconds for network processes
   bool                 m_bCompressData;        // Compress data over network

public:

   QxConnect() : qx::QxSingleton<QxConnect>("qx::service::QxConnect"), m_lPort(0), m_eSerializationType(QX_SERVICE_DEFAULT_SERIALIZATION_TYPE), m_lThreadCount(30), m_iMaxWait(30000), m_bCompressData(false) { ; }
   virtual ~QxConnect();

   QString getIp() const                              { return m_sIp; }
   long getPort() const                               { return m_lPort; }
   serialization_type getSerializationType() const    { return m_eSerializationType; }
   long getThreadCount() const                        { return m_lThreadCount; }
   int getMaxWait() const                             { return m_iMaxWait; }
   bool getCompressData() const                       { return m_bCompressData; }

   void setIp(const QString & s)                      { m_sIp = s; }
   void setPort(long l)                               { m_lPort = l; }
   void setSerializationType(serialization_type e)    { m_eSerializationType = e; }
   void setThreadCount(long l)                        { qAssert(l > 0); m_lThreadCount = l; }
   void setMaxWait(int i)                             { qAssert(i > 0); m_iMaxWait = i; }
   void setCompressData(bool b)                       { m_bCompressData = b; }

};

} // namespace service
} // namespace qx

QX_DLL_EXPORT_QX_SINGLETON_HPP(qx::service::QxConnect)

#endif // _QX_SERVICE_CONNECT_H_
