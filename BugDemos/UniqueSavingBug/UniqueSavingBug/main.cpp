#include "KPI_precompiled_header.gen.h"
#include "../include/kpi_KPI.gen.h"

using namespace kpi; using namespace qx; using namespace dao;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //Create a DB
    auto name = QStringLiteral("%1/UniqueSavingBug.db3").arg(a.applicationDirPath());
    QFile::remove(name);
    QxSqlDatabase::getSingleton()->setDriverName(QStringLiteral("QSQLITE"));
    QxSqlDatabase::getSingleton()->setDatabaseName(name);
    QxSqlDatabase::getDatabase().open();
    QSqlQuery query(QxSqlDatabase::getDatabase());
    QxSqlDatabase::getDatabase().transaction();
    query.exec(QStringLiteral("CREATE TABLE t_KPI (KPI_id INTEGER NOT NULL PRIMARY KEY, "
        "Value REAL, DateTime DateTime, Type_id INTEGER, FOREIGN KEY (Type_id) REFERENCES t_Type (Type_id) "
        "ON UPDATE CASCADE ON DELETE CASCADE DEFERRABLE INITIALLY DEFERRED);"));
    query.exec(QStringLiteral("CREATE TABLE t_Type (Type_id INTEGER NOT NULL PRIMARY KEY, "
        "Name varchar NOT NULL UNIQUE, Def BLOB);"));
    query.exec(QStringLiteral("CREATE TABLE t_MetaDataKey (MetaDataKey_id INTEGER NOT NULL PRIMARY KEY, "
        "Name varchar NOT NULL UNIQUE, Type INTEGER);"));
    query.exec(QStringLiteral("CREATE TABLE t_MetaData (MetaData_id INTEGER NOT NULL PRIMARY KEY, "
        "MetaDataKey_id INTEGER NOT NULL, Value varchar, UNIQUE (MetaDataKey_id, Value), "
        "FOREIGN KEY (MetaDataKey_id) REFERENCES t_MetaDataKey (MetaDataKey_id) "
            "ON UPDATE CASCADE ON DELETE CASCADE DEFERRABLE INITIALLY DEFERRED);"));
    query.exec(QStringLiteral("CREATE TABLE t_qxee_KPI_MetaData (KPI_id INTEGER, MetaData_id INTEGER, "
        "FOREIGN KEY (KPI_id) REFERENCES t_KPI (KPI_id) "
            "ON UPDATE CASCADE ON DELETE CASCADE DEFERRABLE INITIALLY DEFERRED, "
        "FOREIGN KEY (MetaData_id) REFERENCES t_MetaData (MetaData_id) "
            "ON UPDATE CASCADE ON DELETE CASCADE DEFERRABLE INITIALLY DEFERRED);"));
    QxSqlDatabase::getDatabase().commit();
    //Add some data
    MetaDataKey_ptr k(new MetaDataKey); k->setName("name"); k->setType(1);
    list_of_MetaData m;
    for (int i = 0; i < 3; ++i) {
        m.insert(i, MetaData_ptr(new MetaData(i)));
        m.getLast()->setMetaDataKey_id(k); m.getLast()->setValue(QString::number(i));
    }
    Type_ptr t(new Type); t->setName("name"); t->setDef("def");
    QVector<KPI_ptr> v;
    for (int i = 0; i < 2; ++i) {
        v.append(KPI_ptr(new KPI));
        v.at(i)->setDateTime(QDateTime::currentDateTime());
        v.at(i)->list_of_MetaData().append(m.getLast());
        v.at(i)->setType_id(t);
        v.at(i)->setValue(i);
    }
    save(k); save(m); save(t);
    save_with_relation(KPI::relation_list_of_MetaData(), v);
    qAssert(count<KPI>() == v.size());
    //I expect in this case the fetch_all call to have no effect. The data at this point
    //has been stored in the DB, so it should be possible to delete it and then add it
    //again. And it works fine if the fetch_all call is removed, however if it is here
    //saving does not work as it violates the unique contraint.
    fetch_all_with_relation(KPI::relation_list_of_MetaData(), v);
    //Remove all items in KPI and MetaData. Alternatively create a new DB here and try
    //copying the data - this is the real use case of how I encountered the problem.
    delete_all<KPI>(); delete_all<MetaData>();
    //Now try adding them again. This does NOT work if the fetch_all call has been made.
    //The reason is that a new object representing the same MetaData is created when
    //fetch_all is executed, and so we end up having two different MetaData objects that
    //represent the same record in the DB. Without fetch_all we just have 2 pointers to the
    //same object and therefore after removing the fetch_all call saving works fine.
    save_with_relation(KPI::relation_list_of_MetaData(), v);
    qAssert(count<KPI>() == v.size());
    return 0;
}
