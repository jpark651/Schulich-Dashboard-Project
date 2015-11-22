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


namespace Ui {
    class graph;
}


class graph : public QWidget
{
    Q_OBJECT

public:
    explicit graph(QWidget *parent = 0);
    ~graph();
    //processes info for Publications and calls one of the 3 graph creating functions
    void preparePublications(std:: string name, std:: vector<std:: string> types, std:: vector<int> years, int diff_types, int begin, int end, int graphtype);

    //method for creating a window which displays a bar graph from the Publications summary
    void createBarPublications(std:: string name, int num_publications, std:: vector<int> xaxis, std:: vector<std::string> xlabel);

    //method for creating a window which displays a line graph from the Publications summary
    void createLinePublications(std:: string name, int num_publications, std:: vector<int> xaxis, std:: vector<std:: string> xlabel);

    //method for creating a window which display a pie chart from the Publications summary
    void createPiePublications(std:: string name, int num_publications, std:: vector<int> xaxis, std:: vector<std:: string> xlabel);
private:
    Ui::graph *ui;
    std::vector<std::vector<std::string> > names;
};
//

#endif //GRAPH_H_INCLUDED
