#include "fileselector.h"
#include "ui_fileselector.h"
#include "database.h"
#include "admin.h"
#include <QDebug>

fileSelector::fileSelector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fileSelector)
{
    ui->setupUi(this);

    //used to check if file has been added
    added = false;

    //hides add button and fileTable
    ui->addButt->hide();

    //sets up paths for the folder Trees
    QString sPath = "";
    dirModel  = new QFileSystemModel(this);
    dirModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirModel->setRootPath(sPath);
    ui->folderTree->setModel(dirModel);
    fileModel = new QFileSystemModel(this);
    fileModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    fileModel->setRootPath(sPath);
    ui->fileView->setModel(fileModel);

    ui->folderTree->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
}

fileSelector::~fileSelector()
{
    delete ui;
}

void fileSelector::on_folderTree_clicked(const QModelIndex &index)
{
    QString sPath = dirModel->fileInfo(index).absoluteFilePath();
    ui->fileView->setRootIndex(fileModel->setRootPath(sPath));
}

void fileSelector::on_fileView_clicked(const QModelIndex &index)
{
    //clear errorLabel
    ui->ErrorLabel->clear();

    //sets up tableWidget
    ui->fileTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->fileTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->fileTable->setColumnCount(3);
    QStringList headers;
    headers << "Start" << "End" << "Distance";
    ui->fileTable->setHorizontalHeaderLabels(headers);

    Database myDb = Database(PROJECT_PATH + "/college.db"); //db instance
    //sets path
    QString path = fileModel->fileInfo(index).absoluteFilePath();
    pathToFile = path;
    bool correctFileType = path.endsWith(".csv");
    qDebug() << path;
    //checks if file is correct
    if (!correctFileType)
        ui->ErrorLabel->setText("Please select a .csv file");
    else {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly)) {
                qDebug() << file.errorString();
            }
        else {
            qDebug() << "file opened";

            //reads file and outputs info to table
            while (!file.atEnd())
            {
                QString test = QString(file.readLine());
                QStringList toAdd = myDb.parseFile(test);

                QTableWidgetItem *start = new QTableWidgetItem(toAdd.at(0));
                QTableWidgetItem *end = new QTableWidgetItem(toAdd.at(1));
                QTableWidgetItem *dist = new QTableWidgetItem(toAdd.at(2));
                ui->fileTable->insertRow(ui->fileTable->rowCount());
                ui->fileTable->setItem(ui->fileTable->rowCount() - 1, 0, start);
                ui->fileTable->setItem(ui->fileTable->rowCount() - 1, 1, end);
                ui->fileTable->setItem(ui->fileTable->rowCount() - 1, 2, dist);

                ui->ErrorLabel->setText("Click 'Add' to add the information below to the database");
            }
            ui->addButt->show();
        }

    }
}

void fileSelector::on_addButt_clicked()
{
    //parses and added file contents if not yet added
    if (!added)
    {
    Database myDb = Database(PROJECT_PATH + "/college.db"); //db instance

    //checks if file can open
    QFile file(pathToFile);
    if (!file.open(QIODevice::ReadOnly))
            qDebug() << file.errorString();
    else {
        qDebug() << "File is open";

        //reads each line of the file and parses the contents to DB
        while (!file.atEnd())
        {
            QString test = QString(file.readLine());
            QStringList toAdd = myDb.parseFile(test);
            myDb.addNewColleges(toAdd);
        }

        //confirmation message
        ui->ErrorLabel->setText("New Colleges added to database");
        added = true;

        Admin* admin = new Admin();
        admin->updateColleges();
        admin->show();
        hide();
    }
    }
}

void fileSelector::on_pushButton_cancel_clicked()
{
    Admin* admin = new Admin();
    admin->show();
    hide();
}
