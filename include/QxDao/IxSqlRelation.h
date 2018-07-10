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

private:

   struct IxSqlRelationImpl;
   std::unique_ptr<IxSqlRelationImpl> m_pImpl; //!< Private implementation idiom

public:

   enum relation_type { no_relation, one_to_one, one_to_many, many_to_one, many_to_many };

   IxSqlRelation(IxDataMember * p);
   virtual ~IxSqlRelation() = 0;

   QxCollection<QString, IxDataMember *> * getLstDataMember() const;
   IxSqlRelationX * getLstRelation() const;

   void setSqlJoinType(qx::dao::sql_join::join_type e);
   qx::dao::sql_join::join_type getSqlJoinType() const;
   relation_type getRelationType() const;
   IxClass * getClass() const;
   IxClass * getClassOwner() const;
   IxDataMember * getDataMember() const;
   IxDataMemberX * getDataMemberX() const;
   IxDataMember * getDataId() const;
   IxDataMember * getDataIdOwner() const;

   QString getKey() const;
   QString getForeignKey() const;
   QString getForeignKeyOwner() const;
   QString getForeignKeyDataType() const;
   QString getExtraTable() const;
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

   virtual void init();
   virtual QString getDescription() const = 0;
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

   bool verifyOffset(QxSqlRelationParams & params, bool bId) const QX_USED;

   static void setTraceRelationInit(bool bTrace);

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

   bool canInit() const;
   void setIsSameDataOwner(int i);
   void setClass(IxClass * pClass, IxClass * pClassOwner);
   void setRelationType(relation_type e);
   void setForeignKey(const QString & s) const;
   void setForeignKeyOwner(const QString & s) const;
   void setForeignKeyDataType(const QString & s) const;
   void setExtraTable(const QString & s) const;

};

} // namespace qx

#endif // _IX_SQL_RELATION_H_
