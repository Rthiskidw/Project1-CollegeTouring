#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include "choosepath.h"
#include "database.h"
#include "login.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
    * @brief explicit default Constructor
    *
    * Constructor intializes UI for MainWindow
    *
    * @param *parent - for QDialog
    */
    MainWindow(QWidget *parent = nullptr);

    /**
    * @brief Destructor
    *
    * Close the MainWindow UI
    */
    ~MainWindow();

private slots:
    /**
    * @brief Button Method to open choosePath window
    *
    * calls choosePath constructor
    * opens choosePath window
    */
    void on_startButton_clicked();

    /**
    * @brief On Action Method to login as administrator
    *
    * calls Login constructor
    * opens login window to login as administrator
    */
    void on_actionLogin_triggered();

private:
    /**
    * @brief points to MainWindow UI
    */
    Ui::MainWindow *ui;

    /**
    * @brief assigns myDb to predefined PROJECT_PATH constant
    */
    Database myDb = Database(PROJECT_PATH + "/college.db");
};
#endif // MAINWINDOW_H
