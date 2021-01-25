/********************************************************************************
** Form generated from reading UI file 'qxClient.ui'
**
** Created by: Qt User Interface Compiler version 6.0.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QXCLIENT_H
#define UI_QXCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dlgClient
{
public:
    QGroupBox *grpServerInfos;
    QPushButton *btnDateTime;
    QPushButton *btnDateTime_Async;
    QGroupBox *grpTransaction;
    QPlainTextEdit *txtTransaction;
    QGroupBox *grpUser;
    QPushButton *btnGetAllUser;
    QPushButton *btnAddUser;
    QPushButton *btnUpdateUser;
    QPushButton *btnRemoveUser;
    QPushButton *btnRemoveAllUser;
    QPushButton *btnFetchUser;
    QFrame *lineUser;
    QLabel *lblId;
    QLabel *lblFirstName;
    QLabel *lblLastName;
    QLabel *lblBirthDate;
    QLineEdit *txtId;
    QLineEdit *txtFirstName;
    QLineEdit *txtLastName;
    QLineEdit *txtBirthDate;
    QPushButton *btnSearchUser;
    QGroupBox *grpServerConnection;
    QLabel *lblIp;
    QLabel *lblPort;
    QSpinBox *spinPort;
    QLineEdit *txtIp;

    void setupUi(QWidget *dlgClient)
    {
        if (dlgClient->objectName().isEmpty())
            dlgClient->setObjectName(QString::fromUtf8("dlgClient"));
        dlgClient->resize(541, 371);
        dlgClient->setMinimumSize(QSize(541, 371));
        dlgClient->setMaximumSize(QSize(541, 371));
        grpServerInfos = new QGroupBox(dlgClient);
        grpServerInfos->setObjectName(QString::fromUtf8("grpServerInfos"));
        grpServerInfos->setGeometry(QRect(230, 10, 301, 51));
        btnDateTime = new QPushButton(grpServerInfos);
        btnDateTime->setObjectName(QString::fromUtf8("btnDateTime"));
        btnDateTime->setGeometry(QRect(10, 20, 121, 23));
        btnDateTime_Async = new QPushButton(grpServerInfos);
        btnDateTime_Async->setObjectName(QString::fromUtf8("btnDateTime_Async"));
        btnDateTime_Async->setGeometry(QRect(140, 20, 151, 23));
        grpTransaction = new QGroupBox(dlgClient);
        grpTransaction->setObjectName(QString::fromUtf8("grpTransaction"));
        grpTransaction->setGeometry(QRect(10, 170, 521, 191));
        txtTransaction = new QPlainTextEdit(grpTransaction);
        txtTransaction->setObjectName(QString::fromUtf8("txtTransaction"));
        txtTransaction->setGeometry(QRect(10, 20, 501, 161));
        txtTransaction->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        txtTransaction->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        txtTransaction->setLineWrapMode(QPlainTextEdit::NoWrap);
        txtTransaction->setReadOnly(true);
        grpUser = new QGroupBox(dlgClient);
        grpUser->setObjectName(QString::fromUtf8("grpUser"));
        grpUser->setGeometry(QRect(10, 70, 521, 91));
        btnGetAllUser = new QPushButton(grpUser);
        btnGetAllUser->setObjectName(QString::fromUtf8("btnGetAllUser"));
        btnGetAllUser->setGeometry(QRect(380, 20, 61, 23));
        btnAddUser = new QPushButton(grpUser);
        btnAddUser->setObjectName(QString::fromUtf8("btnAddUser"));
        btnAddUser->setGeometry(QRect(10, 20, 51, 23));
        btnUpdateUser = new QPushButton(grpUser);
        btnUpdateUser->setObjectName(QString::fromUtf8("btnUpdateUser"));
        btnUpdateUser->setGeometry(QRect(70, 20, 61, 23));
        btnRemoveUser = new QPushButton(grpUser);
        btnRemoveUser->setObjectName(QString::fromUtf8("btnRemoveUser"));
        btnRemoveUser->setGeometry(QRect(140, 20, 61, 23));
        btnRemoveAllUser = new QPushButton(grpUser);
        btnRemoveAllUser->setObjectName(QString::fromUtf8("btnRemoveAllUser"));
        btnRemoveAllUser->setGeometry(QRect(210, 20, 81, 23));
        btnFetchUser = new QPushButton(grpUser);
        btnFetchUser->setObjectName(QString::fromUtf8("btnFetchUser"));
        btnFetchUser->setGeometry(QRect(300, 20, 71, 23));
        lineUser = new QFrame(grpUser);
        lineUser->setObjectName(QString::fromUtf8("lineUser"));
        lineUser->setGeometry(QRect(10, 40, 501, 20));
        lineUser->setFrameShape(QFrame::HLine);
        lineUser->setFrameShadow(QFrame::Sunken);
        lblId = new QLabel(grpUser);
        lblId->setObjectName(QString::fromUtf8("lblId"));
        lblId->setGeometry(QRect(10, 60, 21, 16));
        lblFirstName = new QLabel(grpUser);
        lblFirstName->setObjectName(QString::fromUtf8("lblFirstName"));
        lblFirstName->setGeometry(QRect(100, 60, 61, 16));
        lblLastName = new QLabel(grpUser);
        lblLastName->setObjectName(QString::fromUtf8("lblLastName"));
        lblLastName->setGeometry(QRect(240, 60, 61, 16));
        lblBirthDate = new QLabel(grpUser);
        lblBirthDate->setObjectName(QString::fromUtf8("lblBirthDate"));
        lblBirthDate->setGeometry(QRect(380, 60, 51, 16));
        txtId = new QLineEdit(grpUser);
        txtId->setObjectName(QString::fromUtf8("txtId"));
        txtId->setGeometry(QRect(30, 60, 61, 20));
        txtFirstName = new QLineEdit(grpUser);
        txtFirstName->setObjectName(QString::fromUtf8("txtFirstName"));
        txtFirstName->setGeometry(QRect(160, 60, 71, 20));
        txtLastName = new QLineEdit(grpUser);
        txtLastName->setObjectName(QString::fromUtf8("txtLastName"));
        txtLastName->setGeometry(QRect(300, 60, 71, 20));
        txtBirthDate = new QLineEdit(grpUser);
        txtBirthDate->setObjectName(QString::fromUtf8("txtBirthDate"));
        txtBirthDate->setGeometry(QRect(440, 60, 71, 20));
        btnSearchUser = new QPushButton(grpUser);
        btnSearchUser->setObjectName(QString::fromUtf8("btnSearchUser"));
        btnSearchUser->setGeometry(QRect(450, 20, 61, 23));
        grpServerConnection = new QGroupBox(dlgClient);
        grpServerConnection->setObjectName(QString::fromUtf8("grpServerConnection"));
        grpServerConnection->setGeometry(QRect(10, 10, 211, 51));
        lblIp = new QLabel(grpServerConnection);
        lblIp->setObjectName(QString::fromUtf8("lblIp"));
        lblIp->setGeometry(QRect(10, 20, 21, 16));
        lblPort = new QLabel(grpServerConnection);
        lblPort->setObjectName(QString::fromUtf8("lblPort"));
        lblPort->setGeometry(QRect(120, 20, 31, 16));
        spinPort = new QSpinBox(grpServerConnection);
        spinPort->setObjectName(QString::fromUtf8("spinPort"));
        spinPort->setGeometry(QRect(150, 20, 51, 22));
        spinPort->setMinimum(1);
        spinPort->setMaximum(32000);
        txtIp = new QLineEdit(grpServerConnection);
        txtIp->setObjectName(QString::fromUtf8("txtIp"));
        txtIp->setGeometry(QRect(30, 20, 81, 20));
        txtIp->setAlignment(Qt::AlignCenter);

        retranslateUi(dlgClient);

        QMetaObject::connectSlotsByName(dlgClient);
    } // setupUi

    void retranslateUi(QWidget *dlgClient)
    {
        dlgClient->setWindowTitle(QCoreApplication::translate("dlgClient", "qxClient", nullptr));
        grpServerInfos->setTitle(QCoreApplication::translate("dlgClient", "Server infos transaction", nullptr));
#if QT_CONFIG(tooltip)
        btnDateTime->setToolTip(QCoreApplication::translate("dlgClient", "Get Server DateTime", nullptr));
#endif // QT_CONFIG(tooltip)
        btnDateTime->setText(QCoreApplication::translate("dlgClient", "Get Server DateTime", nullptr));
#if QT_CONFIG(tooltip)
        btnDateTime_Async->setToolTip(QCoreApplication::translate("dlgClient", "Get Server DateTime Async", nullptr));
#endif // QT_CONFIG(tooltip)
        btnDateTime_Async->setText(QCoreApplication::translate("dlgClient", "Get Server DateTime Async", nullptr));
        grpTransaction->setTitle(QCoreApplication::translate("dlgClient", "Log last client-server reply-request transaction", nullptr));
        grpUser->setTitle(QCoreApplication::translate("dlgClient", "User transaction", nullptr));
#if QT_CONFIG(tooltip)
        btnGetAllUser->setToolTip(QCoreApplication::translate("dlgClient", "Get All Users", nullptr));
#endif // QT_CONFIG(tooltip)
        btnGetAllUser->setText(QCoreApplication::translate("dlgClient", "Get All", nullptr));
#if QT_CONFIG(tooltip)
        btnAddUser->setToolTip(QCoreApplication::translate("dlgClient", "Add User", nullptr));
#endif // QT_CONFIG(tooltip)
        btnAddUser->setText(QCoreApplication::translate("dlgClient", "Add", nullptr));
#if QT_CONFIG(tooltip)
        btnUpdateUser->setToolTip(QCoreApplication::translate("dlgClient", "Update User", nullptr));
#endif // QT_CONFIG(tooltip)
        btnUpdateUser->setText(QCoreApplication::translate("dlgClient", "Update", nullptr));
#if QT_CONFIG(tooltip)
        btnRemoveUser->setToolTip(QCoreApplication::translate("dlgClient", "Remove User", nullptr));
#endif // QT_CONFIG(tooltip)
        btnRemoveUser->setText(QCoreApplication::translate("dlgClient", "Remove", nullptr));
#if QT_CONFIG(tooltip)
        btnRemoveAllUser->setToolTip(QCoreApplication::translate("dlgClient", "Remove All Users", nullptr));
#endif // QT_CONFIG(tooltip)
        btnRemoveAllUser->setText(QCoreApplication::translate("dlgClient", "Remove All", nullptr));
#if QT_CONFIG(tooltip)
        btnFetchUser->setToolTip(QCoreApplication::translate("dlgClient", "Fetch User", nullptr));
#endif // QT_CONFIG(tooltip)
        btnFetchUser->setText(QCoreApplication::translate("dlgClient", "Fetch", nullptr));
#if QT_CONFIG(tooltip)
        lblId->setToolTip(QCoreApplication::translate("dlgClient", "ID", nullptr));
#endif // QT_CONFIG(tooltip)
        lblId->setText(QCoreApplication::translate("dlgClient", "ID :", nullptr));
#if QT_CONFIG(tooltip)
        lblFirstName->setToolTip(QCoreApplication::translate("dlgClient", "First Name", nullptr));
#endif // QT_CONFIG(tooltip)
        lblFirstName->setText(QCoreApplication::translate("dlgClient", "First Name :", nullptr));
#if QT_CONFIG(tooltip)
        lblLastName->setToolTip(QCoreApplication::translate("dlgClient", "Last Name", nullptr));
#endif // QT_CONFIG(tooltip)
        lblLastName->setText(QCoreApplication::translate("dlgClient", "Last Name :", nullptr));
#if QT_CONFIG(tooltip)
        lblBirthDate->setToolTip(QCoreApplication::translate("dlgClient", "Birthdate", nullptr));
#endif // QT_CONFIG(tooltip)
        lblBirthDate->setText(QCoreApplication::translate("dlgClient", "Birthdate :", nullptr));
#if QT_CONFIG(tooltip)
        txtId->setToolTip(QCoreApplication::translate("dlgClient", "ID", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        txtFirstName->setToolTip(QCoreApplication::translate("dlgClient", "First Name", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        txtLastName->setToolTip(QCoreApplication::translate("dlgClient", "Last Name", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        txtBirthDate->setToolTip(QCoreApplication::translate("dlgClient", "Birthdate", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        btnSearchUser->setToolTip(QCoreApplication::translate("dlgClient", "Search Users", nullptr));
#endif // QT_CONFIG(tooltip)
        btnSearchUser->setText(QCoreApplication::translate("dlgClient", "Search", nullptr));
        grpServerConnection->setTitle(QCoreApplication::translate("dlgClient", "Server connection", nullptr));
#if QT_CONFIG(tooltip)
        lblIp->setToolTip(QCoreApplication::translate("dlgClient", "Ip", nullptr));
#endif // QT_CONFIG(tooltip)
        lblIp->setText(QCoreApplication::translate("dlgClient", "Ip :", nullptr));
#if QT_CONFIG(tooltip)
        lblPort->setToolTip(QCoreApplication::translate("dlgClient", "Port", nullptr));
#endif // QT_CONFIG(tooltip)
        lblPort->setText(QCoreApplication::translate("dlgClient", "Port :", nullptr));
#if QT_CONFIG(tooltip)
        spinPort->setToolTip(QCoreApplication::translate("dlgClient", "Port", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        txtIp->setToolTip(QCoreApplication::translate("dlgClient", "Ip", nullptr));
#endif // QT_CONFIG(tooltip)
        txtIp->setText(QCoreApplication::translate("dlgClient", "127.0.0.1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dlgClient: public Ui_dlgClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QXCLIENT_H
