#ifndef TRIPCUSTOM_H
#define TRIPCUSTOM_H

#include <QQuickItem>
#include "mainWindow.h"


namespace Ui {
class tripCustom;
}

class tripCustom : public QWidget
{
    Q_OBJECT

public:
    explicit tripCustom(QWidget *parent = nullptr);
    ~tripCustom();

private slots:
    void on_uciButton_clicked();

private:
    Ui::tripCustom *ui;
};
#endif // TRIPCUSTOM_H
