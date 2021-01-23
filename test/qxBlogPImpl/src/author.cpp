#include "../include/precompiled.h"

#include "../include/author.h"
#include "../include/blog.h"

#include <QxOrm_Impl.h>

QX_REGISTER_CPP_QX_BLOG(author)

struct Q_DECL_HIDDEN author::author_impl
{
   QString           m_id;
   QString           m_name;
   QDate             m_birthdate;
   author::enum_sex  m_sex;
   list_blog         m_blogX;

   author_impl() : m_sex(author::unknown) { ; }
   ~author_impl() { ; }
};

namespace qx {
template <> void register_class(QxClass<author> & t)
{
   IxDataMember * pImpl = t.pimpl(& author::m_pImpl);

   t.id(& author::author_impl::m_id, "author_id", 0, pImpl);

   t.data(& author::author_impl::m_name, "name", 0, true, true, pImpl);
   t.data(& author::author_impl::m_birthdate, "birthdate", 0, true, true, pImpl);
   t.data(& author::author_impl::m_sex, "sex", 0, true, true, pImpl);

   t.relationOneToMany(& author::author_impl::m_blogX, "list_blog", "author_id", 0, pImpl);

   t.fct_0<int>(std::mem_fn(& author::age), "age"); // using std::mem_fn() here is just a workaround for an issue with some versions of MSVC, it is not required with a full compliant C++11 compiler (http://stackoverflow.com/questions/23778883/vs2013-stdfunction-with-member-function)
}}

author::author() : m_pImpl(new author_impl()) { ; }

author::~author() { ; }

author::author(const author & other) : m_pImpl(new author_impl(* other.m_pImpl)) { ; }

author & author::operator=(const author & other)
{
   if (this != (& other)) { (* m_pImpl) = (* other.m_pImpl); }
   return (* this);
}

#ifdef Q_COMPILER_RVALUE_REFS
author::author(author && other) Q_DECL_NOEXCEPT : m_pImpl(std::move(other.m_pImpl)) { ; }
author & author::operator=(author && other) Q_DECL_NOEXCEPT { if (this != (& other)) { m_pImpl = std::move(other.m_pImpl); }; return (* this); }
#endif // Q_COMPILER_RVALUE_REFS

int author::age() const
{
   if (! m_pImpl->m_birthdate.isValid()) { return -1; }
   return (QDate::currentDate().year() - m_pImpl->m_birthdate.year());
}

QString author::id() const { return m_pImpl->m_id; }

QString author::name() const { return m_pImpl->m_name; }

QDate author::birthdate() const { return m_pImpl->m_birthdate; }

author::enum_sex author::sex() const { return m_pImpl->m_sex; }

void author::setId(const QString & s) { m_pImpl->m_id = s; }

void author::setName(const QString & s) { m_pImpl->m_name = s; }

void author::setBirthdate(const QDate & d) { m_pImpl->m_birthdate = d; }

void author::setSex(enum_sex e) { m_pImpl->m_sex = e; }
