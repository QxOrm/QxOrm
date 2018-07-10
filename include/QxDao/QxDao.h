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

#ifndef _QX_DAO_H_
#define _QX_DAO_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxDao.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Provide template functions to map C++ class registered into QxOrm context with table database (ORM - Object Relational Mapping)
 */

#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqlrecord.h>
#include <QtSql/qsqlfield.h>
#include <QtSql/qsqlerror.h>
#include <QtSql/qsqldriver.h>

#include <QxCommon/QxBool.h>

#include <QxDao/QxSoftDelete.h>
#include <QxDao/QxDaoPointer.h>
#include <QxDao/QxSqlQuery.h>

namespace qx {
namespace dao {

namespace detail {
struct IxDao_Helper;
template <class T> struct QxDao_Count;
template <class T> struct QxDao_FetchById;
template <class T> struct QxDao_FetchById_WithRelation;
template <class T> struct QxDao_FetchAll;
template <class T> struct QxDao_FetchAll_WithRelation;
template <class T> struct QxDao_Insert;
template <class T> struct QxDao_Insert_WithRelation;
template <class T> struct QxDao_Update;
template <class T> struct QxDao_Update_Optimized;
template <class T> struct QxDao_Update_WithRelation;
template <class T> struct QxDao_Save;
template <class T> struct QxDao_Save_WithRelation;
template <class T> struct QxDao_DeleteById;
template <class T> struct QxDao_DeleteAll;
template <class T> struct QxDao_Exist;
template <class T> struct QxDao_CreateTable;
template <class T> struct QxDao_Trigger;
} // namespace detail

/*!
 * \ingroup QxDao
 * \brief Return the number of lines in the table (database) mapped to the C++ class T (registered into QxOrm context)
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 *
 * qx::dao::count<T>() execute following SQL query :<br>
 * <i>SELECT COUNT(*) FROM my_table</i>
 */
template <class T>
inline long count(QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_Count<T>::count("", pDatabase); }

/*!
 * \ingroup QxDao
 * \brief Return the number of lines in the table (database) mapped to the C++ class T (registered into QxOrm context) and filtered by a user SQL query
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 *
 * qx::dao::count<T>() execute following SQL query :<br>
 * <i>SELECT COUNT(*) FROM my_table</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline long count(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_Count<T>::count(query, pDatabase); }

/*!
 * \ingroup QxDao
 * \brief Fetch an object t (retrieve all its properties) of type T (registered into QxOrm context) mapped to a table in the database (t must have a valid id before to be fetched without error)
 * \param t Instance (with a valid id) to be fetched (retrieve all properties from database)
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::fetch_by_id<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table WHERE my_id = ?</i>
 */
template <class T>
inline QSqlError fetch_by_id(T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_FetchById<T>::fetchById(t, pDatabase, QStringList()); }

/*!
 * \ingroup QxDao
 * \brief Fetch a list of objects (retrieve all elements and properties associated) of type T (container registered into QxOrm context) mapped to a table in the database
 * \param t Container to be fetched (retrieve all elements and properties associated); t is cleared before executing SQL query
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::fetch_all<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table</i>
 */
template <class T>
inline QSqlError fetch_all(T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_FetchAll<T>::fetchAll("", t, pDatabase, QStringList()); }

/*!
 * \ingroup QxDao
 * \brief Fetch a list of objects (retrieve all elements and properties associated) of type T (container registered into QxOrm context) mapped to a table in the database and filtered by a user SQL query
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param t Container to be fetched (retrieve all elements and properties associated); t is cleared before executing SQL query
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::fetch_by_query<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline QSqlError fetch_by_query(const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_FetchAll<T>::fetchAll(query, t, pDatabase, QStringList()); }

/*!
 * \ingroup QxDao
 * \brief Insert an element or a list of elements into database
 * \param t Element (or list of elements) to be inserted into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::insert<T>() execute following SQL query :<br>
 * <i>INSERT INTO my_table (my_column_1, my_column_2, etc.) VALUES (?, ?, etc.)</i>
 */
template <class T>
inline QSqlError insert(T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_Insert<T>::insert(t, pDatabase); }

/*!
 * \ingroup QxDao
 * \brief Update an element or a list of elements into database
 * \param t Element (or list of elements) to be updated into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::update<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i>
 */
template <class T>
inline QSqlError update(T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_Update<T>::update("", t, pDatabase, QStringList()); }

/*!
 * \ingroup QxDao
 * \brief Update an element or a list of elements into database (adding a user SQL query to the default SQL query builded by QxOrm library)
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param t Element (or list of elements) to be updated into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::update_by_query<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline QSqlError update_by_query(const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_Update<T>::update(query, t, pDatabase, QStringList()); }

/*!
 * \ingroup QxDao
 * \brief Insert (if no exist) or update (if already exist) an element or a list of elements into database
 * \param t Element (or list of elements) to be inserted (if no exist) or updated (if already exist) into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::save<T>() execute following SQL query :<br>
 * <i>INSERT INTO my_table (my_column_1, my_column_2, etc.) VALUES (?, ?, etc.)</i>
 * <br>or (if already exist into database) :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i>
 */
template <class T>
inline QSqlError save(T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_Save<T>::save(t, pDatabase); }

/*!
 * \ingroup QxDao
 * \brief Delete a line (or list of lines) of a table (database) mapped to a C++ object of type T (registered into QxOrm context)
 * \param t Element (or list of elements) to be deleted into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::delete_by_id<T>() execute following SQL query :<br>
 * <i>DELETE FROM my_table WHERE my_id = ?</i><br>
 * <br>
 * If a soft delete behavior is defined for class T, qx::dao::delete_by_id<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET is_deleted='1' WHERE my_id = ?</i>
 */
template <class T>
inline QSqlError delete_by_id(T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_DeleteById<T>::deleteById(t, pDatabase, true); }

/*!
 * \ingroup QxDao
 * \brief Destroy a line (or list of lines) of a table (database) mapped to a C++ object of type T (registered into QxOrm context), even if a soft delete behavior is defined for class T
 * \param t Element (or list of elements) to be destroyed into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::destroy_by_id<T>() execute following SQL query :<br>
 * <i>DELETE FROM my_table WHERE my_id = ?</i>
 */
template <class T>
inline QSqlError destroy_by_id(T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_DeleteById<T>::deleteById(t, pDatabase, false); }

/*!
 * \ingroup QxDao
 * \brief Delete all lines of a table (database) mapped to a C++ class T (registered into QxOrm context)
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::delete_all<T>() execute following SQL query :<br>
 * <i>DELETE FROM my_table</i><br>
 * <br>
 * If a soft delete behavior is defined for class T, qx::dao::delete_all<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET is_deleted='1'</i>
 */
template <class T>
inline QSqlError delete_all(QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_DeleteAll<T>::deleteAll("", pDatabase, true); }

/*!
 * \ingroup QxDao
 * \brief Destroy all lines of a table (database) mapped to a C++ class T (registered into QxOrm context), even if a soft delete behavior is defined for class T
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::destroy_all<T>() execute following SQL query :<br>
 * <i>DELETE FROM my_table</i>
 */
template <class T>
inline QSqlError destroy_all(QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_DeleteAll<T>::deleteAll("", pDatabase, false); }

/*!
 * \ingroup QxDao
 * \brief Delete all lines of a table (database) mapped to a C++ class T (registered into QxOrm context) and filtered by a user SQL query
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::delete_by_query<T>() execute following SQL query :<br>
 * <i>DELETE FROM my_table</i> + <i>WHERE my_query...</i><br>
 * <br>
 * If a soft delete behavior is defined for class T, qx::dao::delete_by_query<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET is_deleted='1'</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline QSqlError delete_by_query(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_DeleteAll<T>::deleteAll(query, pDatabase, true); }

/*!
 * \ingroup QxDao
 * \brief Destroy all lines of a table (database) mapped to a C++ class T (registered into QxOrm context) and filtered by a user SQL query, even if a soft delete behavior is defined for class T
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::destroy_by_query<T>() execute following SQL query :<br>
 * <i>DELETE FROM my_table</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline QSqlError destroy_by_query(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_DeleteAll<T>::deleteAll(query, pDatabase, false); }

/*!
 * \ingroup QxDao
 * \brief Create a table into database (with all columns) mapped to a C++ class T (registered into QxOrm context)
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::create_table<T>() execute following SQL query :<br>
 * <i>CREATE TABLE my_table (my_id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, my_column_1 TEXT, my_column_2 TEXT, etc.)</i>
 */
template <class T>
inline QSqlError create_table(QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_CreateTable<T>::createTable(pDatabase); }

/*!
 * \ingroup QxDao
 * \brief Search if an element (or list of elements) already exists into database
 * \param t Element (or list of elements) to be searched into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Return true if element already exists into database; otherwise return false; if an error occurred, qx_bool object contains a description of database error executing SQL query
 *
 * qx::dao::exist<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table WHERE my_id = ?</i>
 */
template <class T>
inline qx_bool exist(T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_Exist<T>::exist(t, pDatabase); }

/*!
 * \ingroup QxDao
 * \brief Fetch an object t (retrieve all its properties) of type T (registered into QxOrm context) mapped to a table in the database (t must have a valid id before to be fetched without error)
 * \param relation List of relationships keys to be fetched (eager fetch instead of default lazy fetch for a relation) : use "|" separator to put many relationships keys into this parameter
 * \param t Instance (with a valid id) to be fetched (retrieve all properties from database)
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::fetch_by_id_with_relation<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table WHERE my_id = ?</i>
 */
template <class T>
inline QSqlError fetch_by_id_with_relation(const QString & relation, T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_FetchById_WithRelation<T>::fetchById(relation, t, pDatabase); }

/*!
 * \ingroup QxDao
 * \brief Fetch an object t (retrieve all its properties) of type T (registered into QxOrm context) mapped to a table in the database (t must have a valid id before to be fetched without error)
 * \param relation List of relationships keys to be fetched (eager fetch instead of default lazy fetch for a relation)
 * \param t Instance (with a valid id) to be fetched (retrieve all properties from database)
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::fetch_by_id_with_relation<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table WHERE my_id = ?</i>
 */
template <class T>
inline QSqlError fetch_by_id_with_relation(const QStringList & relation, T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_FetchById_WithRelation<T>::fetchById(relation, t, pDatabase); }

/*!
 * \ingroup QxDao
 * \brief Fetch an object t (retrieve all its properties and relationships) of type T (registered into QxOrm context) mapped to a table in the database (t must have a valid id before to be fetched without error)
 * \param t Instance (with a valid id) to be fetched (retrieve all properties and relationships from database)
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::fetch_by_id_with_all_relation<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table WHERE my_id = ?</i>
 */
template <class T>
inline QSqlError fetch_by_id_with_all_relation(T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_FetchById_WithRelation<T>::fetchById("*", t, pDatabase); }

/*!
 * \ingroup QxDao
 * \brief Fetch a list of objects (retrieve all elements and properties associated) of type T (container registered into QxOrm context) mapped to a table in the database
 * \param relation List of relationships keys to be fetched (eager fetch instead of default lazy fetch for a relation) : use "|" separator to put many relationships keys into this parameter
 * \param t Container to be fetched (retrieve all elements and properties associated); t is cleared before executing SQL query
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::fetch_all_with_relation<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table</i>
 */
template <class T>
inline QSqlError fetch_all_with_relation(const QString & relation, T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll(relation, "", t, pDatabase); }

/*!
 * \ingroup QxDao
 * \brief Fetch a list of objects (retrieve all elements and properties associated) of type T (container registered into QxOrm context) mapped to a table in the database
 * \param relation List of relationships keys to be fetched (eager fetch instead of default lazy fetch for a relation)
 * \param t Container to be fetched (retrieve all elements and properties associated); t is cleared before executing SQL query
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::fetch_all_with_relation<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table</i>
 */
template <class T>
inline QSqlError fetch_all_with_relation(const QStringList & relation, T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll(relation, "", t, pDatabase); }

/*!
 * \ingroup QxDao
 * \brief Fetch a list of objects (retrieve all elements and properties + all relationships associated) of type T (container registered into QxOrm context) mapped to a table in the database
 * \param t Container to be fetched (retrieve all elements and properties + all relationships associated); t is cleared before executing SQL query
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::fetch_all_with_all_relation<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table</i>
 */
template <class T>
inline QSqlError fetch_all_with_all_relation(T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll("*", "", t, pDatabase); }

/*!
 * \ingroup QxDao
 * \brief Fetch a list of objects (retrieve all elements and properties associated) of type T (container registered into QxOrm context) mapped to a table in the database and filtered by a user SQL query
 * \param relation List of relationships keys to be fetched (eager fetch instead of default lazy fetch for a relation) : use "|" separator to put many relationships keys into this parameter
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param t Container to be fetched (retrieve all elements and properties associated); t is cleared before executing SQL query
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::fetch_by_query_with_relation<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline QSqlError fetch_by_query_with_relation(const QString & relation, const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll(relation, query, t, pDatabase); }

/*!
 * \ingroup QxDao
 * \brief Fetch a list of objects (retrieve all elements and properties associated) of type T (container registered into QxOrm context) mapped to a table in the database and filtered by a user SQL query
 * \param relation List of relationships keys to be fetched (eager fetch instead of default lazy fetch for a relation)
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param t Container to be fetched (retrieve all elements and properties associated); t is cleared before executing SQL query
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::fetch_by_query_with_relation<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline QSqlError fetch_by_query_with_relation(const QStringList & relation, const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll(relation, query, t, pDatabase); }

/*!
 * \ingroup QxDao
 * \brief Fetch a list of objects (retrieve all elements and properties + all relationships associated) of type T (container registered into QxOrm context) mapped to a table in the database and filtered by a user SQL query
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param t Container to be fetched (retrieve all elements and properties + all relationships associated); t is cleared before executing SQL query
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::fetch_by_query_with_all_relation<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline QSqlError fetch_by_query_with_all_relation(const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll("*", query, t, pDatabase); }

/*!
 * \ingroup QxDao
 * \brief Insert an element and its relationships (or a list of elements + relationships) into database
 * \param relation List of relationships keys to be inserted in others tables of database : use "|" separator to put many relationships keys into this parameter
 * \param t Element (or list of elements) to be inserted into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::insert_with_relation<T>() execute following SQL query :<br>
 * <i>INSERT INTO my_table (my_column_1, my_column_2, etc.) VALUES (?, ?, etc.)</i>
 */
template <class T>
inline QSqlError insert_with_relation(const QString & relation, T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_Insert_WithRelation<T>::insert(relation, t, pDatabase); }

/*!
 * \ingroup QxDao
 * \brief Insert an element and its relationships (or a list of elements + relationships) into database
 * \param relation List of relationships keys to be inserted in others tables of database
 * \param t Element (or list of elements) to be inserted into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::insert_with_relation<T>() execute following SQL query :<br>
 * <i>INSERT INTO my_table (my_column_1, my_column_2, etc.) VALUES (?, ?, etc.)</i>
 */
template <class T>
inline QSqlError insert_with_relation(const QStringList & relation, T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_Insert_WithRelation<T>::insert(relation, t, pDatabase); }

/*!
 * \ingroup QxDao
 * \brief Insert an element and all its relationships (or a list of elements + all relationships) into database
 * \param t Element (or list of elements) to be inserted into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::insert_with_all_relation<T>() execute following SQL query :<br>
 * <i>INSERT INTO my_table (my_column_1, my_column_2, etc.) VALUES (?, ?, etc.)</i>
 */
template <class T>
inline QSqlError insert_with_all_relation(T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_Insert_WithRelation<T>::insert("*", t, pDatabase); }

/*!
 * \ingroup QxDao
 * \brief Update an element and its relationships (or a list of elements + relationships) into database
 * \param relation List of relationships keys to be updated in others tables of database : use "|" separator to put many relationships keys into this parameter
 * \param t Element (or list of elements) to be updated into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::update_with_relation<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i>
 */
template <class T>
inline QSqlError update_with_relation(const QString & relation, T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_Update_WithRelation<T>::update(relation, "", t, pDatabase); }

/*!
 * \ingroup QxDao
 * \brief Update an element and its relationships (or a list of elements + relationships) into database (adding a user SQL query to the default SQL query builded by QxOrm library)
 * \param relation List of relationships keys to be updated in others tables of database : use "|" separator to put many relationships keys into this parameter
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param t Element (or list of elements) to be updated into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::update_by_query_with_relation<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline QSqlError update_by_query_with_relation(const QString & relation, const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_Update_WithRelation<T>::update(relation, query, t, pDatabase); }

/*!
 * \ingroup QxDao
 * \brief Update an element and its relationships (or a list of elements + relationships) into database
 * \param relation List of relationships keys to be updated in others tables of database
 * \param t Element (or list of elements) to be updated into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::update_with_relation<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i>
 */
template <class T>
inline QSqlError update_with_relation(const QStringList & relation, T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_Update_WithRelation<T>::update(relation, "", t, pDatabase); }

/*!
 * \ingroup QxDao
 * \brief Update an element and its relationships (or a list of elements + relationships) into database (adding a user SQL query to the default SQL query builded by QxOrm library)
 * \param relation List of relationships keys to be updated in others tables of database
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param t Element (or list of elements) to be updated into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::update_by_query_with_relation<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline QSqlError update_by_query_with_relation(const QStringList & relation, const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_Update_WithRelation<T>::update(relation, query, t, pDatabase); }

/*!
 * \ingroup QxDao
 * \brief Update an element and all its relationships (or a list of elements + all relationships) into database
 * \param t Element (or list of elements) to be updated into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::update_with_all_relation<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i>
 */
template <class T>
inline QSqlError update_with_all_relation(T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_Update_WithRelation<T>::update("*", "", t, pDatabase); }

/*!
 * \ingroup QxDao
 * \brief Update an element and all its relationships (or a list of elements + all relationships) into database (adding a user SQL query to the default SQL query builded by QxOrm library)
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param t Element (or list of elements) to be updated into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::update_by_query_with_all_relation<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline QSqlError update_by_query_with_all_relation(const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_Update_WithRelation<T>::update("*", query, t, pDatabase); }

/*!
 * \ingroup QxDao
 * \brief Insert (if no exist) or update (if already exist) an element and its relationships (or a list of elements + relationships) into database
 * \param relation List of relationships keys to be inserted or updated in others tables of database : use "|" separator to put many relationships keys into this parameter
 * \param t Element (or list of elements) to be inserted (if no exist) or updated (if already exist) into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::save_with_relation<T>() execute following SQL query :<br>
 * <i>INSERT INTO my_table (my_column_1, my_column_2, etc.) VALUES (?, ?, etc.)</i>
 * <br>or (if already exist into database) :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i>
 */
template <class T>
inline QSqlError save_with_relation(const QString & relation, T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_Save_WithRelation<T>::save(relation, t, pDatabase); }

/*!
 * \ingroup QxDao
 * \brief Insert (if no exist) or update (if already exist) an element and its relationships (or a list of elements + relationships) into database
 * \param relation List of relationships keys to be inserted or updated in others tables of database
 * \param t Element (or list of elements) to be inserted (if no exist) or updated (if already exist) into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::save_with_relation<T>() execute following SQL query :<br>
 * <i>INSERT INTO my_table (my_column_1, my_column_2, etc.) VALUES (?, ?, etc.)</i>
 * <br>or (if already exist into database) :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i>
 */
template <class T>
inline QSqlError save_with_relation(const QStringList & relation, T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_Save_WithRelation<T>::save(relation, t, pDatabase); }

/*!
 * \ingroup QxDao
 * \brief Insert (if no exist) or update (if already exist) an element and all its relationships (or a list of elements + all relationships) into database
 * \param t Element (or list of elements) to be inserted (if no exist) or updated (if already exist) into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::save_with_all_relation<T>() execute following SQL query :<br>
 * <i>INSERT INTO my_table (my_column_1, my_column_2, etc.) VALUES (?, ?, etc.)</i>
 * <br>or (if already exist into database) :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i>
 */
template <class T>
inline QSqlError save_with_all_relation(T & t, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_Save_WithRelation<T>::save("*", t, pDatabase); }

/*!
 * \ingroup QxDao
 * \brief Return the number of lines in the table (database) mapped to the C++ class T (registered into QxOrm context)
 *
 * qx::dao::count<T>() execute following SQL query :<br>
 * <i>SELECT COUNT(*) FROM my_table</i>
 */
template <class T>
inline long count()
{ return qx::dao::detail::QxDao_Count<T>::count("", NULL); }

/*!
 * \ingroup QxDao
 * \brief Return the number of lines in the table (database) mapped to the C++ class T (registered into QxOrm context) and filtered by a user SQL query
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 *
 * qx::dao::count<T>() execute following SQL query :<br>
 * <i>SELECT COUNT(*) FROM my_table</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline long count(const qx::QxSqlQuery & query)
{ return qx::dao::detail::QxDao_Count<T>::count(query, NULL); }

/*!
 * \ingroup QxDao
 * \brief Fetch an object t (retrieve all its properties) of type T (registered into QxOrm context) mapped to a table in the database (t must have a valid id before to be fetched without error)
 * \param t Instance (with a valid id) to be fetched (retrieve all properties from database)
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::fetch_by_id<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table WHERE my_id = ?</i>
 */
template <class T>
inline QSqlError fetch_by_id(T & t)
{ return qx::dao::detail::QxDao_FetchById<T>::fetchById(t, NULL, QStringList()); }

/*!
 * \ingroup QxDao
 * \brief Fetch a list of objects (retrieve all elements and properties associated) of type T (container registered into QxOrm context) mapped to a table in the database
 * \param t Container to be fetched (retrieve all elements and properties associated); t is cleared before executing SQL query
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::fetch_all<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table</i>
 */
template <class T>
inline QSqlError fetch_all(T & t)
{ return qx::dao::detail::QxDao_FetchAll<T>::fetchAll("", t, NULL, QStringList()); }

/*!
 * \ingroup QxDao
 * \brief Fetch a list of objects (retrieve all elements and properties associated) of type T (container registered into QxOrm context) mapped to a table in the database and filtered by a user SQL query
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param t Container to be fetched (retrieve all elements and properties associated); t is cleared before executing SQL query
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::fetch_by_query<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline QSqlError fetch_by_query(const qx::QxSqlQuery & query, T & t)
{ return qx::dao::detail::QxDao_FetchAll<T>::fetchAll(query, t, NULL, QStringList()); }

/*!
 * \ingroup QxDao
 * \brief Insert an element or a list of elements into database
 * \param t Element (or list of elements) to be inserted into database
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::insert<T>() execute following SQL query :<br>
 * <i>INSERT INTO my_table (my_column_1, my_column_2, etc.) VALUES (?, ?, etc.)</i>
 */
template <class T>
inline QSqlError insert(T & t)
{ return qx::dao::detail::QxDao_Insert<T>::insert(t, NULL); }

/*!
 * \ingroup QxDao
 * \brief Update an element or a list of elements into database
 * \param t Element (or list of elements) to be updated into database
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::update<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i>
 */
template <class T>
inline QSqlError update(T & t)
{ return qx::dao::detail::QxDao_Update<T>::update("", t, NULL, QStringList()); }

/*!
 * \ingroup QxDao
 * \brief Update an element or a list of elements into database (adding a user SQL query to the default SQL query builded by QxOrm library)
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param t Element (or list of elements) to be updated into database
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::update_by_query<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline QSqlError update_by_query(const qx::QxSqlQuery & query, T & t)
{ return qx::dao::detail::QxDao_Update<T>::update(query, t, NULL, QStringList()); }

/*!
 * \ingroup QxDao
 * \brief Insert (if no exist) or update (if already exist) an element or a list of elements into database
 * \param t Element (or list of elements) to be inserted (if no exist) or updated (if already exist) into database
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::save<T>() execute following SQL query :<br>
 * <i>INSERT INTO my_table (my_column_1, my_column_2, etc.) VALUES (?, ?, etc.)</i>
 * <br>or (if already exist into database) :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i>
 */
template <class T>
inline QSqlError save(T & t)
{ return qx::dao::detail::QxDao_Save<T>::save(t, NULL); }

/*!
 * \ingroup QxDao
 * \brief Delete a line (or list of lines) of a table (database) mapped to a C++ object of type T (registered into QxOrm context)
 * \param t Element (or list of elements) to be deleted into database
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::delete_by_id<T>() execute following SQL query :<br>
 * <i>DELETE FROM my_table WHERE my_id = ?</i><br>
 * <br>
 * If a soft delete behavior is defined for class T, qx::dao::delete_by_id<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET is_deleted='1' WHERE my_id = ?</i>
 */
template <class T>
inline QSqlError delete_by_id(T & t)
{ return qx::dao::detail::QxDao_DeleteById<T>::deleteById(t, NULL, true); }

/*!
 * \ingroup QxDao
 * \brief Destroy a line (or list of lines) of a table (database) mapped to a C++ object of type T (registered into QxOrm context), even if a soft delete behavior is defined for class T
 * \param t Element (or list of elements) to be destroyed into database
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::destroy_by_id<T>() execute following SQL query :<br>
 * <i>DELETE FROM my_table WHERE my_id = ?</i>
 */
template <class T>
inline QSqlError destroy_by_id(T & t)
{ return qx::dao::detail::QxDao_DeleteById<T>::deleteById(t, NULL, false); }

/*!
 * \ingroup QxDao
 * \brief Delete all lines of a table (database) mapped to a C++ class T (registered into QxOrm context)
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::delete_all<T>() execute following SQL query :<br>
 * <i>DELETE FROM my_table</i><br>
 * <br>
 * If a soft delete behavior is defined for class T, qx::dao::delete_all<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET is_deleted='1'</i>
 */
template <class T>
inline QSqlError delete_all()
{ return qx::dao::detail::QxDao_DeleteAll<T>::deleteAll("", NULL, true); }

/*!
 * \ingroup QxDao
 * \brief Destroy all lines of a table (database) mapped to a C++ class T (registered into QxOrm context), even if a soft delete behavior is defined for class T
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::destroy_all<T>() execute following SQL query :<br>
 * <i>DELETE FROM my_table</i>
 */
template <class T>
inline QSqlError destroy_all()
{ return qx::dao::detail::QxDao_DeleteAll<T>::deleteAll("", NULL, false); }

/*!
 * \ingroup QxDao
 * \brief Delete all lines of a table (database) mapped to a C++ class T (registered into QxOrm context) and filtered by a user SQL query
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::delete_by_query<T>() execute following SQL query :<br>
 * <i>DELETE FROM my_table</i> + <i>WHERE my_query...</i><br>
 * <br>
 * If a soft delete behavior is defined for class T, qx::dao::delete_by_query<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET is_deleted='1'</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline QSqlError delete_by_query(const qx::QxSqlQuery & query)
{ return qx::dao::detail::QxDao_DeleteAll<T>::deleteAll(query, NULL, true); }

/*!
 * \ingroup QxDao
 * \brief Destroy all lines of a table (database) mapped to a C++ class T (registered into QxOrm context) and filtered by a user SQL query, even if a soft delete behavior is defined for class T
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::destroy_by_query<T>() execute following SQL query :<br>
 * <i>DELETE FROM my_table</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline QSqlError destroy_by_query(const qx::QxSqlQuery & query)
{ return qx::dao::detail::QxDao_DeleteAll<T>::deleteAll(query, NULL, false); }

/*!
 * \ingroup QxDao
 * \brief Create a table into database (with all columns) mapped to a C++ class T (registered into QxOrm context)
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::create_table<T>() execute following SQL query :<br>
 * <i>CREATE TABLE my_table (my_id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, my_column_1 TEXT, my_column_2 TEXT, etc.)</i>
 */
template <class T>
inline QSqlError create_table()
{ return qx::dao::detail::QxDao_CreateTable<T>::createTable(NULL); }

/*!
 * \ingroup QxDao
 * \brief Search if an element (or list of elements) already exists into database
 * \param t Element (or list of elements) to be searched into database
 * \return Return true if element already exists into database; otherwise return false; if an error occurred, qx_bool object contains a description of database error executing SQL query
 *
 * qx::dao::exist<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table WHERE my_id = ?</i>
 */
template <class T>
inline qx_bool exist(T & t)
{ return qx::dao::detail::QxDao_Exist<T>::exist(t, NULL); }

/*!
 * \ingroup QxDao
 * \brief Fetch an object t (retrieve all its properties) of type T (registered into QxOrm context) mapped to a table in the database (t must have a valid id before to be fetched without error)
 * \param t Instance (with a valid id) to be fetched (retrieve all properties from database)
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \param columns List of database table columns (mapped to properties of C++ class T) to be fetched
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::fetch_by_id<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table WHERE my_id = ?</i>
 */
template <class T>
inline QSqlError fetch_by_id(T & t, QSqlDatabase * pDatabase, const QStringList & columns)
{ return qx::dao::detail::QxDao_FetchById<T>::fetchById(t, pDatabase, columns); }

/*!
 * \ingroup QxDao
 * \brief Fetch a list of objects (retrieve all elements and properties associated) of type T (container registered into QxOrm context) mapped to a table in the database
 * \param t Container to be fetched (retrieve all elements and properties associated); t is cleared before executing SQL query
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \param columns List of database table columns (mapped to properties of C++ class T) to be fetched
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::fetch_all<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table</i>
 */
template <class T>
inline QSqlError fetch_all(T & t, QSqlDatabase * pDatabase, const QStringList & columns)
{ return qx::dao::detail::QxDao_FetchAll<T>::fetchAll("", t, pDatabase, columns); }

/*!
 * \ingroup QxDao
 * \brief Fetch a list of objects (retrieve all elements and properties associated) of type T (container registered into QxOrm context) mapped to a table in the database and filtered by a user SQL query
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param t Container to be fetched (retrieve all elements and properties associated); t is cleared before executing SQL query
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \param columns List of database table columns (mapped to properties of C++ class T) to be fetched
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::fetch_by_query<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline QSqlError fetch_by_query(const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase, const QStringList & columns)
{ return qx::dao::detail::QxDao_FetchAll<T>::fetchAll(query, t, pDatabase, columns); }

/*!
 * \ingroup QxDao
 * \brief Update an element or a list of elements into database
 * \param t Element (or list of elements) to be updated into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \param columns List of database table columns (mapped to properties of C++ class T) to be updated
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::update<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i>
 */
template <class T>
inline QSqlError update(T & t, QSqlDatabase * pDatabase, const QStringList & columns)
{ return qx::dao::detail::QxDao_Update<T>::update("", t, pDatabase, columns); }

/*!
 * \ingroup QxDao
 * \brief Update an element or a list of elements into database (adding a user SQL query to the default SQL query builded by QxOrm library)
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param t Element (or list of elements) to be updated into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \param columns List of database table columns (mapped to properties of C++ class T) to be updated
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::update_by_query<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline QSqlError update_by_query(const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase, const QStringList & columns)
{ return qx::dao::detail::QxDao_Update<T>::update(query, t, pDatabase, columns); }

/*!
 * \ingroup QxDao
 * \brief Update only modified fields/properties of an element or a list of elements into database (using is dirty pattern and qx::dao::ptr<T> smart-pointer)
 * \param ptr Element (or list of elements) to be updated into database
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::update_optimized<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i>
 */
template <class T>
inline QSqlError update_optimized(qx::dao::ptr<T> & ptr)
{ return qx::dao::detail::QxDao_Update_Optimized<T>::update_optimized("", ptr, NULL); }

/*!
 * \ingroup QxDao
 * \brief Update only modified fields/properties of an element or a list of elements into database (using is dirty pattern and qx::dao::ptr<T> smart-pointer), adding a user SQL query to the default SQL query builded by QxOrm library
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param ptr Element (or list of elements) to be updated into database
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::update_optimized_by_query<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline QSqlError update_optimized_by_query(const qx::QxSqlQuery & query, qx::dao::ptr<T> & ptr)
{ return qx::dao::detail::QxDao_Update_Optimized<T>::update_optimized(query, ptr, NULL); }

/*!
 * \ingroup QxDao
 * \brief Update only modified fields/properties of an element or a list of elements into database (using is dirty pattern and qx::dao::ptr<T> smart-pointer)
 * \param ptr Element (or list of elements) to be updated into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::update_optimized<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i>
 */
template <class T>
inline QSqlError update_optimized(qx::dao::ptr<T> & ptr, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_Update_Optimized<T>::update_optimized("", ptr, pDatabase); }

/*!
 * \ingroup QxDao
 * \brief Update only modified fields/properties of an element or a list of elements into database (using is dirty pattern and qx::dao::ptr<T> smart-pointer), adding a user SQL query to the default SQL query builded by QxOrm library
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param ptr Element (or list of elements) to be updated into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::update_optimized_by_query<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline QSqlError update_optimized_by_query(const qx::QxSqlQuery & query, qx::dao::ptr<T> & ptr, QSqlDatabase * pDatabase)
{ return qx::dao::detail::QxDao_Update_Optimized<T>::update_optimized(query, ptr, pDatabase); }

/*!
 * \ingroup QxDao
 * \brief Fetch an object t (retrieve all its properties) of type T (registered into QxOrm context) mapped to a table in the database (t must have a valid id before to be fetched without error)
 * \param relation List of relationships keys to be fetched (eager fetch instead of default lazy fetch for a relation) : use "|" separator to put many relationships keys into this parameter
 * \param t Instance (with a valid id) to be fetched (retrieve all properties from database)
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::fetch_by_id_with_relation<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table WHERE my_id = ?</i>
 */
template <class T>
inline QSqlError fetch_by_id_with_relation(const QString & relation, T & t)
{ return qx::dao::detail::QxDao_FetchById_WithRelation<T>::fetchById(relation, t, NULL); }

/*!
 * \ingroup QxDao
 * \brief Fetch an object t (retrieve all its properties) of type T (registered into QxOrm context) mapped to a table in the database (t must have a valid id before to be fetched without error)
 * \param relation List of relationships keys to be fetched (eager fetch instead of default lazy fetch for a relation)
 * \param t Instance (with a valid id) to be fetched (retrieve all properties from database)
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::fetch_by_id_with_relation<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table WHERE my_id = ?</i>
 */
template <class T>
inline QSqlError fetch_by_id_with_relation(const QStringList & relation, T & t)
{ return qx::dao::detail::QxDao_FetchById_WithRelation<T>::fetchById(relation, t, NULL); }

/*!
 * \ingroup QxDao
 * \brief Fetch an object t (retrieve all its properties and relationships) of type T (registered into QxOrm context) mapped to a table in the database (t must have a valid id before to be fetched without error)
 * \param t Instance (with a valid id) to be fetched (retrieve all properties and relationships from database)
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::fetch_by_id_with_all_relation<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table WHERE my_id = ?</i>
 */
template <class T>
inline QSqlError fetch_by_id_with_all_relation(T & t)
{ return qx::dao::detail::QxDao_FetchById_WithRelation<T>::fetchById("*", t, NULL); }

/*!
 * \ingroup QxDao
 * \brief Fetch a list of objects (retrieve all elements and properties associated) of type T (container registered into QxOrm context) mapped to a table in the database
 * \param relation List of relationships keys to be fetched (eager fetch instead of default lazy fetch for a relation) : use "|" separator to put many relationships keys into this parameter
 * \param t Container to be fetched (retrieve all elements and properties associated); t is cleared before executing SQL query
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::fetch_all_with_relation<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table</i>
 */
template <class T>
inline QSqlError fetch_all_with_relation(const QString & relation, T & t)
{ return qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll(relation, "", t, NULL); }

/*!
 * \ingroup QxDao
 * \brief Fetch a list of objects (retrieve all elements and properties associated) of type T (container registered into QxOrm context) mapped to a table in the database
 * \param relation List of relationships keys to be fetched (eager fetch instead of default lazy fetch for a relation)
 * \param t Container to be fetched (retrieve all elements and properties associated); t is cleared before executing SQL query
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::fetch_all_with_relation<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table</i>
 */
template <class T>
inline QSqlError fetch_all_with_relation(const QStringList & relation, T & t)
{ return qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll(relation, "", t, NULL); }

/*!
 * \ingroup QxDao
 * \brief Fetch a list of objects (retrieve all elements and properties + all relationships associated) of type T (container registered into QxOrm context) mapped to a table in the database
 * \param t Container to be fetched (retrieve all elements and properties + all relationships associated); t is cleared before executing SQL query
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::fetch_all_with_all_relation<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table</i>
 */
template <class T>
inline QSqlError fetch_all_with_all_relation(T & t)
{ return qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll("*", "", t, NULL); }

/*!
 * \ingroup QxDao
 * \brief Fetch a list of objects (retrieve all elements and properties associated) of type T (container registered into QxOrm context) mapped to a table in the database and filtered by a user SQL query
 * \param relation List of relationships keys to be fetched (eager fetch instead of default lazy fetch for a relation) : use "|" separator to put many relationships keys into this parameter
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param t Container to be fetched (retrieve all elements and properties associated); t is cleared before executing SQL query
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::fetch_by_query_with_relation<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline QSqlError fetch_by_query_with_relation(const QString & relation, const qx::QxSqlQuery & query, T & t)
{ return qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll(relation, query, t, NULL); }

/*!
 * \ingroup QxDao
 * \brief Fetch a list of objects (retrieve all elements and properties associated) of type T (container registered into QxOrm context) mapped to a table in the database and filtered by a user SQL query
 * \param relation List of relationships keys to be fetched (eager fetch instead of default lazy fetch for a relation)
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param t Container to be fetched (retrieve all elements and properties associated); t is cleared before executing SQL query
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::fetch_by_query_with_relation<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline QSqlError fetch_by_query_with_relation(const QStringList & relation, const qx::QxSqlQuery & query, T & t)
{ return qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll(relation, query, t, NULL); }

/*!
 * \ingroup QxDao
 * \brief Fetch a list of objects (retrieve all elements and properties + all relationships associated) of type T (container registered into QxOrm context) mapped to a table in the database and filtered by a user SQL query
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param t Container to be fetched (retrieve all elements and properties + all relationships associated); t is cleared before executing SQL query
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::fetch_by_query_with_all_relation<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline QSqlError fetch_by_query_with_all_relation(const qx::QxSqlQuery & query, T & t)
{ return qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll("*", query, t, NULL); }

/*!
 * \ingroup QxDao
 * \brief Insert an element and its relationships (or a list of elements + relationships) into database
 * \param relation List of relationships keys to be inserted in others tables of database : use "|" separator to put many relationships keys into this parameter
 * \param t Element (or list of elements) to be inserted into database
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::insert_with_relation<T>() execute following SQL query :<br>
 * <i>INSERT INTO my_table (my_column_1, my_column_2, etc.) VALUES (?, ?, etc.)</i>
 */
template <class T>
inline QSqlError insert_with_relation(const QString & relation, T & t)
{ return qx::dao::detail::QxDao_Insert_WithRelation<T>::insert(relation, t, NULL); }

/*!
 * \ingroup QxDao
 * \brief Insert an element and its relationships (or a list of elements + relationships) into database
 * \param relation List of relationships keys to be inserted in others tables of database
 * \param t Element (or list of elements) to be inserted into database
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::insert_with_relation<T>() execute following SQL query :<br>
 * <i>INSERT INTO my_table (my_column_1, my_column_2, etc.) VALUES (?, ?, etc.)</i>
 */
template <class T>
inline QSqlError insert_with_relation(const QStringList & relation, T & t)
{ return qx::dao::detail::QxDao_Insert_WithRelation<T>::insert(relation, t, NULL); }

/*!
 * \ingroup QxDao
 * \brief Insert an element and all its relationships (or a list of elements + all relationships) into database
 * \param t Element (or list of elements) to be inserted into database
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::insert_with_all_relation<T>() execute following SQL query :<br>
 * <i>INSERT INTO my_table (my_column_1, my_column_2, etc.) VALUES (?, ?, etc.)</i>
 */
template <class T>
inline QSqlError insert_with_all_relation(T & t)
{ return qx::dao::detail::QxDao_Insert_WithRelation<T>::insert("*", t, NULL); }

/*!
 * \ingroup QxDao
 * \brief Update an element and its relationships (or a list of elements + relationships) into database
 * \param relation List of relationships keys to be updated in others tables of database : use "|" separator to put many relationships keys into this parameter
 * \param t Element (or list of elements) to be updated into database
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::update_with_relation<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i>
 */
template <class T>
inline QSqlError update_with_relation(const QString & relation, T & t)
{ return qx::dao::detail::QxDao_Update_WithRelation<T>::update(relation, "", t, NULL); }

/*!
 * \ingroup QxDao
 * \brief Update an element and its relationships (or a list of elements + relationships) into database (adding a user SQL query to the default SQL query builded by QxOrm library)
 * \param relation List of relationships keys to be updated in others tables of database : use "|" separator to put many relationships keys into this parameter
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param t Element (or list of elements) to be updated into database
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::update_by_query_with_relation<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline QSqlError update_by_query_with_relation(const QString & relation, const qx::QxSqlQuery & query, T & t)
{ return qx::dao::detail::QxDao_Update_WithRelation<T>::update(relation, query, t, NULL); }

/*!
 * \ingroup QxDao
 * \brief Update an element and its relationships (or a list of elements + relationships) into database
 * \param relation List of relationships keys to be updated in others tables of database
 * \param t Element (or list of elements) to be updated into database
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::update_with_relation<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i>
 */
template <class T>
inline QSqlError update_with_relation(const QStringList & relation, T & t)
{ return qx::dao::detail::QxDao_Update_WithRelation<T>::update(relation, "", t, NULL); }

/*!
 * \ingroup QxDao
 * \brief Update an element and its relationships (or a list of elements + relationships) into database (adding a user SQL query to the default SQL query builded by QxOrm library)
 * \param relation List of relationships keys to be updated in others tables of database
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param t Element (or list of elements) to be updated into database
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::update_by_query_with_relation<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline QSqlError update_by_query_with_relation(const QStringList & relation, const qx::QxSqlQuery & query, T & t)
{ return qx::dao::detail::QxDao_Update_WithRelation<T>::update(relation, query, t, NULL); }

/*!
 * \ingroup QxDao
 * \brief Update an element and all its relationships (or a list of elements + all relationships) into database
 * \param t Element (or list of elements) to be updated into database
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::update_with_all_relation<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i>
 */
template <class T>
inline QSqlError update_with_all_relation(T & t)
{ return qx::dao::detail::QxDao_Update_WithRelation<T>::update("*", "", t, NULL); }

/*!
 * \ingroup QxDao
 * \brief Update an element and all its relationships (or a list of elements + all relationships) into database (adding a user SQL query to the default SQL query builded by QxOrm library)
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param t Element (or list of elements) to be updated into database
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::update_by_query_with_all_relation<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline QSqlError update_by_query_with_all_relation(const qx::QxSqlQuery & query, T & t)
{ return qx::dao::detail::QxDao_Update_WithRelation<T>::update("*", query, t, NULL); }

/*!
 * \ingroup QxDao
 * \brief Insert (if no exist) or update (if already exist) an element and its relationships (or a list of elements + relationships) into database
 * \param relation List of relationships keys to be inserted or updated in others tables of database : use "|" separator to put many relationships keys into this parameter
 * \param t Element (or list of elements) to be inserted (if no exist) or updated (if already exist) into database
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::save_with_relation<T>() execute following SQL query :<br>
 * <i>INSERT INTO my_table (my_column_1, my_column_2, etc.) VALUES (?, ?, etc.)</i>
 * <br>or (if already exist into database) :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i>
 */
template <class T>
inline QSqlError save_with_relation(const QString & relation, T & t)
{ return qx::dao::detail::QxDao_Save_WithRelation<T>::save(relation, t, NULL); }

/*!
 * \ingroup QxDao
 * \brief Insert (if no exist) or update (if already exist) an element and its relationships (or a list of elements + relationships) into database
 * \param relation List of relationships keys to be inserted or updated in others tables of database
 * \param t Element (or list of elements) to be inserted (if no exist) or updated (if already exist) into database
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::save_with_relation<T>() execute following SQL query :<br>
 * <i>INSERT INTO my_table (my_column_1, my_column_2, etc.) VALUES (?, ?, etc.)</i>
 * <br>or (if already exist into database) :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i>
 */
template <class T>
inline QSqlError save_with_relation(const QStringList & relation, T & t)
{ return qx::dao::detail::QxDao_Save_WithRelation<T>::save(relation, t, NULL); }

/*!
 * \ingroup QxDao
 * \brief Insert (if no exist) or update (if already exist) an element and all its relationships (or a list of elements + all relationships) into database
 * \param t Element (or list of elements) to be inserted (if no exist) or updated (if already exist) into database
 * \return Empty QSqlError object (from Qt library) if no error occurred; otherwise QSqlError contains a description of database error executing SQL query
 *
 * qx::dao::save_with_all_relation<T>() execute following SQL query :<br>
 * <i>INSERT INTO my_table (my_column_1, my_column_2, etc.) VALUES (?, ?, etc.)</i>
 * <br>or (if already exist into database) :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i>
 */
template <class T>
inline QSqlError save_with_all_relation(T & t)
{ return qx::dao::detail::QxDao_Save_WithRelation<T>::save("*", t, NULL); }

/*!
 * \ingroup QxDao
 * \brief Callback before inserting an object into database (<a href="http://www.qxorm.com/qxorm_en/faq.html#faq_130" target="_blank">here is an example using QxOrm Trigger</a>)
 */
template <class T>
inline void on_before_insert(T * t, qx::dao::detail::IxDao_Helper * dao)
{ qx::dao::detail::QxDao_Trigger<T>::onBeforeInsert(t, dao); }

/*!
 * \ingroup QxDao
 * \brief Callback before updating an object into database (<a href="http://www.qxorm.com/qxorm_en/faq.html#faq_130" target="_blank">here is an example using QxOrm Trigger</a>)
 */
template <class T>
inline void on_before_update(T * t, qx::dao::detail::IxDao_Helper * dao)
{ qx::dao::detail::QxDao_Trigger<T>::onBeforeUpdate(t, dao); }

/*!
 * \ingroup QxDao
 * \brief Callback before deleting an object into database (<a href="http://www.qxorm.com/qxorm_en/faq.html#faq_130" target="_blank">here is an example using QxOrm Trigger</a>)
 */
template <class T>
inline void on_before_delete(T * t, qx::dao::detail::IxDao_Helper * dao)
{ qx::dao::detail::QxDao_Trigger<T>::onBeforeDelete(t, dao); }

/*!
 * \ingroup QxDao
 * \brief Callback after inserting an object into database (<a href="http://www.qxorm.com/qxorm_en/faq.html#faq_130" target="_blank">here is an example using QxOrm Trigger</a>)
 */
template <class T>
inline void on_after_insert(T * t, qx::dao::detail::IxDao_Helper * dao)
{ qx::dao::detail::QxDao_Trigger<T>::onAfterInsert(t, dao); }

/*!
 * \ingroup QxDao
 * \brief Callback after updating an object into database (<a href="http://www.qxorm.com/qxorm_en/faq.html#faq_130" target="_blank">here is an example using QxOrm Trigger</a>)
 */
template <class T>
inline void on_after_update(T * t, qx::dao::detail::IxDao_Helper * dao)
{ qx::dao::detail::QxDao_Trigger<T>::onAfterUpdate(t, dao); }

/*!
 * \ingroup QxDao
 * \brief Callback after deleting an object into database (<a href="http://www.qxorm.com/qxorm_en/faq.html#faq_130" target="_blank">here is an example using QxOrm trigger</a>)
 */
template <class T>
inline void on_after_delete(T * t, qx::dao::detail::IxDao_Helper * dao)
{ qx::dao::detail::QxDao_Trigger<T>::onAfterDelete(t, dao); }

} // namespace dao
} // namespace qx

#endif // _QX_DAO_H_
