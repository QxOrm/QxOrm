/****************************************************************************
**
** http://www.qxorm.com/
** http://sourceforge.net/projects/qxorm/
** Original file by Lionel Marty
**
** This file is part of the QxOrm library
**
** This software is provided 'as-is', without any express or implied
** warranty. In no event will the authors be held liable for any
** damages arising from the use of this software.
**
** GNU Lesser General Public License Usage
** This file must be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file 'license.lgpl.txt' included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you have questions regarding the use of this file, please contact :
** contact@qxorm.com
**
****************************************************************************/

#ifndef _QX_DAO_POINTER_H_
#define _QX_DAO_POINTER_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QtCore/qsharedpointer.h>
#include <QtCore/qstringlist.h>

namespace qx {
namespace dao {

namespace detail {
template <class T> struct QxDao_IsDirty;
} // namespace detail

template <typename T>
class ptr
{

private:

   QSharedPointer<T> m_pWork;       // Default pointer => user works with this pointer
   QSharedPointer<T> m_pOriginal;   // Keep original pointer containing all values from database

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

   template <class X> qx::dao::ptr<X> staticCast() const       { return qx::dao::ptr<X>(m_pWork.staticCast<X>(), m_pOriginal.staticCast<X>()); }
   template <class X> qx::dao::ptr<X> dynamicCast() const      { return qx::dao::ptr<X>(m_pWork.dynamicCast<X>(), m_pOriginal.dynamicCast<X>()); }
   template <class X> qx::dao::ptr<X> constCast() const        { return qx::dao::ptr<X>(m_pWork.constCast<X>(), m_pOriginal.constCast<X>()); }

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

#endif // _QX_DAO_POINTER_H_
