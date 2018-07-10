#include "../../include/precompiled.h"

#include "../../include/business_object/user_search.h"

#include <QxOrm_Impl.h>

QX_REGISTER_CPP_QX_SERVICE(user_search)

namespace qx {
template <> void register_class(QxClass<user_search> & t)
{
   t.data(& user_search::first_name, "first_name");
   t.data(& user_search::last_name, "last_name");
   t.data(& user_search::birth_date, "birth_date");
}}
