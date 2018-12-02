#include "KPI_precompiled_header.gen.h"
#include "../include/kpi_KPI.gen.h"
#include <QElapsedTimer>

using namespace kpi; using namespace qx; using namespace dao;

QVector<KPI_ptr> CreateDB(QString name)
{
    name = QStringLiteral("%1/%2.db3").arg(qApp->applicationDirPath(), name);
    QFile::remove(name);
    QxSqlDatabase::getSingleton()->setDatabaseName(name);
    QxSqlDatabase::getDatabase().setDatabaseName(name);
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
    MetaDataKey_ptr k(new MetaDataKey); k->setName("name"); k->setType(1); insert(k);
    QVector<MetaData_ptr> vm(99);
    for (int i = 0; i < vm.size(); ++i) {
        vm[i].reset(new MetaData);
        vm.at(i)->setMetaDataKey_id(k); vm.at(i)->setValue(QString::number(i));
    }
    Type_ptr t(new Type); t->setName("name"); t->setDef("def"); insert(t);
    QVector<KPI_ptr> vk(99);
    for (int i = 0; i < vk.size(); ++i) {
        vk[i].reset(new KPI);
        vk.at(i)->setDateTime(QDateTime::currentDateTime());
        vk.at(i)->setlist_of_MetaData(vm);
        vk.at(i)->setType_id(t);
        vk.at(i)->setValue(i);
    }
    return vk;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QxSqlDatabase::getSingleton()->setTraceSqlQuery(false);
    QxSqlDatabase::getSingleton()->setDriverName(QStringLiteral("QSQLITE"));
    //Measure time
    //1. Simple insert_with_relation call
    auto vk = CreateDB(QStringLiteral("InsertWithRelation"));
    QElapsedTimer timer; timer.start();
    insert_with_relation(KPI::relation_list_of_MetaData(), vk);
    auto nInsert = timer.elapsed();

    //2. QxSession insert
    vk = CreateDB(QStringLiteral("SessionInsert"));
    timer.start();
    { QxSession s; s.insert(vk, QStringList() << KPI::relation_list_of_MetaData()); }
    auto nSessionInsert = timer.elapsed();

    //3. Quicker implementation of insert_with_relation
    vk = CreateDB(QStringLiteral("ProposedImplementation"));
    timer.start();
    //Get all unique MetaData_ptr from vk and save them explicitly
    QHash<MetaData*, MetaData_ptr> hm;
    for (const auto& k : vk) for (const auto& m : k->list_of_MetaData()) hm[m.get()] = m;
    { QxSession s; s.insert(vk); s.insert(hm); }

    //Now get the ids
    QVariantList lk, lm;
    for (const auto& k : vk) for (const auto& m : k->list_of_MetaData())
        { lk.append(k->getKPI_id()); lm.append(m->getMetaData_id()); }

    //Put them in the join table
    QSqlQuery query(QxSqlDatabase::getDatabase());
    query.prepare(QStringLiteral(
            "INSERT INTO t_qxee_KPI_MetaData (KPI_id, MetaData_id) VALUES (?, ?);"));
    query.addBindValue(lk); query.addBindValue(lm);
    bool b = QxSqlDatabase::getDatabase().transaction() && query.execBatch() &&
        QxSqlDatabase::getDatabase().commit();
    qAssert(b);

    qDebug() << "1. InsertWithRelation" << nInsert;
    qDebug() << "2. SessionInsert" << nSessionInsert;
    qDebug() << "3. ProposedImplementation" << timer.elapsed();
    return a.exec();
}
