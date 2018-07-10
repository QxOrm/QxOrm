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

#ifndef _QX_DAO_THROWABLE_H_
#define _QX_DAO_THROWABLE_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxDaoThrowable.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Same functions as qx::dao namespace, but throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred (instead of returning a QSqlError instance)
 */

#include <QxDao/QxDao.h>
#include <QxDao/QxSqlError.h>

namespace qx {
namespace dao {

/*!
 * \ingroup QxDao
 * \brief Same functions as qx::dao namespace, but throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred (instead of returning a QSqlError instance)
 */
namespace throwable {

/// @cond TO_AVOID_DOXYGEN_WARNINGS

/*!
 * \ingroup QxDao
 * \brief Return the number of lines in the table (database) mapped to the C++ class T (registered into QxOrm context) and filtered by a user SQL query
 * \param lCount Output parameter with the number of lines in the table associated to the SQL query
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library (optional parameter)
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 *
 * qx::dao::throwable::count<T>() execute following SQL query :<br>
 * <i>SELECT COUNT(*) FROM my_table</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline void count(long & lCount, const qx::QxSqlQuery & query = qx::QxSqlQuery(), QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_Count<T>::count(lCount, query, pDatabase); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Insert an element or a list of elements into database
 * \param t Element (or list of elements) to be inserted into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::insert<T>() execute following SQL query :<br>
 * <i>INSERT INTO my_table (my_column_1, my_column_2, etc.) VALUES (?, ?, etc.)</i>
 */
template <class T>
inline void insert(T & t, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_Insert<T>::insert(t, pDatabase); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Insert (if no exist) or update (if already exist) an element or a list of elements into database
 * \param t Element (or list of elements) to be inserted (if no exist) or updated (if already exist) into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::save<T>() execute following SQL query :<br>
 * <i>INSERT INTO my_table (my_column_1, my_column_2, etc.) VALUES (?, ?, etc.)</i>
 * <br>or (if already exist into database) :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i>
 */
template <class T>
inline void save(T & t, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_Save<T>::save(t, pDatabase); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Delete a line (or list of lines) of a table (database) mapped to a C++ object of type T (registered into QxOrm context)
 * \param t Element (or list of elements) to be deleted into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::delete_by_id<T>() execute following SQL query :<br>
 * <i>DELETE FROM my_table WHERE my_id = ?</i><br>
 * <br>
 * If a soft delete behavior is defined for class T, qx::dao::throwable::delete_by_id<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET is_deleted='1' WHERE my_id = ?</i>
 */
template <class T>
inline void delete_by_id(T & t, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_DeleteById<T>::deleteById(t, pDatabase, true); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Destroy a line (or list of lines) of a table (database) mapped to a C++ object of type T (registered into QxOrm context), even if a soft delete behavior is defined for class T
 * \param t Element (or list of elements) to be destroyed into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::destroy_by_id<T>() execute following SQL query :<br>
 * <i>DELETE FROM my_table WHERE my_id = ?</i>
 */
template <class T>
inline void destroy_by_id(T & t, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_DeleteById<T>::deleteById(t, pDatabase, false); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Delete all lines of a table (database) mapped to a C++ class T (registered into QxOrm context)
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::delete_all<T>() execute following SQL query :<br>
 * <i>DELETE FROM my_table</i><br>
 * <br>
 * If a soft delete behavior is defined for class T, qx::dao::throwable::delete_all<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET is_deleted='1'</i>
 */
template <class T>
inline void delete_all(QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_DeleteAll<T>::deleteAll("", pDatabase, true); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Destroy all lines of a table (database) mapped to a C++ class T (registered into QxOrm context), even if a soft delete behavior is defined for class T
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::destroy_all<T>() execute following SQL query :<br>
 * <i>DELETE FROM my_table</i>
 */
template <class T>
inline void destroy_all(QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_DeleteAll<T>::deleteAll("", pDatabase, false); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Delete all lines of a table (database) mapped to a C++ class T (registered into QxOrm context) and filtered by a user SQL query
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::delete_by_query<T>() execute following SQL query :<br>
 * <i>DELETE FROM my_table</i> + <i>WHERE my_query...</i><br>
 * <br>
 * If a soft delete behavior is defined for class T, qx::dao::throwable::delete_by_query<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET is_deleted='1'</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline void delete_by_query(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_DeleteAll<T>::deleteAll(query, pDatabase, true); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Destroy all lines of a table (database) mapped to a C++ class T (registered into QxOrm context) and filtered by a user SQL query, even if a soft delete behavior is defined for class T
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::destroy_by_query<T>() execute following SQL query :<br>
 * <i>DELETE FROM my_table</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline void destroy_by_query(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_DeleteAll<T>::deleteAll(query, pDatabase, false); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Create a table into database (with all columns) mapped to a C++ class T (registered into QxOrm context) : be careful, this function can be used only with a SQLite database to create examples or prototypes; For other databases, it is recommended to use QxEntityEditor application or to manage the database schema with an external tool provided by the SGBD (SQLite Manager for SQLite, pgAdmin for PostgreSQL, MySQL Workbench for MySQL, etc...)
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::create_table<T>() execute following SQL query :<br>
 * <i>CREATE TABLE my_table (my_id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, my_column_1 TEXT, my_column_2 TEXT, etc.)</i>
 */
template <class T>
inline void create_table(QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_CreateTable<T>::createTable(pDatabase); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Fetch an object t (retrieve all its properties) of type T (registered into QxOrm context) mapped to a table in the database (t must have a valid id before to be fetched without error)
 * \param relation List of relationships keys to be fetched (eager fetch instead of default lazy fetch for a relation) : use "|" separator to put many relationships keys into this parameter
 * \param t Instance (with a valid id) to be fetched (retrieve all properties from database)
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::fetch_by_id_with_relation<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table WHERE my_id = ?</i>
 */
template <class T>
inline void fetch_by_id_with_relation(const QString & relation, T & t, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_FetchById_WithRelation<T>::fetchById(relation, t, pDatabase); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Fetch an object t (retrieve all its properties) of type T (registered into QxOrm context) mapped to a table in the database (t must have a valid id before to be fetched without error)
 * \param relation List of relationships keys to be fetched (eager fetch instead of default lazy fetch for a relation)
 * \param t Instance (with a valid id) to be fetched (retrieve all properties from database)
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::fetch_by_id_with_relation<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table WHERE my_id = ?</i>
 */
template <class T>
inline void fetch_by_id_with_relation(const QStringList & relation, T & t, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_FetchById_WithRelation<T>::fetchById(relation, t, pDatabase); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Fetch an object t (retrieve all its properties and relationships) of type T (registered into QxOrm context) mapped to a table in the database (t must have a valid id before to be fetched without error)
 * \param t Instance (with a valid id) to be fetched (retrieve all properties and relationships from database)
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::fetch_by_id_with_all_relation<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table WHERE my_id = ?</i>
 */
template <class T>
inline void fetch_by_id_with_all_relation(T & t, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_FetchById_WithRelation<T>::fetchById("*", t, pDatabase); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Fetch a list of objects (retrieve all elements and properties associated) of type T (container registered into QxOrm context) mapped to a table in the database
 * \param relation List of relationships keys to be fetched (eager fetch instead of default lazy fetch for a relation) : use "|" separator to put many relationships keys into this parameter
 * \param t Container to be fetched (retrieve all elements and properties associated); t is cleared before executing SQL query
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::fetch_all_with_relation<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table</i>
 */
template <class T>
inline void fetch_all_with_relation(const QString & relation, T & t, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll(relation, "", t, pDatabase); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Fetch a list of objects (retrieve all elements and properties associated) of type T (container registered into QxOrm context) mapped to a table in the database
 * \param relation List of relationships keys to be fetched (eager fetch instead of default lazy fetch for a relation)
 * \param t Container to be fetched (retrieve all elements and properties associated); t is cleared before executing SQL query
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::fetch_all_with_relation<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table</i>
 */
template <class T>
inline void fetch_all_with_relation(const QStringList & relation, T & t, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll(relation, "", t, pDatabase); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Fetch a list of objects (retrieve all elements and properties + all relationships associated) of type T (container registered into QxOrm context) mapped to a table in the database
 * \param t Container to be fetched (retrieve all elements and properties + all relationships associated); t is cleared before executing SQL query
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::fetch_all_with_all_relation<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table</i>
 */
template <class T>
inline void fetch_all_with_all_relation(T & t, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll("*", "", t, pDatabase); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Fetch a list of objects (retrieve all elements and properties associated) of type T (container registered into QxOrm context) mapped to a table in the database and filtered by a user SQL query
 * \param relation List of relationships keys to be fetched (eager fetch instead of default lazy fetch for a relation) : use "|" separator to put many relationships keys into this parameter
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param t Container to be fetched (retrieve all elements and properties associated); t is cleared before executing SQL query
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::fetch_by_query_with_relation<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline void fetch_by_query_with_relation(const QString & relation, const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll(relation, query, t, pDatabase); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Fetch a list of objects (retrieve all elements and properties associated) of type T (container registered into QxOrm context) mapped to a table in the database and filtered by a user SQL query
 * \param relation List of relationships keys to be fetched (eager fetch instead of default lazy fetch for a relation)
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param t Container to be fetched (retrieve all elements and properties associated); t is cleared before executing SQL query
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::fetch_by_query_with_relation<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline void fetch_by_query_with_relation(const QStringList & relation, const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll(relation, query, t, pDatabase); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Fetch a list of objects (retrieve all elements and properties + all relationships associated) of type T (container registered into QxOrm context) mapped to a table in the database and filtered by a user SQL query
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param t Container to be fetched (retrieve all elements and properties + all relationships associated); t is cleared before executing SQL query
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::fetch_by_query_with_all_relation<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline void fetch_by_query_with_all_relation(const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll("*", query, t, pDatabase); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Insert an element and its relationships (or a list of elements + relationships) into database
 * \param relation List of relationships keys to be inserted in others tables of database : use "|" separator to put many relationships keys into this parameter
 * \param t Element (or list of elements) to be inserted into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::insert_with_relation<T>() execute following SQL query :<br>
 * <i>INSERT INTO my_table (my_column_1, my_column_2, etc.) VALUES (?, ?, etc.)</i>
 */
template <class T>
inline void insert_with_relation(const QString & relation, T & t, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_Insert_WithRelation<T>::insert(relation, t, pDatabase); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Insert an element and its relationships (or a list of elements + relationships) into database
 * \param relation List of relationships keys to be inserted in others tables of database
 * \param t Element (or list of elements) to be inserted into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::insert_with_relation<T>() execute following SQL query :<br>
 * <i>INSERT INTO my_table (my_column_1, my_column_2, etc.) VALUES (?, ?, etc.)</i>
 */
template <class T>
inline void insert_with_relation(const QStringList & relation, T & t, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_Insert_WithRelation<T>::insert(relation, t, pDatabase); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Insert an element and all its relationships (or a list of elements + all relationships) into database
 * \param t Element (or list of elements) to be inserted into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::insert_with_all_relation<T>() execute following SQL query :<br>
 * <i>INSERT INTO my_table (my_column_1, my_column_2, etc.) VALUES (?, ?, etc.)</i>
 */
template <class T>
inline void insert_with_all_relation(T & t, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_Insert_WithRelation<T>::insert("*", t, pDatabase); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Update an element and its relationships (or a list of elements + relationships) into database
 * \param relation List of relationships keys to be updated in others tables of database : use "|" separator to put many relationships keys into this parameter
 * \param t Element (or list of elements) to be updated into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::update_with_relation<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i>
 */
template <class T>
inline void update_with_relation(const QString & relation, T & t, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_Update_WithRelation<T>::update(relation, "", t, pDatabase); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Update an element and its relationships (or a list of elements + relationships) into database (adding a user SQL query to the default SQL query builded by QxOrm library)
 * \param relation List of relationships keys to be updated in others tables of database : use "|" separator to put many relationships keys into this parameter
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param t Element (or list of elements) to be updated into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::update_by_query_with_relation<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline void update_by_query_with_relation(const QString & relation, const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_Update_WithRelation<T>::update(relation, query, t, pDatabase); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Update an element and its relationships (or a list of elements + relationships) into database
 * \param relation List of relationships keys to be updated in others tables of database
 * \param t Element (or list of elements) to be updated into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::update_with_relation<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i>
 */
template <class T>
inline void update_with_relation(const QStringList & relation, T & t, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_Update_WithRelation<T>::update(relation, "", t, pDatabase); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Update an element and its relationships (or a list of elements + relationships) into database (adding a user SQL query to the default SQL query builded by QxOrm library)
 * \param relation List of relationships keys to be updated in others tables of database
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param t Element (or list of elements) to be updated into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::update_by_query_with_relation<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline void update_by_query_with_relation(const QStringList & relation, const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_Update_WithRelation<T>::update(relation, query, t, pDatabase); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Update an element and all its relationships (or a list of elements + all relationships) into database
 * \param t Element (or list of elements) to be updated into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::update_with_all_relation<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i>
 */
template <class T>
inline void update_with_all_relation(T & t, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_Update_WithRelation<T>::update("*", "", t, pDatabase); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Update an element and all its relationships (or a list of elements + all relationships) into database (adding a user SQL query to the default SQL query builded by QxOrm library)
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param t Element (or list of elements) to be updated into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::update_by_query_with_all_relation<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline void update_by_query_with_all_relation(const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_Update_WithRelation<T>::update("*", query, t, pDatabase); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Insert (if no exist) or update (if already exist) an element and its relationships (or a list of elements + relationships) into database
 * \param relation List of relationships keys to be inserted or updated in others tables of database : use "|" separator to put many relationships keys into this parameter
 * \param t Element (or list of elements) to be inserted (if no exist) or updated (if already exist) into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::save_with_relation<T>() execute following SQL query :<br>
 * <i>INSERT INTO my_table (my_column_1, my_column_2, etc.) VALUES (?, ?, etc.)</i>
 * <br>or (if already exist into database) :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i>
 */
template <class T>
inline void save_with_relation(const QString & relation, T & t, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_Save_WithRelation<T>::save(relation, t, pDatabase); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Insert (if no exist) or update (if already exist) an element and its relationships (or a list of elements + relationships) into database
 * \param relation List of relationships keys to be inserted or updated in others tables of database
 * \param t Element (or list of elements) to be inserted (if no exist) or updated (if already exist) into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::save_with_relation<T>() execute following SQL query :<br>
 * <i>INSERT INTO my_table (my_column_1, my_column_2, etc.) VALUES (?, ?, etc.)</i>
 * <br>or (if already exist into database) :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i>
 */
template <class T>
inline void save_with_relation(const QStringList & relation, T & t, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_Save_WithRelation<T>::save(relation, t, pDatabase); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Insert (if no exist) or update (if already exist) an element and all its relationships (or a list of elements + all relationships) into database
 * \param t Element (or list of elements) to be inserted (if no exist) or updated (if already exist) into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::save_with_all_relation<T>() execute following SQL query :<br>
 * <i>INSERT INTO my_table (my_column_1, my_column_2, etc.) VALUES (?, ?, etc.)</i>
 * <br>or (if already exist into database) :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i>
 */
template <class T>
inline void save_with_all_relation(T & t, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_Save_WithRelation<T>::save("*", t, pDatabase); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Insert (if no exist) or update (if already exist) recursively an element and all levels of relationships (or a list of elements + all levels of relationships) into database, useful to save a tree structure for example
 * \param t Element (or list of elements) to be inserted (if no exist) or updated (if already exist) into database
 * \param eSaveMode To improve performance, use this parameter to indicate if you just want to insert or update all elements in database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \param pRelationParams Keep this parameter as NULL, it is used internally by QxOrm library to iterate over each level of relationship
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::save_with_relation_recursive<T>() execute following SQL query :<br>
 * <i>INSERT INTO my_table (my_column_1, my_column_2, etc.) VALUES (?, ?, etc.)</i>
 * <br>or (if already exist into database) :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i><br>
 * <br>
 * <b>Note :</b> to improve performance, and if you know that you are just inserting or updating items in database, you can use the parameter <i>eSaveMode</i> :<br>
 * - <i>qx::dao::save_mode::e_check_insert_or_update</i> : check before saving if item already exists in database ;<br>
 * - <i>qx::dao::save_mode::e_insert_only</i> : only insert items in database (use only 1 SQL query to insert collection of items) ;<br>
 * - <i>qx::dao::save_mode::e_update_only</i> : only update items in database (use only 1 SQL query to update collection of items).
 */
template <class T>
inline void save_with_relation_recursive(T & t, qx::dao::save_mode::e_save_mode eSaveMode = qx::dao::save_mode::e_check_insert_or_update, QSqlDatabase * pDatabase = NULL, qx::QxSqlRelationParams * pRelationParams = NULL)
{ QSqlError err = qx::dao::detail::QxDao_Save_WithRelation_Recursive<T>::save(t, eSaveMode, pDatabase, pRelationParams); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Fetch an object t (retrieve all its properties) of type T (registered into QxOrm context) mapped to a table in the database (t must have a valid id before to be fetched without error)
 * \param t Instance (with a valid id) to be fetched (retrieve all properties from database)
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \param columns List of database table columns (mapped to properties of C++ class T) to be fetched (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::fetch_by_id<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table WHERE my_id = ?</i>
 */
template <class T>
inline void fetch_by_id(T & t, QSqlDatabase * pDatabase = NULL, const QStringList & columns = QStringList())
{ QSqlError err = qx::dao::detail::QxDao_FetchById<T>::fetchById(t, pDatabase, columns); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Fetch a list of objects (retrieve all elements and properties associated) of type T (container registered into QxOrm context) mapped to a table in the database
 * \param t Container to be fetched (retrieve all elements and properties associated); t is cleared before executing SQL query
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \param columns List of database table columns (mapped to properties of C++ class T) to be fetched (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::fetch_all<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table</i>
 */
template <class T>
inline void fetch_all(T & t, QSqlDatabase * pDatabase = NULL, const QStringList & columns = QStringList())
{ QSqlError err = qx::dao::detail::QxDao_FetchAll<T>::fetchAll("", t, pDatabase, columns); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Fetch a list of objects (retrieve all elements and properties associated) of type T (container registered into QxOrm context) mapped to a table in the database and filtered by a user SQL query
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param t Container to be fetched (retrieve all elements and properties associated); t is cleared before executing SQL query
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \param columns List of database table columns (mapped to properties of C++ class T) to be fetched (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::fetch_by_query<T>() execute following SQL query :<br>
 * <i>SELECT * FROM my_table</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline void fetch_by_query(const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase = NULL, const QStringList & columns = QStringList())
{ QSqlError err = qx::dao::detail::QxDao_FetchAll<T>::fetchAll(query, t, pDatabase, columns); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Update an element or a list of elements into database
 * \param t Element (or list of elements) to be updated into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \param columns List of database table columns (mapped to properties of C++ class T) to be updated (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::update<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i>
 */
template <class T>
inline void update(T & t, QSqlDatabase * pDatabase = NULL, const QStringList & columns = QStringList())
{ QSqlError err = qx::dao::detail::QxDao_Update<T>::update("", t, pDatabase, columns); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Update an element or a list of elements into database (adding a user SQL query to the default SQL query builded by QxOrm library)
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param t Element (or list of elements) to be updated into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \param columns List of database table columns (mapped to properties of C++ class T) to be updated (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::update_by_query<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline void update_by_query(const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase = NULL, const QStringList & columns = QStringList())
{ QSqlError err = qx::dao::detail::QxDao_Update<T>::update(query, t, pDatabase, columns); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Update only modified fields/properties of an element or a list of elements into database (using is dirty pattern and qx::dao::ptr<T> smart-pointer)
 * \param ptr Element (or list of elements) to be updated into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::update_optimized<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i>
 */
template <class T>
inline void update_optimized(qx::dao::ptr<T> & ptr, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_Update_Optimized<T>::update_optimized("", ptr, pDatabase); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Update only modified fields/properties of an element or a list of elements into database (using is dirty pattern and qx::dao::ptr<T> smart-pointer), adding a user SQL query to the default SQL query builded by QxOrm library
 * \param query Define a user SQL query added to default SQL query builded by QxOrm library
 * \param ptr Element (or list of elements) to be updated into database
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 *
 * qx::dao::throwable::update_optimized_by_query<T>() execute following SQL query :<br>
 * <i>UPDATE my_table SET my_column_1 = ?, my_column_2 = ?, etc.</i> + <i>WHERE my_query...</i>
 */
template <class T>
inline void update_optimized_by_query(const qx::QxSqlQuery & query, qx::dao::ptr<T> & ptr, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_Update_Optimized<T>::update_optimized(query, ptr, pDatabase); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/*!
 * \ingroup QxDao
 * \brief Execute a custom SQL query or a stored procedure, all columns that can be mapped to the instance of type T will be fetched automatically
 * \param query Define a custom SQL query or a stored procedure to call
 * \param t Instance of type T, all columns that can be mapped to this instance will be fetched automatically
 * \param pDatabase Connection to database (you can manage your own connection pool for example, you can also define a transaction, etc.); if NULL, a valid connection for the current thread is provided by qx::QxSqlDatabase singleton class (optional parameter)
 * \return Throw a <i>qx::dao::sql_error</i> exception when a SQL error occurred
 */
template <class T>
inline void execute_query(qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::detail::QxDao_ExecuteQuery<T>::executeQuery(query, t, pDatabase); if (err.isValid()) { throw qx::dao::sql_error(err); } }

inline void call_query(qx::QxSqlQuery & query, QSqlDatabase * pDatabase = NULL)
{ QSqlError err = qx::dao::call_query(query, pDatabase); if (err.isValid()) { throw qx::dao::sql_error(err); } }

/// @endcond

} // namespace throwable
} // namespace dao
} // namespace qx

#endif // _QX_DAO_THROWABLE_H_
