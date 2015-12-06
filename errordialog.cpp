/**
 * This file implements the methods in errordialog.h and displays all mandatory fields that are missing from each row
 */
#include "errordialog.h"
#include "ui_errordialog.h"
#include "QString"
//ErrorDialog constructor
ErrorDialog::ErrorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorDialog)
{
    ui->setupUi(this);
}

//ErrorDialog deconstructor
ErrorDialog::~ErrorDialog()
{
    delete ui;
}

//Sets the data to be displayed in the ErrorDialog window
void ErrorDialog:: setData(std::vector<std::string>errorVector)
{
    for (unsigned int i =0; i < errorVector.size(); i++)
    {
       QString str = QString::fromUtf8(errorVector[i].c_str());
        ui->listWidget->addItem(str);
    }
}

//Clears all data in the window after a new file is opened
void ErrorDialog:: clearData()
{
    while(ui->listWidget->count()>0)
    {
      ui->listWidget->takeItem(0);
    }
}
