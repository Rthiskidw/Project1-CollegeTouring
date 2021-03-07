#include "pathcustom.h"
#include "ui_pathcustom.h"

pathCustom::pathCustom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pathCustom)
{
    ui->setupUi(this);
    fillComboBox();
    initializeList();
}

pathCustom::~pathCustom()
{
    delete ui;
}

void pathCustom::on_startTrip_button_clicked()
{
    QVector<QString> collegeVector = sortedCollegeNamesVector;
    for(int i = 0; i < sortedCollegeNamesVector.size();i++)
    {
        qDebug() << sortedCollegeNamesVector[i] << Qt::endl;
    }
    auto* souvenir  = new souvenirShop(totalDistance, collegeVector);
    hide();
    souvenir -> show();
}

void pathCustom::on_backButton_clicked()
{
    hide();
}

void pathCustom::fillComboBox()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT DISTINCT starting_college FROM Colleges");

    if(qry->exec())
    {
        qDebug() << "college table updated";
    }
    else
        qDebug() << "failed";

    model->setQuery(*qry);

    ui->selectStartingCampus->setModel(model);
}

void pathCustom::initializeList()
{
    QSqlQuery *query = new QSqlQuery();

    checkBoxVector.clear();
    tempLabelVector.clear();
    tempcollegeNamesVector.clear();
    collegeNamesLabelVector.clear();
    collegeNamesVector.clear();
    collegesByDistance.clear();
    sortedCollegeNamesVector.clear();

    QWidget *container = new QWidget;
    QVBoxLayout *vBoxLayout = new QVBoxLayout;

    container->setLayout(vBoxLayout);

    ui->scrollArea_selectColleges->setWidget(container);



    query->prepare("SELECT DISTINCT starting_college FROM Colleges");
    if(!query->exec())
    {
        qDebug() << "pathCustom initializeList query failed";
    }
    else
    {
        campusName = ui->selectStartingCampus->currentText();
        collegeNamesVector.push_back(campusName);

        while(query->next())
        {
            if(campusName != query->value(0).toString())
            {
                QCheckBox* checkBox = new QCheckBox(query->value(0).toString());
                QLabel *collegeLabel = new QLabel(query->value(0).toString());
                QString collegeName = (query->value(0).toString());
                checkBox->setCheckState(Qt::CheckState::Unchecked);
                checkBoxVector.push_back(checkBox);
                tempLabelVector.push_back(collegeLabel);
                tempcollegeNamesVector.push_back(collegeName);
                //connect(checkBox, &QCheckBox::stateChanged, this, &pathCustom::CheckboxChanged);
            }
        }

        for(int i = 0; i < checkBoxVector.size(); i++)
        {
            vBoxLayout->addWidget(checkBoxVector[i]);

        }
    }
}

void pathCustom::CheckboxChanged()
{
    qDebug() << "Signal caught";

    int checkedCount = 0;

    for(int i = 0; i < checkBoxVector.size(); i++)
    {
        if(checkBoxVector[i]->checkState() == Qt::CheckState::Checked)
        {
            qDebug() << tempcollegeNamesVector[i] << Qt::endl;
            collegeNamesVector.push_back(tempcollegeNamesVector[i]);
            checkedCount++;
        }
    }

    if(checkedCount == 11)
    {
        for(int i = 0; i < checkBoxVector.size(); i++)
        {
            if(checkBoxVector[i]->checkState() == Qt::CheckState::Unchecked)
            {
                checkBoxVector[i]->setDisabled(true);
            }
            qDebug() << checkBoxVector[i] << Qt::endl;
        }
    }
    else
    {
        for(int i = 0; i < checkBoxVector.size(); i++)
        {
            checkBoxVector[i]->setDisabled(false);
        }
    }
}

void pathCustom::on_selectStartingCampus_activated()
{
    initializeList();
}

void pathCustom::on_planTrip_button_clicked()
{
    CheckboxChanged();
    efficiencyAlgo(&collegeNamesVector, &sortedCollegeNamesVector, &collegesByDistance, ui->selectStartingCampus->currentText());
    QWidget *container = new QWidget;
    QVBoxLayout *vBoxLayout = new QVBoxLayout;

    container->setLayout(vBoxLayout);

    ui->scrollArea_displayTrip->setWidget(container);

    //filling scroll area with chosen schools
    for(int i = 0; i < collegeNamesLabelVector.size(); i++)
    {
        vBoxLayout->addWidget(collegeNamesLabelVector[i]);
    }
}

void pathCustom::efficiencyAlgo(QVector<QString> *colleges,
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
    QLabel* tempSchool = new QLabel(nextSchool);
    collegeNamesLabelVector.push_back(tempSchool);
    routeNames->push_back(nextSchool);
    // add distance to next school in route
    routeDistances->push_back(minDist);
    totalDistance = totalDistance + minDist;

    // RECURSIVE CALL
    efficiencyAlgo(colleges, routeNames, routeDistances, nextSchool);
}

