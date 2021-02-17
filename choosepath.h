#ifndef CHOOSEPATH_H
#define CHOOSEPATH_H

#include <QWidget>

namespace Ui {
class ChoosePath;
}

class ChoosePath : public QWidget
{
    Q_OBJECT

public:
    explicit ChoosePath(QWidget *parent = nullptr);
    ~ChoosePath();

private:
    Ui::ChoosePath *ui;
};

#endif // CHOOSEPATH_H
