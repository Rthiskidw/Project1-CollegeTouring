#include "mainwindow.h"
#include "database.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    database d;
    w.show();
    d.show();
    return a.exec();
}
