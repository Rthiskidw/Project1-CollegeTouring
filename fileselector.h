#ifndef FILESELECTOR_H
#define FILESELECTOR_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QFileSystemModel>

namespace Ui {
class fileSelector;
}

class fileSelector : public QWidget
{
    Q_OBJECT

public:
    explicit fileSelector(QWidget *parent = nullptr);
    ~fileSelector();

private slots:
    void on_folderTree_clicked(const QModelIndex &index);

    void on_fileView_clicked(const QModelIndex &index);

    void on_addButt_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::fileSelector *ui;
    QFileSystemModel *dirModel;
    QFileSystemModel *fileModel;
    QString pathToFile;
    bool added;
};

#endif // FILESELECTOR_H
