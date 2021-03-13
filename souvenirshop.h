#ifndef SOUVENIRSHOP_H
#define SOUVENIRSHOP_H

#include <QWidget>
#include <QVector>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>

namespace Ui {
class souvenirShop;
}

class souvenirShop : public QWidget
{
    Q_OBJECT

public:
    /**
    * @brief explicit Constructor
    *
    * Constructor intializes UI for souvenirShop
    *
    * @param *parent - for QDialog
    * @param distance - distance traveled
    * @param collegeVector - vector of college names to visit
    */
    explicit souvenirShop(double distance, QVector<QString> collegeVector, QWidget *parent = nullptr);

    /**
    * @brief Destructor
    *
    * Close the souvenirShop UI
    */
    ~souvenirShop();

private slots:
    /**
    * @brief Button Method to visit next college
    *
    * moves to souvenir college for next college in trip
    */
    void on_nextCollege_button_clicked();

    /**
    * @brief Button Method to end tour
    *
    * ends tour
    * calls endTour constructor
    * displays endTour window
    */
    void on_endTour_button_clicked();

    /**
    * @brief On Table View Clicked Method
    *
    * allows user to click on table of souvenirs to choose which one they want to purchase
    */
    void on_souvenir_tableView_clicked(const QModelIndex &index);

    /**
    * @brief Button Method to buy a souvenir
    *
    * purchases souvenir for user and adds cost to total
    */
    void on_buy_button_clicked();

private:
    /**
    * @brief points to souvenirShop UI
    */
    Ui::souvenirShop *ui;

    /**
    * @brief total distance traveled
    */
    double distanceTraveled = 0;

    /**
    * @brief total cost for trip
    */
    double grandTotal = 0;

    /**
    * @brief count to keep track of colleges
    */
    int collegeCount = 0;

    /**
    * @brief number of souvenirs purchased at current campus
    */
    int purchasedSouvAtCampus = 0;

    /**
    * @brief cost at current campus
    */
    double subCostAtCampus = 0;

    /**
    * @brief List to hold costs from each campus
    */
    QStringList subCostList;

    /**
    * @brief vector of selected college names
    */
    QVector<QString> selectedColleges;

    /**
    * @brief temporarily holds name of a souvenir
    */
    QString tempSouvenir;

    /**
    * @brief cost of souvenir(string)
    */
    QString cost;

    /**
    * @brief cost of souvenir(double)
    */
    double souvenirCost;

    /**
    * @brief Amount of souvenirs purchased in total
    */
    int souvenirAmount;

    /**
    * @brief Used to manage widgets
    */
    QVBoxLayout *vBoxLayout;

    /**
    * @brief Container for output
    */
    QWidget *container;

    /**
    * @brief Variable to check if souvenir has been clicked
    */
    bool clicked = false;

    /**
    * @brief custom amount of souvenirs to be purchased
    */
    int customAmount = 0;
};

#endif // SOUVENIRSHOP_H
