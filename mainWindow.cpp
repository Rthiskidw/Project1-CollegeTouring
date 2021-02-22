#include "mainWindow.h"
#include "ui_mainWindow.h"
#include "choosepath.h"
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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    MainWindow* mainwindow = new MainWindow(this);
    mainwindow->show();
    mainwindow->hide();
    auto* choosePath = new ChoosePath(this);
    choosePath->show();
}
