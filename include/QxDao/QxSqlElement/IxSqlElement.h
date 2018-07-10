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

#ifndef _IX_SQL_ELEMENT_H_
#define _IX_SQL_ELEMENT_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file IxSqlElement.h
 * \author Lionel Marty
 * \ingroup QxDao
 * \brief Common interface for all SQL elements to build SQL query
 */

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/nvp.hpp>

#include <QtSql/qsqlquery.h>

#include <QxDao/QxSqlGenerator/IxSqlGenerator.h>

#include <QxSerialize/Qt/QxSerialize_QList.h>
#include <QxSerialize/Qt/QxSerialize_QStringList.h>
#include <QxSerialize/Qt/QxSerialize_QVariant.h>

namespace qx {
namespace dao {
namespace detail {

/*!
 * \ingroup QxDao
 * \brief qx::dao::detail::IxSqlElement : common interface for all SQL elements to build SQL query
 */
class QX_DLL_EXPORT IxSqlElement
{

public:

   enum type_class { _no_type, _sql_compare, _sql_element_temp, _sql_expression, _sql_free_text, 
                     _sql_in, _sql_is_between, _sql_is_null, _sql_limit, _sql_sort };

protected:

   int               m_iIndex;            //!< Index of SQL element to build unique string
   QStringList       m_lstColumns;        //!< List of columns associated to SQL element
   QStringList       m_lstKeys;           //!< List of keys associated to SQL element
   QList<QVariant>   m_lstValues;         //!< List of values associated to SQL element
   IxSqlGenerator *  m_pSqlGenerator;     //!< SQL generator to build SQL query specific for each database

public:

   IxSqlElement(int index);
   virtual ~IxSqlElement();

   void setColumn(const QString & column);
   void setColumns(const QStringList & columns);
   void setValue(const QVariant & val);
   void setValues(const QVariantList & values);

   virtual IxSqlElement::type_class getTypeClass() const = 0;

   virtual QString toString() const = 0;
   virtual void resolve(QSqlQuery & query) const = 0;
   virtual void postProcess(QString & sql) const = 0;

   virtual void clone(IxSqlElement * other);

   template <class Archive>
   void qxSave(Archive & ar) const
   {
      QString sExtraSettings = getExtraSettings();
      ar << boost::serialization::make_nvp("index", m_iIndex);
      ar << boost::serialization::make_nvp("list_columns", m_lstColumns);
      ar << boost::serialization::make_nvp("list_keys", m_lstKeys);
      ar << boost::serialization::make_nvp("list_values", m_lstValues);
      ar << boost::serialization::make_nvp("extra_settings", sExtraSettings);
   }

   template <class Archive>
   void qxLoad(Archive & ar)
   {
      QString sExtraSettings;
      ar >> boost::serialization::make_nvp("index", m_iIndex);
      ar >> boost::serialization::make_nvp("list_columns", m_lstColumns);
      ar >> boost::serialization::make_nvp("list_keys", m_lstKeys);
      ar >> boost::serialization::make_nvp("list_values", m_lstValues);
      ar >> boost::serialization::make_nvp("extra_settings", sExtraSettings);
      setExtraSettings(sExtraSettings);
   }

protected:

   void updateKeys();

   virtual QString getExtraSettings() const = 0;
   virtual void setExtraSettings(const QString & s) = 0;

};

typedef boost::shared_ptr<IxSqlElement> IxSqlElement_ptr;

} // namespace detail
} // namespace dao
} // namespace qx

#endif // _IX_SQL_ELEMENT_H_
