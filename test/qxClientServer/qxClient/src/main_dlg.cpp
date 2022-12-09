#include "../include/precompiled.h"

#include <QtGui/qcursor.h>

#if (QT_VERSION >= 0x050000)
#include <QtWidgets/qmessagebox.h>
#else // (QT_VERSION >= 0x050000)
#include <QtGui/qmessagebox.h>
#endif // (QT_VERSION >= 0x050000)

#include "../include/main_dlg.h"

#include "../../qxService/include/service/server_infos.h"
#include "../../qxService/include/service/user_service.h"

#include <QxOrm_Impl.h>

#define QX_CLIENT_BIRTHDATE_QDATETIME_FORMAT "dd/MM/yyyy"

void main_dlg::init()
{
   setupUi(this);

   QObject::connect(btnDateTime, SIGNAL(clicked()), this, SLOT(onClickBtnDateTime()));
   QObject::connect(btnDateTime_Async, SIGNAL(clicked()), this, SLOT(onClickBtnDateTimeAsync()));
   QObject::connect(btnAddUser, SIGNAL(clicked()), this, SLOT(onClickBtnAddUser()));
   QObject::connect(btnUpdateUser, SIGNAL(clicked()), this, SLOT(onClickBtnUpdateUser()));
   QObject::connect(btnRemoveUser, SIGNAL(clicked()), this, SLOT(onClickBtnRemoveUser()));
   QObject::connect(btnRemoveAllUser, SIGNAL(clicked()), this, SLOT(onClickBtnRemoveAllUsers()));
   QObject::connect(btnFetchUser, SIGNAL(clicked()), this, SLOT(onClickBtnFetchUser()));
   QObject::connect(btnGetAllUser, SIGNAL(clicked()), this, SLOT(onClickBtnGetAllUsers()));
   QObject::connect(btnSearchUser, SIGNAL(clicked()), this, SLOT(onClickBtnSearchUsers()));
   QObject::connect(txtIp, SIGNAL(editingFinished()), this, SLOT(onUpdateServerConnection()));
   QObject::connect(spinPort, SIGNAL(editingFinished()), this, SLOT(onUpdateServerConnection()));

   txtBirthDate->setText(QX_CLIENT_BIRTHDATE_QDATETIME_FORMAT);
   txtBirthDate->setToolTip(QString("Birthdate : ") + QX_CLIENT_BIRTHDATE_QDATETIME_FORMAT);
   txtIp->setText("127.0.0.1");
   spinPort->setValue(7694);
   onUpdateServerConnection();
}

void main_dlg::updateLastTransactionLog(qx::service::QxTransaction_ptr transaction)
{
   if (! transaction) { txtTransaction->setPlainText(""); return; }
#ifdef _QX_ENABLE_BOOST_SERIALIZATION_XML
   QString text = qx::serialization::xml::to_string(* transaction);
#else // _QX_ENABLE_BOOST_SERIALIZATION_XML
   QString text = transaction->getInfos();
#endif // _QX_ENABLE_BOOST_SERIALIZATION_XML
   txtTransaction->setPlainText(text.replace("\t", "    "));
   qx_bool bMsgReturn = transaction->getMessageReturn();
   if (! bMsgReturn.getValue() && ! bMsgReturn.getDesc().isEmpty())
   { QMessageBox::warning(this, "qxClient - transaction error", bMsgReturn.getDesc()); }
}

void main_dlg::fillUser(user_ptr user)
{
   if (! user) { return; }
   txtId->setText(QString::number(user->id));
   txtFirstName->setText(user->first_name);
   txtLastName->setText(user->last_name);
   txtBirthDate->setText(user->birth_date.toString(QX_CLIENT_BIRTHDATE_QDATETIME_FORMAT));
}

user_ptr main_dlg::fileUser()
{
   user_ptr user_to_file = user_ptr(new user());
   user_to_file->id = txtId->text().toLong();
   user_to_file->first_name = txtFirstName->text();
   user_to_file->last_name = txtLastName->text();
   user_to_file->birth_date = QDateTime::fromString(txtBirthDate->text(), QX_CLIENT_BIRTHDATE_QDATETIME_FORMAT);
   return user_to_file;
}

void main_dlg::onUpdateServerConnection()
{
   qx::service::QxConnect::getSingleton()->setIp(txtIp->text());
   qx::service::QxConnect::getSingleton()->setPort(spinPort->value());
}

void main_dlg::onClickBtnDateTime()
{
   QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
   // Create service and call method to retrieve current server date-time
   server_infos service;
   service.get_current_date_time();
   // Update transaction log
   updateLastTransactionLog(service.getTransaction());
   QApplication::restoreOverrideCursor();
}

void main_dlg::onClickBtnDateTimeAsync()
{
   if (m_pDateTimeAsync) { qDebug("[QxOrm] '%s' transaction is already running", "server_infos::get_current_date_time"); return; }
   // Create service and call method to retrieve current server date-time (async mode)
   server_infos_ptr service = server_infos_ptr(new server_infos());
   m_pDateTimeAsync.reset(new qx::service::QxClientAsync());
   QObject::connect(m_pDateTimeAsync.get(), SIGNAL(finished()), this, SLOT(onDateTimeAsyncFinished()));
   m_pDateTimeAsync->setService(service, "get_current_date_time");
   m_pDateTimeAsync->start();
}

void main_dlg::onDateTimeAsyncFinished()
{
   if (! m_pDateTimeAsync || ! m_pDateTimeAsync->getService()) { return; }
   updateLastTransactionLog(m_pDateTimeAsync->getService()->getTransaction());
   m_pDateTimeAsync.reset();
}

void main_dlg::onClickBtnAddUser()
{
   QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
   // Create input parameters with user to add
   user_service_input_ptr input = user_service_input_ptr(new user_service_input());
   input->user = fileUser();
   // Create service to call and set input parameters
   user_service service;
   service.setInputParameter(input);
   service.insert();
   // If transaction is ok => display user with new id added to database
   user_ptr output = (service.isValidWithOutput() ? service.getOutputParameter()->user : user_ptr());
   if (output) { fillUser(output); }
   // Update transaction log
   updateLastTransactionLog(service.getTransaction());
   QApplication::restoreOverrideCursor();
}

void main_dlg::onClickBtnUpdateUser()
{
   QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
   // Create input parameters with user to update
   user_service_input_ptr input = user_service_input_ptr(new user_service_input());
   input->user = fileUser();
   // Create service to call and set input parameters
   user_service service;
   service.setInputParameter(input);
   service.update();
   // Update transaction log
   updateLastTransactionLog(service.getTransaction());
   QApplication::restoreOverrideCursor();
}

void main_dlg::onClickBtnRemoveUser()
{
   QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
   // Create input parameters with user id to remove
   user_service_input_ptr input = user_service_input_ptr(new user_service_input());
   input->id = txtId->text().toLong();
   // Create service to call and set input parameters
   user_service service;
   service.setInputParameter(input);
   service.remove();
   // Update transaction log
   updateLastTransactionLog(service.getTransaction());
   QApplication::restoreOverrideCursor();
}

void main_dlg::onClickBtnRemoveAllUsers()
{
   QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
   // Create service to call
   user_service service;
   service.remove_all();
   // Update transaction log
   updateLastTransactionLog(service.getTransaction());
   QApplication::restoreOverrideCursor();
}

void main_dlg::onClickBtnFetchUser()
{
   QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
   // Create input parameters with user id to fetch
   user_service_input_ptr input = user_service_input_ptr(new user_service_input());
   input->id = txtId->text().toLong();
   // Create service to call and set input parameters
   user_service service;
   service.setInputParameter(input);
   service.fetch_by_id();
   // If transaction is ok => display user fetched on GUI
   user_ptr output = (service.isValidWithOutput() ? service.getOutputParameter()->user : user_ptr());
   if (output) { fillUser(output); }
   // Update transaction log
   updateLastTransactionLog(service.getTransaction());
   QApplication::restoreOverrideCursor();
}

void main_dlg::onClickBtnGetAllUsers()
{
   QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
   // Create service to call
   user_service service;
   service.fetch_all();
   // If transaction is ok => display in a message box the number of users fetched from database
   list_of_users_ptr output = (service.isValidWithOutput() ? service.getOutputParameter()->list_of_users : list_of_users_ptr());
   if (output) { QMessageBox::information(this, "qxClient - get all users", "database contains '" + QString::number(output->size()) + "' user(s)."); }
   // Update transaction log
   updateLastTransactionLog(service.getTransaction());
   QApplication::restoreOverrideCursor();
}

void main_dlg::onClickBtnSearchUsers()
{
   QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
   // Create criteria to search users
   user_search_ptr criteria = user_search_ptr(new user_search());
   criteria->first_name = txtFirstName->text();
   criteria->last_name = txtLastName->text();
   criteria->birth_date = QDateTime::fromString(txtBirthDate->text(), QX_CLIENT_BIRTHDATE_QDATETIME_FORMAT);
   // Create input parameters with criteria to search users
   user_service_input_ptr input = user_service_input_ptr(new user_service_input());
   input->criteria = criteria;
   // Create service to call and set input parameters
   user_service service;
   service.setInputParameter(input);
   service.get_by_criteria();
   // If transaction is ok => display in a message box the number of users fetched from database
   list_of_users_ptr output = (service.isValidWithOutput() ? service.getOutputParameter()->list_of_users : list_of_users_ptr());
   if (output) { QMessageBox::information(this, "qxClient - search users", "database contains '" + QString::number(output->size()) + "' user(s) with input criteria."); }
   // Update transaction log
   updateLastTransactionLog(service.getTransaction());
   QApplication::restoreOverrideCursor();
}
