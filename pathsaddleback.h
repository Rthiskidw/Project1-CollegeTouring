#ifndef PATHSADDLEBACK_H
#define PATHSADDLEBACK_H
#include "souvenirshop.h"
#include <QWidget>

namespace Ui {
class pathSaddleback;
}

class pathSaddleback : public QWidget
{
    Q_OBJECT

public:
    explicit pathSaddleback(QWidget *parent = nullptr);
    ~pathSaddleback();

private slots:
    void on_startTrip_button_clicked();
    void on_planTrip_button_clicked();
    void on_backButton_clicked();

private:
    Ui::pathSaddleback *ui;
};

#endif // PATHSADDLEBACK_H
