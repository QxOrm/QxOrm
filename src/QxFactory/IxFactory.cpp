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

#include "../../include/QxPrecompiled.h"

#include "../../include/QxFactory/IxFactory.h"
#include "../../include/QxFactory/QxFactoryX.h"

#include "../../include/QxMemLeak/mem_leak.h"

namespace qx {

IxFactory::IxFactory(const QString & sKey) : boost::noncopyable(), m_sKeyFactory(sKey)
{
#if _QX_USE_TRACE_CONSTRUCTOR_DESTRUCTOR
   qDebug("[QxOrm] qx::IxFactory constructor '%s'", qPrintable(m_sKeyFactory));
#endif // _QX_USE_TRACE_CONSTRUCTOR_DESTRUCTOR

   QxFactoryX::getSingleton()->registerFactory(m_sKeyFactory, this);
}

IxFactory::~IxFactory()
{
#if _QX_USE_TRACE_CONSTRUCTOR_DESTRUCTOR
   qDebug("[QxOrm] qx::IxFactory destructor '%s'", qPrintable(m_sKeyFactory));
#endif // _QX_USE_TRACE_CONSTRUCTOR_DESTRUCTOR

   if (! QxFactoryX::isSingletonNull()) { QxFactoryX::getSingleton()->unregisterFactory(m_sKeyFactory); }
}

} // namespace qx
