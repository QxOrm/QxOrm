#ifndef _QX_BLOG_BLOG_H_
#define _QX_BLOG_BLOG_H_

#include "author.h"
#include "comment.h"
#include "category.h"

class QX_BLOG_DLL_EXPORT blog
{

   QX_REGISTER_FRIEND_CLASS(blog)

public:

// -- composite key (multi-column primary key in database)
   typedef QPair<long, QString> type_composite_key;
   static QString str_composite_key() { return "blog_id_0|blog_id_1"; }

// -- properties
   type_composite_key   m_id;
   QString              m_text;
   QDateTime            m_dt_creation;
   author_ptr           m_author;
   list_comment         m_commentX;
   list_category        m_categoryX;

// -- contructor, virtual destructor
   blog() : m_id(0, "") { ; }
   virtual ~blog() { ; }

// -- methods "get" to composite key
   type_composite_key getId() const    { return m_id; }
   long getId_0() const                { return m_id.first; }
   QString getId_1() const             { return m_id.second; }

// -- methods "set" to composite key
   void setId_0(long l)                { m_id.first = l; }
   void setId_1(const QString & s)     { m_id.second = s; }

};

QX_REGISTER_PRIMARY_KEY(blog, blog::type_composite_key)
QX_REGISTER_HPP_QX_BLOG(blog, qx::trait::no_base_class_defined, 0)

typedef std::shared_ptr<blog> blog_ptr;
typedef std::vector<blog_ptr> list_blog;

#endif // _QX_BLOG_BLOG_H_
