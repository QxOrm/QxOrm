/****************************************************************************
**
** Copyright (C) 2010 QxOrm France and/or its subsidiary(-ies)
** Contact: QxOrm France Information (contact@qxorm.com)
**
** This file is part of the QxOrm library
**
** Commercial Usage
** Licensees holding valid QxOrm Commercial licenses may use this file in
** accordance with the QxOrm Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and QxOrm France
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file 'license.gpl3.txt' included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html
**
** If you are unsure which license is appropriate for your use, please
** contact the support department at support@qxorm.com
**
****************************************************************************/

#include "../../include/QxPrecompiled.h"

#include "../../include/QxFactory/QxFactoryX.h"

#include "../../include/QxMemLeak/mem_leak.h"

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
   if (! m_mapFactoryX.contains(sKey))
      return boost::any();

   IxFactory * pFactory = m_mapFactoryX.value(sKey);

   return (pFactory ? pFactory->createObject() : boost::any());
}

} // namespace qx
