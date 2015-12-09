/**
  * Author: Team HoneyDew
  * Computer Science 3307, Group Project
  * December 9, 2015
  * This file implements the methods in Parser.h and parses a CSV file to get its respective rows
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <iterator>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <stdbool.h>
#include <vector>
#include "Parser.h"
#include "excelData.h"
using namespace std;

//Parser constructor
Parser:: Parser (string name, int type)
{
    filename = name;
    sheetType = type; // 1 = funding, 2 = presentations, 3 = publications, 4 = teaching
    numCols = colCount(filename);
    vector<vector<string> >temp(numCols);
    rows = temp;
    createCols(filename);
    createRows(filename);
    dateIndex = getDateIndex();
    parseDates(dateIndex);
    errorVector = getMissingFields(sheetType, rows);
}

//Uninitialized Parser constructor
Parser:: Parser () {}

//Helps to handle situations where cells are missing at the end of a line
int Parser:: countCommas(string s)
{
    int count =0;
    for (unsigned int i=0; i < s.length(); i++)
    {
        if (s.at(i) == ',')
        {
            count++;
        }
    }
    return count;
}

//Counts the number of column headers in a CSV file
int Parser:: colCount (string filename)
{
    ifstream file;
    file.open(filename.c_str());
    string line;
    getline(file,line);
    string cell;
    int no = 0;
    while (line.length()>0)
    {
        string temp = "";
        if (line.at(0) == '"')
        {
            int i=0;
            line.erase(0,1);
            while (1)
            {
                if (line.at(i) == '"')
                {
                    if (unsigned(i + 1) >= line.length())
                    {
                        break;
                    }
                    else if(line.at(i+1) == ',')
                    {
                        break;
                    }
                }
                temp += line.at(i);
                i++;
            }
            line.erase(0, temp.length()+1);
            if ((unsigned)countCommas(line) != line.length())
            {
                line.erase(0,1);
            }
            no++;
        }
        else if (line.at(0) == ',')
        {
            line.erase(0, 1);
            no++;
        }
        else
        {
            stringstream linestream(line);
            getline(linestream,cell, ',');
            line.erase(0, cell.length());
            if ((unsigned)countCommas(line) != line.length())
            {
                line.erase(0,1);
            }
            no++;
        }
    }
    file.close();
    return no;
}

//Parse all CSV files and store all items in a vector of vectors
void Parser:: createRows(string filename)
{
    ifstream myfile;
    string line;
    string temp;
    string cell;
    int commas = 0;
    myfile.open(filename.c_str());
    while (getline(myfile, line))
    {
        if (commas == 0)
        {
            commas = countCommas(line);
        }
        if (line.length() != (unsigned)commas)
        {
            int no = 0;
            while (no < commas)
            {
                bool quotes = false;
                while (line.length() > 0)
                {
                    temp = "";
                    if (line.at(0) == '"')
                    {
                        int lineLength = line.length();
                        if (quotes && lineLength > 1 && line.at(1) == '"')
                        {
                            temp += "\"\"";
                            line.erase(0, 1);
                        }
                        else if (quotes)
                        {
                            quotes = false;
                        }
                        else
                        {
                            quotes = true;
                        }
                        int i = 0;
                        line.erase(0, 1);
                        if (line.length() == 0)
                        {
                            if ((unsigned)(no + 1) < rows.size())
                            {
                                rows[no].push_back("");
                                no++;
                            }
                            goto done;
                        }
                        while (quotes)
                        {
                            if (line.at(i) == '"')
                            {
                                int lineLength = line.length();
                                if (lineLength > i + 1 && line.at(i + 1) == '"')
                                {
                                    temp += "\"";
                                    i++;
                                }
                                else
                                {
                                    quotes = false;
                                    break;
                                }
                            }
                            else if ((unsigned)(i + 1) >= line.length())
                            {
                                temp += line.at(i);
                                break;
                            }
                            temp += line.at(i);
                            i++;
                        }
                        line.erase(0, temp.length() + 1);
                        if ((unsigned)countCommas(line) != line.length())
                        {
                            line.erase(0, 1);
                        }
                        rows[no].push_back(temp);
                        no++;
                    }
                    else if (line.at(0) == ',')
                    {
                        line.erase(0, 1);
                        rows[no].push_back(temp);
                        no++;
                    }
                    else
                    {
                        stringstream linestream(line);
                        getline(linestream, cell, ',');
                        line.erase(0, cell.length());
                        if ((unsigned)countCommas(line) != line.length())
                        {
                            line.erase(0, 1);
                        }
                        rows[no].push_back(cell);
                        no++;
                    }
                }
done:
                if (no < commas || quotes)
                {
                    bool done = false;
                    while (!done)
                    {
                        no--;
                        string sameLine;
                        getline(myfile, sameLine);
                        string entry = rows[no].back();
                        rows[no].pop_back();
                        string entryEnd = "";
                        for (int i = 0, iMax = sameLine.length(); i < iMax && !done; i++)
                        {
                            char nextChar = sameLine.at(i);
                            if (nextChar != '"')
                            {
                                entryEnd += nextChar;
                            }
                            else if (quotes && i + 1 < iMax)
                            {
                                char afterNextChar = sameLine.at(i + 1);
                                if (afterNextChar == '"')
                                {
                                    entryEnd += nextChar;
                                    entryEnd += afterNextChar;
                                    i++;
                                }
                                else
                                {
                                    quotes = false;
                                    done = true;
                                }
                            }
                            else if (quotes)
                            {
                                quotes = false;
                                done = true;
                            }
                        }
                        sameLine.erase(0, entryEnd.length());
                        if (done)
                        {
                            sameLine.erase(0, 1);
                            if (sameLine.length() > 0 && sameLine.at(0) == ',')
                            {
                                sameLine.erase(0, 1);
                            }
                            line = sameLine;
                        }
                        rows[no].push_back(entry + "\n" + entryEnd);
                        no++;
                    }
                }
            }
        }
    }
    myfile.close();
}

//Parse the CSV file and store all the column headers in a vector
void Parser:: createCols(string filename)
{
    ifstream myfile;
    string line;
    string temp;
    string cell;
    myfile.open(filename.c_str());
    getline(myfile,line);
done:
    while (line.length()>0)
    {
        temp = "";
        if (line.at(0) == '"')
        {
            int i=0;
            line.erase(0,1);
            if (line.length() == 0)
            {
                goto done;
            }
            while (1)
            {
                if (line.at(i) == '"')
                {
                    if ((unsigned int)(i + 1) >= line.length())
                    {
                        break;
                    }
                    else if(line.at(i+1) == ',')
                    {
                        break;
                    }
                }
                else if ((unsigned int)(i + 1)>= line.length())
                {
                    break;
                }
                temp += line.at(i);
                i++;
            }
            line.erase(0, temp.length()+1);
            if ((unsigned int) countCommas(line) != line.length())
            {
                line.erase(0,1);
            }
            cols.push_back(temp);
        }
        else if (line.at(0) == ',')
        {
            line.erase(0, 1);
        }
        else
        {
            stringstream linestream(line);
            getline(linestream,cell, ',');
            line.erase(0, cell.length());
            if ((unsigned int)countCommas(line) != line.length())
            {
                line.erase(0,1);
            }
            cols.push_back(cell);
        }
    }
    myfile.close();
}

//Returns all rows in a CSV file
vector<vector<string> > Parser:: getRows()
{
    rows = getParsedFile (sheetType, rows);
    return rows;
}

//Returns all the column headers in a CSV file
vector<string> Parser:: getCols()
{
    return cols;
}

//Gets all of the column headers for the given file
vector<string> Parser:: getCols(string filepath)
{
    vector<string> temp = cols;
    createCols(filepath);
    vector<string> columns = cols;
    cols = temp;
    return columns;
}

//Gets index of the dates vector
int Parser:: getDateIndex()
{
    int found = -1;
    string temp;
    int i = 0;
    vector<string>:: iterator coliterator;
    for (coliterator = cols.begin(); coliterator != cols.end(); ++coliterator)
    {
        temp = *(coliterator);
        string searchTerm;
        switch (sheetType) // 1 = funding, 2 = presentations, 3 = publications, 4 = teaching
        {
        case 1:
            searchTerm = "Start Date";
            break;
        case 2:
            searchTerm = "Date";
            break;
        case 3:
            searchTerm = "Status Date";
            break;
        case 4:
            searchTerm = "Start Date";
            break;
        }
        if (temp.compare(searchTerm) == 0)
        {
            found = temp.find(searchTerm);
        }
        if (found != -1)
        {
            break;
        }
        i++;
    }
    return i;
}

//Parses the dates in the dates vectors so that they are all in years
void Parser:: parseDates(int dateIndex)
{
    vector <string> dates = rows[dateIndex];
    vector <string>:: iterator datesIterator;
    for (datesIterator = ++dates.begin(); datesIterator!= dates.end(); ++datesIterator)
    {
        string temp = *(datesIterator);
        string year = "";
        for (int i = 0, iMax = min((int)temp.length(), 4); i < iMax; i++)
        {
            year += temp.at(i);
        }
        *(datesIterator) = year;
    }
    rows[dateIndex] = dates;
}

//Returns a particular column stored at a particular index
vector <string> Parser:: getColumn(int index)
{
    return rows[index];
}


//Removes all rows in a grants clinical funding file that is missing mandatory fields
vector<vector<string> > Parser:: getParsedFunding(vector<vector<string> >rows)
{
    for (unsigned int i =0; i < rows.size(); i++)
    {
        if (rows[i][0].compare("Member Name") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Primary Domain") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Start Date") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("End Date") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Funding Type") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Status") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Peer Reviewed?") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Industry Grant?") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Role") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Title") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Principal Investigator") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Co-Investigators") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Total Amount") == 0)
        {
            rows = removeRows(i,rows);
        }
    }
    return rows;
}

//Removes all rows in a publications file that is missing mandatory fields
vector<vector<string> >  Parser::  getParsedPublications(vector<vector<string> >rows)
{
    for (unsigned int i =0; i < rows.size(); i++)
    {
        if (rows[i][0].compare("Member Name") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Primary Domain") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Publication Status") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Type") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Status Date") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Role") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Journal Name | Published In | Book Title | etc.") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Author(s)") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Title") == 0)
        {
            rows = removeRows(i,rows);
        }
    }
    return rows;
}

//Removes all rows in a presentations file that is missing mandatory fields
vector<vector<string> >  Parser:: getParsedPresentations(vector<vector<string> >rows)
{
    for (unsigned int i =0; i < rows.size(); i++)
    {
        if (rows[i][0].compare("Member Name") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Primary Domain") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Date") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Type") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Role") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Title") == 0)
        {
            rows = removeRows(i,rows);
        }
    }
    return rows;
}

//Removes all rows in a teaching file that are missing mandatory fields
vector<vector<string> >  Parser:: getParsedTeaching(vector<vector<string> >rows)
{
    for (unsigned int i =0; i < rows.size(); i++)
    {
        if (rows[i][0].compare("Member Name") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Primary Domain") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Start Date") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("End Date") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Program") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Type of Course / Activity") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Course / Activity") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Geographical Scope") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Hours per Teaching Session or Week") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Number of Teaching Sessions or Weeks") == 0)
        {
            rows = removeRows(i,rows);
        }
        else if (rows[i][0].compare("Total Hours") == 0)
        {
            rows = removeRows(i,rows);
        }
    }
    return rows;
}

//Decides which parsing method to call based off of sheet type
vector<vector<string> > Parser:: getParsedFile (int sheetType, vector<vector<string> > inputRows)
{
    vector<vector<string> > returnedRows;
    switch(sheetType)
    {
    case 1:
        returnedRows = getParsedFunding(inputRows);
        break;
    case 2:
        returnedRows = getParsedPresentations(inputRows);
        break;
    case 3:
        returnedRows = getParsedPublications(inputRows);
        break;
    case 4:
        returnedRows = getParsedTeaching(inputRows);
        break;
    }
    return returnedRows;
}

//Checks to see if a file is missing any mandatory fields and removes rows that are missing them
vector<vector<string> > Parser:: removeRows(int index, vector<vector<string> >inputRows)
{
    vector<string>temp = inputRows[index];
    for (unsigned int i = 1; i < temp.size(); i++)
    {
        if (temp[i].compare("") == 0)
        {
            for (unsigned int k = 0; k < inputRows.size(); k++)
            {
                vector <string> deletion = inputRows[k];
                deletion.erase(deletion.begin() + i);
                inputRows[k] = deletion;
            }
            temp.erase(temp.begin() + i);
            i--;
        }
    }
    return inputRows;
}

//Builds a vector containing the mandatory information that is missing for the rows in a funding file
vector<string> Parser:: getMissingFunding(vector<vector<string> >rows)
{
    vector<string>missingRows(rows[0].size());
    unsigned int sz = missingRows.size();
    for (unsigned int i =0; i < sz; i++)
    {
        stringstream ss;
        ss << "Row " << i + 1<< " is missing: ";
        string s = ss.str();
        missingRows.push_back(s);
        missingRows.erase(missingRows.begin());
    }
    for (unsigned int i =0; i < rows.size(); i++)
    {
        if (rows[i][0].compare("Member Name") == 0)
        {
            missingRows = missingFields(i,rows,missingRows);
        }
        else if (rows[i][0].compare("Primary Domain") == 0)
        {
            missingRows = missingFields(i,rows,missingRows);
        }
        else if (rows[i][0].compare("Start Date") == 0)
        {
            missingRows = missingFields(i,rows,missingRows);
        }
        else if (rows[i][0].compare("End Date") == 0)
        {
            missingRows = missingFields(i,rows,missingRows);
        }
        else if (rows[i][0].compare("Funding Type") == 0)
        {
            missingRows = missingFields(i,rows,missingRows);
        }
        else if (rows[i][0].compare("Status") == 0)
        {
            missingRows = missingFields(i,rows,missingRows);
        }
        else if (rows[i][0].compare("Peer Reviewed?") == 0)
        {
            missingRows = missingFields(i,rows,missingRows);
        }
        else if (rows[i][0].compare("Industry Grant?") == 0)
        {
            missingRows = missingFields(i,rows,missingRows);
        }
        else if (rows[i][0].compare("Role") == 0)
        {
            missingRows = missingFields(i,rows,missingRows);
        }
        else if (rows[i][0].compare("Title") == 0)
        {
            missingRows = missingFields(i,rows,missingRows);
        }
        else if (rows[i][0].compare("Principal Investigator") == 0)
        {
            missingRows= missingFields(i,rows,missingRows);
        }
        else if (rows[i][0].compare("Co-Investigators") == 0)
        {
            missingRows= missingFields(i,rows,missingRows);
        }
        else if (rows[i][0].compare("Total Amount") == 0)
        {
            missingRows = missingFields(i,rows,missingRows);
        }
    }
    return missingRows;
}

//Builds a vector containing the mandatory information that is missing for the rows in a publications file
vector<string> Parser:: getMissingPublications(vector<vector<string> >rows)
{
    vector<string>missingRows;
    vector<string>temp(rows[0].size());
    missingRows = temp;
    int sz = missingRows.size();
    for (int i =0; i < sz; i++)
    {
        stringstream ss;
        ss << "Row " << i + 1 << " is missing: ";
        string s = ss.str();
        missingRows.push_back(s);
        missingRows.erase(missingRows.begin());
    }
    for (unsigned int i =0; i < rows.size(); i++)
    {
        if (rows[i][0].compare("Member Name") == 0)
        {
            missingRows = missingFields(i,rows,missingRows);
        }
        else if (rows[i][0].compare("Primary Domain") == 0)
        {
            missingRows = missingFields(i,rows,missingRows);
        }
        else if (rows[i][0].compare("Publication Status") == 0)
        {
            missingRows = missingFields(i,rows,missingRows);
        }
        else if (rows[i][0].compare("Type") == 0)
        {
            missingRows = missingFields(i,rows,missingRows);
        }
        else if (rows[i][0].compare("Status Date") == 0)
        {
            missingRows = missingFields(i,rows,missingRows);
        }
        else if (rows[i][0].compare("Role") == 0)
        {
            missingRows = missingFields(i,rows,missingRows);
        }
        else if (rows[i][0].compare("Journal Name | Published In | Book Title | etc.") == 0)
        {
            missingRows = missingFields(i,rows,missingRows);
        }
        else if (rows[i][0].compare("Author(s)") == 0)
        {
            missingRows = missingFields(i,rows,missingRows);
        }
        else if (rows[i][0].compare("Title") == 0)
        {
            missingRows = missingFields(i,rows,missingRows);
        }
    }
    return missingRows;
}

//Builds a vector containing the mandatory information that is missing for the rows in a presentations file
vector<string> Parser:: getMissingPresentations(vector<vector<string> >rows)
{
    vector<string>missingRows;
    vector<string>temp(rows[0].size());
    missingRows = temp;
    int sz = missingRows.size();
    for (int i =0; i < sz; i++)
    {
        stringstream ss;
        ss << "Row " << i + 1 << " is missing: ";
        string s = ss.str();
        missingRows.push_back(s);
        missingRows.erase(missingRows.begin());
    }
    for (unsigned int i =0; i < rows.size(); i++)
    {
        if (rows[i][0].compare("Member Name") == 0)
        {
            missingRows = missingFields(i,rows, missingRows);
        }
        else if (rows[i][0].compare("Primary Domain") == 0)
        {
            missingRows = missingFields(i,rows, missingRows);
        }
        else if (rows[i][0].compare("Date") == 0)
        {
            missingRows = missingFields(i,rows, missingRows);
        }
        else if (rows[i][0].compare("Type") == 0)
        {
            missingRows = missingFields(i,rows, missingRows);
        }
        else if (rows[i][0].compare("Role") == 0)
        {
            missingRows = missingFields(i,rows, missingRows);
        }
        else if (rows[i][0].compare("Title") == 0)
        {
            missingRows = missingFields(i,rows, missingRows);
        }
    }
    return missingRows;
}

//Builds a vector containing the mandatory information that is missing for the rows in a teaching file
vector<string> Parser:: getMissingTeaching(vector<vector<string> >rows)
{
    vector<string>missingRows;
    vector<string>temp(rows[0].size());
    missingRows = temp;
    int sz = missingRows.size();
    for (int i =0; i < sz; i++)
    {
        stringstream ss;
        ss << "Row " << i + 1 << " is missing: ";
        string s = ss.str();
        missingRows.push_back(s);
        missingRows.erase(missingRows.begin());
    }
    for (unsigned int i =0; i < rows.size(); i++)
    {
        if (rows[i][0].compare("Member Name") == 0)
        {
            missingRows = missingFields(i,rows, missingRows);
        }
        else if (rows[i][0].compare("Primary Domain") == 0)
        {
            missingRows = missingFields(i,rows, missingRows);
        }
        else if (rows[i][0].compare("Start Date") == 0)
        {
            missingRows = missingFields(i,rows, missingRows);
        }
        else if (rows[i][0].compare("End Date") == 0)
        {
            missingRows = missingFields(i,rows, missingRows);
        }
        else if (rows[i][0].compare("Program") == 0)
        {
            missingRows = missingFields(i,rows, missingRows);
        }
        else if (rows[i][0].compare("Type of Course / Activity") == 0)
        {
            missingRows = missingFields(i,rows, missingRows);
        }
        else if (rows[i][0].compare("Course / Activity") == 0)
        {
            missingRows = missingFields(i,rows, missingRows);
        }
        else if (rows[i][0].compare("Geographical Scope") == 0)
        {
            missingRows = missingFields(i,rows, missingRows);
        }
        else if (rows[i][0].compare("Hours per Teaching Session or Week") == 0)
        {
            missingRows = missingFields(i,rows, missingRows);
        }
        else if (rows[i][0].compare("Number of Teaching Sessions or Weeks") == 0)
        {
            missingRows = missingFields(i,rows, missingRows);
        }
        else if (rows[i][0].compare("Total Hours") == 0)
        {
            missingRows = missingFields(i,rows, missingRows);
        }
    }
    return missingRows;
}

//Decides which missing fields method to call based off of the sheet type
vector<string> Parser:: getMissingFields (int sheetType, vector<vector<string> > rows)
{
    vector<string> returnedRows;
    switch(sheetType)
    {
    case 1:
        returnedRows = getMissingFunding(rows);
        break;
    case 2:
        returnedRows = getMissingPresentations(rows);
        break;
    case 3:
        returnedRows = getMissingPublications(rows);
        break;
    case 4:
        returnedRows = getMissingTeaching(rows);
        break;
    }
    return returnedRows;
}

//Updates the error vector to specify which row numbers are missing a particular field
vector<string> Parser:: missingFields(int index, vector<vector<string> >inputRows, vector<string>errorVector)
{
    vector<string>temp = inputRows[index];
    for (unsigned int i = 1; i < temp.size(); i++)
    {
        if (temp[i].compare("") == 0)
        {
            errorVector[i] = errorVector[i] + temp.front() + ", ";
        }
    }
    return errorVector;
}

//Returns the vector containing all errors in the file
vector<string> Parser:: getErrorVector()
{
    return errorVector;
}

