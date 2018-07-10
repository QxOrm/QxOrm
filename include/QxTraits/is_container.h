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

#ifndef _QX_IS_CONTAINER_H_
#define _QX_IS_CONTAINER_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file is_container.h
 * \author Lionel Marty
 * \ingroup QxTraits
 * \brief qx::trait::is_container<T>::value : return true if T is a container from stl, boost, Qt or QxOrm library, otherwise return false
 */

#include <QxTraits/is_boost_unordered_map.h>
#include <QxTraits/is_boost_unordered_set.h>
#include <QxTraits/is_qt_hash.h>
#include <QxTraits/is_qt_linked_list.h>
#include <QxTraits/is_qt_list.h>
#include <QxTraits/is_qt_map.h>
#include <QxTraits/is_qt_multi_hash.h>
#include <QxTraits/is_qt_multi_map.h>
#include <QxTraits/is_qt_set.h>
#include <QxTraits/is_qt_vector.h>
#include <QxTraits/is_qx_collection.h>
#include <QxTraits/is_std_list.h>
#include <QxTraits/is_std_map.h>
#include <QxTraits/is_std_set.h>
#include <QxTraits/is_std_vector.h>
#include <QxTraits/is_std_unordered_map.h>
#include <QxTraits/is_std_unordered_set.h>

#include <QxCollection/QxCollection.h>

namespace qx {
namespace trait {

/*!
 * \ingroup QxTraits
 * \brief qx::trait::is_container<T>::value : return true if T is a container from stl, boost, Qt or QxOrm library, otherwise return false
 */
template <typename T>
struct is_container : public std::false_type { ; };

#ifdef _QX_ENABLE_BOOST

template <typename Key, typename Value>
struct is_container< boost::unordered_map<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< boost::unordered_map<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< const boost::unordered_map<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< const boost::unordered_map<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< boost::unordered_multimap<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< boost::unordered_multimap<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< const boost::unordered_multimap<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< const boost::unordered_multimap<Key, Value> & > : public std::true_type { ; };

template <typename T>
struct is_container< boost::unordered_set<T> > : public std::true_type { ; };

template <typename T>
struct is_container< boost::unordered_set<T> & > : public std::true_type { ; };

template <typename T>
struct is_container< const boost::unordered_set<T> > : public std::true_type { ; };

template <typename T>
struct is_container< const boost::unordered_set<T> & > : public std::true_type { ; };

template <typename T>
struct is_container< boost::unordered_multiset<T> > : public std::true_type { ; };

template <typename T>
struct is_container< boost::unordered_multiset<T> & > : public std::true_type { ; };

template <typename T>
struct is_container< const boost::unordered_multiset<T> > : public std::true_type { ; };

template <typename T>
struct is_container< const boost::unordered_multiset<T> & > : public std::true_type { ; };

#endif // _QX_ENABLE_BOOST

template <typename Key, typename Value>
struct is_container< QHash<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< QHash<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< const QHash<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< const QHash<Key, Value> & > : public std::true_type { ; };

template <typename T>
struct is_container< QLinkedList<T> > : public std::true_type { ; };

template <typename T>
struct is_container< QLinkedList<T> & > : public std::true_type { ; };

template <typename T>
struct is_container< const QLinkedList<T> > : public std::true_type { ; };

template <typename T>
struct is_container< const QLinkedList<T> & > : public std::true_type { ; };

template <typename T>
struct is_container< QList<T> > : public std::true_type { ; };

template <typename T>
struct is_container< QList<T> & > : public std::true_type { ; };

template <typename T>
struct is_container< const QList<T> > : public std::true_type { ; };

template <typename T>
struct is_container< const QList<T> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< QMap<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< QMap<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< const QMap<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< const QMap<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< QMultiHash<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< QMultiHash<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< const QMultiHash<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< const QMultiHash<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< QMultiMap<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< QMultiMap<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< const QMultiMap<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< const QMultiMap<Key, Value> & > : public std::true_type { ; };

template <typename T>
struct is_container< QSet<T> > : public std::true_type { ; };

template <typename T>
struct is_container< QSet<T> & > : public std::true_type { ; };

template <typename T>
struct is_container< const QSet<T> > : public std::true_type { ; };

template <typename T>
struct is_container< const QSet<T> & > : public std::true_type { ; };

template <typename T>
struct is_container< QVector<T> > : public std::true_type { ; };

template <typename T>
struct is_container< QVector<T> & > : public std::true_type { ; };

template <typename T>
struct is_container< const QVector<T> > : public std::true_type { ; };

template <typename T>
struct is_container< const QVector<T> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< qx::QxCollection<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< qx::QxCollection<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< const qx::QxCollection<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< const qx::QxCollection<Key, Value> & > : public std::true_type { ; };

template <typename T>
struct is_container< std::list<T> > : public std::true_type { ; };

template <typename T>
struct is_container< std::list<T> & > : public std::true_type { ; };

template <typename T>
struct is_container< const std::list<T> > : public std::true_type { ; };

template <typename T>
struct is_container< const std::list<T> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< std::map<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< std::map<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< const std::map<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< const std::map<Key, Value> & > : public std::true_type { ; };

template <typename T>
struct is_container< std::set<T> > : public std::true_type { ; };

template <typename T>
struct is_container< std::set<T> & > : public std::true_type { ; };

template <typename T>
struct is_container< const std::set<T> > : public std::true_type { ; };

template <typename T>
struct is_container< const std::set<T> & > : public std::true_type { ; };

template <typename T>
struct is_container< std::vector<T> > : public std::true_type { ; };

template <typename T>
struct is_container< std::vector<T> & > : public std::true_type { ; };

template <typename T>
struct is_container< const std::vector<T> > : public std::true_type { ; };

template <typename T>
struct is_container< const std::vector<T> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< std::unordered_map<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< std::unordered_map<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< const std::unordered_map<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< const std::unordered_map<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< std::unordered_multimap<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< std::unordered_multimap<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< const std::unordered_multimap<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container< const std::unordered_multimap<Key, Value> & > : public std::true_type { ; };

template <typename T>
struct is_container< std::unordered_set<T> > : public std::true_type { ; };

template <typename T>
struct is_container< std::unordered_set<T> & > : public std::true_type { ; };

template <typename T>
struct is_container< const std::unordered_set<T> > : public std::true_type { ; };

template <typename T>
struct is_container< const std::unordered_set<T> & > : public std::true_type { ; };

template <typename T>
struct is_container< std::unordered_multiset<T> > : public std::true_type { ; };

template <typename T>
struct is_container< std::unordered_multiset<T> & > : public std::true_type { ; };

template <typename T>
struct is_container< const std::unordered_multiset<T> > : public std::true_type { ; };

template <typename T>
struct is_container< const std::unordered_multiset<T> & > : public std::true_type { ; };

} // namespace trait
} // namespace qx

#endif // _QX_IS_CONTAINER_H_
