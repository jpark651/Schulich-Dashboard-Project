/**
* Header file for the graph class and its associated methods
*/
#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <string>
#include <iostream>
#include <stdlib.h>
#include <list>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
using namespace std;

class graph
{
private:
	//variables
	list<list<string> > names;

public:
	//constructor
	graph();

	//method for creating a window which displays a bar graph from the Publications summary
	void createBarPublications(string name, list<string> types, list<int> years);

	//method for creating a windpw which displays a line graph from the Publications summary
	void createLinePublicatons(string name, list<string> types, list<int> years);

	//method for creating a window which display a pie chart from the Publications summary
	void createPiePublications(string name, list<string> types, list<int> years);
};

#endif //GRAPH_H_INCLUDED
