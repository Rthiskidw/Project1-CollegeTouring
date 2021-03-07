#ifndef PATHSADDLEBACK_H
#define PATHSADDLEBACK_H
#include "database.h"
#include "souvenirshop.h"
#include "QVBoxLayout"
#include <QWidget>
#include <qcheckbox.h>
#include <QList>
#include <QLabel>
#include <QDialog>

namespace Ui {
class pathSaddleback;
}

class pathSaddleback : public QWidget
{
    Q_OBJECT

public:
    explicit pathSaddleback(QWidget *parent = nullptr);
    ~pathSaddleback();
    void initializeList();
    void CheckboxChanged();

private slots:
    void on_startTrip_button_clicked();
    void on_planTrip_button_clicked();
    void on_backButton_clicked();
    void efficiencyAlgo();

private:
    Ui::pathSaddleback *ui;
    QVector<QLabel*> schoolLabelsVector;
    QVector<QString*> chosenSchools;
    QVector<QString> orderedSchoolsName;
    QVector<int> orderedSchoolsDistance;
    QVector<QLabel*> orderedSchoolsLabels;
    //QVector<QLabel*> orderedSchoolsDistanceLabels;
    QVector<QLabel*> chosenSchoolsLabels;


};

#endif // PATHSADDLEBACK_H
