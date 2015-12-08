/**
  * Header file that defines the methods and instance variables in yearRange.cpp
  */
#ifndef YEARRANGE_H
#define YEARRANGE_H

#include <QDialog>
#include <string>
#include <vector>
#include "excelSheet.h"

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
    void on_confirm_released();

private:
    excelSheet *excel;
    QWidget *parent;
    Ui::yearRange *ui;
};

#endif // YEARRANGE_H
