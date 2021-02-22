#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include "mainWindow.h"

class Database: public QSqlDatabase
{
public:
    static Database* getInstance();
private:
    Database();
    static Database* instance;
    QSqlQuery qry;
};

#endif // DATABASE_H
