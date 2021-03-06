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
    QSqlQuery *query = new QSqlQuery();

    query->prepare("SELECT DISTINCT distance FROM Colleges WHERE college= (:college)");

    if(!query->exec())
    {
        qDebug() << "pathCustom initializeList query failed";
    }
    else
    {
        while(query->next())
        {
            totalDistance = totalDistance + query->value(1).toDouble();

        }
    }

    QVector<QString> collegeVector = collegeNamesVector;
    auto* souvenir  = new souvenirShop(collegeVector);
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
        QLabel *startingCollegeLabel = new QLabel(campusName);
        collegeNamesLabelVector.push_back(startingCollegeLabel);
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
                connect(checkBox, &QCheckBox::stateChanged, this, &pathCustom::CheckboxChanged);
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
            collegeNamesLabelVector.push_back(tempLabelVector[i]);
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
