/**
  * Header file that defines the methods and instance variables in errordialog.cpp
  */
#ifndef ERRORDIALOG_H
#define ERRORDIALOG_H

#include <QDialog>
#include <vector>
#include <string>
namespace Ui {
class ErrorDialog;
}


class ErrorDialog : public QDialog
{
    Q_OBJECT

public:

//ErrorDialog constructor
    explicit ErrorDialog(QWidget *parent = 0);

//ErrorDialog deconstructor
    ~ErrorDialog();

//Sets the data to be displayed in the ErrorDialog window
    void setData(std::vector<std::string>errorVector);

//Clears all data in the window after a new file is opened
    void clearData();

private:
    Ui::ErrorDialog *ui;
};

#endif // ERRORDIALOG_H
