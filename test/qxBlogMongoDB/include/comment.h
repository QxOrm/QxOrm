#ifndef _QX_BLOG_COMMENT_H_
#define _QX_BLOG_COMMENT_H_

class blog;

class QX_BLOG_DLL_EXPORT comment
{
public:
// -- typedef
   typedef std::shared_ptr<blog> blog_ptr;
// -- properties
   QString     m_id;
   QString     m_text;
   QDateTime   m_dt_create;
   blog_ptr    m_blog;
// -- contructor, virtual destructor
   comment() { ; }
   virtual ~comment() { ; }
};

QX_REGISTER_PRIMARY_KEY(comment, QString)
QX_REGISTER_HPP_QX_BLOG(comment, qx::trait::no_base_class_defined, 0)

typedef std::shared_ptr<comment> comment_ptr;
typedef QList<comment_ptr> list_comment;

#endif // _QX_BLOG_COMMENT_H_
