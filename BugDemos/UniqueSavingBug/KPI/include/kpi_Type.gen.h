/************************************************************************************************
** File created by QxEntityEditor 1.2.3 (2018/12/02 15:06) : please, do NOT modify this file ! **
************************************************************************************************/

#ifndef _KPI_KPI_TYPE_H_
#define _KPI_KPI_TYPE_H_

namespace kpi {
class KPI;
} // namespace kpi

namespace kpi {

class KPI_EXPORT Type
{

   QX_REGISTER_FRIEND_CLASS(kpi::Type)

public:

   typedef qx::QxCollection<long, std::shared_ptr<kpi::KPI> > type_list_of_KPI;

protected:

   long m_Type_id;
   QString m_Name;
   QByteArray m_Def;
   type_list_of_KPI m_list_of_KPI;

public:

   Type();
   Type(const long & id);
   virtual ~Type();

   long getType_id() const;
   QString getName() const;
   QByteArray getDef() const;
   type_list_of_KPI getlist_of_KPI() const;
   type_list_of_KPI & list_of_KPI();
   const type_list_of_KPI & list_of_KPI() const;

   void setType_id(const long & val);
   void setName(const QString & val);
   void setDef(const QByteArray & val);
   void setlist_of_KPI(const type_list_of_KPI & val);

   type_list_of_KPI getlist_of_KPI(bool bLoadFromDatabase, const QString & sAppendRelations = QString(), QSqlDatabase * pDatabase = NULL, QSqlError * pDaoError = NULL);
   type_list_of_KPI & list_of_KPI(bool bLoadFromDatabase, const QString & sAppendRelations = QString(), QSqlDatabase * pDatabase = NULL, QSqlError * pDaoError = NULL);

public:

   static QString relation_list_of_KPI(bool key = false) { Q_UNUSED(key); return "list_of_KPI"; }

public:

   static QString column_Type_id(bool key = false) { Q_UNUSED(key); return "Type_id"; }
   static QString column_Name(bool key = false) { Q_UNUSED(key); return "Name"; }
   static QString column_Def(bool key = false) { Q_UNUSED(key); return "Def"; }

public:

   static QString table_name(bool key = false) { return (key ? QString("Type") : QString("t_Type")); }

};

typedef std::shared_ptr<Type> Type_ptr;
typedef qx::QxCollection<long, Type_ptr> list_of_Type;
typedef std::shared_ptr<list_of_Type> list_of_Type_ptr;

} // namespace kpi

QX_REGISTER_COMPLEX_CLASS_NAME_HPP_KPI(kpi::Type, qx::trait::no_base_class_defined, 0, kpi_Type)

#include "../include/kpi_KPI.gen.h"

#include "../custom/include/kpi_Type.h"

#endif // _KPI_KPI_TYPE_H_
