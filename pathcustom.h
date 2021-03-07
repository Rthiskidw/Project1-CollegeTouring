#ifndef PATHCUSTOM_H
#define PATHCUSTOM_H
#include "souvenirshop.h"
#include "database.h"
#include "QVBoxLayout"
#include <QWidget>
#include <QDebug>
#include <QSqlQueryModel>
#include <QCheckBox>
#include <QLabel>

namespace Ui {
class pathCustom;
}

class pathCustom : public QWidget
{
    Q_OBJECT

public:
    explicit pathCustom(QWidget *parent = nullptr);
    ~pathCustom();
    void fillComboBox();
    void initializeList();
    void CheckboxChanged();

private slots:
    void on_startTrip_button_clicked();

    void on_backButton_clicked();

    void on_selectStartingCampus_activated();

    void on_planTrip_button_clicked();

private:
    Ui::pathCustom *ui;
    QVector<QCheckBox*> checkBoxVector;
    QVector<QString> collegeNamesVector;
    QVector<double> collegeDistances;
    QVector<QLabel*> collegeNamesLabelVector;
    QVector<QString> tempcollegeNamesVector;
    QVector<QLabel*> tempLabelVector;
    QVector<double> collegesByDistance;
    QString campusName;
    double totalDistance = 0;
};

#endif // PATHCUSTOM_H
