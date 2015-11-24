/**
* Source file for the teaching class and its associated methods
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
//uninitiated constructor
teaching::teaching() {}

//returns the information to be printed to the GUI, with each type's dataset separated by a single hyphen
vector<string> teaching::guiTypeData()
{
    return storedData.guiTypeData();
}

//shows a graph for the given person
void teaching::showGraph(int personIndex, int graphType)
{
    storedData.showGraph(personIndex, graphType);
}

//get the total number of persons
int teaching::getPersonTotal()
{
    return storedData.getPersonTotal();
}

//returns a reference to the Parser object
Parser *teaching::getParse()
{
    return storedData.getParse();
}

