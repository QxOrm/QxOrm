#include "../include/precompiled.h"

#include "../include/category.h"
#include "../include/blog.h"

#include <QxOrm_Impl.h>

QX_REGISTER_CPP_QX_BLOG(category)

namespace qx {
template <> void register_class(QxClass<category> & t)
{
   t.id(& category::m_id, category::str_composite_key());

   t.data(& category::m_name, "name");
   t.data(& category::m_desc, "description");

   t.relationManyToMany(& category::m_blogX, "list_blog", "category_blog", category::str_composite_key(), blog::str_composite_key());
}}
