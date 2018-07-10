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

#ifndef _QX_NO_RTTI
#include <typeinfo>
#endif // _QX_NO_RTTI

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

private:

   struct IxClassImpl;
   std::unique_ptr<IxClassImpl> m_pImpl; //!< Private implementation idiom

protected:

   IxClass();
   virtual ~IxClass() = 0;

public:

   QString getKey() const;
   QString getName() const;
   const char * getNamePtr() const;
   QString getDescription() const;
   long getVersion() const;
   qx::dao::strategy::inheritance getDaoStrategy() const;
   qx::QxSoftDelete getSoftDelete() const;
   bool isFinalClass() const;
   bool isDaoReadOnly() const;
   bool isRegistered() const;
   IxDataMemberX * getDataMemberX() const;
   IxFunctionX * getFctMemberX() const;
   IxFunctionX * getFctStaticX() const;

   void setKey(const QString & s);
   void setName(const QString & s);
   void setDescription(const QString & s);
   void setDaoStrategy(qx::dao::strategy::inheritance e);
   void setSoftDelete(const qx::QxSoftDelete & o);
   void setDaoReadOnly(bool b);
   void setVersion(long l);

   virtual bool isAbstract() const = 0;
   virtual bool implementIxPersistable() const = 0;
   virtual IxClass * getBaseClass() const = 0;
   virtual IxValidatorX * getAllValidator();

   IxDataMember * getId(bool bRecursive = false) const;
   bool isKindOf(const QString & sClassName) const;
   QString dumpClass() const;

#ifndef _QX_NO_RTTI
   virtual const std::type_info & typeInfo() const = 0;
   bool isKindOf(const std::type_info & typeInfo) const;
#endif // _QX_NO_RTTI

protected:

   void updateClassX();
   void setRegistered(bool b);
   void setFinalClass(bool b);
   void setDataMemberX(IxDataMemberX * p);
   void setFctMemberX(IxFunctionX * p);
   void setFctStaticX(IxFunctionX * p);
   IxValidatorX_ptr & getAllValidatorRef();

};

typedef std::shared_ptr<IxClass> IxClass_ptr;

} // namespace qx

#endif // _IX_CLASS_H_
