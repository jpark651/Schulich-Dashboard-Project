/**
* Header file for the teaching class and its associated methods
*/
#ifndef TEACHING_H_INCLUDED
#define TEACHING_H_INCLUDED
#include <iostream>
#include <list>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "excelData.h"
#include "Parser.h"
using namespace std;

class teaching
{
private:
    /*------ Variables ------*/

    excelData storedData;


public:
    /*------ Constructors ------*/

    //first/last year is set to the earliest/latest year in the file
    teaching(string file);
    //first/last year is set using the given parameters
    teaching(string file, int startYear, int endYear);


    /*------ Methods ------*/

    //returns the information to be printed to the GUI, with each type's data separated by a single hyphen
    vector<string> guiTypeData();

    //shows a graph for the given person
    void showGraph(int personIndex, int graphType);

    //get the total number of persons
    int getPersonTotal();

    //returns a reference to the Parser object
    Parser *getParse();
};

#endif //TEACHING_H_INCLUDED

