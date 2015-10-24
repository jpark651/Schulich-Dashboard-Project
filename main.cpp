/**
* This file implements the main.h
*/
#include "mainwindow.h"
#include <QApplication>
#include "Parser.h"
#include <string>
#include <iostream>

int main(int argc, char *argv[])
{
	string file;


    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedHeight(720);
    w.setFixedWidth(1280);
    w.show();

	//TO DO, GUI gets file name input and sends back
	//file =





    return a.exec();
}
