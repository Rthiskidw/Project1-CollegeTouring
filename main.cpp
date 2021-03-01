#include "mainWindow.h"
#include "choosepath.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow k;
    Admin w;
    w.show();
    return a.exec();
}
