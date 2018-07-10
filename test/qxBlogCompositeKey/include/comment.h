#ifndef _QX_BLOG_COMMENT_H_
#define _QX_BLOG_COMMENT_H_

class blog;

class QX_BLOG_DLL_EXPORT comment
{

   QX_REGISTER_FRIEND_CLASS(comment)

public:

// -- composite key (multi-column primary key in database)
   typedef boost::tuple<long, QString> type_composite_key;
   static QString str_composite_key() { return "comment_id_0|comment_id_1"; }

// -- typedef
   typedef qx_shared_ptr<blog> blog_ptr;

// -- properties
   type_composite_key   m_id;
   QString              m_text;
   QDateTime            m_dt_create;
   blog_ptr             m_blog;

// -- contructor, virtual destructor
   comment() : m_id(0, "") { ; }
   virtual ~comment() { ; }

// -- methods "get" to composite key
   type_composite_key getId() const    { return m_id; }
   long getId_0() const                { return boost::tuples::get<0>(m_id); }
   QString getId_1() const             { return boost::tuples::get<1>(m_id); }

// -- methods "set" to composite key
   void setId_0(long l)                { boost::tuples::get<0>(m_id) = l; }
   void setId_1(const QString & s)     { boost::tuples::get<1>(m_id) = s; }

};

QX_REGISTER_PRIMARY_KEY(comment, comment::type_composite_key)
QX_REGISTER_HPP_QX_BLOG(comment, qx::trait::no_base_class_defined, 0)

typedef qx_shared_ptr<comment> comment_ptr;
typedef QList<comment_ptr> list_comment;

#endif // _QX_BLOG_COMMENT_H_
