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

#ifndef _IX_DATA_MEMBER_X_H_
#define _IX_DATA_MEMBER_X_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QxDataMember/IxDataMember.h>

#include <QxCollection/QxCollection.h>

#define QX_TABLE_PER_CLASS       1
#define QX_TABLE_PER_HIERARCHY   2

namespace qx {

class IxClass;

class QX_DLL_EXPORT IxDataMemberX
{

protected:

   QxCollection<QString, IxDataMember *> m_lstDataMember;   // Collection of 'IxDataMember'
   IxClass * m_pClass;                                      // Class definition

protected:

   IxDataMemberX() : m_pClass(NULL) { ; }
   virtual ~IxDataMemberX() { deleteAllIxDataMember(); }

public:

   inline IxClass * getClass() const   { return m_pClass; }
   inline void setClass(IxClass * p)   { m_pClass = p; }

   QString getName() const;
   const char * getNamePtr() const;
   QString getDescription() const;
   long getVersion() const;
   long getDaoStrategy() const;

   inline long count() const                             { return m_lstDataMember.count(); }
   inline long size() const                              { return this->count(); }
   inline bool exist(const QString & sKey) const         { return m_lstDataMember.exist(sKey); }
   inline IxDataMember * get(long l) const               { return m_lstDataMember.getByIndex(l); }
   inline IxDataMember * get(const QString & s) const    { return m_lstDataMember.getByKey(s); }

   virtual IxDataMember * getId() const = 0;
   virtual long count_WithDaoStrategy() const = 0;
   virtual bool exist_WithDaoStrategy(const QString & sKey) const = 0;
   virtual IxDataMember * get_WithDaoStrategy(long lIndex) const = 0;
   virtual IxDataMember * get_WithDaoStrategy(const QString & sKey) const = 0;
   virtual IxDataMember * getId_WithDaoStrategy() const = 0;

private:

   inline void deleteAllIxDataMember() { _foreach(IxDataMember * p, m_lstDataMember) { delete p; }; }

};

typedef boost::shared_ptr<IxDataMemberX> IxDataMemberX_ptr;

} // namespace qx

#endif // _IX_DATA_MEMBER_X_H_
