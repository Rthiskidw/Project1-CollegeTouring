#ifndef PATHASU_H
#define PATHASU_H

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

private:
    Ui::pathASU *ui;
};

#endif // PATHASU_H
