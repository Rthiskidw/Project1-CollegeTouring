#ifndef SOUVENIRSHOP_H
#define SOUVENIRSHOP_H

#include <QWidget>

namespace Ui {
class souvenirShop;
}

class souvenirShop : public QWidget
{
    Q_OBJECT

public:
    explicit souvenirShop(QWidget *parent = nullptr);
    ~souvenirShop();

private:
    Ui::souvenirShop *ui;
};

#endif // SOUVENIRSHOP_H
