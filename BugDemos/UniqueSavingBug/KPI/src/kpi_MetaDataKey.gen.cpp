/************************************************************************************************
** File created by QxEntityEditor 1.2.3 (2018/12/02 15:06) : please, do NOT modify this file ! **
************************************************************************************************/

#include "../include/KPI_precompiled_header.gen.h"

#include "../include/kpi_MetaDataKey.gen.h"
#include "../include/kpi_MetaData.gen.h"

#include <QxOrm_Impl.h>

QX_REGISTER_COMPLEX_CLASS_NAME_CPP_KPI(kpi::MetaDataKey, kpi_MetaDataKey)

namespace qx {

template <>
void register_class(QxClass<kpi::MetaDataKey> & t)
{
   qx::IxDataMember * pData = NULL; Q_UNUSED(pData);
   qx::IxSqlRelation * pRelation = NULL; Q_UNUSED(pRelation);
   qx::IxFunction * pFct = NULL; Q_UNUSED(pFct);
   qx::IxValidator * pValidator = NULL; Q_UNUSED(pValidator);

   t.setName("t_MetaDataKey");

   pData = t.id(& kpi::MetaDataKey::m_MetaDataKey_id, "MetaDataKey_id", 0);

   pData = t.data(& kpi::MetaDataKey::m_Name, "Name", 0, true, true);
   pData->setIsUnique(true);
   pData = t.data(& kpi::MetaDataKey::m_Type, "Type", 0, true, true);

   pRelation = t.relationOneToMany(& kpi::MetaDataKey::m_list_of_MetaData, "list_of_MetaData", "MetaDataKey_id", 0);

   qx::QxValidatorX<kpi::MetaDataKey> * pAllValidator = t.getAllValidator(); Q_UNUSED(pAllValidator);
   pAllValidator->add_NotNull("Name");
}

} // namespace qx

namespace kpi {

MetaDataKey::MetaDataKey() : m_MetaDataKey_id(0), m_Type(0) { ; }

MetaDataKey::MetaDataKey(const long & id) : m_MetaDataKey_id(id), m_Type(0) { ; }

MetaDataKey::~MetaDataKey() { ; }

long MetaDataKey::getMetaDataKey_id() const { return m_MetaDataKey_id; }

QString MetaDataKey::getName() const { return m_Name; }

int MetaDataKey::getType() const { return m_Type; }

MetaDataKey::type_list_of_MetaData MetaDataKey::getlist_of_MetaData() const { return m_list_of_MetaData; }

MetaDataKey::type_list_of_MetaData & MetaDataKey::list_of_MetaData() { return m_list_of_MetaData; }

const MetaDataKey::type_list_of_MetaData & MetaDataKey::list_of_MetaData() const { return m_list_of_MetaData; }

void MetaDataKey::setMetaDataKey_id(const long & val) { m_MetaDataKey_id = val; }

void MetaDataKey::setName(const QString & val) { m_Name = val; }

void MetaDataKey::setType(const int & val) { m_Type = val; }

void MetaDataKey::setlist_of_MetaData(const MetaDataKey::type_list_of_MetaData & val) { m_list_of_MetaData = val; }

MetaDataKey::type_list_of_MetaData MetaDataKey::getlist_of_MetaData(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return getlist_of_MetaData(); }
   QString sRelation = "{MetaDataKey_id} | list_of_MetaData";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   kpi::MetaDataKey tmp;
   tmp.m_MetaDataKey_id = this->m_MetaDataKey_id;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_list_of_MetaData = tmp.m_list_of_MetaData; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_list_of_MetaData;
}

MetaDataKey::type_list_of_MetaData & MetaDataKey::list_of_MetaData(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return list_of_MetaData(); }
   QString sRelation = "{MetaDataKey_id} | list_of_MetaData";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   kpi::MetaDataKey tmp;
   tmp.m_MetaDataKey_id = this->m_MetaDataKey_id;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_list_of_MetaData = tmp.m_list_of_MetaData; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_list_of_MetaData;
}

} // namespace kpi
