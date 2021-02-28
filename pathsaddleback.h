#ifndef PATHSADDLEBACK_H
#define PATHSADDLEBACK_H

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

private:
    Ui::pathSaddleback *ui;
};

#endif // PATHSADDLEBACK_H
