/**
* Header file for the publications class and its associated methods
*/
#ifndef PUBLICATIONS_H_INCLUDED
#define PUBLICATIONS_H_INCLUDED
#include <string>
#include <iostream>
#include <stdlib.h>
#include <list>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
using namespace std;

class publications
{
	private:
		//variables
		string filename;
		list<list<string> > names;

	public:
		//constructor
		publications(string filename);

		//filters out rows with mandatory data that is missing or incorrect
		list<list<string> > filterErrors(list<list<string> > organized);
};

#endif //PUBLICATIONS_H_INCLUDED
