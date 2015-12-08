/**
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

class graph
{
private:
    /*------ Variables ------*/

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


    /*------ Methods ------*/

    //initializes the variables required for graphing
    void initializeObject();

    //sets the y-axis label
    void setLabel();

    //initializes the years for each graph to have empty totals
    void initializeYears();

    //groups data for each graph to be plotted
    void groupByGraph();

    //returns a unique pen for differentiating graphs
    QPen getNextPen(int graphNum);


public:
    /*------ Constructors ------*/

    //graph constructor
    graph(int excelType, QCustomPlot *plot, string name, vector<string> types, vector<int> years,
          vector<long long> money, vector<double> hours, int uniqueTypes, int startYear, int endYear);
    //graph constructor (empty graph)
    graph(QCustomPlot *plot);
    //uninitialized constructor
    graph();


    /*------ Methods ------*/

    //graphs the data using the given type
    void showGraph(int graphType);

    //updates the graph
    void updateGraph(int startYear, int endYear);
};

#endif //GRAPH_H_INCLUDED
