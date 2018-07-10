#ifndef _QX_SERVICE_USER_SERVICE_H_
#define _QX_SERVICE_USER_SERVICE_H_

#include "../../include/business_object/user.h"
#include "../../include/business_object/user_search.h"

/* -- Service Input Parameters -- */

class QX_SERVICE_DLL_EXPORT user_service_input : public qx::service::IxParameter
{
   QX_SERVICE_IX_PARAMETER_SERIALIZATION_HPP(user_service_input);
public:
   user_service_input() : id(0) { ; }
   virtual ~user_service_input() { ; }
   long id;
   user_ptr user;
   user_search_ptr criteria;
};

QX_REGISTER_HPP_QX_SERVICE(user_service_input, qx::service::IxParameter, 0)
typedef qx_shared_ptr<user_service_input> user_service_input_ptr;

/* -- Service Output Parameters -- */

class QX_SERVICE_DLL_EXPORT user_service_output : public qx::service::IxParameter
{
   QX_SERVICE_IX_PARAMETER_SERIALIZATION_HPP(user_service_output);
public:
   user_ptr user;
   list_of_users_ptr list_of_users;
};

QX_REGISTER_HPP_QX_SERVICE(user_service_output, qx::service::IxParameter, 0)
typedef qx_shared_ptr<user_service_output> user_service_output_ptr;

/* -- Service Definition -- */

typedef qx::service::QxService<user_service_input, user_service_output> user_service_base_class;
class QX_SERVICE_DLL_EXPORT user_service : public user_service_base_class
{
public:
   user_service() : user_service_base_class("user_service") { ; }
   virtual ~user_service() { ; }
   void insert();
   void update();
   void remove();
   void remove_all();
   void fetch_by_id();
   void fetch_all();
   void get_by_criteria();
};

QX_REGISTER_HPP_QX_SERVICE(user_service, qx::service::IxService, 0)
typedef qx_shared_ptr<user_service> user_service_ptr;

#endif // _QX_SERVICE_USER_SERVICE_H_
