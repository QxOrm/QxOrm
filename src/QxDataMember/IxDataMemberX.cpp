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

#include <QxPrecompiled.h>

#include <QxDataMember/IxDataMemberX.h>

#include <QxRegister/IxClass.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

struct IxDataMemberX::IxDataMemberXImpl
{

   QxCollection<QString, IxDataMember *> m_lstDataMember;   //!< Collection of IxDataMember
   IxClass * m_pClass;                                      //!< Class definition
   IxDataMember * m_pDataMemberId;                          //!< Data member id with primary key type

   IxDataMemberXImpl() : m_pClass(NULL), m_pDataMemberId(NULL) { ; }
   ~IxDataMemberXImpl() { ; }

   void deleteAllIxDataMember() { for (auto itr = m_lstDataMember.begin(); itr != m_lstDataMember.end(); ++itr) { delete itr->second; } }

};

IxDataMemberX::IxDataMemberX() : m_pImpl(new IxDataMemberXImpl()) { ; }

IxDataMemberX::~IxDataMemberX() { m_pImpl->deleteAllIxDataMember(); }

IxClass * IxDataMemberX::getClass() const { return m_pImpl->m_pClass; }

void IxDataMemberX::setClass(IxClass * p) { m_pImpl->m_pClass = p; }

QString IxDataMemberX::getName() const { return (m_pImpl->m_pClass ? m_pImpl->m_pClass->getName() : ""); }

const char * IxDataMemberX::getNamePtr() const { return (m_pImpl->m_pClass ? m_pImpl->m_pClass->getNamePtr() : NULL); }

QString IxDataMemberX::getDescription() const { return (m_pImpl->m_pClass ? m_pImpl->m_pClass->getDescription() : ""); }

long IxDataMemberX::getVersion() const { return (m_pImpl->m_pClass ? m_pImpl->m_pClass->getVersion() : -1); }

qx::dao::strategy::inheritance IxDataMemberX::getDaoStrategy() const { return (m_pImpl->m_pClass ? m_pImpl->m_pClass->getDaoStrategy() : qx::dao::strategy::concrete_table_inheritance); }

long IxDataMemberX::count() const { return m_pImpl->m_lstDataMember.count(); }

long IxDataMemberX::size() const { return this->count(); }

bool IxDataMemberX::exist(const QString & sKey) const { return m_pImpl->m_lstDataMember.exist(sKey); }

IxDataMember * IxDataMemberX::get(long l) const { return m_pImpl->m_lstDataMember.getByIndex(l); }

IxDataMember * IxDataMemberX::get(const QString & s) const { return m_pImpl->m_lstDataMember.getByKey(s); }

IxDataMember * IxDataMemberX::getId() const { return m_pImpl->m_pDataMemberId; }

void IxDataMemberX::setId(IxDataMember * p) { m_pImpl->m_pDataMemberId = p; }

QxCollection<QString, IxDataMember *> & IxDataMemberX::getListDataMemberRef() { return m_pImpl->m_lstDataMember; }

const QxCollection<QString, IxDataMember *> & IxDataMemberX::getListDataMemberRef() const { return m_pImpl->m_lstDataMember; }

} // namespace qx
