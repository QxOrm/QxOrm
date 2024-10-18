#include "../include/precompiled.h"

#include "../include/category.h"
#include "../include/blog.h"

#include <QxOrm_Impl.h>

QX_REGISTER_CPP_QX_BLOG(category)
QX_PERSISTABLE_CPP(category)

namespace qx {
template <> void register_class(QxClass<category> & t)
{
   t.id(& category::m_id, "category_id");

   t.data(& category::m_name, "name");
   t.data(& category::m_desc, "description");

#ifdef _QX_TEST_WITH_MONGODB
   t.data(& category::m_blogX, "list_blog");
#else // _QX_TEST_WITH_MONGODB
   t.relationManyToMany(& category::m_blogX, "list_blog", "t_qxee_blog_category", "category_id", "blog_id");
#endif // _QX_TEST_WITH_MONGODB
}}
