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

#ifndef _QX_CACHE_H_
#define _QX_CACHE_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/any.hpp>

#include "../../include/QxCommon/QxBool.h"

#include "../../include/QxCollection/QxCollection.h"

#include "../../include/QxSingleton/QxSingleton.h"

namespace qx {
namespace cache {
namespace detail {

class QX_DLL_EXPORT QxCache : public qx::QxSingleton<QxCache>
{

   friend class qx::QxSingleton<QxCache>;

protected:

   typedef std::pair<long, boost::any> type_qx_cache;
   typedef qx::QxCollection<QString, type_qx_cache> type_qx_lst_cache;

   type_qx_lst_cache m_cache;    // List of objects in cache under 'boost::any' format
   QMutex m_oMutexCache;         // Mutex => 'QxCache' is thread-safe
   long m_lMaxCost;              // Max cost before deleting object in cache
   long m_lCurrCost;             // Current cost in cache

public:

   QxCache() : qx::QxSingleton<QxCache>("qx::cache::detail::QxCache"), m_lMaxCost(999999999), m_lCurrCost(0) { ; }
   virtual ~QxCache() { ; }

   inline long getCurrCost() const  { return m_lCurrCost; }
   inline long getMaxCost() const   { return m_lMaxCost; }
   inline void setMaxCost(long l)   { QMutexLocker locker(& m_oMutexCache); m_lMaxCost = ((l < 0) ? 0 : l); updateCost(); }

   inline long count() const                          { return m_cache.count(); }
   inline long size() const                           { return this->count(); }
   inline bool isEmpty() const                        { return (this->count() == 0); }
   inline bool exist(const QString & sKey) const      { return m_cache.exist(sKey); }
   inline bool contains(const QString & sKey) const   { return this->exist(sKey); }
   inline boost::any at(const QString & sKey)         { QMutexLocker locker(& m_oMutexCache); return (this->exist(sKey) ? m_cache.getByKey(sKey).second : boost::any()); }
   inline void clear()                                { QMutexLocker locker(& m_oMutexCache); m_cache.clear(); m_lCurrCost = 0; }

   bool insert(const QString & sKey, const boost::any & pObj, long lCost = 1);
   bool remove(const QString & sKey);

private:

   void updateCost();

};

} // namespace detail

inline void max_cost(long l)                 { qx::cache::detail::QxCache::getSingleton()->setMaxCost(l); }
inline long max_cost()                       { return qx::cache::detail::QxCache::getSingleton()->getMaxCost(); }
inline long current_cost()                   { return qx::cache::detail::QxCache::getSingleton()->getCurrCost(); }
inline long count()                          { return qx::cache::detail::QxCache::getSingleton()->count(); }
inline bool is_empty()                       { return qx::cache::detail::QxCache::getSingleton()->isEmpty(); }
inline void clear()                          { qx::cache::detail::QxCache::getSingleton()->clear(); }
inline bool exist(const QString & sKey)      { return qx::cache::detail::QxCache::getSingleton()->exist(sKey); }
inline bool remove(const QString & sKey)     { return qx::cache::detail::QxCache::getSingleton()->remove(sKey); }

template <typename T>
inline bool set(const QString & sKey, const T & t, long lCost = 1)
{ boost::any obj(t); return qx::cache::detail::QxCache::getSingleton()->insert(sKey, obj, lCost); }

template <typename T>
inline T get(const QString & sKey)
{
   boost::any obj = qx::cache::detail::QxCache::getSingleton()->at(sKey);
   if (obj.empty()) { return T(); }
   try { return boost::any_cast<T>(obj); }
   catch (const boost::bad_any_cast & err) { Q_UNUSED(err); return T(); }
}

template <typename T>
inline qx_bool get(const QString & sKey, T & t)
{
   if (! qx::cache::exist(sKey)) { return qx_bool(false, 0, "[QxOrm] Key doesn't exist in cache"); }
   boost::any obj = qx::cache::detail::QxCache::getSingleton()->at(sKey);
   try { t = boost::any_cast<T>(obj); return qx_bool(true); }
   catch (const boost::bad_any_cast & err) { Q_UNUSED(err); return qx_bool(false, 0, "[QxOrm] Bad any cast exception"); }
}

} // namespace cache
} // namespace qx

#endif // _QX_CACHE_H_
