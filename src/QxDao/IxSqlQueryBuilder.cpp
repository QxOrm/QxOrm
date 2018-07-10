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

#include <QxDao/IxSqlQueryBuilder.h>
#include <QxDao/QxSqlDatabase.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

IxSqlQueryBuilder::~IxSqlQueryBuilder() { ; }

void IxSqlQueryBuilder::displaySqlQuery(int time_ms /* = -1 */) const
{
   if (time_ms < 0)  { qDebug("[QxOrm] sql query : %s", qPrintable(m_sSqlQuery)); }
   else              { qDebug("[QxOrm] sql query (%d ms) : %s", time_ms, qPrintable(m_sSqlQuery)); }
}

void IxSqlQueryBuilder::initIdX(long lAllRelationCount)
{
   if (! m_bCartesianProduct) { qAssert(false); return; }
   m_pIdX.reset(new type_lst_ptr_by_id());
   for (long l = 0; l < (lAllRelationCount + 1); ++l)
   { type_ptr_by_id_ptr pItem = type_ptr_by_id_ptr(new type_ptr_by_id()); m_pIdX->append(pItem); }
}

bool IxSqlQueryBuilder::insertIdX(long lIndex, const QVariant & idOwner, const QVariant & idData, void * ptr)
{
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
   QString sIdOwner = idOwner.toString(); QString sIdData = idData.toString();
   if (! m_pIdX || sIdOwner.isEmpty() || sIdData.isEmpty()) { qAssert(false); return NULL; }
   if ((lIndex < 0) || (lIndex >= m_pIdX->count())) { qAssert(false); return NULL; }

   type_id idX(sIdOwner, sIdData);
   type_ptr_by_id_ptr pHash = m_pIdX->at(lIndex);
   if (! pHash || ! pHash->contains(idX)) { return NULL; }

   return pHash->value(idX);
}

bool IxSqlQueryBuilder::getAddAutoIncrementIdToUpdateQuery() const
{
   return qx::QxSqlDatabase::getSingleton()->getAddAutoIncrementIdToUpdateQuery();
}

void IxSqlQueryBuilder::addSqlQueryAlias(const QString & sql, const QString & sqlAlias)
{
   m_lstSqlQueryAlias.insert(sql, sqlAlias);
}

void IxSqlQueryBuilder::replaceSqlQueryAlias(QString & sql) const
{
   if (! qx::QxSqlDatabase::getSingleton()->getAutoReplaceSqlAliasIntoQuery()) { return; }
   if (m_lstSqlQueryAlias.count() <= 0) { return; }
   QHashIterator<QString, QString> itr(m_lstSqlQueryAlias);
   sql = (" " + sql);
   while (itr.hasNext())
   {
      itr.next();
      QString sBefore = (" " + itr.key() + ".");
      QString sAfter = (" " + itr.value() + ".");
      sql.replace(sBefore, sAfter);
   }
   sql = sql.trimmed();
}

} // namespace qx
