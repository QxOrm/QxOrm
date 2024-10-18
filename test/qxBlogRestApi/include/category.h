#ifndef _QX_BLOG_CATEGORY_H_
#define _QX_BLOG_CATEGORY_H_

class blog;

class QX_BLOG_DLL_EXPORT category : public qx::IxPersistable
{

   QX_PERSISTABLE_HPP(category)

public:

// -- typedef
   typedef std::shared_ptr<blog> blog_ptr;
   typedef qx::QxCollection<long, blog_ptr> list_blog;

// -- properties
#ifdef _QX_TEST_WITH_MONGODB
   QString     m_id;
#else // _QX_TEST_WITH_MONGODB
   long        m_id;
#endif // _QX_TEST_WITH_MONGODB
   QString     m_name;
   QString     m_desc;
   list_blog   m_blogX;

// -- contructor, virtual destructor
#ifdef _QX_TEST_WITH_MONGODB
   category() : qx::IxPersistable() { ; }
#else // _QX_TEST_WITH_MONGODB
   category() : qx::IxPersistable(), m_id(0) { ; }
#endif // _QX_TEST_WITH_MONGODB
   virtual ~category() { ; }

};

#ifdef _QX_TEST_WITH_MONGODB
QX_REGISTER_PRIMARY_KEY(category, QString)
#endif // _QX_TEST_WITH_MONGODB
QX_REGISTER_HPP_QX_BLOG(category, qx::trait::no_base_class_defined, 0)

typedef QSharedPointer<category> category_ptr;
#ifdef _QX_TEST_WITH_MONGODB
typedef qx::QxCollection<QString, category_ptr> list_category;
#else // _QX_TEST_WITH_MONGODB
typedef qx::QxCollection<long, category_ptr> list_category;
#endif // _QX_TEST_WITH_MONGODB

#endif // _QX_BLOG_CATEGORY_H_
