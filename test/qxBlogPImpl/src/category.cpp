#include "../include/precompiled.h"

#include "../include/category.h"
#include "../include/blog.h"

#include <QxOrm_Impl.h>

QX_REGISTER_CPP_QX_BLOG(category)

struct Q_DECL_HIDDEN category::category_impl
{
   typedef qx::QxCollection<long, blog_ptr> list_blog;

   long        m_id;
   QString     m_name;
   QString     m_desc;
   list_blog   m_blogX;

   category_impl() : m_id(0) { ; }
   ~category_impl() { ; }
};

namespace qx {
template <> void register_class(QxClass<category> & t)
{
   IxDataMember * pImpl = t.pimpl(& category::m_pImpl);

   t.id(& category::category_impl::m_id, "category_id", 0, pImpl);

   t.data(& category::category_impl::m_name, "name", 0, true, true, pImpl);
   t.data(& category::category_impl::m_desc, "description", 0, true, true, pImpl);

   t.relationManyToMany(& category::category_impl::m_blogX, "list_blog", "category_blog", "category_id", "blog_id", 0, pImpl);
}}

category::category() : m_pImpl(new category_impl()) { ; }

category::~category() { ; }

category::category(const category & other) : m_pImpl(new category_impl(* other.m_pImpl)) { ; }

category & category::operator=(const category & other)
{
   if (this != (& other)) { (* m_pImpl) = (* other.m_pImpl); }
   return (* this);
}

#ifdef Q_COMPILER_RVALUE_REFS
category::category(category && other) Q_DECL_NOEXCEPT : m_pImpl(std::move(other.m_pImpl)) { ; }
category & category::operator=(category && other) Q_DECL_NOEXCEPT { if (this != (& other)) { m_pImpl = std::move(other.m_pImpl); }; return (* this); }
#endif // Q_COMPILER_RVALUE_REFS

long category::id() const { return m_pImpl->m_id; }

QString category::name() const { return m_pImpl->m_name; }

QString category::desc() const { return m_pImpl->m_desc; }

void category::setId(long l) { m_pImpl->m_id = l; }

void category::setName(const QString & s) { m_pImpl->m_name = s; }

void category::setDesc(const QString & s) { m_pImpl->m_desc = s; }

qx::QxCollection<long, std::shared_ptr<blog> > & category::listOfBlogs() { return m_pImpl->m_blogX; }
