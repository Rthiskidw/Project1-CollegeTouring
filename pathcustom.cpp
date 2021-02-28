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
