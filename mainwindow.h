#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QLabel>
#include <QMainWindow>
#include <QTreeWidgetItem>
#include "errordialog.h"
#include "excelSheet.h"

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
    int yearStart;
    int yearEnd;
    ErrorDialog d;
    vector<string> parsedData;  //Holds parsed data
    QString filePath;
    QLabel *noActiveFile;       //Label to let the user know to open a file
    void insertNames(QTreeWidgetItem*);
    int type_of_file;           //1 = funding, 2 = presentations, 3 = publications, 4 = teaching
    excelSheet excel;
    bool willReset = false;

private slots:
    void on_pushButton_clicked();

    void on_actionOpen_triggered();

    void on_actionCloseFile_triggered();

    void on_actionDisplay_Errors_triggered();

    void on_excelTree_collapsed(const QModelIndex &index);

    void on_excelTree_expanded(const QModelIndex &index);

    void on_excelTree_itemSelectionChanged();

    void on_actionExit_Fullscreen_triggered();

    void on_actionFullscreen_triggered();

    void on_actionSet_Year_Range_triggered();

private:
    Ui::MainWindow *ui;

    //reinitializes the window using the stored excelSheet object
    void reset();

    void createParser(QString);
};

#endif // MAINWINDOW_H
