#include "mainWindow.h"
#include "ui_mainwindow.h"
// #include "login.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this is me adding a comment ok
}

void MainWindow::on_actionLogin_triggered()
{
//    auto* login = newLogin(this);
//    login->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

