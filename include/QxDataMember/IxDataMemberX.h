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

#ifndef _IX_DATA_MEMBER_X_H_
#define _IX_DATA_MEMBER_X_H_

#ifdef _MSC_VER
#pragma once
#endif

#include "../../include/QxDataMember/IxDataMember.h"

#include "../../include/QxCollection/QxCollection.h"

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
