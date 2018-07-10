#ifndef _QX_SERVICE_SERVER_INFOS_H_
#define _QX_SERVICE_SERVER_INFOS_H_

/* -- Service Input Parameters -- */

class QX_SERVICE_DLL_EXPORT server_infos_input : public qx::service::IxParameter
{ QX_SERVICE_IX_PARAMETER_SERIALIZATION_HPP(server_infos_input); };

QX_REGISTER_HPP_QX_SERVICE(server_infos_input, qx::service::IxParameter, 0)
typedef qx_shared_ptr<server_infos_input> server_infos_input_ptr;

/* -- Service Output Parameters -- */

class QX_SERVICE_DLL_EXPORT server_infos_output : public qx::service::IxParameter
{ public: QDateTime current_date_time; QX_SERVICE_IX_PARAMETER_SERIALIZATION_HPP(server_infos_output); };

QX_REGISTER_HPP_QX_SERVICE(server_infos_output, qx::service::IxParameter, 0)
typedef qx_shared_ptr<server_infos_output> server_infos_output_ptr;

/* -- Service Definition -- */

typedef qx::service::QxService<server_infos_input, server_infos_output> server_infos_base_class;
class QX_SERVICE_DLL_EXPORT server_infos : public server_infos_base_class
{
public:
   server_infos() : server_infos_base_class("server_infos") { ; }
   virtual ~server_infos() { ; }
   void get_current_date_time();
};

QX_REGISTER_HPP_QX_SERVICE(server_infos, qx::service::IxService, 0)
typedef qx_shared_ptr<server_infos> server_infos_ptr;

#endif // _QX_SERVICE_SERVER_INFOS_H_
