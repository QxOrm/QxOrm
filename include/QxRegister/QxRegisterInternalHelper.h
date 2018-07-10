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

#ifndef _QX_REGISTER_INTERNAL_HELPER_H_
#define _QX_REGISTER_INTERNAL_HELPER_H_

#ifdef _MSC_VER
#pragma once
#endif

#ifdef _QX_ENABLE_BOOST_SERIALIZATION
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/utility.hpp>
#endif // _QX_ENABLE_BOOST_SERIALIZATION

#include <QxConvert/QxConvert.h>
#include <QxConvert/QxConvert_Impl.h>
#include <QxConvert/QxConvert_Export.h>

#include <QxRegister/QxClass.h>
#include <QxRegister/QxRegister.h>

#include <QxSerialize/QxSerializeFastCompil.h>

#include <QxTraits/get_class_name.h>

#include <QxDao/IxPersistable.h>

#ifdef _QX_ENABLE_BOOST_SERIALIZATION

#define QX_REGISTER_INTERNAL_HELPER_HPP(dllImportExport, className, version) \
BOOST_CLASS_VERSION(className, version) \
QX_REGISTER_CLASS_NAME(className) \
QX_REGISTER_CLASS_MAPPING_FCT_HPP(dllImportExport, className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_HPP(dllImportExport, className) \
QX_BOOST_EXPORT_SERIALIZATION_FAST_COMPIL_HPP(className) \
QX_REGISTER_BOOST_SERIALIZE_HELPER(className)

#define QX_REGISTER_INTERNAL_HELPER_START_FILE_CPP(className) \
QX_REGISTER_CLASS_MAPPING_FCT_EMPTY_CPP(className) \
QX_BOOST_EXPORT_SERIALIZATION_FAST_COMPIL_CPP(className)

#define QX_REGISTER_INTERNAL_HELPER_END_FILE_CPP(className) \
QX_SERIALIZE_FAST_COMPIL_SAVE_LOAD_CPP(className) \
QX_REGISTER_BOOST_SERIALIZE_HELPER_CPP(className)

#else // _QX_ENABLE_BOOST_SERIALIZATION

#define QX_REGISTER_INTERNAL_HELPER_HPP(dllImportExport, className, version) \
BOOST_CLASS_VERSION(className, version) \
QX_REGISTER_CLASS_NAME(className) \
QX_REGISTER_CLASS_MAPPING_FCT_HPP(dllImportExport, className)

#define QX_REGISTER_INTERNAL_HELPER_START_FILE_CPP(className) \
QX_REGISTER_CLASS_MAPPING_FCT_EMPTY_CPP(className)

#define QX_REGISTER_INTERNAL_HELPER_END_FILE_CPP(className) /* Nothing */

#endif // _QX_ENABLE_BOOST_SERIALIZATION

#endif // _QX_REGISTER_INTERNAL_HELPER_H_
