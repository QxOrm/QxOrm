#include "../include/precompiled.h"

#include "../include/blog.h"

#include <QxOrm_Impl.h>

QX_REGISTER_CPP_QX_BLOG(blog)

namespace qx {
template <> void register_class(QxClass<blog> & t)
{
   t.id(& blog::m_id, blog::str_composite_key());

   t.data(& blog::m_text, "blog_text");
   t.data(& blog::m_dt_creation, "date_creation");

   t.relationManyToOne(& blog::m_author, author::str_composite_key());
   t.relationOneToMany(& blog::m_commentX, comment::str_composite_key(), blog::str_composite_key());
   t.relationManyToMany(& blog::m_categoryX, "list_category", "category_blog", blog::str_composite_key(), category::str_composite_key());
}}
