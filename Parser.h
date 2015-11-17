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
    int numCols;
    vector<vector<string>>rows;
    vector<string> cols;
public:
//Parser constructor
    Parser (string file);

//Gets the number of column headers in the file
    int colCount (string filename);

//stores all the items in rows in a vector of vectors
    void createRows(string filename);

//returns a vector of vectors containing all the items in the rows
    vector<vector<string>>getRows();

//stores all the column headers in a vector
    void createCols(string filename);

//gets all of the column headers
    vector<string>getCols();

//helps to handle  situations where empty cells occur at the end of a line
    int countCommas(string s);
};


#endif // PARSER_H_INCLUDED

