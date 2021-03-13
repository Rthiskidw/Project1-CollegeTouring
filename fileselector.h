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
    /**
    * @brief explicit default Constructor
    *
    * Constructor intializes UI for fileSelector
    *
    * @param *parent - for QDialog
    */
    explicit fileSelector(QWidget *parent = nullptr);

    /**
    * @brief Destructor
    *
    * Close the fileSelector UI
    */
    ~fileSelector();

private slots:
    /**
    * @brief Folder tree Clicked Method
    *
    * executes process for making folder tree clickable
    * allows user to choose input file
    *
    * @param &index - model index from folder tree
    */
    void on_folderTree_clicked(const QModelIndex &index);

    /**
    * @brief File View Clicked Method
    *
    * allows user view selected file
    *
    * @param &index - model index from folder tree
    */
    void on_fileView_clicked(const QModelIndex &index);

    /**
    * @brief Button Method to add new colleges
    *
    * executes process for adding new colleges to database
    */
    void on_addButt_clicked();

    /**
    * @brief Button Method to cancel fileSelector
    *
    * closes fileSelector window
    */
    void on_pushButton_cancel_clicked();

private:
    /**
    * @brief points to fileSelector UI
    */
    Ui::fileSelector *ui;

    /**
    * @brief used for file directory
    */
    QFileSystemModel *dirModel;

    /**
    * @brief used for file modal
    */
    QFileSystemModel *fileModel;

    /**
    * @brief used to store path to input file
    */
    QString pathToFile;

    /**
    * @brief used to see if file has already been added
    */
    bool added;
};

#endif // FILESELECTOR_H
