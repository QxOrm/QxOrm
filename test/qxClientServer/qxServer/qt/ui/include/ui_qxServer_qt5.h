/********************************************************************************
** Form generated from reading UI file 'qxServer.ui'
**
** Created: Wed 23. Jan 10:49:00 2013
**      by: Qt User Interface Compiler version 5.0.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QXSERVER_QT5_H
#define UI_QXSERVER_QT5_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dlgServer
{
public:
    QGroupBox *grpError;
    QPlainTextEdit *txtError;
    QGroupBox *grpServerParams;
    QLabel *lblThreadCount;
    QLabel *lblSerializationType;
    QComboBox *cboSerializationType;
    QLabel *lblPortNumber;
    QSpinBox *spinPortNumber;
    QCheckBox *chkCompressData;
    QPushButton *btnStartStop;
    QFrame *lineServerParams;
    QLabel *imgIsRunning;
    QSpinBox *spinThreadCount;
    QCheckBox *chkEncryptData;
    QGroupBox *grpTransaction;
    QPlainTextEdit *txtTransaction;

    void setupUi(QWidget *dlgServer)
    {
        if (dlgServer->objectName().isEmpty())
            dlgServer->setObjectName(QStringLiteral("dlgServer"));
        dlgServer->resize(552, 392);
        dlgServer->setMinimumSize(QSize(552, 392));
        dlgServer->setMaximumSize(QSize(552, 392));
        grpError = new QGroupBox(dlgServer);
        grpError->setObjectName(QStringLiteral("grpError"));
        grpError->setGeometry(QRect(10, 310, 531, 71));
        txtError = new QPlainTextEdit(grpError);
        txtError->setObjectName(QStringLiteral("txtError"));
        txtError->setGeometry(QRect(10, 20, 511, 41));
        QPalette palette;
        QBrush brush(QColor(170, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush1(QColor(112, 111, 113, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        txtError->setPalette(palette);
        txtError->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        txtError->setReadOnly(true);
        grpServerParams = new QGroupBox(dlgServer);
        grpServerParams->setObjectName(QStringLiteral("grpServerParams"));
        grpServerParams->setGeometry(QRect(10, 10, 531, 81));
        lblThreadCount = new QLabel(grpServerParams);
        lblThreadCount->setObjectName(QStringLiteral("lblThreadCount"));
        lblThreadCount->setGeometry(QRect(180, 15, 81, 16));
        lblSerializationType = new QLabel(grpServerParams);
        lblSerializationType->setObjectName(QStringLiteral("lblSerializationType"));
        lblSerializationType->setGeometry(QRect(10, 50, 91, 16));
        cboSerializationType = new QComboBox(grpServerParams);
        cboSerializationType->setObjectName(QStringLiteral("cboSerializationType"));
        cboSerializationType->setGeometry(QRect(110, 50, 51, 20));
        lblPortNumber = new QLabel(grpServerParams);
        lblPortNumber->setObjectName(QStringLiteral("lblPortNumber"));
        lblPortNumber->setGeometry(QRect(10, 20, 81, 16));
        spinPortNumber = new QSpinBox(grpServerParams);
        spinPortNumber->setObjectName(QStringLiteral("spinPortNumber"));
        spinPortNumber->setGeometry(QRect(110, 20, 51, 22));
        spinPortNumber->setMinimum(1);
        spinPortNumber->setMaximum(32000);
        chkCompressData = new QCheckBox(grpServerParams);
        chkCompressData->setObjectName(QStringLiteral("chkCompressData"));
        chkCompressData->setGeometry(QRect(180, 40, 101, 17));
        btnStartStop = new QPushButton(grpServerParams);
        btnStartStop->setObjectName(QStringLiteral("btnStartStop"));
        btnStartStop->setGeometry(QRect(330, 20, 111, 51));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        btnStartStop->setFont(font);
        lineServerParams = new QFrame(grpServerParams);
        lineServerParams->setObjectName(QStringLiteral("lineServerParams"));
        lineServerParams->setGeometry(QRect(320, 10, 3, 61));
        lineServerParams->setFrameShape(QFrame::VLine);
        lineServerParams->setFrameShadow(QFrame::Sunken);
        imgIsRunning = new QLabel(grpServerParams);
        imgIsRunning->setObjectName(QStringLiteral("imgIsRunning"));
        imgIsRunning->setGeometry(QRect(450, 20, 71, 51));
        imgIsRunning->setAlignment(Qt::AlignCenter);
        spinThreadCount = new QSpinBox(grpServerParams);
        spinThreadCount->setObjectName(QStringLiteral("spinThreadCount"));
        spinThreadCount->setGeometry(QRect(260, 15, 51, 22));
        spinThreadCount->setMinimum(1);
        spinThreadCount->setMaximum(999);
        chkEncryptData = new QCheckBox(grpServerParams);
        chkEncryptData->setObjectName(QStringLiteral("chkEncryptData"));
        chkEncryptData->setGeometry(QRect(180, 55, 101, 17));
        grpTransaction = new QGroupBox(dlgServer);
        grpTransaction->setObjectName(QStringLiteral("grpTransaction"));
        grpTransaction->setGeometry(QRect(10, 100, 531, 201));
        txtTransaction = new QPlainTextEdit(grpTransaction);
        txtTransaction->setObjectName(QStringLiteral("txtTransaction"));
        txtTransaction->setGeometry(QRect(10, 20, 511, 171));
        txtTransaction->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        txtTransaction->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        txtTransaction->setLineWrapMode(QPlainTextEdit::NoWrap);
        txtTransaction->setReadOnly(true);

        retranslateUi(dlgServer);

        QMetaObject::connectSlotsByName(dlgServer);
    } // setupUi

    void retranslateUi(QWidget *dlgServer)
    {
        dlgServer->setWindowTitle(QApplication::translate("dlgServer", "qxServer", 0));
        grpError->setTitle(QApplication::translate("dlgServer", "Log last server error", 0));
        grpServerParams->setTitle(QApplication::translate("dlgServer", "Server parameters", 0));
#ifndef QT_NO_TOOLTIP
        lblThreadCount->setToolTip(QApplication::translate("dlgServer", "Thread Count", 0));
#endif // QT_NO_TOOLTIP
        lblThreadCount->setText(QApplication::translate("dlgServer", "Thread Count :", 0));
#ifndef QT_NO_TOOLTIP
        lblSerializationType->setToolTip(QApplication::translate("dlgServer", "Serialization Type", 0));
#endif // QT_NO_TOOLTIP
        lblSerializationType->setText(QApplication::translate("dlgServer", "Serialization Type :", 0));
#ifndef QT_NO_TOOLTIP
        cboSerializationType->setToolTip(QApplication::translate("dlgServer", "Serialization Type", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        lblPortNumber->setToolTip(QApplication::translate("dlgServer", "Port Number", 0));
#endif // QT_NO_TOOLTIP
        lblPortNumber->setText(QApplication::translate("dlgServer", "Port Number :", 0));
#ifndef QT_NO_TOOLTIP
        spinPortNumber->setToolTip(QApplication::translate("dlgServer", "Port Number", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        chkCompressData->setToolTip(QApplication::translate("dlgServer", "Compress Data", 0));
#endif // QT_NO_TOOLTIP
        chkCompressData->setText(QApplication::translate("dlgServer", "Compress Data", 0));
        btnStartStop->setText(QApplication::translate("dlgServer", "Start Server /\n"
"Stop Server", 0));
        imgIsRunning->setText(QApplication::translate("dlgServer", "[ is running ? ]", 0));
#ifndef QT_NO_TOOLTIP
        spinThreadCount->setToolTip(QApplication::translate("dlgServer", "Thread Count", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        chkEncryptData->setToolTip(QApplication::translate("dlgServer", "Encrypt Data", 0));
#endif // QT_NO_TOOLTIP
        chkEncryptData->setText(QApplication::translate("dlgServer", "Encrypt Data", 0));
        grpTransaction->setTitle(QApplication::translate("dlgServer", "Log last client-server reply-request transaction", 0));
    } // retranslateUi

};

namespace Ui {
    class dlgServer: public Ui_dlgServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QXSERVER_QT5_H
