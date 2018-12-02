/************************************************************************************************
** File created by QxEntityEditor 1.2.3 (2018/12/02 15:06) : please, do NOT modify this file ! **
************************************************************************************************/

#include "../include/KPI_precompiled_header.gen.h"

#include "../include/kpi_Type.gen.h"
#include "../include/kpi_KPI.gen.h"

#include <QxOrm_Impl.h>

QX_REGISTER_COMPLEX_CLASS_NAME_CPP_KPI(kpi::Type, kpi_Type)

namespace qx {

template <>
void register_class(QxClass<kpi::Type> & t)
{
   qx::IxDataMember * pData = NULL; Q_UNUSED(pData);
   qx::IxSqlRelation * pRelation = NULL; Q_UNUSED(pRelation);
   qx::IxFunction * pFct = NULL; Q_UNUSED(pFct);
   qx::IxValidator * pValidator = NULL; Q_UNUSED(pValidator);

   t.setName("t_Type");

   pData = t.id(& kpi::Type::m_Type_id, "Type_id", 0);

   pData = t.data(& kpi::Type::m_Name, "Name", 0, true, true);
   pData = t.data(& kpi::Type::m_Def, "Def", 0, true, true);

   pRelation = t.relationOneToMany(& kpi::Type::m_list_of_KPI, "list_of_KPI", "Type_id", 0);

   qx::QxValidatorX<kpi::Type> * pAllValidator = t.getAllValidator(); Q_UNUSED(pAllValidator);
}

} // namespace qx

namespace kpi {

Type::Type() : m_Type_id(0) { ; }

Type::Type(const long & id) : m_Type_id(id) { ; }

Type::~Type() { ; }

long Type::getType_id() const { return m_Type_id; }

QString Type::getName() const { return m_Name; }

QByteArray Type::getDef() const { return m_Def; }

Type::type_list_of_KPI Type::getlist_of_KPI() const { return m_list_of_KPI; }

Type::type_list_of_KPI & Type::list_of_KPI() { return m_list_of_KPI; }

const Type::type_list_of_KPI & Type::list_of_KPI() const { return m_list_of_KPI; }

void Type::setType_id(const long & val) { m_Type_id = val; }

void Type::setName(const QString & val) { m_Name = val; }

void Type::setDef(const QByteArray & val) { m_Def = val; }

void Type::setlist_of_KPI(const Type::type_list_of_KPI & val) { m_list_of_KPI = val; }

Type::type_list_of_KPI Type::getlist_of_KPI(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return getlist_of_KPI(); }
   QString sRelation = "{Type_id} | list_of_KPI";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   kpi::Type tmp;
   tmp.m_Type_id = this->m_Type_id;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_list_of_KPI = tmp.m_list_of_KPI; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_list_of_KPI;
}

Type::type_list_of_KPI & Type::list_of_KPI(bool bLoadFromDatabase, const QString & sAppendRelations /* = QString() */, QSqlDatabase * pDatabase /* = NULL */, QSqlError * pDaoError /* = NULL */)
{
   if (pDaoError) { (* pDaoError) = QSqlError(); }
   if (! bLoadFromDatabase) { return list_of_KPI(); }
   QString sRelation = "{Type_id} | list_of_KPI";
   if (! sAppendRelations.isEmpty() && ! sAppendRelations.startsWith("->") && ! sAppendRelations.startsWith(">>")) { sRelation += "->" + sAppendRelations; }
   else if (! sAppendRelations.isEmpty()) { sRelation += sAppendRelations; }
   kpi::Type tmp;
   tmp.m_Type_id = this->m_Type_id;
   QSqlError daoError = qx::dao::fetch_by_id_with_relation(sRelation, tmp, pDatabase);
   if (! daoError.isValid()) { this->m_list_of_KPI = tmp.m_list_of_KPI; }
   if (pDaoError) { (* pDaoError) = daoError; }
   return m_list_of_KPI;
}

} // namespace kpi
