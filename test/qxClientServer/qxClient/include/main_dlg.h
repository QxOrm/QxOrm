#ifndef _QX_CLIENT_MAIN_DLG_H_
#define _QX_CLIENT_MAIN_DLG_H_

#include "../qt/ui/include/ui_qxClient.h"

#include "../../qxService/include/business_object/user.h"
#include "../../qxService/include/business_object/user_search.h"

class main_dlg : public QWidget, private Ui::dlgClient
{ Q_OBJECT

private:

   qx::service::QxClientAsync_ptr m_pDateTimeAsync;   // To retrieve current server date-time without blocking GUI (async transaction)

public:

   main_dlg(QWidget * parent = NULL) : QWidget(parent), Ui::dlgClient() { main_dlg::init(); }
   virtual ~main_dlg() { ; }

private:

   void init();
   void updateLastTransactionLog(qx::service::QxTransaction_ptr transaction);
   void fillUser(user_ptr user);
   user_ptr fileUser();

private Q_SLOTS:

   void onClickBtnDateTime();
   void onClickBtnDateTimeAsync();
   void onClickBtnAddUser();
   void onClickBtnUpdateUser();
   void onClickBtnRemoveUser();
   void onClickBtnRemoveAllUsers();
   void onClickBtnFetchUser();
   void onClickBtnGetAllUsers();
   void onClickBtnSearchUsers();
   void onDateTimeAsyncFinished();
   void onUpdateServerConnection();

};

#endif // _QX_CLIENT_MAIN_DLG_H_
