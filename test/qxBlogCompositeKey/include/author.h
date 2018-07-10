#ifndef _QX_BLOG_AUTHOR_H_
#define _QX_BLOG_AUTHOR_H_

class blog;

class QX_BLOG_DLL_EXPORT author
{

   QX_REGISTER_FRIEND_CLASS(author)

public:

// -- composite key (multi-column primary key in database)
   typedef boost::tuple<QString, long, QString> type_composite_key;
   static QString str_composite_key() { return "author_id_0|author_id_1|author_id_2"; }

// -- typedef
   typedef qx_shared_ptr<blog> blog_ptr;
   typedef std::vector<blog_ptr> list_blog;

// -- enum
   enum enum_sex { male, female, unknown };

// -- properties
   type_composite_key   m_id;
   QString              m_name;
   QDate                m_birthdate;
   enum_sex             m_sex;
   list_blog            m_blogX;

// -- contructor, virtual destructor
   author() : m_id("", 0, ""), m_sex(unknown) { ; }
   virtual ~author() { ; }

// -- methods
   int age() const;

// -- methods "get" to composite key
   type_composite_key getId() const    { return m_id; }
   QString getId_0() const             { return boost::tuples::get<0>(m_id); }
   long getId_1() const                { return boost::tuples::get<1>(m_id); }
   QString getId_2() const             { return boost::tuples::get<2>(m_id); }

// -- methods "set" to composite key
   void setId_0(const QString & s)     { boost::tuples::get<0>(m_id) = s; }
   void setId_1(long l)                { boost::tuples::get<1>(m_id) = l; }
   void setId_2(const QString & s)     { boost::tuples::get<2>(m_id) = s; }

};

QX_REGISTER_PRIMARY_KEY(author, author::type_composite_key)
QX_REGISTER_HPP_QX_BLOG(author, qx::trait::no_base_class_defined, 0)

typedef qx_shared_ptr<author> author_ptr;
typedef qx::QxCollection<author::type_composite_key, author_ptr> list_author;

#endif // _QX_BLOG_AUTHOR_H_
