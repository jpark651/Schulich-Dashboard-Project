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

    //parses a string and returns the integer
    int stringToInt(string inputString);

    //parses a string and returns the double
    double stringToDouble(string inputString);

    //returns "true" for funding-type Excel files
    int isFunding();

    //returns "true" for presentation-type Excel files
    int isPresentations();

    //returns "true" for publications-type Excel files
    int isPublications();

    //returns "true" for teaching-type Excel files
    int isTeaching();

    //returns a currency string for the given long long
    string formatMoney(long long amount);

    //parses a currency string into a long long
    long long parseMoney(string amount);


    //returns true if the string is "True"
    bool parseBool(string boolTest);


    //returns an acronym for the Teaching type-string
    string acronymize(string type);


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

    //shows a graph for the given entry
    void showGraph(int entryIndex, int graphType);

    //get the total number of entries
    int getTotalEntries();

    //returns a reference to the Parser object
    Parser *getParse();
};

#endif //EXCELDATA_H_INCLUDED
