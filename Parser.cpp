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
using namespace std;
//Parser constructor
Parser:: Parser (string name)
{
    filename = name;
    numCols = colCount(filename);
    vector<vector<string>>temp(numCols);
    rows = temp;
    createCols(filename);
    createRows(filename);
}

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
    file.open(filename);
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
    myfile.open(filename);
    getline(myfile,line);
    while (getline(myfile,line))
    {
        int no = 0;

        while (line.length()>0)
        {
            temp = "";
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
                rows[no].push_back(temp);
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
                rows[no].push_back(cell);
                no++;
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
    myfile.open(filename);
    getline(myfile,line);
    while (line.length()>0)
    {
        temp = "";
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
vector<vector<string>> Parser:: getRows()
{
    return rows;
}

//Returns all the column headers in a CSV file
vector<string> Parser:: getCols()
{
    return cols;
}



