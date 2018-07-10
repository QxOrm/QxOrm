/****************************************************************************
**
** http://www.qxorm.com/
** http://sourceforge.net/projects/qxorm/
** Original file by Lionel Marty
**
** This file is part of the QxOrm library
**
** This software is provided 'as-is', without any express or implied
** warranty. In no event will the authors be held liable for any
** damages arising from the use of this software.
**
** GNU Lesser General Public License Usage
** This file must be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file 'license.lgpl.txt' included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you have questions regarding the use of this file, please contact :
** contact@qxorm.com
**
****************************************************************************/

#ifndef _QX_REGISTER_INTERNAL_HELPER_H_
#define _QX_REGISTER_INTERNAL_HELPER_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/utility.hpp>

#include <QxCommon/QxStringCvt.h>
#include <QxCommon/QxStringCvt_Impl.h>
#include <QxCommon/QxStringCvt_Export.h>

#include <QxRegister/QxClass.h>
#include <QxRegister/QxRegister.h>

#include <QxSerialize/QxSerializeFastCompil.h>

#include <QxTraits/get_class_name.h>

#include <QxDao/IxPersistable.h>

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

#endif // _QX_REGISTER_INTERNAL_HELPER_H_
