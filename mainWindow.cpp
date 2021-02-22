#include "mainWindow.h"
#include "ui_mainWindow.h"
#include "choosepath.h"
#include "database.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this is me adding a comment ok
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
