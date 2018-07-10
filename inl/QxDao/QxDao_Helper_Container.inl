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

#define QX_DAO_HELPER_CONTAINER(className) \
namespace qx { namespace dao { namespace detail { \
template <class T> \
class QxDao_Helper_Container< className<T> > : public IxDao_Helper \
{ \
public: \
   QxDao_Helper_Container(className<T> & t, QSqlDatabase * pDatabase, const QString & sContext, qx::IxSqlQueryBuilder * pBuilder) : IxDao_Helper(pBuilder) { Q_UNUSED(t); init(pDatabase, sContext); } \
   virtual ~QxDao_Helper_Container() { static_assert(qx::trait::is_qx_registered<typename qx::QxSqlQueryBuilder<T>::type_sql>::value, "qx::trait::is_qx_registered<typename qx::QxSqlQueryBuilder<T>::type_sql>::value"); } \
}; }}} // namespace qx::dao::detail

#define QX_DAO_HELPER_CONTAINER_KEY_VALUE(className) \
namespace qx { namespace dao { namespace detail { \
template <class Key, class Value> \
class QxDao_Helper_Container< className<Key, Value> > : public IxDao_Helper \
{ \
public: \
   QxDao_Helper_Container(className<Key, Value> & t, QSqlDatabase * pDatabase, const QString & sContext, qx::IxSqlQueryBuilder * pBuilder) : IxDao_Helper(pBuilder) { Q_UNUSED(t); init(pDatabase, sContext); } \
   virtual ~QxDao_Helper_Container() { static_assert(qx::trait::is_qx_registered<typename qx::QxSqlQueryBuilder<Value>::type_sql>::value, "qx::trait::is_qx_registered<typename qx::QxSqlQueryBuilder<Value>::type_sql>::value"); } \
}; }}} // namespace qx::dao::detail

namespace qx {
namespace dao {
namespace detail {

template <class T>
struct QxDao_Helper_Container { ; };

} // namespace detail
} // namespace dao
} // namespace qx

QX_DAO_HELPER_CONTAINER(std::vector)
QX_DAO_HELPER_CONTAINER(std::list)
QX_DAO_HELPER_CONTAINER(std::set)
QX_DAO_HELPER_CONTAINER_KEY_VALUE(std::map)

#ifdef _QX_ENABLE_BOOST

QX_DAO_HELPER_CONTAINER(boost::unordered_set)
QX_DAO_HELPER_CONTAINER(boost::unordered_multiset)
QX_DAO_HELPER_CONTAINER_KEY_VALUE(boost::unordered_map)
QX_DAO_HELPER_CONTAINER_KEY_VALUE(boost::unordered_multimap)

#endif // _QX_ENABLE_BOOST

QX_DAO_HELPER_CONTAINER(std::unordered_set)
QX_DAO_HELPER_CONTAINER(std::unordered_multiset)
QX_DAO_HELPER_CONTAINER_KEY_VALUE(std::unordered_map)
QX_DAO_HELPER_CONTAINER_KEY_VALUE(std::unordered_multimap)

QX_DAO_HELPER_CONTAINER(QVector)
QX_DAO_HELPER_CONTAINER(QList)
QX_DAO_HELPER_CONTAINER(QLinkedList)
QX_DAO_HELPER_CONTAINER(QSet)
QX_DAO_HELPER_CONTAINER_KEY_VALUE(QMap)
QX_DAO_HELPER_CONTAINER_KEY_VALUE(QMultiMap)
QX_DAO_HELPER_CONTAINER_KEY_VALUE(QHash)
QX_DAO_HELPER_CONTAINER_KEY_VALUE(QMultiHash)

QX_DAO_HELPER_CONTAINER_KEY_VALUE(qx::QxCollection)
