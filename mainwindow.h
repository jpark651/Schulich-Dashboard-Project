#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "publications.h"
#include <QMainWindow>
#include <QTreeWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool activeFile;    //value which tells if a file has been loaded or not
    void unactive();    //Method if user closes
    void active();
    QString filePath;
    publications *pub;


private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    void createParser(QString);
};

#endif // MAINWINDOW_H
