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

#ifndef _IX_CLASS_H_
#define _IX_CLASS_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QxDataMember/IxDataMemberX.h>

#include <QxFunction/IxFunction.h>

namespace qx {

class QX_DLL_EXPORT IxClass
{

protected:

   IxDataMemberX * m_pDataMemberX;                    // List of data member
   IxFunctionX_ptr m_pFctMemberX;                     // List of function member

   QString m_sKey;                                    // 'IxClass' key <=> class name
   QString m_sKeyBaseClass;                           // 'IxClass' base class key <=> base class name
   QString m_sName;                                   // 'IxClass' name <=> database table name (if empty => class name)
   QString m_sDescription;                            // 'IxClass' description
   long m_lVersion;                                   // 'IxClass' version
   bool m_bFinalClass;                                // Class cannot have base class : 'qx::trait::no_base_class_defined' and 'QObject'
   qx::dao::strategy::inheritance m_eDaoStrategy;     // Dao class strategy to access data member

   QByteArray m_byteName;                             // Optimization to retrieve name under "const char *" format
   const char * m_pName;                              // Optimization to retrieve name under "const char *" format

protected:

   IxClass() : m_pDataMemberX(NULL), m_lVersion(-1), m_bFinalClass(false), m_eDaoStrategy(qx::dao::strategy::concrete_table_inheritance), m_pName(NULL) { ; }
   virtual ~IxClass() = 0;

   void updateClassX();

public:

   inline QString getKey() const                                  { return m_sKey; }
   inline QString getKeyBaseClass() const                         { return m_sKeyBaseClass; }
   inline QString getName() const                                 { return m_sName; }
   inline const char * getNamePtr() const                         { return m_pName; }
   inline QString getDescription() const                          { return m_sDescription; }
   inline long getVersion() const                                 { return m_lVersion; }
   inline qx::dao::strategy::inheritance getDaoStrategy() const   { return m_eDaoStrategy; }
   inline bool getFinalClass() const                              { return m_bFinalClass; }
   inline IxDataMemberX * getDataMemberX() const                  { return m_pDataMemberX; }
   inline IxFunctionX * getFctMemberX() const                     { return m_pFctMemberX.get(); }
   inline IxDataMember * getId() const                            { return (m_pDataMemberX ? m_pDataMemberX->getId() : NULL); }

   inline void setName(const QString & sName)                                 { m_sName = sName; updateNamePtr(); }
   inline void setDescription(const QString & sDesc)                          { m_sDescription = sDesc; }
   inline void setDaoStrategy(qx::dao::strategy::inheritance eDaoStrategy)    { m_eDaoStrategy = eDaoStrategy; }

private:

   inline void updateNamePtr()   { m_byteName = m_sName.toAscii(); m_pName = m_byteName.constData(); }

};

typedef boost::shared_ptr<IxClass> IxClass_ptr;

} // namespace qx

#endif // _IX_CLASS_H_
