#include "addsouvenir.h"
#include "ui_addsouvenir.h"

addSouvenir::addSouvenir(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addSouvenir)
{
    ui->setupUi(this);
    fillComboBox();
}

addSouvenir::~addSouvenir()
{
    delete ui;
}

void addSouvenir::fillComboBox()
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

    ui->comboBox_addCollegeName->setModel(model);
}

void addSouvenir::on_pushButton_addNewSouvenir_clicked()
{
    bool success = true;
    QString collegeName = ui->comboBox_addCollegeName->currentText();


    if(ui->lineEdit_addSouvenirName->text() == "")
    {
        ui->lineEdit_addSouvenirName->setPlaceholderText("souvinir name empty!");
        success = false;
    }

    if(myDb.souvenirExists(ui->lineEdit_addSouvenirName->text(), collegeName))
    {
        qDebug() << collegeName;
        qDebug() << ui->lineEdit_addSouvenirName->text();
        ui->lineEdit_addSouvenirName->setText("");
        ui->lineEdit_addSouvenirName->setPlaceholderText("souvinir name exists!");
        success = false;
    }

    if(success)
    {
        myDb.addSouvenir(collegeName,ui->lineEdit_addSouvenirName->text(),ui->lineEdit_addSouvenirCost->text());
        hide();
    }
}

void addSouvenir::on_pushButton_cancelNewSouvenir_clicked()
{
    hide();
}
