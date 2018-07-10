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

#ifndef _QX_SQL_RELATION_LINKED_H_
#define _QX_SQL_RELATION_LINKED_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSqlRelationLinked.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Hierarchy of relationships to build SQL query
 */

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/tuple/tuple_io.hpp>

#include <QtSql/qsqlerror.h>

#include <QxCommon/QxBool.h>

#include <QxDao/IxSqlRelation.h>

#include <QxCollection/QxCollection.h>

namespace qx {

/*!
 * \ingroup QxDao
 * \brief qx::QxSqlRelationLinked : hierarchy of relationships to build SQL query
 *
 * Here is the structure, each real relation has a relation linked associated to build the hierarchy, like this :
 * \code
(<root>, <relation_linked>)
   ("blog", blog_relation)
   ("blog", <relation_linked>)
      ("author", author_relation)
      ("author", <relation_linked>)
         ("list_blog", list_blog_relation)
         ("list_blog", <relation_linked>)
            (etc...)
      ("comment", comment_relation)
      ("comment", <relation_linked>)
         ("blog_id", blog_id_relation)
         ("blog_id", <relation_linked>)
            (etc...)
      ("category", category_relation)
      ("category", <relation_linked>)
         ("list_blog", list_blog_relation)
         ("list_blog", <relation_linked>)
            (etc...)
 * \endcode
 */
class QX_DLL_EXPORT QxSqlRelationLinked
{

protected:

   typedef qx_shared_ptr<QxSqlRelationLinked> type_ptr;
   typedef boost::tuple<qx::dao::sql_join::join_type, IxSqlRelation *, QPair<QSet<QString>, long> > type_relation;
   typedef qx::QxCollection<QString, type_relation> type_lst_relation;
   typedef QHash<QString, type_ptr> type_lst_relation_linked;

   type_lst_relation m_relationX;               //!< List of relationships for current level
   type_lst_relation_linked m_relationLinkedX;  //!< List of child to build the hierarchy
   IxSqlRelationX * m_allRelationX;             //!< List of all relationships per level
   bool m_bRoot;                                //!< Root of the hierarchy
   QSet<QString> m_lstRootColumns;              //!< Root columns to fetch (using syntax { col_1, col_2, etc... } ), if empty then fetch all root columns
   long m_lRootColumnsOffset;                   //!< Root columns offset to resolve SQL query output
   bool m_bRootColumnsModeRemove;               //!< Special syntax to remove root columns instead of adding root columns : -{ column1, column2, etc... }

public:

   QxSqlRelationLinked();
   QxSqlRelationLinked(bool bRoot);
   virtual ~QxSqlRelationLinked();

   qx_bool buildHierarchy(IxSqlRelationX * pRelationX, const QStringList & sRelationX);

   void hierarchySelect(QxSqlRelationParams & params);
   void hierarchyFrom(QxSqlRelationParams & params);
   void hierarchyJoin(QxSqlRelationParams & params);
   void hierarchyWhereSoftDelete(QxSqlRelationParams & params);
   void hierarchyResolveOutput(QxSqlRelationParams & params);
   QSqlError hierarchyOnBeforeSave(QxSqlRelationParams & params);
   QSqlError hierarchyOnAfterSave(QxSqlRelationParams & params);
   void updateOffset(QxSqlRelationParams & params);

   bool getCartesianProduct() const;
   long getAllRelationCount() const;
   long getRelationCount() const;
   bool existRelation(const QString & sKey) const;

   bool checkRootColumns(const QString & s) const  { return (m_lstRootColumns.isEmpty() || (m_bRootColumnsModeRemove ? (! m_lstRootColumns.contains(s)) : m_lstRootColumns.contains(s))); }
   long getRootColumnsCount() const                { return m_lstRootColumns.count(); }
   long getRootColumnsOffset() const               { return m_lRootColumnsOffset; }
   void setRootColumnsOffset(long l)               { m_lRootColumnsOffset = l; }

protected:

   QStringList removeColumns(const QStringList & columnsToRemove, IxSqlRelation * pRelation) const;
   qx_bool insertRelationToHierarchy(const QStringList & sRelationX, const QString & sKey, qx::dao::sql_join::join_type eJoinType);
   bool isValidDaoHelper(QxSqlRelationParams & params) const;

};

typedef qx_shared_ptr<QxSqlRelationLinked> QxSqlRelationLinked_ptr;

} // namespace qx

#endif // _QX_SQL_RELATION_LINKED_H_
