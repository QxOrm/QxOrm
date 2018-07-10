#include "../../include/precompiled.h"

#include "../../include/business_object/user.h"

#include <QxOrm_Impl.h>

QX_REGISTER_CPP_QX_SERVICE(user)

namespace qx {
template <> void register_class(QxClass<user> & t)
{
   t.id(& user::id, "id");

   t.data(& user::first_name, "first_name");
   t.data(& user::last_name, "last_name");
   t.data(& user::birth_date, "birth_date");
}}
