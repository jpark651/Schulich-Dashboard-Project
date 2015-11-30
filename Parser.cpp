/**
* This file implements the methods in Parser.h
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
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
}
//uninitiated Parser constructor
Parser:: Parser () {}

//helps to handle situations where cells are missing at the end of a line
int Parser:: countCommas(string s)
{
    int count =0;
    for (int i=0; i < s.length(); i++)
    {
        if (s.at(i) == ',')
        {
            count++;
        }
    }
    return count;
}
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
                    if (i + 1 >= line.length())
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
            if (countCommas(line) != line.length())
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
            if (countCommas(line) != line.length())
            {
                line.erase(0,1);
            }
            no++;
        }
    }
    file.close();
    return no;
}

//parse all CSV files and store all items in a vector of vectors
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
        if (line.length() != commas)
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
                            if (no + 1 < rows.size())
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
                            else if (i + 1 >= line.length())
                            {
                                temp += line.at(i);
                                break;
                            }
                            temp += line.at(i);
                            i++;
                        }
                        line.erase(0, temp.length() + 1);
                        if (countCommas(line) != line.length())
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
                        if (countCommas(line) != line.length())
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
                    if (i + 1 >= line.length())
                    {
                        break;
                    }
                    else if(line.at(i+1) == ',')
                    {
                        break;
                    }
                }
                else if (i + 1>= line.length())
                {
                    break;
                }
                temp += line.at(i);
                i++;
            }
            line.erase(0, temp.length()+1);
            if (countCommas(line) != line.length())
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
            if (countCommas(line) != line.length())
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

//gets all of the column headers for the given file
vector<string> Parser:: getCols(string filepath)
{
    vector<string> temp = cols;
    createCols(filepath);
    vector<string> columns = cols;
    cols = temp;
    return columns;
}

//gets index of the dates vector
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

//parses the dates in the dates vectors so that they are all in years
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


//removes all rows in grants clinical funding that is missing mandatory fields
vector<vector<string> > Parser:: getParsedFunding(vector<vector<string> >rows)
{
    for (int i =0; i < rows.size(); i++)
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

//removes all rows in publications that is missing mandatory fields
vector<vector<string> >  Parser::  getParsedPublications(vector<vector<string> >rows)
{
    for (int i =0; i < rows.size(); i++)
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

//removes all rows in presentations that is missing mandatory fields
vector<vector<string> >  Parser:: getParsedPresentations(vector<vector<string> >rows)
{
    for (int i =0; i < rows.size(); i++)
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

//removes all rows in teaching that are missing mandatory fields
vector<vector<string> >  Parser:: getParsedTeaching(vector<vector<string> >rows)
{
    for (int i =0; i < rows.size(); i++)
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

//checks to see if a file is missing any mandatory fields and removes rows that are missing them
vector<vector<string> > Parser:: removeRows(int index, vector<vector<string> >inputRows)
{
    vector<string>temp = inputRows[index];
    for (int i = 1; i < temp.size(); i++)
    {
        if (temp[i].compare("") == 0)
        {
            for (int k = 0; k < inputRows.size(); k++)
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
