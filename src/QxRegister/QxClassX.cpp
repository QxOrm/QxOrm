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

#include "../../include/QxPrecompiled.h"

#include "../../include/QxRegister/QxClassX.h"

#include "../../include/QxFactory/QxFactoryX.h"

#include "../../include/QxMemLeak/mem_leak.h"

namespace qx {

IxClass * QxClassX::get(const QString & sKey) const
{
   IxClass * pClass = (m_lstClass.exist(sKey) ? m_lstClass.getByKey(sKey) : NULL);
   if (! pClass) { qx::create(sKey); }
   if (! pClass) { pClass = (m_lstClass.exist(sKey) ? m_lstClass.getByKey(sKey) : NULL); }

   return pClass;
}

bool QxClassX::exist(const QString & sKey) const
{
   return m_lstClass.exist(sKey);
}

bool QxClassX::insert(const QString & sKey, IxClass * pClass)
{
   return ((! pClass || sKey.isEmpty() || m_lstClass.exist(sKey)) ? false : m_lstClass.insert(sKey, pClass));
}

bool QxClassX::remove(const QString & sKey)
{
   return m_lstClass.removeByKey(sKey);
}

void QxClassX::clear()
{
   m_lstClass.clear();
}

boost::any QxClassX::create(const QString & sKey)
{
   return qx::create(sKey);
}

IxClass * QxClassX::getClass(const QString & sKey)
{
   return QxClassX::getSingleton()->get(sKey);
}

IxDataMemberX * QxClassX::getDataMemberX(const QString & sKey)
{
   IxClass * pClass = QxClassX::getClass(sKey);
   return (pClass ? pClass->getDataMemberX() : NULL);
}

IxFunctionX * QxClassX::getFctMemberX(const QString & sKey)
{
   IxClass * pClass = QxClassX::getClass(sKey);
   return (pClass ? pClass->getFctMemberX() : NULL);
}

IxDataMember * QxClassX::getDataMember(const QString & sClassKey, const QString & sDataKey, bool bRecursive /* = true */)
{
   QString sBaseClassKey = sClassKey;
   IxClass * pClass(NULL); IxDataMemberX * pDataX(NULL); IxDataMember * pData(NULL);

   do {
      pClass = QxClassX::getClass(sBaseClassKey);
      pDataX = QxClassX::getDataMemberX(sBaseClassKey);
      pData = ((pDataX && pDataX->exist(sDataKey)) ? pDataX->get(sDataKey) : NULL);
      sBaseClassKey = (pClass ? pClass->getKeyBaseClass() : QString(""));
   } while (bRecursive && ! pData && pClass && ! sBaseClassKey.isEmpty() && ! pClass->getFinalClass());

   return pData;
}

IxFunction * QxClassX::getFctMember(const QString & sClassKey, const QString & sFctKey, bool bRecursive /* = true */)
{
   QString sBaseClassKey = sClassKey;
   IxClass * pClass(NULL); IxFunctionX * pFctX(NULL); IxFunction * pFct(NULL);

   do {
      pClass = QxClassX::getClass(sBaseClassKey);
      pFctX = QxClassX::getFctMemberX(sBaseClassKey);
      pFct = ((pFctX && pFctX->exist(sFctKey)) ? pFctX->getByKey(sFctKey).get() : NULL);
      sBaseClassKey = (pClass ? pClass->getKeyBaseClass() : QString(""));
   } while (bRecursive && ! pFct && pClass && ! sBaseClassKey.isEmpty() && ! pClass->getFinalClass());

   return pFct;
}

qx_bool QxClassX::invokeVoidPtr(const QString & sClassKey, const QString & sFctKey, void * pOwner, const QString & params /* = QString() */, boost::any * ret /* = NULL */)
{
   IxFunction * pFct = QxClassX::getFctMember(sClassKey, sFctKey, true);
   return ((pOwner && pFct) ? pFct->invoke(pOwner, params, ret) : qx_bool(false));
}

qx_bool QxClassX::invokeVoidPtr(const QString & sClassKey, const QString & sFctKey, void * pOwner, const type_any_params & params, boost::any * ret /* = NULL */)
{
   IxFunction * pFct = QxClassX::getFctMember(sClassKey, sFctKey, true);
   return ((pOwner && pFct) ? pFct->invoke(pOwner, params, ret) : qx_bool(false));
}

} // namespace qx
