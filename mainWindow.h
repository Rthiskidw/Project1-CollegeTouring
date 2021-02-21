#ifndef MAINWINDOW_H
#define MAINWINDOW_H
// checking commit
// Pls don't fk anything up

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionLogin_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
