/**
  * Author: Team HoneyDew
  * Computer Science 3307, Group Project
  * December 9, 2015
  * Header file that defines the methods and instance variables in errordialog.cpp
  */
#ifndef ERRORDIALOG_H
#define ERRORDIALOG_H

#include <QDialog>
#include <vector>
#include <string>

//Defines that the Ui namespace will be used in order to help define the qdialog object
namespace Ui
{
class ErrorDialog;
}

//Defines the ErrorDialog object as a QObject
class ErrorDialog : public QDialog
{
    Q_OBJECT

//Public methods and constructors
public:

//ErrorDialog constructor
    explicit ErrorDialog(QWidget *parent = 0);

//ErrorDialog deconstructor
    ~ErrorDialog();

//Sets the data to be displayed in the ErrorDialog window
    void setData(std::vector<std::string>errorVector);

//Clears all data in the window after a new file is opened
    void clearData();

//Instance variables
private:
    Ui::ErrorDialog *ui;
};

#endif // ERRORDIALOG_H
