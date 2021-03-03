#include "database.h"

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

int Database::cartQuantity(const QString college, const QString souvenir)
{
    int count = 0;
    QSqlQuery *query = new QSqlQuery(myDB);
    if(myDB.open())
    {
        query->prepare("SELECT quantity FROM Cart WHERE (college, souvenir) = (:college, :souvenir)");
        query->bindValue(":college", college);
        query->bindValue(":souvenir", souvenir);

        if(query->exec())
            qDebug() << "selected quantity";
        else
            qDebug() << "coudn't select quantity";

        while(query->next())
        {
            count = query->value(0).toInt();
            qDebug() << count;

            return count;
        }
    }

    return 0;
}

void Database::removeCart(const QString college, const QString souvenir)
{
    int count = cartQuantity(college, souvenir);
    count--;

    if(count != 0)
    {
        updateCart(college, souvenir, count);
    }
    else
    {
        QSqlQuery *query = new QSqlQuery(myDB);

        if(myDB.open())
        {
            query->prepare("DELETE FROM Cart WHERE (college, souvenir) = (:college, :souvenir)");
            query->bindValue(":college", college);
            query->bindValue(":souvenir", souvenir);

            if(query->exec())
                qDebug() << "cart delete success!";
            else
                qDebug() << "cart delete failed!";
        }
    }
}

void Database::addPurchase()
{
    QSqlQuery *query = new QSqlQuery(myDB);

    if(myDB.open())
    {
        query->prepare("INSERT INTO Purchases SELECT * FROM Cart");

        if(query->exec())
            qDebug() << "added to purchases!";
        else
            qDebug() << "coudn't add to purchases!";
    }
}

void Database::resetCart()
{
    QSqlQuery *query = new QSqlQuery(myDB);

    if(myDB.open())
    {
        query->prepare("DELETE FROM cart");

        if(query->exec())
            qDebug() << "Delete cART!";
        else
            qDebug() << "coudln't delete cart!";
    }
}

void Database::addCart(const QString trip, const QString college, const QString souvenir, const double price, const int count)
{
   QSqlQuery *query = new QSqlQuery(myDB);

   if(myDB.open())
   {
       query->prepare("INSERT INTO Cart(tripID, college, souvenir, price, quantity) VALUES(:tripID, :college, :souvenir, :price, :quantity)");
       query->bindValue(":tripID", trip);
       query->bindValue(":college", college);
       query->bindValue(":souvenir", souvenir);
       query->bindValue(":price", price);
       query->bindValue(":quantity",count);

       if(query->exec())
           qDebug() << "purchase add success!";
       else
           qDebug() << "pruchase add failed!";
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

void Database::updateCart(const QString college, const QString souvenir, const int count)
{
    QSqlQuery *query = new QSqlQuery(myDB);

    if(myDB.open())
    {
        query->prepare("UPDATE Cart SET (quantity) = (:quantity) WHERE (college, souvenir) = (:college, :souvenir)");
        query->bindValue(":college", college);
        query->bindValue(":souvenir", souvenir);
        query->bindValue(":quantity", count);

        if(query->exec())
            qDebug() << "UPDATE cart";
        else
            qDebug() << "UPDATE failed: " << query->lastError() << Qt::endl;
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

void Database::addUser(const QString &user, const QString &pass)
{
    QSqlQuery *query = new QSqlQuery(myDB);
    QString userVal = "User";

   if(!userExists(user))
   {
    if(myDB.open())
    {
        query->exec("CREATE TABLE Logins ("
                    "Username TEXT,"
                    "Password TEXT,"
                    "UserValue TEXT);");

        query->prepare("INSERT INTO Logins(Username, Password, UserValue) VALUES(:Username, :Password, :UserValue)");

        query->bindValue(":Username", user);
        query->bindValue(":Password", pass);
        query->bindValue(":UserValue", userVal);
        qDebug() << query->exec();
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

bool Database::userExists(const QString &user)
{
    bool exists = false;

    QSqlQuery *checkQuery = new QSqlQuery(myDB);

    checkQuery->prepare("SELECT Username FROM Logins WHERE (Username) = (:Username)");
    checkQuery->bindValue(":Username", user);

    if(checkQuery->exec())
    {
        if(checkQuery->next())
        {
                exists = true;
                QString userName = checkQuery->value("Username").toString();
                qDebug() << userName;
        }
    }
    else
    {
        qDebug() << "person exists failed: " << checkQuery->lastError();
    }

    return exists;
}

void Database::clearDb()
{
    QSqlQuery *deleteQuery = new QSqlQuery(myDB);

    deleteQuery->prepare("DROP TABLE IF EXISTS Colleges");

    deleteQuery->exec();

    deleteQuery->prepare("DROP TABLE IF EXISTS Distances");

    deleteQuery->exec();

    deleteQuery->prepare("DROP TABLE IF EXISTS souvenirs");

    deleteQuery->exec();

}

bool Database::isOpen() const
{
    return myDB.isOpen();
}

bool Database::checkAdmin(const QString &username) const
{
    bool admin = false;

    QSqlQuery *checkQuery = new QSqlQuery(myDB);

    checkQuery->prepare("SELECT UserValue FROM logins where (Username) = (:Username)");
    checkQuery->bindValue(":Username", username);

    if(checkQuery->exec())
    {
        if(checkQuery->next())
        {
            QString userVal = checkQuery->value("UserValue").toString();

            if(userVal == "admin")
            {
                admin = true;
            }
            qDebug() << admin;
        }
    }
    else
    {
        qDebug() << "Admin exists failed:";

    }

    if(admin)
    {
        qDebug() << "Admin";
    }

    return admin;
}

QString Database::getPassword(const QString &username) const
{
    QString password = "ksaflkzfsdjfsflkzfsjlkfxzjkjfklsz";
    QSqlQuery *getQuery = new QSqlQuery(myDB);
        getQuery->prepare("SELECT Password FROM logins WHERE (Username) = (:Username)");
        getQuery->bindValue(":Username", username);

        if (getQuery->exec())
        {
            if (getQuery->next())
            {
                password = getQuery->value("Password").toString();
                qDebug() << password;
            }
            else
            {
                qDebug() << "next query fail: " << getQuery->lastError();
            }
        }
        else
        {
            qDebug() << "person 1exists failed: " << getQuery->lastError();
        }

        return password;
}

void Database::addColleges(const QString &path)
{
    QSqlDatabase fileDB = QSqlDatabase::addDatabase("QODBC", "xlsx_connection");
    fileDB.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};DBQ=" + path);

    if(fileDB.open())
    {
        qDebug() << "Excel connection successful" << Qt::endl;

        QSqlQuery *query = new QSqlQuery(fileDB);
        query->exec("select * from [" + QString("New Campuses") + "$A2:C47]");

        QSqlQuery * querytoDb = new QSqlQuery(myDB);
        QSqlQuery * querytoList = new QSqlQuery(myDB);

        while(query->next())
        {
            if(myDB.open())
            {
                qDebug() << "Database loading..." << Qt::endl;
                querytoDb->prepare("INSERT INTO Distances(starting_college, ending_college, distance) VALUES(:starting_college, :ending_college, :distance)");
                querytoList->prepare("INSERT OR REPLACE INTO Colleges(collegeName) values(:collegeName)");

                QString column1 = query->value(0).toString();
                QString column2 = query->value(1).toString();

                int column3 = query->value(2).toInt();

                querytoDb->bindValue(":starting_college", column1);
                querytoDb->bindValue(":ending_college",column2);
                querytoDb->bindValue(":distance",column3);
                qDebug() << querytoDb->exec();

                {
                    querytoList->bindValue(":collegeName",query->value(0).toString());
                    qDebug() << querytoList->exec();
                }
            }
        }
        fileDB.close();
    }
}

void Database::createTripTable()
{
    QSqlQuery *query = new QSqlQuery(myDB);
    QString userVal = "User";

    if(myDB.open())
    {
        query->exec("CREATE TABLE Trips ("
                    "tripID TEXT,"
                    "college TEXT,"
                    "tripProgress INT,"
                    "distanceToNext INT);");

        query->exec("CREATE TABLE Purchases ("
                    "tripID TEXT,"
                    "college TEXT,"
                    "souvenir TEXT,"
                    "price DOUBLE,"
                    "quantity INTEGER);");
    }
}

void Database::addTrip(QString tripID, QString plannedCollege, int index, int distanceTo)
{
    QSqlQuery *query = new QSqlQuery(myDB);

    if(myDB.open())
    {
        query->prepare("INSERT INTO Trips(tripID, college, tripProgress, distanceToNext) VALUES(:tripID, :college, :int, :distanceToNext)");

        query->bindValue(":tripID", tripID);
        query->bindValue(":college", plannedCollege);
        query->bindValue(":int", (index + 1));
        query->bindValue(":distanceToNext", distanceTo);
        qDebug() << query->exec();
    }
}

bool Database::tripIdExists(QString tripID)
{
    bool exists = false;

    QSqlQuery *checkQuery = new QSqlQuery(myDB);

    checkQuery->prepare("SELECT tripID FROM Trips WHERE (tripID) = (:tripID)");
    checkQuery->bindValue(":tripID", tripID);

    if(checkQuery->exec())
    {
        if(checkQuery->next())
        {
                exists = true;
        }
    }
    else
    {
        qDebug() << "trip id does not exist";
    }

    return exists;
}
