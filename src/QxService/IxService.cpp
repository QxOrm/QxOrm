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

#include <QxService/IxService.h>
#include <QxService/QxTransaction.h>

#include <QxFactory/QxFactoryX.h>

#include <QxMemLeak/mem_leak.h>

QX_REGISTER_INTERNAL_HELPER_START_FILE_CPP(qx::service::IxService)

namespace qx {
namespace service {

IxService::IxService() { ; }
IxService::IxService(const QString & sServiceName) : m_sServiceName(sServiceName) { qAssert(! m_sServiceName.isEmpty()); }
IxService::~IxService() { ; }

qx_shared_ptr<QxTransaction> IxService::getTransaction() const          { return m_pTransaction; }
void IxService::setTransaction(const qx_shared_ptr<QxTransaction> & p)  { m_pTransaction = p; }

} // namespace service
} // namespace qx

#ifdef _QX_ENABLE_BOOST_SERIALIZATION

namespace boost {
namespace serialization {

template <class Archive>
inline void qx_save(Archive & ar, const qx::service::IxService & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);

   QString sServiceName = t.getServiceName();
   qx::service::IxParameter_ptr pInputParam = t.getInputParameter_BaseClass();
   qx::service::IxParameter_ptr pOutputParam = t.getOutputParameter_BaseClass();
   qx_bool bMsgReturn = t.getMessageReturn();

   ar << boost::serialization::make_nvp("service_name", sServiceName);
   ar << boost::serialization::make_nvp("input_param", pInputParam);
   ar << boost::serialization::make_nvp("output_param", pOutputParam);
   ar << boost::serialization::make_nvp("msg_return", bMsgReturn);
}

template <class Archive>
inline void qx_load(Archive & ar, qx::service::IxService & t, const unsigned int file_version)
{
   Q_UNUSED(file_version);
   QString sServiceName; qx::service::IxParameter_ptr pInputParam;
   qx::service::IxParameter_ptr pOutputParam; qx_bool bMsgReturn;

   ar >> boost::serialization::make_nvp("service_name", sServiceName);
   ar >> boost::serialization::make_nvp("input_param", pInputParam);
   ar >> boost::serialization::make_nvp("output_param", pOutputParam);
   ar >> boost::serialization::make_nvp("msg_return", bMsgReturn);

   t.setServiceName(sServiceName);
   t.setInputParameter(pInputParam);
   t.setOutputParameter(pOutputParam);
   t.setMessageReturn(bMsgReturn);
}

} // namespace serialization
} // namespace boost

#endif // _QX_ENABLE_BOOST_SERIALIZATION

QX_REGISTER_INTERNAL_HELPER_END_FILE_CPP(qx::service::IxService)

QDataStream & operator<< (QDataStream & stream, const qx::service::IxService & t)
{
   stream << t.m_sServiceName;
   stream << t.m_sServiceMethodName;
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

QDataStream & operator>> (QDataStream & stream, qx::service::IxService & t)
{
   stream >> t.m_sServiceName;
   stream >> t.m_sServiceMethodName;
   stream >> t.m_bMessageReturn;

   qint16 iIsNull = 0;
   stream >> iIsNull;
   if (iIsNull) { t.m_pInputParameter.reset(); }
   else
   {
      QString sClassName; stream >> sClassName;
      qx::service::IxParameter * ptr = qx::create_nude_ptr<qx::service::IxParameter>(sClassName);
      if (! ptr) { qAssertMsg(false, "[QxOrm] qx::service::IxService, loading QDataStream", "unable to create nude pointer for input parameter"); }
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
      if (! ptr) { qAssertMsg(false, "[QxOrm] qx::service::IxService, loading QDataStream", "unable to create nude pointer for output parameter"); }
      else { ptr->registerClass(); ptr->load(stream); }
      t.m_pOutputParameter.reset(ptr);
   }

   return stream;
}

#endif // _QX_ENABLE_QT_NETWORK
