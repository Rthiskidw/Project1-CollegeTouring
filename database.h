#ifndef DATABASE_H
#define DATABASE_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class database;
}

class database : public QMainWindow
{
    Q_OBJECT

public:
    explicit database(QWidget *parent = nullptr);
    ~database();

private slots:
    void on_pushButton_clicked();

private:
    Ui::database *ui;
    QSqlDatabase myDataBase;
};

#endif // DATABASE_H
