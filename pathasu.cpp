#include "pathasu.h"
#include "ui_pathasu.h"

pathASU::pathASU(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pathASU)
{
    ui->setupUi(this);

    initializeList();
    ui->toolButton_startTrip->hide();
}

pathASU::~pathASU()
{
    delete ui;
}

void pathASU::initializeList()
{
    QSqlQuery *query = new QSqlQuery();

    QWidget *container = new QWidget;
    QVBoxLayout *vBoxLayout = new QVBoxLayout;

    container->setLayout(vBoxLayout);

    ui->scrollArea_Colleges->setWidget(container);

    query->prepare("SELECT ending_college, distances  FROM Colleges WHERE starting_college='Arizona State University'");
    if(!query->exec())
    {
        qDebug() << "pathASU initialize school list query failed";
    }
    else
    {
        while(query->next())
        {
             chosenSchools.push_back((query->value(0).toString()));
        }
    }
    QLabel *startingSchool = new QLabel("Arizona State University[Starting School]");
    orderedSchoolsLabels.push_front(startingSchool);
}

void pathASU::on_backButton_clicked()
{
    hide();
}

void pathASU::on_pushButton_planTrip_clicked()
{
    userInput = ui->spinBox_input->value();

    if(userInput == 0)
    {
        QMessageBox::information(this, "Warning", "Cannot start trip with 0 schools. Please input a number greater than 0 or click 'X' to cancel trip.");
    }
    else if(userInput > 11)
    {
        QMessageBox::information(this, "Warning", "Max amount of schools is 11. Please input a number 1-11 or click 'X' to cancel trip.");
    }
    else
    {
        efficiencyAlgo(&chosenSchools, &orderedSchoolsName, &orderedSchoolsDistance, "Arizona State University");

        QWidget *container = new QWidget;
        QVBoxLayout *vBoxLayout = new QVBoxLayout;

        container->setLayout(vBoxLayout);

        ui->scrollArea_Colleges->setWidget(container);

        //filling scroll area with chosen schools
        for(int i = 0; i < orderedSchoolsLabels.size(); i++)
        {
            vBoxLayout->addWidget(orderedSchoolsLabels[i]);
        }

        //Add ASU(starting school) to vector
        orderedSchoolsName.push_front("Arizona State University");

        ui->toolButton_startTrip->show();
        ui->pushButton_planTrip->hide();
    }
}

void pathASU::efficiencyAlgo(QVector<QString> *colleges,
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

    if(collegeCount < userInput)
    {
        QLabel* tempSchool = new QLabel (nextSchool+ " [" + QString::number(minDist) + " miles from " + currentCollege + "]");

        routeNames->push_back(nextSchool);
        // add distance to next school in route
        routeDistances->push_back(minDist);

        orderedSchoolsLabels.push_back(tempSchool);

        totalDistance = totalDistance + minDist;
        collegeCount++;
    }


    // RECURSIVE CALL
    efficiencyAlgo(colleges, routeNames, routeDistances, nextSchool);
}

void pathASU::on_toolButton_startTrip_clicked()
{
    auto* souvenir  = new souvenirShop(totalDistance, orderedSchoolsName);
    souvenir -> show();
}
