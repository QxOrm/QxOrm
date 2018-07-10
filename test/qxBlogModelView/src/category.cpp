#include "../include/precompiled.h"

#include "../include/category.h"
#include "../include/blog.h"

#include <QxOrm_Impl.h>

QX_REGISTER_CPP_QX_BLOG(category)

namespace qx {
template <> void register_class(QxClass<category> & t)
{
   t.id(& category::m_id, "category_id");

   t.data(& category::m_name, "name");
   t.data(& category::m_desc, "description");

   t.relationManyToMany(& category::m_blogX, "list_blog", "category_blog", "category_id", "blog_id");
}}

long category::getcategory_id() const { return m_id; }

QString category::getname() const { return m_name; }

QString category::getdescription() const { return m_desc; }

category::type_list_of_blog category::getlist_of_blog() const { return m_blogX; }

category::type_list_of_blog & category::list_of_blog() { return m_blogX; }

const category::type_list_of_blog & category::list_of_blog() const { return m_blogX; }

void category::setcategory_id(const long & val) { m_id = val; }

void category::setname(const QString & val) { m_name = val; }

void category::setdescription(const QString & val) { m_desc = val; }

void category::setlist_of_blog(const category::type_list_of_blog & val) { m_blogX = val; }
