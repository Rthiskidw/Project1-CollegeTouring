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

    Database(const QString &path);

    void InitCollegeList(const QString &path);

    void initsouvenirList(const QString &path);

    void initDistanceList(const QString &path);

    void addSouvenir(const QString &college, const QString &souvenirName, const QString &cost);

    void removeSouvenir(const QString &souvenirName, const QString &college);

    void updateSouvenir(const QString &souvenirName, const QString &college, const QString &spin, const QString &newsouvenir);

    bool souvenirExists(const QString &name, const QString &college);

    void clearColleges();

    bool isOpen() const;

    void addNewColleges(QStringList list);

    QStringList parseFile(QString &string);

    void createDataTables();

private:
    /**
 * @brief decalre database field memberobj
 */
    QSqlDatabase myDB;
};

#endif // DATABASE_H
