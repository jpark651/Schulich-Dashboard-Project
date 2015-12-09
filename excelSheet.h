/**
  * Author: Team HoneyDew
  * Computer Science 3307, Group Project
  * December 9, 2015
  * Header file for the excelSheet class and its associated methods
*/
#ifndef EXCELSHEET_H_INCLUDED
#define EXCELSHEET_H_INCLUDED
#include <iostream>
#include <list>
#include <qcustomplot.h>
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
using namespace std;

//Defines the excelSheet class with its intance variables and associated methods
class excelSheet
{
private:

//Instance variables
    string filepath;
    int sheetType;
    funding sheetType1;
    presentations sheetType2;
    publications sheetType3;
    teaching sheetType4;
    vector<string> errorVector;
    bool reset = false;

//Private methods

//Returns the type of the csv file (1 = funding, 2 = presentations, 3 = publications, 4 = teaching)
    int getExcelType(string filename);

//Sets the error vector which contains a list of missing mandatory fields from each row
    void setErrorVector();


public:
//Public constructors

//First/last year is set to the earliest/latest year in the file
    excelSheet(string file);

//First/last year is set using the given parameters
    excelSheet(string file, int startYear, int endYear);

//Uninitialized constructor
    excelSheet();

//Public methods

//Returns the type of Excel sheet (1 = funding, 2 = presentations, 3 = publications, 4 = teaching)
    int getExcelType();

//Returns the information to be printed to the GUI, with each type's data separated by a single hyphen
    vector<string> guiTypeData();

//Shows a graph for the given person
    void showGraph(string personName, int graphType, QCustomPlot *graph);

//Get the total number of entries
    int getTotalEntries();

//Returns a pointer to the Parser object
    Parser *getParse();

//Returns the error vector containing a list of missing mandatory fields from each row
    vector<string> getErrorVector();

//Returns the start year
    int getStartYear();

//Returns the end year
    int getEndYear();

//Returns the specified filepath
    string getFilepath();

//Updates a graph with a new start year and end year
    void updateGraph(int startYear, int endYear);

//Updates the years for a funding, presentations, publications, or teaching object
    void updateYears(int startYear, int endYear);

//Sets a boolean indicating whether mainwindow should reset
    void setReset(bool reset);

//Gets a boolean indicating whether mainwindow should reset
    bool getReset();
};

#endif //EXCELSHEET_H_INCLUDED

