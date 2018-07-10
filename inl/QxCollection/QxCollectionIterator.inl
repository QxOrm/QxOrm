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

namespace qx {

template <typename Key, typename Value>
QxCollectionIterator<Key, Value>::QxCollectionIterator(const QxCollection<Key, Value> & col) : boost::noncopyable(), m_pCollection(& col), m_lCurrIndex(-1)
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
