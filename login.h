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
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pushButton_cancel_clicked();
    void on_pushButton_login_clicked();

private:
    Ui::Login *ui;
    bool loggedIn = false;
    Admin *admin;
    Database myDb = Database(PROJECT_PATH);
};

#endif // LOGIN_H
