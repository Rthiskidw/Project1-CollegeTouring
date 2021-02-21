#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QSqlDatabase>
#include <QFileInfo>
#include <QDebug>
#include <QString>

class Database
{
public:
    Database(const QString& path);
private:
    QSqlDatabase myDatabase;
    QSqlQuery qry;
};

#endif // DATABASE_H
