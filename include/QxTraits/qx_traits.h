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

#ifndef _QX_TRAITS_H_
#define _QX_TRAITS_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QxTraits/get_base_class.h>
#include <QxTraits/get_primary_key.h>
#include <QxTraits/get_class_name.h>
#include <QxTraits/get_class_name_primitive.h>
#include <QxTraits/is_container.h>
#include <QxTraits/is_ptr_base_of.h>
#include <QxTraits/is_ptr_to_pod.h>
#include <QxTraits/is_qt_hash.h>
#include <QxTraits/is_qt_linked_list.h>
#include <QxTraits/is_qt_list.h>
#include <QxTraits/is_qt_map.h>
#include <QxTraits/is_qt_multi_hash.h>
#include <QxTraits/is_qt_multi_map.h>
#include <QxTraits/is_qt_set.h>
#include <QxTraits/is_qt_shared_data_ptr.h>
#include <QxTraits/is_qt_shared_ptr.h>
#include <QxTraits/is_qt_scoped_ptr.h>
#include <QxTraits/is_qt_vector.h>
#include <QxTraits/is_qt_weak_ptr.h>
#include <QxTraits/is_qt_variant_compatible.h>
#include <QxTraits/is_qx_collection.h>
#include <QxTraits/is_qx_pod.h>
#include <QxTraits/is_qx_registered.h>
#include <QxTraits/is_smart_ptr.h>
#include <QxTraits/is_std_list.h>
#include <QxTraits/is_std_map.h>
#include <QxTraits/is_std_set.h>
#include <QxTraits/is_std_vector.h>
#include <QxTraits/archive_wide_traits.h>
#include <QxTraits/archive_printable.h>
#include <QxTraits/remove_attr.h>
#include <QxTraits/remove_smart_ptr.h>
#include <QxTraits/construct_ptr.h>
#include <QxTraits/get_sql_type.h>
#include <QxTraits/generic_container.h>
#include <QxTraits/is_valid_primary_key.h>
#include <QxTraits/is_qx_dao_ptr.h>
#include <QxTraits/is_equal.h>
#include <QxTraits/qt_meta_object.h>
#include <QxTraits/is_std_shared_ptr.h>
#include <QxTraits/is_std_unique_ptr.h>
#include <QxTraits/is_std_unordered_map.h>
#include <QxTraits/is_std_unordered_set.h>
#include <QxTraits/is_std_weak_ptr.h>

#ifdef _QX_ENABLE_BOOST
#include <QxTraits/is_boost_intrusive_ptr.h>
#include <QxTraits/is_boost_scoped_ptr.h>
#include <QxTraits/is_boost_shared_ptr.h>
#include <QxTraits/is_boost_unordered_map.h>
#include <QxTraits/is_boost_unordered_set.h>
#include <QxTraits/is_boost_weak_ptr.h>
#endif // _QX_ENABLE_BOOST

#endif // _QX_TRAITS_H_
