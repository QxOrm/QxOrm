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
