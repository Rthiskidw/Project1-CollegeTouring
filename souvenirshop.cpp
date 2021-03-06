#include "souvenirshop.h"
#include "ui_souvenirshop.h"
#include <QMessageBox>
#include <QVBoxLayout>

souvenirShop::souvenirShop(QVector<QString> collegesVector, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::souvenirShop)
{
    ui->setupUi(this);
    selectedColleges = collegesVector;
    purchasedSouvenirCount = 0;
    ui->label_collegeName->setText(selectedColleges[collegeCount]);

    QSqlQueryModel* model=new QSqlQueryModel();

    QSqlQuery* qry=new QSqlQuery();

    qry->prepare("SELECT souvenirs, cost FROM Souvenirs WHERE college= (:college)");
    qry->bindValue(":college", selectedColleges[collegeCount]);

    if(qry->exec())
    {
        qDebug() << "Souvenirs updated";
    }

    model->setQuery(*qry);

    ui->souvenir_tableView->setModel(model);
    ui->souvenir_tableView->setColumnWidth(0, 195);

    //initliazing purchased souvenirs scroll Area

    container = new QWidget;
    vBoxLayout = new QVBoxLayout;

    container->setLayout(vBoxLayout);

    ui->scrollArea_purchased->setWidget(container);

    collegeCount++;
}

souvenirShop::~souvenirShop()
{
    delete ui;
}

void souvenirShop::on_nextCollege_button_clicked()
{
    if(collegeCount < selectedColleges.size())
    {
        ui->label_collegeName->setText(selectedColleges[collegeCount]);

        QSqlQueryModel* model=new QSqlQueryModel();

        QSqlQuery* qry=new QSqlQuery();

        qry->prepare("SELECT souvenirs, cost FROM Souvenirs WHERE college= (:college)");
        qry->bindValue(":college", selectedColleges[collegeCount]);

        if(qry->exec())
        {
            qDebug() << "Souvenirs updated";
        }

        model->setQuery(*qry);

        ui->souvenir_tableView->setModel(model);
        ui->souvenir_tableView->setColumnWidth(0, 195);

        collegeCount++;
    }
    else
    {
        QMessageBox::information(this, "Warning", "Your tour has ended. To continue, please click \"End Tour\"");
    }
}

void souvenirShop::on_endTour_button_clicked()
{

}

void souvenirShop::on_souvenir_tableView_clicked(const QModelIndex &index)
{
    if(index.isValid())
    {
        int row = index.row();
        tempSouvenir = index.sibling(row, 0).data().toString();
        souvenirCost = index.sibling(row, 1).data().toString().replace("$", "").toDouble();
        cost = index.sibling(row, 1).data().toString();

        qDebug() << tempSouvenir << Qt::endl << souvenirCost << Qt::endl;
    }
}

void souvenirShop::on_buy_button_clicked()
{
    QLabel *souvenirName = new QLabel(tempSouvenir + "\t\t" + cost);

    purchasedSouvenirs.push_back(souvenirName);

    purchasedSouvenirCount++;

    vBoxLayout->addWidget(purchasedSouvenirs[purchasedSouvenirCount - 1]);

    grandTotal = grandTotal + souvenirCost;
}
