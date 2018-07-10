#ifndef _QX_SERVER_MAIN_DLG_H_
#define _QX_SERVER_MAIN_DLG_H_

#include "../qt/ui/include/ui_qxServer.h"

class main_dlg : public QWidget, private Ui::dlgServer
{ Q_OBJECT

private:

   qx::service::QxThreadPool_ptr m_pThreadPool; // Server thread pool to receive all requests

public:

   main_dlg(QWidget * parent = NULL) : QWidget(parent), Ui::dlgServer() { main_dlg::init(); }
   virtual ~main_dlg() { ; }

private:

   void init();
   void loadServices();

private Q_SLOTS:

   void onClickStartStop();
   void onCboIndexChanged(int index);
   void onError(const QString & err, qx::service::QxTransaction_ptr transaction);
   void onServerIsRunning(bool bIsRunning, qx::service::QxServer * pServer);
   void onTransactionFinished(qx::service::QxTransaction_ptr transaction);

};

#endif // _QX_SERVER_MAIN_DLG_H_
