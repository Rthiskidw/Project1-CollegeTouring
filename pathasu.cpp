#include "pathasu.h"
#include "ui_pathasu.h"

pathASU::pathASU(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pathASU)
{
    ui->setupUi(this);
}

pathASU::~pathASU()
{
    delete ui;
}
