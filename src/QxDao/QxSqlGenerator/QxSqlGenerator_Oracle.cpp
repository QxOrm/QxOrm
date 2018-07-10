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

#include <QxDao/QxSqlGenerator/QxSqlGenerator_Oracle.h>

#include <QxDao/QxSqlDatabase.h>

#include <QxRegister/QxClassX.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace dao {
namespace detail {

QxSqlGenerator_Oracle::QxSqlGenerator_Oracle() : QxSqlGenerator_Standard() { this->initSqlTypeByClassName(); }

QxSqlGenerator_Oracle::~QxSqlGenerator_Oracle() { ; }

QString QxSqlGenerator_Oracle::getLimit(const QxSqlLimit * pLimit) const { Q_UNUSED(pLimit); return ""; }

void QxSqlGenerator_Oracle::resolveLimit(QSqlQuery & query, const QxSqlLimit * pLimit) const
{
   if (! pLimit) { qAssert(false); return; }
   QString sMinRow = pLimit->getStartRow_ParamKey();
   QString sMaxRow = pLimit->getMaxRow_ParamKey();
   int iMinRow(pLimit->getStartRow()), iMaxRow(pLimit->getMaxRow());
   bool bQuestionMark = (qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle() == qx::QxSqlDatabase::ph_style_question_mark);
   if (bQuestionMark) { query.addBindValue(iMaxRow); query.addBindValue(iMinRow); }
   else { query.bindValue(sMaxRow, iMaxRow); query.bindValue(sMinRow, iMinRow); }
}

void QxSqlGenerator_Oracle::postProcess(QString & sql, const QxSqlLimit * pLimit) const
{
   if (! pLimit) { qAssert(false); return; }
   QString sMinRow = pLimit->getStartRow_ParamKey();
   QString sMaxRow = pLimit->getMaxRow_ParamKey();
   QString sReplace = "%SQL_QUERY%";

   QString sqlPaging;
   sqlPaging += "SELECT * FROM ";
   sqlPaging += "   ( SELECT a.*, ROWNUM rnum FROM ";
   sqlPaging += "      ( " + sReplace + " ) a ";
   sqlPaging += "     WHERE ROWNUM <= " + sMaxRow + " ) ";
   sqlPaging += "WHERE rnum >= " + sMinRow;
   sqlPaging.replace(sReplace, sql);
   sql = sqlPaging;
}

void QxSqlGenerator_Oracle::initSqlTypeByClassName() const
{
   QHash<QString, QString> * lstSqlType = qx::QxClassX::getAllSqlTypeByClassName();
   if (! lstSqlType) { qAssert(false); return; }

   lstSqlType->insert("bool", "SMALLINT");
   lstSqlType->insert("qx_bool", "VARCHAR2(4000)");
   lstSqlType->insert("short", "SMALLINT");
   lstSqlType->insert("int", "INTEGER");
   lstSqlType->insert("long", "INTEGER");
   lstSqlType->insert("long long", "INTEGER");
   lstSqlType->insert("float", "FLOAT");
   lstSqlType->insert("double", "FLOAT");
   lstSqlType->insert("long double", "FLOAT");
   lstSqlType->insert("unsigned short", "SMALLINT");
   lstSqlType->insert("unsigned int", "INTEGER");
   lstSqlType->insert("unsigned long", "INTEGER");
   lstSqlType->insert("unsigned long long", "INTEGER");
   lstSqlType->insert("std::string", "VARCHAR2(4000)");
   lstSqlType->insert("std::wstring", "VARCHAR2(4000)");
   lstSqlType->insert("QString", "VARCHAR2(4000)");
   lstSqlType->insert("QVariant", "CLOB");
   lstSqlType->insert("QUuid", "VARCHAR2(255)");
   lstSqlType->insert("QDate", "DATE");
   lstSqlType->insert("QTime", "DATE");
   lstSqlType->insert("QDateTime", "TIMESTAMP");
   lstSqlType->insert("QByteArray", "BLOB");
   lstSqlType->insert("qx::QxDateNeutral", "VARCHAR2(8)");
   lstSqlType->insert("qx::QxTimeNeutral", "VARCHAR2(6)");
   lstSqlType->insert("qx::QxDateTimeNeutral", "VARCHAR2(14)");
}

} // namespace detail
} // namespace dao
} // namespace qx
