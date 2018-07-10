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

#ifndef _IX_DATA_MEMBER_H_
#define _IX_DATA_MEMBER_H_

#ifdef _MSC_VER
#pragma once
#endif

/*!
 * \file IxDataMember.h
 * \author Lionel Marty
 * \ingroup QxDataMember
 * \brief Common interface for all class properties registered into QxOrm context
 */

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4996)
#endif // _MSC_VER

#include <boost/any.hpp>

#include <QxCommon/QxBool.h>
#include <QxCommon/QxPropertyBag.h>

#include <QxSerialize/boost/QxSerializeInclude.h>

#include <QxDao/IxSqlRelation.h>

#ifdef _MSC_VER
#pragma warning(pop)
#endif // _MSC_VER

#define QX_CONSTRUCT_IX_DATA_MEMBER() \
m_iPrecision(6), m_iMinLength(-1), m_iMaxLength(-1), m_bRequired(false), \
m_bReadOnly(false), m_bAutoIncrement(false), m_bNotNull(false), \
m_bIsPrimaryKey(false), m_bAccessDataPointer(false), m_bIndex(false), \
m_bUnique(false), m_pName(NULL), m_pParent(NULL)

#define QX_IX_DATA_MEMBER_PURE_VIRTUAL_ARCHIVE(ArchiveInput, ArchiveOutput) \
virtual void toArchive(const void * pOwner, ArchiveOutput & ar) const = 0; \
virtual void fromArchive(void * pOwner, ArchiveInput & ar) = 0;

namespace qx {

class IxDataMemberX;

/*!
 * \ingroup QxDataMember
 * \brief qx::IxDataMember : common interface for all class properties registered into QxOrm context
 */
class QX_DLL_EXPORT IxDataMember : public qx::QxPropertyBag
{

protected:

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

   boost::scoped_ptr<IxSqlRelation> m_pSqlRelation;   //!< Sql relation to build/resolve sql query
   IxDataMemberX * m_pParent;                         //!< 'IxDataMemberX' parent

public:

   IxDataMember(const QString & sKey) : qx::QxPropertyBag(), m_sKey(sKey), m_lVersion(-1), m_bSerialize(true), m_bDao(true), QX_CONSTRUCT_IX_DATA_MEMBER() { qAssert(! m_sKey.isEmpty()); updateNamePtr(); }
   IxDataMember(const QString & sKey, long lVersion, bool bSerialize, bool bDao) : qx::QxPropertyBag(), m_sKey(sKey), m_lVersion(lVersion), m_bSerialize(bSerialize), m_bDao(bDao), QX_CONSTRUCT_IX_DATA_MEMBER() { qAssert(! m_sKey.isEmpty()); updateNamePtr(); }
   virtual ~IxDataMember() = 0;

   inline QString getKey() const                   { return m_sKey; }
   inline QString getName() const                  { return (m_sName.isEmpty() ? m_sKey : m_sName); }
   inline int getNameCount() const                 { return m_lstNames.count(); }
   inline QString getNameParent() const            { return m_sNameParent; }
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
   inline bool getIsIndex() const                  { return m_bIndex; }
   inline bool getIsUnique() const                 { return m_bUnique; }
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
   inline void setPrecision(int iPrecision)                    { m_iPrecision = iPrecision; }
   inline void setRequired(bool bRequired)                     { m_bRequired = bRequired; }
   inline void setReadOnly(bool bReadOnly)                     { m_bReadOnly = bReadOnly; }
   inline void setAutoIncrement(bool bAutoIncrement)           { m_bAutoIncrement = bAutoIncrement; }
   inline void setIsPrimaryKey(bool bIsPrimaryKey)             { m_bIsPrimaryKey = bIsPrimaryKey; }
   inline void setIsIndex(bool bIsIndex)                       { m_bIndex = bIsIndex; }
   inline void setIsUnique(bool bIsUnique)                     { m_bUnique = bIsUnique; }
   inline void setParent(IxDataMemberX * pParent)              { m_pParent = pParent; }
   inline void setSqlRelation(IxSqlRelation * pSqlRelation)    { m_pSqlRelation.reset(pSqlRelation); }

   void setMinValue(long lMinValue, const QString & sMessage = QString());
   void setMinValue(double dMinValue, const QString & sMessage = QString());
   void setMaxValue(long lMaxValue, const QString & sMessage = QString());
   void setMaxValue(double dMaxValue, const QString & sMessage = QString());
   void setMinLength(int iMinLength, const QString & sMessage = QString());
   void setMaxLength(int iMaxLength, const QString & sMessage = QString());
   void setNotNull(bool bNotNull, const QString & sMessage = QString());

   QString getName(int iIndex, const QString & sOtherName = QString()) const;
   QString getSqlAlias(const QString & sTable = QString(), bool bClauseWhere = false, int iIndexName = 0) const;
   QString getSqlType(int iIndexName = -1) const;
   QString getSqlTypeAndParams(int iIndexName = -1) const;
   QString getSqlPlaceHolder(const QString & sAppend = QString(), int iIndexName = 0, const QString & sSep = QString(", "), const QString & sOtherName = QString()) const;
   void setSqlPlaceHolder(QSqlQuery & query, void * pOwner, const QString & sAppend = QString(), const QString & sOtherName = QString()) const;
   QString getSqlAliasEqualToPlaceHolder(const QString & sTable = QString(), bool bClauseWhere = false, const QString & sAppend = QString(), const QString & sSep = QString(" AND ")) const;
   QString getSqlNameEqualToPlaceHolder(const QString & sAppend = QString(), const QString & sSep = QString(" AND ")) const;
   QString getSqlTablePointNameAsAlias(const QString & sTable, const QString & sSep = QString(", "), const QString & sSuffixAlias = QString()) const;
   QString getSqlName(const QString & sSep = QString(", "), const QString & sOtherName = QString()) const;
   QString getSqlNameAndTypeAndParams(const QString & sSep = QString(", "), const QString & sOtherName = QString()) const;

   static QString getSqlFromTable(const QString & sTable);

   virtual bool isEqual(const void * pOwner1, const void * pOwner2) const = 0;
   virtual QString toString(const void * pOwner, const QString & sFormat, int iIndexName = -1) const = 0;
   virtual qx_bool fromString(void * pOwner, const QString & s, const QString & sFormat, int iIndexName = -1) = 0;
   virtual QVariant toVariant(const void * pOwner, const QString & sFormat, int iIndexName = -1) const = 0;
   virtual qx_bool fromVariant(void * pOwner, const QVariant & v, const QString & sFormat, int iIndexName = -1) = 0;

   inline QString toString(const void * pOwner, int iIndexName = -1) const             { return this->toString(pOwner, m_sFormat, iIndexName); }
   inline qx_bool fromString(void * pOwner, const QString & s, int iIndexName = -1)    { return this->fromString(pOwner, s, m_sFormat, iIndexName); }
   inline QVariant toVariant(const void * pOwner, int iIndexName = -1) const           { return this->toVariant(pOwner, m_sFormat, iIndexName); }
   inline qx_bool fromVariant(void * pOwner, const QVariant & v, int iIndexName = -1)  { return this->fromVariant(pOwner, v, m_sFormat, iIndexName); }

protected:

   virtual boost::any getDataPtr(const void * pOwner) const = 0;
   virtual boost::any getDataPtr(void * pOwner) = 0;
   virtual void * getDataVoidPtr(const void * pOwner) const = 0;
   virtual void * getDataVoidPtr(void * pOwner) = 0;

public:

   inline boost::any getValueAnyPtr(const void * pOwner) const    { return this->getDataPtr(pOwner); }
   inline boost::any getValueAnyPtr(void * pOwner)                { return this->getDataPtr(pOwner); }
   inline void * getValueVoidPtr(const void * pOwner) const       { return this->getDataVoidPtr(pOwner); }
   inline void * getValueVoidPtr(void * pOwner)                   { return this->getDataVoidPtr(pOwner); }

   template <typename T>
   T * getValuePtr(void * pOwner, bool * bOk = NULL)
   {
      if (bOk) { (* bOk) = false; }
      if (! m_bAccessDataPointer) { qDebug("[QxOrm] qx::IxDataMember::getValuePtr<T>() : '%s'", "cannot access data-member pointer"); return NULL; }
      boost::any a = this->getDataPtr(pOwner);
      try { T * t = boost::any_cast<T *>(a); if (bOk) { (* bOk) = (t != NULL); }; return t; }
      catch (const boost::bad_any_cast & err) { Q_UNUSED(err); qDebug("[QxOrm] qx::IxDataMember::getValuePtr<T>() : '%s'", "bad any cast exception"); return NULL; }
   }

   template <typename T>
   T getValue(void * pOwner, bool * bOk = NULL)
   {
      if (! m_bAccessDataPointer) { return qxCannotAccessDataPointer<T, 0>::getValue(this, pOwner, bOk); }
      T * t = this->getValuePtr<T>(pOwner, bOk);
      return (t ? (* t) : T());
   }

   template <typename T>
   bool setValue(void * pOwner, const T & val)
   {
      if (! m_bAccessDataPointer) { return qxCannotAccessDataPointer<T, 0>::setValue(this, pOwner, val); }
      T * t = this->getValuePtr<T>(pOwner);
      if (t) { (* t) = val; }
      return (t != NULL);
   }

private:

   template <typename T, int dummy>
   struct qxCannotAccessDataPointer
   {
      static inline T getValue(IxDataMember * pData, void * pOwner, bool * bOk)
      { Q_UNUSED(pData); Q_UNUSED(pOwner); qDebug("[QxOrm] qx::IxDataMember::qxCannotAccessDataPointer<T>::getValue() : '%s'", "type T not supported"); if (bOk) { (* bOk) = false; }; return T(); }
      static inline bool setValue(IxDataMember * pData, void * pOwner, const T & val)
      { Q_UNUSED(pData); Q_UNUSED(pOwner); Q_UNUSED(val); qDebug("[QxOrm] qx::IxDataMember::qxCannotAccessDataPointer<T>::setValue() : '%s'", "type T not supported"); return false; }
   };

   template <int dummy>
   struct qxCannotAccessDataPointer<QVariant, dummy>
   {
      static inline QVariant getValue(IxDataMember * pData, void * pOwner, bool * bOk)
      { if (bOk) { (* bOk) = (pData != NULL); }; return (pData ? pData->toVariant(pOwner, "") : QVariant()); }
      static inline bool setValue(IxDataMember * pData, void * pOwner, const QVariant & val)
      { return (pData ? pData->fromVariant(pOwner, val, "").getValue() : false); }
   };

   template <int dummy>
   struct qxCannotAccessDataPointer<QString, dummy>
   {
      static inline QString getValue(IxDataMember * pData, void * pOwner, bool * bOk)
      { if (bOk) { (* bOk) = (pData != NULL); }; return (pData ? pData->toString(pOwner, "") : QString()); }
      static inline bool setValue(IxDataMember * pData, void * pOwner, const QString & val)
      { return (pData ? pData->fromString(pOwner, val, "").getValue() : false); }
   };

public:

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

   inline void updateNamePtr()
   {
      QString sNamePtr = (m_sName.isEmpty() ? m_sKey : m_sName);
      sNamePtr.replace("|", "-"); // valid xml tag
      m_byteName = sNamePtr.toLatin1();
      m_pName = m_byteName.constData();
      m_lstNames = (m_sName.isEmpty() ? m_sKey.split("|") : m_sName.split("|"));
   }

   template <class Archive>
   void serialize(Archive & ar, const unsigned int version);

};

typedef boost::shared_ptr<IxDataMember> IxDataMember_ptr;

} // namespace qx

QX_DLL_EXPORT_INLINE_FCT inline bool operator< (const qx::IxDataMember & i1, const qx::IxDataMember & i2);
QX_DLL_EXPORT_INLINE_FCT inline bool operator> (const qx::IxDataMember & i1, const qx::IxDataMember & i2);

#endif // _IX_DATA_MEMBER_H_
