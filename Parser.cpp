/**
* This file implements the methods in Parser.h
*/
#include <string.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "Parser.h"
using namespace std;
//Parser constructor
Parser:: Parser (string name)
{
    filename = name;
    file.open(name);
    createColumns();
}
//Loops through the first line of the csv file and extracts all strings that are not empty and puts them in a list
void Parser:: createColumns()
{
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
}
//returns the columns
list<string> Parser:: getColumns()
{
    return columns;
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

