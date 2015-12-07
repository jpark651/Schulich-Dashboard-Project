/**
* Source file for the teaching class and its associated methods
*/
#include <iostream>
#include <iterator>
#include <list>
#include <qcustomplot.h>
#include <sstream>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "excelData.h"
#include "Parser.h"
#include "teaching.h"
using namespace std;

//teaching constructor (first/last year is set to the earliest/latest year in the file)
teaching::teaching(string file)
{
    excelData newData(file, 4);
    storedData = newData;
}
//teaching constructor (first/last year is set using the given parameters)
teaching::teaching(string file, int firstYear, int lastYear)
{
    excelData newData(file, firstYear, lastYear, 4);
    storedData = newData;
}
//uninitialized constructor
teaching::teaching() {}

//returns the information to be printed to the GUI, with each type's dataset separated by a single hyphen
vector<string> teaching::guiTypeData()
{
    return storedData.guiTypeData();
}

//shows a graph for the given person
void teaching::showGraph(string personName, int graphType, QCustomPlot *graph)
{
    storedData.showGraph(personName, graphType, graph);
}

//get the total number of entries
int teaching::getTotalEntries()
{
    return storedData.getTotalEntries();
}

//returns a pointer to the Parser object
Parser *teaching::getParse()
{
    return storedData.getParse();
}

