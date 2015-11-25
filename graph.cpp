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
#include "ui_graph.h"
#include "qcustomplot.h"

using namespace std;

graph::graph(QMainWindow *parent) :
    QWindow(parent),
    ui(new Ui::graph)
    {
        ui->setupUi(this);
		//graph::makePlot();
    }

graph::~graph()
{
    delete ui;
}


/*Prepares the data needed to graph from the publications summary.
*/
void graph:: preparePublications(std:: string name, std:: vector<std:: string> types, std:: vector<int> years, int diff_types, int begin, int end, int graphtype)
{
    vector<string> t = types;	//create a copy to manipulate
    vector<int> y = years;		//create a copy to manipulate
	string compare;				//for checking when a new type of publication exists
	int track = 0;				//used to track where in the string vector we are

	int size = types.size();	//get the size of the list
	int num_publications = 0;	//number of publications that fit the date range. used for y-axis

	vector<int> xaxis;			//array for the number of publications of each publication type
	vector<string> xlabel;		//string array for x-axis tick labels


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
                t.erase(t.begin());
                y.erase(y.begin());
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
                t.erase(t.begin());
                y.erase(y.begin());
				//record the new publication type
				compare = t.front();
			}
		}
		else
		{
			//pop from the list
            t.erase(t.begin());
            y.erase(y.begin());
		}
	}

	//title for the graphs
	string title = name + ", " + begin + "-" + end;

	/* THE TYPE OF GRAPH THAT THE USER WANTS TO DISPLAY
	*    1 = bar
	*    2 = pie
	*    3 = line
	*/
	if (graphtype == 1)
		createBarGraph(title, num_publications, xaxis, xlabel, "Number of Publications", "Publication Type");
	else if (graphtype == 2)
		createLineGraph(title, num_publications, xaxis, xlabel, "Number of Publications", "Publication Type");
	//else if (graphtype == 3)
	//	createPiePublications(name, num_publications)
	
}

//need: clinical/grant, approval, amounts, years
//other: fac name, begin, end, graphtype 

void graph:: prepareFunding(std:: string fname, std:: vector<std:: string> c_or_g, std:: vector<std:: string> approval, std:: vector<int> years, std:: vector<double> amount, int begin, int end, int graphtype)
{
	vector<string> type = c_or_g;	//create a copy to manipulate
	vector<int> y = years;			//create a copy to manipulate
	vector<string> a = approval;	//create a copy to manipulate
	vector<double> a = amounts;		//create a copy to manipulate
	string compare;					//for checking when a new type of publication exists
	int track = 0;					//used to track where in the string array we are

	int size = types.size();	//get the size of the list
	int num_publications = 0;	//number of publications that fit the date range. used for y-axis

	vector<int> xaxis;			//array for the number of publications of each publication type
	vector<string> xlabel;		//string array for x-axis tick labels


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
				t.erase(t.begin());
				y.erase(y.begin());
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
				t.erase(t.begin());
				y.erase(y.begin());
				//record the new publication type
				compare = t.front();
			}
		}
		else
		{
			//pop from the list
			t.erase(t.begin());
			y.erase(y.begin());
		}
	}

	createBarGraph(title, largest, xaxis, xlabel, "Total Amount", "Funding Type"







//method for creating a window which displays a bar graph
void graph:: createBarGraph(string title, int yaxis_range, vector<int> xaxis, vector<string> xlabel, string xtitle, string ytitle)
{
	
    //empty bar chart objects:
    QCPBars *Person = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    ui->customPlot->addPlottable(Person);
    
    //set names and colors:
    QPen pen;
    pen.setWidthF(1.0);
    
    //QString str = QString::fromUtf8(name.c_str());
    //Person->setName(str);
	Person->setName(title);
	pen.setColor(QColor(1, 92, 191));
    Person->setPen(pen);
    Person->setBrush(QColor(1, 92, 191, 50));
        
    //variables for x axis ticks and labels:
    QVector<double> ticks;
    QVector<QString> labels;

	//loop to print the same number of ticks to match the number of publication types
    for (int i = 1 ; i <= xaxis.size() ; i++)
    {
        ticks << i;
    }
    
    //loop to print the labels
    int len = xlabel.size();
    for(int i = 0; i < len; i++)
    {
        //labels.insert(i, QString::fromUtf8(xlabel[i].c_str()));
		labels << xlabel[i];
    }

	//graph plotting settings
    ui->customPlot->xAxis->setAutoTicks(false);
    ui->customPlot->xAxis->setAutoTickLabels(false);
    ui->customPlot->xAxis->setTickVector(ticks);
    ui->customPlot->xAxis->setTickVectorLabels(labels);
    ui->customPlot->xAxis->setTickLabelRotation(60);
    ui->customPlot->xAxis->setSubTickCount(0);
    ui->customPlot->xAxis->setTickLength(0, 4);
    ui->customPlot->xAxis->grid()->setVisible(true);
    ui->customPlot->xAxis->setRange(0, 8);
    ui->customPlot->xAxis->setLabel(xtitle);

    //make the y-axis
    ui->customPlot->yAxis->setRange(0, yaxis_range);

	//add space to the left border
    ui->customPlot->yAxis->setPadding(5);

	//y-axis label
    ui->customPlot->yAxis->setLabel(ytitle);
    ui->customPlot->yAxis->grid()->setSubGridVisible(true);

	//other graph plot settings
    QPen gridPen;
    gridPen.setStyle(Qt::SolidLine);
    gridPen.setColor(QColor(0, 0, 0, 25));
    ui->customPlot->yAxis->grid()->setPen(gridPen);
    gridPen.setStyle(Qt::DotLine);
    ui->customPlot->yAxis->grid()->setSubGridPen(gridPen);

    //The actual values for plotting
    QVector<double> publicationData;
	//loop to put in the values to the QVector
	for (int i = 0; i <= xaxis.size(); i++)
	{
		publicationData << xaxis[i];
	}

	//plot the data onto the graph
    Person->setData(ticks, publicationData);


    //setup legend:
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->customPlot->legend->setBrush(QColor(255, 255, 255, 200));
    QPen legendPen;
    legendPen.setColor(QColor(130, 130, 130, 200));
    ui->customPlot->legend->setBorderPen(legendPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    
}


//method for creating a window which displays a line graph
void graph:: createLineGraph(string title, int yaxis_range, vector<int> xaxis, vector<string> xlabel, string xtitle, string ytitle)
{
    //add graph and set how they look like
    ui->customPlot->addGraph();
    
	/*******
	ui->customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    QPen pen;
    pen.setColor(QColor(1, 92, 191));
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(2.5);
    ui->customPlot->graph()->setPen(pen);
	*******/

	//blue line colour
	customPlot->setPen(QPen(Qt::blue));
	customPlot->setBrush(QBrush(QColor(0, 0, 255, 20)));
	    
    //ui->customPlot->graph()->setScatterStyle(QCPScatterStyle(QPixmap("./sun.png")));
    
    //variables used to plot
    QVector<double> year, value;

	//loop to set x-axis values
    for (int i = 1; i <= xaxis.size(); i++)
    {
        year << i;  //a loop to print out the ticks
    }
    
	//loop to set y-axis values
	for (int i = 0; i < yaxis.size(); i++)
	{
		value << yaxis[i];
	}

	//plot the values
    ui->customPlot->graph()->setData(year, value);
    
    //set title of plot:
    ui->customPlot->plotLayout()->insertRow(0);
    ui->customPlot->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->customPlot,title));
    //set a fixed tick-step to one tick per year value:
    ui->customPlot->xAxis->setAutoTickStep(false);
    ui->customPlot->xAxis->setTickStep(1);
    ui->customPlot->xAxis->setSubTickCount(3);
    //other axis configurations:
    ui->customPlot->xAxis->setLabel(xtitle);
    ui->customPlot->yAxis->setLabel(ytitle);
    ui->customPlot->xAxis2->setVisible(true);
    ui->customPlot->yAxis2->setVisible(true);
    ui->customPlot->xAxis2->setTickLabels(false);
    ui->customPlot->yAxis2->setTickLabels(false);
    ui->customPlot->xAxis2->setTicks(false);
    ui->customPlot->yAxis2->setTicks(false);
    ui->customPlot->xAxis2->setSubTickCount(0);
    ui->customPlot->yAxis2->setSubTickCount(0);
    ui->customPlot->xAxis->setRange(0, xaxis.size());
    ui->customPlot->yAxis->setRange(0, yaxis_range);
    

}

//method for creating a window which display a pie chart from the Publications summary
//void createPieChart(std::string title, int num_publications, std::vector<int> xaxis, std::vector<std::string> xlabel);
//{

//}