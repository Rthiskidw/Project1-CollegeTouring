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
   // QSqlQuery *query = new QSqlQuery();
    efficiencyAlgo();

    QWidget *container = new QWidget;
    QVBoxLayout *vBoxLayout = new QVBoxLayout;

    container->setLayout(vBoxLayout);

    ui->scrollArea_chosenSchools->setWidget(container);

    //filling scroll area with chosen schools
    for(int i = 0; i < orderedSchoolsLabels.size(); i++)
    {
        vBoxLayout->addWidget(orderedSchoolsLabels[i]);
    }


    // -------------------------------------------------------- TESTING ---------------------------------------------------------

}

void pathSaddleback::efficiencyAlgo()
{
    // Used in the efficiency algorithm to keep track of items before sorting
    QVector<int> tempDistanceVector;
    QVector<QString> tempNameVector;
    QVector<int> orderedDistanceIndexes;

    QSqlQuery *query = new QSqlQuery();
    orderedSchoolsDistance.clear();
    orderedSchoolsName.clear();
    orderedDistanceIndexes.clear();

    QString schoolName = "";
    int i = 0;
    int distances = 0;
    int distTo = 0;

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
             // qDebug() << (query->value(1).toInt());
             distances = query->value(1).toInt();
             schoolName = query->value(0).toString();

             tempDistanceVector.push_back(distances);                   // Used to temporarily hold the original distances
             orderedSchoolsDistance.push_back(distances);               // Will be sorted and compared with tempDistanceVector
             tempNameVector.push_back(schoolName);                      // Used to temporarily hold the unsorted school names
             //orderedSchoolsName.push_back(schoolName);
        }
    }

//    for(int i = 0; i < orderedSchoolsName.size(); i++)
//    {
//        qDebug() << orderedSchoolsName[i];
//    }
    std::sort(orderedSchoolsDistance.begin(), orderedSchoolsDistance.end());        // Sorts the vector from least to greatest

    while(orderedDistanceIndexes.size() != orderedSchoolsDistance.size())           // while the new vector size does not equal the orderedSchoolsDistance vector
    {
        for(int i = 0; i < orderedSchoolsDistance.size(); i++)
        {
            for(int k = 0; k < tempDistanceVector.size(); k++)
            {
                if(orderedSchoolsDistance[i] == tempDistanceVector[k])              // If the index of the sorted vector finds the same distance in the unsorted vector
                {
                    orderedDistanceIndexes.push_back(k);                            // then push the index of the found distance in unsorted vector into orderedDistance vector
                }
            }
        }
    }

    //--------------------------------------------------------
    // DON'T DELETE!!! USED FOR TESTING
//    for(int i = 0; i < orderedDistanceIndexes.size(); i++)
//    {
//        qDebug() << orderedDistanceIndexes[i];
//    }

//    for(int i = 0; i < tempDistanceVector.size(); i++)
//    {
//        qDebug() << "The school distance at index 0 for tempDistance is: " << tempDistanceVector[orderedDistanceIndexes[i]] << " and the distance for ordered is: " << orderedSchoolsDistance[i];
//    }
//    qDebug() << "";
//    for(int i = 0; i < orderedSchoolsDistance.size(); i++)
//    {
//        qDebug() << orderedSchoolsDistance[i];
//    }

    for(int i = 0; i < tempNameVector.size(); i++)
    {
        orderedSchoolsName.push_back(tempNameVector[orderedDistanceIndexes[i]]);            // pushes the school names in order by distance into orderedSchoolsName vector
        // qDebug() << orderedSchoolsName[i];                                                  // School names are now in order in the orderedSchoolsName vector
    }

    for(int i = 0; i < orderedSchoolsDistance.size(); i++)
    {
        QString tempName = orderedSchoolsName[i];
        int tempDistance = orderedSchoolsDistance[i];
        QLabel* school = new QLabel(tempName + " [" + QString::number(tempDistance) + " miles from Saddleback]");
        orderedSchoolsLabels.push_back(school);
    }

//    for(int i = 0; i < orderedSchoolsName.size(); i++)
//    {
//        QString temp = orderedSchoolsName[i];
//        QLabel* school = new QLabel("" + temp);
//        orderedSchoolsNameLabels.push_back(school);
//    }
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
             schoolLabelsVector.push_back(school);
        }

        for(int i = 0; i < schoolLabelsVector.size(); i++)
        {
            vBoxLayout->addWidget(schoolLabelsVector[i]);
        }
    }
}


