#include "../../include/precompiled.h"

#include "../../include/service/user_service.h"

#include "../../include/dao/user_manager.h"

#include <QxOrm_Impl.h>

QX_REGISTER_CPP_QX_SERVICE(user_service_input)
QX_REGISTER_CPP_QX_SERVICE(user_service_output)
QX_REGISTER_CPP_QX_SERVICE(user_service)

QX_SERVICE_IX_PARAMETER_SERIALIZATION_CPP(user_service_input)
QX_SERVICE_IX_PARAMETER_SERIALIZATION_CPP(user_service_output)

namespace qx {

template <> void register_class(QxClass<user_service_input> & t)
{
   t.data(& user_service_input::id, "id");
   t.data(& user_service_input::user, "user");
   t.data(& user_service_input::criteria, "criteria");
}

template <> void register_class(QxClass<user_service_output> & t)
{
   t.data(& user_service_output::user, "user");
   t.data(& user_service_output::list_of_users, "list_of_users");
}

template <> void register_class(QxClass<user_service> & t)
{
   t.fct_0<void>(& user_service::insert, "insert");
   t.fct_0<void>(& user_service::update, "update");
   t.fct_0<void>(& user_service::remove, "remove");
   t.fct_0<void>(& user_service::remove_all, "remove_all");
   t.fct_0<void>(& user_service::fetch_by_id, "fetch_by_id");
   t.fct_0<void>(& user_service::fetch_all, "fetch_all");
   t.fct_0<void>(& user_service::get_by_criteria, "get_by_criteria");
}

} // namespace qx

#ifdef _QX_SERVICE_MODE_CLIENT

void user_service::insert()            { qx::service::execute_client(this, "insert"); }
void user_service::update()            { qx::service::execute_client(this, "update"); }
void user_service::remove()            { qx::service::execute_client(this, "remove"); }
void user_service::remove_all()        { qx::service::execute_client(this, "remove_all"); }
void user_service::fetch_by_id()       { qx::service::execute_client(this, "fetch_by_id"); }
void user_service::fetch_all()         { qx::service::execute_client(this, "fetch_all"); }
void user_service::get_by_criteria()   { qx::service::execute_client(this, "get_by_criteria"); }

#else // _QX_SERVICE_MODE_CLIENT

void user_service::insert()
{
   user_service_input_ptr input = getInputParameter();
   if (! input) { setMessageReturn(0, "invalid input parameter to call service 'user_service::insert()'"); return; }
   QSqlError err = user_manager().insert(input->user);
   if (err.isValid()) { setMessageReturn(0, err.text()); return; }
   user_service_output_ptr output = user_service_output_ptr(new user_service_output());
   output->user = input->user;
   setOutputParameter(output);
   setMessageReturn(true);
}

void user_service::update()
{
   user_service_input_ptr input = getInputParameter();
   if (! input) { setMessageReturn(0, "invalid input parameter to call service 'user_service::update()'"); return; }
   QSqlError err = user_manager().update(input->user);
   if (err.isValid()) { setMessageReturn(0, err.text()); }
   else { setMessageReturn(true); }
}

void user_service::remove()
{
   user_service_input_ptr input = getInputParameter();
   if (! input) { setMessageReturn(0, "invalid input parameter to call service 'user_service::remove()'"); return; }
   user_ptr user_tmp = user_ptr(new user());
   user_tmp->id = input->id;
   QSqlError err = user_manager().remove(user_tmp);
   if (err.isValid()) { setMessageReturn(0, err.text()); }
   else { setMessageReturn(true); }
}

void user_service::remove_all()
{
   QSqlError err = user_manager().remove_all();
   if (err.isValid()) { setMessageReturn(0, err.text()); }
   else { setMessageReturn(true); }
}

void user_service::fetch_by_id()
{
   user_service_input_ptr input = getInputParameter();
   if (! input) { setMessageReturn(0, "invalid input parameter to call service 'user_service::fetch_by_id()'"); return; }
   user_ptr user_output = user_ptr(new user());
   user_output->id = input->id;
   QSqlError err = user_manager().fetch_by_id(user_output);
   if (err.isValid()) { setMessageReturn(0, err.text()); return; }
   user_service_output_ptr output = user_service_output_ptr(new user_service_output());
   output->user = user_output;
   setOutputParameter(output);
   setMessageReturn(true);
}

void user_service::fetch_all()
{
   list_of_users_ptr list_of_users_output = list_of_users_ptr(new list_of_users());
   QSqlError err = user_manager().fetch_all(list_of_users_output);
   if (err.isValid()) { setMessageReturn(0, err.text()); return; }
   user_service_output_ptr output = user_service_output_ptr(new user_service_output());
   output->list_of_users = list_of_users_output;
   setOutputParameter(output);
   setMessageReturn(true);
}

void user_service::get_by_criteria()
{
   user_service_input_ptr input = getInputParameter();
   if (! input) { setMessageReturn(0, "invalid input parameter to call service 'user_service::get_by_criteria()'"); return; }
   list_of_users_ptr list_of_users_output = list_of_users_ptr(new list_of_users());
   QSqlError err = user_manager().get_by_criteria(input->criteria, list_of_users_output);
   if (err.isValid()) { setMessageReturn(0, err.text()); return; }
   user_service_output_ptr output = user_service_output_ptr(new user_service_output());
   output->list_of_users = list_of_users_output;
   setOutputParameter(output);
   setMessageReturn(true);
}

#endif // _QX_SERVICE_MODE_CLIENT
