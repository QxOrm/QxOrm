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

#include "../../include/QxDao/IxSqlQueryBuilder.h"

#include "../../include/QxMemLeak/mem_leak.h"

namespace qx {

IxSqlQueryBuilder::~IxSqlQueryBuilder() { ; }

void IxSqlQueryBuilder::displaySqlQuery(int time_ms /* = -1 */) const
{
   if (time_ms < 0)  { qDebug("[QxOrm] sql query : %s", qPrintable(m_sSqlQuery)); }
   else              { qDebug("[QxOrm] sql query (%d ms) : %s", time_ms, qPrintable(m_sSqlQuery)); }
}

void IxSqlQueryBuilder::initIdX()
{
   if (m_pIdX) { return; }
   if (! m_bCartesianProduct || ! m_lstSqlRelationPtr) { qAssert(false); return; }

   m_pIdX.reset(new type_lst_ptr_by_id());
   type_ptr_by_id_ptr pItem;
   pItem.reset(new type_ptr_by_id());
   m_pIdX->append(pItem); // index 0 -> owner

   for (long l = 0; l < m_lstSqlRelationPtr->count(); ++l)
   {
      pItem.reset(new type_ptr_by_id());
      m_pIdX->append(pItem); // index 1 2 3 4 etc... -> relation
   }
}

bool IxSqlQueryBuilder::insertIdX(long lIndex, const QVariant & idOwner, const QVariant & idData, void * ptr)
{
   this->initIdX();
   QString sIdOwner = idOwner.toString(); QString sIdData = idData.toString();
   if (! m_pIdX || sIdOwner.isEmpty() || sIdData.isEmpty()) { qAssert(false); return false; }
   if ((lIndex < 0) || (lIndex >= m_pIdX->count())) { qAssert(false); return false; }

   type_id idX(sIdOwner, sIdData);
   type_ptr_by_id_ptr pHash = m_pIdX->at(lIndex);
   if (! ptr || ! pHash || pHash->contains(idX)) { qAssert(false); return false; }
   pHash->insert(idX, ptr);

   return true;
}

void * IxSqlQueryBuilder::existIdX(long lIndex, const QVariant & idOwner, const QVariant & idData)
{
   this->initIdX();
   QString sIdOwner = idOwner.toString(); QString sIdData = idData.toString();
   if (! m_pIdX || sIdOwner.isEmpty() || sIdData.isEmpty()) { qAssert(false); return NULL; }
   if ((lIndex < 0) || (lIndex >= m_pIdX->count())) { qAssert(false); return NULL; }

   type_id idX(sIdOwner, sIdData);
   type_ptr_by_id_ptr pHash = m_pIdX->at(lIndex);
   if (! pHash || ! pHash->contains(idX)) { return NULL; }

   return pHash->value(idX);
}

} // namespace qx
