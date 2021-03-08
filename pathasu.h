#ifndef PATHASU_H
#define PATHASU_H
#include "database.h"
#include "souvenirshop.h"
#include "QVBoxLayout"
#include <QWidget>
#include <qcheckbox.h>
#include <QList>
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

private slots:
    void on_backButton_clicked();

    void on_pushButton_planTrip_clicked();

private:
    Ui::pathASU *ui;
    QVector<QCheckBox*> checkBoxVector;
    QVector<QLabel*> orderedSchoolsLabels;
    QVector<QString> chosenSchools;
    QVector<QString> orderedSchoolsName;
    QVector<double> orderedSchoolsDistance;
    Database myDb = Database(PROJECT_PATH + "/college.db");
    double totalDistance = 0;
};

#endif // PATHASU_H
