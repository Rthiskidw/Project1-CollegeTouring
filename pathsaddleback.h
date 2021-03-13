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
    /**
    * @brief explicit default Constructor
    *
    * Constructor intializes UI for pathSaddleback
    * Calls initializeList()
    *
    * @param *parent - for QDialog
    */
    explicit pathSaddleback(QWidget *parent = nullptr);

    /**
    * @brief Destructor
    *
    * Close the pathSaddleback UI
    */
    ~pathSaddleback();

    /**
    * @brief Class Method to initialize college list
    *
    * initializes college list
    */
    void initializeList();

    /**
    * @brief Class Method to check if check boxes changed
    *
    * Checks if check boxes checked value changed
    * Puts all checked colleges into a vector
    */
    void CheckboxChanged();

private slots:
    /**
    * @brief Button Method to start trip
    *
    * starts trip
    * calls souvenirShop constructor
    * opens souvenirShop window
    */
    void on_startTrip_button_clicked();

    /**
    * @brief Button Method to plan trip
    *
    * plans trip and sorts colleges in most efficient order
    */
    void on_planTrip_button_clicked();

    /**
    * @brief Button Method to close pathSaddleback window
    *
    * closes pathSaddleback window and returns to choosePath window
    */
    void on_backButton_clicked();

    /**
    * @brief Class Method to recursively choose most efficient trip
    *
    * Takes selected colleges and recursively chooses the most efficient trip
    */
    void efficiencyAlgo(QVector<QString> *colleges,
                     QVector<QString> *routeNames,
                     QVector<double> *routeDistances,
                     QString currentCollege);

private:
    /**
    * @brief points to pathSaddleback UI
    */
    Ui::pathSaddleback *ui;

    /**
    * @brief vector for all college name labels
    */
    QVector<QLabel*> schoolLabelsVector;

    /**
    * @brief vector for selected school names
    */
    QVector<QString> chosenSchools;

    /**
    * @brief vector for ordered school names(sorted by efficiency)
    */
    QVector<QString> orderedSchoolsName;

    /**
    * @brief vector for ordered school distances(sorted by efficiency)
    */
    QVector<double> orderedSchoolsDistance;

    /**
    * @brief vector for ordered school name labels(sorted by efficiency)
    */
    QVector<QLabel*> orderedSchoolsLabels;

    /**
    * @brief assigns myDb to predefined PROJECT_PATH constant
    */
    Database myDb = Database(PROJECT_PATH + "/college.db");

    /**
    * @brief total distance traveled
    */
    double totalDistance = 0;
};

#endif // PATHSADDLEBACK_H
