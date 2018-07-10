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
QxCollection<Key, Value>::QxCollection() : IxCollection(), m_batch(false)
{
}

template <typename Key, typename Value>
QxCollection<Key, Value>::QxCollection(const QxCollection<Key, Value> & other) : IxCollection(), m_batch(false)
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
   qAssert(pRef.m_list.size() == pRef.m_hash.size());
   pClone->m_list = pRef.m_list;
   pClone->m_hash = pRef.m_hash;
}

template <typename Key, typename Value>
bool QxCollection<Key, Value>::isSameCollection(const QxCollection<Key, Value> * p1, const QxCollection<Key, Value> & p2) const
{
   qAssert(p2.m_list.size() == p2.m_hash.size());
   if (! p1 || (p1->size() != p2.size())) { return false; }
   return ((p1->m_list == p2.m_list) && (p1->m_hash == p2.m_hash));
}

template <typename Key, typename Value>
void QxCollection<Key, Value>::updateHashPosition(long from /* = 0 */, long to /* = -1 */)
{
   if (m_batch) { return; }
   qAssert(m_list.size() == m_hash.size());
   if (to == -1) { to = (m_list.size() - 1); }
   if ((from < 0) || (to >= m_list.size()) || (from > to)) { return; }
   for (long idx = from; idx <= to; idx++)
   {
      const Key & key = m_list.at(idx).first;
      m_hash.insert(key, idx);
   }
}

template <typename Key, typename Value>
typename QxCollection<Key, Value>::iterator QxCollection<Key, Value>::begin()
{
   return m_list.begin();
}

template <typename Key, typename Value>
typename QxCollection<Key, Value>::iterator QxCollection<Key, Value>::end()
{
   return m_list.end();
}

template <typename Key, typename Value>
typename QxCollection<Key, Value>::const_iterator QxCollection<Key, Value>::begin() const
{
   return m_list.begin();
}

template <typename Key, typename Value>
typename QxCollection<Key, Value>::const_iterator QxCollection<Key, Value>::end() const
{
   return m_list.end();
}

#if (QT_VERSION >= 0x050600)

template <typename Key, typename Value>
typename QxCollection<Key, Value>::reverse_iterator QxCollection<Key, Value>::rbegin()
{
   return m_list.rbegin();
}

template <typename Key, typename Value>
typename QxCollection<Key, Value>::reverse_iterator QxCollection<Key, Value>::rend()
{
   return m_list.rend();
}

template <typename Key, typename Value>
typename QxCollection<Key, Value>::const_reverse_iterator QxCollection<Key, Value>::rbegin() const
{
   return m_list.rbegin();
}

template <typename Key, typename Value>
typename QxCollection<Key, Value>::const_reverse_iterator QxCollection<Key, Value>::rend() const
{
   return m_list.rend();
}

#endif // (QT_VERSION >= 0x050600)

template <typename Key, typename Value>
void QxCollection<Key, Value>::reserve(long size)
{
   qAssert(m_list.size() == m_hash.size());
   if (size <= 0) { return; }
   m_list.reserve(size);
   m_hash.reserve(size);
}

template <typename Key, typename Value>
void QxCollection<Key, Value>::reverse()
{
   qAssert(m_list.size() == m_hash.size());
   std::reverse(m_list.begin(), m_list.end());
   updateHashPosition();
}

template <typename Key, typename Value>
void QxCollection<Key, Value>::clear()
{
   m_hash.clear();
   m_list.clear();
}

template <typename Key, typename Value>
long QxCollection<Key, Value>::count() const
{
   qAssert(m_list.size() == m_hash.size());
   return static_cast<long>(m_list.size());
}

template <typename Key, typename Value>
long QxCollection<Key, Value>::size() const
{
   return this->count();
}

template <typename Key, typename Value>
bool QxCollection<Key, Value>::contains(const Key & key) const
{
   qAssert(m_list.size() == m_hash.size());
   return (m_hash.contains(key));
}

template <typename Key, typename Value>
bool QxCollection<Key, Value>::exist(const Key & key) const
{
   return this->contains(key);
}

template <typename Key, typename Value>
bool QxCollection<Key, Value>::empty() const
{
   qAssert(m_list.size() == m_hash.size());
   return m_list.isEmpty();
}

template <typename Key, typename Value>
bool QxCollection<Key, Value>::push_back(const Key & key, const Value & value)
{
   return this->insert(key, value);
}

template <typename Key, typename Value>
bool QxCollection<Key, Value>::push_front(const Key & key, const Value & value)
{
   return this->insert(0, key, value);
}

template <typename Key, typename Value>
bool QxCollection<Key, Value>::insert(const Key & key, const Value & value)
{
   qAssert(! exist(key));
   qAssert(m_list.size() == m_hash.size());
   m_list.append(qMakePair(key, value));
   m_hash.insert(key, (m_list.size() - 1));
   return true;
}

template <typename Key, typename Value>
bool QxCollection<Key, Value>::insert(long index, const Key & key, const Value & value)
{
   qAssert(! exist(key));
   if (index < 0) { index = 0; }
   if (index >= size()) { return this->insert(key, value); }
   qAssert(m_list.size() == m_hash.size());
   m_list.insert(index, qMakePair(key, value));
   m_hash.insert(key, index);
   updateHashPosition(index);
   return true;
}

template <typename Key, typename Value>
bool QxCollection<Key, Value>::insert(const QxCollection<Key, Value> & other)
{
   m_list.append(other.m_list);
   m_hash.unite(other.m_hash);
   updateHashPosition();
   qAssert(m_list.size() == m_hash.size());
   return true;
}

template <typename Key, typename Value>
bool QxCollection<Key, Value>::insert(long index, const QxCollection<Key, Value> & other)
{
   if (index < 0) { index = 0; }
   if ((index >= size()) && (index != 0)) { index = (size() - 1); }
   qAssert(m_list.size() == m_hash.size());
   m_batch = true;

   for (long l = 0; l < other.size(); l++)
   {
      const type_pair_key_value & pair = other.m_list.at(l);
      this->insert((index + l), pair.first, pair.second);
   }

   m_batch = false;
   updateHashPosition(index);
   return true;
}

template <typename Key, typename Value>
bool QxCollection<Key, Value>::replace(long index, const Key & key, const Value & value)
{
   qAssert(! exist(key));
   m_hash.remove(m_list.at(index).first);
   m_list.replace(index, qMakePair(key, value));
   m_hash.insert(key, index);
   qAssert(m_list.size() == m_hash.size());
   return true;
}

template <typename Key, typename Value>
bool QxCollection<Key, Value>::swap(long index1, long index2)
{
   if (index1 < 0 || index1 >= size()) { return false; }
   if (index2 < 0 || index2 >= size()) { return false; }
   if (index1 == index2) { return true; }
   const Key & key1 = m_list.at(index1).first;
   const Key & key2 = m_list.at(index2).first;
   m_hash.insert(key1, index2);
   m_hash.insert(key2, index1);
   m_list.swap(index1, index2);
   qAssert(m_list.size() == m_hash.size());
   return true;
}

template <typename Key, typename Value>
bool QxCollection<Key, Value>::move(long indexFrom, long indexTo)
{
   return swap(indexFrom, indexTo);
}

template <typename Key, typename Value>
bool QxCollection<Key, Value>::removeByKey(const Key & key)
{
   qAssert(exist(key));
   long pos = m_hash.value(key, -1);
   if ((pos < 0) || (pos >= m_list.size())) { return false; }
   qAssert(m_list.at(pos).first == key);
   m_hash.remove(key);
   m_list.removeAt(pos);
   updateHashPosition(pos);
   qAssert(m_list.size() == m_hash.size());
   return true;
}

template <typename Key, typename Value>
bool QxCollection<Key, Value>::removeByIndex(long index)
{
   if (index < 0 || index >= size()) { return false; }
   const Key & key = m_list.at(index).first;
   qAssert(m_hash.value(key, -1) == index);
   m_hash.remove(key);
   m_list.removeAt(index);
   updateHashPosition(index);
   qAssert(m_list.size() == m_hash.size());
   return true;
}

template <typename Key, typename Value>
bool QxCollection<Key, Value>::removeByIndex(long first, long last)
{
   if (first < 0 || first >= size()) { return false; }
   if (last < 0 || last >= size()) { return false; }
   if (first > last) { return false; }
   m_batch = true;
   for (long idx = first; idx <= last; idx++) { removeByIndex(idx); }
   m_batch = false;
   updateHashPosition(first);
   return true;
}

template <typename Key, typename Value>
bool QxCollection<Key, Value>::removeFirst()
{
   return this->removeByIndex(0);
}

template <typename Key, typename Value>
bool QxCollection<Key, Value>::removeLast()
{
   return this->removeByIndex(size() - 1);
}

template <typename Key, typename Value>
typename QxCollection<Key, Value>::const_reference_value QxCollection<Key, Value>::getByKey(const Key & key) const
{
   qAssert(exist(key));
   qAssert(m_list.size() == m_hash.size());
   const type_pair_key_value & pair = m_list.at(m_hash.value(key, -1));
   qAssert(pair.first == key);
   return pair.second;
}

template <typename Key, typename Value>
typename QxCollection<Key, Value>::const_reference_value QxCollection<Key, Value>::getByIndex(long index) const
{
   qAssert(m_list.size() == m_hash.size());
   qAssert((index >= 0) && (index < size()));
   qAssert(m_hash.value(m_list.at(index).first, -1) == index);
   return m_list.at(index).second;
}

template <typename Key, typename Value>
typename QxCollection<Key, Value>::const_reference_value QxCollection<Key, Value>::getFirst() const
{
   qAssert(! empty());
   qAssert(m_list.size() == m_hash.size());
   return m_list.at(0).second;
}

template <typename Key, typename Value>
typename QxCollection<Key, Value>::const_reference_value QxCollection<Key, Value>::getLast() const
{
   qAssert(! empty());
   qAssert(m_list.size() == m_hash.size());
   return m_list.at(m_list.size() - 1).second;
}

template <typename Key, typename Value>
typename QxCollection<Key, Value>::const_reference_key QxCollection<Key, Value>::getKeyByIndex(long index) const
{
   qAssert(m_list.size() == m_hash.size());
   qAssert((index >= 0) && (index < size()));
   qAssert(m_hash.value(m_list.at(index).first, -1) == index);
   return m_list.at(index).first;
}

template <typename Key, typename Value>
void QxCollection<Key, Value>::sortByKey(bool bAscending /* = true */)
{
   if (bAscending)   { std::sort(m_list.begin(), m_list.end(), (& compareKeyValue<std::is_pointer<Key>::value || qx::trait::is_smart_ptr<Key>::value, 0>::compareByKeyAscending)); }
   else              { std::sort(m_list.begin(), m_list.end(), (& compareKeyValue<std::is_pointer<Key>::value || qx::trait::is_smart_ptr<Key>::value, 0>::compareByKeyDescending)); }
   updateHashPosition();
   qAssert(m_list.size() == m_hash.size());
}

template <typename Key, typename Value>
void QxCollection<Key, Value>::sortByValue(bool bAscending /* = true */)
{
   if (bAscending)   { std::sort(m_list.begin(), m_list.end(), (& compareKeyValue<std::is_pointer<Value>::value || qx::trait::is_smart_ptr<Value>::value, 0>::compareByValueAscending)); }
   else              { std::sort(m_list.begin(), m_list.end(), (& compareKeyValue<std::is_pointer<Value>::value || qx::trait::is_smart_ptr<Value>::value, 0>::compareByValueDescending)); }
   updateHashPosition();
   qAssert(m_list.size() == m_hash.size());
}

} // namespace qx

template <typename Key, typename Value>
QDataStream & operator<< (QDataStream & stream, const qx::QxCollection<Key, Value> & t)
{
   long lCount = t.count();
   stream << (qint32)(lCount);

   for (long l = 0; l < lCount; l++)
   {
      stream << t.getKeyByIndex(l);
      stream << t.getByIndex(l);
   }

   return stream;
}

template <typename Key, typename Value>
QDataStream & operator>> (QDataStream & stream, qx::QxCollection<Key, Value> & t)
{
   qint32 lCount = 0;
   stream >> lCount;
   t.clear();
   t.reserve(lCount);

   for (qint32 l = 0; l < lCount; l++)
   {
      Key key;       stream >> key;
      Value value;   stream >> value;
      t.insert(key, value);
   }

   return stream;
}
