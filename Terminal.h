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
	bool processCmd(string command);

private:
	list<Directory*> workingDirectory;
	Directory* root;
	vector<string> split(string cmd);

	bool cd(string dirName);
	list<string> ls();
	bool mkdir(string dirName);
	bool touch(string fileName);
	bool echo(string fileName, string text);
};



