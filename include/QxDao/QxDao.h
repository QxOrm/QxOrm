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

#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqlrecord.h>
#include <QtSql/qsqlfield.h>
#include <QtSql/qsqlerror.h>
#include <QtSql/qsqldriver.h>

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
template <class T> struct QxDao_Update_WithRelation;
template <class T> struct QxDao_Save;
template <class T> struct QxDao_Save_WithRelation;
template <class T> struct QxDao_DeleteById;
template <class T> struct QxDao_DeleteAll;
template <class T> struct QxDao_Exist;
template <class T> struct QxDao_CreateTable;
template <class T> struct QxDao_Trigger;
} // namespace detail

template <class T> inline long count(QSqlDatabase * pDatabase)                                                    { return qx::dao::detail::QxDao_Count<T>::count("", pDatabase); }
template <class T> inline long count(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase)                      { return qx::dao::detail::QxDao_Count<T>::count(query, pDatabase); }
template <class T> inline QSqlError fetch_by_id(T & t, QSqlDatabase * pDatabase)                                  { return qx::dao::detail::QxDao_FetchById<T>::fetchById(t, pDatabase); }
template <class T> inline QSqlError fetch_all(T & t, QSqlDatabase * pDatabase)                                    { return qx::dao::detail::QxDao_FetchAll<T>::fetchAll("", t, pDatabase); }
template <class T> inline QSqlError fetch_by_query(const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase) { return qx::dao::detail::QxDao_FetchAll<T>::fetchAll(query, t, pDatabase); }
template <class T> inline QSqlError insert(T & t, QSqlDatabase * pDatabase)                                       { return qx::dao::detail::QxDao_Insert<T>::insert(t, pDatabase); }
template <class T> inline QSqlError update(T & t, QSqlDatabase * pDatabase)                                       { return qx::dao::detail::QxDao_Update<T>::update(t, pDatabase); }
template <class T> inline QSqlError save(T & t, QSqlDatabase * pDatabase)                                         { return qx::dao::detail::QxDao_Save<T>::save(t, pDatabase); }
template <class T> inline QSqlError delete_by_id(T & t, QSqlDatabase * pDatabase)                                 { return qx::dao::detail::QxDao_DeleteById<T>::deleteById(t, pDatabase); }
template <class T> inline QSqlError delete_all(QSqlDatabase * pDatabase)                                          { return qx::dao::detail::QxDao_DeleteAll<T>::deleteAll("", pDatabase); }
template <class T> inline QSqlError delete_by_query(const qx::QxSqlQuery & query, QSqlDatabase * pDatabase)       { return qx::dao::detail::QxDao_DeleteAll<T>::deleteAll(query, pDatabase); }
template <class T> inline QSqlError create_table(QSqlDatabase * pDatabase)                                        { return qx::dao::detail::QxDao_CreateTable<T>::createTable(pDatabase); }
template <class T> inline qx_bool exist(T & t, QSqlDatabase * pDatabase)                                          { return qx::dao::detail::QxDao_Exist<T>::exist(t, pDatabase); }

template <class T> inline QSqlError fetch_by_id_with_relation(const QString & relation, T & t, QSqlDatabase * pDatabase)                                       { return qx::dao::detail::QxDao_FetchById_WithRelation<T>::fetchById(relation, t, pDatabase); }
template <class T> inline QSqlError fetch_by_id_with_relation(const QStringList & relation, T & t, QSqlDatabase * pDatabase)                                   { return qx::dao::detail::QxDao_FetchById_WithRelation<T>::fetchById(relation, t, pDatabase); }
template <class T> inline QSqlError fetch_by_id_with_all_relation(T & t, QSqlDatabase * pDatabase)                                                             { return qx::dao::detail::QxDao_FetchById_WithRelation<T>::fetchById("*", t, pDatabase); }
template <class T> inline QSqlError fetch_all_with_relation(const QString & relation, T & t, QSqlDatabase * pDatabase)                                         { return qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll(relation, "", t, pDatabase); }
template <class T> inline QSqlError fetch_all_with_relation(const QStringList & relation, T & t, QSqlDatabase * pDatabase)                                     { return qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll(relation, "", t, pDatabase); }
template <class T> inline QSqlError fetch_all_with_all_relation(T & t, QSqlDatabase * pDatabase)                                                               { return qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll("*", "", t, pDatabase); }
template <class T> inline QSqlError fetch_by_query_with_relation(const QString & relation, const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase)      { return qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll(relation, query, t, pDatabase); }
template <class T> inline QSqlError fetch_by_query_with_relation(const QStringList & relation, const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase)  { return qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll(relation, query, t, pDatabase); }
template <class T> inline QSqlError fetch_by_query_with_all_relation(const qx::QxSqlQuery & query, T & t, QSqlDatabase * pDatabase)                            { return qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll("*", query, t, pDatabase); }

template <class T> inline QSqlError insert_with_relation(const QString & relation, T & t, QSqlDatabase * pDatabase)        { return qx::dao::detail::QxDao_Insert_WithRelation<T>::insert(relation, t, pDatabase); }
template <class T> inline QSqlError insert_with_relation(const QStringList & relation, T & t, QSqlDatabase * pDatabase)    { return qx::dao::detail::QxDao_Insert_WithRelation<T>::insert(relation, t, pDatabase); }
template <class T> inline QSqlError insert_with_all_relation(T & t, QSqlDatabase * pDatabase)                              { return qx::dao::detail::QxDao_Insert_WithRelation<T>::insert("*", t, pDatabase); }
template <class T> inline QSqlError update_with_relation(const QString & relation, T & t, QSqlDatabase * pDatabase)        { return qx::dao::detail::QxDao_Update_WithRelation<T>::update(relation, t, pDatabase); }
template <class T> inline QSqlError update_with_relation(const QStringList & relation, T & t, QSqlDatabase * pDatabase)    { return qx::dao::detail::QxDao_Update_WithRelation<T>::update(relation, t, pDatabase); }
template <class T> inline QSqlError update_with_all_relation(T & t, QSqlDatabase * pDatabase)                              { return qx::dao::detail::QxDao_Update_WithRelation<T>::update("*", t, pDatabase); }
template <class T> inline QSqlError save_with_relation(const QString & relation, T & t, QSqlDatabase * pDatabase)          { return qx::dao::detail::QxDao_Save_WithRelation<T>::save(relation, t, pDatabase); }
template <class T> inline QSqlError save_with_relation(const QStringList & relation, T & t, QSqlDatabase * pDatabase)      { return qx::dao::detail::QxDao_Save_WithRelation<T>::save(relation, t, pDatabase); }
template <class T> inline QSqlError save_with_all_relation(T & t, QSqlDatabase * pDatabase)                                { return qx::dao::detail::QxDao_Save_WithRelation<T>::save("*", t, pDatabase); }

template <class T> inline long count()                                                    { return qx::dao::detail::QxDao_Count<T>::count("", NULL); }
template <class T> inline long count(const qx::QxSqlQuery & query)                        { return qx::dao::detail::QxDao_Count<T>::count(query, NULL); }
template <class T> inline QSqlError fetch_by_id(T & t)                                    { return qx::dao::detail::QxDao_FetchById<T>::fetchById(t, NULL); }
template <class T> inline QSqlError fetch_all(T & t)                                      { return qx::dao::detail::QxDao_FetchAll<T>::fetchAll("", t, NULL); }
template <class T> inline QSqlError fetch_by_query(const qx::QxSqlQuery & query, T & t)   { return qx::dao::detail::QxDao_FetchAll<T>::fetchAll(query, t, NULL); }
template <class T> inline QSqlError insert(T & t)                                         { return qx::dao::detail::QxDao_Insert<T>::insert(t, NULL); }
template <class T> inline QSqlError update(T & t)                                         { return qx::dao::detail::QxDao_Update<T>::update(t, NULL); }
template <class T> inline QSqlError save(T & t)                                           { return qx::dao::detail::QxDao_Save<T>::save(t, NULL); }
template <class T> inline QSqlError delete_by_id(T & t)                                   { return qx::dao::detail::QxDao_DeleteById<T>::deleteById(t, NULL); }
template <class T> inline QSqlError delete_all()                                          { return qx::dao::detail::QxDao_DeleteAll<T>::deleteAll("", NULL); }
template <class T> inline QSqlError delete_by_query(const qx::QxSqlQuery & query)         { return qx::dao::detail::QxDao_DeleteAll<T>::deleteAll(query, NULL); }
template <class T> inline QSqlError create_table()                                        { return qx::dao::detail::QxDao_CreateTable<T>::createTable(NULL); }
template <class T> inline qx_bool exist(T & t)                                            { return qx::dao::detail::QxDao_Exist<T>::exist(t, NULL); }

template <class T> inline QSqlError fetch_by_id_with_relation(const QString & relation, T & t)                                      { return qx::dao::detail::QxDao_FetchById_WithRelation<T>::fetchById(relation, t, NULL); }
template <class T> inline QSqlError fetch_by_id_with_relation(const QStringList & relation, T & t)                                  { return qx::dao::detail::QxDao_FetchById_WithRelation<T>::fetchById(relation, t, NULL); }
template <class T> inline QSqlError fetch_by_id_with_all_relation(T & t)                                                            { return qx::dao::detail::QxDao_FetchById_WithRelation<T>::fetchById("*", t, NULL); }
template <class T> inline QSqlError fetch_all_with_relation(const QString & relation, T & t)                                        { return qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll(relation, "", t, NULL); }
template <class T> inline QSqlError fetch_all_with_relation(const QStringList & relation, T & t)                                    { return qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll(relation, "", t, NULL); }
template <class T> inline QSqlError fetch_all_with_all_relation(T & t)                                                              { return qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll("*", "", t, NULL); }
template <class T> inline QSqlError fetch_by_query_with_relation(const QString & relation, const qx::QxSqlQuery & query, T & t)     { return qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll(relation, query, t, NULL); }
template <class T> inline QSqlError fetch_by_query_with_relation(const QStringList & relation, const qx::QxSqlQuery & query, T & t) { return qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll(relation, query, t, NULL); }
template <class T> inline QSqlError fetch_by_query_with_all_relation(const qx::QxSqlQuery & query, T & t)                           { return qx::dao::detail::QxDao_FetchAll_WithRelation<T>::fetchAll("*", query, t, NULL); }

template <class T> inline QSqlError insert_with_relation(const QString & relation, T & t)       { return qx::dao::detail::QxDao_Insert_WithRelation<T>::insert(relation, t, NULL); }
template <class T> inline QSqlError insert_with_relation(const QStringList & relation, T & t)   { return qx::dao::detail::QxDao_Insert_WithRelation<T>::insert(relation, t, NULL); }
template <class T> inline QSqlError insert_with_all_relation(T & t)                             { return qx::dao::detail::QxDao_Insert_WithRelation<T>::insert("*", t, NULL); }
template <class T> inline QSqlError update_with_relation(const QString & relation, T & t)       { return qx::dao::detail::QxDao_Update_WithRelation<T>::update(relation, t, NULL); }
template <class T> inline QSqlError update_with_relation(const QStringList & relation, T & t)   { return qx::dao::detail::QxDao_Update_WithRelation<T>::update(relation, t, NULL); }
template <class T> inline QSqlError update_with_all_relation(T & t)                             { return qx::dao::detail::QxDao_Update_WithRelation<T>::update("*", t, NULL); }
template <class T> inline QSqlError save_with_relation(const QString & relation, T & t)         { return qx::dao::detail::QxDao_Save_WithRelation<T>::save(relation, t, NULL); }
template <class T> inline QSqlError save_with_relation(const QStringList & relation, T & t)     { return qx::dao::detail::QxDao_Save_WithRelation<T>::save(relation, t, NULL); }
template <class T> inline QSqlError save_with_all_relation(T & t)                               { return qx::dao::detail::QxDao_Save_WithRelation<T>::save("*", t, NULL); }

template <class T> inline void on_before_insert(T * t, qx::dao::detail::IxDao_Helper * dao)  { qx::dao::detail::QxDao_Trigger<T>::onBeforeInsert(t, dao); }
template <class T> inline void on_before_update(T * t, qx::dao::detail::IxDao_Helper * dao)  { qx::dao::detail::QxDao_Trigger<T>::onBeforeUpdate(t, dao); }
template <class T> inline void on_before_delete(T * t, qx::dao::detail::IxDao_Helper * dao)  { qx::dao::detail::QxDao_Trigger<T>::onBeforeDelete(t, dao); }
template <class T> inline void on_after_insert(T * t, qx::dao::detail::IxDao_Helper * dao)   { qx::dao::detail::QxDao_Trigger<T>::onAfterInsert(t, dao); }
template <class T> inline void on_after_update(T * t, qx::dao::detail::IxDao_Helper * dao)   { qx::dao::detail::QxDao_Trigger<T>::onAfterUpdate(t, dao); }
template <class T> inline void on_after_delete(T * t, qx::dao::detail::IxDao_Helper * dao)   { qx::dao::detail::QxDao_Trigger<T>::onAfterDelete(t, dao); }

} // namespace dao
} // namespace qx

#endif // _QX_DAO_H_
