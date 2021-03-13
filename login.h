#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QMessageBox>
#include "ui_login.h"
#include "mainWindow.h"
#include "admin.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    /**
    * @brief explicit default Constructor
    *
    * Constructor intializes UI for Login
    *
    * @param *parent - for QDialog
    */
    explicit Login(QWidget *parent = nullptr);

    /**
    * @brief Destructor
    *
    * Close the Login UI
    */
    ~Login();

private slots:
    /**
    * @brief Button Method to cancel login
    *
    * cancels login and closes Login window
    */
    void on_pushButton_cancel_clicked();

    /**
    * @brief Button Method to login as administrator
    *
    * opens login window to log in as administrator
    */
    void on_pushButton_login_clicked();

private:
    /**
    * @brief points to Login UI
    */
    Ui::Login *ui;

    /**
    * @brief declaration of Admin object
    */
    Admin *admin;

    /**
    * @brief assigns myDb to predefined PROJECT_PATH constant
    */
    Database myDb = Database(PROJECT_PATH + "/college.db");
};

#endif // LOGIN_H
