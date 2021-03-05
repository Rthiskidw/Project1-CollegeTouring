#ifndef SOUVENIRSHOP_H
#define SOUVENIRSHOP_H

#include <QWidget>
#include <QVector>

namespace Ui {
class souvenirShop;
}

class souvenirShop : public QWidget
{
    Q_OBJECT

public:
    explicit souvenirShop(QVector<QString> collegeVector, QWidget *parent = nullptr);
    ~souvenirShop();

private:
    Ui::souvenirShop *ui;

    double distanceTraveled = 0;    // total distance traveled during trip
    double grandTotal = 0;          // grand total spent on souvenirs
    QVector<double> collegeTotals;  // total for each college
    QVector<int> souvenirQuants;    // souvenir quantities
};

#endif // SOUVENIRSHOP_H
