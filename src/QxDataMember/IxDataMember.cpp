/****************************************************************************
**
** https://www.qxorm.com/
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
#include <QxDao/IxSqlRelation.h>
#include <QxDao/IxDao_Helper.h>
#include <QxDao/IxSqlQueryBuilder.h>

#include <QxSerialize/QxSerialize.h>

#include <QxConvert/QxConvert_Impl.h>

#include <QxRegister/QxRegister.h>
#include <QxRegister/IxClass.h>

#include <QxValidator/IxValidatorX.h>

#include <QxMemLeak/mem_leak.h>

#define QX_CONSTRUCT_IX_DATA_MEMBER() \
m_iPrecision(6), m_iMinLength(-1), m_iMaxLength(-1), m_bRequired(false), \
m_bReadOnly(false), m_bAutoIncrement(false), m_bNotNull(false), \
m_bIsPrimaryKey(false), m_bAccessDataPointer(false), m_bIndex(false), \
m_bUnique(false), m_pName(NULL), m_pParent(NULL), m_pImpl(NULL)

namespace qx {

struct Q_DECL_HIDDEN IxDataMember::IxDataMemberImpl
{

   typedef QMap<int, QPair<IxSqlRelation *, int> > type_fk_part_of_pk;
   typedef std::unique_ptr<type_fk_part_of_pk> type_fk_part_of_pk_ptr;  //!< Type used by primary key to manage the case where a foreign key (relationship) is also a part of primary key (which can contain several columns)
   typedef QMap<int, QPair<IxDataMember *, int> > type_part_of_pk;
   typedef std::unique_ptr<type_part_of_pk> type_part_of_pk_ptr;        //!< Type used by relationship to manage the case where a foreign key (relationship) is also a part of primary key (which can contain several columns)

   QString     m_sKey;                 //!< Data key
   QString     m_sName;                //!< Data name <=> database record name (if empty => data key)
   QString     m_sNameParent;          //!< Data parent name <=> database table name
   QString     m_sDescription;         //!< Data description
   QString     m_sFormat;              //!< Data format ('%04d' for example)
   QString     m_sSqlType;             //!< Data sql type
   QString     m_sSqlAlias;            //!< Data sql alias
   long        m_lVersion;             //!< Data version creation
   bool        m_bSerialize;           //!< Data must be serialized
   bool        m_bDao;                 //!< Data is associated with a data source
   QVariant    m_vDefaultValue;        //!< Data default value under QVariant format
   QVariant    m_vMinValue;            //!< Data minimum value under QVariant format
   QVariant    m_vMaxValue;            //!< Data maximum value under QVariant format
   int         m_iPrecision;           //!< Data precision for numerics values (double, float, etc...)
   int         m_iMinLength;           //!< Data minimum length (-1 <=> no min length)
   int         m_iMaxLength;           //!< Data maximum length (-1 <=> no max length)
   bool        m_bRequired;            //!< Data is required or optional
   bool        m_bReadOnly;            //!< Data is read-only
   bool        m_bAutoIncrement;       //!< Data value is auto-generated (auto-increment)
   bool        m_bNotNull;             //!< Data can be null or not
   bool        m_bIsPrimaryKey;        //!< Data is a primary key
   bool        m_bAccessDataPointer;   //!< Can access to the data-member pointer
   bool        m_bIndex;               //!< Data is an index to optimize SQL queries
   bool        m_bUnique;              //!< Data is unique : 2 rows cannot have the same value for this column

   QByteArray m_byteName;              //!< Optimization to retrieve name under "const char *" format
   const char * m_pName;               //!< Optimization to retrieve name under "const char *" format
   QStringList m_lstNames;             //!< Particular case of "boost::tuple<>" data member (multi-column primary key, composite key)

   std::unique_ptr<IxSqlRelation> m_pSqlRelation;     //!< Sql relation to build/resolve sql query
   IxDataMemberX * m_pParent;                         //!< 'IxDataMemberX' parent
   IxDataMember * m_pImpl;                            //!< If not NULL then this data member is owned by a private implementation idiom instance

   type_fk_part_of_pk_ptr m_pListRelationPartOfPrimaryKey;     //!< Used by primary key to manage the case where a foreign key (relationship) is also a part of primary key (which can contain several columns)
   type_part_of_pk_ptr m_pListPartOfPrimaryKey;                //!< Used by relationship to manage the case where a foreign key (relationship) is also a part of primary key (which can contain several columns)

   IxDataMember::type_fct_sql_callback m_fctCustomGetSqlName;                       //!< Custom callback function called building SQL queries (GetSqlName method)
   IxDataMember::type_fct_sql_callback m_fctCustomGetSqlTablePointNameAsAlias;      //!< Custom callback function called building SQL queries (GetSqlTablePointNameAsAlias method)
   IxDataMember::type_fct_sql_callback m_fctCustomGetSqlNameEqualToPlaceHolder;     //!< Custom callback function called building SQL queries (GetSqlNameEqualToPlaceHolder method)
   IxDataMember::type_fct_sql_callback m_fctCustomGetSqlAliasEqualToPlaceHolder;    //!< Custom callback function called building SQL queries (GetSqlAliasEqualToPlaceHolder method)
   IxDataMember::type_fct_sql_callback m_fctCustomGetSqlAlias;                      //!< Custom callback function called building SQL queries (GetSqlAlias method)

   IxDataMemberImpl(const QString & sKey, long lVersion, bool bSerialize, bool bDao, IxDataMember * pImpl) : m_sKey(sKey), m_lVersion(lVersion), m_bSerialize(bSerialize), m_bDao(bDao), QX_CONSTRUCT_IX_DATA_MEMBER() { qAssert(! m_sKey.isEmpty()); m_pImpl = pImpl; updateNamePtr(); }
   ~IxDataMemberImpl() { ; }

   void updateNamePtr()
   {
      QString sNamePtr = (m_sName.isEmpty() ? m_sKey : m_sName);
      sNamePtr.replace("|", "-"); // valid xml tag
      m_byteName = sNamePtr.toLatin1();
      m_pName = m_byteName.constData();
      m_lstNames = (m_sName.isEmpty() ? m_sKey.split("|") : m_sName.split("|"));
   }

};

IxDataMember::IxDataMember(const QString & sKey, long lVersion, bool bSerialize, bool bDao, IxDataMember * pImpl) : qx::QxPropertyBag(), m_pImpl(new IxDataMemberImpl(sKey, lVersion, bSerialize, bDao, pImpl)) { ; }

IxDataMember::~IxDataMember() { ; }

#ifdef _QX_ENABLE_BOOST_SERIALIZATION
template<class Archive>
void IxDataMember::serialize(Archive & ar, const unsigned int version)
{
   Q_UNUSED(version);
   ar & boost::serialization::make_nvp("key", m_pImpl->m_sKey);
   ar & boost::serialization::make_nvp("name", m_pImpl->m_sName);
   ar & boost::serialization::make_nvp("nameParent", m_pImpl->m_sNameParent);
   ar & boost::serialization::make_nvp("desc", m_pImpl->m_sDescription);
   ar & boost::serialization::make_nvp("format", m_pImpl->m_sFormat);
   ar & boost::serialization::make_nvp("sqlType", m_pImpl->m_sSqlType);
   ar & boost::serialization::make_nvp("sqlAlias", m_pImpl->m_sSqlAlias);
   ar & boost::serialization::make_nvp("version", m_pImpl->m_lVersion);
   ar & boost::serialization::make_nvp("serialize", m_pImpl->m_bSerialize);
   ar & boost::serialization::make_nvp("dao", m_pImpl->m_bDao);
   ar & boost::serialization::make_nvp("defaultValue", m_pImpl->m_vDefaultValue);
   ar & boost::serialization::make_nvp("minValue", m_pImpl->m_vMinValue);
   ar & boost::serialization::make_nvp("maxValue", m_pImpl->m_vMaxValue);
   ar & boost::serialization::make_nvp("precision", m_pImpl->m_iPrecision);
   ar & boost::serialization::make_nvp("minLength", m_pImpl->m_iMinLength);
   ar & boost::serialization::make_nvp("maxLength", m_pImpl->m_iMaxLength);
   ar & boost::serialization::make_nvp("required", m_pImpl->m_bRequired);
   ar & boost::serialization::make_nvp("readOnly", m_pImpl->m_bReadOnly);
   ar & boost::serialization::make_nvp("autoIncrement", m_pImpl->m_bAutoIncrement);
   ar & boost::serialization::make_nvp("notNull", m_pImpl->m_bNotNull);
   ar & boost::serialization::make_nvp("isPrimaryKey", m_pImpl->m_bIsPrimaryKey);
   ar & boost::serialization::make_nvp("isIndex", m_pImpl->m_bIndex);
   ar & boost::serialization::make_nvp("isUnique", m_pImpl->m_bUnique);
}
#endif // _QX_ENABLE_BOOST_SERIALIZATION

QString IxDataMember::getKey() const { return m_pImpl->m_sKey; }

QString IxDataMember::getName() const { return (m_pImpl->m_sName.isEmpty() ? m_pImpl->m_sKey : m_pImpl->m_sName); }

int IxDataMember::getNameCount() const { return m_pImpl->m_lstNames.count(); }

QString IxDataMember::getNameParent() const { return m_pImpl->m_sNameParent; }

const char * IxDataMember::getNamePtr() const { return m_pImpl->m_pName; }

QString IxDataMember::getDescription() const { return m_pImpl->m_sDescription; }

QString IxDataMember::getFormat() const { return m_pImpl->m_sFormat; }

long IxDataMember::getVersion() const { return m_pImpl->m_lVersion; }

bool IxDataMember::getSerialize() const { return m_pImpl->m_bSerialize; }

bool IxDataMember::getDao() const { return m_pImpl->m_bDao; }

QVariant IxDataMember::getDefaultValue() const { return m_pImpl->m_vDefaultValue; }

QVariant IxDataMember::getMinValue() const { return m_pImpl->m_vMinValue; }

QVariant IxDataMember::getMaxValue() const { return m_pImpl->m_vMaxValue; }

int IxDataMember::getPrecision() const { return m_pImpl->m_iPrecision; }

int IxDataMember::getMinLength() const { return m_pImpl->m_iMinLength; }

int IxDataMember::getMaxLength() const { return m_pImpl->m_iMaxLength; }

bool IxDataMember::getRequired() const { return m_pImpl->m_bRequired; }

bool IxDataMember::getReadOnly() const { return m_pImpl->m_bReadOnly; }

bool IxDataMember::getAutoIncrement() const { return m_pImpl->m_bAutoIncrement; }

bool IxDataMember::getNotNull() const { return m_pImpl->m_bNotNull; }

bool IxDataMember::getIsPrimaryKey() const { return m_pImpl->m_bIsPrimaryKey; }

bool IxDataMember::getIsIndex() const { return m_pImpl->m_bIndex; }

bool IxDataMember::getIsUnique() const { return m_pImpl->m_bUnique; }

IxDataMemberX * IxDataMember::getParent() const { return m_pImpl->m_pParent; }

IxSqlRelation * IxDataMember::getSqlRelation() const { return m_pImpl->m_pSqlRelation.get(); }

bool IxDataMember::hasSqlRelation() const { return (m_pImpl->m_pSqlRelation.get() != NULL); }

bool IxDataMember::getAccessDataPointer() const { return m_pImpl->m_bAccessDataPointer; }

QString IxDataMember::getType() const { return ""; }

QString IxDataMember::getTypeParent() const { IxClass * pClass = (m_pImpl->m_pParent ? m_pImpl->m_pParent->getClass() : NULL); return (pClass ? pClass->getKey() : QString()); }

IxDataMember * IxDataMember::getPImpl() const { return m_pImpl->m_pImpl; }

void IxDataMember::setName(const QString & sName) { m_pImpl->m_sName = sName; m_pImpl->updateNamePtr(); }

void IxDataMember::setNameParent(const QString & sName) { m_pImpl->m_sNameParent = sName; }

void IxDataMember::setDescription(const QString & sDesc) { m_pImpl->m_sDescription = sDesc; }

void IxDataMember::setFormat(const QString & sFormat) { m_pImpl->m_sFormat = sFormat; }

void IxDataMember::setSqlType(const QString & sSqlType) { m_pImpl->m_sSqlType = sSqlType; }

void IxDataMember::setSqlAlias(const QString & sSqlAlias) { m_pImpl->m_sSqlAlias = sSqlAlias; }

void IxDataMember::setVersion(long lVersion) { m_pImpl->m_lVersion = lVersion; }

void IxDataMember::setSerialize(bool bSerialize) { m_pImpl->m_bSerialize = bSerialize; }

void IxDataMember::setDao(bool bDao) { m_pImpl->m_bDao = bDao; }

void IxDataMember::setDefaultValue(const QVariant & var) { m_pImpl->m_vDefaultValue = var; }

void IxDataMember::setPrecision(int iPrecision) { m_pImpl->m_iPrecision = iPrecision; }

void IxDataMember::setRequired(bool bRequired) { m_pImpl->m_bRequired = bRequired; }

void IxDataMember::setReadOnly(bool bReadOnly) { m_pImpl->m_bReadOnly = bReadOnly; }

void IxDataMember::setAutoIncrement(bool bAutoIncrement) { m_pImpl->m_bAutoIncrement = bAutoIncrement; }

void IxDataMember::setIsPrimaryKey(bool bIsPrimaryKey) { m_pImpl->m_bIsPrimaryKey = bIsPrimaryKey; }

void IxDataMember::setIsIndex(bool bIsIndex) { m_pImpl->m_bIndex = bIsIndex; }

void IxDataMember::setIsUnique(bool bIsUnique) { m_pImpl->m_bUnique = bIsUnique; }

void IxDataMember::setParent(IxDataMemberX * pParent) { m_pImpl->m_pParent = pParent; }

void IxDataMember::setSqlRelation(IxSqlRelation * pSqlRelation) { m_pImpl->m_pSqlRelation.reset(pSqlRelation); }

void IxDataMember::setAccessDataPointer(bool b) { m_pImpl->m_bAccessDataPointer = b; }

QVariant IxDataMember::toVariant(const void * pOwner, int iIndexName /* = -1 */, qx::cvt::context::ctx_type ctx /* = qx::cvt::context::e_no_context */) const { return this->toVariant(pOwner, m_pImpl->m_sFormat, iIndexName, ctx); }

qx_bool IxDataMember::fromVariant(void * pOwner, const QVariant & v, int iIndexName /* = -1 */, qx::cvt::context::ctx_type ctx /* = qx::cvt::context::e_no_context */) { return this->fromVariant(pOwner, v, m_pImpl->m_sFormat, iIndexName, ctx); }

#ifndef _QX_NO_JSON

QJsonValue IxDataMember::toJson(const void * pOwner) const { return this->toJson(pOwner, m_pImpl->m_sFormat); }

qx_bool IxDataMember::fromJson(void * pOwner, const QJsonValue & j) { return this->fromJson(pOwner, j, m_pImpl->m_sFormat); }

#endif // _QX_NO_JSON

void IxDataMember::setMinValue(long lMinValue, const QString & sMessage /* = QString() */)
{
   m_pImpl->m_vMinValue = (qlonglong)lMinValue;
   IxClass * pClass = (m_pImpl->m_pParent ? m_pImpl->m_pParent->getClass() : NULL); if (! pClass) { return; }
   IxValidatorX * pAllValidator = pClass->getAllValidator(); if (! pAllValidator) { return; }
   pAllValidator->add_MinValue(m_pImpl->m_sKey, lMinValue, sMessage);
}

void IxDataMember::setMinValue(double dMinValue, const QString & sMessage /* = QString() */)
{
   m_pImpl->m_vMinValue = dMinValue;
   IxClass * pClass = (m_pImpl->m_pParent ? m_pImpl->m_pParent->getClass() : NULL); if (! pClass) { return; }
   IxValidatorX * pAllValidator = pClass->getAllValidator(); if (! pAllValidator) { return; }
   pAllValidator->add_MinDecimal(m_pImpl->m_sKey, dMinValue, sMessage);
}

void IxDataMember::setMaxValue(long lMaxValue, const QString & sMessage /* = QString() */)
{
   m_pImpl->m_vMaxValue = (qlonglong)lMaxValue;
   IxClass * pClass = (m_pImpl->m_pParent ? m_pImpl->m_pParent->getClass() : NULL); if (! pClass) { return; }
   IxValidatorX * pAllValidator = pClass->getAllValidator(); if (! pAllValidator) { return; }
   pAllValidator->add_MaxValue(m_pImpl->m_sKey, lMaxValue, sMessage);
}

void IxDataMember::setMaxValue(double dMaxValue, const QString & sMessage /* = QString() */)
{
   m_pImpl->m_vMaxValue = dMaxValue;
   IxClass * pClass = (m_pImpl->m_pParent ? m_pImpl->m_pParent->getClass() : NULL); if (! pClass) { return; }
   IxValidatorX * pAllValidator = pClass->getAllValidator(); if (! pAllValidator) { return; }
   pAllValidator->add_MaxDecimal(m_pImpl->m_sKey, dMaxValue, sMessage);
}

void IxDataMember::setMinLength(int iMinLength, const QString & sMessage /* = QString() */)
{
   m_pImpl->m_iMinLength = iMinLength;
   IxClass * pClass = (m_pImpl->m_pParent ? m_pImpl->m_pParent->getClass() : NULL); if (! pClass) { return; }
   IxValidatorX * pAllValidator = pClass->getAllValidator(); if (! pAllValidator) { return; }
   pAllValidator->add_MinLength(m_pImpl->m_sKey, (long)m_pImpl->m_iMinLength, sMessage);
}

void IxDataMember::setMaxLength(int iMaxLength, const QString & sMessage /* = QString() */)
{
   m_pImpl->m_iMaxLength = iMaxLength;
   IxClass * pClass = (m_pImpl->m_pParent ? m_pImpl->m_pParent->getClass() : NULL); if (! pClass) { return; }
   IxValidatorX * pAllValidator = pClass->getAllValidator(); if (! pAllValidator) { return; }
   pAllValidator->add_MaxLength(m_pImpl->m_sKey, (long)m_pImpl->m_iMaxLength, sMessage);
}

void IxDataMember::setNotNull(bool bNotNull, const QString & sMessage /* = QString() */)
{
   m_pImpl->m_bNotNull = bNotNull;
   IxClass * pClass = (m_pImpl->m_pParent ? m_pImpl->m_pParent->getClass() : NULL); if (! pClass) { return; }
   IxValidatorX * pAllValidator = pClass->getAllValidator(); if (! pAllValidator) { return; }
   if (m_pImpl->m_bNotNull) { pAllValidator->add_NotNull(m_pImpl->m_sKey, sMessage); }
}

bool IxDataMember::isThereRelationPartOfPrimaryKey(int iIndexNamePK, IxSqlRelation * & pRelation, int & iIndexNameFK) const
{
   pRelation = NULL; iIndexNameFK = -1;
   if (! m_pImpl->m_pListRelationPartOfPrimaryKey) { return false; }
   if (! m_pImpl->m_pListRelationPartOfPrimaryKey->contains(iIndexNamePK)) { return false; }
   QPair<IxSqlRelation *, int> pair = m_pImpl->m_pListRelationPartOfPrimaryKey->value(iIndexNamePK);
   pRelation = pair.first; iIndexNameFK = pair.second;
   return true;
}

bool IxDataMember::isPartOfPrimaryKey(int iIndexNameFK, IxDataMember * & pPrimaryKey, int & iIndexNamePK) const
{
   pPrimaryKey = NULL; iIndexNamePK = -1;
   if (! m_pImpl->m_pListPartOfPrimaryKey) { return false; }
   if (! m_pImpl->m_pListPartOfPrimaryKey->contains(iIndexNameFK)) { return false; }
   QPair<IxDataMember *, int> pair = m_pImpl->m_pListPartOfPrimaryKey->value(iIndexNameFK);
   pPrimaryKey = pair.first; iIndexNamePK = pair.second;
   return true;
}

void IxDataMember::setRelationPartOfPrimaryKey(int iIndexNamePK, IxSqlRelation * pRelation, int iIndexNameFK)
{
   if (! m_pImpl->m_pListRelationPartOfPrimaryKey) { m_pImpl->m_pListRelationPartOfPrimaryKey.reset(new IxDataMemberImpl::type_fk_part_of_pk()); }
   if (m_pImpl->m_pListRelationPartOfPrimaryKey->contains(iIndexNamePK)) { return; }
   QPair<IxSqlRelation *, int> pair;
   pair.first = pRelation;
   pair.second = iIndexNameFK;
   m_pImpl->m_pListRelationPartOfPrimaryKey->insert(iIndexNamePK, pair);
}

void IxDataMember::setPartOfPrimaryKey(int iIndexNameFK, IxDataMember * pPrimaryKey, int iIndexNamePK)
{
   if (! m_pImpl->m_pListPartOfPrimaryKey) { m_pImpl->m_pListPartOfPrimaryKey.reset(new IxDataMemberImpl::type_part_of_pk()); }
   if (m_pImpl->m_pListPartOfPrimaryKey->contains(iIndexNameFK)) { return; }
   QPair<IxDataMember *, int> pair;
   pair.first = pPrimaryKey;
   pair.second = iIndexNamePK;
   m_pImpl->m_pListPartOfPrimaryKey->insert(iIndexNameFK, pair);
}

QString IxDataMember::getName(int iIndex, const QString & sOtherName /* = QString() */) const
{
   if (! sOtherName.isEmpty())
   {
      QStringList lstOtherNames = sOtherName.split("|");
      qAssert(m_pImpl->m_lstNames.count() == lstOtherNames.count());
      return (((iIndex >= 0) && (iIndex < lstOtherNames.count())) ? lstOtherNames.at(iIndex) : QString());
   }

   return (((iIndex >= 0) && (iIndex < m_pImpl->m_lstNames.count())) ? m_pImpl->m_lstNames.at(iIndex) : QString());
}

QString IxDataMember::getSqlAlias(const QString & sTable /* = QString() */, bool bClauseWhere /* = false */, int iIndexName /* = 0 */, qx::IxSqlQueryBuilder * pSqlQueryBuilder /* = NULL */) const
{
   QString sSqlAlias;
   QString sTableAlias = sTable;
   sTableAlias.replace(".", "_");

   do
   {
      // Standard SQL disallows references to column aliases in a WHERE clause
      // cf. <http://dev.mysql.com/doc/refman/5.0/en/problems-with-alias.html>
      if (bClauseWhere && ! sTableAlias.isEmpty()) { sSqlAlias = (getSqlTableName(sTableAlias) + "." + getSqlColumnName(getName(iIndexName))); break; }

      sSqlAlias = m_pImpl->m_sSqlAlias;
      if (! sSqlAlias.isEmpty()) { break; }
      if (! sTableAlias.isEmpty()) { sSqlAlias = (sTableAlias + "_" + getName(iIndexName) + "_0"); }
      else { sSqlAlias = (m_pImpl->m_sNameParent + "_" + getName(iIndexName) + "_0"); }

      // Special database keywords using '[', ']' or '"' characters
      sSqlAlias.replace("[", "");
      sSqlAlias.replace("]", "");
      sSqlAlias.replace("\"", "");
      sSqlAlias.replace(".", "_");
   }
   while (0);

   if (m_pImpl->m_fctCustomGetSqlAlias)
   {
      IxDataMemberSqlCallbackParams callbackParams(this, sSqlAlias);
      callbackParams.sTable = sTable;
      callbackParams.bClauseWhere = bClauseWhere;
      callbackParams.iIndexName = iIndexName;
      callbackParams.pDaoHelper = (pSqlQueryBuilder ? pSqlQueryBuilder->getDaoHelper() : NULL);
      callbackParams.pSqlQueryBuilder = pSqlQueryBuilder;
      m_pImpl->m_fctCustomGetSqlAlias(callbackParams);
   }

   return sSqlAlias;
}

QString IxDataMember::getSqlType(int iIndexName /* = -1 */) const
{
   if ((iIndexName == -1) || (getNameCount() <= 1)) { return m_pImpl->m_sSqlType; }
   QStringList lst = m_pImpl->m_sSqlType.split("|");
   return (((iIndexName >= 0) && (iIndexName < lst.count())) ? lst.at(iIndexName) : QString());
}

QString IxDataMember::getSqlTypeAndParams(int iIndexName /* = -1 */) const
{
   QString sResult = getSqlType(iIndexName);
   sResult += (m_pImpl->m_bNotNull ? " NOT NULL" : "");
   sResult += ((m_pImpl->m_bIsPrimaryKey && (getNameCount() <= 1)) ? " PRIMARY KEY" : "");

   if (m_pImpl->m_bAutoIncrement)
   {
      qx::dao::detail::IxSqlGenerator * pSqlGenerator = QxSqlDatabase::getSingleton()->getSqlGenerator();
      if (! pSqlGenerator) { qAssert(false); sResult += " AUTOINCREMENT"; }
      else { sResult += " " + pSqlGenerator->getAutoIncrement(); }
   }

   return sResult;
}

QString IxDataMember::getSqlPlaceHolder(const QString & sAppend /* = QString() */, int iIndexName /* = 0 */, const QString & sSep /* = QString(", ") */, const QString & sOtherName /* = QString() */, bool bCheckFKPartOfPK /* = false */) const
{
   QString sResult;
   int iIndexNameFK = 0;
   IxSqlRelation * pRelation = NULL;

   if (iIndexName == -1)
   {
      for (int i = 0; i < m_pImpl->m_lstNames.count(); i++)
      {
         if (bCheckFKPartOfPK && m_pImpl->m_bIsPrimaryKey && isThereRelationPartOfPrimaryKey(i, pRelation, iIndexNameFK)) { continue; }
         sResult += getSqlPlaceHolder(sAppend, i, sSep, sOtherName) + sSep;
      }

      if (! sResult.isEmpty())
      { sResult = sResult.left(sResult.count() - sSep.count()); } // Remove last separator
      return sResult;
   }

   // Special database keywords using '[', ']' or '"' characters
   if (bCheckFKPartOfPK && m_pImpl->m_bIsPrimaryKey && isThereRelationPartOfPrimaryKey(iIndexName, pRelation, iIndexNameFK)) { return ""; }
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

void IxDataMember::setSqlPlaceHolder(QSqlQuery & query, void * pOwner, const QString & sAppend /* = QString() */, const QString & sOtherName /* = QString() */, bool bCheckFKPartOfPK /* = false */, qx::QxCollection<QString, QVariantList> * pLstExecBatch /* = NULL */) const
{
   int iIndexNameFK = 0;
   IxSqlRelation * pRelation = NULL;
   bool bQuestionMark = (qx::QxSqlDatabase::getSingleton()->getSqlPlaceHolderStyle() == qx::QxSqlDatabase::ph_style_question_mark);

   for (int i = 0; i < m_pImpl->m_lstNames.count(); i++)
   {
      if (bCheckFKPartOfPK && m_pImpl->m_bIsPrimaryKey && isThereRelationPartOfPrimaryKey(i, pRelation, iIndexNameFK)) { continue; }
      QString key = (bQuestionMark ? QString() : getSqlPlaceHolder(sAppend, i, "", sOtherName));
      QVariant val = toVariant(pOwner, i, qx::cvt::context::e_database);
      if (pLstExecBatch)
      {
         if (bQuestionMark) { key = getName(i, sOtherName); }
         if (! pLstExecBatch->exist(key)) { QVariantList empty; pLstExecBatch->insert(key, empty); }
         QVariantList & values = const_cast<QVariantList &>(pLstExecBatch->getByKey(key));
         values.append(val);
      }
      else
      {
         if (bQuestionMark) { query.addBindValue(val); }
         else { query.bindValue(key, val); }
      }
   }
}

QString IxDataMember::getSqlAliasEqualToPlaceHolder(const QString & sTable /* = QString() */, bool bClauseWhere /* = false */, const QString & sAppend /* = QString() */, const QString & sSep /* = QString(" AND ") */, bool bCheckFKPartOfPK /* = false */, qx::IxSqlQueryBuilder * pSqlQueryBuilder /* = NULL */) const
{
   QString sResult;
   int iIndexNameFK = 0;
   IxSqlRelation * pRelation = NULL;

   for (int i = 0; i < m_pImpl->m_lstNames.count(); i++)
   {
      if (bCheckFKPartOfPK && m_pImpl->m_bIsPrimaryKey && isThereRelationPartOfPrimaryKey(i, pRelation, iIndexNameFK)) { continue; }
      sResult += getSqlAlias(sTable, bClauseWhere, i, pSqlQueryBuilder) + " = " + getSqlPlaceHolder(sAppend, i) + sSep;
   }

   if (! sResult.isEmpty())
   { sResult = sResult.left(sResult.count() - sSep.count()); } // Remove last separator

   if (m_pImpl->m_fctCustomGetSqlAliasEqualToPlaceHolder)
   {
      IxDataMemberSqlCallbackParams callbackParams(this, sResult);
      callbackParams.sTable = sTable;
      callbackParams.bClauseWhere = bClauseWhere;
      callbackParams.sAppend = sAppend;
      callbackParams.sSep = sSep;
      callbackParams.bCheckFKPartOfPK = bCheckFKPartOfPK;
      callbackParams.pDaoHelper = (pSqlQueryBuilder ? pSqlQueryBuilder->getDaoHelper() : NULL);
      callbackParams.pSqlQueryBuilder = pSqlQueryBuilder;
      m_pImpl->m_fctCustomGetSqlAliasEqualToPlaceHolder(callbackParams);
   }

   return sResult;
}

QString IxDataMember::getSqlNameEqualToPlaceHolder(const QString & sAppend /* = QString() */, const QString & sSep /* = QString(" AND ") */, bool bCheckFKPartOfPK /* = false */, qx::IxSqlQueryBuilder * pSqlQueryBuilder /* = NULL */) const
{
   QString sResult;
   int iIndexNameFK = 0;
   IxSqlRelation * pRelation = NULL;

   for (int i = 0; i < m_pImpl->m_lstNames.count(); i++)
   {
      if (bCheckFKPartOfPK && m_pImpl->m_bIsPrimaryKey && isThereRelationPartOfPrimaryKey(i, pRelation, iIndexNameFK)) { continue; }
      sResult += getSqlColumnName(getName(i)) + " = " + getSqlPlaceHolder(sAppend, i) + sSep;
   }

   if (! sResult.isEmpty())
   { sResult = sResult.left(sResult.count() - sSep.count()); } // Remove last separator

   if (m_pImpl->m_fctCustomGetSqlNameEqualToPlaceHolder)
   {
      IxDataMemberSqlCallbackParams callbackParams(this, sResult);
      callbackParams.sAppend = sAppend;
      callbackParams.sSep = sSep;
      callbackParams.bCheckFKPartOfPK = bCheckFKPartOfPK;
      callbackParams.pDaoHelper = (pSqlQueryBuilder ? pSqlQueryBuilder->getDaoHelper() : NULL);
      callbackParams.pSqlQueryBuilder = pSqlQueryBuilder;
      m_pImpl->m_fctCustomGetSqlNameEqualToPlaceHolder(callbackParams);
   }

   return sResult;
}

QString IxDataMember::getSqlTablePointNameAsAlias(const QString & sTable, const QString & sSep /* = QString(", ") */, const QString & sSuffixAlias /* = QString() */, bool bCheckFKPartOfPK /* = false */, const QString & sCustomAlias /* = QString() */, qx::IxSqlQueryBuilder * pSqlQueryBuilder /* = NULL */) const
{
   QString sResult;
   int iIndexNameFK = 0;
   IxSqlRelation * pRelation = NULL;
   QString sTableAlias = (sCustomAlias.isEmpty() ? sTable : sCustomAlias);
   sTableAlias.replace(".", "_");
   sTableAlias = getSqlTableName(sTableAlias);

   QString sTableAliasSep = " AS ";
   qx::dao::detail::IxSqlGenerator * pSqlGenerator = QxSqlDatabase::getSingleton()->getSqlGenerator();
   if (pSqlGenerator) { sTableAliasSep = pSqlGenerator->getTableAliasSep(); }

   for (int i = 0; i < m_pImpl->m_lstNames.count(); i++)
   {
      if (bCheckFKPartOfPK && m_pImpl->m_bIsPrimaryKey && isThereRelationPartOfPrimaryKey(i, pRelation, iIndexNameFK)) { continue; }
      // wrap alias with delimiters if needed
      sResult += sTableAlias + "." + getSqlColumnName(getName(i)) + sTableAliasSep + getSqlColumnNameAlias(getSqlAlias((sCustomAlias.isEmpty() ? sTable : sCustomAlias), false, i, pSqlQueryBuilder) + sSuffixAlias) + sSep;
   }

   if (! sResult.isEmpty())
   { sResult = sResult.left(sResult.count() - sSep.count()); } // Remove last separator

   if (m_pImpl->m_fctCustomGetSqlTablePointNameAsAlias)
   {
      IxDataMemberSqlCallbackParams callbackParams(this, sResult);
      callbackParams.sTable = sTable;
      callbackParams.sSep = sSep;
      callbackParams.sSuffixAlias = sSuffixAlias;
      callbackParams.bCheckFKPartOfPK = bCheckFKPartOfPK;
      callbackParams.sCustomAlias = sCustomAlias;
      callbackParams.pDaoHelper = (pSqlQueryBuilder ? pSqlQueryBuilder->getDaoHelper() : NULL);
      callbackParams.pSqlQueryBuilder = pSqlQueryBuilder;
      m_pImpl->m_fctCustomGetSqlTablePointNameAsAlias(callbackParams);
   }

   return sResult;
}

QString IxDataMember::getSqlName(const QString & sSep /* = QString(", ") */, const QString & sOtherName /* = QString() */, bool bCheckFKPartOfPK /* = false */, qx::IxSqlQueryBuilder * pSqlQueryBuilder /* = NULL */) const
{
   QString sResult;
   int iIndexNameFK = 0;
   IxSqlRelation * pRelation = NULL;

   for (int i = 0; i < m_pImpl->m_lstNames.count(); i++)
   {
      if (bCheckFKPartOfPK && m_pImpl->m_bIsPrimaryKey && isThereRelationPartOfPrimaryKey(i, pRelation, iIndexNameFK)) { continue; }
      sResult += getSqlColumnName(getName(i, sOtherName)) + sSep;
   }

   if (! sResult.isEmpty())
   { sResult = sResult.left(sResult.count() - sSep.count()); } // Remove last separator

   if (m_pImpl->m_fctCustomGetSqlName)
   {
      IxDataMemberSqlCallbackParams callbackParams(this, sResult);
      callbackParams.sSep = sSep;
      callbackParams.sOtherName = sOtherName;
      callbackParams.bCheckFKPartOfPK = bCheckFKPartOfPK;
      callbackParams.pDaoHelper = (pSqlQueryBuilder ? pSqlQueryBuilder->getDaoHelper() : NULL);
      callbackParams.pSqlQueryBuilder = pSqlQueryBuilder;
      m_pImpl->m_fctCustomGetSqlName(callbackParams);
   }

   return sResult;
}

QString IxDataMember::getSqlNameAndTypeAndParams(const QString & sSep /* = QString(", ") */, const QString & sOtherName /* = QString() */, bool bCheckFKPartOfPK /* = false */) const
{
   QString sResult;
   int iIndexNameFK = 0;
   IxSqlRelation * pRelation = NULL;

   for (int i = 0; i < m_pImpl->m_lstNames.count(); i++)
   {
      if (bCheckFKPartOfPK && m_pImpl->m_bIsPrimaryKey && isThereRelationPartOfPrimaryKey(i, pRelation, iIndexNameFK)) { continue; }
      sResult += getSqlColumnName(getName(i, sOtherName)) + " " + getSqlTypeAndParams(i) + sSep;
   }

   if (! sResult.isEmpty())
   { sResult = sResult.left(sResult.count() - sSep.count()); } // Remove last separator
   return sResult;
}

void IxDataMember::customGetSqlName(IxDataMember::type_fct_sql_callback fct) { m_pImpl->m_fctCustomGetSqlName = fct; }

void IxDataMember::customGetSqlTablePointNameAsAlias(IxDataMember::type_fct_sql_callback fct) { m_pImpl->m_fctCustomGetSqlTablePointNameAsAlias = fct; }

void IxDataMember::customGetSqlNameEqualToPlaceHolder(IxDataMember::type_fct_sql_callback fct) { m_pImpl->m_fctCustomGetSqlNameEqualToPlaceHolder = fct; }

void IxDataMember::customGetSqlAliasEqualToPlaceHolder(IxDataMember::type_fct_sql_callback fct) { m_pImpl->m_fctCustomGetSqlAliasEqualToPlaceHolder = fct; }

void IxDataMember::customGetSqlAlias(IxDataMember::type_fct_sql_callback fct) { m_pImpl->m_fctCustomGetSqlAlias = fct; }

QString IxDataMember::getSqlFromTable(const QString & sTable, const QString & sCustomAlias /* = QString() */)
{
   if (sCustomAlias.isEmpty() && ! sTable.contains(".")) { return getSqlTableName(sTable); }
   QString sTableAlias = (sCustomAlias.isEmpty() ? sTable : sCustomAlias);
   sTableAlias.replace(".", "_");

   QString sTableAliasSep = " AS ";
   qx::dao::detail::IxSqlGenerator * pSqlGenerator = QxSqlDatabase::getSingleton()->getSqlGenerator();
   if (pSqlGenerator) { sTableAliasSep = pSqlGenerator->getTableAliasSep(); }

   return (getSqlTableName(sTable) + sTableAliasSep + sTableAlias);
}

QString IxDataMember::getSqlTableName(const QString & sTable)
{
   QStringList lstDelimiter = QxSqlDatabase::getSingleton()->getSqlDelimiterForTableName();
   bool bAddSquareBracketsForTableName = QxSqlDatabase::getSingleton()->getAddSqlSquareBracketsForTableName();
   QString sStart = (bAddSquareBracketsForTableName ? QString("[") : QString());
   QString sEnd = (bAddSquareBracketsForTableName ? QString("]") : QString());
   if (lstDelimiter.count() > 0) { sStart = lstDelimiter.at(0); sEnd = lstDelimiter.at(0); }
   if (lstDelimiter.count() > 1) { sEnd = lstDelimiter.at(1); }
   if (sStart.isEmpty() || sEnd.isEmpty() || sTable.contains(sStart) || sTable.contains(sEnd)) { return sTable; }
   QString sResult = (sStart + sTable + sEnd); sResult.replace(".", (sEnd + "." + sStart));
   return sResult;
}

QString IxDataMember::getSqlColumnName(const QString & sColumn)
{
   QStringList lstDelimiter = QxSqlDatabase::getSingleton()->getSqlDelimiterForColumnName();
   bool bAddSquareBracketsForColumnName = QxSqlDatabase::getSingleton()->getAddSqlSquareBracketsForColumnName();
   QString sStart = (bAddSquareBracketsForColumnName ? QString("[") : QString());
   QString sEnd = (bAddSquareBracketsForColumnName ? QString("]") : QString());
   if (lstDelimiter.count() > 0) { sStart = lstDelimiter.at(0); sEnd = lstDelimiter.at(0); }
   if (lstDelimiter.count() > 1) { sEnd = lstDelimiter.at(1); }
   if (sStart.isEmpty() || sEnd.isEmpty() || sColumn.contains(sStart) || sColumn.contains(sEnd)) { return sColumn; }
   QString sResult = (sStart + sColumn + sEnd); sResult.replace(".", (sEnd + "." + sStart));
   return sResult;
}

QString IxDataMember::getSqlTableNameAlias(const QString & sTable)
{
   QStringList lstDelimiter = QxSqlDatabase::getSingleton()->getSqlDelimiterForTableNameAlias();
   QString sStart = QString();
   QString sEnd = QString();
   if (lstDelimiter.count() > 0) { sStart = lstDelimiter.at(0); sEnd = lstDelimiter.at(0); }
   if (lstDelimiter.count() > 1) { sEnd = lstDelimiter.at(1); }
   if (sStart.isEmpty() || sEnd.isEmpty() || sTable.contains(sStart) || sTable.contains(sEnd)) { return sTable; }
   QString sResult = (sStart + sTable + sEnd); sResult.replace(".", (sEnd + "." + sStart));
   return sResult;
}

QString IxDataMember::getSqlColumnNameAlias(const QString & sColumn)
{
   QStringList lstDelimiter = QxSqlDatabase::getSingleton()->getSqlDelimiterForColumnNameAlias();
   QString sStart = QString();
   QString sEnd = QString();
   if (lstDelimiter.count() > 0) { sStart = lstDelimiter.at(0); sEnd = lstDelimiter.at(0); }
   if (lstDelimiter.count() > 1) { sEnd = lstDelimiter.at(1); }
   if (sStart.isEmpty() || sEnd.isEmpty() || sColumn.contains(sStart) || sColumn.contains(sEnd)) { return sColumn; }
   QString sResult = (sStart + sColumn + sEnd); sResult.replace(".", (sEnd + "." + sStart));
   return sResult;
}

IxDataMemberSqlCallbackParams::IxDataMemberSqlCallbackParams(const IxDataMember * p, QString & sql) : pDataMember(p), sSQL(sql), bClauseWhere(false), bCheckFKPartOfPK(false), iIndexName(0), pDaoHelper(NULL), pSqlQueryBuilder(NULL) { qAssert(pDataMember); }

IxDataMemberSqlCallbackParams::~IxDataMemberSqlCallbackParams() { ; }

} // namespace qx

inline bool operator< (const qx::IxDataMember & i1, const qx::IxDataMember & i2) { return (i1.getKey() < i2.getKey()); }
inline bool operator> (const qx::IxDataMember & i1, const qx::IxDataMember & i2) { return (i1.getKey() > i2.getKey()); }
