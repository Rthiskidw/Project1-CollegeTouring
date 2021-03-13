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
    /**
    * @brief explicit Constructor
    *
    * Constructor intializes UI for endTour
    *
    * @param *parent - for QDialog
    * @param totalDistance - total distance traveled
    * @param totalCost - total amount spent
    * @param collegeNames - names of all campuses visited
    * @param costAtEachCampus - total spent at each campus
    */
    explicit endTour(QString totalDistance, QString totalCost, QVector<QString> collegeNames,
                     QStringList costAtEachCampus,QWidget *parent = nullptr);

    /**
    * @brief Destructor
    *
    * Close the endTour UI
    */
    ~endTour();

private slots:
    /**
    * @brief Button Method to close endTour window
    *
    * closes endTour window
    */
    void on_done_button_clicked();

private:
    /**
    * @brief points to endTour UI
    */
    Ui::endTour *ui;

    /**
    * @brief temp label for college name
    */
    QLabel *collegeLabel;

    /**
    * @brief vector to hold labels of all college names
    */
    QVector<QLabel*> labelVector;
};

#endif // ENDTOUR_H
