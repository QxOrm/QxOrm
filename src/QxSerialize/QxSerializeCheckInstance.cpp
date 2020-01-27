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

#include <QxSerialize/QxSerializeCheckInstance.h>

#include <QxDao/QxSqlRelationLinked.h>

#include <QxRegister/IxClass.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {
namespace serialization {
namespace helper {

QSet< QPair<Qt::HANDLE, QPair<qptrdiff, qx::IxClass *> > > QxSerializeCheckInstance::m_lstInstanceByThread;
QHash<Qt::HANDLE, int> QxSerializeCheckInstance::m_hashLevelByThread;
QHash<Qt::HANDLE, QxSerializeCheckInstance::type_hierarchy> QxSerializeCheckInstance::m_hashHierarchyByThread;
QMutex QxSerializeCheckInstance::m_mutex;

QxSerializeCheckInstance::QxSerializeCheckInstance(const void * pInstance, qx::IxClass * pClass) : m_pInstance(0), m_lThreadId(0), m_pClass(pClass)
{
   QMutexLocker locker(& m_mutex);
   m_pInstance = reinterpret_cast<qptrdiff>(const_cast<void *>(pInstance));
   m_lThreadId = QThread::currentThreadId(); qAssert(m_pInstance != 0);
   m_lstInstanceByThread.insert(qMakePair(m_lThreadId, qMakePair(m_pInstance, m_pClass)));
   int iLevel = (m_hashLevelByThread.value(m_lThreadId, 0) + 1);
   m_hashLevelByThread.insert(m_lThreadId, iLevel);
}

QxSerializeCheckInstance::~QxSerializeCheckInstance()
{
   QMutexLocker locker(& m_mutex);
   m_lstInstanceByThread.remove(qMakePair(m_lThreadId, qMakePair(m_pInstance, m_pClass)));
   int iLevel = (m_hashLevelByThread.value(m_lThreadId, 0) - 1);
   m_hashLevelByThread.insert(m_lThreadId, iLevel);
   if (iLevel <= 0) { m_hashHierarchyByThread.remove(m_lThreadId); }
}

bool QxSerializeCheckInstance::contains(const void * pInstance, qx::IxClass * pClass)
{
   QMutexLocker locker(& m_mutex);
   Qt::HANDLE lCurrThreadId = QThread::currentThreadId();
   qptrdiff iInstance = reinterpret_cast<qptrdiff>(const_cast<void *>(pInstance));
   return m_lstInstanceByThread.contains(qMakePair(lCurrThreadId, qMakePair(iInstance, pClass)));
}

bool QxSerializeCheckInstance::isRoot()
{
   QMutexLocker locker(& m_mutex);
   Qt::HANDLE lThreadId = QThread::currentThreadId();
   int iLevel = m_hashLevelByThread.value(lThreadId, 0); qAssert(iLevel >= 0);
   return (iLevel == 0);
}

QxSerializeCheckInstance::type_hierarchy QxSerializeCheckInstance::getHierarchy()
{
   QMutexLocker locker(& m_mutex);
   Qt::HANDLE lThreadId = QThread::currentThreadId();
   return m_hashHierarchyByThread.value(lThreadId);
}

void QxSerializeCheckInstance::setHierarchy(const QxSerializeCheckInstance::type_hierarchy & hierarchy)
{
   QMutexLocker locker(& m_mutex);
   Qt::HANDLE lThreadId = QThread::currentThreadId();
   m_hashHierarchyByThread.insert(lThreadId, hierarchy);
}

} // namespace helper
} // namespace serialization
} // namespace qx
