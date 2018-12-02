/************************************************************************************************
** File created by QxEntityEditor 1.2.3 (2018/12/02 15:06) : please, do NOT modify this file ! **
************************************************************************************************/

#include "../include/KPI_precompiled_header.gen.h"

#include "../include/kpi_KPI.gen.h"
#include "../include/kpi_Type.gen.h"
#include "../include/kpi_MetaData.gen.h"

#include <QxOrm_Impl.h>

QX_REGISTER_COMPLEX_CLASS_NAME_CPP_KPI(kpi::KPI, kpi_KPI)

namespace qx {

template <>
void register_class(QxClass<kpi::KPI> & t)
{
   qx::IxDataMember * pData = NULL; Q_UNUSED(pData);
   qx::IxSqlRelation * pRelation = NULL; Q_UNUSED(pRelation);
   qx::IxFunction * pFct = NULL; Q_UNUSED(pFct);
   qx::IxValidator * pValidator = NULL; Q_UNUSED(pValidator);

   t.setName("t_KPI");

   pData = t.id(& kpi::KPI::m_KPI_id, "KPI_id", 0);

   pData = t.data(& kpi::KPI::m_Value, "Value", 0, true, true);
   pData = t.data(& kpi::KPI::m_DateTime, "DateTime", 0, true, true);

   pRelation = t.relationManyToOne(& kpi::KPI::m_Type_id, "Type_id", 0);
   pRelation = t.relationManyToMany(& kpi::KPI::m_list_of_MetaData, "list_of_MetaData", "t_qxee_KPI_MetaData", "KPI_id", "MetaData_id", 0);

   qx::QxValidatorX<kpi::KPI> * pAllValidator = t.getAllValidator(); Q_UNUSED(pAllValidator);
}

} // namespace qx

namespace kpi {

KPI::KPI() : m_KPI_id(0), m_Value(0.0) { ; }

KPI::KPI(const long & id) : m_KPI_id(id), m_Value(0.0) { ; }

KPI::~KPI() { ; }

long KPI::getKPI_id() const { return m_KPI_id; }

double KPI::getValue() const { return m_Value; }

QDateTime KPI::getDateTime() const { return m_DateTime; }

KPI::type_Type_id KPI::getType_id() const { return m_Type_id; }

KPI::type_list_of_MetaData KPI::getlist_of_MetaData() const { return m_list_of_MetaData; }

KPI::type_list_of_MetaData & KPI::list_of_MetaData() { return m_list_of_MetaData; }

const KPI::type_list_of_MetaData & KPI::list_of_MetaData() const { return m_list_of_MetaData; }

void KPI::setKPI_id(const long & val) { m_KPI_id = val; }

void KPI::setValue(const double & val) { m_Value = val; }

void KPI::setDateTime(const QDateTime & val) { m_DateTime = val; }

void KPI::setType_id(const KPI::type_Type_id & val) { m_Type_id = val; }

void KPI::setlist_of_MetaData(const KPI::type_list_of_MetaData & val) { m_list_of_MetaData = val; }

KPI::type_Type_id KPI::getType_id(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return getType_id(); }
   QString sRelation = "{KPI_id} | Type_id";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   kpi::KPI tmp;
   tmp.m_KPI_id = this->m_KPI_id;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_Type_id = tmp.m_Type_id; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_Type_id;
}

KPI::type_list_of_MetaData KPI::getlist_of_MetaData(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return getlist_of_MetaData(); }
   QString sRelation = "{KPI_id} | list_of_MetaData";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   kpi::KPI tmp;
   tmp.m_KPI_id = this->m_KPI_id;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_list_of_MetaData = tmp.m_list_of_MetaData; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_list_of_MetaData;
}

KPI::type_list_of_MetaData & KPI::list_of_MetaData(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return list_of_MetaData(); }
   QString sRelation = "{KPI_id} | list_of_MetaData";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   kpi::KPI tmp;
   tmp.m_KPI_id = this->m_KPI_id;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_list_of_MetaData = tmp.m_list_of_MetaData; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_list_of_MetaData;
}

} // namespace kpi
