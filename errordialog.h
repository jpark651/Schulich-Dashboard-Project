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
    explicit ErrorDialog(QWidget *parent = 0);
    ~ErrorDialog();
    void setData(std::vector<std::string>errorVector);
    void clearData();

private:
    Ui::ErrorDialog *ui;
};

#endif // ERRORDIALOG_H
