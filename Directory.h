#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <iostream>
#include <string>
#include <list>
#include <math.h>

using namespace std;

class Mappa
{
private:
	string name;
	list<Mappa*> content;

public:
	Mappa(string dirName);
	~Mappa();

	string getName();
	list<string> list();
	Mappa* search(string dirName);
	bool makeDirectory(string dirName);
	bool removeDirectory(string dirName);
	bool removeRecursiveDirectory(string dirName);
};


#endif // DIRECTORY_H

