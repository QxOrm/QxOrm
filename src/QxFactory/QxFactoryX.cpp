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

qx::any QxFactoryX::createObject(const QString & sKey) const
{
   IxFactory * pFactory = (m_mapFactoryX.contains(sKey) ? m_mapFactoryX.value(sKey) : NULL);
   if (! pFactory) { qDebug("[QxOrm] cannot create an instance of type '%s'", qPrintable(sKey)); }

   return (pFactory ? pFactory->createObject() : qx::any());
}

void * QxFactoryX::createObjectNudePtr(const QString & sKey) const
{
   IxFactory * pFactory = (m_mapFactoryX.contains(sKey) ? m_mapFactoryX.value(sKey) : NULL);
   if (! pFactory) { qDebug("[QxOrm] cannot create an instance of type '%s'", qPrintable(sKey)); }

   return (pFactory ? pFactory->createObjectNudePtr() : NULL);
}

#ifndef _QX_NO_RTTI
const std::type_info & QxFactoryX::typeInfo(const QString & sKey) const
{
   IxFactory * pFactory = (m_mapFactoryX.contains(sKey) ? m_mapFactoryX.value(sKey) : NULL);
   if (! pFactory) { qDebug("[QxOrm] cannot get informations about type '%s'", qPrintable(sKey)); }

   return (pFactory ? pFactory->typeInfo() : typeid(void));
}
#endif // _QX_NO_RTTI

} // namespace qx
