/**
  * Author: Team HoneyDew
  * Computer Science 3307, Group Project
  * December 9, 2015
  * Header file that defines the methods and instance variables in yearRange.cpp
  */
#ifndef YEARRANGE_H
#define YEARRANGE_H

#include <QDialog>
#include <string>
#include <vector>
#include "excelSheet.h"

//The Ui namespace is used to display the box that prompts the user to specify a date range
namespace Ui {
class yearRange;
}


class yearRange : public QDialog
{
    Q_OBJECT

public:

//yearRange constructor
    explicit yearRange(excelSheet *excel, QWidget *parent = 0);

//yearRange deconstructor
    ~yearRange();


private slots:

//Updates the graph associated with a user when the date range is confirmed by the user
    void on_confirm_released();

private:

//Instance variables
    excelSheet *excel;
    QWidget *parent;
    Ui::yearRange *ui;
};

#endif // YEARRANGE_H
