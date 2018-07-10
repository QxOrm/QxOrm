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

#ifndef _QX_ORM_H_
#define _QX_ORM_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \defgroup QxCommon QxCommon : QxOrm library common tools and macros
 * \defgroup QxCollection QxCollection : QxOrm library container (keep insertion order + quick access by index + quick access by key)
 * \defgroup QxSingleton QxSingleton : QxOrm library thread-safe singleton pattern
 * \defgroup QxFactory QxFactory : QxOrm library factory pattern used by introspection engine
 * \defgroup QxDataMember QxDataMember : QxOrm library data member (or property) used by introspection engine
 * \defgroup QxFunction QxFunction : QxOrm library function used by introspection engine
 * \defgroup QxRegister QxRegister : QxOrm library register context used by introspection engine (class, function, property...)
 * \defgroup QxSerialize QxSerialize : QxOrm library serialization engine based on 'boost::serialization' library
 * \defgroup QxTraits QxTraits : QxOrm library traits (template metaprogramming) not available in 'boost::type_traits' library
 * \defgroup QxDao QxDao : QxOrm library database communication used by persistence engine (ORM - Object Relational Mapping)
 * \defgroup QxValidator QxValidator : QxOrm library validation engine using validator pattern
 * \defgroup QxModelView QxModelView : All classes registered into QxOrm context can be used with Qt model/view architecture (Qt widgets and/or QML views)
 * \defgroup QxService QxService : QxOrm library services engine to provide easy and powerful way to create C++ application server (to transfer data over network)
 * \defgroup QxCache QxCache : QxOrm library basic thread-safe cache feature to backup and restore any kind of objects (for example, object fetched from database)
 * \defgroup QxConvert QxConvert : QxOrm library conversion tools to-from QString type and to-from QVariant type
 * \defgroup QxExtras QxExtras : QxOrm library extra-tools (for example : enable std::optional for C++17 compilers, enable boost::optional feature without enabling all boost features)
 * \defgroup QxMemLeak QxMemLeak : QxOrm library memory leak detection (by Wu Yongwei)
 */

#include <QxPrecompiled.h>

#include <QxCommon/QxConfig.h>
#include <QxCommon/QxMacro.h>
#include <QxCommon/QxHashValue.h>
#include <QxCommon/QxBool.h>
#include <QxCommon/QxCache.h>
#include <QxCommon/QxPropertyBag.h>
#include <QxCommon/QxSimpleCrypt.h>
#include <QxCommon/QxException.h>
#include <QxCommon/QxExceptionCode.h>
#include <QxCommon/QxAnyCastDynamic.h>
#include <QxCommon/QxAny.h>

#include <QxCollection/IxCollection.h>
#include <QxCollection/QxCollection.h>
#include <QxCollection/QxCollectionIterator.h>
#include <QxCollection/QxForeach.h>

#include <QxSingleton/IxSingleton.h>
#include <QxSingleton/QxSingleton.h>
#include <QxSingleton/QxSingletonX.h>
#include <QxSingleton/QxSingletonInit.h>

#include <QxFactory/IxFactory.h>
#include <QxFactory/QxFactory.h>
#include <QxFactory/QxFactoryX.h>

#include <QxTraits/qx_traits.h>

#include <QxDataMember/IxDataMember.h>
#include <QxDataMember/IxDataMemberX.h>
#include <QxDataMember/QxDataMember.h>
#include <QxDataMember/QxDataMemberX.h>
#include <QxDataMember/QxDataMember_QObject.h>

#include <QxFunction/QxFunctionInclude.h>

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
#include <QxDao/QxDaoThrowable.h>
#include <QxDao/QxDao_Impl.h>
#include <QxDao/QxDaoStrategy.h>
#include <QxDao/QxDaoPointer.h>
#include <QxDao/QxDao_IsDirty.h>
#include <QxDao/QxSoftDelete.h>
#include <QxDao/QxSqlError.h>
#include <QxDao/QxSession.h>
#include <QxDao/QxDateNeutral.h>
#include <QxDao/QxTimeNeutral.h>
#include <QxDao/QxDateTimeNeutral.h>
#include <QxDao/IxPersistable.h>
#include <QxDao/QxSqlJoin.h>
#include <QxDao/QxSqlRelationLinked.h>
#include <QxDao/QxDaoAsync.h>
#include <QxDao/QxSqlSaveMode.h>

#include <QxDao/QxSqlElement/QxSqlElement.h>

#include <QxDao/QxSqlGenerator/QxSqlGenerator.h>

#ifdef _QX_ENABLE_BOOST_SERIALIZATION
#include <QxSerialize/QxSerialize.h>
#endif // _QX_ENABLE_BOOST_SERIALIZATION

#include <QxSerialize/QxSerializeQDataStream.h>
#include <QxSerialize/QDataStream/QxSerializeQDataStream_all_include.h>
#include <QxSerialize/QxClone.h>
#include <QxSerialize/QxDump.h>

#ifndef _QX_NO_JSON
#include <QxSerialize/QJson/QxSerializeQJson_all_include.h>
#include <QxSerialize/QxSerializeQJson.h>
#endif // _QX_NO_JSON

#include <QxConvert/QxConvert.h>
#include <QxConvert/QxConvert_Impl.h>
#include <QxConvert/QxConvert_Export.h>

#include <QxRegister/IxClass.h>
#include <QxRegister/QxClass.h>
#include <QxRegister/QxClassX.h>
#include <QxRegister/QxClassName.h>
#include <QxRegister/QxRegister.h>
#include <QxRegister/QxRegisterInternalHelper.h>
#include <QxRegister/IxTypeInfo.h>
#include <QxRegister/QxRegisterQtProperty.h>
#include <QxRegister/QxVersion.h>

#include <QxValidator/IxValidator.h>
#include <QxValidator/IxValidatorX.h>
#include <QxValidator/QxInvalidValue.h>
#include <QxValidator/QxInvalidValueX.h>
#include <QxValidator/QxValidator.h>
#include <QxValidator/QxValidatorX.h>
#include <QxValidator/QxValidatorError.h>
#include <QxValidator/QxValidatorFct.h>

#endif // _QX_ORM_H_
