/**
* Source file for the excelData class and its associated methods
*/
#include <iostream>
#include <iterator>
#include <list>
#include <qcustomplot.h>
#include <sstream>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "graph.h"
#include "Parser.h"
#include "excelData.h"
using namespace std;

//excelData constructor (first/last year is set using the earliest/latest year in the file)
excelData::excelData(string file, int type)
{
    excelType = type; // 1 = funding, 2 = presentations, 3 = publications, 4 = teaching
    initializeObject(file, 0, 0, false);
}
//excelData constructor (first/last year is set using the given parameters)
excelData::excelData(string file, int firstYear, int lastYear, int type)
{
    excelType = type; // 1 = funding, 2 = presentations, 3 = publications, 4 = teaching
    initializeObject(file, firstYear, lastYear, true);
}
//default excelData constructor (not initialized)
excelData::excelData(){}

//initializes the excelData object
void excelData::initializeObject(string file, int firstYear, int lastYear, bool hasDates)
{
    pathname = file;
    startYear = firstYear;
    endYear = lastYear;
    parse = new Parser(file, excelType);
    organized = parse->getRows();
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
vector<vector<string> > excelData::selectColumns(vector<vector<string> > organizedVects)
{
    bool name = false, type = false, year = false, money = false, hours = false, peer = false, done = false;
    string nameTest = "Member Name", typeTest, yearTest, moneyTest, hoursTest, peerTest;
    switch (excelType) // 1 = funding, 2 = presentations, 3 = publications, 4 = teaching
    {
        case 1:
            typeTest = "Funding Type";
            moneyTest = "Total Amount";
            peerTest = "Peer Reviewed?";
            yearTest = "Start Date";
            break;

        case 2:
            typeTest = "Type";
            yearTest = "Date";
            break;

        case 3:
            typeTest = "Type";
            yearTest = "Status Date";
            break;

        case 4:
            typeTest = "Program";
            hoursTest = "Total Hours";
            yearTest = "Start Date";
            break;
    }
    vector<string> nameVect, typeVect, yearVect, moneyVect, hoursVect, peerVect;
    vector<vector<string> > columnVect = organizedVects;
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
            if (isFunding() && !money && header.compare(moneyTest) == 0)
            {
                moneyVect = columnRows;
                money = true;
            }
            if (isFunding() && !peer && header.compare(peerTest) == 0)
            {
                peerVect = columnRows;
                peer = true;
            }
            if (isTeaching() && !hours && header.compare(hoursTest) == 0)
            {
                hoursVect = columnRows;
                hours = true;
            }
        }
        if (name && type && year)
        {
            if (isFunding())
            {
                if (money && peer)
                {
                    done = true;
                }
            }
            else if (isTeaching())
            {
                if (hours)
                {
                    done = true;
                }
            }
            else
            {
                done = true;
            }
        }
    }
    vector<vector<string> > selectionVect;
    selectionVect.push_back(nameVect);
    selectionVect.push_back(typeVect);
    selectionVect.push_back(yearVect);
    if (isFunding())
    {
        selectionVect.push_back(moneyVect);
        selectionVect.push_back(peerVect);
    }
    else if (isTeaching())
    {
        selectionVect.push_back(hoursVect);
    }
    return selectionVect;
}

//parses the vector of strings into a vector of integers ("selectYears")
void excelData::parseYears()
{
    if (selection.size() >= 3)
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
void excelData::setDates()
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
vector<vector<string> > excelData::removeFirstStrings(vector<vector<string> > selectedVects)
{
    vector<vector<string> > filteredVects;
    int selectedVectsSize = selectedVects.size();
    if (selectedVectsSize >= 3 && selectedVects[0].size() > 1)
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
vector<vector<string> > excelData::filterByDate(vector<vector<string> > selectedVects, int startYear, int endYear)
{
    vector<string> nameVectFilt, typeVectFilt, yearVectFilt, moneyVectFilt, peerVectFilt, hoursVectFilt;
    if (selectedVects.size() >= 3)
    {
        vector<string> nameVect, typeVect, yearVect, moneyVect, peerVect, hoursVect;
        nameVect = selectedVects[0];
        typeVect = selectedVects[1];
        yearVect = selectedVects[2];
        if (isFunding())
        {
            moneyVect = selectedVects[3];
            peerVect = selectedVects[4];
        }
        else if (isTeaching())
        {
            hoursVect = selectedVects[3];
        }
        for (int i = 1, iMax = selectYears.size(); i < iMax; i++)
        {
            int year = selectYears[i];
            if (year >= startYear && year <= endYear)
            {
                nameVectFilt.push_back(nameVect[i]);
                typeVectFilt.push_back(typeVect[i]);
                yearVectFilt.push_back(yearVect[i]);
                if (isFunding())
                {
                    moneyVectFilt.push_back(moneyVect[i]);
                    peerVectFilt.push_back(peerVect[i]);
                }
                else if (isTeaching())
                {
                    hoursVectFilt.push_back(hoursVect[i]);
                }
            }
        }
    }
    vector<vector<string> > filtered;
    filtered.push_back(nameVectFilt);
    filtered.push_back(typeVectFilt);
    filtered.push_back(yearVectFilt);
    if (isFunding())
    {
        filtered.push_back(moneyVectFilt);
        filtered.push_back(peerVectFilt);
    }
    else if (isTeaching())
    {
        filtered.push_back(hoursVectFilt);
    }
    return filtered;
}

//sorts filtered data into "names"/"types"/"uniqueTypes"/"years"
void excelData::sortForGraph(vector<vector<string> > filteredVects)
{
    if (filteredVects.size() >= 3)
    {
        vector<string> namesVect, typesVect, yearsVect, moneyVect, peerVect, hoursVect;
        namesVect = filteredVects[0];
        typesVect = filteredVects[1];
        yearsVect = filteredVects[2];
        if (isFunding())
        {
            moneyVect = filteredVects[3];
            peerVect = filteredVects[4];
        }
        else if (isTeaching())
        {
            hoursVect = filteredVects[3];
        }
        vector<string> namesVectSort;
        vector<int> uniqueTypesVect;
        vector<vector<string> > typesVectSort;
        vector<vector<int> > yearsVectSort;
        vector<vector<string> > moneyVectSort;
        vector<vector<bool> > peerVectSort;
        vector<vector<double> > hoursVectSort;
        for (int i = 0, iMax = namesVect.size(); i < iMax; i++)
        {
            string nextName = namesVect[i];
            string nextType = typesVect[i];
            string nextYear = yearsVect[i];
            string nextMoney;
            string nextPeer;
            string nextHours;
            if (isFunding())
            {
                nextMoney = moneyVect[i];
                nextPeer = peerVect[i];
            }
            else if (isTeaching())
            {
                nextHours = hoursVect[i];
            }
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
                vector<string> newMoneyVect;
                vector<bool> newPeerVect;
                vector<double> newHoursVect;
                typesVectSort.push_back(newTypesVect);
                yearsVectSort.push_back(newYearsVect);
                if (isFunding())
                {
                    moneyVectSort.push_back(newMoneyVect);
                    peerVectSort.push_back(newPeerVect);
                }
                else if (isTeaching())
                {
                    hoursVectSort.push_back(newHoursVect);
                }
                count++;
            }
            typesVectSort[count].push_back(nextType);
            yearsVectSort[count].push_back(stringToInt(nextYear));
            if (isFunding())
            {
                moneyVectSort[count].push_back(nextMoney);
                peerVectSort[count].push_back(parseBool(nextPeer));
            }
            else if (isTeaching())
            {
                hoursVectSort[count].push_back(stringToDouble(nextHours));
            }
        }

        for (int i = 0, totalVects = namesVectSort.size(); i < totalVects; i++)
        {
            vector<string> tempTypesVect = typesVectSort[i];
            vector<int> tempYearsVect = yearsVectSort[i];
            vector<string> tempMoneyVect;
            vector<bool> tempPeerVect;
            vector<double> tempHoursVect;
            if (isFunding())
            {
                tempMoneyVect = moneyVectSort[i];
                tempPeerVect = peerVectSort[i];
            }
            else if (isTeaching())
            {
                tempHoursVect = hoursVectSort[i];
            }
            vector<string> newTypesVect;
            vector<int> newYearsVect;
            vector<string> newMoneyVect;
            vector<bool> newPeerVect;
            vector<double> newHoursVect;
            int count = 0;
            for (int j = 0, jMax = tempTypesVect.size(); j < jMax; j++)
            {
                string testType = tempTypesVect[j];
                int testYear = tempYearsVect[j];
                string testMoney;
                bool testPeer;
                double testHours;
                if (isFunding())
                {
                    testMoney = tempMoneyVect[j];
                    testPeer = tempPeerVect[j];
                }
                else if (isTeaching())
                {
                    testHours = tempHoursVect[j];
                }
                bool exists = false;
                for (int k = 0, kMax = newTypesVect.size(); k < kMax && !exists; k++)
                {
                    if (testType.compare(newTypesVect[k]) == 0)
                    {
                        vector<string>::iterator typesBegin = newTypesVect.begin() + k;
                        vector<int>::iterator yearsBegin = newYearsVect.begin() + k;
                        vector<string>::iterator moneyBegin;
                        vector<bool>::iterator peerBegin;
                        vector<double>::iterator hoursBegin;
                        if (isFunding())
                        {
                            moneyBegin = newMoneyVect.begin() + k;
                            peerBegin = newPeerVect.begin() + k;
                        }
                        else if (isTeaching())
                        {
                            hoursBegin = newHoursVect.begin() + k;
                        }
                        newTypesVect.insert(typesBegin, testType);
                        newYearsVect.insert(yearsBegin, testYear);
                        if (isFunding())
                        {
                            newMoneyVect.insert(moneyBegin, testMoney);
                            newPeerVect.insert(peerBegin, testPeer);
                        }
                        else if (isTeaching())
                        {
                            newHoursVect.insert(hoursBegin, testHours);
                        }
                        exists = true;
                    }
                }
                if (!exists)
                {
                    newTypesVect.push_back(testType);
                    newYearsVect.push_back(testYear);
                    if (isFunding())
                    {
                        newMoneyVect.push_back(testMoney);
                        newPeerVect.push_back(testPeer);
                    }
                    else if (isTeaching())
                    {
                        newHoursVect.push_back(testHours);
                    }
                    count++;
                }
            }
            typesVectSort[i] = newTypesVect;
            yearsVectSort[i] = newYearsVect;
            if (isFunding())
            {
                moneyVectSort[i] = newMoneyVect;
                peerVectSort[i] = newPeerVect;
            }
            else if (isTeaching())
            {
                hoursVectSort[i] = newHoursVect;
            }
            uniqueTypesVect.push_back(count);
        }
        names = namesVectSort;
        uniqueTypes = uniqueTypesVect;
        types = typesVectSort;
        years = yearsVectSort;
        if (isFunding())
        {
            money = moneyVectSort;
            vector<vector<long long> > newMoney;
            vector<long long> newMoneyTemp;
            for (int i = 0, iMax = money.size(); i < iMax; i++)
            {
                newMoneyTemp = vector<long long>();
                for (int j = 0, jMax = money[i].size(); j < jMax; j++)
                {
                    long long newLongMoney = parseMoney(money[i][j]);
                    newMoneyTemp.push_back(newLongMoney);
                }
                newMoney.push_back(newMoneyTemp);
            }
            longMoney = newMoney;
            peerReviewed = peerVectSort;
        }
        else if (isTeaching())
        {
            hours = hoursVectSort;
        }
    }
}

//sorts filtered data into "namesByType"/"countByType"
void excelData::sortForGui(vector<vector<string> > filteredVects)
{
    if (filteredVects.size() >= 3)
    {
        vector<string> namesVect, typesVect, moneyVect, peerVect, hoursVect;
        namesVect = filteredVects[0];
        typesVect = filteredVects[1];
        if (isFunding())
        {
            moneyVect = filteredVects[3];
            peerVect = filteredVects[4];
        }
        else if (isTeaching())
        {
            hoursVect = filteredVects[3];
        }

        vector<vector<string> > dataNamesVect;
        vector<vector<int> > dataCountVect;
        vector<vector<long long> > dataMoneyVect;
        vector<vector<double> > dataHoursVect;
        vector<string> title;
        switch (excelType) // 1 = funding, 2 = presentations, 3 = publications, 4 = teaching
        {
            case 1:
                title.push_back("Grants and Clinical Funding");
                break;

            case 2:
                title.push_back("Presentations");
                break;

            case 3:
                title.push_back("Publications");
                break;

            case 4:
                title.push_back("Teaching");
                break;
        }
        dataNamesVect.push_back(title);
        if (!isTeaching())
        {
            vector<int> total;
            vector<long long> totalMoney;
            total.push_back(0);
            dataCountVect.push_back(total);
            if (isFunding())
            {
                totalMoney.push_back(0);
                dataMoneyVect.push_back(totalMoney);
            }
        }
        else
        {
            vector<double> total;
            total.push_back(0);
            dataHoursVect.push_back(total);
        }
        for (int i = 0, iMax = typesVect.size(); i < iMax; i++)
        {
            string typeTest = typesVect[i];
            if (isTeaching())
            {
                typeTest = acronymize(typeTest);
            }
            string nameTest = namesVect[i];
            long long moneyTest;
            bool peerTest;
            double hoursTest;
            if (isFunding())
            {
                moneyTest = parseMoney(moneyVect[i]);
                peerTest = parseBool(peerVect[i]);
                if (peerTest)
                {
                    typeTest += "P";
                }
                else
                {
                    typeTest += "I";
                }
            }
            else if (isTeaching())
            {
                hoursTest = stringToDouble(hoursVect[i]);
            }
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
                            if (!isTeaching())
                            {
                                dataCountVect[0][0]++;
                                dataCountVect[j][0]++;
                                dataCountVect[j][k]++;
                                if (isFunding())
                                {
                                    dataMoneyVect[j][0] += moneyTest;
                                    dataMoneyVect[j][k] += moneyTest;
                                }
                                nameExists = true;
                            }
                            else
                            {
                                dataHoursVect[0][0] += hoursTest;
                                dataHoursVect[j][0] += hoursTest;
                                dataHoursVect[j][k] += hoursTest;
                                nameExists = true;
                            }
                        }
                    }
                    if (!nameExists)
                    {
                        dataNamesVect[j].push_back(nameTest);
                        if (!isTeaching())
                        {
                            dataCountVect[0][0]++;
                            dataCountVect[j][0]++;
                            dataCountVect[j].push_back(1);
                            if (isFunding())
                            {
                                dataMoneyVect[j][0] += moneyTest;
                                dataMoneyVect[j].push_back(moneyTest);
                            }
                        }
                        else
                        {
                            dataHoursVect[0][0] += hoursTest;
                            dataHoursVect[j][0] += hoursTest;
                            dataHoursVect[j].push_back(hoursTest);
                        }
                    }
                    exists = true;
                }
            }
            if (!exists)
            {
                vector<string> newNameVect;
                vector<int> newCountVect;
                vector<long long> newMoneyVect;
                vector<double> newHoursVect;
                newNameVect.push_back(typeTest);
                newNameVect.push_back(nameTest);
                if (!isTeaching())
                {
                    newCountVect.push_back(1);
                    newCountVect.push_back(1);
                    dataCountVect[0][0]++;
                    if (isFunding())
                    {
                        newMoneyVect.push_back(moneyTest);
                        newMoneyVect.push_back(moneyTest);
                    }
                }
                else
                {
                    newHoursVect.push_back(hoursTest);
                    newHoursVect.push_back(hoursTest);
                    dataHoursVect[0][0] += hoursTest;
                }
                dataNamesVect.push_back(newNameVect);
                if (!isTeaching())
                {
                    dataCountVect.push_back(newCountVect);
                    if (isFunding())
                    {
                        dataMoneyVect.push_back(newMoneyVect);
                    }
                }
                else
                {
                    dataHoursVect.push_back(newHoursVect);
                }
            }
        }
        namesByType = dataNamesVect;
        if (!isTeaching())
        {
            countByType = dataCountVect;
            if (isFunding())
            {
                moneyByType = dataMoneyVect;
            }
        }
        else
        {
            hoursByType = dataHoursVect;
        }
        if (isFunding())
        {
            namesByType.erase(namesByType.begin());
            countByType.erase(countByType.begin());
            moneyByType.erase(moneyByType.begin());
            vector<vector<string> > namesType;
            vector<vector<int> > countType;
            vector<vector<long long> > moneyType;
            for (int i = 0; i < 4; i++)
            {
                vector<string> firstName;
                vector<int> firstCount;
                vector<long long> firstMoney;
                if (i % 2 == 0)
                {
                    firstName.push_back("Peer Reviewed");
                }
                else
                {
                    firstName.push_back("Industry Sponsored");
                }
                firstCount.push_back(0);
                firstMoney.push_back(0);
                namesType.push_back(firstName);
                countType.push_back(firstCount);
                moneyType.push_back(firstMoney);
            }
            for (unsigned int i = 0; i < namesByType.size(); i++)
            {
                if (!namesByType[i].empty())
                {
                    if (namesByType[i][0].compare("GrantsP") == 0)
                    {
                        namesByType[i][0] = "Peer Reviewed";
                        namesType[0] = namesByType[i];
                        countType[0] = countByType[i];
                        moneyType[0] = moneyByType[i];
                    }
                    else if (namesByType[i][0].compare("GrantsI") == 0)
                    {
                        namesByType[i][0] = "Industry Sponsored";
                        namesType[1] = namesByType[i];
                        countType[1] = countByType[i];
                        moneyType[1] = moneyByType[i];
                    }
                    else if (namesByType[i][0].compare("Clinical TrialsP") == 0)
                    {
                        namesByType[i][0] = "Peer Reviewed";
                        namesType[2] = namesByType[i];
                        countType[2] = countByType[i];
                        moneyType[2] = moneyByType[i];
                    }
                    else if (namesByType[i][0].compare("Clinical TrialsI") == 0)
                    {
                        namesByType[i][0] = "Industry Sponsored";
                        namesType[3] = namesByType[i];
                        countType[3] = countByType[i];
                        moneyType[3] = moneyByType[i];
                    }
                }
            }
            namesByType = namesType;
            countByType = countType;
            moneyByType = moneyType;
        }
    }
}

//returns the information to be printed to the GUI, with each type's dataset separated by a single hyphen
vector<string> excelData::guiTypeData()
{
    vector<string> guiData;
    switch(excelType)
    {
    case 1:
        for (int i = 0, iMax = countByType.size(); i < iMax; i++)
        {
            vector<string> namesVect = namesByType[i];
            vector<int> countVect = countByType[i];
            vector<long long> moneyVect = moneyByType[i];
            if (i == 0)
            {
                guiData.push_back("Grants");
                int countTotal = countByType[0][0] + countByType[1][0];
                stringstream ss;
                ss << countTotal;
                guiData.push_back(ss.str());
                long long moneyTotal = moneyByType[0][0] + moneyByType[1][0];
                guiData.push_back(formatMoney(moneyTotal));
            }
            else
            {
                string hyphen = "-";
                guiData.push_back(hyphen);
                if (i == 2)
                {
                    guiData.push_back(hyphen);
                    guiData.push_back("Clinical Funding");
                    int countTotal = countByType[2][0] + countByType[3][0];
                    stringstream ss;
                    ss << countTotal;
                    guiData.push_back(ss.str());
                    long long moneyTotal = moneyByType[2][0] + moneyByType[3][0];
                    guiData.push_back(formatMoney(moneyTotal));
                }
            }
            for (int j = 0, jMax = namesVect.size(); j < jMax; j++)
            {
                guiData.push_back(namesVect[j]);
                stringstream ss;
                ss << countVect[j];
                guiData.push_back(ss.str());
                guiData.push_back(formatMoney(moneyVect[j]));
            }
        }
        break;

    case 2:
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
                guiData.push_back(ss.str());
            }
        }
        break;

    case 3:
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
                guiData.push_back(ss.str());
            }
        }
        break;

    case 4:
        for (int i = 0, iMax = hoursByType.size(); i < iMax; i++)
        {
            vector<string> namesVect = namesByType[i];
            vector<double> hoursVect = hoursByType[i];
            if (i > 1)
            {
                string hyphen = "-";
                guiData.push_back(hyphen);
            }
            for (int j = 0, jMax = namesVect.size(); j < jMax; j++)
            {
                guiData.push_back(namesVect[j]);
                stringstream ss;
                ss << hoursVect[j];
                guiData.push_back(ss.str());
            }
        }
        break;
    }
    return guiData;
}

//shows a graph for the given person
void excelData::showGraph(string personName, int graphType, QCustomPlot *plot)
{
    int personIndex;
    int totalPersons = getTotalEntries();
    if (graphType == 0)
    {
        graph g(plot);
        g.showGraph(graphType);
    }
    else
    {
        bool done = false;
        for (personIndex = 0; personIndex < totalPersons && !done; personIndex++)
        {
            if (names[personIndex].compare(personName) == 0)
            {
                done = true;
                personIndex--;
            }
        }
        if (personIndex < totalPersons)
        {
            vector<long long> graphMoney;
            vector<double> graphHours;
            if (isFunding())
            {
                graphMoney = longMoney[personIndex];
            }
            else if (isTeaching())
            {
                graphHours = hours[personIndex];
            }
            graph g(excelType, plot, names[personIndex], types[personIndex], years[personIndex],
                    graphMoney, graphHours, uniqueTypes[personIndex], startYear, endYear);
            g.showGraph(graphType);
        }
    }
}

//parses a string and returns the integer
int excelData::stringToInt(string inputString)
{
    const char * ctemp = inputString.c_str();
    return atoi(ctemp);
}

//parses a string and returns the double
double excelData::stringToDouble(string inputString)
{
    const char * ctemp = inputString.c_str();
    return atof(ctemp);
}

//returns "true" for funding-type Excel files
int excelData::isFunding()
{
    return (excelType == 1);
}

//returns "true" for presentation-type Excel files
int excelData::isPresentations()
{
    return (excelType == 2);
}

//returns "true" for publications-type Excel files
int excelData::isPublications()
{
    return (excelType == 3);
}

//returns "true" for teaching-type Excel files
int excelData::isTeaching()
{
    return (excelType == 4);
}

//returns a currency string for the given long long
string excelData::formatMoney(long long amount)
{
    stringstream ss;
    ss << amount;
    string raw = ss.str();
    for (int i = raw.length() - 4; i >= 0; i -= 3)
    {
        raw.insert(i + 1, ",");
    }
    raw += ".00";
    return raw;
}

//parses a currency string into a long long
long long excelData::parseMoney(string amount)
{
    long long value = 0;
    long long mult = 1;
    for (int i = amount.length() - 4; i >= 0; i--)
    {
        string nextDigit = "";
        nextDigit += amount[i];
        int digit = stringToInt(nextDigit);
        if (digit > 0 || nextDigit.compare("0") == 0)
        {
            value += (digit * mult);
            mult *= 10;
        }
    }
    return value;
}

//returns true if the string is "True"
bool excelData::parseBool(string boolTest)
{
    return boolTest.compare("True") == 0;
}

//returns an acronym for the Teaching type-string
string excelData::acronymize(string type)
{
    if (type.compare("Continuing Medical Education") == 0)
    {
        type = "CME";
    }
    else if (type.compare("Postgraduate Medical Education") == 0)
    {
        type = "PME";
    }
    else if (type.compare("Undergraduate Medical Education") == 0)
    {
        type = "UME";
    }
    return type;
}

//get the total number of entries
int excelData::getTotalEntries()
{
    return names.size();
}

//returns a pointer to the Parser object
Parser *excelData::getParse()
{
    return parse;
}

