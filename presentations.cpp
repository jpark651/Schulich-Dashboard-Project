/**
* Source file for the presentations class and its associated methods
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
//uninitiated constructor
presentations::presentations() {}

//returns the information to be printed to the GUI, with each type's dataset separated by a single hyphen
vector<string> presentations::guiTypeData()
{
    return storedData.guiTypeData();
}

//shows a graph for the given person
void presentations::showGraph(int personIndex, int graphType)
{
    storedData.showGraph(personIndex, graphType);
}

//get the total number of persons
int presentations::getPersonTotal()
{
    return storedData.getPersonTotal();
}

//returns a reference to the Parser object
Parser *presentations::getParse()
{
    return storedData.getParse();
}

