#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    // Disable resize arrow.
    #if defined(Q_OS_WIN)
        w.setWindowFlags(w.windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
    #endif
    if(w.closeAll)  //close
        return 0;
    else        //open
      w.show();

    return a.exec();
}
