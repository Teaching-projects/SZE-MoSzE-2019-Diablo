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
	string getName() const;
	friend ostream& operator<<(ostream& cout, Directory* dir);
	Directory* searchDir(string dirName);
	File* searchFile(string fileName);
	bool makeDirectory(string dirName);
	bool makeFile(string fileName);
	bool hasChild();
	bool remove(string dirName, bool recursive);
};

inline ostream& operator<<(ostream& cout, Directory* dir) {
	for (auto& i : dir->content) cout << i->getName() << endl;
	for (auto& i : dir->files) cout << i->getName() << endl;
	return cout;
}

#endif