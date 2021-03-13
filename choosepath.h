#ifndef CHOOSEPATH_H
#define CHOOSEPATH_H

#include <QWidget>
#include "mainWindow.h"
#include "pathsaddleback.h"
#include "pathasu.h"
#include "pathcustom.h"

namespace Ui {
class ChoosePath;
}

class ChoosePath : public QWidget
{
    Q_OBJECT

public:
    /**
    * @brief explicit default Constructor
    *
    * Constructor intializes UI for ChoosePath
    *
    * @param *parent - for QDialog
    */
    explicit ChoosePath(QWidget *parent = nullptr);

    /**
    * @brief Destructor
    *
    * Close the ChoosePath UI
    */
    ~ChoosePath();

private slots:
    /**
    * @brief Button Method to show pathSaddlback window
    *
    * calls pathSaddleback constructor
    * opens pathSaddleback window
    */
    void on_uciButton_clicked();

    /**
    * @brief Button Method to show pathASU window
    *
    * calls pathASU constructor
    * opens pathASU window
    */
    void on_pickNumSchoolButton_clicked();

    /**
    * @brief Button Method to show pathCustom window
    *
    * calls pathCustom constructor
    * opens pathCustom window
    */
    void on_customTourButton_clicked();

    /**
    * @brief Button Method to show mainWindow window
    *
    * closes current ChoosePath window
    * shows mainWindow window
    */
    void on_backButton_clicked();

private:
    /**
    * @brief points to ChoosePath UI
    */
    Ui::ChoosePath *ui;
};

#endif // CHOOSEPATH_H
