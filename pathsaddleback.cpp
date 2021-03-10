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
    ui->startTrip_button->hide();
}

pathSaddleback::~pathSaddleback()
{
    delete ui;
}

void pathSaddleback::on_startTrip_button_clicked()
{
    auto* souvenir  = new souvenirShop(totalDistance, orderedSchoolsName);
    hide();
    souvenir -> show();
}

void pathSaddleback::on_planTrip_button_clicked()
{
    efficiencyAlgo(&chosenSchools, &orderedSchoolsName, &orderedSchoolsDistance, "Saddleback College");

    QWidget *container = new QWidget;
    QVBoxLayout *vBoxLayout = new QVBoxLayout;

    container->setLayout(vBoxLayout);

    ui->scrollArea_chosenSchools->setWidget(container);

    //filling scroll area with chosen schools
    for(int i = 0; i < orderedSchoolsLabels.size(); i++)
    {
        vBoxLayout->addWidget(orderedSchoolsLabels[i]);
    }
    ui->startTrip_button->show();
    ui->planTrip_button->hide();
}

void pathSaddleback::efficiencyAlgo(QVector<QString> *colleges,
                 QVector<QString> *routeNames,
                 QVector<double> *routeDistances,
                 QString currentCollege)
{
    // BASE CASE: no more schools to visit
    if(colleges->empty()) { return; }

    QString nextSchool;         // next school in route
    double temp = 0;            // temperary var to compare to min distance
    double distance = 0;        // stores distance
    double minDist = 1000000;   // starting point for min distance
    int minIndex;               // index of min distance in college vector

    // find min distance
    for(int i=0; i < colleges->size(); i++) {

        qDebug() << "i: " << i << Qt::endl;
        QSqlQuery *query = new QSqlQuery();

        query->prepare("SELECT * FROM Colleges WHERE "
                      "Colleges.starting_college == '" + currentCollege + "' AND "
                      "Colleges.ending_college == '" + colleges->at(i) + "'");

        if(query->exec()) {
            qDebug() << "Efficiency algo executed" << Qt::endl;
            query->next();
            qDebug() << "Distance: " << query->value(2).toDouble() << Qt::endl;
            distance = query->value(2).toDouble();

        temp = distance;

        if ( temp < minDist ) {
            minDist = temp;
            nextSchool = colleges->at(i);
            minIndex = i;
        }
    }
}
    // remove nextSchool from college vector
    colleges->erase(colleges->begin()+minIndex);
    // add next school to route
     qDebug() << "School: " << nextSchool << Qt::endl;

    QLabel* tempSchool = new QLabel (nextSchool+ " [" + QString::number(minDist) + " miles from " + currentCollege + "]");

    routeNames->push_back(nextSchool);
    // add distance to next school in route
    routeDistances->push_back(minDist);

    orderedSchoolsLabels.push_back(tempSchool);

    totalDistance = totalDistance + minDist;


    // RECURSIVE CALL
    efficiencyAlgo(colleges, routeNames, routeDistances, nextSchool);
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
             qDebug() << (query->value(0).toString()) + " [" + (query->value(1).toString()) + " Miles From Saddleback]";
             chosenSchools.push_back((query->value(0).toString()));
             schoolLabelsVector.push_back(school);
        }

        for(int i = 0; i < schoolLabelsVector.size(); i++)
        {
            vBoxLayout->addWidget(schoolLabelsVector[i]);
        }
    }
}


