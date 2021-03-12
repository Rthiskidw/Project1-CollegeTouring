#include "souvenirshop.h"
#include "ui_souvenirshop.h"
#include "endtour.h"
#include <QMessageBox>
#include <QVBoxLayout>

souvenirShop::souvenirShop(double distance, QVector<QString> collegesVector, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::souvenirShop)
{
    ui->setupUi(this);
    distanceTraveled = distance;
    selectedColleges = collegesVector;
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
    subCostList.append(QString::number(subCostAtCampus,'f', 2)); //adding subcost to list as a string

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

        purchasedSouvAtCampus = 0; //reseting num of souvenirs bought at each campus
        ui->label_purchasedSouvAtCampus->setText("Souvenirs Purchased Here: $" + QVariant(purchasedSouvAtCampus).toString());
        subCostAtCampus = 0; //reseting cost of souvenirs bought at each campus
        ui->label_subCostAtCampus->setText("Cost of Souvenirs Purchased Here: $" + QString::number(subCostAtCampus,'f', 2));
        collegeCount++;
    }
    else
    {
        QMessageBox::information(this, "Warning", "Your tour has ended. To continue, please click \"End Tour\"");
    }
}

void souvenirShop::on_endTour_button_clicked()
{
    if(collegeCount >= selectedColleges.size())
    {
        QString tempCost = "$" + QString::number(grandTotal, 'f', 2);
        QString tempDistance = QString::number(distanceTraveled, 'f', 2) + " miles";
        auto* endtour = new endTour(tempDistance, tempCost, selectedColleges, subCostList);
        hide();
        endtour->show();
    }
    else
    {
        QMessageBox::information(this, "Warning", "Your tour is not over. Please finish your tour before clicking \"End Tour\"");
    }
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


    customAmount =  ui->customInput->value();

    ui->customInput->setValue(1);

    for (int i = 0; i<customAmount; i++){
        grandTotal = grandTotal + souvenirCost;
        purchasedSouvAtCampus++;
        subCostAtCampus += souvenirCost;
    }

    QString customAmountStr = QString::number(customAmount);
    QString customItemPrice = QString::number(souvenirCost*customAmount);
    QLabel *souvenirName = new QLabel(customAmountStr + " x\t"+ tempSouvenir  +  "\t\t$" + customItemPrice);

    vBoxLayout->addWidget(souvenirName);


    ui->label_purchasedSouvAtCampus->setText("Souvenirs Purchased Here: " + QVariant(purchasedSouvAtCampus).toString());
    ui->label_subCostAtCampus->setText("Cost of Souvenirs Purchased Here: " + QString::number(subCostAtCampus, 'f', 2));


}

