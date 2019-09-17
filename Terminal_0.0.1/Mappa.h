#ifndef MAPPA_H
#define MAPPA_H

#include <iostream>
#include <string>
#include <list>

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
};


#endif // MAPPA_H
