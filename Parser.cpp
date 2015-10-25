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
    list <list<string> > temp (getNumCols());
    organized = temp;
    list <list<string> > temp2 (getNumRowsAfter());
    contents = temp2;
    createRows();
    list <list<string> > temp3 (getNumCols());
    organized = temp3;
    organizeRows();
    parseDate(getList2(6));
}
//Loops through the first line of the csv file and extracts all strings that are not empty and puts them in a list
void Parser:: createColumns()
{
    const char * ctemp = filename.c_str();
    file.open(ctemp);
    file.clear();
    string value;
    string item;
    getline (file,value, '\n');
    char temp;
    for (unsigned int i =0; i < value.length(); i++)
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
    const char * ctemp = filename.c_str();
    file.open(ctemp);
    file.clear();
    string value;
    string item;
    int lineNum = 0;
    char temp;
    getline(file,value,'\n');
    value = "";
    while (getline(file, value, '\n'))
    {
        list <string> tempList = getList(lineNum);
        for (unsigned int i =0; i < value.length(); i++)
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
            else if (temp != ',') //&& isspace(temp) == false && //temp != '"')
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
                int commas = commaChecker(value, i);
                for (int k = 0; k < commas; i++, k++)
                {

                    tempList.push_back(" ");
                }
            }
            else if (temp == ',')
            {
                int commas = commaChecker(value, i);
                for (int k = 0; k < commas; i++, k++)
                {

                    tempList.push_back(" ");
                }
            }
        }
        if (tempList.size() != getNumCols())
        {
            tempList.push_back(" ");
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
    for (unsigned int i = 0; i < word.length(); i++)
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
//returns the number of rows after the column headers
int Parser:: getNumRowsAfter()
{
    const char * ctemp = filename.c_str();
    file.open(ctemp);
    file.clear();
    string value;
    int i =0;
    while (getline(file,value, '\n'))
    {
        i++;
    }
    file.close();
    return i-1;
}
//returns the list at a specified index in the contents list of lists
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
//returns the list at a specified index in the organized list of lists
list <string> Parser:: getList2(int index)
{
    list<string> found;
    int i =0;
    for (listIterator = organized.begin(); i <= index; i++, listIterator++)
    {
        if (i== index)
        {
            found = (*listIterator);
        }
    }
    return found;
}
//updates a list at a certain line in the contents list of lists
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

 //updates a list at a certain line in the organized list of lists
 void Parser:: updateList2 (list <string> listing, int index)
 {
    int i =0;
    for (listIterator = organized.begin(); i <= index; i++, listIterator++)
    {
        if (i == index)
        {
            (*listIterator) = listing;
        }
    }
 }

 //checks the number of commas between in a row in the line
 int Parser:: commaChecker(string word, int index)
 {
    int i = 0;
    while (1)
    {
       if (index + 1 < word.length())
       {
            index++;
            if (word.at(index)== ',')
            {
                i++;
            }
            else
            {
                goto done;
            }
       }
       else
       {
            break;
       }
    }
    done: return i;
 }

 //Organizes all the rows in the content list into lists corresponding to the individual columns
 void Parser:: organizeRows()
 {
    list <string>temp;
    list <string>temp2;
    for (int i =0; i < getNumCols(); i++)
    {
        temp = getList2(i);
        for (int k =0; k < getNumRowsAfter(); k++)
        {
            temp2 = getList(k);
            temp.push_back(getItem(i, temp2));
        }
        updateList2(temp, i);
    }
 }


//Returns an item at a specific index
 string Parser:: getItem(int index, list <string> listing)
 {
    int i =0;
    string item;
    for (itemIterator = listing.begin(); i <= index; itemIterator++, i++)
    {
        if (i == index)
        {
            item = (*itemIterator);
        }
    }
    return item;
 }

//Returns the contents list
 list <list<string> > Parser:: getContents()
 {
    return contents;
 }

 //Returns the organized list
 list <list<string> > Parser:: getOrganized()
 {
    return organized;
 }

 void Parser:: parseDate(list<string> dates)
 {
    for (itemIterator = dates.begin(); itemIterator!= dates.end(); itemIterator++)
    {
        string item = (*itemIterator);
        string temp = "";
        if (item.compare(" ") != 0)
        {
            for (int i = 0; i < 4; i++)
            {
                temp += item.at(i);
            }
        }
        else
        {
            temp = "0";
        }
        (*itemIterator) = temp;
    }
    updateList2(dates, 6);
 }


