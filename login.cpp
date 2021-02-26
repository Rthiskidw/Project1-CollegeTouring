#include "login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_cancel_clicked()
{
    hide();
}

void Login::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    if(username == "Admin" && password == "Admin")
    {
        QMessageBox::information(this, "Login", "Login Successful");
        loggedIn = true;
        hide();
        admin = new Admin(this);
        admin->show();
    }
    else
    {
        QMessageBox::warning(this,"Login", "Username and password is incorrect");
    }
}
