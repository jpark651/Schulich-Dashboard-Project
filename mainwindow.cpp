#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Parser.h"
#include <QMessageBox>
#include <iostream>
#include <QStandardItemModel>
#include <QLabel>

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
        QTreeWidgetItem *publications = new QTreeWidgetItem();
        QTreeWidgetItem *publishedAbstracts = new QTreeWidgetItem();
        QTreeWidgetItem *journalArticles = new QTreeWidgetItem();
        QTreeWidgetItem *books = new QTreeWidgetItem();
        QTreeWidgetItem *bookChapters = new QTreeWidgetItem();
        QTreeWidgetItem *letters = new QTreeWidgetItem();
        ui->publicationTree->addTopLevelItem(publications);
        publications->setText(0, tr("Publications"));
        publishedAbstracts->setText(0, tr("Published Abstracts"));
        journalArticles->setText(0, tr("Journal Articles"));
        books->setText(0, tr("Books"));
        bookChapters->setText(0,tr("Book Chapters"));
        letters->setText(0, tr("Letters to Editors"));


        //TO DO: Get totals


        publications->addChild(publishedAbstracts);
        publications->addChild(journalArticles);
        publications->addChild(books);
        publications->addChild(letters);


        //Adding expandable items for Grants and Clinical Funding Summary
        QTreeWidgetItem *fundingSummary = new QTreeWidgetItem();
        QTreeWidgetItem *peerReviewed = new QTreeWidgetItem();
        peerReviewed->setText(0,tr("Peer Reviewed"));
        fundingSummary->setText(0,tr("Grants and Clinical Funding"));
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
    QLabel *noActiveFile = new QLabel(ui->publicationTree); //Label to let the user know to open a file
    noActiveFile->setText("No file has been loaded.\nTo open a file go to File > Open.");
    noActiveFile->setAlignment(Qt::AlignCenter);
    noActiveFile->setGeometry(50,180,210,210);
    ui->label->setAlignment(Qt::AlignCenter);
    ui->label->setText("No Data to Display.");
}

