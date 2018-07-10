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

#ifndef _IX_SQL_RELATION_H_
#define _IX_SQL_RELATION_H_

#ifdef _MSC_VER
#pragma once
#endif

#include "../../include/QxDao/QxSqlRelationParams.h"

#include "../../include/QxCollection/QxCollection.h"

namespace qx {

class IxDataMember;
class IxDataMemberX;
class IxSqlRelation;

typedef QxCollection<QString, IxSqlRelation *> IxSqlRelationX;

class QX_DLL_EXPORT IxSqlRelation
{

public:

   enum join_type { left_outer_join, inner_join };

protected:

   IxDataMember *    m_pDataMember;       // 'IxDataMember' associated wth sql relation
   IxDataMemberX *   m_pDataMemberX;      // Collection of 'IxDataMember' : parent of 'm_pDataMember'
   IxDataMember *    m_pDataMemberId;     // 'IxDataMember' id of 'm_pDataMemberX'
   long              m_lOffsetRelation;   // Generic offset for sql relation
   join_type         m_eJoinType;         // Join type to build sql query

   QxCollection<QString, IxDataMember *> * m_lstDataMemberPtr;    // Optimization : handle to collection of 'IxDataMember'
   IxSqlRelationX * m_lstSqlRelationPtr;                          // Optimization : handle to collection of 'IxSqlRelation'

public:

   IxSqlRelation(IxDataMember * p) : m_pDataMember(p), m_pDataMemberX(NULL), m_pDataMemberId(NULL), m_lOffsetRelation(100), m_eJoinType(left_outer_join), m_lstDataMemberPtr(NULL), m_lstSqlRelationPtr(NULL) { qAssert(p); }
   virtual ~IxSqlRelation() = 0;

   inline QxCollection<QString, IxDataMember *> * getLstDataMember() const { return m_lstDataMemberPtr; }
   inline IxSqlRelationX * getLstRelation() const                          { return m_lstSqlRelationPtr; }

   inline void setSqlJoinType(join_type e)         { m_eJoinType = e; }
   inline join_type getSqlJoinType() const         { return m_eJoinType; }
   inline IxDataMember * getDataMember() const     { return m_pDataMember; }
   inline IxDataMemberX * getDataMemberX() const   { return m_pDataMemberX; }
   inline IxDataMember * getDataId() const         { return m_pDataMemberId; }

   QString getKey() const;
   long getDataCount() const;
   long getRelationCount() const;
   IxDataMember * getDataByKey(const QString & sKey) const;
   IxDataMember * nextData(long & lIndex) const;
   IxSqlRelation * nextRelation(long & lIndex) const;
   QString table() const;
   QString tableAlias(QxSqlRelationParams & params) const;
   QString getSqlJoin() const;

   virtual void init() = 0;
   virtual bool getCartesianProduct() const = 0;
   virtual QVariant getIdFromQuery(bool bEager, QxSqlRelationParams & params) const = 0;
   virtual void updateOffset(bool bEager, QxSqlRelationParams & params) const = 0;
   virtual void createTable(QxSqlRelationParams & params) const = 0;
   virtual void lazySelect(QxSqlRelationParams & params) const = 0;
   virtual void eagerSelect(QxSqlRelationParams & params) const = 0;
   virtual void lazyFrom(QxSqlRelationParams & params) const = 0;
   virtual void eagerFrom(QxSqlRelationParams & params) const = 0;
   virtual void lazyJoin(QxSqlRelationParams & params) const = 0;
   virtual void eagerJoin(QxSqlRelationParams & params) const = 0;
   virtual void lazyWhere(QxSqlRelationParams & params) const = 0;
   virtual void eagerWhere(QxSqlRelationParams & params) const = 0;
   virtual void lazyFetch_ResolveInput(QxSqlRelationParams & params) const = 0;
   virtual void eagerFetch_ResolveInput(QxSqlRelationParams & params) const = 0;
   virtual void lazyFetch_ResolveOutput(QxSqlRelationParams & params) const = 0;
   virtual void eagerFetch_ResolveOutput(QxSqlRelationParams & params) const = 0;
   virtual void lazyInsert(QxSqlRelationParams & params) const = 0;
   virtual void lazyInsert_Values(QxSqlRelationParams & params) const = 0;
   virtual void lazyUpdate(QxSqlRelationParams & params) const = 0;
   virtual void lazyInsert_ResolveInput(QxSqlRelationParams & params) const = 0;
   virtual void lazyUpdate_ResolveInput(QxSqlRelationParams & params) const = 0;
   virtual QSqlError onBeforeSave(QxSqlRelationParams & params) const = 0;
   virtual QSqlError onAfterSave(QxSqlRelationParams & params) const = 0;

#ifndef NDEBUG
   bool verifyOffset(QxSqlRelationParams & params, bool bId) const;
#else
   inline bool verifyOffset(QxSqlRelationParams & params, bool bId) const { Q_UNUSED(params); Q_UNUSED(bId); return true; }
#endif // NDEBUG

};

} // namespace qx

#endif // _IX_SQL_RELATION_H_
