#include "database.h"
#include "admin.h"

Database::Database(const QString &path)
{
    myDB = QSqlDatabase::addDatabase("QSQLITE");

    myDB.setDatabaseName(path);

    if(!myDB.open())
    {
        qDebug() << "Error: can't connect to database!" << Qt::endl;

    }
    else
    {
        qDebug() << "Database: Connected" << Qt::endl;
    }

    QSqlQuery query;
    query.prepare("PRAGMA foreign_keys = ON");
    query.exec();
}

void Database::InitCollegeList(const QString &path)//path to the excel file
{
   QSqlDatabase fileDB = QSqlDatabase::addDatabase("QODBC", "xlsx_connection");
   fileDB.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};DBQ=" + path);

   if(fileDB.open())
   {
       qDebug() << "Excel connection successful" << Qt::endl;

       QSqlQuery *query = new QSqlQuery(fileDB);
       query->exec("select * from [" + QString("Distances") + "$A1:A111]");   //Distances is the sheet name!

       QSqlQuery * querytoDb = new QSqlQuery(myDB);

       querytoDb->exec("CREATE TABLE Colleges ("
                       "collegeName TEXT);");

       QString compare = "";

       while(query->next())
       {

           if(myDB.open())
           {

               querytoDb->prepare("INSERT INTO Colleges(collegeName) values(:collegeName)");

               QString column1 = query->value(0).toString();

               if(compare != column1)
               {
                   querytoDb->bindValue(":collegeName",query->value(0).toString());
                   qDebug() << querytoDb->exec();

               }
               compare = column1;
           }
       }

       fileDB.close();
   }
}

void Database::initsouvenirList(const QString &path)
{
    QSqlDatabase fileDB = QSqlDatabase::addDatabase("QODBC", "xlsx_connection");
    fileDB.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};DBQ=" + path);

    if(fileDB.open())
    {
        qDebug() << "Excel connection successful" << Qt::endl;

        QSqlQuery *query = new QSqlQuery(fileDB);
        query->exec("select * from [" + QString("souvenirs") + "$A1:C61]");

        QSqlQuery * querytoDb = new QSqlQuery(myDB);

        querytoDb->exec("CREATE TABLE souvenirs ("
                        "collegeName TEXT,"
                        "souvenirName TEXT,"
                        "cost DOUBLE);");

        QString tempColumn1;
        QString check;

        while(query->next())
        {
            if(myDB.open())
            {
                querytoDb->prepare("INSERT INTO souvenirs(collegeName, souvenirName, cost) VALUES(:collegeName, :souvenirName, :cost)");

                QString column1 = query->value(0).toString();
                check = column1;
                if(column1 == "" || column1 == " ")
                {
                    column1 = tempColumn1;
                }

                QString column2 = query->value(1).toString();

                double column3 = query->value(2).toDouble();

                if(check == "" && column2 != "")
                {
                    querytoDb->bindValue(":collegeName", column1);
                    querytoDb->bindValue(":souvenirName",column2);
                    querytoDb->bindValue(":cost",column3);
                    qDebug() << querytoDb->exec();

                }

                tempColumn1 = column1;
            }
        }
        fileDB.close();
    }
}

void Database::initDistanceList(const QString &path)
{
    QSqlDatabase fileDB = QSqlDatabase::addDatabase("QODBC", "xlsx_connection");
    fileDB.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};DBQ=" + path);

    if(fileDB.open())
    {
        qDebug() << "Excel connection successful" << Qt::endl;

        QSqlQuery *query = new QSqlQuery(fileDB);
        query->exec("select * from [" + QString("Distances") + "$A1:C111]");

        QSqlQuery * querytoDb = new QSqlQuery(myDB);

        querytoDb->exec("CREATE TABLE Distances ("
                        "starting_college TEXT,"
                        "ending_college TEXT,"
                        "distance INTEGER);");

        while(query->next())
        {
            //QSqlDatabase myDB = QSqlDatabase::database("sqlite_connection");

            if(myDB.open())
            {
                querytoDb->prepare("INSERT INTO Distances(starting_college, ending_college, distance) VALUES(:starting_college, :ending_college, :distance)");

                QString column1 = query->value(0).toString();

                QString column2 = query->value(1).toString();

                int column3 = query->value(2).toInt();

                querytoDb->bindValue(":starting_college", column1);
                querytoDb->bindValue(":ending_college",column2);
                querytoDb->bindValue(":distance",column3);
                qDebug() << querytoDb->exec();
            }
        }
        fileDB.close();
    }

}

//QSqlDatabase::removeDatabase("xlsx_connection"); // need to put this out of scope of the initialised db

void Database::removeSouvenir(const QString &souvenirName, const QString &college)
{
    QSqlQuery *query = new QSqlQuery(myDB);

    if(souvenirExists(souvenirName, college))
    {
        if(myDB.open())
        {
            query->prepare("DELETE FROM souvenirs WHERE (souvenirs) = (:souvenirs)");
            query->bindValue(":souvenirs", souvenirName);

            if(query->exec())
                qDebug() << "souvenir delete success!";
            else
                qDebug() << "souvenir delete failed!";
        }
    }

}

void Database::addSouvenir(const QString &college, const QString &souvenirName, const QString &cost)
{
    QSqlQuery *query = new QSqlQuery(myDB);

    if(!souvenirExists(souvenirName, college))
    {
        if(myDB.open())
        {
            query->prepare("INSERT INTO souvenirs(college, souvenirs, cost) VALUES(:college, :souvenirs, :cost)");
            query->bindValue(":college", college);
            query->bindValue(":souvenirs", souvenirName);
            query->bindValue(":cost", cost);

            if(query->exec())
                qDebug() << "souvenir add success!";
            else
                qDebug() << "souvenir add failed!";
        }
    }
    else
    {
        qDebug() << "name exists!";
    }
}

void Database::updateSouvenir(const QString &souvenirName, const QString &college, const QString &spin, const QString &newsouvenir)
{
    QSqlQuery *query = new QSqlQuery(myDB);


    if(myDB.open())
    {
        query->prepare("UPDATE souvenirs SET (souvenirs, cost) = (:newsouvenirName, :cost) "
                       "WHERE (college, souvenirs) = (:college, :souvenirs)");
        query->bindValue(":newsouvenirName", newsouvenir);
        query->bindValue(":college", college);
        query->bindValue(":souvenirs", souvenirName);
        query->bindValue(":cost", spin);

        if(query->exec())
        {
            qDebug() << "UPDATE WORKED" << Qt::endl;
        }
        else
        {
            qDebug() << "UPDATE failed: " << query->lastError() << Qt::endl;
        }
    }
}


bool Database::souvenirExists(const QString &name, const QString &college)
{
    bool exists = false;

    QSqlQuery *checkQuery = new QSqlQuery(myDB);

    checkQuery->prepare("SELECT souvenirs FROM souvenirs WHERE (college, souvenirs) = (:college, :souvenirs)");
    checkQuery->bindValue(":souvenirs", name);
    checkQuery->bindValue(":college", college);


    if(checkQuery->exec())
    {
        if(checkQuery->next())
        {
            exists = true;
            QString souvenirName = checkQuery->value("souvenirs").toString();
            QString college = checkQuery->value("college").toString();
            qDebug() << souvenirName << " " << college;
        }
    }
    else
    {
        qDebug() << "souvenir exists failed: " << checkQuery->lastError();
    }

    return exists;
}

void Database::clearColleges()
{
    QSqlQuery *deleteQuery = new QSqlQuery(myDB);

    deleteQuery->prepare("DROP TABLE IF EXISTS Colleges");

    deleteQuery->exec();

    createDataTables();
}

bool Database::isOpen() const
{
    return myDB.isOpen();
}

QStringList Database::parseFile(QString &string) {
    enum State {Normal, Quote} state = Normal;
    QStringList fields;
    QString value;

    for (int i = 0; i < string.size(); i++)
    {
        QChar current = string.at(i);

        // Normal state
        if (state == Normal)
        {
            // Comma
            if (current == ',')
            {
                // Save field
                fields.append(value);
                value.clear();
            }

            // Double-quote
            else if (current == '"')
                state = Quote;

            // Other character
            else
                value += current;
        }

        // In-quote state
        else if (state == Quote)
        {
            // Another double-quote
            if (current == '"')
            {
                if (i+1 < string.size())
                {
                    QChar next = string.at(i+1);

                    // A double double-quote?
                    if (next == '"')
                    {
                        value += '"';
                        i++;
                    }
                    else
                        state = Normal;
                }
            }

            // Other character
            else
                value += current;
        }
    }
    if (!value.isEmpty())
        fields.append(value);

    return fields;
}

/**
 * @brief Database::addNewColleges
 * @param list
 */
void Database::addNewColleges(QStringList list) {
    QSqlQuery* query = new QSqlQuery(myDB);

    //adds collge to College Table
    query->prepare("INSERT INTO Colleges (starting_college, ending_college, distances)"
                  " VALUES (:starting, :ending, :dist)");

    //binds values
    query->bindValue(":starting", list.at(0));
    query->bindValue(":ending", list.at(1));
    query->bindValue(":dist", list.at(2));

    //executes query
    if (query->exec()) {
        qDebug() << "Query was executed";
    } else {
        qDebug() << "Query was not executed";
    }
}

void Database::createDataTables()
{
    QSqlQuery *query = new QSqlQuery(myDB);

    if(myDB.open())
    {
        query->exec("CREATE TABLE Colleges ("
                    "starting_college TEXT,"
                    "ending_college TEXT,"
                    "distances INT);");
    }
}
