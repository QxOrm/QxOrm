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

#ifndef _QX_DAO_IMPL_H_
#define _QX_DAO_IMPL_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QxDao/QxDao.h>
#include <QxDao/QxDaoPointer.h>
#include <QxDao/QxDao_IsDirty.h>
#include <QxDao/QxSqlDatabase.h>
#include <QxDao/QxSqlQueryBuilder.h>
#include <QxDao/QxSqlQueryHelper.h>

#include <QxCollection/QxCollection.h>

#include <QxRegister/QxClass.h>

#include <QxTraits/is_qx_registered.h>
#include <QxTraits/is_container.h>
#include <QxTraits/is_smart_ptr.h>
#include <QxTraits/get_base_class.h>
#include <QxTraits/get_class_name_primitive.h>
#include <QxTraits/construct_ptr.h>
#include <QxTraits/generic_container.h>
#include <QxTraits/is_valid_primary_key.h>

#include "../../inl/QxDao/QxDao_Helper.inl"
#include "../../inl/QxDao/QxDao_Count.inl"
#include "../../inl/QxDao/QxDao_FetchById.inl"
#include "../../inl/QxDao/QxDao_FetchById_WithRelation.inl"
#include "../../inl/QxDao/QxDao_FetchAll.inl"
#include "../../inl/QxDao/QxDao_FetchAll_WithRelation.inl"
#include "../../inl/QxDao/QxDao_Insert.inl"
#include "../../inl/QxDao/QxDao_Insert_WithRelation.inl"
#include "../../inl/QxDao/QxDao_Update.inl"
#include "../../inl/QxDao/QxDao_Update_Optimized.inl"
#include "../../inl/QxDao/QxDao_Update_WithRelation.inl"
#include "../../inl/QxDao/QxDao_Save.inl"
#include "../../inl/QxDao/QxDao_Save_WithRelation.inl"
#include "../../inl/QxDao/QxDao_Save_WithRelation_Recursive.inl"
#include "../../inl/QxDao/QxDao_DeleteById.inl"
#include "../../inl/QxDao/QxDao_DeleteAll.inl"
#include "../../inl/QxDao/QxDao_Exist.inl"
#include "../../inl/QxDao/QxDao_CreateTable.inl"
#include "../../inl/QxDao/QxDao_Trigger.inl"
#include "../../inl/QxDao/QxDao_ExecuteQuery.inl"

#endif // _QX_DAO_IMPL_H_
