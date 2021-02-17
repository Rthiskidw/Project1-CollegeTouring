<<<<<<< HEAD
#include "mainWindow.h"
=======
#include "mainwindow.h"
#include "choosepath.h"
>>>>>>> c7959131e280afb868a0612ef9a56f17643f8b9d

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
