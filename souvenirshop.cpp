#include "souvenirshop.h"
#include "ui_souvenirshop.h"

souvenirShop::souvenirShop(QVector<QString> collegesVector, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::souvenirShop)
{
    ui->setupUi(this);
    ui->label_collegeName->setText(collegesVector[0]);


}

souvenirShop::~souvenirShop()
{
    delete ui;
}
