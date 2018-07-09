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

#include "../../include/QxCommon/QxCache.h"

#include "../../include/QxMemLeak/mem_leak.h"

namespace qx {
namespace cache {
namespace detail {

bool QxCache::insert(const QString & sKey, const boost::any & pObj, long lCost /* = 1 */)
{
   if (sKey.isEmpty()) { qAssert(false); return false; }
   this->remove(sKey);

   QMutexLocker locker(& m_oMutexCache);
   lCost = ((lCost < 0) ? 0 : lCost);
   boost::any obj(pObj);
   type_qx_cache item = std::make_pair(lCost, obj);
   bool bInsertOk = m_cache.insert(sKey, item);
   if (bInsertOk) { m_lCurrCost += lCost; updateCost(); }

   return bInsertOk;
}

bool QxCache::remove(const QString & sKey)
{
   QMutexLocker locker(& m_oMutexCache);
   if (! this->exist(sKey)) { return false; }
   long lCost = m_cache.getByKey(sKey).first;
   bool bRemoveOk = m_cache.removeByKey(sKey);
   if (bRemoveOk) { m_lCurrCost -= lCost; }

   return bRemoveOk;
}

void QxCache::updateCost()
{
   while ((m_lCurrCost > m_lMaxCost) && (m_cache.count() > 0))
   {
      QString sKey = m_cache.getKeyByIndex(0);
      long lCost = m_cache.getByIndex(0).first;
      m_cache.removeByIndex(0);
      m_lCurrCost -= lCost;
      QString sMsg = QString("qx::cache auto remove object in cache '") + sKey + QString("'");
      qDebug("[QxOrm] %s", qPrintable(sMsg));
   }
}

} // namespace detail
} // namespace cache
} // namespace qx
