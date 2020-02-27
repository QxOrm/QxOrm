/****************************************************************************
**
** https://www.qxorm.com/
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

#ifdef _QX_ENABLE_MONGODB
#ifndef _QX_DAO_MONGODB_HELPER_H_
#define _QX_DAO_MONGODB_HELPER_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxMongoDB_Helper.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Helper class to store all QxOrm registered classes in a MongoDB database : qx::QxSqlDatabase::getSingleton()->setDriverName("QXMONGODB");
 */

#include <QtSql/qsqlerror.h>

#include <QxSingleton/QxSingleton.h>

namespace qx {

class IxClass;
class QxSqlQuery;

} // namespace qx

namespace qx {
namespace dao {
namespace detail {

class IxDao_Helper;

} // namespace detail
} // namespace dao
} // namespace qx

namespace qx {
namespace dao {
namespace mongodb {

struct QxMongoDB_Fetcher;

/*!
 * \ingroup QxDao
 * \brief qx::dao::mongodb::QxMongoDB_Helper : helper class to store all QxOrm registered classes in a MongoDB database : qx::QxSqlDatabase::getSingleton()->setDriverName("QXMONGODB");
 */
class QX_DLL_EXPORT QxMongoDB_Helper : public QxSingleton<QxMongoDB_Helper>
{

   friend class QxSingleton<QxMongoDB_Helper>;

public:

   enum opts { opts_collection_insert_one, opts_collection_insert_many, opts_collection_update_one, opts_collection_update_many, 
               opts_collection_delete_one, opts_collection_delete_many, opts_collection_find, opts_collection_command, opts_collection_count, 
               opts_collection_create_bulk_operation, opts_bulk_operation_update_one, opts_bulk_operation_remove_one, opts_collection_aggregate };

private:

   struct QxMongoDB_HelperImpl;
   std::unique_ptr<QxMongoDB_HelperImpl> m_pImpl; //!< Private implementation idiom

   QxMongoDB_Helper();
   virtual ~QxMongoDB_Helper();

public:

   static QSqlError insertOne(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, const QString & json, QString & insertedId);
   static QSqlError insertMany(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, const QStringList & json, QStringList & insertedId);
   static QSqlError updateOne(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, const QString & json, const qx::QxSqlQuery * query = NULL);
   static QSqlError updateMany(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, const QStringList & json, const qx::QxSqlQuery * query = NULL);
   static QSqlError deleteOne(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, const QString & json, const qx::QxSqlQuery * query = NULL);
   static QSqlError deleteMany(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, const QStringList & json, const qx::QxSqlQuery * query = NULL);
   static QSqlError findOne(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, QString & json, const qx::QxSqlQuery * query = NULL);
   static QSqlError findMany(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, QStringList & json, const qx::QxSqlQuery * query = NULL, QxMongoDB_Fetcher * pFetcher = NULL);
   static QSqlError aggregate(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, QStringList & json, const qx::QxSqlQuery * query = NULL, const QString & lookup = QString(), QxMongoDB_Fetcher * pFetcher = NULL);
   static QSqlError count(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, long & cnt, const qx::QxSqlQuery * query = NULL);
   static QSqlError executeCommand(qx::dao::detail::IxDao_Helper * pDaoHelper, qx::IxClass * pClass, qx::QxSqlQuery * query);

   static QSqlError autoCreateIndexes(bool log = true);
   static bool setOptions(opts e, const QString & optsAsJson);
   static void setLogDatabaseReply(bool b);
   static void setLogDatabaseInfo(bool b);
   static void clearPoolConnection();

};

/*!
 * \ingroup QxDao
 * \brief qx::dao::mongodb::QxMongoDB_Fetcher : used to fetch a list of items from MongoDB database without having to put them in a buffer before fetching
 */
struct QX_DLL_EXPORT QxMongoDB_Fetcher
{

   QxMongoDB_Fetcher();
   virtual ~QxMongoDB_Fetcher();

   virtual void fetch(const QString & json) = 0;

};

} // namespace mongodb
} // namespace dao
} // namespace qx

QX_DLL_EXPORT_QX_SINGLETON_HPP(qx::dao::mongodb::QxMongoDB_Helper)

#endif // _QX_DAO_MONGODB_HELPER_H_
#endif // _QX_ENABLE_MONGODB
