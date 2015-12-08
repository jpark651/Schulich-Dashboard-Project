/**
* Source file for the presentations class and its associated methods
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
#include "presentations.h"
using namespace std;

//presentations constructor (first/last year is set to the earliest/latest year in the file)
presentations::presentations(string file)
{
    excelData newData(file, 2);
    storedData = newData;
}
//presentations constructor (first/last year is set using the given parameters)
presentations::presentations(string file, int firstYear, int lastYear)
{
    excelData newData(file, firstYear, lastYear, 2);
    storedData = newData;
}
//uninitialized constructor
presentations::presentations() {}

//returns the information to be printed to the GUI, with each type's dataset separated by a single hyphen
vector<string> presentations::guiTypeData()
{
    return storedData.guiTypeData();
}

//shows a graph for the given person
void presentations::showGraph(string personName, int graphType, QCustomPlot *graph)
{
    storedData.showGraph(personName, graphType, graph);
}

//get the total number of entries
int presentations::getTotalEntries()
{
    return storedData.getTotalEntries();
}

//returns a pointer to the Parser object
Parser *presentations::getParse()
{
    return storedData.getParse();
}

//returns the start year
int presentations::getStartYear()
{
    return storedData.getStartYear();
}

//returns the end year
int presentations::getEndYear()
{
    return storedData.getEndYear();
}

//updates the graph
void presentations::updateGraph(int startYear, int endYear)
{
    storedData.updateGraph(startYear, endYear);
}

//updates the years
void presentations::updateYears(int startYear, int endYear)
{
    storedData.updateYears(startYear, endYear);
}
