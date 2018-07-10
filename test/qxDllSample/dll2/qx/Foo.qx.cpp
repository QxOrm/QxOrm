#include "../include/precompiled.h"

#include "../include/Foo.h"

#include <QxMemLeak.h>

QX_REGISTER_CPP_QX_DLL2(Foo)

namespace qx {
template <> void register_class(QxClass<Foo> & t)
{
   IxDataMember * pData = NULL;
   IxSqlRelation * pRelation = NULL;

   pData = t.data(& Foo::m_sName, "name");
   pData = t.data(& Foo::m_sDesc, "desc");

   pRelation = t.relationOneToMany(& Foo::m_pBarX, "lstBar", "foo_id");
}}
