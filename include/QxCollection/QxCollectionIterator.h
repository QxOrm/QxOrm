/****************************************************************************
**
** Copyright (C) 2010 QxOrm France and/or its subsidiary(-ies)
** Contact: QxOrm France Information (contact@qxorm.com)
**
** This file is part of the QxOrm library
**
** Commercial Usage
** Licensees holding valid QxOrm Commercial licenses may use this file in
** accordance with the QxOrm Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and QxOrm France
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file 'license.gpl3.txt' included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html
**
** If you are unsure which license is appropriate for your use, please
** contact the support department at support@qxorm.com
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
