#include "souvenirshop.h"
#include "ui_souvenirshop.h"

souvenirShop::souvenirShop(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::souvenirShop)
{
    ui->setupUi(this);
}

souvenirShop::~souvenirShop()
{
    delete ui;
}
