/**
* Header file for the publications class and its associated methods
*/
#ifndef PUBLICATIONS_H_INCLUDED
#define PUBLICATIONS_H_INCLUDED
#include "Parser.h"
#include <iostream>
#include <list>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;

class publications
{
    private:
        //variables
        string filename;
        int startYear;
        int endYear;
        list<list<string> > organized;
        list<list<string> > selection;
        list<list<string> > filtered;
        list<string> names;
        list<list<string> > types;
        list<int> uniqueTypes;
        list<list<int> > years;
        list<list<string> > namesByType;
        list<list<int> > countByType;
        Parser *parse;

    public:
        //constructor
        publications(string filename, int startYear, int endYear);

        //creates a selection of columns based on header names
        list<list<string> > selectColumns(list<list<string> > organizedLists);

        //filters out entries which are outside the given date range
        list<list<string> > filterByDate(list<list<string> > selectedLists, int startYear, int endYear);

        //sorts filtered data into "names"/"types"/"years"
        void sortForGraph(list<list<string> > filteredLists);

        //sorts filtered data into "namesByType"/"countByType"
        void sortForGui(list<list<string> > filteredLists);

        //returns the information to be printed to the GUI, with each type's data separated by a single hyphen
        list<string> guiTypeData();

        //shows a graph for the given entry index
        void showGraph(int entryIndex, int graphType);

        //get the total number of entries
        int getEntryTotal();

        //return a referene to the Parser object
        Parser *getParse();
};

#endif //PUBLICATIONS_H_INCLUDED

