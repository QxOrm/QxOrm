#ifndef _QX_BLOG_BLOG_H_
#define _QX_BLOG_BLOG_H_

class author;
class comment;
class category;

class QX_BLOG_DLL_EXPORT blog
{

   QX_REGISTER_FRIEND_CLASS(blog)

private:

   struct blog_impl;
   std::unique_ptr<blog_impl> m_pImpl; //!< Private implementation idiom

public:

   blog();
   virtual ~blog();

   blog(const blog & other);
   blog & operator=(const blog & other);

#ifdef Q_COMPILER_RVALUE_REFS
   blog(blog && other) Q_DECL_NOEXCEPT;
   blog & operator=(blog && other) Q_DECL_NOEXCEPT;
#endif // Q_COMPILER_RVALUE_REFS

   long id() const;
   QString text() const;
   QDateTime dateCreation() const;

   void setId(long l);
   void setText(const QString & s);
   void setDateCreation(const QDateTime & d);

   std::shared_ptr<author> & getAuthor();
   QList< std::shared_ptr<comment> > & listOfComments();
   qx::QxCollection<long, QSharedPointer<category> > & listOfCategories();

};

QX_REGISTER_HPP_QX_BLOG(blog, qx::trait::no_base_class_defined, 0)

typedef std::shared_ptr<blog> blog_ptr;
typedef std::vector<blog_ptr> list_blog;

#endif // _QX_BLOG_BLOG_H_
