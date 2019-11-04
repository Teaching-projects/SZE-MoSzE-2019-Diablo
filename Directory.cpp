#include "Directory.h"

Directory::Directory(string dirName)
{
	name = dirName;
}

Directory::~Directory()
{
	this->recursiveDelete();
}


string Directory::getName() {
	return name;
}

void Directory::recursiveDelete() {
	for (auto i : files) {
		delete i;
	}
	files.clear();
	for (auto i : content) {
		i->recursiveDelete();
		delete i;
	}
	content.clear();
}


list<string> Directory::ls() {
	list<string> kids;
	for (auto& iter : content)
	{
		kids.push_back(iter->getName());
	}
	for (auto& iter : files)
	{
		kids.push_back(iter->getName());
	}
	return kids;
}

Directory* Directory::searchDir(string dirName) {
	for (auto& iter : content)
	{
		if ((iter->getName()) == dirName) return iter;
	}
	return nullptr;
}

bool Directory::makeDirectory(string dirName) {
	if (this->searchDir(dirName) == nullptr) {
		content.push_back(new Directory(dirName));
		return true;
	}
	return false;
}

bool Directory::hasChild() {
	return content.size() > 0 || files.size() > 0;
}

bool Directory::remove(string name, bool recursive) {
	File* f = this->searchFile(name);
	if (f != nullptr) {
		delete f;
		files.remove(f);
		return true;
	}
	Directory* d = this->searchDir(name);
	if (d != nullptr) {
		if (!d->hasChild()) {
			delete d;
			content.remove(d);
			return true;
		}
		else if (recursive) {
			delete d;
			content.remove(d);
			return true;
		}
		else return false;
	}
	else return false;
}

File* Directory::searchFile(string fileName) {
	for (auto& iter : files)
	{
		if ((iter->getName()) == fileName) return iter;
	}
	return nullptr;
}

bool Directory::makeFile(string fileName) {
	if (this->searchDir(fileName) == nullptr && this->searchFile(fileName) == nullptr) {
		files.push_back(new File(fileName));
		return true;
	}
	return false;
}