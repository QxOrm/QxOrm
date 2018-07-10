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

#include <QtSql/qsqlquery.h>
#include <QtSql/qsqlrecord.h>

#include <QxDao/IxSqlRelation.h>
#include <QxDao/IxSqlQueryBuilder.h>
#include <QxDao/QxSqlDatabase.h>
#include <QxDao/QxSqlRelationLinked.h>

#include <QxDataMember/IxDataMember.h>
#include <QxDataMember/IxDataMemberX.h>

#include <QxRegister/IxClass.h>

#include <QxConvert/QxConvert.h>

#include <QxDao/QxSqlRelation_ManyToMany.h>
#include <QxDao/QxSqlRelation_ManyToOne.h>
#include <QxDao/QxSqlRelation_OneToMany.h>
#include <QxDao/QxSqlRelation_OneToOne.h>
#include <QxDao/QxSqlRelation_RawData.h>

#include <QxMemLeak/mem_leak.h>

#define QX_CONSTRUCT_IX_RELATION() \
m_pClass(NULL), m_pClassOwner(NULL), m_pDataMember(p), m_pDataMemberX(NULL), \
m_pDataMemberId(NULL), m_pDataMemberIdOwner(NULL), m_lOffsetRelation(100), \
m_eJoinType(qx::dao::sql_join::left_outer_join), m_eRelationType(IxSqlRelation::no_relation), \
m_bInitInEvent(false), m_bInitDone(false), m_iIsSameDataOwner(0)

namespace qx {

struct IxSqlRelation::IxSqlRelationImpl
{

   typedef QxCollection<QString, IxDataMember *> type_lst_data_member;
   typedef std::shared_ptr<type_lst_data_member> type_lst_data_member_ptr;

   IxClass *                        m_pClass;               //!< 'IxClass' associated wth sql relation
   IxClass *                        m_pClassOwner;          //!< 'IxClass' of the owner
   IxDataMember *                   m_pDataMember;          //!< 'IxDataMember' associated wth sql relation
   IxDataMemberX *                  m_pDataMemberX;         //!< Collection of 'IxDataMember' : parent of 'm_pDataMember'
   IxDataMember *                   m_pDataMemberId;        //!< 'IxDataMember' id of 'm_pDataMemberX'
   IxDataMember *                   m_pDataMemberIdOwner;   //!< 'IxDataMember' id of the owner
   long                             m_lOffsetRelation;      //!< Generic offset for sql relation
   qx::dao::sql_join::join_type     m_eJoinType;            //!< Join type to build sql query
   IxSqlRelation::relation_type     m_eRelationType;        //!< Relation type : one-to-one, one-to-many, etc.
   QxSoftDelete                     m_oSoftDelete;          //!< Soft delete (or logical delete) behavior
   QString                          m_sForeignKey;          //!< SQL query foreign key (1-n)
   QString                          m_sExtraTable;          //!< Extra-table that holds the relationship (n-n)
   QString                          m_sForeignKeyOwner;     //!< SQL query foreign key for owner (n-n)
   QString                          m_sForeignKeyDataType;  //!< SQL query foreign key for data type (n-n)
   bool                             m_bInitInEvent;         //!< Class initialisation in progress
   bool                             m_bInitDone;            //!< Class initialisation finished
   int                              m_iIsSameDataOwner;     //!< Check if relationship source entity and target entity are equal

   type_lst_data_member_ptr m_lstDataMemberPtr;             //!< Optimization : handle to collection of 'IxDataMember'
   std::shared_ptr<IxSqlRelationX> m_lstSqlRelationPtr;     //!< Optimization : handle to collection of 'IxSqlRelation'

   static bool m_bTraceRelationInit;   //!< Can be useful to debug an issue with relationship initialization

   IxSqlRelationImpl(IxDataMember * p) : QX_CONSTRUCT_IX_RELATION() { ; }
   ~IxSqlRelationImpl() { ; }

   IxDataMember * isValid_DataMember(long lIndex) const
   {
      if (! m_pDataMemberX) { return NULL; }
      IxDataMember * p = m_pDataMemberX->get_WithDaoStrategy(lIndex);
      bool bValid = (p && p->getDao() && ! p->hasSqlRelation());
      bValid = (bValid && (p != m_pDataMemberId));
      return (bValid ? p : NULL);
   }

   IxDataMember * isValid_SqlRelation(long lIndex) const
   {
      if (! m_pDataMemberX) { return NULL; }
      IxDataMember * p = m_pDataMemberX->get_WithDaoStrategy(lIndex);
      bool bIsValid = (p && p->getDao() && p->hasSqlRelation());
      if (bIsValid && (! m_iIsSameDataOwner) && (p != m_pDataMember)) { p->getSqlRelation()->init(); }
      return (bIsValid ? p : NULL);
   }

};

bool IxSqlRelation::IxSqlRelationImpl::m_bTraceRelationInit = false;

IxSqlRelation::IxSqlRelation(IxDataMember * p) : qx::QxPropertyBag(), m_pImpl(new IxSqlRelationImpl(p)) { ; }

IxSqlRelation::~IxSqlRelation() { ; }

QString IxSqlRelation::getForeignKey() const { return m_pImpl->m_sForeignKey; }

QString IxSqlRelation::getForeignKeyOwner() const { return m_pImpl->m_sForeignKeyOwner; }

QString IxSqlRelation::getForeignKeyDataType() const { return m_pImpl->m_sForeignKeyDataType; }

QString IxSqlRelation::getExtraTable() const { return m_pImpl->m_sExtraTable; }

QxCollection<QString, IxDataMember *> * IxSqlRelation::getLstDataMember() const { return m_pImpl->m_lstDataMemberPtr.get(); }

IxSqlRelationX * IxSqlRelation::getLstRelation() const { return m_pImpl->m_lstSqlRelationPtr.get(); }

void IxSqlRelation::setSqlJoinType(qx::dao::sql_join::join_type e) { m_pImpl->m_eJoinType = e; }

qx::dao::sql_join::join_type IxSqlRelation::getSqlJoinType() const { return m_pImpl->m_eJoinType; }

IxSqlRelation::relation_type IxSqlRelation::getRelationType() const { return m_pImpl->m_eRelationType; }

IxClass * IxSqlRelation::getClass() const { return m_pImpl->m_pClass; }

IxClass * IxSqlRelation::getClassOwner() const { return m_pImpl->m_pClassOwner; }

IxDataMember * IxSqlRelation::getDataMember() const { return m_pImpl->m_pDataMember; }

IxDataMemberX * IxSqlRelation::getDataMemberX() const { return m_pImpl->m_pDataMemberX; }

IxDataMember * IxSqlRelation::getDataId() const { return m_pImpl->m_pDataMemberId; }

IxDataMember * IxSqlRelation::getDataIdOwner() const { return m_pImpl->m_pDataMemberIdOwner; }

void IxSqlRelation::setIsSameDataOwner(int i) { m_pImpl->m_iIsSameDataOwner = i; }

bool IxSqlRelation::canInit() const { return (! m_pImpl->m_bInitInEvent && ! m_pImpl->m_bInitDone); }

void IxSqlRelation::setClass(IxClass * pClass, IxClass * pClassOwner) { m_pImpl->m_pClass = pClass; m_pImpl->m_pClassOwner = pClassOwner; }

void IxSqlRelation::setRelationType(IxSqlRelation::relation_type e) { m_pImpl->m_eRelationType = e; }

void IxSqlRelation::setForeignKey(const QString & s) const { m_pImpl->m_sForeignKey = s; }

void IxSqlRelation::setForeignKeyOwner(const QString & s) const { m_pImpl->m_sForeignKeyOwner = s; }

void IxSqlRelation::setForeignKeyDataType(const QString & s) const { m_pImpl->m_sForeignKeyDataType = s; }

void IxSqlRelation::setExtraTable(const QString & s) const { m_pImpl->m_sExtraTable = s; }

void IxSqlRelation::init()
{
   if (m_pImpl->m_bInitInEvent || m_pImpl->m_bInitDone) { return; }
   m_pImpl->m_bInitInEvent = true;

   m_pImpl->m_pDataMemberX = (m_pImpl->m_pClass ? m_pImpl->m_pClass->getDataMemberX() : NULL);
   m_pImpl->m_pDataMemberId = (m_pImpl->m_pDataMemberX ? m_pImpl->m_pDataMemberX->getId_WithDaoStrategy() : NULL);
   m_pImpl->m_pDataMemberIdOwner = ((m_pImpl->m_pClassOwner && m_pImpl->m_pClassOwner->getDataMemberX()) ? m_pImpl->m_pClassOwner->getDataMemberX()->getId_WithDaoStrategy() : NULL);
   if (m_pImpl->m_pClass) { m_pImpl->m_oSoftDelete = m_pImpl->m_pClass->getSoftDelete(); }

#ifdef _QX_MODE_DEBUG
   QString sCheckMsg = "Check relationship '" + this->getKey() + "' from '" + (m_pImpl->m_pClassOwner ? m_pImpl->m_pClassOwner->getKey() : QString()) + "' to '" + (m_pImpl->m_pClass ? m_pImpl->m_pClass->getKey() : QString()) + "'";
   if (! m_pImpl->m_pClass) { QString sAssertMsg = sCheckMsg + " : m_pImpl->m_pClass is equal to NULL"; qAssertMsg(false, "[QxOrm] qx::IxSqlRelation::init()", qPrintable(sAssertMsg)); }
   if (! m_pImpl->m_pClassOwner) { QString sAssertMsg = sCheckMsg + " : m_pImpl->m_pClassOwner is equal to NULL"; qAssertMsg(false, "[QxOrm] qx::IxSqlRelation::init()", qPrintable(sAssertMsg)); }
   if (! m_pImpl->m_pDataMember) { QString sAssertMsg = sCheckMsg + " : m_pImpl->m_pDataMember is equal to NULL"; qAssertMsg(false, "[QxOrm] qx::IxSqlRelation::init()", qPrintable(sAssertMsg)); }
   if (! m_pImpl->m_pDataMemberX) { QString sAssertMsg = sCheckMsg + " : m_pImpl->m_pDataMemberX is equal to NULL"; qAssertMsg(false, "[QxOrm] qx::IxSqlRelation::init()", qPrintable(sAssertMsg)); }
   if (! m_pImpl->m_pDataMemberId) { QString sAssertMsg = sCheckMsg + " : m_pImpl->m_pDataMemberId is equal to NULL"; qAssertMsg(false, "[QxOrm] qx::IxSqlRelation::init()", qPrintable(sAssertMsg)); }
#endif // _QX_MODE_DEBUG

   if (IxSqlRelation::IxSqlRelationImpl::m_bTraceRelationInit)
   { QString sTraceMsg = "[QxOrm] Init relationship '" + this->getKey() + "' from '" + (m_pImpl->m_pClassOwner ? m_pImpl->m_pClassOwner->getKey() : QString()) + "' to '" + (m_pImpl->m_pClass ? m_pImpl->m_pClass->getKey() : QString()) + "'"; qDebug() << sTraceMsg; }

   m_pImpl->m_lstSqlRelationPtr.reset(new IxSqlRelationX());
   m_pImpl->m_lstDataMemberPtr.reset(new QxCollection<QString, IxDataMember *>());
   IxDataMember * p = NULL; long lCount = m_pImpl->m_pDataMemberX->count_WithDaoStrategy();

   for (long l = 0; l < lCount; ++l)
   {
      p = m_pImpl->isValid_DataMember(l); if (! p) { continue; }
#ifdef _QX_MODE_DEBUG
      if (m_pImpl->m_lstDataMemberPtr->exist(p->getKey()))
      { QString sDebugMsg = "[QxOrm] Relationship '" + this->getKey() + "' from '" + (m_pImpl->m_pClassOwner ? m_pImpl->m_pClassOwner->getKey() : QString()) + "' to '" + (m_pImpl->m_pClass ? m_pImpl->m_pClass->getKey() : QString()) + "' : data member '" + p->getKey() + "' already exists in the collection"; qDebug() << sDebugMsg; }
#endif // _QX_MODE_DEBUG
      m_pImpl->m_lstDataMemberPtr->insert(p->getKey(), p);
   }

   for (long l = 0; l < lCount; ++l)
   {
      p = m_pImpl->isValid_SqlRelation(l); if (! p) { continue; }
#ifdef _QX_MODE_DEBUG
      if (m_pImpl->m_lstSqlRelationPtr->exist(p->getKey()))
      { QString sDebugMsg = "[QxOrm] Relationship '" + this->getKey() + "' from '" + (m_pImpl->m_pClassOwner ? m_pImpl->m_pClassOwner->getKey() : QString()) + "' to '" + (m_pImpl->m_pClass ? m_pImpl->m_pClass->getKey() : QString()) + "' : relation '" + p->getKey() + "' already exists in the collection"; qDebug() << sDebugMsg; }
#endif // _QX_MODE_DEBUG
      m_pImpl->m_lstSqlRelationPtr->insert(p->getKey(), p->getSqlRelation());
   }

   if (m_pImpl->m_eRelationType == qx::IxSqlRelation::many_to_one)
   {
      // Check if relationship (foreign key) is also a part of primary key
      int iRelationNameCount = (m_pImpl->m_pDataMember ? m_pImpl->m_pDataMember->getNameCount() : 0);
      int iIdOwnerNameCount = (m_pImpl->m_pDataMemberIdOwner ? m_pImpl->m_pDataMemberIdOwner->getNameCount() : 0);
      for (int i = 0; i < iRelationNameCount; i++)
      {
         for (int j = 0; j < iIdOwnerNameCount; j++)
         {
            if (m_pImpl->m_pDataMember->getName(i) == m_pImpl->m_pDataMemberIdOwner->getName(j))
            {
               m_pImpl->m_pDataMemberIdOwner->setRelationPartOfPrimaryKey(j, this, i);
               m_pImpl->m_pDataMember->setPartOfPrimaryKey(i, m_pImpl->m_pDataMemberIdOwner, j);
            }
         }
      }
   }

   m_pImpl->m_bInitInEvent = false;
   m_pImpl->m_bInitDone = true;
}

void IxSqlRelation::setTraceRelationInit(bool bTrace) { IxSqlRelation::IxSqlRelationImpl::m_bTraceRelationInit = bTrace; }

QString IxSqlRelation::getKey() const
{ return (m_pImpl->m_pDataMember ? m_pImpl->m_pDataMember->getKey() : ""); }

long IxSqlRelation::getDataCount() const
{ return (m_pImpl->m_lstDataMemberPtr ? m_pImpl->m_lstDataMemberPtr->count() : 0); }

long IxSqlRelation::getRelationCount() const
{ return (m_pImpl->m_lstSqlRelationPtr ? m_pImpl->m_lstSqlRelationPtr->count() : 0); }

QString IxSqlRelation::table() const
{ return (m_pImpl->m_pDataMemberX ? m_pImpl->m_pDataMemberX->getName() : ""); }

bool IxSqlRelation::traceSqlQuery() const
{ return qx::QxSqlDatabase::getSingleton()->getTraceSqlQuery(); }

IxDataMember * IxSqlRelation::getDataByKey(const QString & sKey) const
{
   if (m_pImpl->m_lstDataMemberPtr && m_pImpl->m_lstDataMemberPtr->exist(sKey)) { return m_pImpl->m_lstDataMemberPtr->getByKey(sKey); }
   else if (m_pImpl->m_lstSqlRelationPtr && m_pImpl->m_lstSqlRelationPtr->exist(sKey)) { return m_pImpl->m_lstSqlRelationPtr->getByKey(sKey)->getDataMember(); }
   return NULL;
}

IxDataMember * IxSqlRelation::nextData(long & lIndex) const
{
   if ((! m_pImpl->m_lstDataMemberPtr) || (lIndex < 0) || (lIndex >= m_pImpl->m_lstDataMemberPtr->count())) { return NULL; }
   ++lIndex;
   return m_pImpl->m_lstDataMemberPtr->getByIndex(lIndex - 1);
}

IxSqlRelation * IxSqlRelation::nextRelation(long & lIndex) const
{
   if ((! m_pImpl->m_lstSqlRelationPtr) || (lIndex < 0) || (lIndex >= m_pImpl->m_lstSqlRelationPtr->count())) { return NULL; }
   ++lIndex;
   return m_pImpl->m_lstSqlRelationPtr->getByIndex(lIndex - 1);
}

QString IxSqlRelation::tableAlias(QxSqlRelationParams & params) const
{
   QString sTableAlias = (m_pImpl->m_pDataMemberX ? (m_pImpl->m_pDataMemberX->getName() + "_" + QString::number(params.index())) : QString(""));
   sTableAlias.replace(".", "_");
   return sTableAlias;
}

QString IxSqlRelation::tableAliasOwner(QxSqlRelationParams & params) const
{
   if (! m_pImpl->m_pClassOwner) { qAssert(false); return ""; }
   QString sTableAliasOwner = (m_pImpl->m_pClassOwner->getName() + "_" + QString::number(params.indexOwner()));
   if (params.indexOwner() <= 0) { sTableAliasOwner = params.builder().table(); }
   if (! params.getTableAlias().isEmpty()) { sTableAliasOwner = params.getTableAlias(); }
   sTableAliasOwner.replace(".", "_");
   return sTableAliasOwner;
}

QString IxSqlRelation::getSqlJoin(qx::dao::sql_join::join_type e /* = qx::dao::sql_join::no_join */) const
{
   QString sJoin;
   if (e == qx::dao::sql_join::no_join) { e = m_pImpl->m_eJoinType; }

   switch (e)
   {
      case qx::dao::sql_join::left_outer_join:  sJoin = " LEFT OUTER JOIN ";     break;
      case qx::dao::sql_join::inner_join:       sJoin = " INNER JOIN ";          break;
      default:                                  sJoin = " LEFT OUTER JOIN ";     break;
   }

   return sJoin;
}

bool IxSqlRelation::verifyOffset(QxSqlRelationParams & params, bool bId) const
{
#ifdef _QX_MODE_DEBUG
   if (! qx::QxSqlDatabase::getSingleton()->getVerifyOffsetRelation()) { return true; }
   IxDataMember * p = (bId ? this->getDataId() : this->getDataMember());
   QString table = (bId ? this->tableAlias(params) : this->tableAliasOwner(params));
   if (! p || table.isEmpty()) { return true; }
   QString sSuffixAlias = ((! bId && (params.indexOwner() > 0)) ? QString("_" + QString::number(params.indexOwner())) : QString());
   QString sRecordToFind = p->getSqlAlias(table) + sSuffixAlias;
   int index = params.query().record().indexOf(sRecordToFind);
   qAssert(index == params.offset());
   return (index == params.offset());
#else // _QX_MODE_DEBUG
   Q_UNUSED(params); Q_UNUSED(bId); return true;
#endif // _QX_MODE_DEBUG
}

QVariant IxSqlRelation::getIdFromQuery_ManyToMany(bool bEager, QxSqlRelationParams & params) const
{
   QString sId; IxDataMember * pId = this->getDataId();
   if (! bEager || ! pId) { return QVariant(); }
   for (int i = 0; i < pId->getNameCount(); i++)
   { sId += params.query().value(params.offset() + i).toString() + "|"; }
   return QVariant(sId);
}

QVariant IxSqlRelation::getIdFromQuery_ManyToOne(bool bEager, QxSqlRelationParams & params) const
{
   Q_UNUSED(bEager); QString sId;
   IxDataMember * pId = this->getDataId(); if (! pId) { return QVariant(); }
   for (int i = 0; i < pId->getNameCount(); i++)
   { sId += params.query().value(params.offset() + i).toString() + "|"; }
   return QVariant(sId);
}

QVariant IxSqlRelation::getIdFromQuery_OneToMany(bool bEager, QxSqlRelationParams & params) const
{
   QString sId; IxDataMember * pId = this->getDataId();
   if (! bEager || ! pId) { return QVariant(); }
   for (int i = 0; i < pId->getNameCount(); i++)
   { sId += params.query().value(params.offset() + i).toString() + "|"; }
   return QVariant(sId);
}

QVariant IxSqlRelation::getIdFromQuery_OneToOne(bool bEager, QxSqlRelationParams & params) const
{
   QString sId; IxDataMember * pId = this->getDataId();
   if (! bEager || ! pId) { return QVariant(); }
   for (int i = 0; i < pId->getNameCount(); i++)
   { sId += params.query().value(params.offset() + i).toString() + "|"; }
   return QVariant(sId);
}

void IxSqlRelation::updateOffset_ManyToMany(bool bEager, QxSqlRelationParams & params) const
{
   if (! bEager) { return; }
   long lOffsetNew = params.offset() + this->getDataCount();
   lOffsetNew += (this->getDataId() ? this->getDataId()->getNameCount() : 0);
   lOffsetNew += (this->m_pImpl->m_oSoftDelete.isEmpty() ? 0 : 1);
   params.setOffset(lOffsetNew);

   if (bEager && (params.getColumnsCount() > 0) && (params.getColumnsOffset() > 0))
   { lOffsetNew = (lOffsetNew - params.getColumnsOffset()); params.setOffset(lOffsetNew); }
   else if (bEager && (params.getColumnsCount() > 0))
   {
      long l1 = 0; IxDataMember * p = NULL; long lColumnsOffset = 0;
      while ((p = this->nextData(l1))) { if (! params.checkColumns(p->getKey())) { lOffsetNew = (lOffsetNew - 1); lColumnsOffset++; } }
      params.setOffset(lOffsetNew); params.setColumnsOffset(lColumnsOffset);
   }

   if (! params.relationX()) { return; }
   long lRelation = 0; IxSqlRelation * pRelation = NULL;
   long lIndexOwnerOld = params.indexOwner();
   params.setIndexOwner(params.index());
   while ((pRelation = this->nextRelation(lRelation)))
   {
      if (this->addLazyRelation(params, pRelation))
      { pRelation->updateOffset(false, params); }
   }
   params.setIndexOwner(lIndexOwnerOld);
}

void IxSqlRelation::updateOffset_ManyToOne(bool bEager, QxSqlRelationParams & params) const
{
   long lOffsetDataMember = (this->getDataMember() ? this->getDataMember()->getNameCount() : 0);
   long lOffsetDataId = (bEager ? (this->getDataId() ? this->getDataId()->getNameCount() : 0) : 0);
   long lOffsetDataCount = (bEager ? this->getDataCount() : 0);
   long lOffsetSoftDelete = (bEager ? (this->m_pImpl->m_oSoftDelete.isEmpty() ? 0 : 1) : 0);
   long lOffsetNew = (params.offset() + lOffsetDataMember + lOffsetDataId + lOffsetDataCount + lOffsetSoftDelete);
   params.setOffset(lOffsetNew);

   if (bEager && (params.getColumnsCount() > 0) && (params.getColumnsOffset() > 0))
   { lOffsetNew = (lOffsetNew - params.getColumnsOffset()); params.setOffset(lOffsetNew); }
   else if (bEager && (params.getColumnsCount() > 0))
   {
      long l1 = 0; IxDataMember * p = NULL; long lColumnsOffset = 0;
      while ((p = this->nextData(l1))) { if (! params.checkColumns(p->getKey())) { lOffsetNew = (lOffsetNew - 1); lColumnsOffset++; } }
      params.setOffset(lOffsetNew); params.setColumnsOffset(lColumnsOffset);
   }

   if (! bEager || ! params.relationX()) { return; }
   long lRelation = 0; IxSqlRelation * pRelation = NULL;
   long lIndexOwnerOld = params.indexOwner();
   params.setIndexOwner(params.index());
   while ((pRelation = this->nextRelation(lRelation)))
   {
      if (this->addLazyRelation(params, pRelation))
      { pRelation->updateOffset(false, params); }
   }
   params.setIndexOwner(lIndexOwnerOld);
}

void IxSqlRelation::updateOffset_OneToMany(bool bEager, QxSqlRelationParams & params) const
{
   if (! bEager) { return; }
   IxDataMember * pForeign = this->getDataByKey(m_pImpl->m_sForeignKey);
   bool bAddOffsetForeign = (pForeign && ! this->getLstDataMember()->exist(m_pImpl->m_sForeignKey));
   long lOffsetId = (this->getDataId() ? this->getDataId()->getNameCount() : 0);
   long lOffsetNew = (params.offset() + this->getDataCount() + lOffsetId);
   lOffsetNew = (lOffsetNew + (bAddOffsetForeign ? pForeign->getNameCount() : 0));
   lOffsetNew = (lOffsetNew + (this->m_pImpl->m_oSoftDelete.isEmpty() ? 0 : 1));
   params.setOffset(lOffsetNew);

   if (bEager && (params.getColumnsCount() > 0) && (params.getColumnsOffset() > 0))
   { lOffsetNew = (lOffsetNew - params.getColumnsOffset()); params.setOffset(lOffsetNew); }
   else if (bEager && (params.getColumnsCount() > 0))
   {
      long l1 = 0; IxDataMember * p = NULL; long lColumnsOffset = 0;
      while ((p = this->nextData(l1))) { if (! params.checkColumns(p->getKey())) { lOffsetNew = (lOffsetNew - 1); lColumnsOffset++; } }
      params.setOffset(lOffsetNew); params.setColumnsOffset(lColumnsOffset);
   }

   if (! params.relationX()) { return; }
   long lRelation = 0; IxSqlRelation * pRelation = NULL;
   long lIndexOwnerOld = params.indexOwner();
   params.setIndexOwner(params.index());
   while ((pRelation = this->nextRelation(lRelation)))
   {
      if (this->addLazyRelation(params, pRelation))
      { pRelation->updateOffset(false, params); }
   }
   params.setIndexOwner(lIndexOwnerOld);
}

void IxSqlRelation::updateOffset_OneToOne(bool bEager, QxSqlRelationParams & params) const
{
   if (! bEager) { return; }
   long lOffsetNew = params.offset() + this->getDataCount();
   lOffsetNew += (this->getDataId() ? this->getDataId()->getNameCount() : 0);
   lOffsetNew += (this->m_pImpl->m_oSoftDelete.isEmpty() ? 0 : 1);
   params.setOffset(lOffsetNew);

   if (bEager && (params.getColumnsCount() > 0) && (params.getColumnsOffset() > 0))
   { lOffsetNew = (lOffsetNew - params.getColumnsOffset()); params.setOffset(lOffsetNew); }
   else if (bEager && (params.getColumnsCount() > 0))
   {
      long l1 = 0; IxDataMember * p = NULL; long lColumnsOffset = 0;
      while ((p = this->nextData(l1))) { if (! params.checkColumns(p->getKey())) { lOffsetNew = (lOffsetNew - 1); lColumnsOffset++; } }
      params.setOffset(lOffsetNew); params.setColumnsOffset(lColumnsOffset);
   }

   if (! params.relationX()) { return; }
   long lRelation = 0; IxSqlRelation * pRelation = NULL;
   long lIndexOwnerOld = params.indexOwner();
   params.setIndexOwner(params.index());
   while ((pRelation = this->nextRelation(lRelation)))
   {
      if (this->addLazyRelation(params, pRelation))
      { pRelation->updateOffset(false, params); }
   }
   params.setIndexOwner(lIndexOwnerOld);
}

void IxSqlRelation::eagerSelect_ManyToMany(QxSqlRelationParams & params) const
{
   long l1(0), l2(0);
   QString & sql = params.sql();
   IxSqlRelation * pRelation = NULL;
   IxDataMember * p = NULL; IxDataMember * pId = this->getDataId(); qAssert(pId);
   QString tableAlias = this->tableAlias(params);
   if (pId) { sql += (pId->getSqlTablePointNameAsAlias(tableAlias) + ", "); }
   while ((p = this->nextData(l1))) { if (params.checkColumns(p->getKey())) { sql += (p->getSqlTablePointNameAsAlias(tableAlias) + ", "); } }

   if (params.relationX())
   {
      long lIndexOwnerOld = params.indexOwner();
      QString sTableAliasOld = params.getTableAlias();
      params.setIndexOwner(params.index());
      params.setTableAlias(tableAlias);
      while ((pRelation = this->nextRelation(l2)))
      { if (this->addLazyRelation(params, pRelation)) { pRelation->lazySelect(params); } }
      params.setIndexOwner(lIndexOwnerOld);
      params.setTableAlias(sTableAliasOld);
   }

   if (! this->m_pImpl->m_oSoftDelete.isEmpty()) { sql += (this->m_pImpl->m_oSoftDelete.buildSqlTablePointName(tableAlias) + ", "); }
}

void IxSqlRelation::eagerSelect_ManyToOne(QxSqlRelationParams & params) const
{
   long l1(0), l2(0);
   QString & sql = params.sql();
   IxSqlRelation * pRelation = NULL;
   IxDataMember * pData = this->getDataMember(); qAssert(pData);
   IxDataMember * p = NULL; IxDataMember * pId = this->getDataId(); qAssert(pId);
   QString table = this->table(); QString tableAlias = this->tableAlias(params);
   QString tableRef = this->tableAliasOwner(params); QString sSuffixAlias;
   if (params.indexOwner() > 0) { sSuffixAlias = "_" + QString::number(params.indexOwner()); }
   if (pData) { sql += (pData->getSqlTablePointNameAsAlias(tableRef, ", ", sSuffixAlias) + ", "); }
   if (pId) { sql += (pId->getSqlTablePointNameAsAlias(tableAlias) + ", "); }
   while ((p = this->nextData(l1))) { if (params.checkColumns(p->getKey())) { sql += (p->getSqlTablePointNameAsAlias(tableAlias) + ", "); } }

   if (params.relationX())
   {
      long lIndexOwnerOld = params.indexOwner();
      QString sTableAliasOld = params.getTableAlias();
      params.setIndexOwner(params.index());
      params.setTableAlias(tableAlias);
      while ((pRelation = this->nextRelation(l2)))
      { if (this->addLazyRelation(params, pRelation)) { pRelation->lazySelect(params); } }
      params.setIndexOwner(lIndexOwnerOld);
      params.setTableAlias(sTableAliasOld);
   }

   if (! this->m_pImpl->m_oSoftDelete.isEmpty()) { sql += (this->m_pImpl->m_oSoftDelete.buildSqlTablePointName(tableAlias) + ", "); }
}

void IxSqlRelation::eagerSelect_OneToMany(QxSqlRelationParams & params) const
{
   long l1(0), l2(0);
   QString & sql = params.sql();
   IxSqlRelation * pRelation = NULL;
   IxDataMember * pForeign = this->getDataByKey(this->m_pImpl->m_sForeignKey); qAssert(pForeign);
   IxDataMember * p = NULL; IxDataMember * pId = this->getDataId(); qAssert(pId);
   QString tableAlias = this->tableAlias(params);
   if (pId) { sql += (pId->getSqlTablePointNameAsAlias(tableAlias) + ", "); }
   if (pForeign) { sql += (pForeign->getSqlTablePointNameAsAlias(tableAlias) + ", "); }
   while ((p = this->nextData(l1))) { if ((p != pForeign) && (params.checkColumns(p->getKey()))) { sql += (p->getSqlTablePointNameAsAlias(tableAlias) + ", "); } }

   if (params.relationX())
   {
      long lIndexOwnerOld = params.indexOwner();
      QString sTableAliasOld = params.getTableAlias();
      params.setIndexOwner(params.index());
      params.setTableAlias(tableAlias);
      while ((pRelation = this->nextRelation(l2)))
      { if (this->addLazyRelation(params, pRelation)) { pRelation->lazySelect(params); } }
      params.setIndexOwner(lIndexOwnerOld);
      params.setTableAlias(sTableAliasOld);
   }

   if (! this->m_pImpl->m_oSoftDelete.isEmpty()) { sql += (this->m_pImpl->m_oSoftDelete.buildSqlTablePointName(tableAlias) + ", "); }
}

void IxSqlRelation::eagerSelect_OneToOne(QxSqlRelationParams & params) const
{
   long l1(0), l2(0);
   QString & sql = params.sql();
   IxSqlRelation * pRelation = NULL;
   QString tableAlias = this->tableAlias(params);
   IxDataMember * p = NULL; IxDataMember * pId = this->getDataId(); qAssert(pId);
   if (pId) { sql += (pId->getSqlTablePointNameAsAlias(tableAlias) + ", "); }
   while ((p = this->nextData(l1))) { if (params.checkColumns(p->getKey())) { sql += (p->getSqlTablePointNameAsAlias(tableAlias) + ", "); } }

   if (params.relationX())
   {
      long lIndexOwnerOld = params.indexOwner();
      QString sTableAliasOld = params.getTableAlias();
      params.setIndexOwner(params.index());
      params.setTableAlias(tableAlias);
      while ((pRelation = this->nextRelation(l2)))
      { if (this->addLazyRelation(params, pRelation)) { pRelation->lazySelect(params); } }
      params.setIndexOwner(lIndexOwnerOld);
      params.setTableAlias(sTableAliasOld);
   }

   if (! this->m_pImpl->m_oSoftDelete.isEmpty()) { sql += (this->m_pImpl->m_oSoftDelete.buildSqlTablePointName(tableAlias) + ", "); }
}

void IxSqlRelation::eagerJoin_ManyToMany(QxSqlRelationParams & params) const
{
   QString & sql = params.sql();
   IxDataMember * pIdOwner = this->getDataIdOwner(); qAssert(pIdOwner);
   IxDataMember * pIdData = this->getDataId(); qAssert(pIdData);
   QString table = this->table(); QString tableAlias = this->tableAlias(params);
   QString tableOwner = this->tableAliasOwner(params);
   if (! pIdOwner || ! pIdData) { return; }
   QStringList lstForeignKeyOwner = m_pImpl->m_sForeignKeyOwner.split("|");
   QStringList lstForeignKeyDataType = m_pImpl->m_sForeignKeyDataType.split("|");
   qAssert(pIdOwner->getNameCount() == lstForeignKeyOwner.count());
   qAssert(pIdData->getNameCount() == lstForeignKeyDataType.count());
   QString sExtraTableAlias = m_pImpl->m_sExtraTable + "_" + QString::number(params.index());
   sql += this->getSqlJoin(params.joinType()) + m_pImpl->m_sExtraTable + " " + sExtraTableAlias + " ON ";
   for (int i = 0; i < pIdOwner->getNameCount(); i++)
   { sql += pIdOwner->getSqlAlias(tableOwner, true, i) + " = " + sExtraTableAlias + "." + lstForeignKeyOwner.at(i) + " AND "; }
   sql = sql.left(sql.count() - 5); // Remove last " AND "
   sql += this->getSqlJoin(params.joinType()) + table + " " + tableAlias + " ON ";
   params.builder().addSqlQueryAlias(table, tableAlias);
   for (int i = 0; i < pIdData->getNameCount(); i++)
   { sql += sExtraTableAlias + "." + lstForeignKeyDataType.at(i) + " = " + pIdData->getSqlAlias(tableAlias, true, i) + " AND "; }
   sql = sql.left(sql.count() - 5); // Remove last " AND "
}

void IxSqlRelation::eagerJoin_ManyToOne(QxSqlRelationParams & params) const
{
   QString & sql = params.sql();
   IxDataMember * pId = this->getDataId(); qAssert(pId);
   IxDataMember * pData = this->getDataMember(); qAssert(pData);
   QString table = this->table(); QString tableAlias = this->tableAlias(params);
   QString tableRef = this->tableAliasOwner(params);
   if (! pId || ! pData) { return; }
   sql += this->getSqlJoin(params.joinType()) + table + " " + tableAlias + " ON ";
   params.builder().addSqlQueryAlias(table, tableAlias);
   for (int i = 0; i < pId->getNameCount(); i++)
   { sql += pId->getSqlAlias(tableAlias, true, i) + " = " + pData->getSqlAlias(tableRef, true, i) + " AND "; }
   sql = sql.left(sql.count() - 5); // Remove last " AND "
}

void IxSqlRelation::eagerJoin_OneToMany(QxSqlRelationParams & params) const
{
   QString & sql = params.sql();
   IxDataMember * pId = this->getDataIdOwner(); qAssert(pId);
   IxDataMember * pForeign = this->getDataByKey(this->m_pImpl->m_sForeignKey); qAssert(pForeign);
   QString table = this->table(); QString tableAlias = this->tableAlias(params);
   QString tableRef = this->tableAliasOwner(params);
   if (! pId || ! pForeign) { return; }
   sql += this->getSqlJoin(params.joinType()) + table + " " + tableAlias + " ON ";
   params.builder().addSqlQueryAlias(table, tableAlias);
   for (int i = 0; i < pId->getNameCount(); i++)
   { sql += pForeign->getSqlAlias(tableAlias, true, i) + " = " + pId->getSqlAlias(tableRef, true, i) + " AND "; }
   sql = sql.left(sql.count() - 5); // Remove last " AND "
}

void IxSqlRelation::eagerJoin_OneToOne(QxSqlRelationParams & params) const
{
   QString & sql = params.sql();
   IxDataMember * pId = this->getDataId(); qAssert(pId);
   IxDataMember * pIdRef = this->getDataIdOwner(); qAssert(pIdRef);
   QString table = this->table(); QString tableAlias = this->tableAlias(params);
   QString tableRef = this->tableAliasOwner(params);
   if (! pId || ! pIdRef) { return; }
   sql += this->getSqlJoin(params.joinType()) + table + " " + tableAlias + " ON ";
   params.builder().addSqlQueryAlias(table, tableAlias);
   for (int i = 0; i < pId->getNameCount(); i++)
   { sql += pId->getSqlAlias(tableAlias, true, i) + " = " + pIdRef->getSqlAlias(tableRef, true, i) + " AND "; }
   sql = sql.left(sql.count() - 5); // Remove last " AND "
}

void IxSqlRelation::eagerWhereSoftDelete_ManyToMany(QxSqlRelationParams & params) const
{
   if (this->m_pImpl->m_oSoftDelete.isEmpty()) { return; }
   QString & sql = params.sql();
   QString tableAlias = this->tableAlias(params);
   sql += qx::IxSqlQueryBuilder::addSqlCondition(sql);
   sql += this->m_pImpl->m_oSoftDelete.buildSqlQueryToFetch(tableAlias);
}

void IxSqlRelation::eagerWhereSoftDelete_ManyToOne(QxSqlRelationParams & params) const
{
   if (this->m_pImpl->m_oSoftDelete.isEmpty()) { return; }
   QString & sql = params.sql();
   QString tableAlias = this->tableAlias(params);
   sql += qx::IxSqlQueryBuilder::addSqlCondition(sql);
   sql += this->m_pImpl->m_oSoftDelete.buildSqlQueryToFetch(tableAlias);
}

void IxSqlRelation::eagerWhereSoftDelete_OneToMany(QxSqlRelationParams & params) const
{
   if (this->m_pImpl->m_oSoftDelete.isEmpty()) { return; }
   QString & sql = params.sql();
   QString tableAlias = this->tableAlias(params);
   sql += qx::IxSqlQueryBuilder::addSqlCondition(sql);
   sql += this->m_pImpl->m_oSoftDelete.buildSqlQueryToFetch(tableAlias);
}

void IxSqlRelation::eagerWhereSoftDelete_OneToOne(QxSqlRelationParams & params) const
{
   if (this->m_pImpl->m_oSoftDelete.isEmpty()) { return; }
   QString & sql = params.sql();
   QString tableAlias = this->tableAlias(params);
   sql += qx::IxSqlQueryBuilder::addSqlCondition(sql);
   sql += this->m_pImpl->m_oSoftDelete.buildSqlQueryToFetch(tableAlias);
}

void IxSqlRelation::lazySelect_ManyToOne(QxSqlRelationParams & params) const
{
   QString & sql = params.sql();
   IxDataMember * pData = this->getDataMember(); qAssert(pData);
   QString tableRef = this->tableAliasOwner(params); QString sSuffixAlias;
   if (params.indexOwner() > 0) { sSuffixAlias = "_" + QString::number(params.indexOwner()); }
   if (pData) { sql += (pData->getSqlTablePointNameAsAlias(tableRef, ", ", sSuffixAlias) + ", "); }
}

void IxSqlRelation::lazyInsert_ManyToOne(QxSqlRelationParams & params) const
{
   QString & sql = params.sql();
   IxDataMember * pData = this->getDataMember(); qAssert(pData);
   if (pData) { sql += pData->getSqlName(", ") + ", "; }
}

void IxSqlRelation::lazyInsert_Values_ManyToOne(QxSqlRelationParams & params) const
{
   QString & sql = params.sql();
   IxDataMember * pData = this->getDataMember(); qAssert(pData);
   if (pData) { sql += pData->getSqlPlaceHolder("", -1, ", ") + ", "; }
}

void IxSqlRelation::lazyUpdate_ManyToOne(QxSqlRelationParams & params) const
{
   QString & sql = params.sql();
   IxDataMember * pData = this->getDataMember(); qAssert(pData);
   if (pData) { sql += pData->getSqlNameEqualToPlaceHolder("", ", ") + ", "; }
}

void IxSqlRelation::createTable_ManyToOne(QxSqlRelationParams & params) const
{
   QString & sql = params.sql();
   IxDataMember * pData = this->getDataMember(); qAssert(pData);
   if (pData) { sql += pData->getSqlNameAndTypeAndParams(", ") + ", "; qAssert(! pData->getSqlType().isEmpty()); }
}

QString IxSqlRelation::createExtraTable_ManyToMany() const
{
   IxDataMember * pIdOwner = this->getDataIdOwner(); qAssert(pIdOwner);
   IxDataMember * pIdData = this->getDataId(); qAssert(pIdData);
   if (! pIdOwner || ! pIdData) { return ""; }

   bool bOldPKOwner = pIdOwner->getIsPrimaryKey(); pIdOwner->setIsPrimaryKey(false);
   bool bOldPKData = ((pIdOwner == pIdData) ? bOldPKOwner : pIdData->getIsPrimaryKey()); pIdData->setIsPrimaryKey(false);
   bool bOldAIOwner = pIdOwner->getAutoIncrement(); pIdOwner->setAutoIncrement(false);
   bool bOldAIData = ((pIdOwner == pIdData) ? bOldAIOwner : pIdData->getAutoIncrement()); pIdData->setAutoIncrement(false);

   QString sql = "CREATE TABLE IF NOT EXISTS " + this->m_pImpl->m_sExtraTable + " (";
   sql += pIdOwner->getSqlNameAndTypeAndParams(", ", this->m_pImpl->m_sForeignKeyOwner) + ", "; qAssert(! pIdOwner->getSqlType().isEmpty());
   sql += pIdData->getSqlNameAndTypeAndParams(", ", this->m_pImpl->m_sForeignKeyDataType) + ", "; qAssert(! pIdData->getSqlType().isEmpty());
   sql = sql.left(sql.count() - 2); // Remove last ", "
   sql += ")";

   pIdOwner->setIsPrimaryKey(bOldPKOwner); pIdData->setIsPrimaryKey(bOldPKData);
   pIdOwner->setAutoIncrement(bOldAIOwner); pIdData->setAutoIncrement(bOldAIData);
   if (this->traceSqlQuery()) { qDebug("[QxOrm] create extra-table (relation many-to-many) : %s", qPrintable(sql)); }
   return sql;
}

QSqlError IxSqlRelation::deleteFromExtraTable_ManyToMany(QxSqlRelationParams & params) const
{
   IxDataMember * pIdOwner = this->getDataIdOwner(); qAssert(pIdOwner);
   QString sql = "DELETE FROM " + this->m_pImpl->m_sExtraTable + " WHERE ";
   QStringList lstForeignKeyOwner = this->m_pImpl->m_sForeignKeyOwner.split("|");
   qAssert(pIdOwner->getNameCount() == lstForeignKeyOwner.count());
   for (int i = 0; i < pIdOwner->getNameCount(); i++)
   { sql += this->m_pImpl->m_sExtraTable + "." + lstForeignKeyOwner.at(i) + " = " + pIdOwner->getSqlPlaceHolder("", i) + " AND "; }
   sql = sql.left(sql.count() - 5); // Remove last " AND "
   if (this->traceSqlQuery()) { qDebug("[QxOrm] sql query (extra-table) : %s", qPrintable(sql)); }

   QSqlQuery queryDelete(params.database());
   if (! queryDelete.prepare(sql)) { return queryDelete.lastError(); }
   pIdOwner->setSqlPlaceHolder(queryDelete, params.owner());
   if (! queryDelete.exec()) { return queryDelete.lastError(); }
   return QSqlError();
}

bool IxSqlRelation::addLazyRelation(QxSqlRelationParams & params, IxSqlRelation * pRelation) const
{
   if (! params.relationX() || ! pRelation) { return false; }
   qx::QxSqlRelationLinked_ptr pRelationLinked = params.relationX()->value(this->getKey());
   return (! pRelationLinked || ! pRelationLinked->existRelation(pRelation->getKey()));
}

} // namespace qx
