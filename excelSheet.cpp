/**
  * Author: Team HoneyDew
  * Computer Science 3307, Group Project
  * December 9, 2015
  * Source file for the excelSheet class that implements the methods in excelSheet.h
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
#include "funding.h"
#include "presentations.h"
#include "publications.h"
#include "teaching.h"
#include "Parser.h"
#include "excelSheet.h"
using namespace std;

//excelSheet constructor (first/last year is set to the earliest/latest year in the file)
excelSheet::excelSheet(string file)
{
    filepath = file;
    sheetType = getExcelType(file);
    switch (sheetType)
    {
    case 1:
        sheetType1 = funding(file);
        break;
    case 2:
        sheetType2 = presentations(file);
        break;
    case 3:
        sheetType3 = publications(file);
        break;
    case 4:
        sheetType4 = teaching(file);
        break;
    }
    setErrorVector();
}

//excelSheet constructor (first/last year is set using the given parameters)
excelSheet::excelSheet(string file, int firstYear, int lastYear)
{
    filepath = file;
    sheetType = getExcelType(file);
    switch (sheetType)
    {
    case 1:
        sheetType1 = funding(file, firstYear, lastYear);
        break;
    case 2:
        sheetType2 = presentations(file, firstYear, lastYear);
        break;
    case 3:
        sheetType3 = publications(file, firstYear, lastYear);
        break;
    case 4:
        sheetType4 = teaching(file, firstYear, lastYear);
        break;
    }
    setErrorVector();
}

//Uninitialized constructor
excelSheet::excelSheet() {}


//Returns the type of CSV file (1 = funding, 2 = presentations, 3 = publications, 4 = teaching)
int excelSheet::getExcelType(string filename)
{
    int type = 0;
    Parser *parse = new Parser();
    vector<string> headers = parse->getCols(filename);
    for (int i = 0, iMax = headers.size(); i < iMax; i++)
    {
        string temp = headers[i];
        if (temp.compare("Total Amount") == 0)
        {
            type = 1;
            break;
        }
        if (temp.compare("Date") == 0)
        {
            type = 2;
            break;
        }
        if (temp.compare("Status Date") == 0)
        {
            type = 3;
            break;
        }
        if (temp.compare("Program") == 0)
        {
            type = 4;
            break;
        }
    }
    return type;
}

//Sets the error vector which contains a list of missing mandatory fields from each row
void excelSheet::setErrorVector()
{
    Parser *p;
    switch (sheetType)
    {
    case 1:
        p = sheetType1.getParse();
        break;
    case 2:
        p = sheetType2.getParse();
        break;
    case 3:
        p = sheetType3.getParse();
        break;
    case 4:
        p = sheetType4.getParse();
        break;
    }
    errorVector = p->getErrorVector();
}

//Returns the type of Excel sheet (1 = funding, 2 = presentations, 3 = publications, 4 = teaching)
int excelSheet::getExcelType()
{
    return sheetType;
}

//Returns the information to be printed to the GUI, with each type's dataset separated by a single hyphen
vector<string> excelSheet::guiTypeData()
{
    vector<string> typeData;
    switch (sheetType)
    {
    case 1:
        typeData = sheetType1.guiTypeData();
        break;
    case 2:
        typeData = sheetType2.guiTypeData();
        break;
    case 3:
        typeData = sheetType3.guiTypeData();
        break;
    case 4:
        typeData = sheetType4.guiTypeData();
        break;
    }
    return typeData;
}

//Shows a graph for the given person
void excelSheet::showGraph(string personName, int graphType, QCustomPlot *graph)
{
    switch (sheetType)
    {
    case 1:
        sheetType1.showGraph(personName, graphType, graph);
        break;
    case 2:
        sheetType2.showGraph(personName, graphType, graph);
        break;
    case 3:
        sheetType3.showGraph(personName, graphType, graph);
        break;
    case 4:
        sheetType4.showGraph(personName, graphType, graph);
        break;
    }
}

//Get the total number of entries
int excelSheet::getTotalEntries()
{
    int entryTotal;
    switch (sheetType)
    {
    case 1:
        entryTotal = sheetType1.getTotalEntries();
        break;
    case 2:
        entryTotal = sheetType2.getTotalEntries();
        break;
    case 3:
        entryTotal = sheetType3.getTotalEntries();
        break;
    case 4:
        entryTotal = sheetType4.getTotalEntries();
        break;
    }
    return entryTotal;
}

//Returns a pointer to the Parser object
Parser *excelSheet::getParse()
{
    Parser *parse = new Parser();
    switch (sheetType)
    {
    case 1:
        parse = sheetType1.getParse();
        break;
    case 2:
        parse = sheetType2.getParse();
        break;
    case 3:
        parse = sheetType3.getParse();
        break;
    case 4:
        parse = sheetType4.getParse();
        break;
    }
    return parse;
}

//Returns the error vector that contains a list of rows with missing mandatory fields
vector<string> excelSheet::getErrorVector()
{
    return errorVector;
}

//Returns the start year
int excelSheet::getStartYear()
{
    int year;
    switch (sheetType)
    {
    case 1:
        year = sheetType1.getStartYear();
        break;
    case 2:
        year = sheetType2.getStartYear();
        break;
    case 3:
        year = sheetType3.getStartYear();
        break;
    case 4:
        year = sheetType4.getStartYear();
        break;
    }
    return year;
}

//Returns the end year
int excelSheet::getEndYear()
{
    int year;
    switch (sheetType)
    {
    case 1:
        year = sheetType1.getEndYear();
        break;
    case 2:
        year = sheetType2.getEndYear();
        break;
    case 3:
        year = sheetType3.getEndYear();
        break;
    case 4:
        year = sheetType4.getEndYear();
        break;
    }
    return year;
}

//Returns the specified filepath
string excelSheet::getFilepath()
{
    return filepath;
}

//Updates the graph with a new start year and end year
void excelSheet::updateGraph(int startYear, int endYear)
{
    switch (sheetType)
    {
    case 1:
        sheetType1.updateGraph(startYear, endYear);
        break;
    case 2:
        sheetType2.updateGraph(startYear, endYear);
        break;
    case 3:
        sheetType3.updateGraph(startYear, endYear);
        break;
    case 4:
        sheetType4.updateGraph(startYear, endYear);
        break;
    }
}

//Updates the start year and end year being stored
void excelSheet::updateYears(int startYear, int endYear)
{
    switch (sheetType)
    {
    case 1:
        sheetType1.updateYears(startYear, endYear);
        break;
    case 2:
        sheetType2.updateYears(startYear, endYear);
        break;
    case 3:
        sheetType3.updateYears(startYear, endYear);
        break;
    case 4:
        sheetType4.updateYears(startYear, endYear);
        break;
    }
}

//Sets a boolean indicating whether mainwindow should reset
void excelSheet::setReset(bool reset)
{
    this->reset = reset;
}

//Gets a boolean indicating whether mainwindow should reset
bool excelSheet::getReset()
{
    return reset;
}
