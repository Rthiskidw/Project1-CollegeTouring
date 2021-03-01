#ifndef ADDSOUVENIR_H
#define ADDSOUVENIR_H

#include <QDialog>
#include "database.h"

namespace Ui {
class addSouvenir;
}

class addSouvenir : public QDialog
{
    Q_OBJECT

public:
    explicit addSouvenir(QWidget *parent = nullptr);
    ~addSouvenir();
    void fillComboBox();

private slots:
    void on_pushButton_addNewSouvenir_clicked();

    void on_pushButton_cancelNewSouvenir_clicked();

private:
    Ui::addSouvenir *ui;
    Database myDb = Database();
};

#endif // ADDSOUVENIR_H
