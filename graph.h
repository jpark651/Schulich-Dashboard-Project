/**
* Header file for the graph class and its associated methods
*/
#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
//
//#ifndef GRAPH_H
//#define GRAPH_H

#include <QMainWindow>
//
#include <string>
#include <iostream>
#include <stdlib.h>
#include <list>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <vector>
using namespace std;

class graph
{
private:
	//variables
	list<list<string> > names;

public:
	//constructor
	graph();

	//processes info for Publications and calls one of the 3 graph creating functions 
	void preparePublications(string name, list<string> types, list<int> years, int diff_types, int begin, int end, int graphtype);

	//method for creating a window which displays a bar graph from the Publications summary
	void createBarPublications(string name, int num_publications, vector<int> xaxis, vector<string> xlabel);

	//method for creating a window which displays a line graph from the Publications summary
	void createLinePublications(string name, int num_publications, vector<int> xaxis, vector<string> xlabel);

	//method for creating a window which display a pie chart from the Publications summary
	void createPiePublications(string name, int num_publications, vector<int> xaxis, vector<string> xlabel);
};

//
namespace Ui {
    class graph;
}

class graph : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit graph(QWidget *parent = 0);
    ~graph();
    
    private slots:
private:
    Ui::graph *ui;
};
//

#endif //GRAPH_H_INCLUDED
