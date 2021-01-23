#ifndef _QX_BLOG_COMMENT_H_
#define _QX_BLOG_COMMENT_H_

class blog;

class QX_BLOG_DLL_EXPORT comment
{

   QX_REGISTER_FRIEND_CLASS(comment)

private:

   struct comment_impl;
   std::unique_ptr<comment_impl> m_pImpl; //!< Private implementation idiom

public:

   comment();
   virtual ~comment();

   comment(const comment & other);
   comment & operator=(const comment & other);

#ifdef Q_COMPILER_RVALUE_REFS
   comment(comment && other) Q_DECL_NOEXCEPT;
   comment & operator=(comment && other) Q_DECL_NOEXCEPT;
#endif // Q_COMPILER_RVALUE_REFS

   long id() const;
   QString text() const;
   QDateTime dateCreation() const;

   void setId(long l);
   void setText(const QString & s);
   void setDateCreation(const QDateTime & d);

   std::shared_ptr<blog> & getBlog();

};

QX_REGISTER_HPP_QX_BLOG(comment, qx::trait::no_base_class_defined, 0)

typedef std::shared_ptr<comment> comment_ptr;
typedef QList<comment_ptr> list_comment;

#endif // _QX_BLOG_COMMENT_H_
