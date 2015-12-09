/**
  * Author: Team HoneyDew
  * Computer Science 3307, Group Project
  * December 9, 2015
  * This file implements the methods in publications.h
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
#include "publications.h"
using namespace std;

//Publications constructor (first/last year is set to the earliest/latest year in the file)
publications::publications(string file)
{
    excelData newData(file, 3);
    storedData = newData;
}

//Publications constructor (first/last year is set using the given parameters)
publications::publications(string file, int firstYear, int lastYear)
{
    excelData newData(file, firstYear, lastYear, 3);
    storedData = newData;
}

//Uninitialized constructor
publications::publications() {}

//Returns the information to be printed to the GUI, with each type's dataset separated by a single hyphen
vector<string> publications::guiTypeData()
{
    return storedData.guiTypeData();
}

//Shows a graph for the given person
void publications::showGraph(string personName, int graphType, QCustomPlot *graph)
{
    storedData.showGraph(personName, graphType, graph);
}

//Get the total number of entries
int publications::getTotalEntries()
{
    return storedData.getTotalEntries();
}

//Returns a pointer to the Parser object
Parser *publications::getParse()
{
    return storedData.getParse();
}

//Returns the start year
int publications::getStartYear()
{
    return storedData.getStartYear();
}

//Returns the end year
int publications::getEndYear()
{
    return storedData.getEndYear();
}

//Updates the graph with a new start year and end year
void publications::updateGraph(int startYear, int endYear)
{
    storedData.updateGraph(startYear, endYear);
}

//Updates the years
void publications::updateYears(int startYear, int endYear)
{
    storedData.updateYears(startYear, endYear);
}
