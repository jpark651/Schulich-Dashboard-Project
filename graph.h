/**
  * Author: Team HoneyDew
  * Computer Science 3307, Group Project
  * December 9, 2015
  * Header file for the graph class and its associated methods
*/
#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
//
//#ifndef GRAPH_H
//#define GRAPH_H

#include <iostream>
#include <qcustomplot.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "graph.h"
using namespace std;

//Class that defines a graph to be displayed in the GUI
class graph
{
private:
//Instance variables

    int excelType;
    int graphType = 0;
    QCustomPlot *plot;
    string name;
    vector<string> types;
    vector<int> years;
    vector<long long> money;
    vector<double> hours;
    string labelY;
    vector<string> labelsGraph;
    vector<vector<double> > totalsY;
    vector<vector<double> > yearsX;
    int uniqueTypes;
    double yRangeEnd;
    int xRangeStart;
    int xRangeEnd;

//Private methods

//Initializes the variables required for graphing
    void initializeObject();

//Sets the y-axis label
    void setLabel();

//Initializes the years for each graph to have empty totals
    void initializeYears();

//Groups data for each graph to be plotted
    void groupByGraph();

//Returns a unique pen for differentiating graphs
    QPen getNextPen(int graphNum);


public:
//Public constructors

//Graph constructor
    graph(int excelType, QCustomPlot *plot, string name, vector<string> types, vector<int> years,
          vector<long long> money, vector<double> hours, int uniqueTypes, int startYear, int endYear);

//Graph constructor (empty graph)
    graph(QCustomPlot *plot);

//Uninitialized constructor
    graph();

//Public methods

//Builds the QCustomPlot that will allow the graph to be displayed
    void showGraph(int graphType);

//Updates the graph with a new start year and end year specfied by the user
    void updateGraph(int startYear, int endYear);
};

#endif //GRAPH_H_INCLUDED
