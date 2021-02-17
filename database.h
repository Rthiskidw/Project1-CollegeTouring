#ifndef DATABASE_H
#define DATABASE_H

#include <QMainWindow>

namespace Ui {
class database;
}

class database : public QMainWindow
{
    Q_OBJECT

public:
    explicit database(QWidget *parent = nullptr);
    ~database();

private:
    Ui::database *ui;
};

#endif // DATABASE_H
