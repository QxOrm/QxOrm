#ifndef _QX_SERVICE_MODE_CLIENT

#include "../../include/precompiled.h"

#include "../../include/dao/user_manager.h"

#include <QxOrm_Impl.h>

void user_manager::init_database()
{
   static QMutex mutex;
   static bool bInitDone = false;
   if (bInitDone) { return; }
   QMutexLocker locker(& mutex);
   if (bInitDone) { return; }
   bInitDone = true;

   QFile::remove("./user.db");
   qx::QxSqlDatabase::getSingleton()->setDriverName("QSQLITE");
   qx::QxSqlDatabase::getSingleton()->setDatabaseName("user.db");
   qx::QxSqlDatabase::getSingleton()->setHostName("localhost");
   qx::QxSqlDatabase::getSingleton()->setUserName("root");
   qx::QxSqlDatabase::getSingleton()->setPassword("");
   qx::dao::create_table<user>();
}

QSqlError user_manager::insert(user_ptr p)
{
   if (! p) { return QSqlError("cannot insert user : invalid user (null pointer)", "", QSqlError::UnknownError); }
   if (p->first_name.trimmed().isEmpty()) { return QSqlError("cannot insert user : 'first_name' is required", "", QSqlError::UnknownError); }
   if (p->last_name.trimmed().isEmpty()) { return QSqlError("cannot insert user : 'last_name' is required", "", QSqlError::UnknownError); }
   return qx::dao::insert(p);
}

QSqlError user_manager::update(user_ptr p)
{
   if (! p) { return QSqlError("cannot update user : invalid user (null pointer)", "", QSqlError::UnknownError); }
   if (p->id == 0) { return QSqlError("cannot update user : 'id' is required", "", QSqlError::UnknownError); }
   if (p->first_name.trimmed().isEmpty()) { return QSqlError("cannot update user : 'first_name' is required", "", QSqlError::UnknownError); }
   if (p->last_name.trimmed().isEmpty()) { return QSqlError("cannot update user : 'last_name' is required", "", QSqlError::UnknownError); }
   if (! qx::dao::exist(p)) { return QSqlError("cannot update user : user doesn't exist in database", "", QSqlError::UnknownError); }
   return qx::dao::update(p);
}

QSqlError user_manager::remove(user_ptr p)
{
   if (! p) { return QSqlError("cannot remove user : invalid user (null pointer)", "", QSqlError::UnknownError); }
   if (p->id == 0) { return QSqlError("cannot remove user : 'id' is required", "", QSqlError::UnknownError); }
   if (! qx::dao::exist(p)) { return QSqlError("cannot remove user : user doesn't exist in database", "", QSqlError::UnknownError); }
   return qx::dao::delete_by_id(p);
}

QSqlError user_manager::remove_all()
{
   return qx::dao::delete_all<user>();
}

QSqlError user_manager::fetch_by_id(user_ptr p)
{
   if (! p) { return QSqlError("cannot fetch user : invalid user (null pointer)", "", QSqlError::UnknownError); }
   if (p->id == 0) { return QSqlError("cannot fetch user : 'id' is required", "", QSqlError::UnknownError); }
   if (! qx::dao::exist(p)) { return QSqlError("cannot fetch user : user doesn't exist in database", "", QSqlError::UnknownError); }
   return qx::dao::fetch_by_id(p);
}

QSqlError user_manager::fetch_all(list_of_users_ptr lst)
{
   return qx::dao::fetch_all(lst);
}

QSqlError user_manager::get_by_criteria(user_search_ptr criteria, list_of_users_ptr lst)
{
   if (! criteria) { return QSqlError("cannot search users : invalid criteria (null pointer)", "", QSqlError::UnknownError); }
   if (criteria->empty()) { return fetch_all(lst); }

   QString sql = "WHERE ";
   if (! criteria->first_name.isEmpty()) { sql += "user.first_name LIKE :first_name AND "; }
   if (! criteria->last_name.isEmpty()) { sql += "user.last_name LIKE :last_name AND "; }
   if (criteria->birth_date.isValid()) { sql += "user.birth_date = :birth_date AND "; }
   sql = sql.left(sql.count() - 5); // Remove last " AND "

   qx::QxSqlQuery query(sql);
   if (! criteria->first_name.isEmpty()) { query.bind(":first_name", criteria->first_name); }
   if (! criteria->last_name.isEmpty()) { query.bind(":last_name", criteria->last_name); }
   if (criteria->birth_date.isValid()) { query.bind(":birth_date", criteria->birth_date); }

   return qx::dao::fetch_by_query(query, lst);
}

#endif // _QX_SERVICE_MODE_CLIENT
