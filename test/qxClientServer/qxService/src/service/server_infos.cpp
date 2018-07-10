#include "../../include/precompiled.h"

#include "../../include/service/server_infos.h"

#include <QxOrm_Impl.h>

QX_REGISTER_CPP_QX_SERVICE(server_infos_input)
QX_REGISTER_CPP_QX_SERVICE(server_infos_output)
QX_REGISTER_CPP_QX_SERVICE(server_infos)

QX_SERVICE_IX_PARAMETER_SERIALIZATION_CPP(server_infos_input)
QX_SERVICE_IX_PARAMETER_SERIALIZATION_CPP(server_infos_output)

namespace qx {

template <> void register_class(QxClass<server_infos_input> & t)
{ Q_UNUSED(t); }

template <> void register_class(QxClass<server_infos_output> & t)
{ t.data(& server_infos_output::current_date_time, "current_date_time"); }

template <> void register_class(QxClass<server_infos> & t)
{ t.fct_0<void>(& server_infos::get_current_date_time, "get_current_date_time"); }

} // namespace qx

#ifdef _QX_SERVICE_MODE_CLIENT

void server_infos::get_current_date_time()
{ qx::service::execute_client(this, "get_current_date_time"); }

#else // _QX_SERVICE_MODE_CLIENT

void server_infos::get_current_date_time()
{
   server_infos_output_ptr output = server_infos_output_ptr(new server_infos_output());
   output->current_date_time = QDateTime::currentDateTime();
   setOutputParameter(output);
   setMessageReturn(true);
}

#endif // _QX_SERVICE_MODE_CLIENT
