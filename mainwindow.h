#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "publications.h"
#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QLabel>

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
    QLabel *noActiveFile; //Label to let the user know to open a file
    list<string> parsedData;
    void insertNames(QTreeWidgetItem*);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    //graph graphn;
    void createParser(QString);
};

#endif // MAINWINDOW_H
