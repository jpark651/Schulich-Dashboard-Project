#include "errordialog.h"
#include "ui_errordialog.h"
#include "QString"
ErrorDialog::ErrorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorDialog)
{
    ui->setupUi(this);
}

ErrorDialog::~ErrorDialog()
{
    delete ui;
}

void ErrorDialog:: setData(std::vector<std::string>errorVector)
{
    for (unsigned int i =0; i < errorVector.size(); i++)
    {
       QString str = QString::fromUtf8(errorVector[i].c_str());
        ui->listWidget->addItem(str);
    }
}

void ErrorDialog:: clearData()
{
    while(ui->listWidget->count()>0)
    {
      ui->listWidget->takeItem(0);
    }
}
