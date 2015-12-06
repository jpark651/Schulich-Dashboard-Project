#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "publications.h"
#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QLabel>
#include "errordialog.h"
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
    ErrorDialog d;
    vector<string> parsedData;  //Holds parsed data
    QString filePath;
    publications *pub;
    QLabel *noActiveFile;   //Label to let the user know to open a file
    void insertNames(QTreeWidgetItem*);
    int type_of_file;       //1 = funding, 2 = presentations, 3 = publications, 4 = teaching

private slots:
    void on_pushButton_clicked();

    void on_actionOpen_triggered();

    void on_actionCloseFile_triggered();



    void on_actionDisplay_Errors_triggered();

private:
    Ui::MainWindow *ui;
    //graph graphn;
    void createParser(QString);
};

#endif // MAINWINDOW_H
