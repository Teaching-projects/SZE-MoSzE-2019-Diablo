#include <iostream>
#include <string>
#include <list>
#include <vector>

#include "Directory.h"

using namespace std;

class Terminal
{
public:
	Terminal();
	~Terminal();
	string pwd();
	bool cd(string dirName);
	list<string> ls();
	bool mkdir(string dirName);
	bool processCmd(string command);

private:
	list<Mappa*> workingDirectory;
	Mappa* root;
	vector<string> split(string cmd);
};



