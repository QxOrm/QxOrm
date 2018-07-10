/****************************************************************************
**
** http://www.qxorm.com/
** http://sourceforge.net/projects/qxorm/
** Original file by Lionel Marty
**
** This file is part of the QxOrm library
**
** This software is provided 'as-is', without any express or implied
** warranty. In no event will the authors be held liable for any
** damages arising from the use of this software.
**
** GNU Lesser General Public License Usage
** This file must be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file 'license.lgpl.txt' included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you have questions regarding the use of this file, please contact :
** contact@qxorm.com
**
****************************************************************************/

#include "../../include/QxPrecompiled.h"

#include <QtSql/qsqlquery.h>
#include <QtSql/qsqlrecord.h>

#include "../../include/QxDao/IxSqlRelation.h"
#include "../../include/QxDao/IxSqlQueryBuilder.h"

#include "../../include/QxDataMember/IxDataMember.h"
#include "../../include/QxDataMember/IxDataMemberX.h"

#include "../../include/QxMemLeak/mem_leak.h"

namespace qx {

IxSqlRelation::~IxSqlRelation() { ; }

QString IxSqlRelation::getKey() const
{ return (m_pDataMember ? m_pDataMember->getKey() : ""); }

long IxSqlRelation::getDataCount() const
{ return (m_lstDataMemberPtr ? m_lstDataMemberPtr->count() : 0); }

long IxSqlRelation::getRelationCount() const
{ return (m_lstSqlRelationPtr ? m_lstSqlRelationPtr->count() : 0); }

IxDataMember * IxSqlRelation::getDataByKey(const QString & sKey) const
{ return ((m_lstDataMemberPtr && m_lstDataMemberPtr->exist(sKey)) ? m_lstDataMemberPtr->getByKey(sKey) : ((m_lstSqlRelationPtr && m_lstSqlRelationPtr->exist(sKey)) ? m_lstSqlRelationPtr->getByKey(sKey)->getDataMember() : NULL)); }

IxDataMember * IxSqlRelation::nextData(long & lIndex) const
{ if ((! m_lstDataMemberPtr) || (lIndex < 0) || (lIndex >= m_lstDataMemberPtr->count())) { return NULL; }; ++lIndex; return m_lstDataMemberPtr->getByIndex(lIndex - 1); }

IxSqlRelation * IxSqlRelation::nextRelation(long & lIndex) const
{ if ((! m_lstSqlRelationPtr) || (lIndex < 0) || (lIndex >= m_lstSqlRelationPtr->count())) { return NULL; }; ++lIndex; return m_lstSqlRelationPtr->getByIndex(lIndex - 1); }

QString IxSqlRelation::table() const
{ return (m_pDataMemberX ? m_pDataMemberX->getName() : ""); }

QString IxSqlRelation::tableAlias(QxSqlRelationParams & params) const
{ return (m_pDataMemberX ? (m_pDataMemberX->getName() + "_" + QString::number(params.index())) : ""); }

QString IxSqlRelation::getSqlJoin() const
{
   QString sJoin;
   switch (m_eJoinType)
   {
      case left_outer_join:   sJoin = " LEFT OUTER JOIN ";                    break;
      case inner_join:        sJoin = " INNER JOIN ";                         break;
      default:                qAssert(false); sJoin = " LEFT OUTER JOIN ";    break;
   }

   return sJoin;
}

#ifndef NDEBUG
bool IxSqlRelation::verifyOffset(QxSqlRelationParams & params, bool bId) const
{
   IxDataMember * p = (bId ? this->getDataId() : this->getDataMember());
   QString table = (bId ? this->tableAlias(params) : params.builder().table());
   if (! p || table.isEmpty()) { return true; }
   int index = params.query().record().indexOf(p->getSqlAlias(& table));
   qAssert(index == params.offset());

   return (index == params.offset());
}
#endif // NDEBUG

} // namespace qx
