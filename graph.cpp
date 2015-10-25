/**
* This class implements the methods in graph.h
*/
#include <string>
#include <iostream>
#include <stdlib.h>
#include <list>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "graph.h"
using namespace std;

//constructor
graph::graph()
{
}

/*The method takes a person's name, the list of their publications that are ordered by type, the list
* of years corresponding to the list of publications, and the user specified date range which is 
  split into beginning and end date.
*/
void createBarPublications(string name, list<string> types, list<int> years, int diff_types, int begin, int end)
{
	list<string> t = types;	//create a copy to manipulate
	list<int> y = years;	//create a copy to manipulate
	string compare;			//for checking when a new type of publication exists
	int track = 0;				//used to track where in the string array we are

	int size = types.size(); //get the size of the list
	int num_publications = 0;//number of publications that fit the date range. used for y-axis

	int xaxis[diff_types];		//array for the number of publications of each publication type
	string xlabel[diff_types];	//string array for x-axis tick labels


	//initialize the array values to 0 to prepare for counting
	for (int count = 0; count < diff_types; count++)
	{
		xaxis[count] = 0;
	}


	compare = t.front();	//the first publication type
	xlabel[0] = t.front();	//record the first label

	//This loop goes through the list of publications and counts how many are of each type.
	for (int count = 0; count < size; count++) 
	{
		//check if the publications is in the date range
		if ((y.front() >= begin) && (y.front() <= end))
		{
			//check if the publication type is the same as the previous
			if (t.front() == compare)
			{
				//record the publication
				xaxis[track]++;
				//pop from the list
				t.pop_front();
				y.pop_front();
			}
			//else start counting the next type
			else
			{
				//record the publication for the new type
				track++;
				xaxis[track]++;
				//record the label for the new type
				xlabel[track] = t.front();

				//pop from the list
				t.pop_front();
				y.pop_front();
				//record the new publication type
				compare = t.front();
			}
		}
		else
		{
			//pop from the list
			t.pop_front();
			y.pop_front();
		}
	}



	//TO DO: tick loop

	//TO DO: x-axis label loop using xlabel[]

	//TO DO: loop for the actual bar data using xaxis[]
}

//method for creating a windpw which displays a line graph from the Publications summary
void createLinePublicatons(string name, list<string> types, list<int> years)
{

}

//method for creating a window which display a pie chart from the Publications summary
void createPiePublications(string name, list<string> types, list<int> years)
{

}

