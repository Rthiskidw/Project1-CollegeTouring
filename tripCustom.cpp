#include "tripCustom.h"


tripCustom::tripCustom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tripCustom)
{
    ui->setupUi(this);
}

tripCustom::~tripCustom()
{
    delete ui;
}
