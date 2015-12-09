/**
  * Author: Team HoneyDew
  * Computer Science 3307, Group Project
  * December 9, 2015
  * Header file for the excelData class and its associated methods
*/
#ifndef EXCELDATA_H_INCLUDED
#define EXCELDATA_H_INCLUDED
#include <iostream>
#include <list>
#include <qcustomplot.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "graph.h"
#include "Parser.h"
using namespace std;

class excelData
{
//Friend classes that implement excelData object

    friend class funding;
    friend class presentations;
    friend class publications;
    friend class teaching;

private:
//Instance variables

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
    vector<vector<bool> > peerReviewed;
    vector<vector<string> > money;
    vector<vector<long long> > longMoney;
    vector<vector<double> > hours;
    vector<vector<int> > years;
    vector<vector<string> > namesByType;
    vector<vector<int> > countByType;
    vector<vector<double> > hoursByType;
    vector<vector<long long> > moneyByType;
    Parser *parse;
    bool graphed = false;
    graph storedGraph;


    /*------ Methods ------*/

//Initializes the excelData object
    void initializeObject(string file, int firstYear, int lastYear, bool hasDates);

//Creates a selection of columns based on header names
    vector<vector<string> > selectColumns(vector<vector<string> > organizedVects);

//Parses the vector of strings into a vector of integers ("selectYears")
    void parseYears();

//Sets "startYear"/"endYear" based on earliest/latest years in the file
    void setDates();

//Removes first string from each vector nested in the vector
    vector<vector<string> > removeFirstStrings(vector<vector<string> > selectedVects);

//Filters out entries which are outside the given date range
    vector<vector<string> > filterByDate(vector<vector<string> > selectedVects, int startYear, int endYear);

//Sorts filtered data into "names"/"types"/"years"
    void sortForGraph(vector<vector<string> > filteredVects);

//Sorts filtered data into "namesByType"/"countByType"
    void sortForGui(vector<vector<string> > filteredVects);

//Parses a string and returns the integer
    int stringToInt(string inputString);

//Parses a string and returns the double
    double stringToDouble(string inputString);

//Returns "true" for funding-type Excel files
    int isFunding();

//Returns "true" for presentation-type Excel files
    int isPresentations();

//Returns "true" for publications-type Excel files
    int isPublications();

//Returns "true" for teaching-type Excel files
    int isTeaching();

//Returns a currency string for the given long long
    string formatMoney(long long amount);

//Parses a currency string into a long long
    long long parseMoney(string amount);

//Returns true if the string is "True"
    bool parseBool(string boolTest);

//Returns an acronym for the Teaching type-string
    string acronymize(string type);


/*------ Constructors ------*/

//Default constructor (not initialized)
    excelData();


/*------Constructors ------*/// (public in friend class)

//First/last year is set to the earliest/latest year in the file
    excelData(string file, int type);

//First/last year is set using the given parameters
    excelData(string file, int startYear, int endYear, int type);


/*------ Methods ------*/// (public in friend class)

//Returns the information to be printed to the GUI, with each type's data separated by a single hyphen
    vector<string> guiTypeData();

//Shows a graph for the given person
    void showGraph(string personName, int graphType, QCustomPlot *plot);

//Get the total number of entries
    int getTotalEntries();

//Returns a pointer to the Parser object
    Parser *getParse();

//Returns the start year
    int getStartYear();

//Returns the end year
    int getEndYear();

//Updates the graph with a new start year and end year specified by the user
    void updateGraph(int startYear, int endYear);

//Updates the years in a given graph
    void updateYears(int startYear, int endYear);
};

#endif //EXCELDATA_H_INCLUDED
