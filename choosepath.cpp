#include "choosepath.h"
#include "ui_choosepath.h"
#include "mainWindow.h"
#include "ui_mainWindow.h"
//test

ChoosePath::ChoosePath(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChoosePath)
{
    ui->setupUi(this);
}

ChoosePath::~ChoosePath()
{
    delete ui;
}

void ChoosePath::on_uciButton_clicked()
{
    auto* saddleback = new pathSaddleback();
    saddleback->show();

}

void ChoosePath::on_pickNumSchoolButton_clicked()
{
    auto* ASU = new pathASU();
    ASU -> show();
}

void ChoosePath::on_customTourButton_clicked()
{
    auto* custom = new pathCustom();
    custom -> show();

}

void ChoosePath::on_backButton_clicked()
{
    hide();
}
