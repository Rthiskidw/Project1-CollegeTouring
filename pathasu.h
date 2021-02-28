#ifndef PATHASU_H
#define PATHASU_H
#include "souvenirshop.h"
#include <QWidget>

namespace Ui {
class pathASU;
}

class pathASU : public QWidget
{
    Q_OBJECT

public:
    explicit pathASU(QWidget *parent = nullptr);
    ~pathASU();

private slots:
    void on_toolButton_2_clicked();

private:
    Ui::pathASU *ui;
};

#endif // PATHASU_H
