#ifndef _QX_BLOG_CATEGORY_H_
#define _QX_BLOG_CATEGORY_H_

class blog;

class QX_BLOG_DLL_EXPORT category
{

   QX_REGISTER_FRIEND_CLASS(category)

private:

   struct category_impl;
   std::unique_ptr<category_impl> m_pImpl; //!< Private implementation idiom

public:

   category();
   virtual ~category();

   category(const category & other);
   category & operator=(const category & other);

#ifdef Q_COMPILER_RVALUE_REFS
   category(category && other) Q_DECL_NOEXCEPT;
   category & operator=(category && other) Q_DECL_NOEXCEPT;
#endif // Q_COMPILER_RVALUE_REFS

   long id() const;
   QString name() const;
   QString desc() const;

   void setId(long l);
   void setName(const QString & s);
   void setDesc(const QString & s);

   qx::QxCollection<long, std::shared_ptr<blog> > & listOfBlogs();

};

QX_REGISTER_HPP_QX_BLOG(category, qx::trait::no_base_class_defined, 0)

typedef QSharedPointer<category> category_ptr;
typedef qx::QxCollection<long, category_ptr> list_category;

#endif // _QX_BLOG_CATEGORY_H_
