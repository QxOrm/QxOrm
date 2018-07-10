#include "../include/precompiled.h"

#include "../include/comment.h"
#include "../include/blog.h"

#include <QxOrm_Impl.h>

QX_REGISTER_CPP_QX_BLOG(comment)

namespace qx {
template <> void register_class(QxClass<comment> & t)
{
   t.id(& comment::m_id, "comment_id");

   t.data(& comment::m_text, "comment_text");
   t.data(& comment::m_dt_create, "date_creation");

   t.relationManyToOne(& comment::m_blog, "blog_id");
}}
