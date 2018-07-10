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

#ifndef _QX_SQL_GENERATOR_STANDARD_H_
#define _QX_SQL_GENERATOR_STANDARD_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxSqlGenerator_Standard.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief SQL generator to build standard SQL query
 */

#include <QxDao/QxSqlGenerator/IxSqlGenerator.h>

#include <QxDao/QxSqlElement/QxSqlElement.h>

namespace qx {
namespace dao {
namespace detail {

/*!
 * \ingroup QxDao
 * \brief qx::dao::detail::QxSqlGenerator_Standard : SQL generator to build standard SQL query
 */
class QX_DLL_EXPORT QxSqlGenerator_Standard : public IxSqlGenerator
{

public:

   QxSqlGenerator_Standard();
   virtual ~QxSqlGenerator_Standard();

   virtual void init();
   virtual QString getAutoIncrement() const;
   virtual QString getWildCard() const;
   virtual QString getLimit(const QxSqlLimit * pLimit) const;
   virtual void resolveLimit(QSqlQuery & query, const QxSqlLimit * pLimit) const;
   virtual void postProcess(QString & sql, const QxSqlLimit * pLimit) const;
   virtual void onBeforeInsert(IxDao_Helper * pDaoHelper, void * pOwner) const;
   virtual void onAfterInsert(IxDao_Helper * pDaoHelper, void * pOwner) const;
   virtual void onBeforeUpdate(IxDao_Helper * pDaoHelper, void * pOwner) const;
   virtual void onAfterUpdate(IxDao_Helper * pDaoHelper, void * pOwner) const;
   virtual void onBeforeDelete(IxDao_Helper * pDaoHelper, void * pOwner) const;
   virtual void onAfterDelete(IxDao_Helper * pDaoHelper, void * pOwner) const;

};

typedef qx_shared_ptr<QxSqlGenerator_Standard> QxSqlGenerator_Standard_ptr;

} // namespace detail
} // namespace dao
} // namespace qx

#endif // _QX_SQL_GENERATOR_STANDARD_H_
