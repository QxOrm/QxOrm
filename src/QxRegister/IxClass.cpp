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

#include <QxRegister/IxClass.h>
#include <QxRegister/QxClassX.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

IxClass::~IxClass()
{
   if (QxClassX::isSingletonNull() || m_sKey.isEmpty()) { return; }
   if (! QxClassX::getSingleton()->exist(m_sKey)) { return; }
   QxClassX::getSingleton()->remove(m_sKey);
}

void IxClass::updateClassX()
{
   qAssert(! m_sKey.isEmpty() && ! QxClassX::getSingleton()->exist(m_sKey));
   QxClassX::getSingleton()->insert(m_sKey, this);
}

IxValidatorX * IxClass::getAllValidator()
{
   if (! m_pAllValidator) { return NULL; }
   m_pAllValidator->setClass(this);
   return m_pAllValidator.get();
}

bool IxClass::isKindOf(const QString & sClassName) const
{
   if (sClassName.isEmpty()) { qAssert(false); return false; }
   if (m_sKey == sClassName) { return true; }

   IxClass * p = getBaseClass();
   while (p != NULL)
   {
      if (p->getKey() == sClassName) { return true; }
      p = p->getBaseClass();
   }

   return false;
}

bool IxClass::isKindOf(const std::type_info & typeInfo) const
{
   if (typeInfo == typeid(void)) { qAssert(false); return false; }
   if (typeInfo == this->typeInfo()) { return true; }

   IxClass * p = getBaseClass();
   while (p != NULL)
   {
      if (typeInfo == p->typeInfo()) { return true; }
      p = p->getBaseClass();
   }

   return false;
}

QString IxClass::dumpClass() const
{
   QString sDump;
   sDump += "-- class '" + m_sKey + "' (name '" + m_sName + "', ";
   sDump += "description '" + m_sDescription + "', version '" + QString::number(m_lVersion) + "', ";
   sDump += "base class '" + (getBaseClass() ? getBaseClass()->getKey() : "") + "')\n";

   long lCount = (m_pDataMemberX ? m_pDataMemberX->count() : 0);
   sDump += "\t* list of registered properties (" + QString::number(lCount) + ")\n";
   if (m_pDataMemberX)
   {
      IxDataMember * pId = this->getId();
      for (long l = 0; l < lCount; l++)
      {
         IxDataMember * p = m_pDataMemberX->get(l); if (! p) { continue; }
         IxSqlRelation * pRelation = p->getSqlRelation();
         QString sInfos = p->getKey() + ((p == pId) ? QString(" (id)") : QString());
         sInfos += (pRelation ? (QString(" (") + pRelation->getDescription() + QString(")")) : QString());
         sDump += "\t\t" + sInfos + "\n";
      }
   }

   lCount = (m_pFctMemberX ? m_pFctMemberX->count() : 0);
   sDump += "\t* list of registered member functions (" + QString::number(lCount) + ")\n";
   if (m_pFctMemberX)
   {
      _foreach_if(IxFunction_ptr p, (* m_pFctMemberX), (p))
      { QString sKey = p->getKey(); sDump += "\t\t" + sKey + "\n"; }
   }

   lCount = (m_pFctStaticX ? m_pFctStaticX->count() : 0);
   sDump += "\t* list of registered static functions (" + QString::number(lCount) + ")\n";
   if (m_pFctStaticX)
   {
      _foreach_if(IxFunction_ptr p, (* m_pFctStaticX), (p))
      { QString sKey = p->getKey(); sDump += "\t\t" + sKey + "\n"; }
   }

   qDebug("%s", qPrintable(sDump));
   return sDump;
}

} // namespace qx
