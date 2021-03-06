#ifndef DATABASE_H
#define DATABASE_H

#include <QAbstractItemModel>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QDebug"

//ryans path - "/Users/ryans/OneDrive/Documents/Project1-CollegeTouring/"
//reeds path - "/Users/ReedWilson/reed/college/cs 1d/Project1-CollegeTouring/"
//alans path -
//quans path -
static const QString PROJECT_PATH = "/Users/ryans/OneDrive/Documents/Project1-CollegeTouring/";

class Database
{
public:
    /**
    * @brief Constructor
    *
    * Constructor sets up connection with db and opens it
    * @param path - absolute path to db file
    */
    Database(const QString &path);

    /**
    * @brief initalizes sql data table for college and inputs all data from path parameter file location
    * @param &path - filepath for DB
    * @return void - none
    */
    void InitCollegeList(const QString &path);

    /**
    * @brief initalizes sql data table for souvenir and inputs all data from path parameter file location
    * @param &path - filepath for DB
    * @return void - none
    */
    void initsouvenirList(const QString &path);

    /**
    * @brief initalizes sql data table for college distances and inputs all data from path parameter file location
    * @param &path - filepath for DB
    * @return void - none
    */
    void initDistanceList(const QString &path);

    /**
    * @brief adds a user to DB for future logins
    * @param &user - user name
    * @param &pass - password
    * @return void - none
    */
    void addUser(const QString &user, const QString &pass);

    /**
    * @brief adds a souvenir to DB for data tables
    * @param &college - college containing souvenir
    * @param &souvenirName - name of souvenir
    * @param &cost - cost of souvenir
    * @return void - none
    */
    void addSouvenir(const QString &college, const QString &souvenirName, const QString &cost);

    /**
    * @brief removes a souvenir to DB for data tables
    * @param &college - college containing souvenir
    * @param &souvenirName - name of souvenir
    * @return void - none
    */
    void removeSouvenir(const QString &souvenirName, const QString &college);

    /**
    * @brief updates souvenir to DB for data tables with new values
    * @param &college - college containing souvenir
    * @param &souvenirName - name of souvenir
    * @param &cost - cost of souvenir
    * @param &newSovenir - new object data
    * @return void - none
    */
    void updateSouvenir(const QString &souvenirName, const QString &college, const QString &spin, const QString &newsouvenir);

    /**
    * @brief adds souvenir to cart
    * @param count - quantity of items
    * @param souvenir - name of souvenir
    * @param price - cost of souvenir
    * @return void - none
    */
    void addCart(const QString trip, const QString college, const QString souvenir, const double price, const int count);

    /**
    * @brief updates total items in carts with accurate corresponding data
    * @param count - quantity of items
    * @param souvenir - name of souvenir
    * @param college - name of college selling souvenir
    * @return void - none
    */
    void updateCart(const QString college, const QString souvenir, const int count);

    /**
    * @brief returns quanitity of items in cart
    * @param souvenir - name of souvenir
    * @param college - name of college selling souvenir
    * @return int - quanity of cart
    */
    int cartQuantity(const QString college, const QString souvenir);

    /**
    * @brief delete item from cart
    * @param souvenir - name of souvenir
    * @param college - name of college selling souvenir
    * @return void - none
    */
    void removeCart(const QString college, const QString souvenir);

    /**
    * @brief adds purchase to DB and cart
    * @return void - none
    */
    void addPurchase();

    /**
    * @brief clear all items from cart
    * @return void - none
    */
    void resetCart();

    /**
    * @brief add colleges from file to DB
    * @param path - absolute path to db file souvenir
    * @return void - none
    */
    void addColleges(const QString &path);

    /**
    * @brief checks to see if the username exists
    * @param name of the user
    * @return true - username exists, false - username does not exist
    */
    bool userExists(const QString &user);

    /**
    * @brief checks to see if the souvenir exists
    * @param &name - name of souvenir
    * @param &college - college that contains souvenir
    * @return true - username exists, false - username does not exist
    */
    bool souvenirExists(const QString &name, const QString &college);

    /**
    * @brief clears database of all data
    * @return void - nothing
    */
    void clearDb();

    /**
     * @brief checks to see if Database is open
     * @return true - Database is open, false - Database is closed
     */
    bool isOpen() const;

    /**
     * @brief checks to see if the username entered is an admin
     * @param username of the user
     * @return true - will enable admin login, false - the person is not an admin
     */
    bool checkAdmin(const QString &username) const;

    /**
     * @brief Gets password from user
     * @param name of the user(s)
     * @return obtains the password from user
     */
    QString getPassword(const QString &username) const;

    /**
    * @brief adds a trip to appropiate dataTables
    * @param tripID - passed in trip ID
    * @param plannedCollege - holds selected college name
    * @param index- position for data structure
    * @return void - nothing
    */
    void addTrip(QString tripID, QString plannedCollege, int index, int distanceTo);

    /**
    * @brief returns whether tripID data exists in DB
    * @param tripID- trip id to verify
    * @return bool- whether data exists
    */
    bool tripIdExists(QString tripID);

    void createTripTable();

private:
    /**
 * @brief decalre database field memberobj
 */
    QSqlDatabase myDB;
};

#endif // DATABASE_H
