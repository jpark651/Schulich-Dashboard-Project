/**
* Source file for the funding class and its associated methods
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
#include "funding.h"
using namespace std;

//funding constructor (first/last year is set to the earliest/latest year in the file)
funding::funding(string file)
{
    excelData newData(file, 1);
    storedData = newData;
}
//funding constructor (first/last year is set using the given parameters)
funding::funding(string file, int firstYear, int lastYear)
{
    excelData newData(file, firstYear, lastYear, 1);
    storedData = newData;
}
//uninitiated constructor
funding::funding(){}


//returns the information to be printed to the GUI, with each type's dataset separated by a single hyphen
vector<string> funding::guiTypeData()
{
    return storedData.guiTypeData();
}

//shows a graph for the given entry
void funding::showGraph(int entryIndex, int graphType, QCustomPlot *graph)
{
    storedData.showGraph(entryIndex, graphType, graph);
}

//get the total number of entries
int funding::getTotalEntries()
{
    return storedData.getTotalEntries();
}

//returns a pointer to the Parser object
Parser *funding::getParse()
{
    return storedData.getParse();
}

