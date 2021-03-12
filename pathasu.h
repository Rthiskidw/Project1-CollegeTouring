#ifndef PATHASU_H
#define PATHASU_H
#include "database.h"
#include "souvenirshop.h"
#include "QVBoxLayout"
#include <QWidget>
#include <QList>
#include <QMessageBox>
#include <QDialog>

namespace Ui {
class pathASU;
}

class pathASU : public QWidget
{
    Q_OBJECT

public:
    explicit pathASU(QWidget *parent = nullptr);
    ~pathASU();
    void initializeList();
    void CheckboxChanged();
    void efficiencyAlgo(QVector<QString> *colleges,
                     QVector<QString> *routeNames,
                     QVector<double> *routeDistances,
                     QString currentCollege);

private slots:
    void on_backButton_clicked();

    void on_pushButton_planTrip_clicked();

    void on_toolButton_startTrip_clicked();

private:
    Ui::pathASU *ui;
    QVector<QLabel*> orderedSchoolsLabels;
    QVector<QString> chosenSchools;
    QVector<QString> orderedSchoolsName;
    QVector<double> orderedSchoolsDistance;
    Database myDb = Database(PROJECT_PATH + "/college.db");
    double totalDistance = 0;
    int collegeCount = 1;
    int userInput = 0;
};

#endif // PATHASU_H
