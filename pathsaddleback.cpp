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
    initializeList();
}

pathSaddleback::~pathSaddleback()
{
    delete ui;
}

void pathSaddleback::on_startTrip_button_clicked()
{
//    auto* souvenir  = new souvenirShop(this);
//    souvenir -> show();
}

void pathSaddleback::on_planTrip_button_clicked()
{
    QWidget *container = new QWidget;
    QVBoxLayout *vBoxLayout = new QVBoxLayout;

    container->setLayout(vBoxLayout);

    ui->scrollArea_chosenSchools->setWidget(container);

    //filling scroll area with chosen schools
    for(int i = 0; i < chosenSchoolsLabels.size(); i++)
    {
        vBoxLayout->addWidget(chosenSchoolsLabels[i]);
    }
}

void pathSaddleback::on_backButton_clicked()
{
    hide();
}

void pathSaddleback::initializeList()
{
    QSqlQuery *query = new QSqlQuery();

    schoolLabelsVector.clear();

    QWidget *container = new QWidget;
    QVBoxLayout *vBoxLayout = new QVBoxLayout;

    container->setLayout(vBoxLayout);

    ui->scrollArea_SchoolOptions->setWidget(container);


    query->prepare("SELECT ending_college, distances  FROM Colleges WHERE starting_college='Saddleback College'");
    if(!query->exec())
    {
        qDebug() << "pathSaddleback initialize school list query failed";
    }
    else
    {
        while(query->next())
        {
             //adding college options and their distances from saddleback to labels
             QLabel* school = new QLabel((query->value(0).toString()) + " [" + (query->value(1).toString()) + " Miles From Saddleback]");
             schoolLabelsVector.push_back(school);
        }

        for(int i = 0; i < schoolLabelsVector.size(); i++)
        {
            vBoxLayout->addWidget(schoolLabelsVector[i]);
        }
    }
}


