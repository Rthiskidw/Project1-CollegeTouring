#include "pathsaddleback.h"
#include "ui_pathsaddleback.h"
#include "mainWindow.h"
#include "choosepath.h"
#include "ui_choosepath.h"

pathSaddleback::pathSaddleback(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pathSaddleback)
{
    ui->setupUi(this);
}

pathSaddleback::~pathSaddleback()
{
    delete ui;
}

void pathSaddleback::on_startTrip_button_clicked()
{
    auto* souvenir  = new souvenirShop(this);
    souvenir -> show();
}

void pathSaddleback::on_planTrip_button_clicked()
{
    // Need to implement planTrip button

}

void pathSaddleback::on_backButton_clicked()
{
//    auto* saddleback = new pathSaddleback(this);
//    saddleback->hide();
    ChoosePath* choosePath = new ChoosePath(this);
    choosePath -> show();

}
