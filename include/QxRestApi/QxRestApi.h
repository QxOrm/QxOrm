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

#ifndef _QX_REST_API_H_
#define _QX_REST_API_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxRestApi.h
 * \author Lionel Marty
 * \ingroup QxRestApi
 * \brief Provide a REST API to send requests in JSON format from external application, from web-site or from QML view (https://www.qxorm.com/qxorm_en/manual.html#manual_97)
 */

#ifdef _QX_NO_PRECOMPILED_HEADER
#ifndef Q_MOC_RUN
#include <QxPrecompiled.h> // Need to include precompiled header for the generated moc file
#endif // Q_MOC_RUN
#endif // _QX_NO_PRECOMPILED_HEADER

#include <QtSql/qsqlerror.h>

#ifndef _QX_NO_JSON
#include <QtCore/qjsonvalue.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsondocument.h>
#endif // _QX_NO_JSON

namespace qx {

/*!
 * \ingroup QxRestApi
 * \brief qx::QxRestApi : provide a REST API to send requests in JSON format from external application, from web-site or from QML view (https://www.qxorm.com/qxorm_en/manual.html#manual_97)
 */
class QX_DLL_EXPORT QxRestApi : public QObject
{

   Q_OBJECT

private:

   struct QxRestApiImpl;
   std::unique_ptr<QxRestApiImpl> m_pImpl; //!< Private implementation idiom

public:

   QxRestApi(QObject * parent = NULL);
   virtual ~QxRestApi();

   Q_INVOKABLE QString processRequest(const QString & request);
   Q_INVOKABLE void clearAll();

   Q_INVOKABLE QString getErrorDesc() const;
   Q_INVOKABLE int getErrorCode() const;
   QSqlError getError() const;

#if (QT_VERSION >= 0x050300)
   Q_INVOKABLE QString getNativeErrorCode() const;
#endif // (QT_VERSION >= 0x050300)

   Q_INVOKABLE void setEntity(const QString & entity);
   Q_INVOKABLE void setAction(const QString & action);
   Q_INVOKABLE void setFunction(const QString & fct);
   Q_INVOKABLE void setColumns(const QStringList & columns);
   Q_INVOKABLE void setRelations(const QStringList & relations);
   Q_INVOKABLE void setOutputFormat(const QStringList & outputFormat);
   Q_INVOKABLE void setDatabase(const QString & database);
   Q_INVOKABLE void setQuery(const QString & query);
   Q_INVOKABLE void setData(const QString & data);

#ifndef _QX_NO_JSON
   QJsonValue processRequest(const QJsonValue & request);
   void setData(const QJsonValue & data);
#endif // _QX_NO_JSON

};

} // namespace qx

#endif // _QX_REST_API_H_
