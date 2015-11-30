/**
* Source file for the excelSheet class and its associated methods
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
}
//excelSheet constructor (first/last year is set using the given parameters)
excelSheet::excelSheet(string file, int firstYear, int lastYear)
{
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
}

//returns the type of Excel file (1 = funding, 2 = presentations, 3 = publications, 4 = teaching)
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

//returns the type of Excel sheet (1 = funding, 2 = presentations, 3 = publications, 4 = teaching)
int excelSheet::getExcelType()
{
    return sheetType;
}

//returns the information to be printed to the GUI, with each type's dataset separated by a single hyphen
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

//shows a graph for the given entry
void excelSheet::showGraph(int entryIndex, int graphType)
{
    switch (sheetType)
    {
    case 1:
        sheetType1.showGraph(entryIndex, graphType);
        break;
    case 2:
        sheetType2.showGraph(entryIndex, graphType);
        break;
    case 3:
        sheetType3.showGraph(entryIndex, graphType);
        break;
    case 4:
        sheetType4.showGraph(entryIndex, graphType);
        break;
    }
}

//get the total number of entries
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

//returns a reference to the Parser object
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

