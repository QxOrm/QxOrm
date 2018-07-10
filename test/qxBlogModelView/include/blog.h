#ifndef _QX_BLOG_BLOG_H_
#define _QX_BLOG_BLOG_H_

#include "author.h"
#include "comment.h"
#include "category.h"

class QX_BLOG_DLL_EXPORT blog
{
public:
// -- properties
   long           m_id;
   QString        m_text;
   QDateTime      m_dt_creation;
   author_ptr     m_author;
   list_comment   m_commentX;
   list_category  m_categoryX;
// -- contructor, virtual destructor
   blog() : m_id(0) { ; }
   virtual ~blog() { ; }
};

QX_REGISTER_HPP_QX_BLOG(blog, qx::trait::no_base_class_defined, 0)

typedef qx_shared_ptr<blog> blog_ptr;
typedef std::vector<blog_ptr> list_blog;

#endif // _QX_BLOG_BLOG_H_
