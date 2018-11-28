#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ChildModelSavingBug_precompiled_header.model_view.gen.h"
#include "Parent.model_view.gen.h"
#include "Child.model_view.gen.h"

namespace Ui {
class MainWindow;
}

using namespace model_view;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_bWorks_clicked();
    void on_bDoesNotWork_clicked();

private:
    Ui::MainWindow *ui;
    Parent_model* m_mp;
    Child_model* m_mc;

    void Create();
    void Res();
};

#endif // MAINWINDOW_H
