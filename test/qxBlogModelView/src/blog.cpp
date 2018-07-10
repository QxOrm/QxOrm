#include "../include/precompiled.h"

#include "../include/blog.h"

#include <QxOrm_Impl.h>

QX_REGISTER_CPP_QX_BLOG(blog)

namespace qx {
template <> void register_class(QxClass<blog> & t)
{
   t.id(& blog::m_id, "blog_id");

   t.data(& blog::m_title, "blog_title");
   t.data(& blog::m_text, "blog_text");
   t.data(& blog::m_dt_creation, "date_creation");

   t.relationManyToOne(& blog::m_author, "author_id");
   t.relationOneToMany(& blog::m_commentX, "list_comment", "blog_id");
   t.relationManyToMany(& blog::m_categoryX, "list_category", "category_blog", "blog_id", "category_id");
}}

long blog::getblog_id() const { return m_id; }

QString blog::gettitle() const { return m_title; }

QString blog::gettext() const { return m_text; }

blog::type_author blog::getauthor() const { return m_author; }

blog::type_list_of_comment blog::getlist_of_comment() const { return m_commentX; }

blog::type_list_of_comment & blog::list_of_comment() { return m_commentX; }

const blog::type_list_of_comment & blog::list_of_comment() const { return m_commentX; }

blog::type_list_of_category blog::getlist_of_category() const { return m_categoryX; }

blog::type_list_of_category & blog::list_of_category() { return m_categoryX; }

const blog::type_list_of_category & blog::list_of_category() const { return m_categoryX; }

void blog::setblog_id(const long & val) { m_id = val; }

void blog::settitle(const QString & val) { m_title = val; }

void blog::settext(const QString & val) { m_text = val; }

void blog::setauthor(const blog::type_author & val) { m_author = val; }

void blog::setlist_of_comment(const blog::type_list_of_comment & val) { m_commentX = val; }

void blog::setlist_of_category(const blog::type_list_of_category & val) { m_categoryX = val; }
