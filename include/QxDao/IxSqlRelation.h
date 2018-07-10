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

#ifndef _IX_SQL_RELATION_H_
#define _IX_SQL_RELATION_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file IxSqlRelation.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Common interface for all relationships defined between 2 classes (or between 2 tables in database)
 */

#include <QxCommon/QxPropertyBag.h>

#include <QxDao/QxSqlRelationParams.h>
#include <QxDao/QxSoftDelete.h>
#include <QxDao/QxSqlJoin.h>

#include <QxCollection/QxCollection.h>

#define QX_CONSTRUCT_IX_RELATION() \
m_pClass(NULL), m_pClassOwner(NULL), m_pDataMember(p), m_pDataMemberX(NULL), \
m_pDataMemberId(NULL), m_pDataMemberIdOwner(NULL), m_lOffsetRelation(100), \
m_eJoinType(qx::dao::sql_join::left_outer_join), m_eRelationType(no_relation), \
m_lstDataMemberPtr(NULL), m_lstSqlRelationPtr(NULL)

namespace qx {

class IxClass;
class IxDataMember;
class IxDataMemberX;
class IxSqlRelation;

typedef QxCollection<QString, IxSqlRelation *> IxSqlRelationX;

/*!
 * \ingroup QxDao
 * \brief qx::IxSqlRelation : common interface for all relationships defined between 2 classes (or between 2 tables in database)
 */
class QX_DLL_EXPORT IxSqlRelation : public qx::QxPropertyBag
{

public:

   enum relation_type { no_relation, one_to_one, one_to_many, many_to_one, many_to_many };

protected:

   IxClass *                        m_pClass;               //!< 'IxClass' associated wth sql relation
   IxClass *                        m_pClassOwner;          //!< 'IxClass' of the owner
   IxDataMember *                   m_pDataMember;          //!< 'IxDataMember' associated wth sql relation
   IxDataMemberX *                  m_pDataMemberX;         //!< Collection of 'IxDataMember' : parent of 'm_pDataMember'
   IxDataMember *                   m_pDataMemberId;        //!< 'IxDataMember' id of 'm_pDataMemberX'
   IxDataMember *                   m_pDataMemberIdOwner;   //!< 'IxDataMember' id of the owner
   long                             m_lOffsetRelation;      //!< Generic offset for sql relation
   qx::dao::sql_join::join_type     m_eJoinType;            //!< Join type to build sql query
   relation_type                    m_eRelationType;        //!< Relation type : one-to-one, one-to-many, etc.
   QxSoftDelete                     m_oSoftDelete;          //!< Soft delete (or logical delete) behavior
   QString                          m_sForeignKey;          //!< SQL query foreign key (1-n)
   QString                          m_sExtraTable;          //!< Extra-table that holds the relationship (n-n)
   QString                          m_sForeignKeyOwner;     //!< SQL query foreign key for owner (n-n)
   QString                          m_sForeignKeyDataType;  //!< SQL query foreign key for data type (n-n)

   QxCollection<QString, IxDataMember *> * m_lstDataMemberPtr;    //!< Optimization : handle to collection of 'IxDataMember'
   IxSqlRelationX * m_lstSqlRelationPtr;                          //!< Optimization : handle to collection of 'IxSqlRelation'

public:

   IxSqlRelation(IxDataMember * p) : qx::QxPropertyBag(), QX_CONSTRUCT_IX_RELATION() { ; }
   virtual ~IxSqlRelation() = 0;

   inline QxCollection<QString, IxDataMember *> * getLstDataMember() const { return m_lstDataMemberPtr; }
   inline IxSqlRelationX * getLstRelation() const                          { return m_lstSqlRelationPtr; }

   inline void setSqlJoinType(qx::dao::sql_join::join_type e)     { m_eJoinType = e; }
   inline qx::dao::sql_join::join_type getSqlJoinType() const     { return m_eJoinType; }
   inline relation_type getRelationType() const                   { return m_eRelationType; }
   inline IxClass * getClass() const                              { return m_pClass; }
   inline IxClass * getClassOwner() const                         { return m_pClassOwner; }
   inline IxDataMember * getDataMember() const                    { return m_pDataMember; }
   inline IxDataMemberX * getDataMemberX() const                  { return m_pDataMemberX; }
   inline IxDataMember * getDataId() const                        { return m_pDataMemberId; }
   inline IxDataMember * getDataIdOwner() const                   { return m_pDataMemberIdOwner; }

   QString getKey() const;
   long getDataCount() const;
   long getRelationCount() const;
   IxDataMember * getDataByKey(const QString & sKey) const;
   IxDataMember * nextData(long & lIndex) const;
   IxSqlRelation * nextRelation(long & lIndex) const;
   QString table() const;
   QString tableAlias(QxSqlRelationParams & params) const;
   QString tableAliasOwner(QxSqlRelationParams & params) const;
   QString getSqlJoin(qx::dao::sql_join::join_type e = qx::dao::sql_join::no_join) const;
   bool traceSqlQuery() const;

   virtual void init() = 0;
   virtual QString getDescription() const = 0;
   virtual QString getExtraTable() const = 0;
   virtual QString createExtraTable() const = 0;
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
   virtual void lazyWhereSoftDelete(QxSqlRelationParams & params) const = 0;
   virtual void eagerWhereSoftDelete(QxSqlRelationParams & params) const = 0;
   virtual void lazyFetch_ResolveInput(QxSqlRelationParams & params) const = 0;
   virtual void eagerFetch_ResolveInput(QxSqlRelationParams & params) const = 0;
   virtual void lazyFetch_ResolveOutput(QxSqlRelationParams & params) const = 0;
   virtual void * eagerFetch_ResolveOutput(QxSqlRelationParams & params) const = 0;
   virtual void lazyInsert(QxSqlRelationParams & params) const = 0;
   virtual void lazyInsert_Values(QxSqlRelationParams & params) const = 0;
   virtual void lazyUpdate(QxSqlRelationParams & params) const = 0;
   virtual void lazyInsert_ResolveInput(QxSqlRelationParams & params) const = 0;
   virtual void lazyUpdate_ResolveInput(QxSqlRelationParams & params) const = 0;
   virtual QSqlError onBeforeSave(QxSqlRelationParams & params) const = 0;
   virtual QSqlError onAfterSave(QxSqlRelationParams & params) const = 0;

   bool verifyOffset(QxSqlRelationParams & params, bool bId) const BOOST_USED;

protected:

   QVariant getIdFromQuery_ManyToMany(bool bEager, QxSqlRelationParams & params) const;
   QVariant getIdFromQuery_ManyToOne(bool bEager, QxSqlRelationParams & params) const;
   QVariant getIdFromQuery_OneToMany(bool bEager, QxSqlRelationParams & params) const;
   QVariant getIdFromQuery_OneToOne(bool bEager, QxSqlRelationParams & params) const;

   void updateOffset_ManyToMany(bool bEager, QxSqlRelationParams & params) const;
   void updateOffset_ManyToOne(bool bEager, QxSqlRelationParams & params) const;
   void updateOffset_OneToMany(bool bEager, QxSqlRelationParams & params) const;
   void updateOffset_OneToOne(bool bEager, QxSqlRelationParams & params) const;

   void eagerSelect_ManyToMany(QxSqlRelationParams & params) const;
   void eagerSelect_ManyToOne(QxSqlRelationParams & params) const;
   void eagerSelect_OneToMany(QxSqlRelationParams & params) const;
   void eagerSelect_OneToOne(QxSqlRelationParams & params) const;

   void eagerJoin_ManyToMany(QxSqlRelationParams & params) const;
   void eagerJoin_ManyToOne(QxSqlRelationParams & params) const;
   void eagerJoin_OneToMany(QxSqlRelationParams & params) const;
   void eagerJoin_OneToOne(QxSqlRelationParams & params) const;

   void eagerWhereSoftDelete_ManyToMany(QxSqlRelationParams & params) const;
   void eagerWhereSoftDelete_ManyToOne(QxSqlRelationParams & params) const;
   void eagerWhereSoftDelete_OneToMany(QxSqlRelationParams & params) const;
   void eagerWhereSoftDelete_OneToOne(QxSqlRelationParams & params) const;

   void lazySelect_ManyToOne(QxSqlRelationParams & params) const;
   void lazyInsert_ManyToOne(QxSqlRelationParams & params) const;
   void lazyInsert_Values_ManyToOne(QxSqlRelationParams & params) const;
   void lazyUpdate_ManyToOne(QxSqlRelationParams & params) const;

   void createTable_ManyToOne(QxSqlRelationParams & params) const;
   QSqlError deleteFromExtraTable_ManyToMany(QxSqlRelationParams & params) const;
   QString createExtraTable_ManyToMany() const;

   bool addLazyRelation(QxSqlRelationParams & params, IxSqlRelation * pRelation) const;

};

} // namespace qx

#endif // _IX_SQL_RELATION_H_
