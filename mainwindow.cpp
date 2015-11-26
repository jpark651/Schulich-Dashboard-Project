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

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->menuBar->setNativeMenuBar(false);
    activeFile=false;
    ui->publicationTree->header()->resizeSection(0,400);

    //Adding expandable items for Publications
    if (activeFile==true) {
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
    noActiveFile = new QLabel(ui->publicationTree);
    noActiveFile->setText("No file has been loaded.\nTo open a file go to File > Open.");
    noActiveFile->setAlignment(Qt::AlignCenter);
    noActiveFile->setGeometry(50,180,210,210);
    noActiveFile->show();
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
    parsedData = excel.guiTypeData();

    string path;
    path = filePath.toStdString();
//    pub = new publications(path,1970,2020);
    active();
}

void MainWindow::active() {
    if (type_of_file==0)
        activePublication();
    else if (type_of_file==1)
        activeTeaching();
    else if (type_of_file==2)
        activePresentation();
    else if (type_of_file==3)
        activeGrants();
    else
        //Error, let the user know there was a problem
        //TODO
        printf("ERROR");
}

void MainWindow::activePresentation() {
    //To do
    noActiveFile->hide();

    QTreeWidgetItem *presentation = new QTreeWidgetItem();
    QTreeWidgetItem *invitedLectures = new QTreeWidgetItem();
    QTreeWidgetItem *abstractsPresented = new QTreeWidgetItem();
    QTreeWidgetItem *nextPrentationType = new QTreeWidgetItem();
    QTreeWidgetItem *Other = new QTreeWidgetItem();

    ui->publicationTree->clear();
    ui->publicationTree->setColumnCount(3);

    QStringList horizontalHeaders;
    horizontalHeaders << "Summary" << "Faculty Name" << "Number of Presentations";

    ui->publicationTree->setHeaderLabels(horizontalHeaders);

    ui->publicationTree->addTopLevelItem(presentation);

    //TO DO


}

void MainWindow::activeGrants() {
    noActiveFile->hide();

    QTreeWidgetItem *grants = new QTreeWidgetItem();
    QTreeWidgetItem *peerReviewed1 = new QTreeWidgetItem();
    QTreeWidgetItem *industrySponsored1 = new QTreeWidgetItem();
    QTreeWidgetItem *clinicalFunding = new QTreeWidgetItem();
    QTreeWidgetItem *peerReviewed2 = new QTreeWidgetItem();
    QTreeWidgetItem *industrySponsored2 = new QTreeWidgetItem();

    ui->publicationTree->clear();
    ui->publicationTree->setColumnCount(3);

    QStringList horizontalHeaders;
    horizontalHeaders << "Summary" << "Total #" << "Total $";
    ui->publicationTree->setHeaderLabels(horizontalHeaders);

    ui->publicationTree->addTopLevelItem(grants);

    // TODO
}

void MainWindow::activeTeaching() {
    noActiveFile->hide();
    
    QTreeWidgetItem *teaching = new QTreeWidgetItem();
    QTreeWidgetItem *pme = new QTreeWidgetItem();
    QTreeWidgetItem *ume = new QTreeWidgetItem();
    QTreeWidgetItem *cme = new QTreeWidgetItem();
    QTreeWidgetItem *other = new QTreeWidgetItem();

    //Readjusting the headers to match teaching summary
    ui->publicationTree->clear();
    ui->publicationTree->setColumnCount(4);

    //Creating a string list of the headers
    QStringList horizontalHeaders;
    horizontalHeaders << "Summary" << "Academic Year" << "Hours" << "Students";

    //Setting the column headers
    ui->publicationTree->setHeaderLabels(horizontalHeaders);

    ui->publicationTree->addTopLevelItem(teaching);

    //TODO
}


void MainWindow::activePublication() {
    noActiveFile->hide();
    QTreeWidgetItem *publicat = new QTreeWidgetItem();

    ui->publicationTree->clear();
    ui->publicationTree->setColumnCount(2);

    QStringList horizontalHeaders;
    horizontalHeaders << "Summary" << "Total";

    ui->publicationTree->setHeaderLabels(horizontalHeaders);

    ui->publicationTree->addTopLevelItem(publicat);

//    parsedData = pub->guiTypeData();        //Getting the parsedData from publications

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
    while (parsedData.front()!="-" && parsedData.empty()!=true) {
        QTreeWidgetItem *newItem = new QTreeWidgetItem();       //Create a new tree widget item
        newItem->setText(0, QString::fromStdString(parsedData.front()));                //Set it's name to the next item in the parsed data
        parsedData.erase(parsedData.begin());                                 //Pop the item off the list
        newItem->setText(1, QString::fromStdString(parsedData.front()));                //Set the # to the next item in the list
         parsedData.erase(parsedData.begin());
        parent->addChild(newItem);
    }
    if (parsedData.empty() != true)
    {
        parsedData.erase(parsedData.begin());
    }
}
