/**
* This file implements the main.h
*/
#include "mainwindow.h"
#include <QApplication>
#include "Parser.h"
#include "funding.h"
#include "presentations.h"
#include "publications.h"
#include "teaching.h"
#include "excelSheet.h"
#include "graph.h"
#include <string>
#include <iostream>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
