/********************************************************************************
** Form generated from reading UI file 'qxClient.ui'
**
** Created: Wed 23. Jan 10:45:24 2013
**      by: Qt User Interface Compiler version 5.0.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QXCLIENT_QT5_H
#define UI_QXCLIENT_QT5_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
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
            dlgClient->setObjectName(QStringLiteral("dlgClient"));
        dlgClient->resize(541, 371);
        dlgClient->setMinimumSize(QSize(541, 371));
        dlgClient->setMaximumSize(QSize(541, 371));
        grpServerInfos = new QGroupBox(dlgClient);
        grpServerInfos->setObjectName(QStringLiteral("grpServerInfos"));
        grpServerInfos->setGeometry(QRect(230, 10, 301, 51));
        btnDateTime = new QPushButton(grpServerInfos);
        btnDateTime->setObjectName(QStringLiteral("btnDateTime"));
        btnDateTime->setGeometry(QRect(10, 20, 121, 23));
        btnDateTime_Async = new QPushButton(grpServerInfos);
        btnDateTime_Async->setObjectName(QStringLiteral("btnDateTime_Async"));
        btnDateTime_Async->setGeometry(QRect(140, 20, 151, 23));
        grpTransaction = new QGroupBox(dlgClient);
        grpTransaction->setObjectName(QStringLiteral("grpTransaction"));
        grpTransaction->setGeometry(QRect(10, 170, 521, 191));
        txtTransaction = new QPlainTextEdit(grpTransaction);
        txtTransaction->setObjectName(QStringLiteral("txtTransaction"));
        txtTransaction->setGeometry(QRect(10, 20, 501, 161));
        txtTransaction->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        txtTransaction->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        txtTransaction->setLineWrapMode(QPlainTextEdit::NoWrap);
        txtTransaction->setReadOnly(true);
        grpUser = new QGroupBox(dlgClient);
        grpUser->setObjectName(QStringLiteral("grpUser"));
        grpUser->setGeometry(QRect(10, 70, 521, 91));
        btnGetAllUser = new QPushButton(grpUser);
        btnGetAllUser->setObjectName(QStringLiteral("btnGetAllUser"));
        btnGetAllUser->setGeometry(QRect(380, 20, 61, 23));
        btnAddUser = new QPushButton(grpUser);
        btnAddUser->setObjectName(QStringLiteral("btnAddUser"));
        btnAddUser->setGeometry(QRect(10, 20, 51, 23));
        btnUpdateUser = new QPushButton(grpUser);
        btnUpdateUser->setObjectName(QStringLiteral("btnUpdateUser"));
        btnUpdateUser->setGeometry(QRect(70, 20, 61, 23));
        btnRemoveUser = new QPushButton(grpUser);
        btnRemoveUser->setObjectName(QStringLiteral("btnRemoveUser"));
        btnRemoveUser->setGeometry(QRect(140, 20, 61, 23));
        btnRemoveAllUser = new QPushButton(grpUser);
        btnRemoveAllUser->setObjectName(QStringLiteral("btnRemoveAllUser"));
        btnRemoveAllUser->setGeometry(QRect(210, 20, 81, 23));
        btnFetchUser = new QPushButton(grpUser);
        btnFetchUser->setObjectName(QStringLiteral("btnFetchUser"));
        btnFetchUser->setGeometry(QRect(300, 20, 71, 23));
        lineUser = new QFrame(grpUser);
        lineUser->setObjectName(QStringLiteral("lineUser"));
        lineUser->setGeometry(QRect(10, 40, 501, 20));
        lineUser->setFrameShape(QFrame::HLine);
        lineUser->setFrameShadow(QFrame::Sunken);
        lblId = new QLabel(grpUser);
        lblId->setObjectName(QStringLiteral("lblId"));
        lblId->setGeometry(QRect(10, 60, 21, 16));
        lblFirstName = new QLabel(grpUser);
        lblFirstName->setObjectName(QStringLiteral("lblFirstName"));
        lblFirstName->setGeometry(QRect(100, 60, 61, 16));
        lblLastName = new QLabel(grpUser);
        lblLastName->setObjectName(QStringLiteral("lblLastName"));
        lblLastName->setGeometry(QRect(240, 60, 61, 16));
        lblBirthDate = new QLabel(grpUser);
        lblBirthDate->setObjectName(QStringLiteral("lblBirthDate"));
        lblBirthDate->setGeometry(QRect(380, 60, 51, 16));
        txtId = new QLineEdit(grpUser);
        txtId->setObjectName(QStringLiteral("txtId"));
        txtId->setGeometry(QRect(30, 60, 61, 20));
        txtFirstName = new QLineEdit(grpUser);
        txtFirstName->setObjectName(QStringLiteral("txtFirstName"));
        txtFirstName->setGeometry(QRect(160, 60, 71, 20));
        txtLastName = new QLineEdit(grpUser);
        txtLastName->setObjectName(QStringLiteral("txtLastName"));
        txtLastName->setGeometry(QRect(300, 60, 71, 20));
        txtBirthDate = new QLineEdit(grpUser);
        txtBirthDate->setObjectName(QStringLiteral("txtBirthDate"));
        txtBirthDate->setGeometry(QRect(440, 60, 71, 20));
        btnSearchUser = new QPushButton(grpUser);
        btnSearchUser->setObjectName(QStringLiteral("btnSearchUser"));
        btnSearchUser->setGeometry(QRect(450, 20, 61, 23));
        grpServerConnection = new QGroupBox(dlgClient);
        grpServerConnection->setObjectName(QStringLiteral("grpServerConnection"));
        grpServerConnection->setGeometry(QRect(10, 10, 211, 51));
        lblIp = new QLabel(grpServerConnection);
        lblIp->setObjectName(QStringLiteral("lblIp"));
        lblIp->setGeometry(QRect(10, 20, 21, 16));
        lblPort = new QLabel(grpServerConnection);
        lblPort->setObjectName(QStringLiteral("lblPort"));
        lblPort->setGeometry(QRect(120, 20, 31, 16));
        spinPort = new QSpinBox(grpServerConnection);
        spinPort->setObjectName(QStringLiteral("spinPort"));
        spinPort->setGeometry(QRect(150, 20, 51, 22));
        spinPort->setMinimum(1);
        spinPort->setMaximum(32000);
        txtIp = new QLineEdit(grpServerConnection);
        txtIp->setObjectName(QStringLiteral("txtIp"));
        txtIp->setGeometry(QRect(30, 20, 81, 20));
        txtIp->setAlignment(Qt::AlignCenter);

        retranslateUi(dlgClient);

        QMetaObject::connectSlotsByName(dlgClient);
    } // setupUi

    void retranslateUi(QWidget *dlgClient)
    {
        dlgClient->setWindowTitle(QApplication::translate("dlgClient", "qxClient", 0));
        grpServerInfos->setTitle(QApplication::translate("dlgClient", "Server infos transaction", 0));
#ifndef QT_NO_TOOLTIP
        btnDateTime->setToolTip(QApplication::translate("dlgClient", "Get Server DateTime", 0));
#endif // QT_NO_TOOLTIP
        btnDateTime->setText(QApplication::translate("dlgClient", "Get Server DateTime", 0));
#ifndef QT_NO_TOOLTIP
        btnDateTime_Async->setToolTip(QApplication::translate("dlgClient", "Get Server DateTime Async", 0));
#endif // QT_NO_TOOLTIP
        btnDateTime_Async->setText(QApplication::translate("dlgClient", "Get Server DateTime Async", 0));
        grpTransaction->setTitle(QApplication::translate("dlgClient", "Log last client-server reply-request transaction", 0));
        grpUser->setTitle(QApplication::translate("dlgClient", "User transaction", 0));
#ifndef QT_NO_TOOLTIP
        btnGetAllUser->setToolTip(QApplication::translate("dlgClient", "Get All Users", 0));
#endif // QT_NO_TOOLTIP
        btnGetAllUser->setText(QApplication::translate("dlgClient", "Get All", 0));
#ifndef QT_NO_TOOLTIP
        btnAddUser->setToolTip(QApplication::translate("dlgClient", "Add User", 0));
#endif // QT_NO_TOOLTIP
        btnAddUser->setText(QApplication::translate("dlgClient", "Add", 0));
#ifndef QT_NO_TOOLTIP
        btnUpdateUser->setToolTip(QApplication::translate("dlgClient", "Update User", 0));
#endif // QT_NO_TOOLTIP
        btnUpdateUser->setText(QApplication::translate("dlgClient", "Update", 0));
#ifndef QT_NO_TOOLTIP
        btnRemoveUser->setToolTip(QApplication::translate("dlgClient", "Remove User", 0));
#endif // QT_NO_TOOLTIP
        btnRemoveUser->setText(QApplication::translate("dlgClient", "Remove", 0));
#ifndef QT_NO_TOOLTIP
        btnRemoveAllUser->setToolTip(QApplication::translate("dlgClient", "Remove All Users", 0));
#endif // QT_NO_TOOLTIP
        btnRemoveAllUser->setText(QApplication::translate("dlgClient", "Remove All", 0));
#ifndef QT_NO_TOOLTIP
        btnFetchUser->setToolTip(QApplication::translate("dlgClient", "Fetch User", 0));
#endif // QT_NO_TOOLTIP
        btnFetchUser->setText(QApplication::translate("dlgClient", "Fetch", 0));
#ifndef QT_NO_TOOLTIP
        lblId->setToolTip(QApplication::translate("dlgClient", "ID", 0));
#endif // QT_NO_TOOLTIP
        lblId->setText(QApplication::translate("dlgClient", "ID :", 0));
#ifndef QT_NO_TOOLTIP
        lblFirstName->setToolTip(QApplication::translate("dlgClient", "First Name", 0));
#endif // QT_NO_TOOLTIP
        lblFirstName->setText(QApplication::translate("dlgClient", "First Name :", 0));
#ifndef QT_NO_TOOLTIP
        lblLastName->setToolTip(QApplication::translate("dlgClient", "Last Name", 0));
#endif // QT_NO_TOOLTIP
        lblLastName->setText(QApplication::translate("dlgClient", "Last Name :", 0));
#ifndef QT_NO_TOOLTIP
        lblBirthDate->setToolTip(QApplication::translate("dlgClient", "Birthdate", 0));
#endif // QT_NO_TOOLTIP
        lblBirthDate->setText(QApplication::translate("dlgClient", "Birthdate :", 0));
#ifndef QT_NO_TOOLTIP
        txtId->setToolTip(QApplication::translate("dlgClient", "ID", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        txtFirstName->setToolTip(QApplication::translate("dlgClient", "First Name", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        txtLastName->setToolTip(QApplication::translate("dlgClient", "Last Name", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        txtBirthDate->setToolTip(QApplication::translate("dlgClient", "Birthdate", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        btnSearchUser->setToolTip(QApplication::translate("dlgClient", "Search Users", 0));
#endif // QT_NO_TOOLTIP
        btnSearchUser->setText(QApplication::translate("dlgClient", "Search", 0));
        grpServerConnection->setTitle(QApplication::translate("dlgClient", "Server connection", 0));
#ifndef QT_NO_TOOLTIP
        lblIp->setToolTip(QApplication::translate("dlgClient", "Ip", 0));
#endif // QT_NO_TOOLTIP
        lblIp->setText(QApplication::translate("dlgClient", "Ip :", 0));
#ifndef QT_NO_TOOLTIP
        lblPort->setToolTip(QApplication::translate("dlgClient", "Port", 0));
#endif // QT_NO_TOOLTIP
        lblPort->setText(QApplication::translate("dlgClient", "Port :", 0));
#ifndef QT_NO_TOOLTIP
        spinPort->setToolTip(QApplication::translate("dlgClient", "Port", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        txtIp->setToolTip(QApplication::translate("dlgClient", "Ip", 0));
#endif // QT_NO_TOOLTIP
        txtIp->setText(QApplication::translate("dlgClient", "127.0.0.1", 0));
    } // retranslateUi

};

namespace Ui {
    class dlgClient: public Ui_dlgClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QXCLIENT_QT5_H
