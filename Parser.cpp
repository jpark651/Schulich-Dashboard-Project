/**
* This file implements the methods in Parser.h
*/
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <stdbool.h>
#include "Parser.h"
using namespace std;
//Parser constructor
Parser:: Parser (string name)
{
    filename = name;
    createColumns();
    list <list<string>> temp (getNumCols());
    rows = temp;
    list <list<string>> temp2 (getNumRowsAfter());
    contents = temp2;
    cout << contents.size() << endl;
    createRows();
}
//Loops through the first line of the csv file and extracts all strings that are not empty and puts them in a list
void Parser:: createColumns()
{
    file.open(filename);
    string value;
    string item;
    getline (file,value, '\n');
    char temp;
    for (int i =0; i < value.length(); i++)
    {
        temp = value.at(i);
        if (temp == '"')
        {
                item = "";
                while (1)
                {
                    i++;
                    temp = value.at(i);
                    if (temp =='"')
                    {
                        break;
                    }
                    else
                    {
                        item += temp;
                    }
                }
                if (allSpacing(item) == false)
                {
                    columns.push_back(item);
                }
        }
    }
    file.close();
}
//returns the columns
list<string> Parser:: getColumns()
{
    return columns;
}
//places all of the content held in the rows of the csv file into a list of lists
//the number of lists in the list corresponds to the number of rows that exist after the column headers
//all of the content from each row have been placed in their own list
//still need to figure out how to properly organize lists to correspond to column headers
void Parser:: createRows()
{
    file.open(filename);
    string value;
    string item;
    int lineNum = 0;
    char temp;
    getline(file,value,'\n');
    value = "";
    while (getline(file, value, '\n'))
    {
        list <string> tempList = getList(lineNum);
        for (int i =0; i < value.length(); i++)
        {
            temp = value.at(i);
            if (temp == '"')
            {
                    item = "";
                    while (1)
                    {
                        i++;
                        temp = value.at(i);
                        if (temp =='"')
                        {
                            break;
                        }
                        else
                        {
                            item += temp;
                        }
                    }
                    tempList.push_back(item);
            }
            else if (temp != ',' && isspace(temp) == false && temp != '"')
            {
                item = "";
                while (1)
                {
                    temp = value.at(i);
                    if (temp==',')
                    {
                        break;
                    }
                    item+=temp;
                    i++;
                }
                tempList.push_back(item);
            }
        }
        updateList(tempList, lineNum);
        lineNum++;
    }
   file.close();
}
//returns true if a string only contains spaces, false otherwise
bool Parser:: allSpacing(string word)
{
    bool flag = true;
    for (int i = 0; i < word.length(); i++)
    {
        if (isspace(word.at(i)) == false)
        {
            flag = false;
        }
    }
    return flag;
}
//returns the number of columns in the csv file
int Parser:: getNumCols()
{
    return columns.size();
}
//returns the number of
int Parser:: getNumRowsAfter()
{
    file.open(filename);
    string value;
    int i =0;
    while (getline(file,value, '\n'))
    {
        i++;
    }
    file.close();
    return i-1;
}
//returns the list at a specified index in the list of lists
list <string> Parser:: getList(int index)
{
    list<string> found;
    int i =0;
    for (listIterator = contents.begin(); i <= index; i++, listIterator++)
    {
        if (i== index)
        {
            found = (*listIterator);
        }
    }
    return found;
}
//updates a list at a certain index
 void Parser:: updateList (list <string> listing, int index)
 {
    int i =0;
    for (listIterator = contents.begin(); i <= index; i++, listIterator++)
    {
        if (i == index)
        {
            (*listIterator) = listing;
        }
    }
 }

