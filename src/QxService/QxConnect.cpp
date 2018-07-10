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

#include <QxService/QxConnect.h>

#include <QxMemLeak/mem_leak.h>

QX_DLL_EXPORT_QX_SINGLETON_CPP(qx::service::QxConnect)

namespace qx {
namespace service {

QxConnect::~QxConnect() { ; }

} // namespace service
} // namespace qx

#endif // _QX_ENABLE_QT_NETWORK_DEPENDENCY
