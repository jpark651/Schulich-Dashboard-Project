/**
  * Author: Team HoneyDew
  * Computer Science 3307, Group Project
  * December 9, 2015
  * This class implements the methods in graph.h
*/
#include <iostream>
#include <qcustomplot.h>
#include <QString>
#include <QVector>
#include <sstream>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "graph.h"
using namespace std;

//Graph constructor
graph::graph(int excelType, QCustomPlot *plot, string name, vector<string> types, vector<int> years,
             vector<long long> money, vector<double> hours, int uniqueTypes, int startYear, int endYear)
{
    this->excelType = excelType;
    this->plot = plot;
    this->name = name;
    this->types = types;
    this->years = years;
    this->money = money;
    this->hours = hours;
    this->uniqueTypes = uniqueTypes;
    this->xRangeStart = startYear;
    this->xRangeEnd = endYear;
    initializeObject();
}

//Graph constructor that sets the plot for the graph to be displayed
graph::graph(QCustomPlot *plot)
{
    this->plot = plot;
}

//Uninitialized constructor
graph::graph(){}


//Initializes the variables required for graphing
void graph::initializeObject()
{
    setLabel();
    initializeYears();
    groupByGraph();
}

//Sets the y-axis label
void graph::setLabel()
{
    switch(excelType)
    {
    case 1:
        labelY = "Total $";
        break;

    case 2:
        labelY = "Total Presentations";
        break;

    case 3:
        labelY = "Total Publications";
        break;

    case 4:
        labelY = "Total Hours";
        break;
    }
}

//Initializes the years for each graph to have empty totals
void graph::initializeYears()
{
    vector<double> defaultYearVect;
    vector<double> defaultTotalVect;
    for (int i = xRangeStart; i <= xRangeEnd; i++)
    {
        defaultYearVect.push_back(i);
        defaultTotalVect.push_back(0);
    }
    for (int i = 0; i < uniqueTypes; i++)
    {
        yearsX.push_back(defaultYearVect);
        totalsY.push_back(defaultTotalVect);
    }
}

//Groups data for each graph to be plotted
void graph::groupByGraph()
{
    double maxY = 0;
    for (int i = 0, iMax = types.size(); i < iMax; i++)
    {
        bool unique = true;
        int index = 0;
        for (int indexMax = labelsGraph.size(); index < indexMax && unique; index++)
        {
            if (types[i].compare(labelsGraph[index]) == 0)
            {
                unique = false;
                index--;
            }
        }
        if (unique)
        {
            labelsGraph.push_back(types[i]);
        }
        bool uniqueYear = true;
        int yearIndex = 0;
        for (int yearIndexMax = yearsX[index].size(); yearIndex < yearIndexMax && uniqueYear; yearIndex++)
        {
            if (years[i] == yearsX[index][yearIndex])
            {
                uniqueYear = false;
                yearIndex--;
            }
        }
        if (uniqueYear)
        {
            yearsX[index].push_back(years[i]);
            if (excelType == 4)
            {
                totalsY[index].push_back(hours[i]);
                maxY = max(maxY, hours[i]);
            }
            else
            {
                double newTotal = 1;
                if (excelType == 1)
                {
                    newTotal = money[i];
                }
                totalsY[index].push_back(newTotal);
                maxY = max(maxY, newTotal);
            }
        }
        else
        {
            if (excelType == 4)
            {
                totalsY[index][yearIndex] += hours[i];
                maxY = max(maxY, totalsY[index][yearIndex]);
            }
            else
            {
                double newValue = 1;
                if (excelType == 1)
                {
                    newValue = money[i];
                }
                totalsY[index][yearIndex] += newValue;
                maxY = max(maxY, totalsY[index][yearIndex]);
            }
        }
    }
    yRangeEnd = 1.1 * maxY;
}

//Returns a unique pen for differentiating graphs
QPen graph::getNextPen(int graphNum)
{
    QPen nextPen;
    int color = graphNum % 7;
    int style = graphNum / 7;
    style %= 5;
    switch(color)
    {
    case 0:
        nextPen.setColor(Qt::blue);
        break;
    case 1:
        nextPen.setColor(Qt::red);
        break;
    case 2:
        nextPen.setColor(Qt::green);
        break;
    case 3:
        nextPen.setColor(Qt::magenta);
        break;
    case 4:
        nextPen.setColor(Qt::cyan);
        break;
    case 5:
        nextPen.setColor(Qt::yellow);
        break;
    case 6:
        nextPen.setColor(Qt::darkGray);
        break;
    }

    switch(style)
    {
    case 0:
        nextPen.setStyle(Qt::SolidLine);
        break;
    case 1:
        nextPen.setStyle(Qt::DashLine);
        break;
    case 2:
        nextPen.setStyle(Qt::DotLine);
        break;
    case 3:
        nextPen.setStyle(Qt::DashDotLine);
        break;
    case 4:
        nextPen.setStyle(Qt::DashDotDotLine);
        break;
    }

    return nextPen;
}

//Builds the QCustomPlot that will allow the graph to be displayed
void graph::showGraph(int graphType)
{
    this->graphType = graphType;
    plot->clearGraphs();
    if (graphType == 0)
    {
        QVector<QString> blankTicks;
        plot->legend->setVisible(false);
        plot->xAxis->setLabel("");
        plot->xAxis->setAutoTicks(true);
        plot->xAxis->setAutoTickStep(true);
        plot->xAxis->setAutoTickLabels(false);
        plot->xAxis->setTickVectorLabels(blankTicks);
        plot->xAxis->rescale();
        plot->yAxis->setLabel("");
        plot->yAxis->setAutoTicks(true);
        plot->yAxis->setAutoTickStep(true);
        plot->yAxis->setAutoTickLabels(false);
        plot->yAxis->setTickVectorLabels(blankTicks);
        plot->yAxis->rescale();
    }
    else if (graphType == 1)
    {
        plot->legend->setVisible(true);
        plot->legend->setBrush(Qt::transparent);
        for (int i = 0, iMax = labelsGraph.size(); i < iMax; i++)
        {
            plot->addGraph();
            QPen nextPen = getNextPen(i);
            plot->graph(i)->setPen(nextPen);
            QString qs = QString::fromStdString(labelsGraph[i]);
            plot->graph(i)->setName(qs);
            QVector<double> xVect = QVector<double>::fromStdVector(yearsX[i]);
            QVector<double> yVect = QVector<double>::fromStdVector(totalsY[i]);
            plot->graph(i)->setData(xVect, yVect);
        }
        plot->xAxis->setLabel("Year");
        QString qs = QString::fromStdString(labelY);
        plot->yAxis->setLabel(qs);
        plot->yAxis->setRange(0, yRangeEnd);
        plot->xAxis->setRange(xRangeStart, xRangeEnd);
        if (excelType == 2 || excelType == 3)
        {
            plot->yAxis->setTickStep(1);
            vector<double> tickVectY;
            QVector<QString> labelVectY;
            int diff = yRangeEnd;
            int perTicks = (9 + diff) / 10;
            int countY = 0;
            for (int i = 0; i <= yRangeEnd; i++)
            {
                tickVectY.push_back(i);
                if (diff > 1)
                {
                    if (i == 0)
                    {
                        labelVectY.push_back("");
                    }
                    else if (countY == 0)
                    {
                        stringstream ss;
                        ss << i;
                        labelVectY.push_back(QString::fromStdString(ss.str()));
                        countY++;
                    }
                    else
                    {
                        labelVectY.push_back("");
                        countY++;
                    }
                }
                else
                {
                    stringstream ss;
                    ss << i;
                    labelVectY.push_back(QString::fromStdString(ss.str()));
                }
                if (countY == perTicks)
                {
                    countY = 0;
                }
            }
            QVector<double> tickQVectY = QVector<double>::fromStdVector(tickVectY);
            plot->yAxis->setAutoTicks(false);
            plot->yAxis->setAutoTickStep(false);
            plot->yAxis->setTickVector(tickQVectY);
            plot->yAxis->setAutoTickLabels(false);
            plot->yAxis->setTickVectorLabels(labelVectY);
            plot->yAxis->setSubTickCount(0);
        }
        else
        {
            plot->yAxis->setAutoTicks(true);
            plot->yAxis->setAutoTickStep(true);
            plot->yAxis->setAutoTickLabels(true);
        }
        plot->xAxis->setTickStep(1);
        vector<double> tickVect;
        QVector<QString> labelVect;
        int diff = xRangeEnd - xRangeStart;
        int perTicks = (9 + diff) / 10;
        int count = 0;
        for (int i = xRangeStart; i <= xRangeEnd; i++)
        {
            tickVect.push_back(i);
            if (diff > 1)
            {
                if (i == xRangeStart)
                {
                    labelVect.push_back("");
                }
                else if (count == 0)
                {
                    stringstream ss;
                    ss << i;
                    labelVect.push_back(QString::fromStdString(ss.str()));
                    count++;
                }
                else
                {
                    labelVect.push_back("");
                    count++;
                }
            }
            else
            {
                stringstream ss;
                ss << i;
                labelVect.push_back(QString::fromStdString(ss.str()));
            }
            if (count == perTicks)
            {
                count = 0;
            }
        }
        QVector<double> tickQVect = QVector<double>::fromStdVector(tickVect);
        plot->xAxis->setAutoTicks(false);
        plot->xAxis->setAutoTickStep(false);
        plot->xAxis->setTickVector(tickQVect);
        plot->xAxis->setAutoTickLabels(false);
        plot->xAxis->setTickVectorLabels(labelVect);
        plot->xAxis->setSubTickCount(0);
    }
    plot->replot();
}

//Updates the graph with a new start year and end year specfied by the user
void graph::updateGraph(int startYear, int endYear)
{
    this->xRangeStart = startYear;
    this->xRangeEnd = endYear;
    showGraph(graphType);
}
