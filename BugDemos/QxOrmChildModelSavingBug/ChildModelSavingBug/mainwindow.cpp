#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../include/Grandchild.model_view.gen.h"

using namespace qx;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), m_mp(nullptr), m_mc(nullptr),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QxSqlDatabase::getSingleton()->setDriverName(QStringLiteral("QSQLITE"));
    QFile::remove(qApp->applicationDirPath() + "/ChildModelSavingBug.db3");
    QxSqlDatabase::getSingleton()->setDatabaseName(
                qApp->applicationDirPath() + "/ChildModelSavingBug.db3");
    QxSqlDatabase::getDatabase().open();
    QSqlQuery query(QxSqlDatabase::getDatabase());
    query.exec(QStringLiteral("CREATE TABLE t_Parent ("
          "Parent_id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, Name TEXT);"));
    query.exec(QStringLiteral("CREATE TABLE t_Child ("
           "Child_id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, Name TEXT, "
           "parent INTEGER, FOREIGN KEY (parent) REFERENCES t_Parent (Parent_id));"));
    query.exec(QStringLiteral("CREATE TABLE t_Grandchild ("
           "Grandchild_id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, Name TEXT, "
           "parent INTEGER, FOREIGN KEY (parent) REFERENCES t_Child (Child_id));"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Create()
{
    //Create a new item in table parent
    Parent_ptr p(new Parent);
    p->setName(QDateTime::currentDateTime().toString(Qt::ISODateWithMs));
    dao::save(p);
    //Load parent model from db
    delete m_mp; m_mp = new Parent_model;
    m_mp->qxFetchAll();
    //create a nested child model for the last item in table parent
    m_mc = static_cast<Child_model*>(m_mp->list_of_Child(m_mp->rowCount() - 1, true));
    //create a new child item and put it in the nested model
    Child_ptr c(new Child);
    p = static_cast<list_of_Parent*>(m_mp->getCollection())->getLast();
    c->setName(p->getName());
    c->setparent(p);
    //create a grandchild item and add it to the child item just created
    Grandchild_ptr gc(new Grandchild);
    gc->setName(p->getName());
    gc->setparent(c);
    c->list_of_Grandchild().insert(0, gc);
    static_cast<list_of_Child*>(m_mc->getCollection())->push_back(0, c);
}

void MainWindow::on_bDoesNotWork_clicked()
{
    Create();
    //save to db - does not save the grandchild item
    m_mp->qxSaveRow(m_mp->rowCount() - 1, QStringList() <<
       Parent::relation_list_of_Child() + "->" + Child::relation_list_of_Grandchild());
    Res();
}

void MainWindow::on_bWorks_clicked()
{
    Create();
    //save to db - saves the grandchild item as it should
    m_mc->qxSave(QStringList() << Child::relation_list_of_Grandchild());
    Res();
}

void MainWindow::Res()
{
    //display the number of grandchild items just added
    m_mc = static_cast<Child_model*>(m_mp->list_of_Child(m_mp->rowCount() - 1, true));
    ui->lRes->setText(tr("New grandchildren: %1").arg(
       static_cast<Grandchild_model*>(m_mc->list_of_Grandchild(0, true))->rowCount()));
}
