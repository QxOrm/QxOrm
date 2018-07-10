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

#ifndef _IX_DATA_MEMBER_X_H_
#define _IX_DATA_MEMBER_X_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file IxDataMemberX.h
 * \author Lionel Marty
 * \ingroup QxDataMember
 * \brief Common interface for a list of IxDataMember class properties registered into QxOrm context (for example, list of data member of a class)
 */

#include <QxDataMember/IxDataMember.h>

#include <QxDao/QxDaoStrategy.h>

#include <QxCollection/QxCollection.h>

namespace qx {

class IxClass;

/*!
 * \ingroup QxDataMember
 * \brief qx::IxDataMemberX : common interface for a list of IxDataMember class properties registered into QxOrm context (for example, list of data member of a class)
 */
class QX_DLL_EXPORT IxDataMemberX
{

private:

   struct IxDataMemberXImpl;
   std::unique_ptr<IxDataMemberXImpl> m_pImpl; //!< Private implementation idiom

protected:

   IxDataMemberX();
   virtual ~IxDataMemberX();

public:

   IxClass * getClass() const;
   void setClass(IxClass * p);

   QString getName() const;
   const char * getNamePtr() const;
   QString getDescription() const;
   long getVersion() const;
   qx::dao::strategy::inheritance getDaoStrategy() const;

   long count() const;
   long size() const;
   bool exist(const QString & sKey) const;
   IxDataMember * get(long l) const;
   IxDataMember * get(const QString & s) const;
   IxDataMember * getId() const;

   virtual long count_WithDaoStrategy() const = 0;
   virtual bool exist_WithDaoStrategy(const QString & sKey) const = 0;
   virtual IxDataMember * get_WithDaoStrategy(long lIndex) const = 0;
   virtual IxDataMember * get_WithDaoStrategy(const QString & sKey) const = 0;
   virtual IxDataMember * getId_WithDaoStrategy() const = 0;

protected:

   void setId(IxDataMember * p);
   QxCollection<QString, IxDataMember *> & getListDataMemberRef();
   const QxCollection<QString, IxDataMember *> & getListDataMemberRef() const;

};

typedef std::shared_ptr<IxDataMemberX> IxDataMemberX_ptr;

} // namespace qx

#endif // _IX_DATA_MEMBER_X_H_
