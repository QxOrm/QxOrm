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

#include <QxPrecompiled.h>

#include <QxCollection/QxCollection.h>
#include <QxCollection/QxCollectionIterator.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

IxCollection::~IxCollection() { ; }

namespace unit_test {

void qx_collection_unit_test()
{
   QxCollection<QString, QString *> obj;
   QxCollectionIterator<QString, QString *> itr(obj);

   obj.sortByKey();
   obj.sortByValue();

   typedef boost::tuple<QString, std::string, int> new_type;
   qx::QxCollection< new_type, boost::shared_ptr<QWidget> > objColTuple;
   objColTuple.begin();
   objColTuple.reserve(10);
   objColTuple.clear();
   objColTuple.count();
   objColTuple.empty();

   new_type t1 = boost::make_tuple("","",1);
   new_type t2 = boost::make_tuple("","",1);
}

} // namespace unit_test
} // namespace qx
