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

/*!
 * \file all.cpp
 * \author Lionel Marty
 * \brief all.cpp file can be used to perform a Unity Build to reduce compilation times (http://stackoverflow.com/questions/543697/include-all-cpp-files-into-a-single-compilation-unit) : _QX_UNITY_BUILD compilation option must be defined (see QxOrm.pri configuration file for more details)
 */

#ifdef _QX_UNITY_BUILD

#include <QxPrecompiled.h>

#include "./QxMemLeak/bool_array.cpp"
#include "./QxMemLeak/debug_new.cpp"
#include "./QxMemLeak/mem_pool_base.cpp"
#include "./QxMemLeak/static_mem_pool.cpp"

#include "./QxSingleton/IxSingleton.cpp"
#include "./QxSingleton/QxSingletonX.cpp"
#include "./QxSingleton/QxSingletonInit.cpp"

#include "./QxFactory/IxFactory.cpp"
#include "./QxFactory/QxFactoryX.cpp"

#include "./QxCollection/QxCollection.cpp"

#include "./QxCommon/QxBool.cpp"
#include "./QxCommon/QxCache.cpp"
#include "./QxCommon/QxSimpleCrypt.cpp"

#include "./QxConvert/QxConvert_Export.cpp"

#include "./QxRegister/IxClass.cpp"
#include "./QxRegister/QxClassX.cpp"

#include "./QxDataMember/IxDataMember.cpp"
#include "./QxDataMember/IxDataMemberX.cpp"
#include "./QxDataMember/QxDataMember_QObject.cpp"

#include "./QxTraits/unit_test_is_smart_ptr.cpp"
#include "./QxTraits/unit_test_is_container.cpp"

// #include "./QxXml/QxXmlReader.cpp"
// #include "./QxXml/QxXmlWriter.cpp"

#include "./QxDao/IxSqlQueryBuilder.cpp"
#include "./QxDao/QxSqlDatabase.cpp"
#include "./QxDao/IxSqlRelation.cpp"
#include "./QxDao/QxSqlQuery.cpp"
#include "./QxDao/QxSession.cpp"
#include "./QxDao/IxDao_Helper.cpp"
#include "./QxDao/IxPersistable.cpp"
#include "./QxDao/QxSqlRelationLinked.cpp"
#include "./QxDao/QxDaoAsync.cpp"
#include "./QxDao/QxSqlRelationParams.cpp"
#include "./QxDao/QxSoftDelete.cpp"
#include "./QxDao/QxDateNeutral.cpp"
#include "./QxDao/QxDateTimeNeutral.cpp"
#include "./QxDao/QxTimeNeutral.cpp"

#include "./QxDao/QxSqlElement/IxSqlElement.cpp"
#include "./QxDao/QxSqlElement/QxSqlCompare.cpp"
#include "./QxDao/QxSqlElement/QxSqlElementTemp.cpp"
#include "./QxDao/QxSqlElement/QxSqlExpression.cpp"
#include "./QxDao/QxSqlElement/QxSqlFreeText.cpp"
#include "./QxDao/QxSqlElement/QxSqlIn.cpp"
#include "./QxDao/QxSqlElement/QxSqlIsBetween.cpp"
#include "./QxDao/QxSqlElement/QxSqlIsNull.cpp"
#include "./QxDao/QxSqlElement/QxSqlLimit.cpp"
#include "./QxDao/QxSqlElement/QxSqlSort.cpp"

#include "./QxDao/QxSqlGenerator/IxSqlGenerator.cpp"
#include "./QxDao/QxSqlGenerator/QxSqlGenerator_MySQL.cpp"
#include "./QxDao/QxSqlGenerator/QxSqlGenerator_Oracle.cpp"
#include "./QxDao/QxSqlGenerator/QxSqlGenerator_PostgreSQL.cpp"
#include "./QxDao/QxSqlGenerator/QxSqlGenerator_SQLite.cpp"
#include "./QxDao/QxSqlGenerator/QxSqlGenerator_MSSQLServer.cpp"
#include "./QxDao/QxSqlGenerator/QxSqlGenerator_Standard.cpp"

#include "./QxDao/QxRepository/IxRepository.cpp"
#include "./QxDao/QxRepository/QxRepositoryX.cpp"

#include "./QxSerialize/QxSerializeCheckInstance.cpp"

#include "./QxSerialize/QxBoostSerializeHelper/IxBoostSerializeRegisterHelper.cpp"
#include "./QxSerialize/QxBoostSerializeHelper/QxBoostSerializeRegisterHelperX.cpp"

#include "./QxSerialize/boost/QxExportDllBoostArchive.cpp"

#include "./QxSerialize/Qt/QxSerialize_QBrush.cpp"
#include "./QxSerialize/Qt/QxSerialize_QByteArray.cpp"
#include "./QxSerialize/Qt/QxSerialize_QColor.cpp"
#include "./QxSerialize/Qt/QxSerialize_QDate.cpp"
#include "./QxSerialize/Qt/QxSerialize_QDateTime.cpp"
#include "./QxSerialize/Qt/QxSerialize_QFont.cpp"
#include "./QxSerialize/Qt/QxSerialize_QImage.cpp"
#include "./QxSerialize/Qt/QxSerialize_QMatrix.cpp"
#include "./QxSerialize/Qt/QxSerialize_QObject.cpp"
#include "./QxSerialize/Qt/QxSerialize_QPicture.cpp"
#include "./QxSerialize/Qt/QxSerialize_QPixmap.cpp"
#include "./QxSerialize/Qt/QxSerialize_QPoint.cpp"
#include "./QxSerialize/Qt/QxSerialize_QRect.cpp"
#include "./QxSerialize/Qt/QxSerialize_QRegExp.cpp"
#include "./QxSerialize/Qt/QxSerialize_QRegion.cpp"
#include "./QxSerialize/Qt/QxSerialize_QSize.cpp"
#include "./QxSerialize/Qt/QxSerialize_QString.cpp"
#include "./QxSerialize/Qt/QxSerialize_QStringList.cpp"
#include "./QxSerialize/Qt/QxSerialize_QTime.cpp"
#include "./QxSerialize/Qt/QxSerialize_QUrl.cpp"
#include "./QxSerialize/Qt/QxSerialize_QUuid.cpp"
#include "./QxSerialize/Qt/QxSerialize_QVariant.cpp"
#include "./QxSerialize/Qt/QxSerialize_QSqlError.cpp"

#include "./QxSerialize/QDataStream/QxSerializeQDataStream_primitive_type.cpp"
#include "./QxSerialize/QDataStream/QxSerializeQDataStream_QObject.cpp"
#include "./QxSerialize/QDataStream/QxSerializeQDataStream_QSqlError.cpp"
#include "./QxSerialize/QDataStream/QxSerializeQDataStream_std_string.cpp"
#include "./QxSerialize/QDataStream/QxSerializeQDataStream_qx_registered_class.cpp"

#include "./QxSerialize/QJson/QxSerializeQJson_qx_registered_class.cpp"
#include "./QxSerialize/QJson/QxSerializeQJson_IxService.cpp"
#include "./QxSerialize/QJson/QxSerializeQJson_IxSqlElement.cpp"
#include "./QxSerialize/QJson/QxSerializeQJson_QBrush.cpp"
#include "./QxSerialize/QJson/QxSerializeQJson_QColor.cpp"
#include "./QxSerialize/QJson/QxSerializeQJson_QFont.cpp"
#include "./QxSerialize/QJson/QxSerializeQJson_QImage.cpp"
#include "./QxSerialize/QJson/QxSerializeQJson_QMatrix.cpp"
#include "./QxSerialize/QJson/QxSerializeQJson_QObject.cpp"
#include "./QxSerialize/QJson/QxSerializeQJson_QPicture.cpp"
#include "./QxSerialize/QJson/QxSerializeQJson_QPixmap.cpp"
#include "./QxSerialize/QJson/QxSerializeQJson_QPoint.cpp"
#include "./QxSerialize/QJson/QxSerializeQJson_QRect.cpp"
#include "./QxSerialize/QJson/QxSerializeQJson_QRegExp.cpp"
#include "./QxSerialize/QJson/QxSerializeQJson_QRegion.cpp"
#include "./QxSerialize/QJson/QxSerializeQJson_QSize.cpp"
#include "./QxSerialize/QJson/QxSerializeQJson_QSqlError.cpp"
#include "./QxSerialize/QJson/QxSerializeQJson_QStringList.cpp"
#include "./QxSerialize/QJson/QxSerializeQJson_QxInvalidValue.cpp"
#include "./QxSerialize/QJson/QxSerializeQJson_QxInvalidValueX.cpp"
#include "./QxSerialize/QJson/QxSerializeQJson_QxSqlQuery.cpp"
#include "./QxSerialize/QJson/QxSerializeQJson_QxTransaction.cpp"

#include "./QxService/IxParameter.cpp"
#include "./QxService/IxService.cpp"
#include "./QxService/QxConnect.cpp"
#include "./QxService/QxServer.cpp"
#include "./QxService/QxThread.cpp"
#include "./QxService/QxThreadPool.cpp"
#include "./QxService/QxTools.cpp"
#include "./QxService/QxTransaction.cpp"

#include "./QxValidator/IxValidator.cpp"
#include "./QxValidator/IxValidatorX.cpp"
#include "./QxValidator/QxInvalidValue.cpp"
#include "./QxValidator/QxInvalidValueX.cpp"

#include "./QxModelView/IxModel.cpp"
#include "./QxModelView/QxNestedModel.cpp"

#include "./main.cpp"

#endif // _QX_UNITY_BUILD
