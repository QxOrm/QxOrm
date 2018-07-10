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

   t.fct_0<int>(& author::age, "age");
}}

int author::age() const
{
   if (! m_birthdate.isValid()) { return -1; }
   return (QDate::currentDate().year() - m_birthdate.year());
}

QString author::getauthor_id() const { return m_id; }

QString author::getname() const { return m_name; }

QDate author::getbirthdate() const { return m_birthdate; }

author::enum_sex author::getsex() const { return m_sex; }

author::type_list_of_blog author::getlist_of_blog() const { return m_blogX; }

author::type_list_of_blog & author::list_of_blog() { return m_blogX; }

const author::type_list_of_blog & author::list_of_blog() const { return m_blogX; }

void author::setauthor_id(const QString & val) { m_id = val; }

void author::setname(const QString & val) { m_name = val; }

void author::setbirthdate(const QDate & val) { m_birthdate = val; }

void author::setsex(const author::enum_sex & val) { m_sex = val; }

void author::setlist_of_blog(const author::type_list_of_blog & val) { m_blogX = val; }
