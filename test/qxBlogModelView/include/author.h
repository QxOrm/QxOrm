#ifndef _QX_BLOG_AUTHOR_H_
#define _QX_BLOG_AUTHOR_H_

class blog;

class QX_BLOG_DLL_EXPORT author
{
public:
// -- typedef
   typedef qx_shared_ptr<blog> blog_ptr;
   typedef std::vector<blog_ptr> list_blog;
// -- enum
   enum enum_sex { male, female, unknown };
// -- properties
   QString     m_id;
   QString     m_name;
   QDate       m_birthdate;
   enum_sex    m_sex;
   list_blog   m_blogX;
// -- contructor, virtual destructor
   author() : m_id("0"), m_sex(unknown) { ; }
   virtual ~author() { ; }
// -- methods
   int age() const;
};

QX_REGISTER_PRIMARY_KEY(author, QString)
QX_REGISTER_HPP_QX_BLOG(author, qx::trait::no_base_class_defined, 0)

typedef qx_shared_ptr<author> author_ptr;
typedef qx::QxCollection<QString, author_ptr> list_author;

#endif // _QX_BLOG_AUTHOR_H_
