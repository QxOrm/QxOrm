#ifndef _QX_SERVICE_BO_USER_H_
#define _QX_SERVICE_BO_USER_H_

class QX_SERVICE_DLL_EXPORT user
{
public:
// -- contructor, virtual destructor
   user() : id(0) { ; }
   virtual ~user() { ; }
// -- properties
   long id;
   QString first_name;
   QString last_name;
   QDateTime birth_date;
};

QX_REGISTER_HPP_QX_SERVICE(user, qx::trait::no_base_class_defined, 0)

typedef qx_shared_ptr<user> user_ptr;
typedef qx::QxCollection<long, user_ptr> list_of_users;
typedef qx_shared_ptr<list_of_users> list_of_users_ptr;

#endif // _QX_SERVICE_BO_USER_H_
