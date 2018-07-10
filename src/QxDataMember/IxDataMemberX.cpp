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

#include <QxDataMember/IxDataMemberX.h>

#include <QxRegister/IxClass.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

QString IxDataMemberX::getName() const
{ return (m_pClass ? m_pClass->getName() : ""); }

const char * IxDataMemberX::getNamePtr() const
{ return (m_pClass ? m_pClass->getNamePtr() : NULL); }

QString IxDataMemberX::getDescription() const
{ return (m_pClass ? m_pClass->getDescription() : ""); }

long IxDataMemberX::getVersion() const
{ return (m_pClass ? m_pClass->getVersion() : -1); }

qx::dao::strategy::inheritance IxDataMemberX::getDaoStrategy() const
{ return (m_pClass ? m_pClass->getDaoStrategy() : qx::dao::strategy::concrete_table_inheritance); }

} // namespace qx
