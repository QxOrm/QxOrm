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

#include <QxService/IxParameter.h>

#include <QxMemLeak/mem_leak.h>

QX_REGISTER_INTERNAL_HELPER_START_FILE_CPP(qx::service::IxParameter)

namespace qx {
namespace service {

IxParameter::IxParameter() { ; }
IxParameter::~IxParameter() { ; }

} // namespace service
} // namespace qx

namespace boost {
namespace serialization {

template <class Archive>
inline void qx_save(Archive & ar, const qx::service::IxParameter & t, const unsigned int file_version)
{ Q_UNUSED(ar); Q_UNUSED(t); Q_UNUSED(file_version); }

template <class Archive>
inline void qx_load(Archive & ar, qx::service::IxParameter & t, const unsigned int file_version)
{ Q_UNUSED(ar); Q_UNUSED(t); Q_UNUSED(file_version); }

} // namespace boost
} // namespace serialization

QX_REGISTER_INTERNAL_HELPER_END_FILE_CPP(qx::service::IxParameter)

#endif // _QX_ENABLE_QT_NETWORK_DEPENDENCY
