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
        list <list<string>> rows;
    public:
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
};


#endif // PARSER_H_INCLUDED
