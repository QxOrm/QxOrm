#ifndef _QX_BLOG_COMMENT_H_
#define _QX_BLOG_COMMENT_H_

class blog;

class QX_BLOG_DLL_EXPORT comment
{
public:
// -- typedef
   typedef qx_shared_ptr<blog> blog_ptr;
   typedef qx_shared_ptr<blog> type_blog_id;
// -- properties
   long        m_id;
   QString     m_title;
   QString     m_text;
   QDateTime   m_dt_create;
   blog_ptr    m_blog;
// -- contructor, virtual destructor
   comment() : m_id(0) { ; }
   virtual ~comment() { ; }

   long getcomment_id() const;
   QString gettitle() const;
   QString gettext() const;
   type_blog_id getblog_id() const;

   void setcomment_id(const long & val);
   void settitle(const QString & val);
   void settext(const QString & val);
   void setblog_id(const type_blog_id & val);

};

QX_REGISTER_HPP_QX_BLOG(comment, qx::trait::no_base_class_defined, 0)

typedef qx_shared_ptr<comment> comment_ptr;
typedef QList<comment_ptr> list_comment;

#endif // _QX_BLOG_COMMENT_H_
