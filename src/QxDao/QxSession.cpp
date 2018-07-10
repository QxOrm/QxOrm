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

#include <QxDao/QxSession.h>
#include <QxDao/QxSqlDatabase.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

QxSession::QxSession() : boost::noncopyable(), m_bTransaction(false), m_bThrowInEvent(false), m_bAutoOpenClose(false)
{
   m_database = qx::QxSqlDatabase::getDatabaseCloned();
   m_bThrowable = qx::QxSqlDatabase::getSingleton()->getSessionThrowable();
   if (qx::QxSqlDatabase::getSingleton()->getSessionAutoTransaction()) { open(); }
}

QxSession::QxSession(const QSqlDatabase & database) : boost::noncopyable(), m_database(database), m_bTransaction(false), m_bThrowInEvent(false), m_bAutoOpenClose(false)
{
   m_bThrowable = qx::QxSqlDatabase::getSingleton()->getSessionThrowable();
   if (qx::QxSqlDatabase::getSingleton()->getSessionAutoTransaction()) { open(); }
}

QxSession::QxSession(const QSqlDatabase & database, bool bOpenTransaction) : boost::noncopyable(), m_database(database), m_bTransaction(false), m_bThrowInEvent(false), m_bAutoOpenClose(false)
{
   m_bThrowable = qx::QxSqlDatabase::getSingleton()->getSessionThrowable();
   if (bOpenTransaction) { open(); }
}

QxSession::QxSession(const QSqlDatabase & database, bool bOpenTransaction, bool bThrowable) : boost::noncopyable(), m_database(database), m_bTransaction(false), m_bThrowable(bThrowable), m_bThrowInEvent(false), m_bAutoOpenClose(false)
{
   if (bOpenTransaction) { open(); }
}

bool QxSession::open()
{
   if (m_bTransaction) { return true; }
   if (! m_database.isOpen()) { m_bAutoOpenClose = m_database.open(); if (! m_bAutoOpenClose) { appendSqlError(m_database.lastError()); return false; } }
   if (! m_database.driver() || ! m_database.driver()->hasFeature(QSqlDriver::Transactions)) { return false; }
   m_bTransaction = m_database.transaction();
   return m_bTransaction;
}

bool QxSession::close()
{
   bool bCloseOk = true;
   if (m_bTransaction && isValid()) { bCloseOk = commit(); }
   else if (m_bTransaction) { bCloseOk = rollback(); }
   if (m_bAutoOpenClose) { m_database.close(); m_bAutoOpenClose = false; }
   return bCloseOk;
}

bool QxSession::commit()
{
   if (m_bTransaction && ! isValid()) { qDebug("[QxOrm] %s", "qx::QxSession is not valid and 'commit()' method is called"); }
   if (! m_bTransaction) { clear(); return false; }
   bool bCommit = m_database.commit();
   if (bCommit) { clear(); return true; }
   appendSqlError(m_database.lastError());
   m_bTransaction = false;
   return false;
}

bool QxSession::rollback()
{
   if (! m_bTransaction) { clear(); return false; }
   qDebug("[QxOrm] qx::QxSession : '%s'", "rollback transaction");
   bool bRollback = m_database.rollback();
   if (bRollback) { clear(); return true; }
   appendSqlError(m_database.lastError());
   m_bTransaction = false;
   return false;
}

void QxSession::appendSqlError(const QSqlError & err)
{
   if (! err.isValid()) { return; }
   m_lstSqlError.append(err);
   if (m_bThrowInEvent) { return; }
   if (m_bThrowable) { qDebug("[QxOrm] qx::QxSession throw 'qx::dao::sql_error' exception : '%s'", qPrintable(err.text())); }
   if (m_bThrowable) { m_bThrowInEvent = true; throw qx::dao::sql_error(err); }
   m_bThrowInEvent = false;
}

void QxSession::clear()
{
   m_lstSqlError.clear();
   m_bTransaction = false;
}

QxSession & QxSession::operator+= (const QSqlError & err)
{
   appendSqlError(err);
   return (* this);
}

} // namespace qx
