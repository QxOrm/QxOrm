#include "../include/precompiled.h"

#include "../include/blog.h"
#include "../include/author.h"
#include "../include/comment.h"
#include "../include/category.h"

#include <QxOrm_Impl.h>

QX_REGISTER_CPP_QX_BLOG(blog)

struct Q_DECL_HIDDEN blog::blog_impl
{
   long           m_id;
   QString        m_text;
   QDateTime      m_dt_creation;
   author_ptr     m_author;
   list_comment   m_commentX;
   list_category  m_categoryX;

   blog_impl() : m_id(0) { ; }
   ~blog_impl() { ; }
};

namespace qx {
template <> void register_class(QxClass<blog> & t)
{
   IxDataMember * pImpl = t.pimpl(& blog::m_pImpl);

   t.id(& blog::blog_impl::m_id, "blog_id", 0, pImpl);

   t.data(& blog::blog_impl::m_text, "blog_text", 0, true, true, pImpl);
   t.data(& blog::blog_impl::m_dt_creation, "date_creation", 0, true, true, pImpl);

   t.relationManyToOne(& blog::blog_impl::m_author, "author_id", 0, pImpl);
   t.relationOneToMany(& blog::blog_impl::m_commentX, "list_comment", "blog_id", 0, pImpl);
   t.relationManyToMany(& blog::blog_impl::m_categoryX, "list_category", "category_blog", "blog_id", "category_id", 0, pImpl);
}}

blog::blog() : m_pImpl(new blog_impl()) { ; }

blog::~blog() { ; }

blog::blog(const blog & other) : m_pImpl(new blog_impl(* other.m_pImpl)) { ; }

blog & blog::operator=(const blog & other)
{
   if (this != (& other)) { (* m_pImpl) = (* other.m_pImpl); }
   return (* this);
}

#ifdef Q_COMPILER_RVALUE_REFS
blog::blog(blog && other) Q_DECL_NOEXCEPT : m_pImpl(std::move(other.m_pImpl)) { ; }
blog & blog::operator=(blog && other) Q_DECL_NOEXCEPT { if (this != (& other)) { m_pImpl = std::move(other.m_pImpl); }; return (* this); }
#endif // Q_COMPILER_RVALUE_REFS

long blog::id() const { return m_pImpl->m_id; }

QString blog::text() const { return m_pImpl->m_text; }

QDateTime blog::dateCreation() const { return m_pImpl->m_dt_creation; }

void blog::setId(long l) { m_pImpl->m_id = l; }

void blog::setText(const QString & s) { m_pImpl->m_text = s; }

void blog::setDateCreation(const QDateTime & d) { m_pImpl->m_dt_creation = d; }

std::shared_ptr<author> & blog::getAuthor() { return m_pImpl->m_author; }

QList< std::shared_ptr<comment> > & blog::listOfComments() { return m_pImpl->m_commentX; }

qx::QxCollection<long, QSharedPointer<category> > & blog::listOfCategories() { return m_pImpl->m_categoryX; }
