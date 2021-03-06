#include "endtour.h"
#include "ui_endtour.h"

endTour::endTour(QString totalDistance, QString totalCost, QVector<QString> collegeNames,
                 QVector<double> costAtEachCampus,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::endTour)
{
    ui->setupUi(this);

    ui->label_totalDistance->setText(totalDistance);
    ui->label_totalCost->setText(totalCost);

    QWidget *container = new QWidget;
    QVBoxLayout *vBoxLayout = new QVBoxLayout;

    container->setLayout(vBoxLayout);

    ui->scrollArea_colleges->setWidget(container);

    //filling scroll area with chosen schools
    for(int i = 0; i < collegeNames.size(); i++)
    {
        //collegeLabel = new QLabel(collegeNames[i] + "\t\t" + costAtEachCampus[i]);
        collegeLabel = new QLabel(collegeNames[i]);
        vBoxLayout->addWidget(collegeLabel);
    }
}

endTour::~endTour()
{
    delete ui;
}

void endTour::on_done_button_clicked()
{
    hide();
}
