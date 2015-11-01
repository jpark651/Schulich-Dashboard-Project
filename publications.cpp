/**
* Header file for the publications class and its associated methods
*/
#include <iostream>
#include <iterator>
#include <list>
#include <sstream>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "graph.h"
#include "Parser.h"
#include "publications.h"
using namespace std;

//publications constructor (sets first/last year to the earlier/latest year in the file)
publications::publications(string file)
{
    initializeObject(file, 0, 0, false);
}
//publications constructor
publications::publications(string file, int firstYear, int lastYear)
{
    initializeObject(file, firstYear, lastYear, true);
}

//initializes the publications object
void publications::initializeObject(string file, int firstYear, int lastYear, bool hasDates)
{
    pathname = file;
    startYear = firstYear;
    endYear = lastYear;
    parse = new Parser(file);
    organized = nestedListToVector(parse->getOrganizedH());
    selection = selectColumns(organized);
    parseYears();
    if (!hasDates)
    {
        setDates();
        filtered = removeFirstStrings(selection);
    }
    else
    {
        filtered = filterByDate(selection, startYear, endYear);
    }
    sortForGraph(filtered);
    sortForGui(filtered);
}

//creates a selection of columns based on header names
vector<vector<string> > publications::selectColumns(vector<vector<string> > organizedVects)
{
    bool name = false, type = false, year = false, done = false;
    string nameTest = "Member Name";
    string typeTest = "Type";
    string yearTest = "Status Date";
    vector<string> nameVect, typeVect, yearVect;
    vector<vector<string> > columnVect = organized;
    for (int i = 0, iMax = columnVect.size(); i < iMax && !done; i++)
    {
        vector<string> columnRows = columnVect[i];
        if (!columnRows.empty())
        {
            string header = columnRows[0];
            if (!name && header.compare(nameTest) == 0)
            {
                nameVect = columnRows;
                name = true;
            }
            if (!type && header.compare(typeTest) == 0)
            {
                typeVect = columnRows;
                type = true;
            }
            if (!year && header.compare(yearTest) == 0)
            {
                yearVect = columnRows;
                year = true;
            }
        }
        if (name && type && year)
        {
            done = true;
        }
    }
    vector<vector<string> > selectionVect;
    selectionVect.push_back(nameVect);
    selectionVect.push_back(typeVect);
    selectionVect.push_back(yearVect);
    return selectionVect;
}

//parses the vector of strings into a vector of integers ("selectYears")
void publications::parseYears()
{
    if (selection.size() == 3)
    {
        vector<int> intYears;
        vector<string> yearsVect = selection[2];
        intYears.push_back(0);
        for (int i = 1, iMax = yearsVect.size(); i < iMax; i++)
        {
            intYears.push_back(stringToInt(yearsVect[i]));
        }
        selectYears = intYears;
    }
}

//sets "startYear"/"endYear" based on earliest/latest years in the file
void publications::setDates()
{
    int selectYearsSize = selectYears.size();
    if (selectYearsSize > 2)
    {
        int firstYear = selectYears[1], lastYear = selectYears[2];
        if (lastYear < firstYear)
        {
            int tempInt = firstYear;
            firstYear = lastYear;
            lastYear = tempInt;
        }
        for (int i = 3, iMax = selectYearsSize; i < iMax; i++)
        {
            int testInt = selectYears[i];
            if (testInt < firstYear)
            {
                firstYear = testInt;
            }
            else if (testInt > lastYear)
            {
                lastYear = testInt;
            }
        }
        startYear = firstYear;
        endYear = lastYear;
    }
    else if (selectYearsSize == 2)
    {
        startYear = endYear = selectYears[1];
    }
}

//removes first string from each vector nested in the vector
vector<vector<string> > publications::removeFirstStrings(vector<vector<string> > selectedVects)
{
    vector<vector<string> > filteredVects;
    int selectedVectsSize = selectedVects.size();
    if (selectedVectsSize == 3 && selectedVects[0].size() > 1)
    {
        for (int i = 0, iMax = selectedVectsSize; i < iMax; i++)
        {
            vector<string> currentVector(selectedVects[i].begin() + 1, selectedVects[i].end());
            filteredVects.push_back(currentVector);
        }
    }
    return filteredVects;
}

//filters out entries (from the selection) which are outside the given date range
vector<vector<string> > publications::filterByDate(vector<vector<string> > selectedVects, int startYear, int endYear)
{
    vector<string> nameVectFilt, typeVectFilt, yearVectFilt;
    if (selectedVects.size() == 3)
    {
        vector<string> nameVect, typeVect, yearVect;
        nameVect = selectedVects[0];
        typeVect = selectedVects[1];
        yearVect = selectedVects[2];
        for (int i = 1, iMax = selectYears.size(); i < iMax; i++)
        {
            int year = selectYears[i];
            if (year >= startYear && year <= endYear)
            {
                nameVectFilt.push_back(nameVect[i]);
                typeVectFilt.push_back(typeVect[i]);
                yearVectFilt.push_back(yearVect[i]);
            }
        }
    }
    vector<vector<string> > filtered;
    filtered.push_back(nameVectFilt);
    filtered.push_back(typeVectFilt);
    filtered.push_back(yearVectFilt);
    return filtered;
}

//sorts filtered data into "names"/"types"/"uniqueTypes"/"years"
void publications::sortForGraph(vector<vector<string> > filteredVects)
{
    if (filteredVects.size() == 3)
    {
        vector<string> namesVect, typesVect, yearsVect;
        namesVect = filteredVects[0];
        typesVect = filteredVects[1];
        yearsVect = filteredVects[2];

        vector<string> namesVectSort;
        vector<int> uniqueTypesVect;
        vector<vector<string> > typesVectSort;
        vector<vector<int> > yearsVectSort;
        for (int i = 0, iMax = namesVect.size(); i < iMax; i++)
        {
            string nextName = namesVect[i];
            string nextType = typesVect[i];
            string nextYear = yearsVect[i];
            bool exists = false;
            int count = -1;
            for (int j = 0, jMax = namesVectSort.size(); j < jMax && !exists; j++)
            {
                string testString = namesVectSort[j];
                if (testString.compare(nextName) == 0)
                {
                    exists = true;
                }
                count++;
            }
            if (!exists)
            {
                namesVectSort.push_back(nextName);
                vector<string> newTypesVect;
                vector<int> newYearsVect;
                typesVectSort.push_back(newTypesVect);
                yearsVectSort.push_back(newYearsVect);
                count++;
            }
            typesVectSort[count].push_back(nextType);
            const char * ctemp = nextYear.c_str();
            int nextYearInt = atoi(ctemp);
            yearsVectSort[count].push_back(nextYearInt);
        }

        for (int i = 0, totalVects = namesVectSort.size(); i < totalVects; i++)
        {
            vector<string> tempTypesVect = typesVectSort[i];
            vector<int> tempYearsVect = yearsVectSort[i];
            vector<string> newTypesVect;
            vector<int> newYearsVect;
            int count = 0;
            for (int j = 0, jMax = tempTypesVect.size(); j < jMax; j++)
            {
                string testType = tempTypesVect[j];
                int testYear = tempYearsVect[j];
                bool exists = false;
                for (int k = 0, kMax = newTypesVect.size(); k < kMax && !exists; k++)
                {
                    if (testType.compare(newTypesVect[k]) == 0)
                    {
                        vector<string>::iterator typesBegin = newTypesVect.begin() + k;
                        vector<int>::iterator yearsBegin = newYearsVect.begin() + k;
                        newTypesVect.insert(typesBegin, testType);
                        newYearsVect.insert(yearsBegin, testYear);
                        exists = true;
                    }
                }
                if (!exists)
                {
                    newTypesVect.push_back(testType);
                    newYearsVect.push_back(testYear);
                    count++;
                }
            }
            typesVectSort[i] = newTypesVect;
            yearsVectSort[i] = newYearsVect;
            uniqueTypesVect.push_back(count);
        }
        names = namesVectSort;
        uniqueTypes = uniqueTypesVect;
        types = typesVectSort;
        years = yearsVectSort;
    }
}

//sorts filtered data into "namesByType"/"countByType"
void publications::sortForGui(vector<vector<string> > filteredVects)
{
    if (filteredVects.size() == 3)
    {
        vector<string> namesVect, typesVect;
        namesVect = filteredVects[0];
        typesVect = filteredVects[1];

        vector<vector<string> > dataNamesVect;
        vector<vector<int> > dataCountVect;
        vector<string> title;
        title.push_back("Publications");
        dataNamesVect.push_back(title);
        vector<int> total;
        total.push_back(0);
        dataCountVect.push_back(total);
        for (int i = 0, iMax = typesVect.size(); i < iMax; i++)
        {
            string typeTest = typesVect[i];
            string nameTest = namesVect[i];
            bool exists = false;
            for (int j = 1, jMax = dataNamesVect.size(); j < jMax && !exists; j++)
            {
                string tempType = dataNamesVect[j][0];
                if (tempType.compare(typeTest) == 0)
                {
                    bool nameExists = false;
                    for (int k = 1, kMax = dataNamesVect[j].size(); k < kMax && !nameExists; k++)
                    {
                        string tempName = dataNamesVect[j][k];
                        if (tempName.compare(nameTest) == 0)
                        {
                            dataCountVect[0][0]++;
                            dataCountVect[j][0]++;
                            dataCountVect[j][k]++;
                            nameExists = true;
                        }
                    }
                    if (!nameExists)
                    {
                        dataNamesVect[j].push_back(nameTest);
                        dataCountVect[0][0]++;
                        dataCountVect[j][0]++;
                        dataCountVect[j].push_back(1);
                    }
                    exists = true;
                }
            }
            if (!exists)
            {
                vector<string> newNameVect;
                vector<int> newCountVect;
                newNameVect.push_back(typeTest);
                newNameVect.push_back(nameTest);
                newCountVect.push_back(1);
                newCountVect.push_back(1);
                dataCountVect[0][0]++;
                dataNamesVect.push_back(newNameVect);
                dataCountVect.push_back(newCountVect);
            }
        }
        namesByType = dataNamesVect;
        countByType = dataCountVect;
    }
}

//returns the information to be printed to the GUI, with each type's dataset separated by a single hyphen
vector<string> publications::guiTypeData()
{
    vector<string> guiData;
    for (int i = 0, iMax = countByType.size(); i < iMax; i++)
    {
        vector<string> namesVect = namesByType[i];
        vector<int> countVect = countByType[i];
        if (i > 1)
        {
            string hyphen = "-";
            guiData.push_back(hyphen);
        }
        for (int j = 0, jMax = namesVect.size(); j < jMax; j++)
        {
            guiData.push_back(namesVect[j]);
            stringstream ss;
            ss << countVect[j];
            string count = ss.str();
            guiData.push_back(count);
        }
    }
    return guiData;
}

//shows a graph for the given person
void publications::showGraph(int personIndex, int graphType)
{
    if (personIndex < getPersonTotal())
    {
        graph newGraph;
        newGraph.preparePublications(names[personIndex], vectorToList(types[personIndex]), vectorToList(years[personIndex]),
                                     uniqueTypes[personIndex], startYear, endYear, graphType);
    }
}

//returns a list representation of the input vector
template <typename T>
list<T> publications::vectorToList(vector<T> inputVector)
{
    list<T> result(inputVector.begin(), inputVector.end());
    return result;
}

//returns a nested list representation of the input nested vector
template <typename T>
list<list<T> > publications::nestedVectorToList(vector<vector<T> > inputNestedVector)
{
    list<list<T> > result;
    vector<list<T> > listVect;
    for (int i = 0, iMax = inputNestedVector.size(); i < iMax; i++)
    {
        listVect.push_back(vectorToList(inputNestedVector[i]));
    }
    result = vectorToList(listVect);
    return result;
}

//returns a vector representation of the input list
template <typename T>
vector<T> publications::listToVector(list<T> inputList)
{
    vector<T> result{make_move_iterator(begin(inputList)), make_move_iterator(end(inputList))};
    return result;
}

//returns a nested vector representation of the input nested list
template <typename T>
vector<vector<T> > publications::nestedListToVector(list<list<T> > inputNestedList)
{
    vector<vector<T> > result;
    vector<list<T> > listVect = listToVector(inputNestedList);
    for (int i = 0, iMax = listVect.size(); i < iMax; i++)
    {
        result.push_back(listToVector(listVect[i]));
    }
    return result;
}

//parses a string and returns the integer
int publications::stringToInt(string inputString)
{
    const char * ctemp = inputString.c_str();
    return atoi(ctemp);
}

//get the total number of persons
int publications::getPersonTotal()
{
    return names.size();
}

//returns a reference to the Parser object
Parser *publications::getParse()
{
    return parse;
}

