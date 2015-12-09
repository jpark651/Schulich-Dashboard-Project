/**
  * Author: Team HoneyDew
  * Computer Science 3307, Group Project
  * December 9, 2015
  * This file implements the methods in yearRange.h
 */
#include <sstream>
#include "excelSheet.h"
#include "QString"
#include "yearRange.h"
#include "ui_yearRange.h"
using namespace std;

//yearRange constructor
yearRange::yearRange(excelSheet *excel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::yearRange)
{
    ui->setupUi(this);
    this->excel = excel;
    this->setWindowTitle("Select Years");
    this->setFixedSize(this->width(),this->height());
    stringstream ss1, ss2;
    ss1 << excel->getStartYear();
    ss2 << excel->getEndYear();
    ui->lineStart->setText(QString::fromStdString(ss1.str()));
    ui->lineEnd->setText(QString::fromStdString(ss2.str()));
}

//yearRange deconstructor
yearRange::~yearRange()
{
    delete ui;
}

//Updates the graph associated with a user when the date range is confirmed by the user
void yearRange::on_confirm_released()
{
    QString newStartQ = ui->lineStart->text(), newEndQ = ui->lineEnd->text();
    int newStart = newStartQ.toInt(), newEnd = newEndQ.toInt();
    int choice = ui->filterScope->currentIndex();
    switch(choice)
    {
    case 0:
        excel->updateGraph(newStart, newEnd);
        break;

    case 1:
        excel->updateYears(newStart, newEnd);
        excel->setReset(true);
        break;
    }
    this->close();
}
