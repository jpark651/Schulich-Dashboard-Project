#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Parser.h"
#include "publications.h"
#include <QMessageBox>
#include <iostream>
#include <vector>
#include <QStandardItemModel>
#include <QLabel>
#include <QFileDialog>
#include <string>
#include <QHeaderView>
#include "excelSheet.h"
#include "errordialog.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->menuBar->setNativeMenuBar(false);
    activeFile=false;
    ui->excelTree->header()->resizeSection(0,400);

    //Adding expandable items for Publications
    if (activeFile) {
        active();
    }
    else {
        unactive();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::unactive() {
    ui->unactiveLabel->setAlignment(Qt::AlignCenter);
    ui->unactiveLabel->setText("No file has been loaded.\nTo open a file go to File > Open.");
    ui->unactiveLabel->show();
    ui->excelTree->clear();
    ui->excelTree->setColumnCount(0);
    ui->label->setAlignment(Qt::AlignCenter);
    ui->label->setText("No Data to Display.");
}


void MainWindow::on_pushButton_clicked()
{
    filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "", "csv files (*.csv)");
    cout<<"Path: "<<filePath.toStdString();
    if (filePath.toStdString() != "") {
        createParser(filePath);
    }
}

void MainWindow::createParser(QString filePath) {
    excelSheet excel(filePath.toStdString());
    d.clearData();
    d.setData(excel.getErrorVector());
    type_of_file = excel.getExcelType();
    parsedData = excel.guiTypeData();
    active();
}

void MainWindow::active() {
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
        //Error, let the user know there was a problem
        //TODO
        printf("ERROR");
    }
}

void MainWindow::activePresentation() {
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
}

void MainWindow::activeGrants() {
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
}

void MainWindow::activeTeaching() {
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
}


void MainWindow::activePublication() {
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
}


void MainWindow::insertNames(QTreeWidgetItem *parent) {
    //While current item isn't a "-" and isn't empty do
    while (parsedData.front()!="-" && !parsedData.empty()) {
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

void MainWindow::on_actionOpen_triggered()
{
    on_pushButton_clicked();
}

void MainWindow::on_actionCloseFile_triggered()
{
    unactive();
}

void MainWindow::on_actionDisplay_Errors_triggered()
{
    d.setModal(true);
    d.exec();
}
