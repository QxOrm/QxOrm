#ifndef _QX_SERVER_MAIN_DLG_H_
#define _QX_SERVER_MAIN_DLG_H_

#include "../qt/ui/include/ui_qxServer.h"

class main_dlg : public QWidget, private Ui::dlgServer
{ Q_OBJECT

private:

   qx::service::QxThreadPool_ptr m_pThreadPool; // Server thread pool to receive all requests
   qx::QxDaoAsync m_daoAsync;                   // To test to run queries in a different thread

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
   void onQueryFinished(const QSqlError & daoError, qx::dao::detail::QxDaoAsyncParams_ptr pDaoParams);

};

#endif // _QX_SERVER_MAIN_DLG_H_
