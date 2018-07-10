#ifndef _QX_BLOG_BLOG_H_
#define _QX_BLOG_BLOG_H_

#include "author.h"
#include "comment.h"
#include "category.h"

class QX_BLOG_DLL_EXPORT blog
{
public:

   typedef qx_shared_ptr<author> type_author;
   typedef QList<comment_ptr> type_list_of_comment;
   typedef qx::QxCollection<long, category_ptr> type_list_of_category;

// -- properties
   long           m_id;
   QString        m_title;
   QString        m_text;
   QDateTime      m_dt_creation;
   author_ptr     m_author;
   list_comment   m_commentX;
   list_category  m_categoryX;
// -- contructor, virtual destructor
   blog() : m_id(0) { ; }
   virtual ~blog() { ; }

   long getblog_id() const;
   QString gettitle() const;
   QString gettext() const;
   type_author getauthor() const;
   type_list_of_comment getlist_of_comment() const;
   type_list_of_comment & list_of_comment();
   const type_list_of_comment & list_of_comment() const;
   type_list_of_category getlist_of_category() const;
   type_list_of_category & list_of_category();
   const type_list_of_category & list_of_category() const;

   void setblog_id(const long & val);
   void settitle(const QString & val);
   void settext(const QString & val);
   void setauthor(const type_author & val);
   void setlist_of_comment(const type_list_of_comment & val);
   void setlist_of_category(const type_list_of_category & val);

};

QX_REGISTER_HPP_QX_BLOG(blog, qx::trait::no_base_class_defined, 0)

typedef qx_shared_ptr<blog> blog_ptr;
typedef std::vector<blog_ptr> list_blog;

#endif // _QX_BLOG_BLOG_H_
