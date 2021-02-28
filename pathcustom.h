#ifndef PATHCUSTOM_H
#define PATHCUSTOM_H

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

private:
    Ui::pathCustom *ui;
};

#endif // PATHCUSTOM_H
