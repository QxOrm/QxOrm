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

#ifndef _QX_DAO_STRATEGY_H_
#define _QX_DAO_STRATEGY_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxDaoStrategy.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Class inheritance strategy and database (Concrete Table Inheritance is the default strategy used by QxOrm library)
 */

namespace qx {
namespace dao {

/*!
 * \ingroup QxDao
 * \brief qx::dao::strategy : class inheritance strategy and database (Concrete Table Inheritance is the default strategy used by QxOrm library)
 *
 * With ORM tools, there is usually 3 strategies to manage inheritance and database :
 * - Single Table Inheritance
 * - Class Table Inheritance
 * - Concrete Table Inheritance
 *
 * QxOrm works by default with Concrete Table Inheritance strategy (others are not supported yet).
 * Many tutorials and forums are available on internet to more details about ORM inheritance and database.
 * You can find a sample in the directory ./test/qxDllSample/dll2/ with the class BaseClassTrigger.
 */
struct strategy
{

   enum inheritance
   {
      single_table_inheritance,
      class_table_inheritance,
      concrete_table_inheritance
   };

};

} // namespace dao
} // namespace qx

#endif // _QX_DAO_STRATEGY_H_
