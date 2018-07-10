#ifndef _QX_SERVICE_BO_USER_SEARCH_H_
#define _QX_SERVICE_BO_USER_SEARCH_H_

class QX_SERVICE_DLL_EXPORT user_search
{
public:
// -- contructor, virtual destructor
   user_search() { ; }
   virtual ~user_search() { ; }
// -- properties
   QString first_name;
   QString last_name;
   QDateTime birth_date;
// -- methods
   bool empty() const
   { return (first_name.isEmpty() && last_name.isEmpty() && ! birth_date.isValid()); }
};

QX_REGISTER_HPP_QX_SERVICE(user_search, qx::trait::no_base_class_defined, 0)

typedef qx_shared_ptr<user_search> user_search_ptr;

#endif // _QX_SERVICE_BO_USER_SEARCH_H_
