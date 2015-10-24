#include "mainwindow.h"
#include <QApplication>
#include "Parser.h"
#include "main.h"

int main(int argc, char *argv[])
{
	string file;


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

	//TO DO, GUI gets file name input and sends back
	//file =





    return a.exec();
}
