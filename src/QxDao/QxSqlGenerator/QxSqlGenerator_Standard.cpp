/****************************************************************************
**
** https://www.qxorm.com/
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

#include <QxDao/QxSqlGenerator/QxSqlGenerator_Standard.h>

#include <QxDao/QxSqlDatabase.h>
#include <QxDao/IxDao_Helper.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace dao {
namespace detail {

QxSqlGenerator_Standard::QxSqlGenerator_Standard() : IxSqlGenerator() { ; }

QxSqlGenerator_Standard::~QxSqlGenerator_Standard() { ; }

void QxSqlGenerator_Standard::init() { ; }

QString QxSqlGenerator_Standard::getAutoIncrement() const { return "AUTOINCREMENT"; }

QString QxSqlGenerator_Standard::getWildCard() const { return "%"; }

QString QxSqlGenerator_Standard::getTableAliasSep() const { return " AS "; }

QString QxSqlGenerator_Standard::getLimit(const QxSqlLimit * pLimit) const
{
   if (! pLimit) { qAssert(false); return ""; }
   QString sStartRow = pLimit->getStartRow_ParamKey();
   QString sRowsCount = pLimit->getRowsCount_ParamKey();
   return ("LIMIT " + sRowsCount + " OFFSET " + sStartRow);
}

void QxSqlGenerator_Standard::resolveLimit(QSqlQuery & query, const QxSqlLimit * pLimit, qx::QxCollection<QString, QVariantList> * pLstExecBatch /* = NULL */) const
{
   if (! pLimit) { qAssert(false); return; }
   QString sStartRow = pLimit->getStartRow_ParamKey();
   QString sRowsCount = pLimit->getRowsCount_ParamKey();
   int iStartRow(pLimit->getStartRow()), iRowsCount(pLimit->getRowsCount());
   bool bQuestionMark = (qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle() == qx::QxSqlDatabase::ph_style_question_mark);

   if (pLstExecBatch)
   {
      if (! pLstExecBatch->exist(sRowsCount)) { QVariantList empty; pLstExecBatch->insert(sRowsCount, empty); }
      if (! pLstExecBatch->exist(sStartRow)) { QVariantList empty; pLstExecBatch->insert(sStartRow, empty); }
      QVariantList & valuesRowsCount = const_cast<QVariantList &>(pLstExecBatch->getByKey(sRowsCount));
      QVariantList & valuesStartRow = const_cast<QVariantList &>(pLstExecBatch->getByKey(sStartRow));
      valuesRowsCount.append(iRowsCount);
      valuesStartRow.append(iStartRow);
   }
   else
   {
      if (bQuestionMark) { query.addBindValue(iRowsCount); query.addBindValue(iStartRow); }
      else { query.bindValue(sRowsCount, iRowsCount); query.bindValue(sStartRow, iStartRow); }
   }
}

void QxSqlGenerator_Standard::postProcess(QString & sql, const QxSqlLimit * pLimit) const { Q_UNUSED(sql); Q_UNUSED(pLimit); }

void QxSqlGenerator_Standard::onBeforeInsert(IxDao_Helper * pDaoHelper, void * pOwner) const { Q_UNUSED(pDaoHelper); Q_UNUSED(pOwner); }

void QxSqlGenerator_Standard::onAfterInsert(IxDao_Helper * pDaoHelper, void * pOwner) const { Q_UNUSED(pDaoHelper); Q_UNUSED(pOwner); }

void QxSqlGenerator_Standard::onBeforeUpdate(IxDao_Helper * pDaoHelper, void * pOwner) const { Q_UNUSED(pDaoHelper); Q_UNUSED(pOwner); }

void QxSqlGenerator_Standard::onAfterUpdate(IxDao_Helper * pDaoHelper, void * pOwner) const { Q_UNUSED(pDaoHelper); Q_UNUSED(pOwner); }

void QxSqlGenerator_Standard::onBeforeDelete(IxDao_Helper * pDaoHelper, void * pOwner) const { Q_UNUSED(pDaoHelper); Q_UNUSED(pOwner); }

void QxSqlGenerator_Standard::onAfterDelete(IxDao_Helper * pDaoHelper, void * pOwner) const { Q_UNUSED(pDaoHelper); Q_UNUSED(pOwner); }

void QxSqlGenerator_Standard::checkSqlInsert(IxDao_Helper * pDaoHelper, QString & sql) const { Q_UNUSED(pDaoHelper); Q_UNUSED(sql); }

void QxSqlGenerator_Standard::onBeforeSqlPrepare(IxDao_Helper * pDaoHelper, QString & sql) const { Q_UNUSED(pDaoHelper); Q_UNUSED(sql); }

void QxSqlGenerator_Standard::formatSqlQuery(IxDao_Helper * pDaoHelper, QString & sql) const
{
   Q_UNUSED(pDaoHelper);

   if (sql.startsWith("SELECT ")) { sql = "\nSELECT " + sql.right(sql.size() - 7); }
   else if (sql.startsWith("INSERT ")) { sql = "\nINSERT " + sql.right(sql.size() - 7); }
   else if (sql.startsWith("UPDATE ")) { sql = "\nUPDATE " + sql.right(sql.size() - 7); }
   else if (sql.startsWith("DELETE ")) { sql = "\nDELETE " + sql.right(sql.size() - 7); }
   else if (sql.startsWith("CREATE ")) { sql = "\nCREATE " + sql.right(sql.size() - 7); }

   sql.replace(" FROM ", "\n  FROM ");
   sql.replace(" WHERE ", "\n  WHERE ");
   sql.replace(" LEFT OUTER JOIN ", "\n  LEFT OUTER JOIN ");
   sql.replace(" INNER JOIN ", "\n  INNER JOIN ");
   sql.replace(" ORDER BY ", "\n  ORDER BY ");
   sql.replace(" GROUP BY ", "\n  GROUP BY ");
   sql.replace(" AND ", "\n  AND ");
   sql.replace(" OR ", "\n  OR ");
   sql.replace(" VALUES ", "\n  VALUES ");
   sql.replace(" SET ", "\n  SET ");
   sql.replace(" RETURNING ", "\n  RETURNING ");
   sql += "\n";
}

} // namespace detail
} // namespace dao
} // namespace qx
