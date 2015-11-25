/**
* Header file for the graph class and its associated methods
*/
#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
//
//#ifndef GRAPH_H
//#define GRAPH_H

#include <QWidget>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <list>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <vector>
#include <QMainWindow>


namespace Ui {
    class graph;
}


class graph : public QMainWindow
{
    Q_OBJECT

public:
	
	explicit graph(QWidget *parent = 0);	//choice is the data and graph type to be displayed
	~graph();

    //processes info for Publications and calls one of the 3 graph creating functions
    void preparePublications(std:: string name, std:: vector<std:: string> types, std:: vector<int> years, int diff_types, int begin, int end, int graphtype);

	//processes info for Funding and calls one of the 3 graph creating functions
	//void graph::prepareFunding(std::string name, std::vector<std::string> types, std::vector<int> years, std::vector<double> amount, int diff_types, int begin, int end, int graphtype)


    //method for creating a window which displays a bar graph
    void createBarGraph(std:: string title, int yaxis_range, std:: vector<int> xaxis, std:: vector<std::string> xlabel, std:: string xtitle, std:: string ytitle);

    //method for creating a window which displays a line graph
    void createLineGraph(std:: string title, int yaxis_range, std:: vector<int> xaxis, std:: vector<int> yaxis, std:: vector<std:: string> xlabel, std::string xtitle, std::string ytitle);

    //method for creating a window which display a pie chart
    //void createPieChart(std:: string title, int num_publications, std:: vector<int> xaxis, std:: vector<std:: string> xlabel);


private:
    Ui::graph *ui;
    std::vector<std::vector<std::string> > names;
};
//

#endif //GRAPH_H_INCLUDED
