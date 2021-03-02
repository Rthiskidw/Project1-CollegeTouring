#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
#include "database.h"
#include "addsouvenir.h"

namespace Ui {
class Admin;
}

class Admin : public QDialog
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();
    void updateColleges();
    void updateSouvenirs();
    void onInitialise();

private slots:
    void on_pushButton_updateSouvenir_clicked();
    void on_pushButton_removeSouvenir_clicked();

    void on_souvenir_tableView_clicked(const QModelIndex &index);

    void on_pushButton_addSouvenir_clicked();

    void on_pushButton_addNewColleges_clicked();

    void on_pushButton_Initialize_clicked();

private:
    Ui::Admin *ui;
    QString tempSouvenir;
    Database myDb = Database(PROJECT_PATH + "/college.db");
};

#endif // ADMIN_H
