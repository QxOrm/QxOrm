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

#ifndef _QX_ORM_H_
#define _QX_ORM_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <QxPrecompiled.h>

#include <QxCommon/QxConfig.h>
#include <QxCommon/QxMacro.h>
#include <QxCommon/QxHashValue.h>
#include <QxCommon/QxBool.h>
#include <QxCommon/QxCache.h>

#include <QxMemLeak/bool_array.h>
#include <QxMemLeak/class_level_lock.h>
#include <QxMemLeak/cont_ptr_utils.h>
#include <QxMemLeak/fast_mutex.h>
#include <QxMemLeak/fixed_mem_pool.h>
#include <QxMemLeak/mem_pool_base.h>
#include <QxMemLeak/object_level_lock.h>
#include <QxMemLeak/pctimer.h>
#include <QxMemLeak/set_assign.h>
#include <QxMemLeak/static_assert.h>
#include <QxMemLeak/static_mem_pool.h>

#include <QxCollection/IxCollection.h>
#include <QxCollection/QxCollection.h>
#include <QxCollection/QxCollectionIterator.h>
#include <QxCollection/QxForeach.h>

#include <QxSingleton/IxSingleton.h>
#include <QxSingleton/QxSingleton.h>
#include <QxSingleton/QxSingletonX.h>

#include <QxFactory/IxFactory.h>
#include <QxFactory/QxFactory.h>
#include <QxFactory/QxFactoryX.h>

#include <QxTraits/qx_traits.h>

#include <QxDataMember/IxDataMember.h>
#include <QxDataMember/IxDataMemberX.h>
#include <QxDataMember/QxDataMember.h>
#include <QxDataMember/QxDataMemberX.h>

#include <QxFunction/QxFunctionInclude.h>

#include <QxXml/QxXmlReader.h>
#include <QxXml/QxXmlWriter.h>
#include <QxXml/QxXml.h>

#include <QxDao/IxSqlQueryBuilder.h>
#include <QxDao/QxSqlQueryBuilder.h>
#include <QxDao/QxSqlQueryHelper.h>
#include <QxDao/QxSqlQuery.h>
#include <QxDao/QxSqlDatabase.h>
#include <QxDao/IxSqlRelation.h>
#include <QxDao/QxSqlRelation.h>
#include <QxDao/QxSqlRelationParams.h>
#include <QxDao/QxSqlRelation_ManyToMany.h>
#include <QxDao/QxSqlRelation_ManyToOne.h>
#include <QxDao/QxSqlRelation_OneToMany.h>
#include <QxDao/QxSqlRelation_OneToOne.h>
#include <QxDao/QxSqlRelation_RawData.h>
#include <QxDao/QxDao.h>
#include <QxDao/QxDao_Impl.h>
#include <QxDao/QxDaoStrategy.h>
#include <QxDao/QxDaoPointer.h>
#include <QxDao/QxDao_IsDirty.h>

#include <QxSerialize/QxSerialize.h>

#include <QxCommon/QxStringCvt.h>
#include <QxCommon/QxStringCvt_Impl.h>
#include <QxCommon/QxStringCvt_Export.h>

#include <QxRegister/IxClass.h>
#include <QxRegister/QxClass.h>
#include <QxRegister/QxClassX.h>
#include <QxRegister/QxClassName.h>
#include <QxRegister/QxRegister.h>
#include <QxRegister/QxRegisterInternalHelper.h>
#include <QxRegister/IxTypeInfo.h>

#include <QxService/IxParameter.h>
#include <QxService/IxService.h>
#include <QxService/QxClientAsync.h>
#include <QxService/QxConnect.h>
#include <QxService/QxServer.h>
#include <QxService/QxService.h>
#include <QxService/QxThread.h>
#include <QxService/QxThreadPool.h>
#include <QxService/QxTools.h>
#include <QxService/QxTransaction.h>

#endif // _QX_ORM_H_
