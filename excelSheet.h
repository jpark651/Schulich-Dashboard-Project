/**
* Header file for the excelSheet class and its associated methods
*/
#ifndef EXCELSHEET_H_INCLUDED
#define EXCELSHEET_H_INCLUDED
#include <iostream>
#include <list>
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

class excelSheet
{
private:
    /*------ Variables ------*/

    int sheetType;
    funding sheetType1;
    presentations sheetType2;
    publications sheetType3;
    teaching sheetType4;


    /*------ Methods ------*/

    //returns the type of Excel file (1 = funding, 2 = presentations, 3 = publications, 4 = teaching)
    int getExcelType(string filename);


public:
    /*------ Constructors ------*/

    //first/last year is set to the earliest/latest year in the file
    excelSheet(string file);
    //first/last year is set using the given parameters
    excelSheet(string file, int startYear, int endYear);


    /*------ Methods ------*/

    //returns the type of Excel sheet (1 = funding, 2 = presentations, 3 = publications, 4 = teaching)
    int getExcelType();

    //returns the information to be printed to the GUI, with each type's data separated by a single hyphen
    vector<string> guiTypeData();

    //shows a graph for the given entry
    void showGraph(int entryIndex, int graphType);

    //get the total number of entries
    int getTotalEntries();

    //returns a reference to the Parser object
    Parser *getParse();
};

#endif //EXCELSHEET_H_INCLUDED

