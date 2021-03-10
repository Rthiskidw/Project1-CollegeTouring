#ifndef ENDTOUR_H
#define ENDTOUR_H

#include <QWidget>
#include "QVBoxLayout"
#include <QLabel>

namespace Ui {
class endTour;
}

class endTour : public QWidget
{
    Q_OBJECT

public:
    explicit endTour(QString totalDistance, QString totalCost, QVector<QString> collegeNames,
                     QStringList costAtEachCampus,QWidget *parent = nullptr);
    ~endTour();

private slots:
    void on_done_button_clicked();

private:
    Ui::endTour *ui;
    QLabel *collegeLabel;
    QVector<QLabel*> labelVector;
};

#endif // ENDTOUR_H
