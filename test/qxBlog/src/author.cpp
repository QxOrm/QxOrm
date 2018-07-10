#include "../include/precompiled.h"

#include "../include/author.h"
#include "../include/blog.h"

#include <QxOrm_Impl.h>

QX_REGISTER_CPP_QX_BLOG(author)

namespace qx {
template <> void register_class(QxClass<author> & t)
{
   t.id(& author::m_id, "author_id");

   t.data(& author::m_name, "name");
   t.data(& author::m_birthdate, "birthdate");
   t.data(& author::m_sex, "sex");

   t.relationOneToMany(& author::m_blogX, "list_blog", "author_id");

   t.fct_0<int>(std::mem_fn(& author::age), "age"); // using std::mem_fn() here is just a workaround for an issue with some versions of MSVC, it is not required with a full compliant C++11 compiler (http://stackoverflow.com/questions/23778883/vs2013-stdfunction-with-member-function)
}}

int author::age() const
{
   if (! m_birthdate.isValid()) { return -1; }
   return (QDate::currentDate().year() - m_birthdate.year());
}
