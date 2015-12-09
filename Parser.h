/**
  * Author: Team HoneyDew
  * Computer Science 3307, Group Project
  * December 9, 2015
  * Header file for the Parser class and its associated methods
*/
#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
using namespace std;
class Parser
{

//Instance variables
private:
    string filename;
    int sheetType;
    int numCols;
    vector<vector<string> >rows;
    vector<string> cols;
    vector<string>errorVector;
    int dateIndex;
public:
//Public methods

//Parser constructor
    Parser (string file, int type);

//Uninitialized Parser constructor
    Parser ();

//Gets the number of column headers in the file
    int colCount (string filename);

//Stores all the items in rows in a vector of vectors
    void createRows(string filename);

//Returns a vector of vectors containing all the items in the rows
    vector<vector<string> >getRows();

//Stores all the column headers in a vector
    void createCols(string filename);

//Gets all of the column headers
    vector<string>getCols();

//Gets all of the column headers for the given file
    vector<string>getCols(string filepath);

//Helps to handle  situations where empty cells occur at the end of a line
    int countCommas(string s);

//Gets the index of the in rows where dates are contained
    int getDateIndex();

//Parses the dates and sets all of them to years
    void parseDates(int dateIndex);

//Returns a particular column stored at a particular index
    vector <string> getColumn(int index);

//Removes all rows in grants clinical funding file that is missing mandatory fields
    vector<vector<string> > getParsedFunding(vector<vector<string> >rows);

//Removes all rows in publications file that is missing mandatory fields
    vector<vector<string> > getParsedPublications(vector<vector<string> >rows);

//Removes all rows in presentations file that is missing mandatory fields
    vector<vector<string> > getParsedPresentations(vector<vector<string> >rows);

//Removes all rows in teaching file that are missing mandatory fields
    vector<vector<string> > getParsedTeaching(vector<vector<string> >rows);

//Decides which parsing method to call based off of sheet type
    vector<vector<string> > getParsedFile (int sheetType, vector<vector<string> > inputRows);

//checks to see if a file is missing any mandatory fields and removes rows that are missing them
    vector<vector<string> > removeRows(int index, vector<vector<string> >inputRows);

//Builds a vector containing the mandatory information that is missing for the rows in funding file
    vector<string> getMissingFunding(vector<vector<string> >rows);

//Builds a vector containing the mandatory information that is missing for the rows in publications file
    vector<string> getMissingPublications(vector<vector<string> >rows);

//Builds a vector containing the mandatory information that is missing for the rows in presentations file
    vector<string> getMissingPresentations(vector<vector<string> >rows);

//Builds a vector containing the mandatory information that is missing for the rows in teaching file
    vector<string> getMissingTeaching(vector<vector<string> >rows);

//Decides which missing fields method to call based off of sheet type
    vector<string> getMissingFields (int sheetType, vector<vector<string> > rows);

//updates the error vector to specify which row numbers are missing a particular field
    vector<string> missingFields(int index, vector<vector<string> >inputRows, vector<string>errorVector);

//Returns the vector containing all errors in the file
    vector<string> getErrorVector();
};


#endif // PARSER_H_INCLUDED
