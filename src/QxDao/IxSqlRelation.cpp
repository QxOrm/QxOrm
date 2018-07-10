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

#include <QxCommon/QxStringCvt.h>

#include <QxDao/QxSqlRelation_ManyToMany.h>
#include <QxDao/QxSqlRelation_ManyToOne.h>
#include <QxDao/QxSqlRelation_OneToMany.h>
#include <QxDao/QxSqlRelation_OneToOne.h>
#include <QxDao/QxSqlRelation_RawData.h>

#include <QxMemLeak/mem_leak.h>

namespace qx {

IxSqlRelation::~IxSqlRelation() { ; }

QString IxSqlRelation::getKey() const
{ return (m_pDataMember ? m_pDataMember->getKey() : ""); }

long IxSqlRelation::getDataCount() const
{ return (m_lstDataMemberPtr ? m_lstDataMemberPtr->count() : 0); }

long IxSqlRelation::getRelationCount() const
{ return (m_lstSqlRelationPtr ? m_lstSqlRelationPtr->count() : 0); }

QString IxSqlRelation::table() const
{ return (m_pDataMemberX ? m_pDataMemberX->getName() : ""); }

bool IxSqlRelation::traceSqlQuery() const
{ return qx::QxSqlDatabase::getSingleton()->getTraceSqlQuery(); }

IxDataMember * IxSqlRelation::getDataByKey(const QString & sKey) const
{
   if (m_lstDataMemberPtr && m_lstDataMemberPtr->exist(sKey)) { return m_lstDataMemberPtr->getByKey(sKey); }
   else if (m_lstSqlRelationPtr && m_lstSqlRelationPtr->exist(sKey)) { return m_lstSqlRelationPtr->getByKey(sKey)->getDataMember(); }
   return NULL;
}

IxDataMember * IxSqlRelation::nextData(long & lIndex) const
{
   if ((! m_lstDataMemberPtr) || (lIndex < 0) || (lIndex >= m_lstDataMemberPtr->count())) { return NULL; }
   ++lIndex;
   return m_lstDataMemberPtr->getByIndex(lIndex - 1);
}

IxSqlRelation * IxSqlRelation::nextRelation(long & lIndex) const
{
   if ((! m_lstSqlRelationPtr) || (lIndex < 0) || (lIndex >= m_lstSqlRelationPtr->count())) { return NULL; }
   ++lIndex;
   return m_lstSqlRelationPtr->getByIndex(lIndex - 1);
}

QString IxSqlRelation::tableAlias(QxSqlRelationParams & params) const
{
   QString sTableAlias = (m_pDataMemberX ? (m_pDataMemberX->getName() + "_" + QString::number(params.index())) : QString(""));
   sTableAlias.replace(".", "_");
   return sTableAlias;
}

QString IxSqlRelation::tableAliasOwner(QxSqlRelationParams & params) const
{
   if (! m_pClassOwner) { qAssert(false); return ""; }
   QString sTableAliasOwner = (m_pClassOwner->getName() + "_" + QString::number(params.indexOwner()));
   if (params.indexOwner() <= 0) { sTableAliasOwner = params.builder().table(); }
   if (! params.getTableAlias().isEmpty()) { sTableAliasOwner = params.getTableAlias(); }
   sTableAliasOwner.replace(".", "_");
   return sTableAliasOwner;
}

QString IxSqlRelation::getSqlJoin(qx::dao::sql_join::join_type e /* = qx::dao::sql_join::no_join */) const
{
   QString sJoin;
   if (e == qx::dao::sql_join::no_join) { e = m_eJoinType; }

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
#ifndef _QX_MODE_RELEASE
   if (! qx::QxSqlDatabase::getSingleton()->getVerifyOffsetRelation()) { return true; }
   IxDataMember * p = (bId ? this->getDataId() : this->getDataMember());
   QString table = (bId ? this->tableAlias(params) : this->tableAliasOwner(params));
   if (! p || table.isEmpty()) { return true; }
   QString sSuffixAlias = ((! bId && (params.indexOwner() > 0)) ? QString("_" + QString::number(params.indexOwner())) : QString());
   QString sRecordToFind = p->getSqlAlias(table) + sSuffixAlias;
   int index = params.query().record().indexOf(sRecordToFind);
   qAssert(index == params.offset());
   return (index == params.offset());
#else // _QX_MODE_RELEASE
   Q_UNUSED(params); Q_UNUSED(bId); return true;
#endif // _QX_MODE_RELEASE
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
   lOffsetNew += (this->m_oSoftDelete.isEmpty() ? 0 : 1);
   params.setOffset(lOffsetNew);

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
   long lOffsetSoftDelete = (bEager ? (this->m_oSoftDelete.isEmpty() ? 0 : 1) : 0);
   params.setOffset(params.offset() + lOffsetDataMember + lOffsetDataId + lOffsetDataCount + lOffsetSoftDelete);

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
   IxDataMember * pForeign = this->getDataByKey(m_sForeignKey);
   bool bAddOffsetForeign = (pForeign && ! this->getLstDataMember()->exist(m_sForeignKey));
   long lOffsetId = (this->getDataId() ? this->getDataId()->getNameCount() : 0);
   long lNewOffset = (params.offset() + this->getDataCount() + lOffsetId);
   lNewOffset = (lNewOffset + (bAddOffsetForeign ? pForeign->getNameCount() : 0));
   lNewOffset = (lNewOffset + (this->m_oSoftDelete.isEmpty() ? 0 : 1));
   params.setOffset(lNewOffset);

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
   lOffsetNew += (this->m_oSoftDelete.isEmpty() ? 0 : 1);
   params.setOffset(lOffsetNew);

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
   while ((p = this->nextData(l1))) { sql += (p->getSqlTablePointNameAsAlias(tableAlias) + ", "); }

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

   if (! this->m_oSoftDelete.isEmpty()) { sql += (this->m_oSoftDelete.buildSqlTablePointName(tableAlias) + ", "); }
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
   while ((p = this->nextData(l1))) { sql += (p->getSqlTablePointNameAsAlias(tableAlias) + ", "); }

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

   if (! this->m_oSoftDelete.isEmpty()) { sql += (this->m_oSoftDelete.buildSqlTablePointName(tableAlias) + ", "); }
}

void IxSqlRelation::eagerSelect_OneToMany(QxSqlRelationParams & params) const
{
   long l1(0), l2(0);
   QString & sql = params.sql();
   IxSqlRelation * pRelation = NULL;
   IxDataMember * pForeign = this->getDataByKey(this->m_sForeignKey); qAssert(pForeign);
   IxDataMember * p = NULL; IxDataMember * pId = this->getDataId(); qAssert(pId);
   QString tableAlias = this->tableAlias(params);
   if (pId) { sql += (pId->getSqlTablePointNameAsAlias(tableAlias) + ", "); }
   if (pForeign) { sql += (pForeign->getSqlTablePointNameAsAlias(tableAlias) + ", "); }
   while ((p = this->nextData(l1))) { if (p != pForeign) { sql += (p->getSqlTablePointNameAsAlias(tableAlias) + ", "); } }

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

   if (! this->m_oSoftDelete.isEmpty()) { sql += (this->m_oSoftDelete.buildSqlTablePointName(tableAlias) + ", "); }
}

void IxSqlRelation::eagerSelect_OneToOne(QxSqlRelationParams & params) const
{
   long l1(0), l2(0);
   QString & sql = params.sql();
   IxSqlRelation * pRelation = NULL;
   QString tableAlias = this->tableAlias(params);
   IxDataMember * p = NULL; IxDataMember * pId = this->getDataId(); qAssert(pId);
   if (pId) { sql += (pId->getSqlTablePointNameAsAlias(tableAlias) + ", "); }
   while ((p = this->nextData(l1))) { sql += (p->getSqlTablePointNameAsAlias(tableAlias) + ", "); }

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

   if (! this->m_oSoftDelete.isEmpty()) { sql += (this->m_oSoftDelete.buildSqlTablePointName(tableAlias) + ", "); }
}

void IxSqlRelation::eagerJoin_ManyToMany(QxSqlRelationParams & params) const
{
   QString & sql = params.sql();
   IxDataMember * pIdOwner = this->getDataIdOwner(); qAssert(pIdOwner);
   IxDataMember * pIdData = this->getDataId(); qAssert(pIdData);
   QString table = this->table(); QString tableAlias = this->tableAlias(params);
   QString tableOwner = this->tableAliasOwner(params);
   if (! pIdOwner || ! pIdData) { return; }
   QStringList lstForeignKeyOwner = m_sForeignKeyOwner.split("|");
   QStringList lstForeignKeyDataType = m_sForeignKeyDataType.split("|");
   qAssert(pIdOwner->getNameCount() == lstForeignKeyOwner.count());
   qAssert(pIdData->getNameCount() == lstForeignKeyDataType.count());
   QString sExtraTableAlias = m_sExtraTable + "_" + QString::number(params.index());
   sql += this->getSqlJoin(params.joinType()) + m_sExtraTable + " " + sExtraTableAlias + " ON ";
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
   IxDataMember * pForeign = this->getDataByKey(this->m_sForeignKey); qAssert(pForeign);
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
   if (this->m_oSoftDelete.isEmpty()) { return; }
   QString & sql = params.sql();
   QString tableAlias = this->tableAlias(params);
   sql += qx::IxSqlQueryBuilder::addSqlCondition(sql);
   sql += this->m_oSoftDelete.buildSqlQueryToFetch(tableAlias);
}

void IxSqlRelation::eagerWhereSoftDelete_ManyToOne(QxSqlRelationParams & params) const
{
   if (this->m_oSoftDelete.isEmpty()) { return; }
   QString & sql = params.sql();
   QString tableAlias = this->tableAlias(params);
   sql += qx::IxSqlQueryBuilder::addSqlCondition(sql);
   sql += this->m_oSoftDelete.buildSqlQueryToFetch(tableAlias);
}

void IxSqlRelation::eagerWhereSoftDelete_OneToMany(QxSqlRelationParams & params) const
{
   if (this->m_oSoftDelete.isEmpty()) { return; }
   QString & sql = params.sql();
   QString tableAlias = this->tableAlias(params);
   sql += qx::IxSqlQueryBuilder::addSqlCondition(sql);
   sql += this->m_oSoftDelete.buildSqlQueryToFetch(tableAlias);
}

void IxSqlRelation::eagerWhereSoftDelete_OneToOne(QxSqlRelationParams & params) const
{
   if (this->m_oSoftDelete.isEmpty()) { return; }
   QString & sql = params.sql();
   QString tableAlias = this->tableAlias(params);
   sql += qx::IxSqlQueryBuilder::addSqlCondition(sql);
   sql += this->m_oSoftDelete.buildSqlQueryToFetch(tableAlias);
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

   QString sql = "CREATE TABLE IF NOT EXISTS " + this->m_sExtraTable + " (";
   sql += pIdOwner->getSqlNameAndTypeAndParams(", ", this->m_sForeignKeyOwner) + ", "; qAssert(! pIdOwner->getSqlType().isEmpty());
   sql += pIdData->getSqlNameAndTypeAndParams(", ", this->m_sForeignKeyDataType) + ", "; qAssert(! pIdData->getSqlType().isEmpty());
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
   QString sql = "DELETE FROM " + this->m_sExtraTable + " WHERE ";
   QStringList lstForeignKeyOwner = this->m_sForeignKeyOwner.split("|");
   qAssert(pIdOwner->getNameCount() == lstForeignKeyOwner.count());
   for (int i = 0; i < pIdOwner->getNameCount(); i++)
   { sql += this->m_sExtraTable + "." + lstForeignKeyOwner.at(i) + " = " + pIdOwner->getSqlPlaceHolder("", i) + " AND "; }
   sql = sql.left(sql.count() - 5); // Remove last " AND "
   if (this->traceSqlQuery()) { qDebug("[QxOrm] sql query (extra-table) : %s", qPrintable(sql)); }

   QSqlQuery queryDelete(params.database());
   queryDelete.prepare(sql);
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
