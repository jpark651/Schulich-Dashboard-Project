/**
* This class implements the methods in publications.h
*/
#include <string>
#include <iostream>
#include <stdlib.h>
#include <list>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "publications.h"
using namespace std;

//publications constructor
publications:: publications (string file)
{
	filename = file;
}

//filters out rows with mandatory data that is missing or incorrect
list<list<string> > publications:: filterErrors(list<list<string> > organized)
{
	list<list<string> > filtered;

	/* code goes here */

	return filtered;
}
