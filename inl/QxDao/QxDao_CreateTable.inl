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

namespace qx {
namespace dao {
namespace detail {

template <class T>
struct QxDao_CreateTable
{

   static QSqlError createTable(QSqlDatabase * pDatabase)
   {
      T t; Q_UNUSED(t);
      qx::dao::detail::QxDao_Helper<T> dao(t, pDatabase, "create table", new qx::QxSqlQueryBuilder_CreateTable<T>());
      if (! dao.isValid()) { return dao.error(); }

      if (dao.database().driverName() != "QSQLITE")
      {
         QString sWarningMsg = "-- WARNING -- the function qx::dao::create_table<T>() can be used only with a SQLite database to create examples or prototypes, for other databases, it is recommended :";
         sWarningMsg += "\n\t - to use QxEntityEditor application and its DDL SQL database schema export plugin ;";
         sWarningMsg += "\n\t - or to manage the database schema with an external tool provided by the SGBD (SQLite Manager for SQLite, pgAdmin for PostgreSQL, MySQL Workbench for MySQL, etc...) ;";
         sWarningMsg += "\n\t - or to generate database schema using the introspection engine of QxOrm library : go to 'http://www.qxorm.com/qxorm_en/faq.html#faq_230' web page for more details.";
         qDebug("[QxOrm] %s", qPrintable(sWarningMsg));
      }

      QString sql = dao.builder().buildSql().getSqlQuery();
      if (sql.isEmpty()) { return dao.errEmpty(); }
      if (! dao.query().exec(sql)) { return dao.errFailed(); }

      long index = 0; qx::IxSqlRelation * pRelation = NULL;
      while ((pRelation = dao.builder().nextRelation(index)))
      {
         QString sqlExtraTable = pRelation->createExtraTable();
         if (sqlExtraTable.isEmpty()) { continue; }
         QSqlQuery queryCreateTable(dao.database());
         bool bExtraTable = queryCreateTable.exec(sqlExtraTable);
         if (! bExtraTable) { dao.updateError(queryCreateTable.lastError()); break; }
      }

      return dao.error();
   }

};

} // namespace detail
} // namespace dao
} // namespace qx
