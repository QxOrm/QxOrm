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

#ifdef _QX_ENABLE_QT_NETWORK
#ifndef _IX_SERVICE_PARAMETER_H_
#define _IX_SERVICE_PARAMETER_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file IxParameter.h
 * \author Lionel Marty
 * \ingroup QxService
 * \brief Common interface for all parameters transfered by QxService module of QxOrm library
 */

#include <QtCore/qdatastream.h>

#ifndef _QX_NO_JSON
#include <QtCore/qjsonvalue.h>
#endif // _QX_NO_JSON

#include <QxRegister/QxRegisterInternalHelper.h>

namespace qx {
namespace service {
class IxParameter;
} // namespace service
} // namespace qx

QX_DLL_EXPORT QDataStream & operator<< (QDataStream & stream, const qx::service::IxParameter & t) BOOST_USED;
QX_DLL_EXPORT QDataStream & operator>> (QDataStream & stream, qx::service::IxParameter & t) BOOST_USED;

namespace qx {
namespace service {

/*!
 * \ingroup QxService
 * \brief qx::service::IxParameter : common interface for all parameters transfered by QxService module of QxOrm library
 *
 * <a href="http://www.qxorm.com/qxorm_en/tutorial_2.html" target="_blank">Click here to access to a tutorial to explain how to work with QxService module.</a>
 */
class QX_DLL_EXPORT IxParameter
{

   friend QDataStream & ::operator<< (QDataStream & stream, const qx::service::IxParameter & t);
   friend QDataStream & ::operator>> (QDataStream & stream, qx::service::IxParameter & t);

public:

   IxParameter();
   virtual ~IxParameter();

   // Need to override these methods only if you are using 'qx::service::QxConnect::serialization_qt' type (based on QDataStream) or 'qx::service::QxConnect::serialization_json' type (based on QJson engine)
   // You can use QX_SERVICE_IX_PARAMETER_SERIALIZATION_HPP and QX_SERVICE_IX_PARAMETER_SERIALIZATION_CPP macro to override
   virtual void registerClass() const;
   virtual QString getClassName() const;
   virtual void save(QDataStream & stream) const;
   virtual void load(QDataStream & stream);

#ifndef _QX_NO_JSON
   virtual QJsonValue saveToJson() const;
   virtual qx_bool loadFromJson(const QJsonValue & val);
#endif // _QX_NO_JSON

};

typedef qx_shared_ptr<IxParameter> IxParameter_ptr;

} // namespace service
} // namespace qx

QX_REGISTER_INTERNAL_HELPER_HPP(QX_DLL_EXPORT, qx::service::IxParameter, 0)

#define QX_SERVICE_IX_PARAMETER_QDATASTREAM_HPP(className) \
public: \
virtual void save(QDataStream & stream) const; \
virtual void load(QDataStream & stream);

#define QX_SERVICE_IX_PARAMETER_QDATASTREAM_CPP(className) \
void className::save(QDataStream & stream) const { qx::QxSerializeRegistered< className >::save(stream, (* this)); } \
void className::load(QDataStream & stream) { qx::QxSerializeRegistered< className >::load(stream, (* this)); }

#ifndef _QX_NO_JSON

#define QX_SERVICE_IX_PARAMETER_QJSON_HPP(className) \
public: \
virtual QJsonValue saveToJson() const; \
virtual qx_bool loadFromJson(const QJsonValue & val);

#define QX_SERVICE_IX_PARAMETER_QJSON_CPP(className) \
QJsonValue className::saveToJson() const { return qx::cvt::detail::QxSerializeJsonRegistered< className >::save((* this), ""); } \
qx_bool className::loadFromJson(const QJsonValue & val) { return qx::cvt::detail::QxSerializeJsonRegistered< className >::load(val, (* this), ""); }

#else // _QX_NO_JSON
#define QX_SERVICE_IX_PARAMETER_QJSON_HPP(className) /* Nothing */
#define QX_SERVICE_IX_PARAMETER_QJSON_CPP(className) /* Nothing */
#endif // _QX_NO_JSON

#define QX_SERVICE_IX_PARAMETER_SERIALIZATION_HPP(className) \
QX_SERVICE_IX_PARAMETER_QDATASTREAM_HPP(className) \
QX_SERVICE_IX_PARAMETER_QJSON_HPP(className) \
public: \
virtual void registerClass() const; \
virtual QString getClassName() const;

#define QX_SERVICE_IX_PARAMETER_SERIALIZATION_CPP(className) \
QX_SERVICE_IX_PARAMETER_QDATASTREAM_CPP(className) \
QX_SERVICE_IX_PARAMETER_QJSON_CPP(className) \
void className::registerClass() const { qx::QxClass< className >::getSingleton(); } \
QString className::getClassName() const { return #className; }

#endif // _IX_SERVICE_PARAMETER_H_
#endif // _QX_ENABLE_QT_NETWORK
