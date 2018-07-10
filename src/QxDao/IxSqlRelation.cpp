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

#include <QtSql/qsqlquery.h>
#include <QtSql/qsqlrecord.h>

#include <QxDao/IxSqlRelation.h>
#include <QxDao/IxSqlQueryBuilder.h>
#include <QxDao/QxSqlDatabase.h>

#include <QxDataMember/IxDataMember.h>
#include <QxDataMember/IxDataMemberX.h>

#include <QxRegister/IxClass.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

IxSqlRelation::~IxSqlRelation() { ; }

QString IxSqlRelation::getKey() const
{ return (m_pDataMember ? m_pDataMember->getKey() : ""); }

long IxSqlRelation::getDataCount() const
{ return (m_lstDataMemberPtr ? m_lstDataMemberPtr->count() : 0); }

long IxSqlRelation::getRelationCount() const
{ return (m_lstSqlRelationPtr ? m_lstSqlRelationPtr->count() : 0); }

QString IxSqlRelation::table() const
{ return (m_pDataMemberX ? m_pDataMemberX->getName() : ""); }

bool IxSqlRelation::traceSqlQuery() const
{ return qx::QxSqlDatabase::getSingleton()->getTraceSqlQuery(); }

IxDataMember * IxSqlRelation::getDataByKey(const QString & sKey) const
{
   if (m_lstDataMemberPtr && m_lstDataMemberPtr->exist(sKey)) { return m_lstDataMemberPtr->getByKey(sKey); }
   else if (m_lstSqlRelationPtr && m_lstSqlRelationPtr->exist(sKey)) { return m_lstSqlRelationPtr->getByKey(sKey)->getDataMember(); }
   return NULL;
}

IxDataMember * IxSqlRelation::nextData(long & lIndex) const
{
   if ((! m_lstDataMemberPtr) || (lIndex < 0) || (lIndex >= m_lstDataMemberPtr->count())) { return NULL; }
   ++lIndex;
   return m_lstDataMemberPtr->getByIndex(lIndex - 1);
}

IxSqlRelation * IxSqlRelation::nextRelation(long & lIndex) const
{
   if ((! m_lstSqlRelationPtr) || (lIndex < 0) || (lIndex >= m_lstSqlRelationPtr->count())) { return NULL; }
   ++lIndex;
   return m_lstSqlRelationPtr->getByIndex(lIndex - 1);
}

QString IxSqlRelation::tableAlias(QxSqlRelationParams & params) const
{
   QString sTableAlias = (m_pDataMemberX ? (m_pDataMemberX->getName() + "_" + QString::number(params.index())) : QString(""));
   sTableAlias.replace(".", "_");
   return sTableAlias;
}

QString IxSqlRelation::tableAliasOwner(QxSqlRelationParams & params) const
{
   if (! m_pClassOwner) { qAssert(false); return ""; }
   QString sTableAliasOwner = (m_pClassOwner->getName() + "_" + QString::number(params.indexOwner()));
   if (params.indexOwner() <= 0) { sTableAliasOwner = params.builder().table(); }
   sTableAliasOwner.replace(".", "_");
   return sTableAliasOwner;
}

QString IxSqlRelation::getSqlJoin(qx::dao::sql_join::join_type e /* = qx::dao::sql_join::no_join */) const
{
   QString sJoin;
   if (e == qx::dao::sql_join::no_join) { e = m_eJoinType; }

   switch (e)
   {
      case qx::dao::sql_join::left_outer_join:  sJoin = " LEFT OUTER JOIN ";     break;
      case qx::dao::sql_join::inner_join:       sJoin = " INNER JOIN ";          break;
      default:                                  sJoin = " LEFT OUTER JOIN ";     break;
   }

   return sJoin;
}

#ifndef NDEBUG
bool IxSqlRelation::verifyOffset(QxSqlRelationParams & params, bool bId) const
{
   if (! qx::QxSqlDatabase::getSingleton()->getVerifyOffsetRelation()) { return true; }
   IxDataMember * p = (bId ? this->getDataId() : this->getDataMember());
   QString table = (bId ? this->tableAlias(params) : this->tableAliasOwner(params));
   if (! p || table.isEmpty()) { return true; }
   QString sSuffixAlias = ((! bId && (params.indexOwner() > 0)) ? QString("_" + QString::number(params.indexOwner())) : QString());
   int index = params.query().record().indexOf(p->getSqlAlias(table) + sSuffixAlias);
   qAssert(index == params.offset());

   return (index == params.offset());
}
#endif // NDEBUG

} // namespace qx
