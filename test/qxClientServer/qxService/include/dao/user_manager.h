#ifndef _QX_SERVICE_MODE_CLIENT
#ifndef _QX_SERVICE_USER_MANAGER_H_
#define _QX_SERVICE_USER_MANAGER_H_

#include "../../include/business_object/user.h"
#include "../../include/business_object/user_search.h"

class QX_SERVICE_DLL_EXPORT user_manager
{
public:
   user_manager() { user_manager::init_database(); }
   ~user_manager() { ; }
   QSqlError insert(user_ptr p);
   QSqlError update(user_ptr p);
   QSqlError remove(user_ptr p);
   QSqlError remove_all();
   QSqlError fetch_by_id(user_ptr p);
   QSqlError fetch_all(list_of_users_ptr lst);
   QSqlError get_by_criteria(user_search_ptr criteria, list_of_users_ptr lst);
private:
   static void init_database();
};

#endif // _QX_SERVICE_USER_MANAGER_H_
#endif // _QX_SERVICE_MODE_CLIENT
