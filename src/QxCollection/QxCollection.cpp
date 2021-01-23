/****************************************************************************
**
** https://www.qxorm.com/
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

#include <QxPrecompiled.h>

#include <QxCollection/QxCollection.h>
#include <QxCollection/QxCollectionIterator.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

IxCollection::~IxCollection() { ; }

namespace unit_test {

// Compilation option '_QX_HASH_NO_STD_NAMESPACE'
// Try to avoid compilation error, something like : error: no matching function for call to 'qHash(const std::tuple<...>&)'
// This is due to C++ ADL to resolve specialized functions : qHash(T) should be implemented in the same namespace as T
// For 'std' classes, it should be NOT allowed : the behavior of a C++ program is undefined if it adds declarations or definitions to namespace std or to a namespace within namespace std
// More details here : https://www.kdab.com/how-to-declare-a-qhash-overload/
// And here : https://stackoverflow.com/questions/47460098/using-standard-library-types-as-keys-in-qhash-or-qset
void qx_collection_unit_test()
{
   {
      QxCollection<QString, QString *> coll;
      QxCollectionIterator<QString, QString *> itr(coll);
      coll.sortByKey(); coll.sortByValue(); itr.toFirst();
   }

   {
      typedef std::tuple<QString, std::string, int> type_std_tuple;
      qx::QxCollection< type_std_tuple, std::shared_ptr<QWidget> > coll;
      coll.begin(); coll.reserve(10); coll.clear(); coll.count(); coll.empty();

      type_std_tuple item = std::make_tuple(QString(), std::string(), 1);
      coll.contains(item);
   }

   {
      typedef std::pair<QString, std::string> type_std_pair;
      qx::QxCollection< type_std_pair, std::shared_ptr<QWidget> > coll;
      coll.begin(); coll.reserve(10); coll.clear(); coll.count(); coll.empty();

      type_std_pair item = std::make_pair(QString(), std::string("1"));
      coll.contains(item);
   }

   {
      typedef QPair<QDateTime, std::string> type_qt_pair;
      qx::QxCollection< type_qt_pair, std::shared_ptr<QWidget> > coll;
      coll.begin(); coll.reserve(10); coll.clear(); coll.count(); coll.empty();

      type_qt_pair item = qMakePair(QDateTime(), std::string("1"));
      coll.contains(item);
   }

#ifdef _QX_ENABLE_BOOST
   {
      typedef boost::tuple<QString, std::string, int> type_boost_tuple;
      qx::QxCollection< type_boost_tuple, std::shared_ptr<QWidget> > coll;
      coll.begin(); coll.reserve(10); coll.clear(); coll.count(); coll.empty();

      type_boost_tuple item = boost::make_tuple(QString(), std::string(), 1);
      coll.contains(item);
   }
#endif // _QX_ENABLE_BOOST
}

} // namespace unit_test
} // namespace qx
