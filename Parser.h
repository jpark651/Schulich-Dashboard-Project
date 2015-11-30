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
//instance variables
    private:
        string filename;
        int sheetType;
        int numCols;
        vector<vector<string> >rows;
        vector<string> cols;
        int dateIndex;
    public:
//Parser constructor
        Parser (string file, int type);
//uninitiated Parser constructor
        Parser ();

//Gets the number of column headers in the file
        int colCount (string filename);

//stores all the items in rows in a vector of vectors
        void createRows(string filename);

//returns a vector of vectors containing all the items in the rows
        vector<vector<string> >getRows();

//stores all the column headers in a vector
        void createCols(string filename);

//gets all of the column headers
        vector<string>getCols();

//gets all of the column headers for the given file
        vector<string>getCols(string filepath);

//helps to handle  situations where empty cells occur at the end of a line
        int countCommas(string s);

//Gets the index of the in rows where dates are contained
        int getDateIndex();

//parses the dates and sets all of them to years
        void parseDates(int dateIndex);

//Returns a particular column stored at a particular index
        vector <string> getColumn(int index);

//removes all rows in grants clinical funding that is missing mandatory fields
        vector<vector<string> > getParsedFunding(vector<vector<string> >rows);

//removes all rows in publications that is missing mandatory fields
        vector<vector<string> > getParsedPublications(vector<vector<string> >rows);

//removes all rows in presentations that is missing mandatory fields
        vector<vector<string> > getParsedPresentations(vector<vector<string> >rows);

//removes all rows in teaching that are missing mandatory fields
       vector<vector<string> > getParsedTeaching(vector<vector<string> >rows);

//Decides which parsing method to call based off of sheet type
        vector<vector<string> > getParsedFile (int sheetType, vector<vector<string> > inputRows);

//checks to see if a file is missing any mandatory fields and removes rows that are missing them
        vector<vector<string> > removeRows(int index, vector<vector<string> >inputRows);

};


#endif // PARSER_H_INCLUDED
