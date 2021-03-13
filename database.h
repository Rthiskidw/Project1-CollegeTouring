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
//alans path - "D:\\Qt Projects\\CS1D\\Project1-CollegeTouring"
//quans path - "C:/Users/Quan/Documents/Project1-CollegeTouring"

static const QString PROJECT_PATH = "/Users/ryans/OneDrive/Documents/Project1-CollegeTouring/";


class Database
{
public:

    /**
    * @brief explicit default Constructor
    *
    * Constructor adds database
    * sets database path
    * checks if database is open
    *
    * @param &path - for database path
    */
    Database(const QString &path);

    /**
    * @brief Method to add new Souvenir
    *
    * adds new souvenir to database
    *
    * @param &college - name of college
    * @param &souvenirName - name of souvenir
    * @param &cost - cost of souvenir
    */
    void addSouvenir(const QString &college, const QString &souvenirName, const QString &cost);

    /**
    * @brief Method to remove a Souvenir
    *
    * removes a souvenir from database
    *
    * @param &souvenirName - name of souvenir
    * @param &college - name of college
    */
    void removeSouvenir(const QString &souvenirName, const QString &college);

    /**
    * @brief Method to update a Souvenir
    *
    * updates a current souvenir in database
    *
    * @param &souvenirName - name of souvenir
    * @param &college - name of college
    * @param &spin - cost of souvenir
    * @param &newsouvenir - name of new souvenir
    */
    void updateSouvenir(const QString &souvenirName, const QString &college, const QString &spin, const QString &newsouvenir);

    /**
    * @brief Method to check if souvenir exists
    *
    * checks to see if souvenir already exists in database
    *
    * @param &name - name of souvenir
    * @param &college - name of college
    */
    bool souvenirExists(const QString &name, const QString &college);

    /**
    * @brief Method to clear all colleges
    *
    * clears all colleges from database
    */
    void clearColleges();

    /**
    * @brief Method to check if database is open
    *
    * checks to see if database is open
    */
    bool isOpen() const;

    /**
    * @brief Method to add new colleges
    *
    * adds new colleges to database
    *
    * @param list - list of colleges to add
    */
    void addNewColleges(QStringList list);

    /**
    * @brief Method to parse a CSV file
    *
    * parses a CSV file and extracts information
    *
    * @param &string - string to parse
    */
    QStringList parseFile(QString &string);

    /**
    * @brief Method to create data tables
    *
    * creates data tables for information in database
    */
    void createDataTables();

private:
    /**
    * @brief declaree database object
    */
    QSqlDatabase myDB;
};

#endif // DATABASE_H
