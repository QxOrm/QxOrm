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

#ifndef _QX_VALIDATOR_INVALID_VALUE_X_H_
#define _QX_VALIDATOR_INVALID_VALUE_X_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file QxInvalidValueX.h
 * \author Lionel Marty
 * \ingroup QxValidator
 * \brief List of invalid values
 */

#ifdef _QX_ENABLE_BOOST_SERIALIZATION
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>
#endif // _QX_ENABLE_BOOST_SERIALIZATION

#ifndef _QX_NO_JSON
#include <QtCore/qjsonvalue.h>
#endif // _QX_NO_JSON

#include <QxSerialize/Qt/QxSerialize_QString.h>
#include <QxSerialize/Qt/QxSerialize_QList.h>

#include <QxValidator/QxInvalidValue.h>

#include <QxConvert/QxConvert.h>

#include <QxTraits/get_class_name.h>

namespace qx {
class QxInvalidValueX;
} // namespace qx

QX_DLL_EXPORT QDataStream & operator<< (QDataStream & stream, const qx::QxInvalidValueX & t) BOOST_USED;
QX_DLL_EXPORT QDataStream & operator>> (QDataStream & stream, qx::QxInvalidValueX & t) BOOST_USED;

#ifndef _QX_NO_JSON
namespace qx {
namespace cvt {
namespace detail {
template <> struct QxConvert_ToJson< qx::QxInvalidValueX >;
template <> struct QxConvert_FromJson< qx::QxInvalidValueX >;
QX_DLL_EXPORT QJsonValue QxConvert_ToJson_Helper(const qx::QxInvalidValueX & t, const QString & format) BOOST_USED;
QX_DLL_EXPORT qx_bool QxConvert_FromJson_Helper(const QJsonValue & j, qx::QxInvalidValueX & t, const QString & format) BOOST_USED;
} // namespace detail
} // namespace cvt
} // namespace qx
#endif // _QX_NO_JSON

namespace qx {

/*!
 * \ingroup QxValidator
 * \brief qx::QxInvalidValueX : list of invalid values
 *
 * For more informations about <b>QxValidator module</b>, <a href="http://www.qxorm.com/qxorm_en/faq.html#faq_250" target="_blank">goto the FAQ of QxOrm website</a> :
 * <a href="http://www.qxorm.com/qxorm_en/faq.html#faq_250" target="_blank">http://www.qxorm.com/qxorm_en/faq.html#faq_250</a>
 */
class QX_DLL_EXPORT QxInvalidValueX
{

#ifdef _QX_ENABLE_BOOST_SERIALIZATION
   friend class boost::serialization::access;
#endif // _QX_ENABLE_BOOST_SERIALIZATION

   friend QDataStream & ::operator<< (QDataStream & stream, const qx::QxInvalidValueX & t);
   friend QDataStream & ::operator>> (QDataStream & stream, qx::QxInvalidValueX & t);

#ifndef _QX_NO_JSON
   friend struct qx::cvt::detail::QxConvert_ToJson< qx::QxInvalidValueX >;
   friend struct qx::cvt::detail::QxConvert_FromJson< qx::QxInvalidValueX >;
   friend QJsonValue qx::cvt::detail::QxConvert_ToJson_Helper(const qx::QxInvalidValueX & t, const QString & format);
   friend qx_bool qx::cvt::detail::QxConvert_FromJson_Helper(const QJsonValue & j, qx::QxInvalidValueX & t, const QString & format);
#endif // _QX_NO_JSON

protected:

   QList<QxInvalidValue> m_lstInvalidValues;    //!< List of invalid values
   QString m_sCurrentPath;                      //!< Current path of validation process

public:

   QxInvalidValueX();
   virtual ~QxInvalidValueX();

   QString getCurrentPath() const;
   void setCurrentPath(const QString & s);

   long count() const;
   QxInvalidValue at(long l) const;
   void insert(const IxValidator * pValidator);
   void insert(const QString & sMessage);
   void insert(const QxInvalidValue & invalidValue);
   void insert(const QxInvalidValueX & other);

   QString text() const;
   void dump() const;

   inline operator bool() const
   { return (m_lstInvalidValues.count() == 0); }

private:

#ifdef _QX_ENABLE_BOOST_SERIALIZATION
   template <class Archive>
   void serialize(Archive & ar, const unsigned int file_version)
   {
      Q_UNUSED(file_version);
      ar & boost::serialization::make_nvp("list_invalid_values", m_lstInvalidValues);
      ar & boost::serialization::make_nvp("current_path", m_sCurrentPath);
   }
#endif // _QX_ENABLE_BOOST_SERIALIZATION

};

} // namespace qx

QX_REGISTER_CLASS_NAME(qx::QxInvalidValueX)

#endif // _QX_VALIDATOR_INVALID_VALUE_X_H_
