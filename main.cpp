/**
* This file implements the main.h
*/
#include "mainwindow.h"
#include <QApplication>
#include "Parser.h"
#include "publications.h"
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
