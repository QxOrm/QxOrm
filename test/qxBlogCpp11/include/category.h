#ifndef _QX_BLOG_CATEGORY_H_
#define _QX_BLOG_CATEGORY_H_

class blog;

class QX_BLOG_DLL_EXPORT category
{

   QX_REGISTER_FRIEND_CLASS(category)

public:

// -- composite key (multi-column primary key in database)
   typedef QX_TUPLE<QString, long, QString, long> type_composite_key;
   static QString str_composite_key() { return "category_id_0|category_id_1|category_id_2|category_id_3"; }

// -- typedef
   typedef std::shared_ptr<blog> blog_ptr;
   typedef qx::QxCollection<long, blog_ptr> list_blog;

// -- properties
   type_composite_key   m_id;
   QString              m_name;
   QString              m_desc;
   list_blog            m_blogX;

// -- contructor, virtual destructor
   category() : m_id("", 0, "", 0) { ; }
   virtual ~category() { ; }

// -- methods "get" to composite key
   type_composite_key getId() const    { return m_id; }
   QString getId_0() const             { return QX_TUPLE_GET<0>(m_id); }
   long getId_1() const                { return QX_TUPLE_GET<1>(m_id); }
   QString getId_2() const             { return QX_TUPLE_GET<2>(m_id); }
   long getId_3() const                { return QX_TUPLE_GET<3>(m_id); }

// -- methods "set" to composite key
   void setId_0(const QString & s)     { QX_TUPLE_GET<0>(m_id) = s; }
   void setId_1(long l)                { QX_TUPLE_GET<1>(m_id) = l; }
   void setId_2(const QString & s)     { QX_TUPLE_GET<2>(m_id) = s; }
   void setId_3(long l)                { QX_TUPLE_GET<3>(m_id) = l; }

};

QX_REGISTER_PRIMARY_KEY(category, category::type_composite_key)
QX_REGISTER_HPP_QX_BLOG(category, qx::trait::no_base_class_defined, 0)

typedef QSharedPointer<category> category_ptr;
typedef qx::QxCollection<category::type_composite_key, category_ptr> list_category;

#endif // _QX_BLOG_CATEGORY_H_
