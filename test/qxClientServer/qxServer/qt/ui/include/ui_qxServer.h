#ifndef _QX_UI_QXSERVER_H_
#define _QX_UI_QXSERVER_H_

#include <QtCore/qglobal.h>

#if (QT_VERSION >= 0x060000)
#include "./ui_qxServer_qt6.h"
#elif (QT_VERSION >= 0x050000)
#include "./ui_qxServer_qt5.h"
#else // (QT_VERSION >= 0x050000)
#include "./ui_qxServer_qt4.h"
#endif // (QT_VERSION >= 0x050000)

#endif // _QX_UI_QXSERVER_H_
