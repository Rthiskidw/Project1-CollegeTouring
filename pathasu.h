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
    /**
    * @brief explicit default Constructor
    *
    * Constructor intializes UI for pathASU
    * Calls initializeList()
    *
    * @param *parent - for QDialog
    */
    explicit pathASU(QWidget *parent = nullptr);

    /**
    * @brief Destructor
    *
    * Close the pathASU UI
    */
    ~pathASU();

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

    /**
    * @brief Class Method to recursively choose most efficient trip
    *
    * Takes selected colleges and recursively chooses the most efficient trip
    */
    void efficiencyAlgo(QVector<QString> *colleges,
                     QVector<QString> *routeNames,
                     QVector<double> *routeDistances,
                     QString currentCollege);

private slots:
    /**
    * @brief Button Method to close pathASU window
    *
    * closes pathASU window and returns to choosePath window
    */
    void on_backButton_clicked();

    /**
    * @brief Button Method to plan trip
    *
    * plans trip and sorts colleges in most efficient order
    */
    void on_pushButton_planTrip_clicked();

    /**
    * @brief Button Method to start trip
    *
    * starts trip
    * calls souvenirShop constructor
    * opens souvenirShop window
    */
    void on_toolButton_startTrip_clicked();

private:
    /**
    * @brief points to pathASU UI
    */
    Ui::pathASU *ui;

    /**
    * @brief vector of all college name labels
    */
    QVector<QLabel*> orderedSchoolsLabels;

    /**
    * @brief vector of selected school names
    */
    QVector<QString> chosenSchools;

    /**
    * @brief sorted vector with ordered school names
    */
    QVector<QString> orderedSchoolsName;

    /**
    * @brief vector to store distance of each college
    */
    QVector<double> orderedSchoolsDistance;

    /**
    * @brief assigns myDb to predefined PROJECT_PATH constant
    */
    Database myDb = Database(PROJECT_PATH + "/college.db");

    /**
    * @brief total distance of trip
    */
    double totalDistance = 0;

    /**
    * @brief campus number
    */
    int collegeCount = 1;

    /**
    * @brief user input number of colleges to visit
    */
    int userInput = 0;
};

#endif // PATHASU_H
