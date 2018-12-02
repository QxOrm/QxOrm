/************************************************************************************************
** File created by QxEntityEditor 1.2.3 (2018/12/02 15:06) : please, do NOT modify this file ! **
************************************************************************************************/

#ifndef _KPI_KPI_METADATAKEY_H_
#define _KPI_KPI_METADATAKEY_H_

namespace kpi {
class MetaData;
} // namespace kpi

namespace kpi {

class KPI_EXPORT MetaDataKey
{

   QX_REGISTER_FRIEND_CLASS(kpi::MetaDataKey)

public:

   typedef QVector<std::shared_ptr<kpi::MetaData> > type_list_of_MetaData;

protected:

   long m_MetaDataKey_id;
   QString m_Name;
   int m_Type;
   type_list_of_MetaData m_list_of_MetaData;

public:

   MetaDataKey();
   MetaDataKey(const long & id);
   virtual ~MetaDataKey();

   long getMetaDataKey_id() const;
   QString getName() const;
   int getType() const;
   type_list_of_MetaData getlist_of_MetaData() const;
   type_list_of_MetaData & list_of_MetaData();
   const type_list_of_MetaData & list_of_MetaData() const;

   void setMetaDataKey_id(const long & val);
   void setName(const QString & val);
   void setType(const int & val);
   void setlist_of_MetaData(const type_list_of_MetaData & val);

   type_list_of_MetaData getlist_of_MetaData(bool bLoadFromDatabase, const QString & sAppendRelations = QString(), QSqlDatabase * pDatabase = NULL, QSqlError * pDaoError = NULL);
   type_list_of_MetaData & list_of_MetaData(bool bLoadFromDatabase, const QString & sAppendRelations = QString(), QSqlDatabase * pDatabase = NULL, QSqlError * pDaoError = NULL);

public:

   static QString relation_list_of_MetaData(bool key = false) { Q_UNUSED(key); return "list_of_MetaData"; }

public:

   static QString column_MetaDataKey_id(bool key = false) { Q_UNUSED(key); return "MetaDataKey_id"; }
   static QString column_Name(bool key = false) { Q_UNUSED(key); return "Name"; }
   static QString column_Type(bool key = false) { Q_UNUSED(key); return "Type"; }

public:

   static QString table_name(bool key = false) { return (key ? QString("MetaDataKey") : QString("t_MetaDataKey")); }

};

typedef std::shared_ptr<MetaDataKey> MetaDataKey_ptr;
typedef qx::QxCollection<long, MetaDataKey_ptr> list_of_MetaDataKey;
typedef std::shared_ptr<list_of_MetaDataKey> list_of_MetaDataKey_ptr;

} // namespace kpi

QX_REGISTER_COMPLEX_CLASS_NAME_HPP_KPI(kpi::MetaDataKey, qx::trait::no_base_class_defined, 0, kpi_MetaDataKey)

#include "../include/kpi_MetaData.gen.h"

#include "../custom/include/kpi_MetaDataKey.h"

#endif // _KPI_KPI_METADATAKEY_H_
