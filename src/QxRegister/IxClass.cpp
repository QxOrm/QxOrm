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

#include <QxDao/IxSqlRelation.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

struct IxClass::IxClassImpl
{

   IxDataMemberX * m_pDataMemberX;                    //!< List of data member
   IxFunctionX_ptr m_pFctMemberX;                     //!< List of function member
   IxFunctionX_ptr m_pFctStaticX;                     //!< List of function static

   QString m_sKey;                                    //!< 'IxClass' key <=> class name
   QString m_sName;                                   //!< 'IxClass' name <=> database table name (if empty => class name)
   QString m_sDescription;                            //!< 'IxClass' description
   long m_lVersion;                                   //!< 'IxClass' version
   bool m_bFinalClass;                                //!< Class without base class (for example, qx::trait::no_base_class_defined and QObject)
   bool m_bDaoReadOnly;                               //!< If 'true', cannot INSERT, UPDATE OR DELETE an instance of this class using qx::dao namespace
   bool m_bRegistered;                                //!< Class registered into QxOrm context
   qx::dao::strategy::inheritance m_eDaoStrategy;     //!< Dao class strategy to access data member
   qx::QxSoftDelete m_oSoftDelete;                    //!< Soft delete (or logical delete) behavior
   IxValidatorX_ptr m_pAllValidator;                  //!< List of validator associated to the class

   QByteArray m_byteName;                             //!< Optimization to retrieve name under "const char *" format
   const char * m_pName;                              //!< Optimization to retrieve name under "const char *" format

   IxClassImpl() : m_pDataMemberX(NULL), m_lVersion(-1), m_bFinalClass(false), m_bDaoReadOnly(false), m_bRegistered(false), m_eDaoStrategy(qx::dao::strategy::concrete_table_inheritance), m_pName(NULL) { ; }
   ~IxClassImpl() { ; }

   void updateNamePtr() { m_byteName = m_sName.toLatin1(); m_pName = m_byteName.constData(); }

};

IxClass::IxClass() : qx::QxPropertyBag(), m_pImpl(new IxClassImpl()) { ; }

IxClass::~IxClass()
{
   if (QxClassX::isSingletonNull() || m_pImpl->m_sKey.isEmpty()) { return; }
   if (! QxClassX::getSingleton()->exist(m_pImpl->m_sKey)) { return; }
   QxClassX::getSingleton()->remove(m_pImpl->m_sKey);
}

QString IxClass::getKey() const { return m_pImpl->m_sKey; }

QString IxClass::getName() const { return m_pImpl->m_sName; }

const char * IxClass::getNamePtr() const { return m_pImpl->m_pName; }

QString IxClass::getDescription() const { return m_pImpl->m_sDescription; }

long IxClass::getVersion() const { return m_pImpl->m_lVersion; }

qx::dao::strategy::inheritance IxClass::getDaoStrategy() const { return m_pImpl->m_eDaoStrategy; }

qx::QxSoftDelete IxClass::getSoftDelete() const { return m_pImpl->m_oSoftDelete; }

bool IxClass::isFinalClass() const { return m_pImpl->m_bFinalClass; }

bool IxClass::isDaoReadOnly() const { return m_pImpl->m_bDaoReadOnly; }

bool IxClass::isRegistered() const { return m_pImpl->m_bRegistered; }

IxDataMemberX * IxClass::getDataMemberX() const { return m_pImpl->m_pDataMemberX; }

IxFunctionX * IxClass::getFctMemberX() const { return m_pImpl->m_pFctMemberX.get(); }

IxFunctionX * IxClass::getFctStaticX() const { return m_pImpl->m_pFctStaticX.get(); }

IxValidatorX_ptr & IxClass::getAllValidatorRef() { return m_pImpl->m_pAllValidator; }

void IxClass::setKey(const QString & sKey) { m_pImpl->m_sKey = sKey; }

void IxClass::setName(const QString & sName) { m_pImpl->m_sName = sName; m_pImpl->updateNamePtr(); }

void IxClass::setDescription(const QString & sDesc) { m_pImpl->m_sDescription = sDesc; }

void IxClass::setDaoStrategy(qx::dao::strategy::inheritance eDaoStrategy) { m_pImpl->m_eDaoStrategy = eDaoStrategy; }

void IxClass::setSoftDelete(const qx::QxSoftDelete & oSoftDelete) { m_pImpl->m_oSoftDelete = oSoftDelete; if (m_pImpl->m_oSoftDelete.getTableName().isEmpty()) { m_pImpl->m_oSoftDelete.setTableName(m_pImpl->m_sName); } }

void IxClass::setDaoReadOnly(bool bDaoReadOnly) { m_pImpl->m_bDaoReadOnly = bDaoReadOnly; }

void IxClass::setVersion(long l) { m_pImpl->m_lVersion = l; }

void IxClass::setRegistered(bool b) { m_pImpl->m_bRegistered = b; }

void IxClass::setFinalClass(bool b) { m_pImpl->m_bFinalClass = b; }

void IxClass::setDataMemberX(IxDataMemberX * p) { m_pImpl->m_pDataMemberX = p; }

void IxClass::setFctMemberX(IxFunctionX * p) { m_pImpl->m_pFctMemberX.reset(p); }

void IxClass::setFctStaticX(IxFunctionX * p) { m_pImpl->m_pFctStaticX.reset(p); }

void IxClass::updateClassX()
{
   qAssert(! m_pImpl->m_sKey.isEmpty() && ! QxClassX::getSingleton()->exist(m_pImpl->m_sKey));
   QxClassX::getSingleton()->insert(m_pImpl->m_sKey, this);
}

IxValidatorX * IxClass::getAllValidator()
{
   if (! m_pImpl->m_pAllValidator) { return NULL; }
   m_pImpl->m_pAllValidator->setClass(this);
   return m_pImpl->m_pAllValidator.get();
}

IxDataMember * IxClass::getId(bool bRecursive /* = false */) const
{
   IxDataMember * pId = (m_pImpl->m_pDataMemberX ? m_pImpl->m_pDataMemberX->getId() : NULL);
   if (pId || ! bRecursive) { return pId; }
   IxClass * pBaseClass = getBaseClass();
   return (pBaseClass ? pBaseClass->getId(bRecursive) : NULL);
}

bool IxClass::isKindOf(const QString & sClassName) const
{
   if (sClassName.isEmpty()) { qAssert(false); return false; }
   if (m_pImpl->m_sKey == sClassName) { return true; }

   IxClass * p = getBaseClass();
   while (p != NULL)
   {
      if (p->getKey() == sClassName) { return true; }
      p = p->getBaseClass();
   }

   return false;
}

#ifndef _QX_NO_RTTI
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
#endif // _QX_NO_RTTI

QString IxClass::dumpClass() const
{
   QString sDump;
   sDump += "-- class '" + m_pImpl->m_sKey + "' (name '" + m_pImpl->m_sName + "', ";
   sDump += "description '" + m_pImpl->m_sDescription + "', version '" + QString::number(m_pImpl->m_lVersion) + "', ";
   sDump += "base class '" + (getBaseClass() ? getBaseClass()->getKey() : "") + "')\n";

   long lCount = (m_pImpl->m_pDataMemberX ? m_pImpl->m_pDataMemberX->count() : 0);
   sDump += "\t* list of registered properties (" + QString::number(lCount) + ")\n";
   if (m_pImpl->m_pDataMemberX)
   {
      IxDataMember * pId = this->getId();
      for (long l = 0; l < lCount; l++)
      {
         IxDataMember * p = m_pImpl->m_pDataMemberX->get(l); if (! p) { continue; }
         IxSqlRelation * pRelation = p->getSqlRelation();
         QString sInfos = p->getKey() + ((p == pId) ? QString(" (id)") : QString());
         sInfos += (pRelation ? (QString(" (") + pRelation->getDescription() + QString(")")) : QString());
         sDump += "\t\t" + sInfos + "\n";
      }
   }

   lCount = (m_pImpl->m_pFctMemberX ? m_pImpl->m_pFctMemberX->count() : 0);
   sDump += "\t* list of registered member functions (" + QString::number(lCount) + ")\n";
   if (m_pImpl->m_pFctMemberX)
   {
      for (auto itr = m_pImpl->m_pFctMemberX->begin(); itr != m_pImpl->m_pFctMemberX->end(); ++itr)
      {
         IxFunction_ptr p = itr->second; if (! p) { continue; }
         QString sKey = p->getKey();
         sDump += "\t\t" + sKey + "\n";
      }
   }

   lCount = (m_pImpl->m_pFctStaticX ? m_pImpl->m_pFctStaticX->count() : 0);
   sDump += "\t* list of registered static functions (" + QString::number(lCount) + ")\n";
   if (m_pImpl->m_pFctStaticX)
   {
      for (auto itr = m_pImpl->m_pFctStaticX->begin(); itr != m_pImpl->m_pFctStaticX->end(); ++itr)
      {
         IxFunction_ptr p = itr->second; if (! p) { continue; }
         QString sKey = p->getKey();
         sDump += "\t\t" + sKey + "\n";
      }
   }

   qDebug("%s", qPrintable(sDump));
   return sDump;
}

} // namespace qx
