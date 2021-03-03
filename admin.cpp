#include "admin.h"
#include "ui_admin.h"
#include "database.h"

Admin::Admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
    updateColleges();
    updateSouvenirs();
}

Admin::~Admin()
{
    delete ui;
}

void Admin::updateColleges()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT * FROM Colleges");

    if(qry->exec())
    {
        qDebug() << "Colleges updated";
    }

    model->setQuery(*qry);

    ui->college_tableView->setModel(model);
    ui->college_tableView->resizeColumnsToContents();
}

void Admin::updateSouvenirs()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT * FROM Souvenirs");

    if(qry->exec())
    {
        qDebug() << "Souvenirs updated";
    }

    model->setQuery(*qry);

    ui->souvenir_tableView->setModel(model);
    ui->souvenir_tableView->setColumnWidth(0, 220);
}

void Admin::on_pushButton_updateSouvenir_clicked()
{
    bool success = true;

    if(ui->lineEdit_souvenirName->text() == "")
    {
        ui->lineEdit_souvenirName->setPlaceholderText("souvenir name empty!");
        success = false;
    }

    if(!myDb.souvenirExists(ui->lineEdit_souvenirName->text(), ui->label_collegeName->text()))
    {
        if(success)
        {
            myDb.updateSouvenir(tempSouvenir, ui->label_collegeName->text(),ui->lineEdit_souvenirPrice->text(), ui->lineEdit_souvenirName->text());
        }
        else
        {
            qDebug() << "Remove error";
        }
    }
    else if(tempSouvenir == ui->lineEdit_souvenirName->text())
    {
        if(success)
        {
            myDb.updateSouvenir(tempSouvenir, ui->label_collegeName->text(),ui->lineEdit_souvenirPrice->text(), ui->lineEdit_souvenirName->text());
        }
        else
        {
            qDebug() << "Remove error";
        }
        updateSouvenirs();
    }
}

void Admin::on_pushButton_removeSouvenir_clicked()
{
    bool success = true;

    if(ui->lineEdit_souvenirName->text() == "")
    {
        ui->lineEdit_souvenirName->setPlaceholderText("souvenir name empty!");
        success = false;
    }

    if(!myDb.souvenirExists(ui->lineEdit_souvenirName->text(), ui->label_collegeName->text()))
    {
       ui->lineEdit_souvenirName->setText("");
       ui->lineEdit_souvenirName->setPlaceholderText("souvenir doesn't exist!");
       success = false;
    }

    if(myDb.souvenirExists(ui->lineEdit_souvenirName->text(), ui->label_collegeName->text()) && success)
    {
        myDb.removeSouvenir(ui->lineEdit_souvenirName->text(), ui->label_collegeName->text());
        ui->lineEdit_souvenirName->setText("");
        ui->lineEdit_souvenirName->setPlaceholderText("souvenir name");
    }
    else
    {
        qDebug() << "Error removing Souvenir";
    }
    updateSouvenirs();
}

void Admin::on_souvenir_tableView_clicked(const QModelIndex &index)
{
    if(index.isValid())
    {
        int row = index.row();
        QString firstText = index.sibling(row, 0).data().toString();
        QString secondText = index.sibling(row, 1).data().toString();
        tempSouvenir = index.sibling(row, 1).data().toString();
        QString thirdText = index.sibling(row, 2).data().toString();

        ui->lineEdit_souvenirName->setText(secondText);
        ui->label_collegeName->setText(firstText);
        ui->lineEdit_souvenirPrice->setText(thirdText);
    }
}

void Admin::onInitialise()
{
        myDb.clearDb();

        myDb.InitCollegeList(PROJECT_PATH + "/College_Campus_Distances_and_Souvenirs.xlsx");

        myDb.initsouvenirList(PROJECT_PATH + "/College_Campus_Distances_and_Souvenirs.xlsx");

        myDb.initDistanceList(PROJECT_PATH + "/College_Campus_Distances_and_Souvenirs.xlsx");

    updateColleges();
    updateSouvenirs();
}

void Admin::on_pushButton_addSouvenir_clicked()
{
    addSouvenir adding;
    adding.setModal(true);
    adding.exec();
    updateSouvenirs();
}

void Admin::on_pushButton_addNewColleges_clicked()
{
    myDb.addColleges(PROJECT_PATH + "/College_Campus_Distances_and_Souvenirs.xlsx");

    updateColleges();
    updateSouvenirs();
}

void Admin::on_pushButton_Initialize_clicked()
{
    //onInitialise();
}
