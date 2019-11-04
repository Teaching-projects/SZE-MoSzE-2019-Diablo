#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <iostream>
#include <string>
#include <list>

#include "File.h"

using namespace std;

class Directory
{
private:
	string name;
	list<Directory*> content;
	list<File*> files;

public:
	Directory(string dirName);
	~Directory();

    void recursiveDelete();
	string getName();
	list<string> ls();
	Directory* searchDir(string dirName);
	File* searchFile(string fileName);
	bool makeDirectory(string dirName);
	bool makeFile(string fileName);
	bool hasChild();
	bool remove(string dirName, bool recursive);
	//bool removeRecursiveDirectory(string dirName);
};


#endif