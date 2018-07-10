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

#ifndef _QX_COLLECTION_H_
#define _QX_COLLECTION_H_

#ifdef _MSC_VER
#pragma once
#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4996)
#pragma warning(disable:4503)
#endif // _MSC_VER

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/type_traits/is_pointer.hpp>

#include <QtCore/qpair.h>

#include "../../include/QxCollection/IxCollection.h"
#include "../../include/QxCollection/QxForeach.h"

#include "../../include/QxCommon/QxHashValue.h"

#include "../../include/QxTraits/get_class_name.h"
#include "../../include/QxTraits/is_smart_ptr.h"

namespace qx {

template <typename Key, typename Value>
class QxCollection : public IxCollection
{

public:

   typedef QPair<Key, Value> type_pair_key_value;

protected:

   typedef boost::multi_index::member<type_pair_key_value, Key, & type_pair_key_value::first> type_member;
   typedef boost::multi_index::random_access<> type_first_index;
   typedef boost::multi_index::hashed_unique<type_member> type_second_index;
   typedef boost::multi_index::indexed_by<type_first_index, type_second_index> type_indexed_by;
   typedef boost::multi_index::multi_index_container<type_pair_key_value, type_indexed_by> type_container;

   typedef typename type_container::template nth_index<0>::type type_index_rand;
   typedef typename type_container::template nth_index<1>::type type_index_hash;

public:

   typedef typename type_index_rand::iterator iterator;
   typedef typename type_index_rand::const_iterator const_iterator;
   typedef typename type_index_rand::reverse_iterator reverse_iterator;
   typedef typename type_index_rand::const_reverse_iterator const_reverse_iterator;

   typedef const Key & const_reference_key;
   typedef const Value & const_reference_value;

protected:

   type_container m_qxCollection;   // Collection with random access (like std::vector) and fast lookup by key (like boost::unordered_map)

public:

   QxCollection();
   QxCollection(const QxCollection<Key, Value> & other);
   virtual ~QxCollection();

   QxCollection<Key, Value> & operator= (const QxCollection<Key, Value> & other);
   bool operator== (const QxCollection<Key, Value> & other) const;
   bool operator!= (const QxCollection<Key, Value> & other) const;

   inline iterator begin();
   inline iterator end();
   inline const_iterator begin() const;
   inline const_iterator end() const;

   inline reverse_iterator rbegin();
   inline reverse_iterator rend();
   inline const_reverse_iterator rbegin() const;
   inline const_reverse_iterator rend() const;

   inline long capacity() const;
   inline void reserve(long size);
   inline void reverse();
   inline void clear();
   inline long count() const;
   inline long size() const;
   inline bool contains(const Key & key) const;
   inline bool exist(const Key & key) const;
   inline bool empty() const;

   inline bool push_back(const Key & key, const Value & value);
   inline bool push_front(const Key & key, const Value & value);
   inline bool insert(const Key & key, const Value & value);
   inline bool insert(long index, const Key & key, const Value & value);
   inline bool insert(const QxCollection<Key, Value> & other);
   inline bool insert(long index, const QxCollection<Key, Value> & other);
   inline bool replace(long index, const Key & key, const Value & value);
   inline bool swap(long index1, long index2);
   inline bool move(long indexFrom, long indexTo);

   inline bool removeByKey(const Key & key);
   inline bool removeByIndex(long index);
   inline bool removeByIndex(long first, long last);
   inline bool removeFirst();
   inline bool removeLast();

   inline const_reference_value getByKey(const Key & key) const;
   inline const_reference_value getByIndex(long index) const;
   inline const_reference_value getFirst() const;
   inline const_reference_value getLast() const;
   inline const_reference_key getKeyByIndex(long index) const;

   inline void sortByKey(bool bAscending = true);
   inline void sortByValue(bool bAscending = true);

   template <typename Compare>
   inline void sort(Compare comp) { m_qxCollection.template get<0>().sort(comp); }

private:

   void cloneCollection(QxCollection<Key, Value> * pClone, const QxCollection<Key, Value> & pRef);
   bool isSameCollection(const QxCollection<Key, Value> * p1, const QxCollection<Key, Value> & p2) const;

   template <bool bIsPointer /* = false */, int dummy>
   struct compareKeyValue
   {
      static inline bool compareByKeyAscending(const type_pair_key_value & v1, const type_pair_key_value & v2)    { return (v1.first < v2.first); }
      static inline bool compareByKeyDescending(const type_pair_key_value & v1, const type_pair_key_value & v2)   { return (v1.first > v2.first); }
      static inline bool compareByValueAscending(const type_pair_key_value & v1, const type_pair_key_value & v2)  { return (v1.second < v2.second); }
      static inline bool compareByValueDescending(const type_pair_key_value & v1, const type_pair_key_value & v2) { return (v1.second > v2.second); }
   };

   template <int dummy>
   struct compareKeyValue<true, dummy>
   {
      static inline bool compareByKeyAscending(const type_pair_key_value & v1, const type_pair_key_value & v2)    { return ((v1.first && v2.first) ? ((* v1.first) < (* v2.first)) : false); }
      static inline bool compareByKeyDescending(const type_pair_key_value & v1, const type_pair_key_value & v2)   { return ((v1.first && v2.first) ? ((* v1.first) > (* v2.first)) : true); }
      static inline bool compareByValueAscending(const type_pair_key_value & v1, const type_pair_key_value & v2)  { return ((v1.second && v2.second) ? ((* v1.second) < (* v2.second)) : false); }
      static inline bool compareByValueDescending(const type_pair_key_value & v1, const type_pair_key_value & v2) { return ((v1.second && v2.second) ? ((* v1.second) > (* v2.second)) : true); }
   };

};

} // namespace qx

#include "../../inl/QxCollection/QxCollection.inl"

QX_REGISTER_CLASS_NAME_TEMPLATE_2(qx::QxCollection)

#ifdef _MSC_VER
#pragma warning(pop)
#endif // _MSC_VER

#endif // _QX_COLLECTION_H_
