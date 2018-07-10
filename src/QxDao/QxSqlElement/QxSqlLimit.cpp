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

#include <QxDao/QxSqlElement/QxSqlLimit.h>

#include <QxDao/QxSqlDatabase.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace dao {
namespace detail {

QxSqlLimit::QxSqlLimit() : IxSqlElement(0) { ; }

QxSqlLimit::QxSqlLimit(int index) : IxSqlElement(index) { ; }

QxSqlLimit::~QxSqlLimit() { ; }

IxSqlElement::type_class QxSqlLimit::getTypeClass() const { return IxSqlElement::_sql_limit; }

QString QxSqlLimit::toString() const
{
   if (! m_pSqlGenerator) { qAssert(false); return ""; }
   return m_pSqlGenerator->getLimit(this);
}

void QxSqlLimit::resolve(QSqlQuery & query) const
{
   if (! m_pSqlGenerator) { qAssert(false); return; }
   m_pSqlGenerator->resolveLimit(query, this);
}

void QxSqlLimit::postProcess(QString & sql) const
{
   if (! m_pSqlGenerator) { qAssert(false); return; }
   m_pSqlGenerator->postProcess(sql, this);
}

int QxSqlLimit::getStartRow() const
{
   qAssert(m_lstValues.count() == 2);
   return ((m_lstValues.count() > 0) ? m_lstValues.at(0).toInt() : 0);
}

int QxSqlLimit::getRowsCount() const
{
   qAssert(m_lstValues.count() == 2);
   return ((m_lstValues.count() > 1) ? m_lstValues.at(1).toInt() : 0);
}

int QxSqlLimit::getMaxRow() const
{
   qAssert(m_lstValues.count() == 2);
   return ((m_lstValues.count() > 1) ? (m_lstValues.at(0).toInt() + m_lstValues.at(1).toInt()) : 0);
}

QString QxSqlLimit::getStartRow_ParamKey() const
{
   QString sStartRow("offset_start_row");
   sStartRow += "_" + QString::number(m_iIndex) + "_0";
   if (qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle() == qx::QxSqlDatabase::ph_style_question_mark) { sStartRow = "?"; }
   else if (qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle() == qx::QxSqlDatabase::ph_style_at_name) { sStartRow = "@" + sStartRow; }
   else { sStartRow = ":" + sStartRow; }
   return sStartRow;
}

QString QxSqlLimit::getRowsCount_ParamKey() const
{
   QString sRowsCount("limit_rows_count");
   sRowsCount += "_" + QString::number(m_iIndex) + "_0";
   if (qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle() == qx::QxSqlDatabase::ph_style_question_mark) { sRowsCount = "?"; }
   else if (qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle() == qx::QxSqlDatabase::ph_style_at_name) { sRowsCount = "@" + sRowsCount; }
   else { sRowsCount = ":" + sRowsCount; }
   return sRowsCount;
}

QString QxSqlLimit::getMaxRow_ParamKey() const
{
   QString sMaxRow("offset_max_row");
   sMaxRow += "_" + QString::number(m_iIndex) + "_0";
   if (qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle() == qx::QxSqlDatabase::ph_style_question_mark) { sMaxRow = "?"; }
   else if (qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle() == qx::QxSqlDatabase::ph_style_at_name) { sMaxRow = "@" + sMaxRow; }
   else { sMaxRow = ":" + sMaxRow; }
   return sMaxRow;
}

QString QxSqlLimit::getExtraSettings() const { return ""; }

void QxSqlLimit::setExtraSettings(const QString & s) { Q_UNUSED(s); }

} // namespace detail
} // namespace dao
} // namespace qx
