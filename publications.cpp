/**
* Header file for the publications class and its associated methods
*/
#include <iostream>
#include <iterator>
#include <list>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <sstream>
#include "graph.h"
#include "Parser.h"
#include "publications.h"
using namespace std;

//publications constructor
publications:: publications (string file, int firstYear, int lastYear)
{
    filename = file;
    startYear = firstYear;
    endYear = lastYear;
    parse = new Parser(file);
    organized = parse->getOrganized();
    selection = selectColumns(organized);
    filtered = filterByDate(selection, startYear, endYear);
    sortForGraph(filtered);
    sortForGui(filtered);
}

//creates a selection of columns based on header names
list<list<string> > publications:: selectColumns(list<list<string> > organizedLists)
{
    bool name, type, year, done = false;
    string nameTest = "Member Name";
    string typeTest = "Type";
    string yearTest = "Status Date";
    list<string> nameList, typeList, yearList;
    list<list<string> > columnList = organized;
    while (!columnList.empty() && !done)
    {
        list <string> columnRows = columnList.front();
        columnRows.pop_front();
        if (!columnRows.empty())
        {
            string header = columnRows.front();
            int compare;
            if (!name)
            {
                compare = header.compare(nameTest);
                if (compare == 0)
                {
                    nameList = columnRows;
                    name = true;
                }
            }
            if (!type)
            {
                compare = header.compare(typeTest);
                if (compare == 0)
                {
                    typeList = columnRows;
                    type = true;
                }
            }
            if (!year)
            {
                compare = header.compare(yearTest);
                if (compare == 0)
                {
                    yearList = columnRows;
                    year = true;
                }
            }
        }
        if (name && type && year)
        {
            done = true;
        }
    }
    list<list<string> > selectionList;
    selectionList.push_back(nameList);
    selectionList.push_back(typeList);
    selectionList.push_back(yearList);
    return selectionList;
}

//filters out entries (from the selection) which are outside the given date range
list<list<string> > publications:: filterByDate(list<list<string> > selectedLists, int startYear, int endYear)
{
    list<string> nameListFilt, typeListFilt, yearListFilt;
    if (selectedLists.size() == 3)
    {
        list<string> nameList, typeList, yearList;
        nameList = selectedLists.front();
        selectedLists.pop_front();
        typeList = selectedLists.front();
        selectedLists.pop_front();
        yearList = selectedLists.front();
        if (!yearList.empty())
        {
            nameList.pop_front();
            typeList.pop_front();
            yearList.pop_front();
        }
        while (!yearList.empty())
        {
            string next = yearList.front();
            yearList.pop_front();
            const char * ctemp = next.c_str();
            int year = atoi(ctemp);
            if (year >= startYear && year <= endYear)
            {
                string tempName, tempType, tempYear;
                tempName = nameList.front();
                tempType = typeList.front();
                tempYear = next;
                nameListFilt.push_back(tempName);
                typeListFilt.push_back(tempType);
                yearListFilt.push_back(tempYear);
            }
            nameList.pop_front();
            typeList.pop_front();
        }
    }
    list<list<string> > filtered;
    filtered.push_back(nameListFilt);
    filtered.push_back(typeListFilt);
    filtered.push_back(yearListFilt);
    return filtered;
}

//sorts filtered data into "names"/"types"/"years"
void publications:: sortForGraph (list<list<string> > filteredLists)
{
    if (filteredLists.size() == 3)
    {
        list<string> namesList, typesList, yearsList;
        namesList = filteredLists.front();
        filteredLists.pop_front();
        typesList = filteredLists.front();
        filteredLists.pop_front();
        yearsList = filteredLists.front();

        list<string> namesListSort;
        list<int> uniqueTypesList;
        vector<list<string> > typesListSort;
        vector<list<int> > yearsListSort;
        while (!namesList.empty())
        {
            string nextName = namesList.front();
            string nextType = typesList.front();
            string nextYear = yearsList.front();
            namesList.pop_front();
            typesList.pop_front();
            yearsList.pop_front();
            list<string> tempNames = namesListSort;
            bool exists = false;
            int count = -1;
            while (!tempNames.empty() && !exists)
            {
                string testString = tempNames.front();
                tempNames.pop_front();
                int compare = testString.compare(nextName);
                if (compare == 0)
                {
                    exists = true;
                }
                count++;
            }
            if (!exists)
            {
                namesListSort.push_back(nextName);
                list<string> newTypesList;
                list<int> newYearsList;
                typesListSort.push_back(newTypesList);
                yearsListSort.push_back(newYearsList);
                count++;
            }
            typesListSort[count].push_back(nextType);
            const char * ctemp = nextYear.c_str();
            int nextYearInt = atoi(ctemp);
            yearsListSort[count].push_back(nextYearInt);
        }

        int totalLists = namesListSort.size();
        for (int i = 0; i < totalLists; i++)
        {
            list<string> tempTypesList = typesListSort[i];
            list<int> tempYearsList = yearsListSort[i];
            vector<string> newTypesList;
            vector<int> newYearsList;
            int count = 0;
            while (!tempTypesList.empty())
            {
                string testType = tempTypesList.front();
                int testYear = tempYearsList.front();
                tempTypesList.pop_front();
                tempYearsList.pop_front();
                int jMax = newTypesList.size();
                bool exists = false;
                for (int j = 0; j < jMax && !exists; j++)
                {
                    int compare = testType.compare(newTypesList[j]);
                    if (compare == 0)
                    {
                        vector<string>::iterator typesBegin = newTypesList.begin() + j;
                        vector<int>::iterator yearsBegin = newYearsList.begin() + j;
                        newTypesList.insert(typesBegin, testType);
                        newYearsList.insert(yearsBegin, testYear);
                        exists = true;
                    }
                }
                if (!exists)
                {
                    newTypesList.push_back(testType);
                    newYearsList.push_back(testYear);
                    count++;
                }
            }
            list<string> stringList(newTypesList.begin(), newTypesList.end());
            typesListSort[i] = stringList;
            list<int> intList(newYearsList.begin(), newYearsList.end());
            yearsListSort[i] = intList;
            uniqueTypesList.push_back(count);
        }
        names = namesListSort;
        uniqueTypes = uniqueTypesList;
        list<list<string> > typesSorted(typesListSort.begin(), typesListSort.end());
        types = typesSorted;
        list<list<int> > yearsSorted(yearsListSort.begin(), yearsListSort.end());
        years = yearsSorted;
    }
}

//sorts filtered data into "namesByType"/"countByType"
void publications:: sortForGui (list<list<string> > filteredLists)
{
    if (filteredLists.size() == 3)
    {
        list<string> namesList, typesList;
        namesList = filteredLists.front();
        filteredLists.pop_front();
        typesList = filteredLists.front();

        vector<vector<string> > dataNamesList;
        vector<vector<int> > dataCountList;
		vector<string> title;
		title[0] = "Publications";
		dataNamesList.push_back(title);
		vector<int> total;
		total[0] = 0;
		dataCountList.push_back(total);
        while (!typesList.empty())
        {
            string typeTest = typesList.front();
            typesList.pop_front();
            int iMax = dataNamesList.size();
            bool exists = false;
            for (int i = 1; i < iMax && !exists; i++)
            {
                string tempType = dataNamesList[i][0];
                int compare = tempType.compare(typeTest);
                if (compare == 0)
                {
                    string nameTest = namesList.front();
                    namesList.pop_front();
                    bool nameExists = false;
                    for (int j = 1; j < dataNamesList[i].size() && !nameExists; j++)
                    {
                        string tempName = dataNamesList[i][j];
                        compare = tempName.compare(nameTest);
                        if (compare == 0)
                        {
							dataCountList[0][0]++;
                            dataCountList[i][0]++;
                            dataCountList[i][j]++;
                            nameExists = true;
                        }
                    }
                    if (!nameExists)
                    {
                        dataNamesList[i].push_back(nameTest);
						dataCountList[0][0]++;
                        dataCountList[i][0]++;
                        dataCountList[i].push_back(1);
                    }
                    exists = true;
                }
            }
            if (!exists)
            {
                vector<string> newNameList;
                vector<int> newCountList;
                newNameList.push_back(typeTest);
                newCountList.push_back(1);
                newNameList.push_back(namesList.front());
                namesList.pop_front();
                newCountList.push_back(1);
				dataCountList[0][0]++;
                dataNamesList.push_back(newNameList);
                dataCountList.push_back(newCountList);
            }
        }

        vector<list<string> > namesToListVect;
        vector<list<int> > countToListVect;
        for (int i = 0; i < dataNamesList.size(); i++)
        {
            list<string> newNamesList(dataNamesList[i].begin(), dataNamesList[i].end());
            namesToListVect.push_back(newNamesList);
        }
        for (int i = 0; i < dataCountList.size(); i++)
        {
            list<int> newCountList(dataCountList[i].begin(), dataCountList[i].end());
            countToListVect.push_back(newCountList);
        }
        list<list<string> > namesToList(namesToListVect.begin(), namesToListVect.end());
        namesByType = namesToList;
        list<list<int> > countToList(countToListVect.begin(), countToListVect.end());
        countByType = countToList;
    }
}

//returns the information to be printed to the GUI, with each type's dataset separated by a single hyphen
list<string> publications:: guiTypeData ()
{
    list<string> guiData;
    int counter = 0;
    while (!namesByType.empty())
    {
        list<string> namesList = namesByType.front();
        list<int> countList = countByType.front();
        namesList.pop_front();
        countList.pop_front();
        if (counter > 1)
        {
            string hyphen = "-";
            guiData.push_back(hyphen);
        }
		counter++;
        while (!namesList.empty())
        {
            guiData.push_back(namesList.front());
            stringstream ss;
            ss << countList.front();
            string count = ss.str();
            guiData.push_back(count);
            namesList.pop_front();
            countList.pop_front();
        }
    }
    return guiData;
}

//shows a graph for the given person entry index
void publications:: showGraph(int entryIndex, int graphType)
{
    if (entryIndex < getEntryTotal())
    {
        list<string> tempNames = names;
        list<list<string> > tempTypes = types;
        list<list<int> > tempYears = years;
        list<int> tempUniqueTypes = uniqueTypes;
        for (int i = 0; i < entryIndex; i++)
        {
            tempNames.pop_front();
            tempTypes.pop_front();
            tempYears.pop_front();
            tempUniqueTypes.pop_front();
        }
        string tName = tempNames.front();
        list<string> tType = tempTypes.front();
        list<int> tYear = tempYears.front();
        int tUniqueType = tempUniqueTypes.front();

        graph newGraph;
        newGraph.preparePublications(tName, tType, tYear, tUniqueType, startYear, endYear, graphType);
    }
}

//get the total number of person entries
int publications:: getEntryTotal()
{
    return names.size();
}

//returns a reference to the parser object
Parser *publications:: getParse()
{
    return parse;
}

