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

#ifndef _IX_FACTORY_H_
#define _IX_FACTORY_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file IxFactory.h
 * \author Lionel Marty
 * \ingroup QxFactory
 * \brief Common interface for all classes that can be created dynamically using the class name
 */

#ifndef _QX_NO_RTTI
#include <typeinfo>
#endif // _QX_NO_RTTI

#include <QxCommon/QxAny.h>

namespace qx {

/*!
 * \ingroup QxFactory
 * \brief qx::IxFactory : common interface for all classes that can be created dynamically using the class name
 */
class QX_DLL_EXPORT IxFactory
{

protected:

   QString m_sKeyFactory;  //!< Factory key used by the collection QxFactoryX

public:

   IxFactory(const QString & sKey);
   virtual ~IxFactory();

   virtual qx::any createObject() const = 0;
   virtual void * createObjectNudePtr() const = 0;

#ifndef _QX_NO_RTTI
   virtual const std::type_info & typeInfo() const = 0;
#endif // _QX_NO_RTTI

private:

   IxFactory(const IxFactory & other) { Q_UNUSED(other); }
   IxFactory & operator=(const IxFactory & other) { Q_UNUSED(other); return (* this); }

};

} // namespace qx

#endif // _IX_FACTORY_H_
