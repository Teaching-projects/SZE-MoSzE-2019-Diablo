#ifndef TERMINAL_H
#define TERMINAL_H

#include <string>
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
	bool WriteToFile(string filename);

private:
	vector<Directory*> workingDirectory;
	Directory* root;
	vector<string> split(string cmd);

	bool cd(vector<Directory*> dir);
	bool ls(vector<Directory*> dir);
	bool mkdir(vector<Directory*> dir, string dirName);
	bool touch(vector<Directory*> dir, string fileName);
	bool echo(vector<Directory*> dir, string fileName, string text);
	//bool mv(vector<Directory*> path1, vector<Directory*> path2);
	vector<string> processPath(string path);
	vector<Directory*> followPath(vector<string> path);
};

#endif
