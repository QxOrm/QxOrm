#include "../include/precompiled.h"

#include "../include/author.h"
#include "../include/blog.h"

#include <QxOrm_Impl.h>

QX_REGISTER_CPP_QX_BLOG(author)

namespace qx {
template <> void register_class(QxClass<author> & t)
{
   t.id(& author::m_id, author::str_composite_key());

   t.data(& author::m_name, "name");
   t.data(& author::m_birthdate, "birthdate");
   t.data(& author::m_sex, "sex");

   t.relationOneToMany(& author::m_blogX, blog::str_composite_key(), author::str_composite_key());

   t.fct_0<int>(& author::age, "age");
}}

int author::age() const
{
   if (! m_birthdate.isValid()) { return -1; }
   return (QDate::currentDate().year() - m_birthdate.year());
}
