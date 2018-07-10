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

#ifndef _IX_DATA_MEMBER_H_
#define _IX_DATA_MEMBER_H_

#ifdef _MSC_VER
#pragma once
#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4996)
#endif // _MSC_VER

#include <boost/any.hpp>

#include "../../include/QxCommon/QxBool.h"

#include "../../include/QxSerialize/boost/QxSerializeInclude.h"

#include "../../include/QxDao/IxSqlRelation.h"

#ifdef _MSC_VER
#pragma warning(pop)
#endif // _MSC_VER

#define QX_CONSTRUCT_IX_DATA_MEMBER() \
m_iPrecision(6), m_iMinLength(-1), m_iMaxLength(-1), m_bRequired(false), \
m_bReadOnly(false), m_bAutoIncrement(false), m_bNotNull(false), \
m_bIsPrimaryKey(false), m_pName(NULL), m_pParent(NULL)

#define QX_IX_DATA_MEMBER_PURE_VIRTUAL_ARCHIVE(ArchiveInput, ArchiveOutput) \
virtual void toArchive(const void * pOwner, ArchiveOutput & ar) const = 0; \
virtual void fromArchive(void * pOwner, ArchiveInput & ar) = 0;

namespace qx {

class IxDataMemberX;

class QX_DLL_EXPORT IxDataMember
{

protected:

   QString     m_sKey;              // Data key
   QString     m_sName;             // Data name <=> database record name (if empty => data key)
   QString     m_sNameParent;       // Data parent name <=> database table name
   QString     m_sDescription;      // Data description
   QString     m_sFormat;           // Data format ('%04d' for example)
   QString     m_sSqlType;          // Data sql type
   QString     m_sSqlAlias;         // Data sql alias
   long        m_lVersion;          // Data version creation
   bool        m_bSerialize;        // Data must be serialized
   bool        m_bDao;              // Data is associated with a data source
   QVariant    m_vDefaultValue;     // Data default value under QVariant format
   QVariant    m_vMinValue;         // Data minimum value under QVariant format
   QVariant    m_vMaxValue;         // Data maximum value under QVariant format
   int         m_iPrecision;        // Data precision for numerics values (double, float, etc...)
   int         m_iMinLength;        // Data minimum length (-1 <=> no min length)
   int         m_iMaxLength;        // Data maximum length (-1 <=> no max length)
   bool        m_bRequired;         // Data is required or optional
   bool        m_bReadOnly;         // Data is read-only
   bool        m_bAutoIncrement;    // Data value is auto-generated (auto-increment)
   bool        m_bNotNull;          // Data can be null or not
   bool        m_bIsPrimaryKey;     // Data is a primary key

   QByteArray m_byteName;           // Optimization to retrieve name under "const char *" format
   const char * m_pName;            // Optimization to retrieve name under "const char *" format

   boost::scoped_ptr<IxSqlRelation> m_pSqlRelation;   // Sql relation to build/resolve sql query
   IxDataMemberX * m_pParent;                         // 'IxDataMemberX' parent

public:

   IxDataMember(const QString & sKey) : m_sKey(sKey), m_lVersion(-1), m_bSerialize(true), m_bDao(true), QX_CONSTRUCT_IX_DATA_MEMBER() { qAssert(! m_sKey.isEmpty()); updateNamePtr(); }
   IxDataMember(const QString & sKey, long lVersion, bool bSerialize, bool bDao) : m_sKey(sKey), m_lVersion(lVersion), m_bSerialize(bSerialize), m_bDao(bDao), QX_CONSTRUCT_IX_DATA_MEMBER() { qAssert(! m_sKey.isEmpty()); updateNamePtr(); }
   virtual ~IxDataMember() = 0;

   inline QString getKey() const                   { return m_sKey; }
   inline QString getName() const                  { return (m_sName.isEmpty() ? m_sKey : m_sName); }
   inline QString getNameParent() const            { return m_sNameParent; }
   inline QString getSqlType() const               { return m_sSqlType; }
   inline const char * getNamePtr() const          { return m_pName; }
   inline QString getDescription() const           { return m_sDescription; }
   inline QString getFormat() const                { return m_sFormat; }
   inline long getVersion() const                  { return m_lVersion; }
   inline bool getSerialize() const                { return m_bSerialize; }
   inline bool getDao() const                      { return m_bDao; }
   inline QVariant getDefaultValue() const         { return m_vDefaultValue; }
   inline QVariant getMinValue() const             { return m_vMinValue; }
   inline QVariant getMaxValue() const             { return m_vMaxValue; }
   inline int getPrecision() const                 { return m_iPrecision; }
   inline int getMinLength() const                 { return m_iMinLength; }
   inline int getMaxLength() const                 { return m_iMaxLength; }
   inline bool getRequired() const                 { return m_bRequired; }
   inline bool getReadOnly() const                 { return m_bReadOnly; }
   inline bool getAutoIncrement() const            { return m_bAutoIncrement; }
   inline bool getNotNull() const                  { return m_bNotNull; }
   inline bool getIsPrimaryKey() const             { return m_bIsPrimaryKey; }
   inline IxDataMemberX * getParent() const        { return m_pParent; }
   inline IxSqlRelation * getSqlRelation() const   { return m_pSqlRelation.get(); }
   inline bool hasSqlRelation() const              { return (m_pSqlRelation.get() != NULL); }

   inline void setName(const QString & sName)                  { m_sName = sName; updateNamePtr(); }
   inline void setNameParent(const QString & sName)            { m_sNameParent = sName; }
   inline void setDescription(const QString & sDesc)           { m_sDescription = sDesc; }
   inline void setFormat(const QString & sFormat)              { m_sFormat = sFormat; }
   inline void setSqlType(const QString & sSqlType)            { m_sSqlType = sSqlType; }
   inline void setSqlAlias(const QString & sSqlAlias)          { m_sSqlAlias = sSqlAlias; }
   inline void setVersion(long lVersion)                       { m_lVersion = lVersion; }
   inline void setSerialize(bool bSerialize)                   { m_bSerialize = bSerialize; }
   inline void setDao(bool bDao)                               { m_bDao = bDao; }
   inline void setDefaultValue(const QVariant & var)           { m_vDefaultValue = var; }
   inline void setMinValue(const QVariant & var)               { m_vMinValue = var; }
   inline void setMaxValue(const QVariant & var)               { m_vMaxValue = var; }
   inline void setPrecision(int iPrecision)                    { m_iPrecision = iPrecision; }
   inline void setMinLength(int iMinLength)                    { m_iMinLength = iMinLength; }
   inline void setMaxLength(int iMaxLength)                    { m_iMaxLength = iMaxLength; }
   inline void setRequired(bool bRequired)                     { m_bRequired = bRequired; }
   inline void setReadOnly(bool bReadOnly)                     { m_bReadOnly = bReadOnly; }
   inline void setAutoIncrement(bool bAutoIncrement)           { m_bAutoIncrement = bAutoIncrement; }
   inline void setNotNull(bool bNotNull)                       { m_bNotNull = bNotNull; }
   inline void setIsPrimaryKey(bool bIsPrimaryKey)             { m_bIsPrimaryKey = bIsPrimaryKey; }
   inline void setParent(IxDataMemberX * pParent)              { m_pParent = pParent; }
   inline void setSqlRelation(IxSqlRelation * pSqlRelation)    { m_pSqlRelation.reset(pSqlRelation); }

   QString getSqlAlias(QString * pTable = NULL, bool bClauseWhere = false) const;
   QString getSqlTypeAndParams() const;
   QString getSqlPlaceHolder(const QString & sAppend = QString()) const;
   void setSqlPlaceHolder(QSqlQuery & query, void * pOwner, const QString & sAppend = QString()) const;

   virtual boost::any getDataPtr(const void * pOwner) const = 0;
   virtual boost::any getDataPtr(void * pOwner) = 0;
   virtual void * getDataVoidPtr(const void * pOwner) const = 0;
   virtual void * getDataVoidPtr(void * pOwner) = 0;
   virtual qx_bool isValid(const void * pOwner) const = 0;
   virtual qx_bool isValid(void * pOwner) = 0;
   virtual QString toString(const void * pOwner, const QString & sFormat) const = 0;
   virtual qx_bool fromString(void * pOwner, const QString & s, const QString & sFormat) = 0;
   virtual QVariant toVariant(const void * pOwner, const QString & sFormat) const = 0;
   virtual qx_bool fromVariant(void * pOwner, const QVariant & v, const QString & sFormat) = 0;

   inline QString toString(const void * pOwner) const             { return this->toString(pOwner, m_sFormat); }
   inline qx_bool fromString(void * pOwner, const QString & s)    { return this->fromString(pOwner, s, m_sFormat); }
   inline QVariant toVariant(const void * pOwner) const           { return this->toVariant(pOwner, m_sFormat); }
   inline qx_bool fromVariant(void * pOwner, const QVariant & v)  { return this->fromVariant(pOwner, v, m_sFormat); }

#if _QX_SERIALIZE_POLYMORPHIC
   QX_IX_DATA_MEMBER_PURE_VIRTUAL_ARCHIVE(boost::archive::polymorphic_iarchive, boost::archive::polymorphic_oarchive)
#endif // _QX_SERIALIZE_POLYMORPHIC

#if _QX_SERIALIZE_BINARY
   QX_IX_DATA_MEMBER_PURE_VIRTUAL_ARCHIVE(boost::archive::binary_iarchive, boost::archive::binary_oarchive)
#endif // _QX_SERIALIZE_BINARY

#if _QX_SERIALIZE_TEXT
   QX_IX_DATA_MEMBER_PURE_VIRTUAL_ARCHIVE(boost::archive::text_iarchive, boost::archive::text_oarchive)
#endif // _QX_SERIALIZE_TEXT

#if _QX_SERIALIZE_XML
   QX_IX_DATA_MEMBER_PURE_VIRTUAL_ARCHIVE(boost::archive::xml_iarchive, boost::archive::xml_oarchive)
#endif // _QX_SERIALIZE_XML

#if _QX_SERIALIZE_PORTABLE_BINARY
   QX_IX_DATA_MEMBER_PURE_VIRTUAL_ARCHIVE(eos::portable_iarchive, eos::portable_oarchive)
#endif // _QX_SERIALIZE_PORTABLE_BINARY

#if _QX_SERIALIZE_WIDE_BINARY
   QX_IX_DATA_MEMBER_PURE_VIRTUAL_ARCHIVE(boost::archive::binary_wiarchive, boost::archive::binary_woarchive)
#endif // _QX_SERIALIZE_WIDE_BINARY

#if _QX_SERIALIZE_WIDE_TEXT
   QX_IX_DATA_MEMBER_PURE_VIRTUAL_ARCHIVE(boost::archive::text_wiarchive, boost::archive::text_woarchive)
#endif // _QX_SERIALIZE_WIDE_TEXT

#if _QX_SERIALIZE_WIDE_XML
   QX_IX_DATA_MEMBER_PURE_VIRTUAL_ARCHIVE(boost::archive::xml_wiarchive, boost::archive::xml_woarchive)
#endif // _QX_SERIALIZE_WIDE_XML

private:

   inline void updateNamePtr() { m_byteName = (m_sName.isEmpty() ? m_sKey.toAscii() : m_sName.toAscii()); m_pName = m_byteName.constData(); }

   template<class Archive>
   void serialize(Archive & ar, const unsigned int version);

};

typedef boost::shared_ptr<IxDataMember> IxDataMember_ptr;

} // namespace qx

QX_DLL_EXPORT inline bool operator< (const qx::IxDataMember & i1, const qx::IxDataMember & i2);
QX_DLL_EXPORT inline bool operator> (const qx::IxDataMember & i1, const qx::IxDataMember & i2);

#endif // _IX_DATA_MEMBER_H_
