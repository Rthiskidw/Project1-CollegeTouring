#ifndef PATHCUSTOM_H
#define PATHCUSTOM_H
#include "souvenirshop.h"
#include <QWidget>

namespace Ui {
class pathCustom;
}

class pathCustom : public QWidget
{
    Q_OBJECT

public:
    explicit pathCustom(QWidget *parent = nullptr);
    ~pathCustom();

private slots:
    void on_toolButton_2_clicked();

private:
    Ui::pathCustom *ui;
};

#endif // PATHCUSTOM_H
