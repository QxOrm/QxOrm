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

#ifndef _QX_IS_CONTAINER_KEY_VALUE_H_
#define _QX_IS_CONTAINER_KEY_VALUE_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file is_container_key_value.h
 * \author Lionel Marty
 * \ingroup QxTraits
 * \brief qx::trait::is_container_key_value<T>::value : return true if T is a map or hash-map (with <Key, Value> template format) container from stl, boost, Qt or QxOrm library, otherwise return false
 */

#include <QxTraits/is_container.h>

namespace qx {
namespace trait {

/*!
 * \ingroup QxTraits
 * \brief qx::trait::is_container_key_value<T>::value : return true if T is a map or hash-map (with <Key, Value> template format) container from stl, boost, Qt or QxOrm library, otherwise return false
 */
template <typename T>
struct is_container_key_value : public std::false_type { ; };

#ifdef _QX_ENABLE_BOOST

template <typename Key, typename Value>
struct is_container_key_value< boost::unordered_map<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< boost::unordered_map<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< const boost::unordered_map<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< const boost::unordered_map<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< boost::unordered_multimap<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< boost::unordered_multimap<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< const boost::unordered_multimap<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< const boost::unordered_multimap<Key, Value> & > : public std::true_type { ; };

#endif // _QX_ENABLE_BOOST

template <typename Key, typename Value>
struct is_container_key_value< QHash<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< QHash<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< const QHash<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< const QHash<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< QMap<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< QMap<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< const QMap<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< const QMap<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< QMultiHash<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< QMultiHash<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< const QMultiHash<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< const QMultiHash<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< QMultiMap<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< QMultiMap<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< const QMultiMap<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< const QMultiMap<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< qx::QxCollection<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< qx::QxCollection<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< const qx::QxCollection<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< const qx::QxCollection<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< std::map<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< std::map<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< const std::map<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< const std::map<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< std::unordered_map<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< std::unordered_map<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< const std::unordered_map<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< const std::unordered_map<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< std::unordered_multimap<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< std::unordered_multimap<Key, Value> & > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< const std::unordered_multimap<Key, Value> > : public std::true_type { ; };

template <typename Key, typename Value>
struct is_container_key_value< const std::unordered_multimap<Key, Value> & > : public std::true_type { ; };

} // namespace trait
} // namespace qx

#endif // _QX_IS_CONTAINER_KEY_VALUE_H_
