#include "../include/precompiled.h"

#include "../include/Bar.h"
#include "../include/Foo.h"

#include <QxOrm_Impl.h>

void Bar::setFoo(long l)
{
   m_pFoo.reset(new Foo());
   m_pFoo->setId(l);
}
