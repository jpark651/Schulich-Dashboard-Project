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

graph::graph(QWidget *parent) :
    //graph::graph(QWidget *parent) {
    QMainWindow(parent),
    ui(new Ui::graph)
{
    ui->setupUi(this);
    //    setGeometry(400, 250, 542, 390);
    //    graph::makePlot();
}

graph::~graph()
{
    delete ui;
}


/*Prepares the data needed to graph from the publications summary.
*/
void graph::preparePublications(string name, vector<string> types, vector<int> years, int diff_types, int begin, int end, int graphtype)
{
    vector<string> t = types;	//create a copy to manipulate
    vector<int> y = years;		//create a copy to manipulate
    string compare;				//for checking when a new type of publication exists
    int track = 0;				//used to track where in the string vector we are

    int size = types.size();	//get the size of the list
    int num_publications = 0;	//number of publications that fit the date range. used for y-axis

    vector<int> xaxis;			//array for the number of publications of each publication type
    vector<string> xlabel;		//string array for x-axis tick labels


    vector<int>::iterator itx;
    vector<string>::iterator itlabel;
    itx = xaxis.begin();
    itlabel = xlabel.begin();

    //initialize the array values to 0 to prepare for counting
    for (int count = 0; count < diff_types; count++)
    {
        //        xaxis.
        itx = xaxis.insert(itx, 0);
        itlabel = xlabel.insert(itlabel, "");

        //        xaxis[count] = 0;
    }

    printf("Inside prepare publications\n");

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

    printf("setting title for the graphs\n");

    //title for the graphs
    int beginsize = snprintf(NULL, 0, "%d", begin);
    int endsize = snprintf(NULL, 0, "%d", end);

    char beginstring[beginsize + 1];
    char endstring[endsize + 1];

    sprintf(beginstring, "%d", begin);
    sprintf(endstring, "%d", end);

    string title = name + ", " + beginstring + "-" + endstring;

    /* THE TYPE OF GRAPH THAT THE USER WANTS TO DISPLAY
    *    1 = bar
    *    2 = pie
    *    3 = line
    */
    if (graphtype == 1) {
        printf("Bar graph\n");
        createBarGraph(title, num_publications, xaxis, xlabel, "Number of Publications", "Publication Type");
    }
    else if (graphtype == 2) {
        printf("Line graph\n");
        createLineGraph(title, num_publications, xaxis, xlabel, "Number of Publications", "Publication Type");
    }
    //else if (graphtype == 3)
    //	createPiePublications(name, num_publications)

}

//need: clinical/grant, approval, amounts, years
//other: fac name, begin, end, graphtype

/*void graph:: prepareFunding(string fname, vector<string> c_or_g, vector<string> approval, vector<int> years, vector<double> amount, int begin, int end, int graphtype)
{
vector<string> type = c_or_g;	//create a copy to manipulate
vector<int> y = years;			//create a copy to manipulate
vector<string> a = approval;	//create a copy to manipulate
vector<double> am = amount;		//create a copy to manipulate
string compare;					//for checking when a new type of publication exists
int track = 0;					//used to track where in the string array we are
int size = type.size();	//get the size of the list
int num_publications = 0;	//number of publications that fit the date range. used for y-axis
vector<int> xaxis;			//array for the number of publications of each publication type
vector<string> xlabel;		//string array for x-axis tick labels
//initialize the array values to 0 to prepare for counting
for (int count = 0; count < diff_types; count++)
{
xaxis[count] = 0;
}
compare = type.front();	//the first publication type
xlabel[0] = type.front();	//record the first label
//This loop goes through the list of publications and counts how many are of each type.
for (int count = 0; count < size; count++)
{
//check if the publications is in the date range
if ((y.front() >= begin) && (y.front() <= end))
{
//check if the publication type is the same as the previous
if (type.front() == compare)
{
//record the publication
xaxis[track]++;
//pop from the list
type.erase(type.begin());
y.erase(y.begin());
}
//else start counting the next type
else
{
//record the publication for the new type
track++;
xaxis[track]++;
//record the label for the new type
xlabel[track] = type.front();
//pop from the list
type.erase(type.begin());
y.erase(y.begin());
//record the new publication type
compare = type.front();
}
}
else
{
//pop from the list
type.erase(type.begin());
y.erase(y.begin());
}
}
createBarGraph(title, largest, xaxis, xlabel, "Total Amount", "Funding Type");
}*/






//method for creating a window which displays a bar graph
void graph::createBarGraph(string title, int yaxis_range, vector<int> xaxis, vector<string> xlabel, string xtitle, string ytitle)
{
    //empty bar chart objects:
    QCPBars *Person = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    ui->customPlot->addPlottable(Person);

    //set names and colors:
    QPen pen;
    pen.setWidthF(1.0);

    //convert the string and set to be the title for the graph
    QString qTitle = QString::fromUtf8(title.c_str());
    Person->setName(qTitle);

    //colour
    pen.setColor(QColor(1, 92, 191));
    Person->setPen(pen);
    Person->setBrush(QColor(1, 92, 191, 50));

    //variables for x axis ticks and labels:
    QVector<double> ticks;
    QVector<QString> labels(0);

    //loop to print the same number of ticks to match the number of publication types
    for (int i = 1; i <= xaxis.size(); i++)
    {
        ticks << i;
    }

    //loop to print the labels
    int len = xlabel.size();
    for (int i = 0; i < len; i++)
    {
        //labels.insert(i, QString::fromUtf8(xlabel[i].c_str()));
        //		labels << xlabel[i];
        QString tmpLabel = QString::fromUtf8(xlabel.at(i).c_str());
        labels.append(tmpLabel);

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

    //convert string and display the xaxis title
    QString qXTitle = QString::fromUtf8(xtitle.c_str());
    ui->customPlot->xAxis->setLabel(qXTitle);

    //make the y-axis
    ui->customPlot->yAxis->setRange(0, yaxis_range);

    //add space to the left border
    ui->customPlot->yAxis->setPadding(5);

    //convert string and display y-axis label
    QString qYTitle = QString::fromUtf8(ytitle.c_str());
    ui->customPlot->yAxis->setLabel(qYTitle);
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
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop | Qt::AlignHCenter);
    ui->customPlot->legend->setBrush(QColor(255, 255, 255, 200));
    QPen legendPen;
    legendPen.setColor(QColor(130, 130, 130, 200));
    ui->customPlot->legend->setBorderPen(legendPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    QPixmap pixmap = QPixmap(this->width(), this->height());
    pixmap.fill(QColor(0, 0, 0, 255));


    this->ui->customPlot->activateWindow();
    statusBar()->clearMessage();
    ui->customPlot->replot();
    ui->customPlot->show();




}

void graph::closeEvent(QCloseEvent *event) {
    event->ignore();
    if (QMessageBox::Yes == QMessageBox::question(this, "Close Confirmation?",
        "Are you sure you want to exit?",
        QMessageBox::Yes | QMessageBox::No))
    {
        event->accept();
    }
}


void graph::close() {
    cout << "hello\n";
}

//void graph::do


//method for creating a window which displays a line graph
void graph::createLineGraph(string title, int yaxis_range, vector<int> xaxis, vector<string> xlabel, string xtitle, string ytitle)
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
    ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    ui->customPlot->graph(0)->setPen(QPen(Qt::blue));


    //variables used to plot
    QVector<double> year, value;

    //loop to set x-axis values
    for (int i = 1; i <= xaxis.size(); i++)
    {
        year << i;  //a loop to print out the ticks
    }

    //loop to set y-axis values
    for (int i = 0; i < xaxis.size(); i++)
    {
        value << xaxis[i];
    }

    //convert strings for titles
    QString qTitle = QString::fromUtf8(title.c_str());
    QString qXTitle = QString::fromUtf8(xtitle.c_str());
    QString qYTitle = QString::fromUtf8(ytitle.c_str());


    //plot the values
    ui->customPlot->graph()->setData(year, value);

    //set title of plot:
    ui->customPlot->plotLayout()->insertRow(0);
    ui->customPlot->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->customPlot, qTitle));
    //set a fixed tick-step to one tick per year value:
    ui->customPlot->xAxis->setAutoTickStep(false);
    ui->customPlot->xAxis->setTickStep(1);
    ui->customPlot->xAxis->setSubTickCount(3);
    //other axis configurations:
    ui->customPlot->xAxis->setLabel(qXTitle);
    ui->customPlot->yAxis->setLabel(qYTitle);
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