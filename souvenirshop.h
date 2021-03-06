#ifndef SOUVENIRSHOP_H
#define SOUVENIRSHOP_H

#include <QWidget>
#include <QVector>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include <QLabel>

namespace Ui {
class souvenirShop;
}

class souvenirShop : public QWidget
{
    Q_OBJECT

public:
    explicit souvenirShop(QVector<QString> collegeVector, QWidget *parent = nullptr);
    ~souvenirShop();

private slots:
    void on_nextCollege_button_clicked();

    void on_endTour_button_clicked();

    void on_souvenir_tableView_clicked(const QModelIndex &index);

    void on_buy_button_clicked();

private:
    Ui::souvenirShop *ui;

    double distanceTraveled = 0;    // total distance traveled during trip
    double grandTotal = 0;          // grand total spent on souvenirs
    int collegeCount = 0;           // Used for vector index to keep track of which college to display
    QVector<QString> selectedColleges; // Names of each selected college
    QVector<double> collegeTotals;  // total for each college
    QVector<int> souvenirQuants;    // souvenir quantities
    QVector<QLabel*> purchasedSouvenirs;
    QString tempSouvenir;
    QString cost;
    double souvenirCost;
};

#endif // SOUVENIRSHOP_H
