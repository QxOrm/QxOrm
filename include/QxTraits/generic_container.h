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

#ifndef _QX_GENERIC_CONTAINER_H_
#define _QX_GENERIC_CONTAINER_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file generic_container.h
 * \author Lionel Marty
 * \ingroup QxTraits
 * \brief qx::trait::generic_container<T> : provide some tools to manage all containers without knowing its type
 */

#include <QxTraits/is_smart_ptr.h>
#include <QxTraits/remove_attr.h>
#include <QxTraits/remove_smart_ptr.h>
#include <QxTraits/construct_ptr.h>

namespace qx {
namespace trait {

class no_type
{ private: void dummy() const { ; } };

/*!
 * \ingroup QxTraits
 * \brief qx::trait::generic_container<T> : provide some tools to manage all containers without knowing its type
 */
template <class T>
struct generic_container
{ typedef no_type type_item; typedef no_type type_key; typedef no_type type_value; typedef no_type type_value_qx; typedef no_type type_iterator; };

template <typename Key, typename Value>
struct generic_container_item
{

   typedef Key type_key;
   typedef Value type_value;
   typedef typename qx::trait::remove_attr<Value>::type type_value_qx_tmp;
   typedef typename qx::trait::remove_smart_ptr<type_value_qx_tmp>::type type_value_qx;

   enum { is_key_pointer = (std::is_pointer<type_key>::value || qx::trait::is_smart_ptr<type_key>::value) };
   enum { is_value_pointer = (std::is_pointer<type_value>::value || qx::trait::is_smart_ptr<type_value>::value) };

private:

   std::pair<type_key, type_value> m_pair;

public:

   generic_container_item() { ; }
   generic_container_item(const Key & key, const Value & value) { m_pair = std::make_pair(key, value); }
   ~generic_container_item() { ; }

   inline type_key & key()                         { return m_pair.first; }
   inline type_value & value()                     { return m_pair.second; }
   inline const type_key & key() const             { return m_pair.first; }
   inline const type_value & value() const         { return m_pair.second; }
   inline type_value_qx & value_qx()               { return value_qx_Helper<is_value_pointer, type_value, type_value_qx, 0>::get(m_pair.second); }
   inline const type_value_qx & value_qx() const   { return value_qx_Helper<is_value_pointer, type_value, type_value_qx, 0>::get(m_pair.second); }

   inline void key(const Key & key)                { m_pair.first = key; }
   inline void value(const Value & value)          { m_pair.second = value; }

   static inline type_key newKey()     { return new_Helper<is_key_pointer, type_key, 0>::get(); }
   static inline type_value newValue() { return new_Helper<is_value_pointer, type_value, 0>::get(); }

private:

   template <bool bIsPointer /* = true */, typename T, int dummy>
   struct new_Helper
   { static inline T get() { T t; qx::trait::construct_ptr<T>::get(t); return t; } };

   template <typename T, int dummy>
   struct new_Helper<false, T, dummy>
   { static inline T get() { return T(); } };

   template <bool bIsPointer /* = true */, typename T, typename U, int dummy>
   struct value_qx_Helper
   { static inline U & get(T & t) { return (* t); } };

   template <typename T, typename U, int dummy>
   struct value_qx_Helper<false, T, U, dummy>
   { static inline U & get(T & t) { return t; } };

};

} // namespace trait
} // namespace qx

#define QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(TypeContainer, TypeKey, TypeValue) \
typedef qx::trait::generic_container_item< TypeKey, TypeValue > type_item; \
typedef typename type_item::type_key type_key; \
typedef typename type_item::type_value type_value; \
typedef typename type_item::type_value_qx type_value_qx; \
typedef typename TypeContainer::iterator type_iterator;

namespace qx {
namespace trait {
namespace detail {

template <typename Container, typename Item>
struct generic_container_base
{

   QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(Container, qx::trait::no_type, Item)

   static inline long size(const Container & t)                      { return static_cast<long>(t.size()); }
   static inline void clear(Container & t)                           { t.clear(); }
   static inline void reserve(Container & t, long l)                 { t.reserve(l); }
   static inline type_item createItem()                              { return type_item(type_item::newKey(), type_item::newValue()); }
   static inline Item * insertItem(Container & t, type_item & item)  { t.push_back(item.value()); return (& t.back()); }
   static inline type_iterator end(Container & t)                    { return t.end(); }

   static inline type_iterator begin(Container & t, type_item & item)
   { if (t.size() <= 0) { return t.end(); }; item.value(* t.begin()); return t.begin(); }

   static inline type_iterator next(Container & t, type_iterator itr, type_item & item)
   { itr++; if (itr == t.end()) { return t.end(); }; item.value(* itr); return itr; }

};

template <typename Container, typename Item>
struct generic_container_base_without_reserve
{

   QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(Container, qx::trait::no_type, Item)

   static inline long size(const Container & t)                      { return static_cast<long>(t.size()); }
   static inline void clear(Container & t)                           { t.clear(); }
   static inline void reserve(Container & t, long l)                 { Q_UNUSED(t); Q_UNUSED(l); }
   static inline type_item createItem()                              { return type_item(type_item::newKey(), type_item::newValue()); }
   static inline Item * insertItem(Container & t, type_item & item)  { t.push_back(item.value()); return (& t.back()); }
   static inline type_iterator end(Container & t)                    { return t.end(); }

   static inline type_iterator begin(Container & t, type_item & item)
   { if (t.size() <= 0) { return t.end(); }; item.value(* t.begin()); return t.begin(); }

   static inline type_iterator next(Container & t, type_iterator itr, type_item & item)
   { itr++; if (itr == t.end()) { return t.end(); }; item.value(* itr); return itr; }

};

template <typename Container, typename Item>
struct generic_container_base_set
{

   QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(Container, qx::trait::no_type, Item)

   static inline long size(const Container & t)                      { return static_cast<long>(t.size()); }
   static inline void clear(Container & t)                           { t.clear(); }
   static inline void reserve(Container & t, long l)                 { Q_UNUSED(t); Q_UNUSED(l); }
   static inline type_item createItem()                              { return type_item(type_item::newKey(), type_item::newValue()); }
   static inline Item * insertItem(Container & t, type_item & item)  { return const_cast<Item *>(& (* (t.insert(item.value()).first))); }
   static inline type_iterator end(Container & t)                    { return t.end(); }

   static inline type_iterator begin(Container & t, type_item & item)
   { if (t.size() <= 0) { return t.end(); }; item.value(* t.begin()); return t.begin(); }

   static inline type_iterator next(Container & t, type_iterator itr, type_item & item)
   { itr++; if (itr == t.end()) { return t.end(); }; item.value(* itr); return itr; }

};

template <typename Container, typename Item>
struct generic_container_base_multi_set
{

   QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(Container, qx::trait::no_type, Item)

   static inline long size(const Container & t)                      { return static_cast<long>(t.size()); }
   static inline void clear(Container & t)                           { t.clear(); }
   static inline void reserve(Container & t, long l)                 { Q_UNUSED(t); Q_UNUSED(l); }
   static inline type_item createItem()                              { return type_item(type_item::newKey(), type_item::newValue()); }
   static inline Item * insertItem(Container & t, type_item & item)  { return const_cast<Item *>(& (* (t.insert(item.value())))); }
   static inline type_iterator end(Container & t)                    { return t.end(); }

   static inline type_iterator begin(Container & t, type_item & item)
   { if (t.size() <= 0) { return t.end(); }; item.value(* t.begin()); return t.begin(); }

   static inline type_iterator next(Container & t, type_iterator itr, type_item & item)
   { itr++; if (itr == t.end()) { return t.end(); }; item.value(* itr); return itr; }

};

template <typename Container, typename Key, typename Value>
struct generic_container_base_key_value_std_style
{

   QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(Container, Key, Value)

   static inline long size(const Container & t)                      { return static_cast<long>(t.size()); }
   static inline void clear(Container & t)                           { t.clear(); }
   static inline void reserve(Container & t, long l)                 { t.reserve(l); }
   static inline type_item createItem()                              { return type_item(type_item::newKey(), type_item::newValue()); }
   static inline Value * insertItem(Container & t, type_item & item) { return (& (t.insert(std::make_pair(item.key(), item.value())).first->second)); }
   static inline type_iterator end(Container & t)                    { return t.end(); }

   static inline type_iterator begin(Container & t, type_item & item)
   { if (t.size() <= 0) { return t.end(); }; item.value(* t.begin().second); item.key(* t.begin().first); return t.begin(); }

   static inline type_iterator next(Container & t, type_iterator itr, type_item & item)
   { itr++; if (itr == t.end()) { return t.end(); }; item.value(* itr.second); item.key(* itr.first); return itr; }

};

template <typename Container, typename Key, typename Value>
struct generic_container_base_key_value_multi_std_style
{

   QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(Container, Key, Value)

   static inline long size(const Container & t)                      { return static_cast<long>(t.size()); }
   static inline void clear(Container & t)                           { t.clear(); }
   static inline void reserve(Container & t, long l)                 { t.reserve(l); }
   static inline type_item createItem()                              { return type_item(type_item::newKey(), type_item::newValue()); }
   static inline Value * insertItem(Container & t, type_item & item) { return (& (t.insert(std::make_pair(item.key(), item.value()))->second)); }
   static inline type_iterator end(Container & t)                    { return t.end(); }

   static inline type_iterator begin(Container & t, type_item & item)
   { if (t.size() <= 0) { return t.end(); }; item.value(* t.begin().second); item.key(* t.begin().first); return t.begin(); }

   static inline type_iterator next(Container & t, type_iterator itr, type_item & item)
   { itr++; if (itr == t.end()) { return t.end(); }; item.value(* itr.second); item.key(* itr.first); return itr; }

};

template <typename Container, typename Key, typename Value>
struct generic_container_base_key_value_qt_style
{

   QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(Container, Key, Value)

   static inline long size(const Container & t)                      { return static_cast<long>(t.size()); }
   static inline void clear(Container & t)                           { t.clear(); }
   static inline void reserve(Container & t, long l)                 { t.reserve(l); }
   static inline type_item createItem()                              { return type_item(type_item::newKey(), type_item::newValue()); }
   static inline Value * insertItem(Container & t, type_item & item) { return (& (t.insert(item.key(), item.value()).value())); }
   static inline type_iterator end(Container & t)                    { return t.end(); }

   static inline type_iterator begin(Container & t, type_item & item)
   { if (t.size() <= 0) { return t.end(); }; item.value(* t.begin().value()); item.key(* t.begin().key()); return t.begin(); }

   static inline type_iterator next(Container & t, type_iterator itr, type_item & item)
   { itr++; if (itr == t.end()) { return t.end(); }; item.value(* itr.value()); item.key(* itr.key()); return itr; }

};

} // namespace detail

template <typename T>
struct generic_container< std::vector<T> > : public qx::trait::detail::generic_container_base< std::vector<T>, T >
{ QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(QX_TEMPLATE_T_P1(std::vector, T), qx::trait::no_type, T) };

template <typename T>
struct generic_container< std::list<T> > : public qx::trait::detail::generic_container_base_without_reserve< std::list<T>, T >
{ QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(QX_TEMPLATE_T_P1(std::list, T), qx::trait::no_type, T) };

template <typename T>
struct generic_container< std::set<T> > : public qx::trait::detail::generic_container_base_set< std::set<T>, T >
{ QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(QX_TEMPLATE_T_P1(std::set, T), qx::trait::no_type, T) };

template <typename Key, typename Value>
struct generic_container< std::map<Key, Value> > : public qx::trait::detail::generic_container_base_key_value_std_style< std::map<Key, Value>, Key, Value >
{ QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(QX_TEMPLATE_T_P1_P2(std::map, Key, Value), Key, Value) };

#ifdef _QX_ENABLE_BOOST

template <typename T>
struct generic_container< boost::unordered_set<T> > : public qx::trait::detail::generic_container_base_set< boost::unordered_set<T>, T >
{ QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(QX_TEMPLATE_T_P1(boost::unordered_set, T), qx::trait::no_type, T) };

template <typename T>
struct generic_container< boost::unordered_multiset<T> > : public qx::trait::detail::generic_container_base_multi_set< boost::unordered_multiset<T>, T >
{ QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(QX_TEMPLATE_T_P1(boost::unordered_multiset, T), qx::trait::no_type, T) };

template <typename Key, typename Value>
struct generic_container< boost::unordered_map<Key, Value> > : public qx::trait::detail::generic_container_base_key_value_std_style< boost::unordered_map<Key, Value>, Key, Value >
{ QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(QX_TEMPLATE_T_P1_P2(boost::unordered_map, Key, Value), Key, Value) };

template <typename Key, typename Value>
struct generic_container< boost::unordered_multimap<Key, Value> > : public qx::trait::detail::generic_container_base_key_value_multi_std_style< boost::unordered_multimap<Key, Value>, Key, Value >
{ QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(QX_TEMPLATE_T_P1_P2(boost::unordered_multimap, Key, Value), Key, Value) };

#endif // _QX_ENABLE_BOOST

template <typename T>
struct generic_container< std::unordered_set<T> > : public qx::trait::detail::generic_container_base_set< std::unordered_set<T>, T >
{ QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(QX_TEMPLATE_T_P1(std::unordered_set, T), qx::trait::no_type, T) };

template <typename T>
struct generic_container< std::unordered_multiset<T> > : public qx::trait::detail::generic_container_base_multi_set< std::unordered_multiset<T>, T >
{ QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(QX_TEMPLATE_T_P1(std::unordered_multiset, T), qx::trait::no_type, T) };

template <typename Key, typename Value>
struct generic_container< std::unordered_map<Key, Value> > : public qx::trait::detail::generic_container_base_key_value_std_style< std::unordered_map<Key, Value>, Key, Value >
{ QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(QX_TEMPLATE_T_P1_P2(std::unordered_map, Key, Value), Key, Value) };

template <typename Key, typename Value>
struct generic_container< std::unordered_multimap<Key, Value> > : public qx::trait::detail::generic_container_base_key_value_multi_std_style< std::unordered_multimap<Key, Value>, Key, Value >
{ QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(QX_TEMPLATE_T_P1_P2(std::unordered_multimap, Key, Value), Key, Value) };

template <typename T>
struct generic_container< QVector<T> > : public qx::trait::detail::generic_container_base< QVector<T>, T >
{ QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(QX_TEMPLATE_T_P1(QVector, T), qx::trait::no_type, T) };

#if (QT_VERSION >= 0x040700)

template <typename T>
struct generic_container< QList<T> > : public qx::trait::detail::generic_container_base< QList<T>, T >
{ QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(QX_TEMPLATE_T_P1(QList, T), qx::trait::no_type, T) };

#else // (QT_VERSION >= 0x040700)

template <typename T>
struct generic_container< QList<T> > : public qx::trait::detail::generic_container_base_without_reserve< QList<T>, T >
{ QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(QX_TEMPLATE_T_P1(QList, T), qx::trait::no_type, T) };

#endif // (QT_VERSION >= 0x040700)

template <typename T>
struct generic_container< QLinkedList<T> > : public qx::trait::detail::generic_container_base_without_reserve< QLinkedList<T>, T >
{ QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(QX_TEMPLATE_T_P1(QLinkedList, T), qx::trait::no_type, T) };

template <typename T>
struct generic_container< QSet<T> > : public qx::trait::detail::generic_container_base_multi_set< QSet<T>, T >
{ QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(QX_TEMPLATE_T_P1(QSet, T), qx::trait::no_type, T) };

template <typename Key, typename Value>
struct generic_container< QMap<Key, Value> > : public qx::trait::detail::generic_container_base_key_value_qt_style< QMap<Key, Value>, Key, Value >
{ QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(QX_TEMPLATE_T_P1_P2(QMap, Key, Value), Key, Value) };

template <typename Key, typename Value>
struct generic_container< QMultiMap<Key, Value> > : public qx::trait::detail::generic_container_base_key_value_qt_style< QMultiMap<Key, Value>, Key, Value >
{ QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(QX_TEMPLATE_T_P1_P2(QMultiMap, Key, Value), Key, Value) };

template <typename Key, typename Value>
struct generic_container< QHash<Key, Value> > : public qx::trait::detail::generic_container_base_key_value_qt_style< QHash<Key, Value>, Key, Value >
{ QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(QX_TEMPLATE_T_P1_P2(QHash, Key, Value), Key, Value) };

template <typename Key, typename Value>
struct generic_container< QMultiHash<Key, Value> > : public qx::trait::detail::generic_container_base_key_value_qt_style< QMultiHash<Key, Value>, Key, Value >
{ QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(QX_TEMPLATE_T_P1_P2(QMultiHash, Key, Value), Key, Value) };

template <typename Key, typename Value>
struct generic_container< qx::QxCollection<Key, Value> >
{

   QX_TRAIT_GENERIC_CONTAINER_TYPEDEF(QX_TEMPLATE_T_P1_P2(qx::QxCollection, Key, Value), Key, Value)

   static inline long size(const qx::QxCollection<Key, Value> & t)                        { return static_cast<long>(t.size()); }
   static inline void clear(qx::QxCollection<Key, Value> & t)                             { t.clear(); }
   static inline void reserve(qx::QxCollection<Key, Value> & t, long l)                   { t.reserve(l); }
   static inline type_item createItem()                                                   { return type_item(type_item::newKey(), type_item::newValue()); }
   static inline Value * insertItem(qx::QxCollection<Key, Value> & t, type_item & item)   { t.insert(item.key(), item.value()); return const_cast<Value *>(& t.getByKey(item.key())); }
   static inline type_iterator end(qx::QxCollection<Key, Value> & t)                      { return t.end(); }

   static inline type_iterator begin(qx::QxCollection<Key, Value> & t, type_item & item)
   { if (t.size() <= 0) { return t.end(); }; item.value(t.getByIndex(0)); item.key(t.getKeyByIndex(0)); return t.begin(); }

   static inline type_iterator next(qx::QxCollection<Key, Value> & t, type_iterator itr, type_item & item)
   { itr++; if (itr == t.end()) { return t.end(); }; long l = (itr - t.begin()); item.value(t.getByIndex(l)); item.key(t.getKeyByIndex(l)); return itr; }

};

} // namespace trait
} // namespace qx

#endif // _QX_GENERIC_CONTAINER_H_
