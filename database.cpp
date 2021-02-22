#include <QSqlRecord>
#include <QDir>
#include <QSqlField>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlError>
#include "database.h"
#include "mainWindow.h"

Database* Database::instance = nullptr;

/**
 * @brief Database::getInstance
 *
 * returns a pointer to Database
 * If one is not created, one is created
 *
 * @return instance
 */
Database* Database::getInstance() {
    if (instance == nullptr)
        instance = new Database;

    return instance;
}

/**
 * @brief Database::Database
 * creates a connection to a SQLite database file.  Verfies that
 * it is open
 */
Database::Database(): QSqlDatabase(addDatabase("QSQLITE")) {
    QDir dir(QDir::currentPath()); //gets current path
    QString current;//holds new path


    while(dir.dirName() != "College-Tour") {
        dir.cdUp();
    }

    //adds path to database
    current = dir.absolutePath() + "/DB/College_DB.db";
    qDebug() << "Path is " + current;

    //sets database path
    setDatabaseName(current);
    QFileInfo existingDatabaseInfo(current);

    //outputs if path exists
    if (existingDatabaseInfo.exists())
    {
        qDebug() << "Database file is open\n";
        open();
    }
    else
        qDebug() << "Datebase file is not open\n";

}

