/**
  * Author: Team HoneyDew
  * Computer Science 3307, Group Project
  * December 9, 2015
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

//Uninitialized constructor
teaching::teaching() {}

//Returns the information to be printed to the GUI, with each type's dataset separated by a single hyphen
vector<string> teaching::guiTypeData()
{
    return storedData.guiTypeData();
}

//Shows a graph for the given person
void teaching::showGraph(string personName, int graphType, QCustomPlot *graph)
{
    storedData.showGraph(personName, graphType, graph);
}

//Get the total number of entries
int teaching::getTotalEntries()
{
    return storedData.getTotalEntries();
}

//Returns a pointer to the Parser object
Parser *teaching::getParse()
{
    return storedData.getParse();
}

//Returns the start year
int teaching::getStartYear()
{
    return storedData.getStartYear();
}

//Returns the end year
int teaching::getEndYear()
{
    return storedData.getEndYear();
}

//Updates the graph with a new start year and end year
void teaching::updateGraph(int startYear, int endYear)
{
    storedData.updateGraph(startYear, endYear);
}

//Updates the start year and end year being stored
void teaching::updateYears(int startYear, int endYear)
{
    storedData.updateYears(startYear, endYear);
}
