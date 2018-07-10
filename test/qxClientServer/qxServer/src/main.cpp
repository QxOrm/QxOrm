#include <QtGui/qapplication.h>

#include "../include/precompiled.h"
#include "../include/main_dlg.h"

#include <QxMemLeak.h>

int main(int argc, char * argv[])
{
   QApplication app(argc, argv);

   main_dlg dlg;
   dlg.show();

   return app.exec();
}
