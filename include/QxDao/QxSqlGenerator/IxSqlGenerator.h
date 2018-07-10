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

#ifndef _IX_SQL_GENERATOR_H_
#define _IX_SQL_GENERATOR_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file IxSqlGenerator.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Common interface for all SQL generators to build SQL query specific for each database
 */

#include <QtSql/qsqlquery.h>

namespace qx {
namespace dao {
namespace detail {

class IxDao_Helper;
class IxSqlElement;
class QxSqlCompare;
class QxSqlElementTemp;
class QxSqlExpression;
class QxSqlFreeText;
class QxSqlIn;
class QxSqlIsBetween;
class QxSqlIsNull;
class QxSqlLimit;
class QxSqlSort;

/*!
 * \ingroup QxDao
 * \brief qx::dao::detail::IxSqlGenerator : common interface for all SQL generators to build SQL query specific for each database
 */
class QX_DLL_EXPORT IxSqlGenerator
{

public:

   IxSqlGenerator();
   virtual ~IxSqlGenerator();

   virtual void init() = 0;
   virtual QString getAutoIncrement() const = 0;
   virtual QString getWildCard() const = 0;
   virtual QString getLimit(const QxSqlLimit * pLimit) const = 0;
   virtual void resolveLimit(QSqlQuery & query, const QxSqlLimit * pLimit) const = 0;
   virtual void postProcess(QString & sql, const QxSqlLimit * pLimit) const = 0;
   virtual void onBeforeInsert(IxDao_Helper * pDaoHelper, void * pOwner) const = 0;
   virtual void onAfterInsert(IxDao_Helper * pDaoHelper, void * pOwner) const = 0;
   virtual void onBeforeUpdate(IxDao_Helper * pDaoHelper, void * pOwner) const = 0;
   virtual void onAfterUpdate(IxDao_Helper * pDaoHelper, void * pOwner) const = 0;
   virtual void onBeforeDelete(IxDao_Helper * pDaoHelper, void * pOwner) const = 0;
   virtual void onAfterDelete(IxDao_Helper * pDaoHelper, void * pOwner) const = 0;

};

typedef qx_shared_ptr<IxSqlGenerator> IxSqlGenerator_ptr;

} // namespace detail
} // namespace dao
} // namespace qx

#endif // _IX_SQL_GENERATOR_H_
