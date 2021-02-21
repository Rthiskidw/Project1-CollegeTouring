#include "database.h"

Database::Database(const QString& path)
{
    myDatabase = QSqlDatabase::addDatabase("QSQLITE");

    myDatabase.setDatabaseName(path);

    if(myDatabase.open()) {
            qDebug() << "Connected to the database." << Qt::endl;
        }
        else{
            qDebug() << "Database not connected." << Qt::endl;
        }




}
