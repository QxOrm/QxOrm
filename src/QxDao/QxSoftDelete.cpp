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

#include <QxDao/QxSoftDelete.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

QxSoftDelete::QxSoftDelete() : m_eMode(QxSoftDelete::mode_date_time) { ; }

QxSoftDelete::QxSoftDelete(const QString & sColumn) : m_sColumn(sColumn), m_eMode(QxSoftDelete::mode_date_time) { ; }

QxSoftDelete::QxSoftDelete(const QString & sColumn, QxSoftDelete::mode eMode) : m_sColumn(sColumn), m_eMode(eMode) { ; }

QxSoftDelete::~QxSoftDelete() { ; }

QString QxSoftDelete::getTableName() const { return m_sTable; }

QString QxSoftDelete::getColumnName() const { return m_sColumn; }

QString QxSoftDelete::getSqlQueryToFetch() const { return m_sSqlQueryToFetch; }

QString QxSoftDelete::getSqlQueryToUpdate() const { return m_sSqlQueryToUpdate; }

QString QxSoftDelete::getSqlQueryToCreateTable() const { return m_sSqlQueryToCreateTable; }

QxSoftDelete::mode QxSoftDelete::getMode() const { return m_eMode; }

void QxSoftDelete::setTableName(const QString & sTable) { m_sTable = sTable; }

void QxSoftDelete::setColumnName(const QString & sColumn) { m_sColumn = sColumn; }

void QxSoftDelete::setSqlQueryToFetch(const QString & s) { m_sSqlQueryToFetch = s; }

void QxSoftDelete::setSqlQueryToUpdate(const QString & s) { m_sSqlQueryToUpdate = s; }

void QxSoftDelete::setSqlQueryToCreateTable(const QString & s) { m_sSqlQueryToCreateTable = s; }

void QxSoftDelete::setMode(QxSoftDelete::mode eMode) { m_eMode = eMode; }

bool QxSoftDelete::isEmpty() const { return (m_sTable.isEmpty() || m_sColumn.isEmpty()); }

QString QxSoftDelete::buildSqlTablePointName(const QString & sTable /* = QString() */) const
{
   if (this->isEmpty()) { return ""; }
   QString sCurrTable = (sTable.isEmpty() ? m_sTable : sTable);
   sCurrTable.replace(".", "_");
   return (sCurrTable + "." + m_sColumn);
}

QString QxSoftDelete::buildSqlQueryToFetch(const QString & sTable /* = QString() */) const
{
   QString sCurrTable = (sTable.isEmpty() ? m_sTable : sTable);
   sCurrTable.replace(".", "_");
   if (this->isEmpty()) { return ""; }
   else if (! m_sSqlQueryToFetch.isEmpty()) { return m_sSqlQueryToFetch; }
   else if (m_eMode == QxSoftDelete::mode_flag) { return ("(" + sCurrTable + "." + m_sColumn + " IS NULL" + " OR " + sCurrTable + "." + m_sColumn + " = ''" + " OR " + sCurrTable + "." + m_sColumn + " = '0'" + ")"); }
   else if (m_eMode == QxSoftDelete::mode_date_time) { return ("(" + sCurrTable + "." + m_sColumn + " IS NULL" + " OR " + sCurrTable + "." + m_sColumn + " = ''" + ")"); }
   qAssert(false); return "";
}

QString QxSoftDelete::buildSqlQueryToUpdate() const
{
   if (this->isEmpty()) { return ""; }
   else if (! m_sSqlQueryToUpdate.isEmpty()) { return m_sSqlQueryToUpdate; }
   else if (m_eMode == QxSoftDelete::mode_flag) { return (m_sColumn + " = '1'"); }
   else if (m_eMode == QxSoftDelete::mode_date_time) { return (m_sColumn + " = '" + QDateTime::currentDateTime().toString(QX_DAO_SOFT_DELETE_QDATETIME_FORMAT) + "'"); }
   qAssert(false); return "";
}

QString QxSoftDelete::buildSqlQueryToCreateTable() const
{
   if (this->isEmpty()) { return ""; }
   else if (! m_sSqlQueryToCreateTable.isEmpty()) { return m_sSqlQueryToCreateTable; }
   else if (m_eMode == QxSoftDelete::mode_flag) { return (m_sColumn + " " + "TEXT"); }
   else if (m_eMode == QxSoftDelete::mode_date_time) { return (m_sColumn + " " + "TEXT"); }
   qAssert(false); return "";
}

} // namespace qx
