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

#include <QtSql/qsqlquery.h>

#ifndef _QX_NO_JSON
#include <QtCore/qjsonvalue.h>
#endif // _QX_NO_JSON

#include <QxCommon/QxAny.h>
#include <QxCommon/QxBool.h>
#include <QxCommon/QxPropertyBag.h>

#include <QxSerialize/boost/QxSerializeInclude.h>

#include <QxConvert/QxConvert.h>

#ifdef _MSC_VER
#pragma warning(pop)
#endif // _MSC_VER

#define QX_IX_DATA_MEMBER_PURE_VIRTUAL_ARCHIVE(ArchiveInput, ArchiveOutput) \
virtual void toArchive(const void * pOwner, ArchiveOutput & ar) const = 0; \
virtual void fromArchive(void * pOwner, ArchiveInput & ar) = 0;

namespace qx {

class IxDataMemberX;
class IxSqlRelation;

/*!
 * \ingroup QxDataMember
 * \brief qx::IxDataMember : common interface for all class properties registered into QxOrm context
 */
class QX_DLL_EXPORT IxDataMember : public qx::QxPropertyBag
{

private:

   struct IxDataMemberImpl;
   std::unique_ptr<IxDataMemberImpl> m_pImpl; //!< Private implementation idiom

public:

   IxDataMember(const QString & sKey);
   IxDataMember(const QString & sKey, long lVersion, bool bSerialize, bool bDao);
   virtual ~IxDataMember() = 0;

   QString getKey() const;
   QString getName() const;
   int getNameCount() const;
   QString getNameParent() const;
   const char * getNamePtr() const;
   QString getDescription() const;
   QString getFormat() const;
   long getVersion() const;
   bool getSerialize() const;
   bool getDao() const;
   QVariant getDefaultValue() const;
   QVariant getMinValue() const;
   QVariant getMaxValue() const;
   int getPrecision() const;
   int getMinLength() const;
   int getMaxLength() const;
   bool getRequired() const;
   bool getReadOnly() const;
   bool getAutoIncrement() const;
   bool getNotNull() const;
   bool getIsPrimaryKey() const;
   bool getIsIndex() const;
   bool getIsUnique() const;
   IxDataMemberX * getParent() const;
   IxSqlRelation * getSqlRelation() const;
   bool hasSqlRelation() const;
   bool getAccessDataPointer() const;

   void setName(const QString & s);
   void setNameParent(const QString & s);
   void setDescription(const QString & s);
   void setFormat(const QString & s);
   void setSqlType(const QString & s);
   void setSqlAlias(const QString & s);
   void setVersion(long l);
   void setSerialize(bool b);
   void setDao(bool b);
   void setDefaultValue(const QVariant & v);
   void setPrecision(int i);
   void setRequired(bool b);
   void setReadOnly(bool b);
   void setAutoIncrement(bool b);
   void setIsPrimaryKey(bool b);
   void setIsIndex(bool b);
   void setIsUnique(bool b);
   void setParent(IxDataMemberX * p);
   void setSqlRelation(IxSqlRelation * p);
   void setAccessDataPointer(bool b);

   void setMinValue(long lMinValue, const QString & sMessage = QString());
   void setMinValue(double dMinValue, const QString & sMessage = QString());
   void setMaxValue(long lMaxValue, const QString & sMessage = QString());
   void setMaxValue(double dMaxValue, const QString & sMessage = QString());
   void setMinLength(int iMinLength, const QString & sMessage = QString());
   void setMaxLength(int iMaxLength, const QString & sMessage = QString());
   void setNotNull(bool bNotNull, const QString & sMessage = QString());

   bool isThereRelationPartOfPrimaryKey(int iIndexNamePK, IxSqlRelation * & pRelation, int & iIndexNameFK) const;
   bool isPartOfPrimaryKey(int iIndexNameFK, IxDataMember * & pPrimaryKey, int & iIndexNamePK) const;
   void setRelationPartOfPrimaryKey(int iIndexNamePK, IxSqlRelation * pRelation, int iIndexNameFK);
   void setPartOfPrimaryKey(int iIndexNameFK, IxDataMember * pPrimaryKey, int iIndexNamePK);

   QString getName(int iIndex, const QString & sOtherName = QString()) const;
   QString getSqlAlias(const QString & sTable = QString(), bool bClauseWhere = false, int iIndexName = 0) const;
   QString getSqlType(int iIndexName = -1) const;
   QString getSqlTypeAndParams(int iIndexName = -1) const;
   QString getSqlPlaceHolder(const QString & sAppend = QString(), int iIndexName = 0, const QString & sSep = QString(", "), const QString & sOtherName = QString(), bool bCheckFKPartOfPK = false) const;
   void setSqlPlaceHolder(QSqlQuery & query, void * pOwner, const QString & sAppend = QString(), const QString & sOtherName = QString(), bool bCheckFKPartOfPK = false) const;
   QString getSqlAliasEqualToPlaceHolder(const QString & sTable = QString(), bool bClauseWhere = false, const QString & sAppend = QString(), const QString & sSep = QString(" AND "), bool bCheckFKPartOfPK = false) const;
   QString getSqlNameEqualToPlaceHolder(const QString & sAppend = QString(), const QString & sSep = QString(" AND "), bool bCheckFKPartOfPK = false) const;
   QString getSqlTablePointNameAsAlias(const QString & sTable, const QString & sSep = QString(", "), const QString & sSuffixAlias = QString(), bool bCheckFKPartOfPK = false) const;
   QString getSqlName(const QString & sSep = QString(", "), const QString & sOtherName = QString(), bool bCheckFKPartOfPK = false) const;
   QString getSqlNameAndTypeAndParams(const QString & sSep = QString(", "), const QString & sOtherName = QString(), bool bCheckFKPartOfPK = false) const;

   static QString getSqlFromTable(const QString & sTable);

   virtual bool isEqual(const void * pOwner1, const void * pOwner2) const = 0;
   virtual QVariant toVariant(const void * pOwner, const QString & sFormat, int iIndexName = -1, qx::cvt::context::ctx_type ctx = qx::cvt::context::e_no_context) const = 0;
   virtual qx_bool fromVariant(void * pOwner, const QVariant & v, const QString & sFormat, int iIndexName = -1, qx::cvt::context::ctx_type ctx = qx::cvt::context::e_no_context) = 0;

   QVariant toVariant(const void * pOwner, int iIndexName = -1, qx::cvt::context::ctx_type ctx = qx::cvt::context::e_no_context) const;
   qx_bool fromVariant(void * pOwner, const QVariant & v, int iIndexName = -1, qx::cvt::context::ctx_type ctx = qx::cvt::context::e_no_context);

#ifndef _QX_NO_JSON
   virtual QJsonValue toJson(const void * pOwner, const QString & sFormat) const = 0;
   virtual qx_bool fromJson(void * pOwner, const QJsonValue & j, const QString & sFormat) = 0;

   QJsonValue toJson(const void * pOwner) const;
   qx_bool fromJson(void * pOwner, const QJsonValue & j);
#endif // _QX_NO_JSON

protected:

   virtual qx::any getDataPtr(const void * pOwner) const = 0;
   virtual qx::any getDataPtr(void * pOwner) = 0;
   virtual void * getDataVoidPtr(const void * pOwner) const = 0;
   virtual void * getDataVoidPtr(void * pOwner) = 0;

public:

   qx::any getValueAnyPtr(const void * pOwner) const    { return this->getDataPtr(pOwner); }
   qx::any getValueAnyPtr(void * pOwner)                { return this->getDataPtr(pOwner); }
   void * getValueVoidPtr(const void * pOwner) const       { return this->getDataVoidPtr(pOwner); }
   void * getValueVoidPtr(void * pOwner)                   { return this->getDataVoidPtr(pOwner); }

   template <typename T>
   T * getValuePtr(void * pOwner, bool * bOk = NULL)
   {
      if (bOk) { (* bOk) = false; }
      if (! getAccessDataPointer()) { qDebug("[QxOrm] qx::IxDataMember::getValuePtr<T>() : '%s'", "cannot access data-member pointer"); return NULL; }
      qx::any a = this->getDataPtr(pOwner);
      try { T * t = qx::any_cast<T *>(a); if (bOk) { (* bOk) = (t != NULL); }; return t; }
      catch (const qx::bad_any_cast & err) { Q_UNUSED(err); qDebug("[QxOrm] qx::IxDataMember::getValuePtr<T>() : '%s'", "bad any cast exception"); return NULL; }
      catch (...) { qDebug("[QxOrm] qx::IxDataMember::getValuePtr<T>() : '%s'", "unknown cast exception"); return NULL; }
   }

   template <typename T>
   T getValue(void * pOwner, bool * bOk = NULL)
   {
      if (! getAccessDataPointer()) { return qxCannotAccessDataPointer<T, 0>::getValue(this, pOwner, bOk); }
      T * t = this->getValuePtr<T>(pOwner, bOk);
      return (t ? (* t) : T());
   }

   template <typename T>
   bool setValue(void * pOwner, const T & val)
   {
      if (! getAccessDataPointer()) { return qxCannotAccessDataPointer<T, 0>::setValue(this, pOwner, val); }
      T * t = this->getValuePtr<T>(pOwner);
      if (t) { (* t) = val; }
      return (t != NULL);
   }

private:

   template <typename T, int dummy>
   struct qxCannotAccessDataPointer
   {
      static T getValue(IxDataMember * pData, void * pOwner, bool * bOk)
      { Q_UNUSED(pData); Q_UNUSED(pOwner); qDebug("[QxOrm] qx::IxDataMember::qxCannotAccessDataPointer<T>::getValue() : '%s'", "type T not supported"); if (bOk) { (* bOk) = false; }; return T(); }
      static bool setValue(IxDataMember * pData, void * pOwner, const T & val)
      { Q_UNUSED(pData); Q_UNUSED(pOwner); Q_UNUSED(val); qDebug("[QxOrm] qx::IxDataMember::qxCannotAccessDataPointer<T>::setValue() : '%s'", "type T not supported"); return false; }
   };

   template <int dummy>
   struct qxCannotAccessDataPointer<QVariant, dummy>
   {
      static QVariant getValue(IxDataMember * pData, void * pOwner, bool * bOk)
      { if (bOk) { (* bOk) = (pData != NULL); }; return (pData ? pData->toVariant(pOwner, "") : QVariant()); }
      static bool setValue(IxDataMember * pData, void * pOwner, const QVariant & val)
      { return (pData ? pData->fromVariant(pOwner, val, "").getValue() : false); }
   };

   template <int dummy>
   struct qxCannotAccessDataPointer<QString, dummy>
   {
      static QString getValue(IxDataMember * pData, void * pOwner, bool * bOk)
      { if (bOk) { (* bOk) = (pData != NULL); }; return (pData ? pData->toVariant(pOwner, "").toString() : QString()); }
      static bool setValue(IxDataMember * pData, void * pOwner, const QString & val)
      { QVariant tmp(val); return (pData ? pData->fromVariant(pOwner, tmp, "").getValue() : false); }
   };

public:

#ifdef _QX_ENABLE_BOOST_SERIALIZATION

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

#endif // _QX_ENABLE_BOOST_SERIALIZATION

private:

#ifdef _QX_ENABLE_BOOST_SERIALIZATION
   template <class Archive>
   void serialize(Archive & ar, const unsigned int version);
#endif // _QX_ENABLE_BOOST_SERIALIZATION

};

typedef std::shared_ptr<IxDataMember> IxDataMember_ptr;

} // namespace qx

QX_DLL_EXPORT_INLINE_FCT bool operator< (const qx::IxDataMember & i1, const qx::IxDataMember & i2);
QX_DLL_EXPORT_INLINE_FCT bool operator> (const qx::IxDataMember & i1, const qx::IxDataMember & i2);

#endif // _IX_DATA_MEMBER_H_
