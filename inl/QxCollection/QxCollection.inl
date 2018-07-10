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

namespace qx {

template <typename Key, typename Value>
QxCollection<Key, Value>::QxCollection() : IxCollection()
{
}

template <typename Key, typename Value>
QxCollection<Key, Value>::QxCollection(const QxCollection<Key, Value> & other) : IxCollection()
{
   cloneCollection(this, other);
}

template <typename Key, typename Value>
QxCollection<Key, Value>::~QxCollection()
{
}

template <typename Key, typename Value>
QxCollection<Key, Value> & QxCollection<Key, Value>::operator= (const QxCollection<Key, Value> & other)
{
   if (this != (& other)) { cloneCollection(this, other); }
   return (* this);
}

template <typename Key, typename Value>
bool QxCollection<Key, Value>::operator== (const QxCollection<Key, Value> & other) const
{
   return isSameCollection(this, other);
}

template <typename Key, typename Value>
bool QxCollection<Key, Value>::operator!= (const QxCollection<Key, Value> & other) const
{
   return (! isSameCollection(this, other));
}

template <typename Key, typename Value>
void QxCollection<Key, Value>::cloneCollection(QxCollection<Key, Value> * pClone, const QxCollection<Key, Value> & pRef)
{
   if (! pClone) { return; }
   pClone->m_qxCollection.clear();

   for (long l = 0; l < pRef.size(); l++)
   {
      type_pair_key_value pair = pRef.m_qxCollection.template get<0>().at(l);
      pClone->m_qxCollection.template get<0>().push_back(pair);
   }
}

template <typename Key, typename Value>
bool QxCollection<Key, Value>::isSameCollection(const QxCollection<Key, Value> * p1, const QxCollection<Key, Value> & p2) const
{
   if (! p1 || (p1->size() != p2.size()))
      return false;

   for (long l = 0; l < p2.size(); l++)
   {
      type_pair_key_value pair = p2.m_qxCollection.template get<0>().at(l);
      if (p1->m_qxCollection.template get<0>().at(l) != pair) { return false; }
   }

   return true;
}

template <typename Key, typename Value>
inline typename QxCollection<Key, Value>::iterator QxCollection<Key, Value>::begin()
{
   return m_qxCollection.template get<0>().begin();
}

template <typename Key, typename Value>
inline typename QxCollection<Key, Value>::iterator QxCollection<Key, Value>::end()
{
   return m_qxCollection.template get<0>().end();
}

template <typename Key, typename Value>
inline typename QxCollection<Key, Value>::const_iterator QxCollection<Key, Value>::begin() const
{
   return m_qxCollection.template get<0>().begin();
}

template <typename Key, typename Value>
inline typename QxCollection<Key, Value>::const_iterator QxCollection<Key, Value>::end() const
{
   return m_qxCollection.template get<0>().end();
}

template <typename Key, typename Value>
inline typename QxCollection<Key, Value>::reverse_iterator QxCollection<Key, Value>::rbegin()
{
   return m_qxCollection.template get<0>().rbegin();
}

template <typename Key, typename Value>
inline typename QxCollection<Key, Value>::reverse_iterator QxCollection<Key, Value>::rend()
{
   return m_qxCollection.template get<0>().rend();
}

template <typename Key, typename Value>
inline typename QxCollection<Key, Value>::const_reverse_iterator QxCollection<Key, Value>::rbegin() const
{
   return m_qxCollection.template get<0>().rbegin();
}

template <typename Key, typename Value>
inline typename QxCollection<Key, Value>::const_reverse_iterator QxCollection<Key, Value>::rend() const
{
   return m_qxCollection.template get<0>().rend();
}

template <typename Key, typename Value>
inline long QxCollection<Key, Value>::capacity() const
{
   return m_qxCollection.template get<0>().capacity();
}

template <typename Key, typename Value>
inline void QxCollection<Key, Value>::reserve(long size)
{
   if (size <= 0) { return; }
   m_qxCollection.template get<0>().reserve(size);
}

template <typename Key, typename Value>
inline void QxCollection<Key, Value>::reverse()
{
   m_qxCollection.template get<0>().reverse();
}

template <typename Key, typename Value>
inline void QxCollection<Key, Value>::clear()
{
   m_qxCollection.clear();
}

template <typename Key, typename Value>
inline long QxCollection<Key, Value>::count() const
{
   return static_cast<long>(m_qxCollection.template get<0>().size());
}

template <typename Key, typename Value>
inline long QxCollection<Key, Value>::size() const
{
   return this->count();
}

template <typename Key, typename Value>
inline bool QxCollection<Key, Value>::contains(const Key & key) const
{
   return (m_qxCollection.template get<1>().find(key) != m_qxCollection.template get<1>().end());
}

template <typename Key, typename Value>
inline bool QxCollection<Key, Value>::exist(const Key & key) const
{
   return this->contains(key);
}

template <typename Key, typename Value>
inline bool QxCollection<Key, Value>::empty() const
{
   return m_qxCollection.template get<0>().empty();
}

template <typename Key, typename Value>
inline bool QxCollection<Key, Value>::push_back(const Key & key, const Value & value)
{
   return this->insert(key, value);
}

template <typename Key, typename Value>
inline bool QxCollection<Key, Value>::push_front(const Key & key, const Value & value)
{
   return this->insert(0, key, value);
}

template <typename Key, typename Value>
inline bool QxCollection<Key, Value>::insert(const Key & key, const Value & value)
{
   qAssert(! exist(key));
   return m_qxCollection.template get<0>().push_back(type_pair_key_value(key, value)).second;
}

template <typename Key, typename Value>
inline bool QxCollection<Key, Value>::insert(long index, const Key & key, const Value & value)
{
   qAssert(! exist(key));
   if (index < 0) { index = 0; }
   if ((index >= size()) && (index != 0)) { index = (size() - 1); }
   return m_qxCollection.template get<0>().insert((begin() + index), type_pair_key_value(key, value)).second;
}

template <typename Key, typename Value>
inline bool QxCollection<Key, Value>::insert(const QxCollection<Key, Value> & other)
{
   return this->insert((size() - 1), other);
}

template <typename Key, typename Value>
inline bool QxCollection<Key, Value>::insert(long index, const QxCollection<Key, Value> & other)
{
   if (index < 0) { index = 0; }
   if ((index >= size()) && (index != 0)) { index = (size() - 1); }

   for (long l = 0; l < other.size(); l++)
   {
      type_pair_key_value pair = other.m_qxCollection.template get<0>().at(l);
      this->insert(pair.first, pair.second);
   }

   return true;
}

template <typename Key, typename Value>
inline bool QxCollection<Key, Value>::replace(long index, const Key & key, const Value & value)
{
   qAssert(! exist(key));
   return m_qxCollection.template get<0>().replace((begin() + index), type_pair_key_value(key, value));
}

template <typename Key, typename Value>
inline bool QxCollection<Key, Value>::swap(long index1, long index2)
{
   if (index1 < 0 || index1 >= size()) { return false; }
   if (index2 < 0 || index2 >= size()) { return false; }
   if (index1 == index2) { return true; }
   m_qxCollection.template get<0>().relocate((begin() + index1), (begin() + index2));
   m_qxCollection.template get<0>().relocate((begin() + index2), (begin() + index1));
   return true;
}

template <typename Key, typename Value>
inline bool QxCollection<Key, Value>::move(long indexFrom, long indexTo)
{
   if (indexFrom < 0 || indexFrom >= size()) { return false; }
   if (indexTo < 0 || indexTo >= size()) { return false; }
   if (indexFrom == indexTo) { return true; }
   m_qxCollection.template get<0>().relocate((begin() + indexTo), (begin() + indexFrom));
   return true;
}

template <typename Key, typename Value>
inline bool QxCollection<Key, Value>::removeByKey(const Key & key)
{
   qAssert(exist(key));
   return (m_qxCollection.template get<1>().erase(key) > 0);
}

template <typename Key, typename Value>
inline bool QxCollection<Key, Value>::removeByIndex(long index)
{
   if (index < 0 || index >= size()) { return false; }
   return (m_qxCollection.template get<0>().erase(begin() + index) != end());
}

template <typename Key, typename Value>
inline bool QxCollection<Key, Value>::removeByIndex(long first, long last)
{
   if (first < 0 || first >= size()) { return false; }
   if (last < 0 || last >= size()) { return false; }
   if (first > last) { return false; }
   return (m_qxCollection.template get<0>().erase((begin() + first), (begin() + last)) != end());
}

template <typename Key, typename Value>
inline bool QxCollection<Key, Value>::removeFirst()
{
   return this->removeByIndex(0);
}

template <typename Key, typename Value>
inline bool QxCollection<Key, Value>::removeLast()
{
   return this->removeByIndex(size() - 1);
}

template <typename Key, typename Value>
inline typename QxCollection<Key, Value>::const_reference_value QxCollection<Key, Value>::getByKey(const Key & key) const
{
   qAssert(exist(key));
   return (* m_qxCollection.template get<1>().find(key)).second;
}

template <typename Key, typename Value>
inline typename QxCollection<Key, Value>::const_reference_value QxCollection<Key, Value>::getByIndex(long index) const
{
   qAssert((index >= 0) && (index < size()));
   return m_qxCollection.template get<0>().at(index).second;
}

template <typename Key, typename Value>
inline typename QxCollection<Key, Value>::const_reference_value QxCollection<Key, Value>::getFirst() const
{
   qAssert(! empty());
   return m_qxCollection.template get<0>().front().second;
}

template <typename Key, typename Value>
inline typename QxCollection<Key, Value>::const_reference_value QxCollection<Key, Value>::getLast() const
{
   qAssert(! empty());
   return m_qxCollection.template get<0>().back().second;
}

template <typename Key, typename Value>
inline typename QxCollection<Key, Value>::const_reference_key QxCollection<Key, Value>::getKeyByIndex(long index) const
{
   qAssert((index >= 0) && (index < size()));
   return m_qxCollection.template get<0>().at(index).first;
}

template <typename Key, typename Value>
inline void QxCollection<Key, Value>::sortByKey(bool bAscending /* = true */)
{
   if (bAscending)   { m_qxCollection.template get<0>().sort(& compareKeyValue<boost::is_pointer<Key>::value || qx::trait::is_smart_ptr<Key>::value, 0>::compareByKeyAscending); }
   else              { m_qxCollection.template get<0>().sort(& compareKeyValue<boost::is_pointer<Key>::value || qx::trait::is_smart_ptr<Key>::value, 0>::compareByKeyDescending); }
}

template <typename Key, typename Value>
inline void QxCollection<Key, Value>::sortByValue(bool bAscending /* = true */)
{
   if (bAscending)   { m_qxCollection.template get<0>().sort(& compareKeyValue<boost::is_pointer<Value>::value || qx::trait::is_smart_ptr<Value>::value, 0>::compareByValueAscending); }
   else              { m_qxCollection.template get<0>().sort(& compareKeyValue<boost::is_pointer<Value>::value || qx::trait::is_smart_ptr<Value>::value, 0>::compareByValueDescending); }
}

} // namespace qx

template <typename Key, typename Value>
QDataStream & operator >> (QDataStream & stream, qx::QxCollection<Key, Value> & coll)
{
   qint32 lCount = 0;
   stream >> lCount;
   coll.clear();
   coll.reserve(lCount);

   for (qint32 l = 0; l < lCount; l++)
   {
      Key key;       stream >> key;
      Value value;   stream >> value;
      coll.insert(key, value);
   }

   return stream;
}

template <typename Key, typename Value>
QDataStream & operator << (QDataStream & stream, const qx::QxCollection<Key, Value> & coll)
{
   long lCount = coll.count();
   stream << (qint32)(lCount);

   for (long l = 0; l < lCount; l++)
   {
      stream << coll.getKeyByIndex(l);
      stream << coll.getByIndex(l);
   }

   return stream;
}
