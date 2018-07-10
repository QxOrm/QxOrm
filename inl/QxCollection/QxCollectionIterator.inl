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
QxCollectionIterator<Key, Value>::QxCollectionIterator(const QxCollection<Key, Value> & col) : m_pCollection(& col), m_lCurrIndex(-1)
{
}

template <typename Key, typename Value>
QxCollectionIterator<Key, Value>::~QxCollectionIterator()
{
}

template <typename Key, typename Value>
inline const Key & QxCollectionIterator<Key, Value>::key() const
{
   qAssert(m_pCollection && (m_lCurrIndex >= 0) && (m_lCurrIndex < m_pCollection->size()));
   return m_pCollection->getKeyByIndex(m_lCurrIndex);
}

template <typename Key, typename Value>
inline const Value & QxCollectionIterator<Key, Value>::value() const
{
   qAssert(m_pCollection && (m_lCurrIndex >= 0) && (m_lCurrIndex < m_pCollection->size()));
   return m_pCollection->getByIndex(m_lCurrIndex);
}

template <typename Key, typename Value>
inline void QxCollectionIterator<Key, Value>::toFirst()
{
   m_lCurrIndex = -1;
}

template <typename Key, typename Value>
inline void QxCollectionIterator<Key, Value>::toLast()
{
   m_lCurrIndex = m_pCollection->size();
}

template <typename Key, typename Value>
inline bool QxCollectionIterator<Key, Value>::next()
{
   long lCurrIndex = m_lCurrIndex;
   m_lCurrIndex = ((m_lCurrIndex < (m_pCollection->size() - 1)) ? (m_lCurrIndex + 1) : m_lCurrIndex);
   return (m_lCurrIndex > lCurrIndex);
}

template <typename Key, typename Value>
inline bool QxCollectionIterator<Key, Value>::previous()
{
   long lCurrIndex = m_lCurrIndex;
   m_lCurrIndex = ((m_lCurrIndex > 0) ? (m_lCurrIndex - 1) : m_lCurrIndex);
   return (m_lCurrIndex < lCurrIndex);
}

} // namespace qx
