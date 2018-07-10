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

#include <QxFactory/QxFactoryX.h>

#include <QxMemLeak/mem_leak.h>

QX_DLL_EXPORT_QX_SINGLETON_CPP(qx::QxFactoryX)

namespace qx {

void QxFactoryX::registerFactory(const QString & sKey, IxFactory * pFactory)
{
   QMutexLocker locker(& m_oMutexFactoryX);
   qAssert(! sKey.isEmpty() && ! m_mapFactoryX.contains(sKey));

   if (! pFactory || sKey.isEmpty() || m_mapFactoryX.contains(sKey))
      return;

   m_mapFactoryX.insert(sKey, pFactory);
}

void QxFactoryX::unregisterFactory(const QString & sKey)
{
   QMutexLocker locker(& m_oMutexFactoryX);
   m_mapFactoryX.remove(sKey);
}

boost::any QxFactoryX::createObject(const QString & sKey) const
{
   IxFactory * pFactory = (m_mapFactoryX.contains(sKey) ? m_mapFactoryX.value(sKey) : NULL);
   if (! pFactory) { qDebug("[QxOrm] cannot create an instance of type '%s'", qPrintable(sKey)); }

   return (pFactory ? pFactory->createObject() : boost::any());
}

} // namespace qx
