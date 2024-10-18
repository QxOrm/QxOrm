#ifndef _QX_BLOG_BLOG_H_
#define _QX_BLOG_BLOG_H_

#include "author.h"
#include "comment.h"
#include "category.h"

class QX_BLOG_DLL_EXPORT blog : public qx::IxPersistable
{

   QX_PERSISTABLE_HPP(blog)
   QX_REGISTER_FRIEND_CLASS(blog)

public:

// -- properties
#ifdef _QX_TEST_WITH_MONGODB
   QString        m_id;
#else // _QX_TEST_WITH_MONGODB
   long           m_id;
#endif // _QX_TEST_WITH_MONGODB
   QString        m_text;
   QDateTime      m_dt_creation;
   author_ptr     m_author;
   list_comment   m_commentX;
   list_category  m_categoryX;

// -- contructor, virtual destructor
#ifdef _QX_TEST_WITH_MONGODB
   blog() : qx::IxPersistable() { ; }
#else // _QX_TEST_WITH_MONGODB
   blog() : qx::IxPersistable(), m_id(0) { ; }
#endif // _QX_TEST_WITH_MONGODB
   virtual ~blog() { ; }

#ifndef _QX_NO_JSON
// -- function callable by introspection and REST API
   static QJsonValue helloWorld(const QJsonValue & request);
#endif // _QX_NO_JSON

private:

// -- function to validate a blog instance
   void isValid(qx::QxInvalidValueX & invalidValues);

};

#ifdef _QX_TEST_WITH_MONGODB
QX_REGISTER_PRIMARY_KEY(blog, QString)
#endif // _QX_TEST_WITH_MONGODB
QX_REGISTER_HPP_QX_BLOG(blog, qx::trait::no_base_class_defined, 0)

typedef std::shared_ptr<blog> blog_ptr;
typedef std::vector<blog_ptr> list_blog;

#endif // _QX_BLOG_BLOG_H_
