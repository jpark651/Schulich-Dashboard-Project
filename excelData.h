/**
* Header file for the excelData class and its associated methods
*/
#ifndef EXCELDATA_H_INCLUDED
#define EXCELDATA_H_INCLUDED
#include <iostream>
#include <list>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "Parser.h"
using namespace std;

class excelData
{
    friend class funding;
    friend class presentations;
    friend class publications;
    friend class teaching;

private:
    /*------ Variables ------*/

    string pathname;
    int startYear;
    int endYear;
    int excelType;
    vector<vector<string> > organized;
    vector<vector<string> > selection;
    vector<int> selectYears;
    vector<vector<string> > filtered;
    vector<string> names;
    vector<vector<string> > types;
    vector<int> uniqueTypes;
    vector<vector<int> > years;
    vector<vector<string> > namesByType;
    vector<vector<int> > countByType;
    Parser *parse;


    /*------ Methods ------*/

    //initializes the excelData object
    void initializeObject(string file, int firstYear, int lastYear, bool hasDates);

    //creates a selection of columns based on header names
    vector<vector<string> > selectColumns(vector<vector<string> > organizedVects);

    //parses the vector of strings into a vector of integers ("selectYears")
    void parseYears();

    //sets "startYear"/"endYear" based on earliest/latest years in the file
    void setDates();

    //removes first string from each vector nested in the vector
    vector<vector<string> > removeFirstStrings(vector<vector<string> > selectedVects);

    //filters out entries which are outside the given date range
    vector<vector<string> > filterByDate(vector<vector<string> > selectedVects, int startYear, int endYear);

    //sorts filtered data into "names"/"types"/"years"
    void sortForGraph(vector<vector<string> > filteredVects);

    //sorts filtered data into "namesByType"/"countByType"
    void sortForGui(vector<vector<string> > filteredVects);

    //returns a list representation of the input vector
    template <typename T>
    list<T> vectorToList(vector<T> inputVector);

    //returns a nested list representation of the input nested vector
    template <typename T>
    list<list<T> > nestedVectorToList(vector<vector<T> > inputNestedVector);

    //returns a vector representation of the input list
    template <typename T>
    vector<T> listToVector(list<T> inputList);

    //returns a nested vector representation of the input nested list
    template <typename T>
    vector<vector<T> > nestedListToVector(list<list<T> > inputNestedList);

    //parses a string and returns the integer
    int stringToInt(string inputString);


    /*------ Constructors ------*/

    //default constructor (not initialized)
    excelData();


    /*------Constructors ------*/// (public in friend class)

    //first/last year is set to the earliest/latest year in the file
    excelData(string file, int type);
    //first/last year is set using the given parameters
    excelData(string file, int startYear, int endYear, int type);


    /*------ Methods ------*/// (public in friend class)

    //returns the information to be printed to the GUI, with each type's data separated by a single hyphen
    vector<string> guiTypeData();

    //shows a graph for the given person
    void showGraph(int personIndex, int graphType);

    //get the total number of persons
    int getPersonTotal();

    //returns a reference to the Parser object
    Parser *getParse();
};

#endif //EXCELDATA_H_INCLUDED