/**
  * Author: Team HoneyDew
  * Computer Science 3307, Group Project
  * December 9, 2015
  * This file defines instance variables and associated with methods with MainWindow
  */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QLabel>
#include <QMainWindow>
#include <QTreeWidgetItem>
#include "errordialog.h"
#include "excelSheet.h"

//Defines the Ui namespace that is used to display the GUI
namespace Ui
{
class MainWindow;
}

//Defines the MainWindow Class and its associated methods and instance variables
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

//MainWindow constructor
    explicit MainWindow(QWidget *parent = 0);

//MainWindow deconstructor
    ~MainWindow();
    bool activeFile;            //value which tells if a file has been loaded or not

//Clears GUI if user closes a file
    void unactive();

//Updates the view of the graph to show data when a file is opened
    void active();

//Builds the display for publications data in the GUI if a publications file is opened
    void activePublication();

//Builds the display for teaching data in the GUI if a teaching file is opened
    void activeTeaching();

//Builds the display for presentation data in the GUI if a presentations file is opened
    void activePresentation();

//Builds the display for grants data in the GUI if a presentations file is opened
    void activeGrants();
    int yearStart;
    int yearEnd;
    ErrorDialog d;

//Holds parsed data
    vector<string> parsedData;
    QString filePath;

//Label to let the user know to open a file
    QLabel *noActiveFile;
    void insertNames(QTreeWidgetItem*);

//1 = funding, 2 = presentations, 3 = publications, 4 = teaching
    int type_of_file;
    excelSheet excel;
    bool willReset = false;

private slots:
//Opens a file to be parsed and displayed when the user clicks the open file button
    void on_pushButton_clicked();

//Slot for action when a file is opened
    void on_actionOpen_triggered();

//Slot for action when a file is closed that causes the GUI to be cleared
    void on_actionCloseFile_triggered();

//Causes the errordialog window to pop up
    void on_actionDisplay_Errors_triggered();

//Resizes the columns to fit the visible data when a section is collapsed
    void on_excelTree_collapsed(const QModelIndex &index);

//Resizes the columns to fit the visible data when a section is expanded
    void on_excelTree_expanded(const QModelIndex &index);

//Displays the graph for an inidivudal person if their name is clicked
    void on_excelTree_itemSelectionChanged();

//Causes the program to enter full screen mode
    void on_actionExit_Fullscreen_triggered();

//Allows the program to exit full screen mode
    void on_actionFullscreen_triggered();

//Causes the dialog box that prompts the user to enter a year range to be displayed
    void on_actionSet_Year_Range_triggered();

//Instance variables and methods
private:
    Ui::MainWindow *ui;

//Reinitializes the window using the stored excelSheet object
    void reset();

//Parses the CSV file, then displays all data and a default empty graph to the screen
    void createParser(QString);
};

#endif // MAINWINDOW_H
