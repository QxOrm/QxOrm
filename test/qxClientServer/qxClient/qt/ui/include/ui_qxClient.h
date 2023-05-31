#ifndef _QX_UI_QXCLIENT_H_
#define _QX_UI_QXCLIENT_H_

#include <QtCore/qglobal.h>

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
#include "./ui_qxClient_qt6.h"
#elif (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include "./ui_qxClient_qt5.h"
#else // (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include "./ui_qxClient_qt4.h"
#endif // (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))

#endif // _QX_UI_QXCLIENT_H_
