#include "../include/precompiled.h"

#include "../include/blog.h"

#include <QxOrm_Impl.h>

QX_REGISTER_CPP_QX_BLOG(blog)
QX_PERSISTABLE_CPP(blog)

namespace qx {
template <> void register_class(QxClass<blog> & t)
{
   t.id(& blog::m_id, "blog_id");

   t.data(& blog::m_text, "blog_text");
   t.data(& blog::m_dt_creation, "date_creation");

   t.relationManyToOne(& blog::m_author, "author_id");
   t.relationOneToMany(& blog::m_commentX, "list_comment", "blog_id");
   t.relationManyToMany(& blog::m_categoryX, "list_category", "category_blog", "blog_id", "category_id");

#ifndef _QX_NO_JSON
   t.fctStatic_1<QJsonValue, const QJsonValue &>(& blog::helloWorld, "helloWorld");
#endif // _QX_NO_JSON

   QxValidatorX<blog> * pAllValidator = t.getAllValidator();
   pAllValidator->add_CustomValidator(std::mem_fn(& blog::isValid)); // using std::mem_fn() here is just a workaround for an issue with some versions of MSVC, it is not required with a full compliant C++11 compiler (http://stackoverflow.com/questions/23778883/vs2013-stdfunction-with-member-function)
}}

#ifndef _QX_NO_JSON
QJsonValue blog::helloWorld(const QJsonValue & request)
{
   QJsonObject response;
   response.insert("request", request);
   response.insert("response", QString("Hello World !"));
   return response;
}
#endif // _QX_NO_JSON

void blog::isValid(qx::QxInvalidValueX & invalidValues)
{
   if (m_text.isEmpty()) { invalidValues.insert("'blog_text' property cannot be empty"); }
}
