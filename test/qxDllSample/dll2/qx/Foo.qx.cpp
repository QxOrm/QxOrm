#include "../include/precompiled.h"

#include "../include/Foo.h"

#include <QxOrm_Impl.h>

QX_REGISTER_CPP_QX_DLL2(Foo)
QX_PERSISTABLE_CPP(Foo)

namespace qx {
template <> void register_class(QxClass<Foo> & t)
{
   IxDataMember * pData = NULL;
   IxSqlRelation * pRelation = NULL;

   pData = t.data(& Foo::m_sName, "name");
   pData = t.data(& Foo::m_sDesc, "desc");
   pData = t.data(& Foo::m_oDateNeutral, "date_neutral");
   pData = t.data(& Foo::m_oTimeNeutral, "time_neutral");
   pData = t.data(& Foo::m_oDateTimeNeutral, "dt_neutral");
   pData = t.data(& Foo::m_optInt, "optional_int");
   pData = t.data(& Foo::m_optString, "optional_string");

   pRelation = t.relationOneToMany(& Foo::m_pBarX, "lstBar", "foo_id");
}}
