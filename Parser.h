/**
* Header file for the Parser class and its associated methods
*/
#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED
#include <string>
#include <fstream>
#include <list>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
using namespace std;
class Parser
{
    private:
        string filename;
        ifstream file;
        list <string> columns;
        list <list<string> > contents;
        list <list<string> > organized;
        list <list<string> >:: iterator listIterator;
        list <string> :: iterator itemIterator;
        list <int>:: iterator countIterator;
        list <int> itemCount;
    public:
//Empty Parser constructor
        Parser ();
//Parser constructor
        Parser (string file);
//generates a list containing all the column headers
        void createColumns ();
//creates a list of lists containing all the items under each column header
        void createRows();
//returns the columns list
        list<string> getColumns();
//returns the rows list
        list <string> getOrganizedRows();
//closes the ifstream file
        void closeFile();
//checks to see if the string contained in a cell is just a bunch of spaces
        bool allSpacing(string word);
//returns the number of columns in the file
        int getNumCols();
//returns the number of rows after the column headers
        int getNumRowsAfter();
//returns the list at a specific index in the contents list of lists
        list <string> getList(int index);
//returns the list at a specific index in the organized list of lists
        list <string> getList2(int index);
//updates the current list being accessed in the contents list of lists
        void updateList (list <string> listing, int index);
//updates the current list being accessed in the organized list of lists
        void updateList2 (list <string> listing, int index);
//checks the number of commas between each item in the line
        int commaChecker (string word, int index);
//Organizes all the rows in the content list into lists corresponding to the individual columns
        void organizeRows();
//Returns an item at a specific index
        string getItem(int index, list <string> listing);
//Returns the contents list
        list <list<string> > getContents();
//Returns the organized list
        list <list<string> > getOrganized();
//Gives years for all dates
        void parseDate(list <string>dates);
//get number of non-empty items in a list
        list<int> getNumItems();
//returns the itemCount list
        list<int> getItemCount();
//returns the number of items sotred in a specified list index
        int getNumberOfItems(int index);
};


#endif // PARSER_H_INCLUDED

