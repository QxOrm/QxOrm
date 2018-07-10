#include "../include/precompiled.h"

#include "../include/comment.h"
#include "../include/blog.h"

#include <QxOrm_Impl.h>

QX_REGISTER_CPP_QX_BLOG(comment)

namespace qx {
template <> void register_class(QxClass<comment> & t)
{
   t.id(& comment::m_id, "comment_id");

   t.data(& comment::m_title, "comment_title");
   t.data(& comment::m_text, "comment_text");
   t.data(& comment::m_dt_create, "date_creation");

   t.relationManyToOne(& comment::m_blog, "blog_id");
}}

long comment::getcomment_id() const { return m_id; }

QString comment::gettitle() const { return m_title; }

QString comment::gettext() const { return m_text; }

comment::type_blog_id comment::getblog_id() const { return m_blog; }

void comment::setcomment_id(const long & val) { m_id = val; }

void comment::settitle(const QString & val) { m_title = val; }

void comment::settext(const QString & val) { m_text = val; }

void comment::setblog_id(const comment::type_blog_id & val) { m_blog = val; }
