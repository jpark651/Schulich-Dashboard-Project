/**
  * Author: Team HoneyDew
  * Computer Science 3307, Group Project
  * December 9, 2015
  * This file implements the methods in mainwindow.h and represents the GUI where all of the main
  * data will be displayed
  */
#include <iostream>
#include <qcustomplot.h>
#include <QFileDialog>
#include <QHeaderView>
#include <QLabel>
#include <QMessageBox>
#include <QStandardItemModel>
#include <string>
#include <vector>
#include "errordialog.h"
#include "excelSheet.h"
#include "publications.h"
#include "Parser.h"
#include "yearRange.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"

using namespace std;

//MainWindow constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menuBar->setNativeMenuBar(false);
    ui->actionExit_Fullscreen->setDisabled(true);
    ui->actionCloseFile->setDisabled(true);
    ui->actionDisplay_Errors->setDisabled(true);
    ui->actionSet_Year_Range->setDisabled(true);
    ui->grid->removeWidget(ui->label);
    ui->grid->addWidget(ui->label, 0, 0, Qt::AlignCenter|Qt::AlignCenter);
    ui->border->setFrameShape(QFrame::Box);
    ui->excelTree->setSelectionMode(QTreeWidget::SingleSelection);
    activeFile=false;
    unactive();
}

//MainWindow deconstructor
MainWindow::~MainWindow()
{
    delete ui;
}

//Clears the GUI when a file is closed
void MainWindow::unactive()
{
    ui->actionCloseFile->setDisabled(true);
    ui->actionDisplay_Errors->setDisabled(true);
    ui->actionSet_Year_Range->setDisabled(true);
    ui->unactiveLabel->setAlignment(Qt::AlignCenter);
    ui->unactiveLabel->setText("No file has been loaded.\nTo open a file go to File > Open.");
    ui->unactiveLabel->show();
    ui->excelTree->clear();
    ui->excelTree->setColumnCount(0);
    ui->graph->hide();
    ui->label->show();
    ui->label->setAlignment(Qt::AlignCenter);
    ui->label->setText("No Data to Display.");
}

//Opens a file to be parsed and displayed with the user clicks the open file button
void MainWindow::on_pushButton_clicked()
{
    filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "", "csv files (*.csv)");
    cout<<"Path: "<<filePath.toStdString();
    if (filePath.toStdString() != "")
    {
        createParser(filePath);
    }
}

//Parses the csv file and displays all data as well as a default empty graph to the screen
void MainWindow::createParser(QString filePath)
{
    if (willReset)
    {
        excel = excelSheet(excel.getFilepath(), excel.getStartYear(), excel.getEndYear());
        willReset = false;
    }
    else
    {
        excel = excelSheet(filePath.toStdString());
    }
    d.clearData();
    d.setData(excel.getErrorVector());
    yearStart = excel.getStartYear();
    yearEnd = excel.getEndYear();
    type_of_file = excel.getExcelType();
    parsedData = excel.guiTypeData();
    excel.showGraph("", 0, ui->graph);
    active();
}

//Updates the view of the graph to show data when a file is opened
void MainWindow::active()
{
    ui->actionCloseFile->setDisabled(false);
    ui->actionDisplay_Errors->setDisabled(false);
    ui->actionSet_Year_Range->setDisabled(false);
    ui->label->hide();
    ui->graph->show();
    ui->unactiveLabel->hide();
    switch (type_of_file)
    {
    case 1:
        activeGrants();
        break;
    case 2:
        activePresentation();
        break;
    case 3:
        activePublication();
        break;
    case 4:
        activeTeaching();
        break;
    default:
        printf("ERROR");
    }
}

//Builds the display for presentation data in the GUI if a presentations file is opened
void MainWindow::activePresentation()
{
    QTreeWidgetItem *presentation = new QTreeWidgetItem();

    ui->excelTree->clear();
    ui->excelTree->setColumnCount(0);
    ui->excelTree->setColumnCount(2);

    QStringList horizontalHeaders;
    horizontalHeaders << "Summary" << "Number of Presentations";

    ui->excelTree->setHeaderLabels(horizontalHeaders);
    ui->excelTree->addTopLevelItem(presentation);

    //Presentations
    presentation->setText(0, QString::fromStdString(parsedData.front()));   //Setting "Presentations"
    parsedData.erase(parsedData.begin());

    presentation->setText(1, QString::fromStdString(parsedData.front()));   //Setting # of presentations
    parsedData.erase(parsedData.begin());

    while (parsedData.size() > 0)
    {
        QTreeWidgetItem *nextSection = new QTreeWidgetItem();
        nextSection->setText(0, QString::fromStdString(parsedData.front()));
        parsedData.erase(parsedData.begin());
        nextSection->setText(1, QString::fromStdString(parsedData.front()));
        parsedData.erase(parsedData.begin());
        presentation->addChild(nextSection);

        //Insert names
        insertNames(nextSection);
    }
    ui->excelTree->resizeColumnToContents(0);
    ui->excelTree->resizeColumnToContents(1);
}

//Builds the display for grants data in the GUI if a grants file is opened
void MainWindow::activeGrants()
{
    //Readjusting the headers to match teaching summary
    ui->excelTree->clear();
    ui->excelTree->setColumnCount(0);
    ui->excelTree->setColumnCount(3);

    //Creating a string list of the headers
    QStringList horizontalHeaders;
    horizontalHeaders << "Summary" << "Total #" << "Total $";

    //Setting the column headers
    ui->excelTree->setHeaderLabels(horizontalHeaders);

    //Grants
    for (int i = 0; i < 2; i++)
    {
        QTreeWidgetItem *subSection = new QTreeWidgetItem();
        subSection->setText(0, QString::fromStdString(parsedData.front()));   //Setting "Grants"/"Clinical Funding"
        parsedData.erase(parsedData.begin());

        subSection->setText(1, QString::fromStdString(parsedData.front()));   //Setting number of grants/funding
        parsedData.erase(parsedData.begin());

        subSection->setText(2, QString::fromStdString(parsedData.front()));   //Setting amount of money
        parsedData.erase(parsedData.begin());
        ui->excelTree->addTopLevelItem(subSection);

        while (parsedData.size() > 0 && parsedData.front().compare("-") != 0)
        {
            QTreeWidgetItem *nextSection = new QTreeWidgetItem();
            nextSection->setText(0, QString::fromStdString(parsedData.front()));
            parsedData.erase(parsedData.begin());
            nextSection->setText(1, QString::fromStdString(parsedData.front()));
            parsedData.erase(parsedData.begin());
            nextSection->setText(2, QString::fromStdString(parsedData.front()));
            parsedData.erase(parsedData.begin());
            subSection->addChild(nextSection);

            //Insert names
            insertNames(nextSection);
        }
        if (!parsedData.empty())
        {
            parsedData.erase(parsedData.begin());
        }
    }
    ui->excelTree->resizeColumnToContents(0);
    ui->excelTree->resizeColumnToContents(1);
}

//Builds the display for teaching data in the GUI if a teaching file is opened
void MainWindow::activeTeaching()
{
    QTreeWidgetItem *teaching = new QTreeWidgetItem();

    //Readjusting the headers to match teaching summary
    ui->excelTree->clear();
    ui->excelTree->setColumnCount(0);
    ui->excelTree->setColumnCount(2);

    //Creating a string list of the headers
    QStringList horizontalHeaders;
    horizontalHeaders << "Summary" << "Hours";

    //Setting the column headers
    ui->excelTree->setHeaderLabels(horizontalHeaders);
    ui->excelTree->addTopLevelItem(teaching);

    //Teaching
    teaching->setText(0, QString::fromStdString(parsedData.front()));   //Setting "Teaching"
    parsedData.erase(parsedData.begin());

    teaching->setText(1, QString::fromStdString(parsedData.front()));   //Setting # of hours
    parsedData.erase(parsedData.begin());

    while (parsedData.size() > 0)
    {
        QTreeWidgetItem *nextSection = new QTreeWidgetItem();
        nextSection->setText(0, QString::fromStdString(parsedData.front()));
        parsedData.erase(parsedData.begin());
        nextSection->setText(1, QString::fromStdString(parsedData.front()));
        parsedData.erase(parsedData.begin());
        teaching->addChild(nextSection);

        //Insert names
        insertNames(nextSection);
    }
    ui->excelTree->resizeColumnToContents(0);
    ui->excelTree->resizeColumnToContents(1);
}

//Builds the display for publications data in the GUI if a publications file is opened
void MainWindow::activePublication()
{
    QTreeWidgetItem *publicat = new QTreeWidgetItem();

    ui->excelTree->clear();
    ui->excelTree->setColumnCount(0);
    ui->excelTree->setColumnCount(2);

    QStringList horizontalHeaders;
    horizontalHeaders << "Summary" << "Total";

    ui->excelTree->setHeaderLabels(horizontalHeaders);
    ui->excelTree->addTopLevelItem(publicat);

    //Publications
    publicat->setText(0, QString::fromStdString(parsedData.front()));   //Setting "Publications"
    parsedData.erase(parsedData.begin());

    publicat->setText(1, QString::fromStdString(parsedData.front()));   //Setting # of publications
    parsedData.erase(parsedData.begin());

    while (parsedData.size() > 0)
    {
        QTreeWidgetItem *nextSection = new QTreeWidgetItem();
        nextSection->setText(0, QString::fromStdString(parsedData.front()));
        parsedData.erase(parsedData.begin());
        nextSection->setText(1, QString::fromStdString(parsedData.front()));
        parsedData.erase(parsedData.begin());
        publicat->addChild(nextSection);

        //Insert names
        insertNames(nextSection);
    }
    ui->excelTree->resizeColumnToContents(0);
    ui->excelTree->resizeColumnToContents(1);
}

//Inserts the names for all contributors in the file when a new file is opened
void MainWindow::insertNames(QTreeWidgetItem *parent)
{
    //While current item isn't a "-" and isn't empty do
    while (parsedData.front()!="-" && !parsedData.empty())
    {
        QTreeWidgetItem *newItem = new QTreeWidgetItem();                   //Create a new tree widget item
        newItem->setText(0, QString::fromStdString(parsedData.front()));    //Set its name to the next item in the parsed data
        parsedData.erase(parsedData.begin());                               //Pop the item off the list
        newItem->setText(1, QString::fromStdString(parsedData.front()));    //Set the # to the next item in the list
        parsedData.erase(parsedData.begin());
        if (type_of_file == 1)
        {
            newItem->setText(2, QString::fromStdString(parsedData.front()));
            parsedData.erase(parsedData.begin());
        }
        parent->addChild(newItem);
    }
    if (!parsedData.empty())
    {
        parsedData.erase(parsedData.begin());
    }
}

//Slot for action when a file is opened
void MainWindow::on_actionOpen_triggered()
{
    on_pushButton_clicked();
}

//Slot for action when a file is closed that causes the GUI to be cleared
void MainWindow::on_actionCloseFile_triggered()
{
    unactive();
}

//Causes the errordialog window to pop up
void MainWindow::on_actionDisplay_Errors_triggered()
{
    d.setModal(true);
    d.exec();
}

//Allows a data display to be closed to show less data
void MainWindow::on_excelTree_collapsed(const QModelIndex &index)
{
    ui->excelTree->resizeColumnToContents(0);
    ui->excelTree->resizeColumnToContents(1);
}

//Allows a data display to be closed to show more data for a given section
void MainWindow::on_excelTree_expanded(const QModelIndex &index)
{
    ui->excelTree->resizeColumnToContents(0);
    ui->excelTree->resizeColumnToContents(1);
}

//Displays the graph for an inidivudal person if their name is clicked
void MainWindow::on_excelTree_itemSelectionChanged()
{
    QList<QTreeWidgetItem*> selected = ui->excelTree->selectedItems();
    QTreeWidgetItem item;
    if (selected.size() > 0)
    {
        item = *selected.back();
    }
    QString qName = item.text(0);
    string name = "";
    if (!qName.isNull() && !qName.isEmpty())
    {
        name = qName.toStdString();
        for (int i = 0, iMax = name.size(); i < iMax; i++)
        {
            if (name[i] == ',')
            {
                excel.showGraph(name, 1, ui->graph);
            }
        }
    }
}

//Causes the program to enter full screen mode
void MainWindow::on_actionExit_Fullscreen_triggered()
{
    ui->actionExit_Fullscreen->setDisabled(true);
    ui->actionFullscreen->setDisabled(false);
}

//Allows the program to exit full screen mode
void MainWindow::on_actionFullscreen_triggered()
{
    ui->actionFullscreen->setDisabled(true);
    ui->actionExit_Fullscreen->setDisabled(false);
}

//Causes the dialog box that prompts the user to enter in a year range to be displayed
void MainWindow::on_actionSet_Year_Range_triggered()
{
    yearRange filter(&excel);
    filter.exec();
    if (excel.getReset())
    {
        reset();
    }
}

//Reinitializes the window using the stored excelSheet object
void MainWindow::reset()
{
    willReset = true;
    createParser(QString::fromStdString(excel.getFilepath()));
}
