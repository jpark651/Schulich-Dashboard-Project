/**
* Source file for the publications class and its associated methods
*/
#include <iostream>
#include <iterator>
#include <list>
#include <sstream>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "excelData.h"
#include "Parser.h"
#include "publications.h"


#include <unistd.h>
using namespace std;


//publications constructor (first/last year is set to the earliest/latest year in the file)
publications::publications(string file)
{
    excelData newData(file, 3);
    storedData = newData;
}
//publications constructor (first/last year is set using the given parameters)
publications::publications(string file, int firstYear, int lastYear)
{
    excelData newData(file, firstYear, lastYear, 3);
    storedData = newData;

//    unsigned int microseconds = 5000000;
//    usleep(microseconds);
//    Dialog dialog;
//    dialog.show();


//    usleep(microseconds);
    printf("About to show graph!\n");
}
//uninitiated constructor
publications::publications() {}

//returns the information to be printed to the GUI, with each type's dataset separated by a single hyphen
vector<string> publications::guiTypeData()
{
    return storedData.guiTypeData();
}

//shows a graph for the given person
void publications::showGraph(int personIndex, int graphType)
{
    storedData.showGraph(personIndex, graphType);
}

//get the total number of persons
int publications::getPersonTotal()
{
    return storedData.getPersonTotal();
}

//returns a reference to the Parser object
Parser *publications::getParse()
{
    return storedData.getParse();
}

