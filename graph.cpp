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
#include <vector>
#include "graph.h"

using namespace std;

//constructor
graph::graph()
{
}

void graph::preparePublications(string name, list<string> types, list<int> years, int diff_types, int begin, int end, int graphtype)
{
    list<string> t = types;	//create a copy to manipulate
    list<int> y = years;	//create a copy to manipulate
    string compare;			//for checking when a new type of publication exists
    int track = 0;				//used to track where in the string array we are

    int size = types.size(); //get the size of the list
    int num_publications = 0;//number of publications that fit the date range. used for y-axis

    vector<int> xaxis;		//array for the number of publications of each publication type
    vector<string> xlabel;	//string array for x-axis tick labels


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


    /* THE TYPE OF GRAPH THAT THE USER WANTS TO DISPLAY
    *    1 = bar
    *    2 = pie
    *    3 = line
    */
    if (graphtype == 1)
        createBarPublications(name, num_publications, xaxis, xlabel);
    else if (graphtype == 2)
        createLinePublications(name, num_publications, xaxis, xlabel);

}



//method for creating a window which displays a bar graph from the Publications summary
void graph::createBarPublications(string name, int num_publications, vector<int> xaxis, vector<string> xlabel)
{

}

//method for creating a window which displays a line graph from the Publications summary
void graph::createLinePublications(string name, int num_publications, vector<int> xaxis, vector<string> xlabel)
{

}
