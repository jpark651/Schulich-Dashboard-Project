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

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->menuBar->setNativeMenuBar(false);
    activeFile=false;

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

    string path;
    path = filePath.toStdString();
    pub = new publications(path,1970,2020);
    active();
}

void MainWindow::active() {
    noActiveFile->hide();
    QTreeWidgetItem *publicat = new QTreeWidgetItem();
    QTreeWidgetItem *publishedAbstracts = new QTreeWidgetItem();
    QTreeWidgetItem *journalArticles = new QTreeWidgetItem();
    QTreeWidgetItem *books = new QTreeWidgetItem();
    QTreeWidgetItem *bookChapters = new QTreeWidgetItem();
    QTreeWidgetItem *letters = new QTreeWidgetItem();
    ui->publicationTree->addTopLevelItem(publicat);

    parsedData = pub->guiTypeData();        //Getting the parsedData from publications

    //Publications
    publicat->setText(0, QString::fromStdString(parsedData.front()));   //Setting "Publications"
    parsedData.erase(parsedData.begin());
    publicat->setText(1, QString::fromStdString(parsedData.front()));   //Setting # of publications
    parsedData.erase(parsedData.begin());


    //Published Abstracts
    publishedAbstracts->setText(0, QString::fromStdString(parsedData.front()));    //Setting "Published Abstracts"
     parsedData.erase(parsedData.begin());
    publishedAbstracts->setText(1, QString::fromStdString(parsedData.front()));    //Setting # of published abstracts
   parsedData.erase(parsedData.begin());
    publicat->addChild(publishedAbstracts);                //Add to publication tree

    //Insert the author's names
    insertNames(publishedAbstracts);


    //Journal Articles
    journalArticles->setText(0, QString::fromStdString(parsedData.front()));
     parsedData.erase(parsedData.begin());
    journalArticles->setText(1, QString::fromStdString(parsedData.front()));
     parsedData.erase(parsedData.begin());
    publicat->addChild(publishedAbstracts);

    //Insert the author's names
    insertNames(journalArticles);


    //Books
    books->setText(0, QString::fromStdString(parsedData.front()));
     parsedData.erase(parsedData.begin());
    books->setText(1, QString::fromStdString(parsedData.front()));
     parsedData.erase(parsedData.begin());
    publicat->addChild(books);

    //Insert the author's names
    insertNames(books);


    //Book Chapters
    bookChapters->setText(0,QString::fromStdString(parsedData.front()));
     parsedData.erase(parsedData.begin());
    bookChapters->setText(1,QString::fromStdString(parsedData.front()));
     parsedData.erase(parsedData.begin());
    publicat->addChild(bookChapters);

    //Insert Author's names
    insertNames(bookChapters);


    //Letters to Editors
    letters->setText(0, QString::fromStdString(parsedData.front()));
     parsedData.erase(parsedData.begin());
    letters->setText(1, QString::fromStdString(parsedData.front()));
     parsedData.erase(parsedData.begin());
    publicat->addChild(letters);

    //Insert names
    insertNames(letters);
    publicat->addChild(letters);
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
}
