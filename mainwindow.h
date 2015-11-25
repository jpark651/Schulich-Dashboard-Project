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
    bool activeFile;            //value which tells if a file has been loaded or not
    void unactive();            //Method if user closes
    void active();              //Method which finds what type of file to look for
    void activePublication();   //A method which creates a publication summary
    void activeTeaching();
    void activePresentation();
    void activeGrants();
    QString filePath;
    publications *pub;
    QLabel *noActiveFile;   //Label to let the user know to open a file
    vector<string> parsedData;
    void insertNames(QTreeWidgetItem*);
    int type_of_file=0;       //0=publication, 1=teaching, 2=presentation, 3=grants and clinical funding summary

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    //graph graphn;
    void createParser(QString);
};

#endif // MAINWINDOW_H
