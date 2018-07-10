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

#ifndef _QX_SOFT_DELETE_H_
#define _QX_SOFT_DELETE_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSoftDelete.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Soft delete (or logical delete) behavior to update a row into database (flag it as deleted) instead of delete it from database
 */

#define QX_DAO_SOFT_DELETE_QDATETIME_FORMAT "yyyyMMddhhmmsszzz"

namespace qx {

/*!
 * \ingroup QxDao
 * \brief qx::QxSoftDelete : soft delete (or logical delete) behavior to update a row into database (flag it as deleted) instead of delete it from database
 *
 * A soft delete doesn't remove rows from database (this is not a physical delete) : a new column is added to the table definition to flag a row as deleted or not.
 * This column can contain a boolean (1 means row deleted, 0 or NULL means row not deleted), or can contain deletion date-time (if empty or NULL, row is not deleted).
 * So you can reactivate a deleted row by setting NULL or empty value into database.
 *
 * To define a soft delete behavior with QxOrm library, you have to use the class qx::QxSoftDelete in function mapping by class qx::register_class<T>.
 * Here is an example with the class <i>Bar</i> containing 2 properties <i>m_id</i> and <i>m_desc</i> :
 * \code
namespace qx {
template <> void register_class(QxClass<Bar> & t)
{
   t.setSoftDelete(qx::QxSoftDelete("deleted_at"));

   t.id(& Bar::m_id, "id");
   t.data(& Bar::m_desc, "desc");
}}
 * \endcode
 *
 * SQL queries builded by QxOrm library will take into account this soft delete parameter to add conditions (don't fetch deleted item, don't delete physically a row, etc.).
 * For example, if you execute this code with the class <i>Bar</i> :
 * \code
Bar_ptr pBar; pBar.reset(new Bar());
pBar->setId(5);
QSqlError daoError = qx::dao::delete_by_id(pBar);     qAssert(! daoError.isValid());
qx_bool bDaoExist = qx::dao::exist(pBar);             qAssert(! bDaoExist);
daoError = qx::dao::delete_all<Bar>();                qAssert(! daoError.isValid());
long lBarCount = qx::dao::count<Bar>();               qAssert(lBarCount == 0);
daoError = qx::dao::destroy_all<Bar>();               qAssert(! daoError.isValid());
 * \endcode
 *
 * You will obtain following output trace :
 * \code
[QxOrm] sql query (93 ms) : UPDATE Bar SET deleted_at = '20110617115148615' WHERE id = :id
[QxOrm] sql query (0 ms) : SELECT Bar.id AS Bar_id_0, Bar.deleted_at FROM Bar WHERE Bar.id = :id AND (Bar.deleted_at IS NULL OR Bar.deleted_at = '')
[QxOrm] sql query (78 ms) : UPDATE Bar SET deleted_at = '20110617115148724'
[QxOrm] sql query (0 ms) : SELECT COUNT(*) FROM Bar WHERE (Bar.deleted_at IS NULL OR Bar.deleted_at = '')
[QxOrm] sql query (110 ms) : DELETE FROM Bar
 * \endcode
 *
 * <i>Note :</i> To delete physically a row from database, you have to use followings functions : qx::dao::destroy_by_id() and qx::dao::destroy_all().
 *
 * <i>Other note :</i> it is recommended to define into database an index on column <i>deleted_at</i> to optimize execution of SQL queries.
 */
class QX_DLL_EXPORT QxSoftDelete
{

public:

   enum mode { mode_flag, mode_date_time };

private:

   QString m_sTable;                      //!< Table name where soft delete behavior is applied
   QString m_sColumn;                     //!< Column name to store soft delete information
   QString m_sSqlQueryToFetch;            //!< Overrided user SQL query to fetch an item, if empty QxOrm library builds a default SQL query
   QString m_sSqlQueryToUpdate;           //!< Overrided user SQL query to update an item, if empty QxOrm library builds a default SQL query
   QString m_sSqlQueryToCreateTable;      //!< Overrided user SQL query to create table, if empty QxOrm library builds a default SQL query
   mode m_eMode;                          //!< Soft delete mode : 'mode_flag' with a boolean column, 'mode_date_time' with a date-time column containing deletion date-time

public:

   QxSoftDelete();
   QxSoftDelete(const QString & sColumn);
   QxSoftDelete(const QString & sColumn, mode eMode);
   ~QxSoftDelete();

   QString getTableName() const;
   QString getColumnName() const;
   QString getSqlQueryToFetch() const;
   QString getSqlQueryToUpdate() const;
   QString getSqlQueryToCreateTable() const;
   mode getMode() const;

   void setTableName(const QString & sTable);
   void setColumnName(const QString & sColumn);
   void setSqlQueryToFetch(const QString & s);
   void setSqlQueryToUpdate(const QString & s);
   void setSqlQueryToCreateTable(const QString & s);
   void setMode(mode eMode);

   bool isEmpty() const;

   QString buildSqlTablePointName(const QString & sTable = QString()) const;
   QString buildSqlQueryToFetch(const QString & sTable = QString()) const;
   QString buildSqlQueryToUpdate() const;
   QString buildSqlQueryToCreateTable() const;

};

} // namespace qx

#endif // _QX_SOFT_DELETE_H_
