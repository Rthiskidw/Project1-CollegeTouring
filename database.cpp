#include "database.h"
#include "ui_database.h"
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

database::database(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::database)
{
    ui->setupUi(this);

    //creating an sqlite data base called myDataBase
    myDataBase = QSqlDatabase::addDatabase("QSQLITE");

    //associating database with the college.db within our project folder
    myDataBase.setDatabaseName("/Users/ReedWilson/reed/college/cs 1d/Project1_CollegeTouring/college.db");

    //confirming whether or not the database was successfully opened
//    if (!myDataBase.open()){
//        ui->label->setText("Failed to open.");
//    }
//    else{
//        ui->label->setText("Connected!.");
//    }
}

database::~database()
{
    delete ui;
}

void database::on_pushButton_clicked()
{
    QString username, password;
    username=ui->lineEdit_username->text();
    password=ui->lineEdit_password->text();

    //confirming whether or not the database was successfully opened
    if (!myDataBase.open()){
        qDebug() << "Failed to open database!";
        return;
    }
    else{
        qDebug() << "Successfully opened database!";
    }

    QSqlQuery qry;

    if(qry.exec("select * from distances where StartingCollege ='"+username+"'and EndingCollege ='"+password+"'")){
        int count = 0;

        while(qry.next()){
            count++;
        }
        if (count == 1){
            ui->label_status->setText("username and password are correct!");
        }
        if (count >1){
            ui->label_status->setText("DUPLICATE username and password are correct!");
        }
        if (count <1){
            ui->label_status->setText("username and password are NOT correct!");
        }
        ui->label_status->setText("SHEESH");
    }


}
