#include "../include/precompiled.h"

#include "../include/BaseClassTrigger.h"

#include <QxOrm_Impl.h>

QX_REGISTER_CPP_QX_DLL2(BaseClassTrigger)

namespace qx {
template <> void register_class(QxClass<BaseClassTrigger> & t)
{
   IxDataMember * pData = NULL;

   pData = t.id(& BaseClassTrigger::m_id, "id");

   pData = t.data(& BaseClassTrigger::m_dateCreation, "date_creation");
   pData = t.data(& BaseClassTrigger::m_dateModification, "date_modification");
   pData = t.data(& BaseClassTrigger::m_userCreation, "user_creation");
   pData = t.data(& BaseClassTrigger::m_userModification, "user_modification");
}}
