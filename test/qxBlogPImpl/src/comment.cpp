#include "../include/precompiled.h"

#include "../include/comment.h"
#include "../include/blog.h"

#include <QxOrm_Impl.h>

QX_REGISTER_CPP_QX_BLOG(comment)

struct Q_DECL_HIDDEN comment::comment_impl
{
   long        m_id;
   QString     m_text;
   QDateTime   m_dt_create;
   blog_ptr    m_blog;

   comment_impl() : m_id(0) { ; }
   ~comment_impl() { ; }
};

namespace qx {
template <> void register_class(QxClass<comment> & t)
{
   IxDataMember * pImpl = t.pimpl(& comment::m_pImpl);

   t.id(& comment::comment_impl::m_id, "comment_id", 0, pImpl);

   t.data(& comment::comment_impl::m_text, "comment_text", 0, true, true, pImpl);
   t.data(& comment::comment_impl::m_dt_create, "date_creation", 0, true, true, pImpl);

   t.relationManyToOne(& comment::comment_impl::m_blog, "blog_id", 0, pImpl);
}}

comment::comment() : m_pImpl(new comment_impl()) { ; }

comment::~comment() { ; }

comment::comment(const comment & other) : m_pImpl(new comment_impl(* other.m_pImpl)) { ; }

comment & comment::operator=(const comment & other)
{
   if (this != (& other)) { (* m_pImpl) = (* other.m_pImpl); }
   return (* this);
}

#ifdef Q_COMPILER_RVALUE_REFS
comment::comment(comment && other) Q_DECL_NOEXCEPT : m_pImpl(std::move(other.m_pImpl)) { ; }
comment & comment::operator=(comment && other) Q_DECL_NOEXCEPT { if (this != (& other)) { m_pImpl = std::move(other.m_pImpl); }; return (* this); }
#endif // Q_COMPILER_RVALUE_REFS

long comment::id() const { return m_pImpl->m_id; }

QString comment::text() const { return m_pImpl->m_text; }

QDateTime comment::dateCreation() const { return m_pImpl->m_dt_create; }

void comment::setId(long l) { m_pImpl->m_id = l; }

void comment::setText(const QString & s) { m_pImpl->m_text = s; }

void comment::setDateCreation(const QDateTime & d) { m_pImpl->m_dt_create = d; }

std::shared_ptr<blog> & comment::getBlog() { return m_pImpl->m_blog; }
