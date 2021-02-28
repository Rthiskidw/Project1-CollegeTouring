#include "pathcustom.h"
#include "ui_pathcustom.h"

pathCustom::pathCustom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pathCustom)
{
    ui->setupUi(this);
}

pathCustom::~pathCustom()
{
    delete ui;
}

void pathCustom::on_toolButton_2_clicked()
{
    auto* souvenir  = new souvenirShop(this);
    souvenir -> show();
}
