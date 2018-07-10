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

#include <QxPrecompiled.h>

#include <QxService/IxParameter.h>

#include <QxMemLeak/mem_leak.h>

QX_REGISTER_INTERNAL_HELPER_START_FILE_CPP(qx::service::IxParameter)

namespace qx {
namespace service {

IxParameter::IxParameter() { ; }

IxParameter::~IxParameter() { ; }

void IxParameter::registerClass() const { qAssertMsg(false, "[QxOrm] qx::service::IxParameter::registerClass()", "need to override this method with 'qx::service::QxConnect::serialization_qt' or 'qx::service::QxConnect::serialization_json' (use QX_SERVICE_IX_PARAMETER_SERIALIZATION_HPP and QX_SERVICE_IX_PARAMETER_SERIALIZATION_CPP macro to override)"); }

QString IxParameter::getClassName() const { qAssertMsg(false, "[QxOrm] qx::service::IxParameter::getClassName()", "need to override this method with 'qx::service::QxConnect::serialization_qt' or 'qx::service::QxConnect::serialization_json' (use QX_SERVICE_IX_PARAMETER_SERIALIZATION_HPP and QX_SERVICE_IX_PARAMETER_SERIALIZATION_CPP macro to override)"); return ""; }

void IxParameter::save(QDataStream & stream) const { qAssertMsg(false, "[QxOrm] qx::service::IxParameter::save()", "need to override this method with 'qx::service::QxConnect::serialization_qt' (use QX_SERVICE_IX_PARAMETER_SERIALIZATION_HPP and QX_SERVICE_IX_PARAMETER_SERIALIZATION_CPP macro to override)"); Q_UNUSED(stream); }

void IxParameter::load(QDataStream & stream) { qAssertMsg(false, "[QxOrm] qx::service::IxParameter::load()", "need to override this method with 'qx::service::QxConnect::serialization_qt' (use QX_SERVICE_IX_PARAMETER_SERIALIZATION_HPP and QX_SERVICE_IX_PARAMETER_SERIALIZATION_CPP macro to override)"); Q_UNUSED(stream); }

#ifndef _QX_NO_JSON

QJsonValue IxParameter::saveToJson() const { qAssertMsg(false, "[QxOrm] qx::service::IxParameter::saveToJson()", "need to override this method with 'qx::service::QxConnect::serialization_json' (use QX_SERVICE_IX_PARAMETER_SERIALIZATION_HPP and QX_SERVICE_IX_PARAMETER_SERIALIZATION_CPP macro to override)"); return QJsonValue(); }

qx_bool IxParameter::loadFromJson(const QJsonValue & val) { qAssertMsg(false, "[QxOrm] qx::service::IxParameter::loadFromJson()", "need to override this method with 'qx::service::QxConnect::serialization_json' (use QX_SERVICE_IX_PARAMETER_SERIALIZATION_HPP and QX_SERVICE_IX_PARAMETER_SERIALIZATION_CPP macro to override)"); Q_UNUSED(val); return qx_bool(); }

#endif // _QX_NO_JSON

} // namespace service
} // namespace qx

#ifdef _QX_ENABLE_BOOST_SERIALIZATION

namespace boost {
namespace serialization {

template <class Archive>
inline void qx_save(Archive & ar, const qx::service::IxParameter & t, const unsigned int file_version)
{ Q_UNUSED(ar); Q_UNUSED(t); Q_UNUSED(file_version); }

template <class Archive>
inline void qx_load(Archive & ar, qx::service::IxParameter & t, const unsigned int file_version)
{ Q_UNUSED(ar); Q_UNUSED(t); Q_UNUSED(file_version); }

} // namespace serialization
} // namespace boost

#endif // _QX_ENABLE_BOOST_SERIALIZATION

QX_REGISTER_INTERNAL_HELPER_END_FILE_CPP(qx::service::IxParameter)

QDataStream & operator<< (QDataStream & stream, const qx::service::IxParameter & t)
{ Q_UNUSED(t); return stream; }

QDataStream & operator>> (QDataStream & stream, qx::service::IxParameter & t)
{ Q_UNUSED(t); return stream; }

#endif // _QX_ENABLE_QT_NETWORK
