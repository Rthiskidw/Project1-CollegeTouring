#include "login.h"
#include "ui_login.h"
#include "mainWindow.h"
#include <QMessageBox>
#include <QPixmap>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

//Sign in button clicked , username and password check
void login::on_pushButton_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    QString uppercaseUsername;
    uppercaseUsername = username.toUpper();

    if(uppercaseUsername == "A" && password == "A")
    {
        QMessageBox::information(this, "Login", "Username and password is correct");
        hide();
        MainWindow* mainwindow = new MainWindow(this);
        mainwindow->show();//since valid usernam and password we can show the main window
        mainwindow->hide();
    }
    else
    {
        QMessageBox::warning(this,"Login", "Username and password is not correct");
    }
}
