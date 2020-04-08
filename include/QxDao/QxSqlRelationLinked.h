/****************************************************************************
**
** https://www.qxorm.com/
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

#include <QtSql/qsqlerror.h>

#include <QxCommon/QxBool.h>

#include <QxDao/IxSqlRelation.h>

#include <QxCollection/QxCollection.h>

namespace qx {
namespace dao {
namespace detail {

class IxDao_Helper;

} // namespace detail
} // namespace dao
} // namespace qx

namespace qx {

class IxClass;

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

public:

   typedef std::shared_ptr<QxSqlRelationLinked> type_ptr;
   typedef std::tuple<qx::dao::sql_join::join_type, IxSqlRelation *, QPair<QSet<QString>, long>, QString> type_relation;
   typedef qx::QxCollection<QString, type_relation> type_lst_relation;
   typedef QHash<QString, type_ptr> type_lst_relation_linked;

private:

   struct QxSqlRelationLinkedImpl;
   std::unique_ptr<QxSqlRelationLinkedImpl> m_pImpl; //!< Private implementation idiom

public:

   QxSqlRelationLinked();
   QxSqlRelationLinked(bool bRoot);
   virtual ~QxSqlRelationLinked();

   static type_ptr getHierarchy(IxClass * pClass, const QStringList & sRelationX, qx_bool & bOk, qx::dao::detail::IxDao_Helper * pDaoHelper = NULL);

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
   type_lst_relation_linked getRelationLinkedX() const;
   type_lst_relation getRelationX() const;

   bool isRoot() const;
   bool checkRootColumns(const QString & s) const;
   long getRootColumnsCount() const;
   long getRootColumnsOffset() const;
   void setRootColumnsOffset(long l);
   QString getRootCustomAlias() const;

protected:

   bool isValidDaoHelper(QxSqlRelationParams & params) const;

};

typedef std::shared_ptr<QxSqlRelationLinked> QxSqlRelationLinked_ptr;

} // namespace qx

#endif // _QX_SQL_RELATION_LINKED_H_
