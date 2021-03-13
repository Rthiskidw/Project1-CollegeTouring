#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
#include "database.h"
#include "addsouvenir.h"

namespace Ui {
class Admin;
}

class Admin : public QDialog
{
    Q_OBJECT

public:
    /**
    * @brief explicit default Constructor
    *
    * Constructor intializes UI for Admin
    * calls UpdateSouvenirs()
    * calls UpdateColleges()
    *
    * @param *parent - for QDialog
    */
    explicit Admin(QWidget *parent = nullptr);

    /**
    * @brief Destructor
    *
    * Close the Admin UI
    */
    ~Admin();

    /**
    * @brief Class Method to update colleges
    *
    * updates query for entire Colleges chart and sets ui Model
    */
    void updateColleges();

    /**
    * @brief Class Method to update souvenirs
    *
    * updates query for entire Souvenirs chart and sets ui Model
    */
    void updateSouvenirs();

private slots:
    /**
    * @brief Button Method to update a souvenir
    *
    * executes process for updating a souvenir in database
    */
    void on_pushButton_updateSouvenir_clicked();

    /**
    * @brief Button Method to remove a souvenir
    *
    * executes process for removing a souvenir from database
    */
    void on_pushButton_removeSouvenir_clicked();

    /**
    * @brief Table Clicked Method to update a souvenir
    *
    * executes process for making souvenir table clickable
    * sets value for UI elements based off information from souvenir table
    *
    * @param &index - model index from chart
    */
    void on_souvenir_tableView_clicked(const QModelIndex &index);

    /**
    * @brief Button Method to show addSouvenir UI window
    *
    * calls constructor for addSouvenir UI window
    * opens addSouvenir UI window
    */
    void on_pushButton_addSouvenir_clicked();

    /**
    * @brief Button Method to add new colleges
    *
    * executes process for adding new colleges to database
    */
    void on_pushButton_addNewColleges_clicked();

    /**
    * @brief Button Method to clear all colleges
    *
    * executes process for removing all colleges in database
    */
    void on_pushButton_clearColleges_clicked();

private:
    /**
    * @brief points to Admin UI
    */
    Ui::Admin *ui;

    /**
    * @brief variable hold souvenir names
    */
    QString tempSouvenir;

    /**
    * @brief assigns myDb to predefined PROJECT_PATH constant
    */
    Database myDb = Database(PROJECT_PATH + "/college.db");
};

#endif // ADMIN_H
