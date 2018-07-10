/****************************************************************************
**
** http://www.qxorm.com/
** Copyright (C) 2013 Lionel Marty (contact@qxorm.com)
**
** This file is part of the QxOrm library
**
** This software is provided 'as-is', without any express or implied
** warranty. In no event will the authors be held liable for any
** damages arising from the use of this software
**
** Commercial Usage
** Licensees holding valid commercial QxOrm licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Lionel Marty
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file 'license.gpl3.txt' included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met : http://www.gnu.org/copyleft/gpl.html
**
** If you are unsure which license is appropriate for your use, or
** if you have questions regarding the use of this file, please contact :
** contact@qxorm.com
**
****************************************************************************/

#ifndef _QX_DAO_POINTER_H_
#define _QX_DAO_POINTER_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxDaoPointer.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief qx::dao::ptr<T> : provide a classic smart-pointer (like boost::shared_ptr<T> or QSharedPointer<T>) with some features associated with QxDao module of QxOrm library
 */

#include <QtCore/qsharedpointer.h>
#include <QtCore/qstringlist.h>
#include <QtCore/qdatastream.h>

#include <QxSerialize/QDataStream/QxSerializeQDataStream_QSharedPointer.h>

namespace qx {
template <class T> QSharedPointer<T> clone_to_qt_shared_ptr(const T & obj);
} // namespace qx

namespace qx {
namespace dao {
template <typename T> class ptr;
} // namespace dao
} // namespace qx

template <typename T> QDataStream & operator<< (QDataStream & stream, const qx::dao::ptr<T> & t);
template <typename T> QDataStream & operator>> (QDataStream & stream, qx::dao::ptr<T> & t);

namespace qx {
namespace dao {

namespace detail {
template <class T> struct QxDao_IsDirty;
} // namespace detail

/*!
 * \ingroup QxDao
 * \brief qx::dao::ptr<T> : provide a classic smart-pointer (like boost::shared_ptr<T> or QSharedPointer<T>) with some features associated with QxDao module of QxOrm library
 *
 * QxOrm can be used with smart-pointers of boost and Qt libraries.
 * QxOrm smart-pointer is based on QSharedPointer and provides new features with qx::dao::xxx functions of QxDao module.
 * qx::dao::ptr<T> keeps automatically values from database.
 * So it's possible to detect if an instance has been modified using the method isDirty() : this method can return list of properties changed.
 * qx::dao::ptr<T> can also be used with the function qx::dao::update_optimized() to update in database only properties changed.
 * qx::dao::ptr<T> can be used with a simple object and with many containers : stl, boost, Qt and qx::QxCollection<Key, Value>.
 *
 * Quick sample using qx::dao::ptr<T> smart-pointer :
 * \code
// Test 'isDirty()' method
qx::dao::ptr<blog> blog_isdirty = qx::dao::ptr<blog>(new blog());
blog_isdirty->m_id = blog_1->m_id;
daoError = qx::dao::fetch_by_id(blog_isdirty);
qAssert(! daoError.isValid() && ! blog_isdirty.isDirty());

blog_isdirty->m_text = "blog property 'text' modified => blog is dirty !!!";
QStringList lstDiff; bool bDirty = blog_isdirty.isDirty(lstDiff);
qAssert(bDirty && (lstDiff.count() == 1) && (lstDiff.at(0) == "blog_text"));
if (bDirty) { qDebug("[QxOrm] test dirty 1 : blog is dirty => '%s'", qPrintable(lstDiff.join("|"))); }

// Update only property 'm_text' of 'blog_isdirty'
daoError = qx::dao::update_optimized(blog_isdirty);
qAssert(! daoError.isValid() && ! blog_isdirty.isDirty());
qx::dump(blog_isdirty);

// Test 'isDirty()' method with a container
typedef qx::dao::ptr< QList<author_ptr> > type_lst_author_test_is_dirty;

type_lst_author_test_is_dirty container_isdirty = type_lst_author_test_is_dirty(new QList<author_ptr>());
daoError = qx::dao::fetch_all(container_isdirty);
qAssert(! daoError.isValid() && ! container_isdirty.isDirty() && (container_isdirty->count() == 3));

author_ptr author_ptr_dirty = container_isdirty->at(1);
author_ptr_dirty->m_name = "author name modified at index 1 => container is dirty !!!";
bDirty = container_isdirty.isDirty(lstDiff);
qAssert(bDirty && (lstDiff.count() == 1));
if (bDirty) { qDebug("[QxOrm] test dirty 2 : container is dirty => '%s'", qPrintable(lstDiff.join("|"))); }

author_ptr_dirty = container_isdirty->at(2);
author_ptr_dirty->m_birthdate = QDate(1998, 03, 06);
bDirty = container_isdirty.isDirty(lstDiff);
qAssert(bDirty && (lstDiff.count() == 2));
if (bDirty) { qDebug("[QxOrm] test dirty 3 : container is dirty => '%s'", qPrintable(lstDiff.join("|"))); }

// Update only property 'm_name' at position 1, only property 'm_birthdate' at position 2 and nothing at position 0
daoError = qx::dao::update_optimized(container_isdirty);
qAssert(! daoError.isValid() && ! container_isdirty.isDirty());
qx::dump(container_isdirty);

// Fetch only property 'm_dt_creation' of blog
QStringList lstColumns = QStringList() << "date_creation";
list_blog lst_blog_with_only_date_creation;
daoError = qx::dao::fetch_all(lst_blog_with_only_date_creation, NULL, lstColumns);
qAssert(! daoError.isValid() && (lst_blog_with_only_date_creation.size() > 0));

if ((lst_blog_with_only_date_creation.size() > 0) && (lst_blog_with_only_date_creation[0] != NULL))
{ qAssert(lst_blog_with_only_date_creation[0]->m_text.isEmpty()); }

qx::dump(lst_blog_with_only_date_creation);
 * \endcode
 */
template <typename T>
class ptr
{

   template <class U> friend QDataStream & ::operator<< (QDataStream & stream, const qx::dao::ptr<U> & t);
   template <class U> friend QDataStream & ::operator>> (QDataStream & stream, qx::dao::ptr<U> & t);

private:

   QSharedPointer<T> m_pWork;       //!< Default pointer => user works with this pointer
   QSharedPointer<T> m_pOriginal;   //!< Keep original pointer containing all values from database

public:

   ptr()                                                                                                             { ; }
   explicit ptr(T * ptr) : m_pWork(ptr)                                                                              { ; }
   explicit ptr(T * ptr, T * original) : m_pWork(ptr), m_pOriginal(original)                                         { ; }
   ptr(const qx::dao::ptr<T> & other) : m_pWork(other.m_pWork), m_pOriginal(other.m_pOriginal)                       { ; }
   ptr(const QSharedPointer<T> & other) : m_pWork(other)                                                             { ; }
   ptr(const QSharedPointer<T> & other, const QSharedPointer<T> & original) : m_pWork(other), m_pOriginal(original)  { ; }
   ptr(const QWeakPointer<T> & other) : m_pWork(other)                                                               { ; }
   ptr(const QWeakPointer<T> & other, const QWeakPointer<T> & original) : m_pWork(other), m_pOriginal(original)      { ; }
   virtual ~ptr()                                                                                                    { ; }

   template <typename Deleter> ptr(T * ptr, Deleter deleter) : m_pWork(ptr, deleter)                                       { ; }
   template <typename Deleter> ptr(T * ptr, T * original, Deleter deleter) : m_pWork(ptr, deleter), m_pOriginal(original)  { ; }

   template <class X> ptr(const qx::dao::ptr<X> & other) : m_pWork(qSharedPointerCast<T>(other.m_pWork)), m_pOriginal(qSharedPointerCast<T>(other.m_pOriginal))                                                { ; }
   template <class X> ptr(const QSharedPointer<X> & other) : m_pWork(qSharedPointerCast<T>(other))                                                                                                             { ; }
   template <class X> ptr(const QSharedPointer<X> & other, const QSharedPointer<T> & original) : m_pWork(qSharedPointerCast<T>(other)), m_pOriginal(qSharedPointerCast<T>(original))                           { ; }
   template <class X> ptr(const QWeakPointer<X> & other) : m_pWork(qSharedPointerCast<T>(other.toStrongRef()))                                                                                                 { ; }
   template <class X> ptr(const QWeakPointer<X> & other, const QWeakPointer<X> & original) : m_pWork(qSharedPointerCast<T>(other.toStrongRef())), m_pOriginal(qSharedPointerCast<T>(original.toStrongRef()))   { ; }

   qx::dao::ptr<T> & operator=(const qx::dao::ptr<T> & other)     { m_pWork = other.m_pWork; m_pOriginal = other.m_pOriginal; return (* this); }
   qx::dao::ptr<T> & operator=(const QSharedPointer<T> & other)   { m_pWork = other; m_pOriginal.clear(); return (* this); }
   qx::dao::ptr<T> & operator=(const QWeakPointer<T> & other)     { m_pWork = other; m_pOriginal.clear(); return (* this); }

   template <class X> qx::dao::ptr<T> & operator=(const qx::dao::ptr<X> & other)    { m_pWork = qSharedPointerCast<T>(other.m_pWork); m_pOriginal = qSharedPointerCast<T>(other.m_pOriginal); return (* this); }
   template <class X> qx::dao::ptr<T> & operator=(const QSharedPointer<X> & other)  { m_pWork = qSharedPointerCast<T>(other); m_pOriginal.clear(); return (* this); }
   template <class X> qx::dao::ptr<T> & operator=(const QWeakPointer<X> & other)    { m_pWork = qSharedPointerCast<T>(other.toStrongRef()); m_pOriginal.clear(); return (* this); }

   inline T * get() const                                      { return m_pWork.data(); }
   inline T * getOriginal() const                              { return m_pOriginal.data(); }
   inline T * data() const                                     { return m_pWork.data(); }
   inline T * dataOriginal() const                             { return m_pOriginal.data(); }
   inline bool isNull() const                                  { return m_pWork.isNull(); }
   inline operator bool() const                                { return (! m_pWork.isNull()); }
   inline bool operator!() const                               { return m_pWork.isNull(); }
   inline T & operator*() const                                { return (* m_pWork.data()); }
   inline T * operator->() const                               { return m_pWork.data(); }
   inline void clear()                                         { m_pWork.clear(); m_pOriginal.clear(); }
   inline void reset()                                         { m_pWork.clear(); m_pOriginal.clear(); }
   inline void reset(const QSharedPointer<T> & ptr)            { m_pWork = ptr; m_pOriginal.clear(); }
   inline void resetOriginal(const QSharedPointer<T> & ptr)    { m_pOriginal = ptr; }
   inline bool isDirty() const                                 { QStringList lstDiff; return isDirty(lstDiff); }
   inline QSharedPointer<T> toQtSharedPointer() const          { return m_pWork; }
   inline void saveToOriginal()                                { m_pOriginal.clear(); if (m_pWork) { m_pOriginal = qx::clone_to_qt_shared_ptr(* m_pWork); } }
   inline void restoreFromOriginal()                           { m_pWork.clear(); if (m_pOriginal) { m_pWork = qx::clone_to_qt_shared_ptr(* m_pOriginal); } }

   template <class X> qx::dao::ptr<X> staticCast() const       { return qx::dao::ptr<X>(m_pWork.template staticCast<X>(), m_pOriginal.template staticCast<X>()); }
   template <class X> qx::dao::ptr<X> dynamicCast() const      { return qx::dao::ptr<X>(m_pWork.template dynamicCast<X>(), m_pOriginal.template dynamicCast<X>()); }
   template <class X> qx::dao::ptr<X> constCast() const        { return qx::dao::ptr<X>(m_pWork.template constCast<X>(), m_pOriginal.template constCast<X>()); }

   bool isDirty(QStringList & lstDiff) const
   {
      lstDiff.clear();
      if (m_pWork.isNull() || m_pOriginal.isNull()) { lstDiff.append("*"); return true; }
      if (m_pWork == m_pOriginal) { return false; }
      qx::dao::detail::QxDao_IsDirty<T>::compare((* m_pWork), (* m_pOriginal), lstDiff);
      return (! lstDiff.isEmpty());
   }

};

} // namespace dao
} // namespace qx

template<class T, class X> bool operator==(const qx::dao::ptr<T> & ptr1, const qx::dao::ptr<X> & ptr2)   { return (ptr1.toQtSharedPointer() == ptr2.toQtSharedPointer()); }
template<class T, class X> bool operator!=(const qx::dao::ptr<T> & ptr1, const qx::dao::ptr<X> & ptr2)   { return (ptr1.toQtSharedPointer() != ptr2.toQtSharedPointer()); }
template<class T, class X> bool operator==(const qx::dao::ptr<T> & ptr1, const X * ptr2)                 { return (ptr1.toQtSharedPointer() == ptr2); }
template<class T, class X> bool operator!=(const qx::dao::ptr<T> & ptr1, const X * ptr2)                 { return (ptr1.toQtSharedPointer() != ptr2); }
template<class T, class X> bool operator==(const T * ptr1, const qx::dao::ptr<X> & ptr2)                 { return (ptr1 == ptr2.toQtSharedPointer()); }
template<class T, class X> bool operator!=(const T * ptr1, const qx::dao::ptr<X> & ptr2)                 { return (ptr1 != ptr2.toQtSharedPointer()); }

template <typename T>
QDataStream & operator<< (QDataStream & stream, const qx::dao::ptr<T> & t)
{
   stream << t.m_pWork;
   stream << t.m_pOriginal;
   return stream;
}

template <typename T>
QDataStream & operator>> (QDataStream & stream, qx::dao::ptr<T> & t)
{
   stream >> t.m_pWork;
   stream >> t.m_pOriginal;
   return stream;
}

#endif // _QX_DAO_POINTER_H_
