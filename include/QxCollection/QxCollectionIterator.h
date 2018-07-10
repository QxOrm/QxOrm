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

#ifndef _QX_COLLECTION_ITERATOR_H_
#define _QX_COLLECTION_ITERATOR_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/noncopyable.hpp>

#include "../../include/QxCollection/QxCollection.h"

namespace qx {

template <typename Key, typename Value>
class QxCollectionIterator : private boost::noncopyable
{

private:

   const QxCollection<Key, Value> * m_pCollection;    // Collection to iterate
   long m_lCurrIndex;                                 // Current index (position) in the collection

public:

   QxCollectionIterator(const QxCollection<Key, Value> & col);
   ~QxCollectionIterator();

   inline const Key & key() const;
   inline const Value & value() const;

   inline void toFirst();
   inline void toLast();

   inline bool next();
   inline bool previous();

};

} // namespace qx

#include "../../inl/QxCollection/QxCollectionIterator.inl"

#endif // _QX_COLLECTION_ITERATOR_H_
