#ifndef SOUVENIRSHOP_H
#define SOUVENIRSHOP_H

#include <QWidget>
#include <QVector>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>

namespace Ui {
class souvenirShop;
}

class souvenirShop : public QWidget
{
    Q_OBJECT

public:
    explicit souvenirShop(double distance, QVector<QString> collegeVector, QWidget *parent = nullptr);
    ~souvenirShop();

private slots:
    void on_nextCollege_button_clicked();

    void on_endTour_button_clicked();

    void on_souvenir_tableView_clicked(const QModelIndex &index);

    void on_buy_button_clicked();

private:
    Ui::souvenirShop *ui;

    double distanceTraveled = 0;       // total distance traveled during trip
    double grandTotal = 0;             // grand total spent on souvenirs
    int collegeCount = 0;              // Used for vector index to keep track of which college to display
    int purchasedSouvAtCampus = 0;     //number of souvenirs bought at each campus
    double subCostAtCampus = 0;        //sub total cost of souvenirs bought at each campus
    QStringList subCostList;         //sub total cost of souvenirs bought at each campus as strings
    int subCostIndex = 0;              //index of subcost array
    QVector<QString> selectedColleges; // Names of each selected college
    QVector<double> collegeTotals;     // total for each college
    QVector<int> souvenirQuants;       // souvenir quantities
    QVector<QLabel*> purchasedSouvenirs;
    QString tempSouvenir;
    QString cost;
    double souvenirCost;
    int purchasedSouvenirCount;
    QVBoxLayout *vBoxLayout;
    QWidget *container ;

};

#endif // SOUVENIRSHOP_H
