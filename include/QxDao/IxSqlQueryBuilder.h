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

#ifndef _IX_SQL_QUERY_BUILDER_H_
#define _IX_SQL_QUERY_BUILDER_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QxDataMember/IxDataMemberX.h>

#include <QxDao/IxSqlRelation.h>

namespace qx {

class QX_DLL_EXPORT IxSqlQueryBuilder
{

public:

   typedef QPair<QString, QString> type_id;
   typedef QHash<type_id, void *> type_ptr_by_id;
   typedef boost::shared_ptr<type_ptr_by_id> type_ptr_by_id_ptr;
   typedef QList<type_ptr_by_id_ptr> type_lst_ptr_by_id;
   typedef boost::shared_ptr<type_lst_ptr_by_id> type_lst_ptr_by_id_ptr;

protected:

   QxCollection<QString, IxDataMember *> * m_lstDataMemberPtr;    // Collection of 'IxDataMember' to build sql query
   IxSqlRelationX * m_lstSqlRelationPtr;                          // Collection of 'IxSqlRelation' to build sql query
   IxDataMember * m_pDataMemberId;                                // Data member id for sql query
   QString m_sSqlQuery;                                           // Current sql query
   QString m_sTableName;                                          // Sql table name of current object
   QString m_sHashRelation;                                       // Optimization : hash to retrieve sql query with relation
   bool m_bCartesianProduct;                                      // Recordset can return cartesian product => same id in multiple records
   type_lst_ptr_by_id_ptr m_pIdX;                                 // Collection of id (and pointer associated) to avoid multiple fetch on same id (cartesian product)

public:

   IxSqlQueryBuilder() : m_lstDataMemberPtr(NULL), m_lstSqlRelationPtr(NULL), m_pDataMemberId(NULL), m_bCartesianProduct(false) { ; }
   IxSqlQueryBuilder(const QString & sql) : m_lstDataMemberPtr(NULL), m_lstSqlRelationPtr(NULL), m_pDataMemberId(NULL), m_sSqlQuery(sql), m_bCartesianProduct(false) { ; }
   virtual ~IxSqlQueryBuilder() = 0;

   inline QxCollection<QString, IxDataMember *> * getLstDataMember() const    { return m_lstDataMemberPtr; }
   inline IxSqlRelationX * getLstRelation() const                             { return m_lstSqlRelationPtr; }

   inline void setSqlQuery(const QString & sql)          { m_sSqlQuery = sql; }
   inline void setHashRelation(const QString & s)        { m_sHashRelation = s; }
   inline void setCartesianProduct(bool b)               { m_bCartesianProduct = b; }
   inline QString getSqlQuery() const                    { return m_sSqlQuery; }
   inline QString getHashRelation() const                { return m_sHashRelation; }
   inline QString table() const                          { return m_sTableName; }
   inline bool getCartesianProduct() const               { return m_bCartesianProduct; }
   inline long getDataCount() const                      { return (m_lstDataMemberPtr ? m_lstDataMemberPtr->count() : 0); }
   inline long getRelationCount() const                  { return (m_lstSqlRelationPtr ? m_lstSqlRelationPtr->count() : 0); }
   inline IxDataMember * getDataId() const               { return m_pDataMemberId; }
   inline IxDataMember * nextData(long & l) const        { if ((! m_lstDataMemberPtr) || (l < 0) || (l >= m_lstDataMemberPtr->count())) { return NULL; }; ++l; return m_lstDataMemberPtr->getByIndex(l - 1); }
   inline IxSqlRelation * nextRelation(long & l) const   { if ((! m_lstSqlRelationPtr) || (l < 0) || (l >= m_lstSqlRelationPtr->count())) { return NULL; }; ++l; return m_lstSqlRelationPtr->getByIndex(l - 1); }

   void displaySqlQuery(int time_ms = -1) const;
   bool insertIdX(long lIndex, const QVariant & idOwner, const QVariant & idData, void * ptr);
   void * existIdX(long lIndex, const QVariant & idOwner, const QVariant & idData);

   virtual void init() = 0;
   virtual IxDataMemberX * getDataMemberX() const = 0;

   virtual IxSqlQueryBuilder & count() = 0;
   virtual IxSqlQueryBuilder & exist() = 0;
   virtual IxSqlQueryBuilder & fetchAll() = 0;
   virtual IxSqlQueryBuilder & fetchById() = 0;
   virtual IxSqlQueryBuilder & insert() = 0;
   virtual IxSqlQueryBuilder & update() = 0;
   virtual IxSqlQueryBuilder & deleteAll() = 0;
   virtual IxSqlQueryBuilder & deleteById() = 0;
   virtual IxSqlQueryBuilder & createTable() = 0;

   virtual IxSqlQueryBuilder & fetchAll(const QStringList & columns) = 0;
   virtual IxSqlQueryBuilder & fetchById(const QStringList & columns) = 0;
   virtual IxSqlQueryBuilder & update(const QStringList & columns) = 0;

   virtual IxSqlQueryBuilder & fetchAll_WithRelation(IxSqlRelationX * pRelationX) = 0;
   virtual IxSqlQueryBuilder & fetchById_WithRelation(IxSqlRelationX * pRelationX) = 0;

private:

   void initIdX();

};

typedef boost::shared_ptr<IxSqlQueryBuilder> IxSqlQueryBuilder_ptr;

} // namespace qx

#endif // _IX_SQL_QUERY_BUILDER_H_
