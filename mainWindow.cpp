#include "mainWindow.h"
#include "ui_mainwindow.h"
//#include "login.h"
#include "database.h"
#include <QSqlRecord>
#include <QDir>
#include <QSqlField>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlError>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

