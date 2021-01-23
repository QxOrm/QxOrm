#ifndef _QX_BLOG_AUTHOR_H_
#define _QX_BLOG_AUTHOR_H_

class QX_BLOG_DLL_EXPORT author
{

   QX_REGISTER_FRIEND_CLASS(author)

private:

   struct author_impl;
   std::unique_ptr<author_impl> m_pImpl; //!< Private implementation idiom

public:

   enum enum_sex { male, female, unknown };

   author();
   virtual ~author();

   author(const author & other);
   author & operator=(const author & other);

#ifdef Q_COMPILER_RVALUE_REFS
   author(author && other) Q_DECL_NOEXCEPT;
   author & operator=(author && other) Q_DECL_NOEXCEPT;
#endif // Q_COMPILER_RVALUE_REFS

   int age() const;
   QString id() const;
   QString name() const;
   QDate birthdate() const;
   enum_sex sex() const;

   void setId(const QString & s);
   void setName(const QString & s);
   void setBirthdate(const QDate & d);
   void setSex(enum_sex e);

};

QX_REGISTER_PRIMARY_KEY(author, QString)
QX_REGISTER_HPP_QX_BLOG(author, qx::trait::no_base_class_defined, 0)

typedef std::shared_ptr<author> author_ptr;
typedef qx::QxCollection<QString, author_ptr> list_author;

#endif // _QX_BLOG_AUTHOR_H_
