/****************************************************************************
**
** Copyright (C) 2010 QxOrm France and/or its subsidiary(-ies)
** Contact: QxOrm France Information (contact@qxorm.com)
**
** This file is part of the QxOrm library
**
** Commercial Usage
** Licensees holding valid QxOrm Commercial licenses may use this file in
** accordance with the QxOrm Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and QxOrm France
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file 'license.gpl3.txt' included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html
**
** If you are unsure which license is appropriate for your use, please
** contact the support department at support@qxorm.com
**
****************************************************************************/

#ifndef _QX_TRAITS_H_
#define _QX_TRAITS_H_

#ifdef _MSC_VER
#pragma once
#endif

#include "../../include/QxTraits/get_base_class.h"
#include "../../include/QxTraits/get_primary_key.h"
#include "../../include/QxTraits/get_class_name.h"
#include "../../include/QxTraits/get_class_name_primitive.h"
#include "../../include/QxTraits/is_boost_intrusive_ptr.h"
#include "../../include/QxTraits/is_boost_scoped_ptr.h"
#include "../../include/QxTraits/is_boost_shared_ptr.h"
#include "../../include/QxTraits/is_boost_unordered_map.h"
#include "../../include/QxTraits/is_boost_unordered_set.h"
#include "../../include/QxTraits/is_boost_weak_ptr.h"
#include "../../include/QxTraits/is_container.h"
#include "../../include/QxTraits/is_container_base_of.h"
#include "../../include/QxTraits/is_container_key_value.h"
#include "../../include/QxTraits/is_container_to_pod.h"
#include "../../include/QxTraits/is_ptr_base_of.h"
#include "../../include/QxTraits/is_ptr_to_pod.h"
#include "../../include/QxTraits/is_qt_hash.h"
#include "../../include/QxTraits/is_qt_linked_list.h"
#include "../../include/QxTraits/is_qt_list.h"
#include "../../include/QxTraits/is_qt_map.h"
#include "../../include/QxTraits/is_qt_multi_hash.h"
#include "../../include/QxTraits/is_qt_multi_map.h"
#include "../../include/QxTraits/is_qt_set.h"
#include "../../include/QxTraits/is_qt_shared_data_ptr.h"
#include "../../include/QxTraits/is_qt_shared_ptr.h"
#include "../../include/QxTraits/is_qt_scoped_ptr.h"
#include "../../include/QxTraits/is_qt_vector.h"
#include "../../include/QxTraits/is_qt_weak_ptr.h"
#include "../../include/QxTraits/is_qt_variant_compatible.h"
#include "../../include/QxTraits/is_qx_collection.h"
#include "../../include/QxTraits/is_qx_pod.h"
#include "../../include/QxTraits/is_qx_registered.h"
#include "../../include/QxTraits/is_smart_ptr.h"
#include "../../include/QxTraits/is_smart_ptr_base_of.h"
#include "../../include/QxTraits/is_smart_ptr_to_pod.h"
#include "../../include/QxTraits/is_std_list.h"
#include "../../include/QxTraits/is_std_map.h"
#include "../../include/QxTraits/is_std_set.h"
#include "../../include/QxTraits/is_std_vector.h"
#include "../../include/QxTraits/archive_wide_traits.h"
#include "../../include/QxTraits/archive_printable.h"
#include "../../include/QxTraits/remove_attr.h"
#include "../../include/QxTraits/remove_smart_ptr.h"
#include "../../include/QxTraits/construct_ptr.h"
#include "../../include/QxTraits/get_sql_type.h"
#include "../../include/QxTraits/generic_container.h"
#include "../../include/QxTraits/is_valid_primary_key.h"

#endif // _QX_TRAITS_H_
