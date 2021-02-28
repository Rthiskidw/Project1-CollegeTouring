#ifndef CHOOSEPATH_H
#define CHOOSEPATH_H

#include <QWidget>
#include "mainWindow.h"
#include "pathsaddleback.h"
#include "pathasu.h"
#include "pathcustom.h"

namespace Ui {
class ChoosePath;
}

class ChoosePath : public QWidget
{
    Q_OBJECT

public:
    explicit ChoosePath(QWidget *parent = nullptr);
    ~ChoosePath();

private slots:
    void on_uciButton_clicked();

    void on_pickNumSchoolButton_clicked();

    void on_customTourButton_clicked();

private:
    Ui::ChoosePath *ui;
};

#endif // CHOOSEPATH_H
