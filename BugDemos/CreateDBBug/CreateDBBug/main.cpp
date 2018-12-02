#include <QCoreApplication>
#include <QxOrm.h>

using namespace qx;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //Baseline what I expect to happen
    auto db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"));
    for (int i = 0; i < 2; ++i) {
        auto name = QStringLiteral("%1/Qt%2.db3").arg(a.applicationDirPath()).arg(i);
        QFile::remove(name);
        db.setDatabaseName(name);
        db.open();
        QSqlQuery query(db);
        query.exec(QStringLiteral("CREATE TABLE t (id INTEGER);"));
        qDebug() << "err" << query.lastError();
        qAssert(!query.lastError().isValid());
        db.close();
        qAssert(QFile::exists(name));
    }

    //Now try the same with QxOrm
    QxSqlDatabase::getSingleton()->setDriverName(QStringLiteral("QSQLITE"));
    //Two setDatabaseName calls make it work
    for (int i = 0; i < 2; ++i) {
        auto name = QStringLiteral("%1/QxOK%2.db3").arg(a.applicationDirPath()).arg(i);
        QFile::remove(name);
        QxSqlDatabase::getSingleton()->setDatabaseName(name);
        QxSqlDatabase::getDatabase().setDatabaseName(name);
        QxSqlDatabase::getDatabase().open();
        QSqlQuery query(QxSqlDatabase::getDatabase());
        query.exec(QStringLiteral("CREATE TABLE t (id INTEGER);"));
        qDebug() << "err" << query.lastError();
        qAssert(!query.lastError().isValid());
        QxSqlDatabase::getDatabase().close();
        qAssert(QFile::exists(name));
    }
    QxSqlDatabase::getSingleton()->clearAllDatabases();

    //However, take either of the setDatabaseName calls out and it breaks
    QxSqlDatabase::getSingleton()->setDriverName(QStringLiteral("QSQLITE"));
    //Alternatively this could be used as a workaround, but it creates an empty file
//    QxSqlDatabase::getSingleton()->setDatabaseName(QStringLiteral("%1/dummy.db3")
//                                                   .arg(a.applicationDirPath()));
    for (int i = 0; i < 2; ++i) {
        auto name = QStringLiteral("%1/QxBad%2.db3").arg(a.applicationDirPath()).arg(i);
        QFile::remove(name);
        QxSqlDatabase::getSingleton()->setDatabaseName(name);
        //QxSqlDatabase::getDatabase().setDatabaseName(name);
        //This assert fails and is the reason for the following asserts failing
//        qAssert(QxSqlDatabase::getSingleton()->getDatabaseName() ==
//                QxSqlDatabase::getDatabase().databaseName());
        QxSqlDatabase::getDatabase().open();
        QSqlQuery query(QxSqlDatabase::getDatabase());
        query.exec(QStringLiteral("CREATE TABLE t (id INTEGER);"));
        qDebug() << "err" << query.lastError(); //if (i == 1) has error
        //qAssert(!query.lastError().isValid()); //if (i == 1) fails
        QxSqlDatabase::getDatabase().close();
        qAssert(QFile::exists(name));
    }
    return a.exec();
}
