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

#ifndef _QX_VALIDATOR_INVALID_VALUE_H_
#define _QX_VALIDATOR_INVALID_VALUE_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxInvalidValue.h
 * \author Lionel Marty
 * \ingroup QxValidator
 * \brief Invalid value when a property fails to pass a constraint
 */

#ifdef _QX_ENABLE_BOOST_SERIALIZATION
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>
#endif // _QX_ENABLE_BOOST_SERIALIZATION

#ifndef _QX_NO_JSON
#include <QtCore/qjsonvalue.h>
#endif // _QX_NO_JSON

#include <QxSerialize/boost/QxSerialize_shared_ptr.h>

#include <QxSerialize/Qt/QxSerialize_QString.h>
#include <QxSerialize/Qt/QxSerialize_QVariant.h>
#include <QxSerialize/Qt/QxSerialize_QHash.h>

#include <QxConvert/QxConvert.h>

#include <QxTraits/get_class_name.h>

#include <QxCommon/QxPropertyBag.h>

namespace qx {
class IxValidator;
class QxInvalidValue;
} // namespace qx

QX_DLL_EXPORT QDataStream & operator<< (QDataStream & stream, const qx::QxInvalidValue & t) BOOST_USED;
QX_DLL_EXPORT QDataStream & operator>> (QDataStream & stream, qx::QxInvalidValue & t) BOOST_USED;

#ifndef _QX_NO_JSON
namespace qx {
namespace cvt {
namespace detail {
template <> struct QxConvert_ToJson< qx::QxInvalidValue >;
template <> struct QxConvert_FromJson< qx::QxInvalidValue >;
QX_DLL_EXPORT QJsonValue QxConvert_ToJson_Helper(const qx::QxInvalidValue & t, const QString & format) BOOST_USED;
QX_DLL_EXPORT qx_bool QxConvert_FromJson_Helper(const QJsonValue & j, qx::QxInvalidValue & t, const QString & format) BOOST_USED;
} // namespace detail
} // namespace cvt
} // namespace qx
#endif // _QX_NO_JSON

namespace qx {

/*!
 * \ingroup QxValidator
 * \brief qx::QxInvalidValue : invalid value when a property fails to pass a constraint
 *
 * For more informations about <b>QxValidator module</b>, <a href="http://www.qxorm.com/qxorm_en/faq.html#faq_250" target="_blank">goto the FAQ of QxOrm website</a> :
 * <a href="http://www.qxorm.com/qxorm_en/faq.html#faq_250" target="_blank">http://www.qxorm.com/qxorm_en/faq.html#faq_250</a>
 */
class QX_DLL_EXPORT QxInvalidValue : public QxPropertyBag
{

#ifdef _QX_ENABLE_BOOST_SERIALIZATION
   friend class boost::serialization::access;
#endif // _QX_ENABLE_BOOST_SERIALIZATION

   friend QDataStream & ::operator<< (QDataStream & stream, const qx::QxInvalidValue & t);
   friend QDataStream & ::operator>> (QDataStream & stream, qx::QxInvalidValue & t);

#ifndef _QX_NO_JSON
   friend struct qx::cvt::detail::QxConvert_ToJson< qx::QxInvalidValue >;
   friend struct qx::cvt::detail::QxConvert_FromJson< qx::QxInvalidValue >;
   friend QJsonValue qx::cvt::detail::QxConvert_ToJson_Helper(const qx::QxInvalidValue & t, const QString & format);
   friend qx_bool qx::cvt::detail::QxConvert_FromJson_Helper(const QJsonValue & j, qx::QxInvalidValue & t, const QString & format);
#endif // _QX_NO_JSON

protected:

   QString m_sMessage;                    //!< Message associated to the invalid value
   QString m_sPropertyName;               //!< Property name failing to pass the constraint
   QString m_sPath;                       //!< Path of property failing to pass the constraint
   const IxValidator * m_pValidator;      //!< IxValidator class associated to the invalid value

public:

   QxInvalidValue();
   virtual ~QxInvalidValue();

   QString getMessage() const                   { return m_sMessage; }
   QString getPropertyName() const              { return m_sPropertyName; }
   QString getPath() const                      { return m_sPath; }
   QString getFullName() const;
   const IxValidator * getValidator() const;

   void setMessage(const QString & s)           { m_sMessage = s; }
   void setPropertyName(const QString & s)      { m_sPropertyName = s; }
   void setPath(const QString & s)              { m_sPath = s; }
   void setValidator(const IxValidator * p);

private:

#ifdef _QX_ENABLE_BOOST_SERIALIZATION
   template <class Archive>
   void serialize(Archive & ar, const unsigned int file_version)
   {
      Q_UNUSED(file_version);
      ar & boost::serialization::make_nvp("message", m_sMessage);
      ar & boost::serialization::make_nvp("property_name", m_sPropertyName);
      ar & boost::serialization::make_nvp("path", m_sPath);
      ar & boost::serialization::make_nvp("list_property_bag", this->m_lstPropertyBag);
   }
#endif // _QX_ENABLE_BOOST_SERIALIZATION

};

} // namespace qx

QX_REGISTER_CLASS_NAME(qx::QxInvalidValue)

#endif // _QX_VALIDATOR_INVALID_VALUE_H_
