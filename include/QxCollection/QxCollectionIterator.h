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

#ifndef _QX_COLLECTION_ITERATOR_H_
#define _QX_COLLECTION_ITERATOR_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxCollectionIterator.h
 * \author Lionel Marty
 * \ingroup QxCollection
 * \brief Java-style iterator to iterate over a qx::QxCollection<Key, Value> container
 */

#include <QxCollection/QxCollection.h>

namespace qx {

/*!
 * \ingroup QxCollection
 * \brief qx::QxCollectionIterator : Java-style iterator to iterate over a qx::QxCollection<Key, Value> container
 *
 * Quick sample using qx::QxCollectionIterator Java-style iterator :
 * \code
// iterate over a drugs container using 'qx::QxCollectionIterator' Java-style iterator
qx::QxCollectionIterator<QString, drug_ptr> itr(lstDrugs);
while (itr.next())
{
   QString code = itr.key();
   qDebug() << qPrintable(itr.value()->name) << " " << qPrintable(itr.value()->desc);
}
 * \endcode
 */
template <typename Key, typename Value>
class QxCollectionIterator
{

private:

   const QxCollection<Key, Value> * m_pCollection;    //!< Collection to iterate over
   long m_lCurrIndex;                                 //!< Current index (position) in the collection

public:

   QxCollectionIterator(const QxCollection<Key, Value> & col);    //!< Construct an iterator for traversing the collection. The iterator is set to be at the front of the list (before the first item)
   ~QxCollectionIterator();                                       //!< Destroy the iterator

   inline const Key & key() const;        //!< Return the 'key' at current position
   inline const Value & value() const;    //!< Return the 'value' at current position

   inline void toFirst();                 //!< Move the iterator to the front of the container (before the first item)
   inline void toLast();                  //!< Move the iterator to the back of the container (after the last item)

   inline bool next();                    //!< Advance the iterator by one position. Return 'true' if there is at least one item ahead of the iterator, i.e. the iterator is not at the back of the container; otherwise return 'false'
   inline bool previous();                //!< Move the iterator back by one position. Return 'true' if there is at least one item behind the iterator, i.e. the iterator is not at the front of the container; otherwise return 'false'

private:

   QxCollectionIterator(const QxCollectionIterator & other) { Q_UNUSED(other); }
   QxCollectionIterator & operator=(const QxCollectionIterator & other) { Q_UNUSED(other); return (* this); }

};

} // namespace qx

#include "../../inl/QxCollection/QxCollectionIterator.inl"

#endif // _QX_COLLECTION_ITERATOR_H_
