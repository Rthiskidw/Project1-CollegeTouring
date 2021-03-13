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
    /**
    * @brief explicit default Constructor
    *
    * Constructor intializes UI for pathCustom
    * Calls initializeList()
    * Calls fillComboBox()
    *
    * @param *parent - for QDialog
    */
    explicit pathCustom(QWidget *parent = nullptr);

    /**
    * @brief Destructor
    *
    * Close the pathCustom UI
    */
    ~pathCustom();

    /**
    * @brief Class Method to fill combo box
    *
    * fills combo box with starting colleges
    */
    void fillComboBox();

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
    * @brief Button Method to start trip
    *
    * starts trip
    * calls souvenirShop constructor
    * opens souvenirShop window
    */
    void on_startTrip_button_clicked();

    /**
    * @brief Button Method to close pathCustom window
    *
    * closes pathCustom window and returns to choosePath window
    */
    void on_backButton_clicked();

    /**
    * @brief On Activiated Method for Combo Box
    *
    * when combo box is activated, calls initializeList() to reset list
    */
    void on_selectStartingCampus_activated();

    /**
    * @brief Button Method to plan trip
    *
    * plans trip and sorts colleges in most efficient order
    */
    void on_planTrip_button_clicked();

private:
    /**
    * @brief points to pathCustom UI
    */
    Ui::pathCustom *ui;

    /**
    * @brief vector for check box elements
    */
    QVector<QCheckBox*> checkBoxVector;

    /**
    * @brief vector for selected college names
    */
    QVector<QString> collegeNamesVector;

    /**
    * @brief vector for college distances
    */
    QVector<double> collegeDistances;

    /**
    * @brief vector for college names labels
    */
    QVector<QLabel*> collegeNamesLabelVector;

    /**
    * @brief vector for all college names
    */
    QVector<QString> tempcollegeNamesVector;

    /**
    * @brief vector for college distances
    */
    QVector<double> collegesByDistance;

    /**
    * @brief vector for sorted colleges in most efficient order
    */
    QVector<QString> sortedCollegeNamesVector;

    /**
    * @brief name for current campus
    */
    QString campusName;

    /**
    * @brief total distance traveled
    */
    double totalDistance = 0;
};

#endif // PATHCUSTOM_H
