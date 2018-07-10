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

#ifndef _IX_CLASS_H_
#define _IX_CLASS_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file IxClass.h
 * \author Lionel Marty
 * \ingroup QxRegister
 * \brief Common interface for all classes registered into QxOrm context
 */

#include <typeinfo>

#include <QxCommon/QxPropertyBag.h>

#include <QxDataMember/IxDataMemberX.h>

#include <QxFunction/IxFunction.h>

#include <QxDao/QxSoftDelete.h>

#include <QxValidator/IxValidatorX.h>

namespace qx {

/*!
 * \ingroup QxRegister
 * \brief qx::IxClass : common interface for all classes registered into QxOrm context
 */
class QX_DLL_EXPORT IxClass : public qx::QxPropertyBag
{

protected:

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

protected:

   IxClass() : qx::QxPropertyBag(), m_pDataMemberX(NULL), m_lVersion(-1), m_bFinalClass(false), m_bDaoReadOnly(false), m_bRegistered(false), m_eDaoStrategy(qx::dao::strategy::concrete_table_inheritance), m_pName(NULL) { ; }
   virtual ~IxClass() = 0;

   void updateClassX();

public:

   inline QString getKey() const                                  { return m_sKey; }
   inline QString getName() const                                 { return m_sName; }
   inline const char * getNamePtr() const                         { return m_pName; }
   inline QString getDescription() const                          { return m_sDescription; }
   inline long getVersion() const                                 { return m_lVersion; }
   inline qx::dao::strategy::inheritance getDaoStrategy() const   { return m_eDaoStrategy; }
   inline qx::QxSoftDelete getSoftDelete() const                  { return m_oSoftDelete; }
   inline bool isFinalClass() const                               { return m_bFinalClass; }
   inline bool isDaoReadOnly() const                              { return m_bDaoReadOnly; }
   inline bool isRegistered() const                               { return m_bRegistered; }
   inline IxDataMemberX * getDataMemberX() const                  { return m_pDataMemberX; }
   inline IxFunctionX * getFctMemberX() const                     { return m_pFctMemberX.get(); }
   inline IxFunctionX * getFctStaticX() const                     { return m_pFctStaticX.get(); }
   inline IxDataMember * getId() const                            { return (m_pDataMemberX ? m_pDataMemberX->getId() : NULL); }

   inline void setName(const QString & sName)                                 { m_sName = sName; updateNamePtr(); }
   inline void setDescription(const QString & sDesc)                          { m_sDescription = sDesc; }
   inline void setDaoStrategy(qx::dao::strategy::inheritance eDaoStrategy)    { m_eDaoStrategy = eDaoStrategy; }
   inline void setSoftDelete(const qx::QxSoftDelete & oSoftDelete)            { m_oSoftDelete = oSoftDelete; if (m_oSoftDelete.getTableName().isEmpty()) { m_oSoftDelete.setTableName(m_sName); } }
   inline void setDaoReadOnly(bool bDaoReadOnly)                              { m_bDaoReadOnly = bDaoReadOnly; }

   virtual bool isAbstract() const = 0;
   virtual bool implementIxPersistable() const = 0;
   virtual const std::type_info & typeInfo() const = 0;
   virtual IxClass * getBaseClass() const = 0;
   virtual IxValidatorX * getAllValidator();

   bool isKindOf(const QString & sClassName) const;
   bool isKindOf(const std::type_info & typeInfo) const;
   QString dumpClass() const;

private:

   inline void updateNamePtr()   { m_byteName = m_sName.toLatin1(); m_pName = m_byteName.constData(); }

};

typedef boost::shared_ptr<IxClass> IxClass_ptr;

} // namespace qx

#endif // _IX_CLASS_H_
