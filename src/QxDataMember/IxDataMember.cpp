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

#include <QxPrecompiled.h>

#include <QxDataMember/IxDataMember.h>
#include <QxDataMember/IxDataMemberX.h>

#include <QxDao/QxSqlDatabase.h>

#include <QxSerialize/QxSerialize.h>

#include <QxCommon/QxStringCvt_Impl.h>

#include <QxRegister/QxRegister.h>
#include <QxRegister/IxClass.h>

#include <QxValidator/IxValidatorX.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

IxDataMember::~IxDataMember() { ; }

template<class Archive>
void IxDataMember::serialize(Archive & ar, const unsigned int version)
{
   Q_UNUSED(version);
   ar & boost::serialization::make_nvp("key", m_sKey);
   ar & boost::serialization::make_nvp("name", m_sName);
   ar & boost::serialization::make_nvp("nameParent", m_sNameParent);
   ar & boost::serialization::make_nvp("desc", m_sDescription);
   ar & boost::serialization::make_nvp("format", m_sFormat);
   ar & boost::serialization::make_nvp("sqlType", m_sSqlType);
   ar & boost::serialization::make_nvp("sqlAlias", m_sSqlAlias);
   ar & boost::serialization::make_nvp("version", m_lVersion);
   ar & boost::serialization::make_nvp("serialize", m_bSerialize);
   ar & boost::serialization::make_nvp("dao", m_bDao);
   ar & boost::serialization::make_nvp("defaultValue", m_vDefaultValue);
   ar & boost::serialization::make_nvp("minValue", m_vMinValue);
   ar & boost::serialization::make_nvp("maxValue", m_vMaxValue);
   ar & boost::serialization::make_nvp("precision", m_iPrecision);
   ar & boost::serialization::make_nvp("minLength", m_iMinLength);
   ar & boost::serialization::make_nvp("maxLength", m_iMaxLength);
   ar & boost::serialization::make_nvp("required", m_bRequired);
   ar & boost::serialization::make_nvp("readOnly", m_bReadOnly);
   ar & boost::serialization::make_nvp("autoIncrement", m_bAutoIncrement);
   ar & boost::serialization::make_nvp("notNull", m_bNotNull);
   ar & boost::serialization::make_nvp("isPrimaryKey", m_bIsPrimaryKey);
   ar & boost::serialization::make_nvp("isIndex", m_bIndex);
   ar & boost::serialization::make_nvp("isUnique", m_bUnique);
}

void IxDataMember::setMinValue(long lMinValue, const QString & sMessage /* = QString() */)
{
   m_vMinValue = (qlonglong)lMinValue;
   IxClass * pClass = (m_pParent ? m_pParent->getClass() : NULL); if (! pClass) { return; }
   IxValidatorX * pAllValidator = pClass->getAllValidator(); if (! pAllValidator) { return; }
   pAllValidator->add_MinValue(m_sKey, lMinValue, sMessage);
}

void IxDataMember::setMinValue(double dMinValue, const QString & sMessage /* = QString() */)
{
   m_vMinValue = dMinValue;
   IxClass * pClass = (m_pParent ? m_pParent->getClass() : NULL); if (! pClass) { return; }
   IxValidatorX * pAllValidator = pClass->getAllValidator(); if (! pAllValidator) { return; }
   pAllValidator->add_MinDecimal(m_sKey, dMinValue, sMessage);
}

void IxDataMember::setMaxValue(long lMaxValue, const QString & sMessage /* = QString() */)
{
   m_vMaxValue = (qlonglong)lMaxValue;
   IxClass * pClass = (m_pParent ? m_pParent->getClass() : NULL); if (! pClass) { return; }
   IxValidatorX * pAllValidator = pClass->getAllValidator(); if (! pAllValidator) { return; }
   pAllValidator->add_MaxValue(m_sKey, lMaxValue, sMessage);
}

void IxDataMember::setMaxValue(double dMaxValue, const QString & sMessage /* = QString() */)
{
   m_vMaxValue = dMaxValue;
   IxClass * pClass = (m_pParent ? m_pParent->getClass() : NULL); if (! pClass) { return; }
   IxValidatorX * pAllValidator = pClass->getAllValidator(); if (! pAllValidator) { return; }
   pAllValidator->add_MaxDecimal(m_sKey, dMaxValue, sMessage);
}

void IxDataMember::setMinLength(int iMinLength, const QString & sMessage /* = QString() */)
{
   m_iMinLength = iMinLength;
   IxClass * pClass = (m_pParent ? m_pParent->getClass() : NULL); if (! pClass) { return; }
   IxValidatorX * pAllValidator = pClass->getAllValidator(); if (! pAllValidator) { return; }
   pAllValidator->add_MinLength(m_sKey, (long)m_iMinLength, sMessage);
}

void IxDataMember::setMaxLength(int iMaxLength, const QString & sMessage /* = QString() */)
{
   m_iMaxLength = iMaxLength;
   IxClass * pClass = (m_pParent ? m_pParent->getClass() : NULL); if (! pClass) { return; }
   IxValidatorX * pAllValidator = pClass->getAllValidator(); if (! pAllValidator) { return; }
   pAllValidator->add_MaxLength(m_sKey, (long)m_iMaxLength, sMessage);
}

void IxDataMember::setNotNull(bool bNotNull, const QString & sMessage /* = QString() */)
{
   m_bNotNull = bNotNull;
   IxClass * pClass = (m_pParent ? m_pParent->getClass() : NULL); if (! pClass) { return; }
   IxValidatorX * pAllValidator = pClass->getAllValidator(); if (! pAllValidator) { return; }
   if (m_bNotNull) { pAllValidator->add_NotNull(m_sKey, sMessage); }
}

QString IxDataMember::getName(int iIndex, const QString & sOtherName /* = QString() */) const
{
   if (! sOtherName.isEmpty())
   {
      QStringList lstOtherNames = sOtherName.split("|");
      qAssert(m_lstNames.count() == lstOtherNames.count());
      return (((iIndex >= 0) && (iIndex < lstOtherNames.count())) ? lstOtherNames.at(iIndex) : QString());
   }

   return (((iIndex >= 0) && (iIndex < m_lstNames.count())) ? m_lstNames.at(iIndex) : QString());
}

QString IxDataMember::getSqlAlias(const QString & sTable /* = QString() */, bool bClauseWhere /* = false */, int iIndexName /* = 0 */) const
{
   QString sTableAlias = sTable;
   sTableAlias.replace(".", "_");

   // Standard SQL disallows references to column aliases in a WHERE clause
   // cf. <http://dev.mysql.com/doc/refman/5.0/en/problems-with-alias.html>
   if (bClauseWhere && ! sTableAlias.isEmpty()) { return (sTableAlias + "." + getName(iIndexName)); }

   QString sSqlAlias = m_sSqlAlias;
   if (! sSqlAlias.isEmpty()) { return sSqlAlias; }
   if (! sTableAlias.isEmpty()) { sSqlAlias = (sTableAlias + "_" + getName(iIndexName) + "_0"); }
   else { sSqlAlias = (m_sNameParent + "_" + getName(iIndexName) + "_0"); }

   // Special database keywords using '[', ']' or '"' characters
   sSqlAlias.replace("[", "");
   sSqlAlias.replace("]", "");
   sSqlAlias.replace("\"", "");
   sSqlAlias.replace(".", "_");

   return sSqlAlias;
}

QString IxDataMember::getSqlType(int iIndexName /* = -1 */) const
{
   if ((iIndexName == -1) || (getNameCount() <= 1)) { return m_sSqlType; }
   QStringList lst = m_sSqlType.split("|");
   return (((iIndexName >= 0) && (iIndexName < lst.count())) ? lst.at(iIndexName) : QString());
}

QString IxDataMember::getSqlTypeAndParams(int iIndexName /* = -1 */) const
{
   QString sResult = getSqlType(iIndexName);
   sResult += (m_bNotNull ? " NOT NULL" : "");
   sResult += ((m_bIsPrimaryKey && (getNameCount() <= 1)) ? " PRIMARY KEY" : "");

   if (m_bAutoIncrement)
   {
      qx::dao::detail::IxSqlGenerator * pSqlGenerator = QxSqlDatabase::getSingleton()->getSqlGenerator();
      if (! pSqlGenerator) { qAssert(false); sResult += " AUTOINCREMENT"; }
      else { sResult += " " + pSqlGenerator->getAutoIncrement(); }
   }

   return sResult;
}

QString IxDataMember::getSqlPlaceHolder(const QString & sAppend /* = QString() */, int iIndexName /* = 0 */, const QString & sSep /* = QString(", ") */, const QString & sOtherName /* = QString() */) const
{
   QString sResult;
   if (iIndexName == -1)
   {
      for (int i = 0; i < m_lstNames.count(); i++)
      { sResult += getSqlPlaceHolder(sAppend, i, sSep, sOtherName); sResult += sSep; }
      sResult = sResult.left(sResult.count() - sSep.count()); // Remove last separator
      return sResult;
   }

   // Special database keywords using '[', ']' or '"' characters
   QString sSqlPlaceHolder = getName(iIndexName, sOtherName) + sAppend;
   sSqlPlaceHolder.replace("[", "");
   sSqlPlaceHolder.replace("]", "");
   sSqlPlaceHolder.replace("\"", "");

   switch (QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle())
   {
      case QxSqlDatabase::ph_style_question_mark:  sResult = "?";                      break;
      case QxSqlDatabase::ph_style_2_point_name:   sResult = ":" + sSqlPlaceHolder;    break;
      case QxSqlDatabase::ph_style_at_name:        sResult = "@" + sSqlPlaceHolder;    break;
      default:                                     sResult = ":" + sSqlPlaceHolder;    break;
   }

   return sResult;
}

void IxDataMember::setSqlPlaceHolder(QSqlQuery & query, void * pOwner, const QString & sAppend /* = QString() */, const QString & sOtherName /* = QString() */) const
{
   for (int i = 0; i < m_lstNames.count(); i++)
   {
      switch (QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle())
      {
         case QxSqlDatabase::ph_style_question_mark:  query.addBindValue(toVariant(pOwner, i));                                                 break;
         case QxSqlDatabase::ph_style_2_point_name:   query.bindValue(getSqlPlaceHolder(sAppend, i, "", sOtherName), toVariant(pOwner, i));     break;
         case QxSqlDatabase::ph_style_at_name:        query.bindValue(getSqlPlaceHolder(sAppend, i, "", sOtherName), toVariant(pOwner, i));     break;
         default:                                     query.bindValue(getSqlPlaceHolder(sAppend, i, "", sOtherName), toVariant(pOwner, i));     break;
      }
   }
}

QString IxDataMember::getSqlAliasEqualToPlaceHolder(const QString & sTable /* = QString() */, bool bClauseWhere /* = false */, const QString & sAppend /* = QString() */, const QString & sSep /* = QString(" AND ") */) const
{
   QString sResult;
   for (int i = 0; i < m_lstNames.count(); i++)
   { sResult += getSqlAlias(sTable, bClauseWhere, i) + " = " + getSqlPlaceHolder(sAppend, i); sResult += sSep; }
   sResult = sResult.left(sResult.count() - sSep.count()); // Remove last separator
   return sResult;
}

QString IxDataMember::getSqlNameEqualToPlaceHolder(const QString & sAppend /* = QString() */, const QString & sSep /* = QString(" AND ") */) const
{
   QString sResult;
   for (int i = 0; i < m_lstNames.count(); i++)
   { sResult += getName(i) + " = " + getSqlPlaceHolder(sAppend, i); sResult += sSep; }
   sResult = sResult.left(sResult.count() - sSep.count()); // Remove last separator
   return sResult;
}

QString IxDataMember::getSqlTablePointNameAsAlias(const QString & sTable, const QString & sSep /* = QString(", ") */, const QString & sSuffixAlias /* = QString() */) const
{
   QString sResult;
   QString sTableAlias = sTable;
   sTableAlias.replace(".", "_");
   for (int i = 0; i < m_lstNames.count(); i++)
   { sResult += sTableAlias + "." + getName(i) + " AS " + getSqlAlias(sTable, false, i) + sSuffixAlias; sResult += sSep; }
   sResult = sResult.left(sResult.count() - sSep.count()); // Remove last separator
   return sResult;
}

QString IxDataMember::getSqlName(const QString & sSep /* = QString(", ") */, const QString & sOtherName /* = QString() */) const
{
   QString sResult;
   for (int i = 0; i < m_lstNames.count(); i++)
   { sResult += getName(i, sOtherName); sResult += sSep; }
   sResult = sResult.left(sResult.count() - sSep.count()); // Remove last separator
   return sResult;
}

QString IxDataMember::getSqlNameAndTypeAndParams(const QString & sSep /* = QString(", ") */, const QString & sOtherName /* = QString() */) const
{
   QString sResult;
   for (int i = 0; i < m_lstNames.count(); i++)
   { sResult += getName(i, sOtherName) + " " + getSqlTypeAndParams(i); sResult += sSep; }
   sResult = sResult.left(sResult.count() - sSep.count()); // Remove last separator
   return sResult;
}

QString IxDataMember::getSqlFromTable(const QString & sTable)
{
   if (! sTable.contains(".")) { return sTable; }
   QString sTableAlias = sTable;
   sTableAlias.replace(".", "_");
   return (sTable + " AS " + sTableAlias);
}

} // namespace qx

inline bool operator< (const qx::IxDataMember & i1, const qx::IxDataMember & i2) { return (i1.getKey() < i2.getKey()); }
inline bool operator> (const qx::IxDataMember & i1, const qx::IxDataMember & i2) { return (i1.getKey() > i2.getKey()); }
