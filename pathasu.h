#ifndef PATHASU_H
#define PATHASU_H
#include "database.h"
#include "souvenirshop.h"
#include "QVBoxLayout"
#include <QWidget>
#include <qcheckbox.h>
#include <QList>
#include <QDialog>

namespace Ui {
class pathASU;
}

class pathASU : public QWidget
{
    Q_OBJECT

public:
    explicit pathASU(QWidget *parent = nullptr);
    ~pathASU();
    void initializeList();
    void CheckboxChanged();

private slots:
    void on_toolButton_2_clicked();

private:
    Ui::pathASU *ui;
    QVector<QCheckBox*> checkBoxVector;
};

#endif // PATHASU_H
