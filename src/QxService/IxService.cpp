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

#include <QxService/IxService.h>
#include <QxService/QxTransaction.h>

#include <QxMemLeak/mem_leak.h>

QX_REGISTER_INTERNAL_HELPER_START_FILE_CPP(qx::service::IxService)

namespace qx {
namespace service {

IxService::IxService() { ; }
IxService::IxService(const QString & sServiceName) : m_sServiceName(sServiceName) { qAssert(! m_sServiceName.isEmpty()); }
IxService::~IxService() { ; }

boost::shared_ptr<QxTransaction> IxService::getTransaction() const            { return m_pTransaction; }
void IxService::setTransaction(const boost::shared_ptr<QxTransaction> & p)    { m_pTransaction = p; }

} // namespace service
} // namespace qx

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

} // namespace boost
} // namespace serialization

QX_REGISTER_INTERNAL_HELPER_END_FILE_CPP(qx::service::IxService)

#endif // _QX_ENABLE_QT_NETWORK_DEPENDENCY
