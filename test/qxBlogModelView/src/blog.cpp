#include "../include/precompiled.h"

#include "../include/blog.h"

#include <QxMemLeak.h>

QX_REGISTER_CPP_QX_BLOG(blog)

namespace qx {
template <> void register_class(QxClass<blog> & t)
{
   t.id(& blog::m_id, "blog_id");

   t.data(& blog::m_text, "blog_text");
   t.data(& blog::m_dt_creation, "date_creation");

   t.relationManyToOne(& blog::m_author, "author_id");
   t.relationOneToMany(& blog::m_commentX, "list_comment", "blog_id");
   t.relationManyToMany(& blog::m_categoryX, "list_category", "category_blog", "blog_id", "category_id");
}}
