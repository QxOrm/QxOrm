#ifndef _QX_UI_QXCLIENT_H_
#define _QX_UI_QXCLIENT_H_

#include <QtCore/qglobal.h>

#if (QT_VERSION >= QT_VERSION_CHECK(6,00,00))
#include "./ui_qxClient_qt6.h"
#elif (QT_VERSION >= QT_VERSION_CHECK(5,00,00))
#include "./ui_qxClient_qt5.h"
#else // (QT_VERSION >= QT_VERSION_CHECK(5,00,00))
#include "./ui_qxClient_qt4.h"
#endif // (QT_VERSION >= QT_VERSION_CHECK(5,00,00))

#endif // _QX_UI_QXCLIENT_H_
