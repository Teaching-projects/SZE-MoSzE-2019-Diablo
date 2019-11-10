#include "Directory.h"

Directory::Directory(string dirName)
{
	name = dirName;
}

Directory::~Directory()
{
	this->recursiveDelete();
}


string Directory::getName() const {
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
	throw runtime_error("File or directory already exist!");
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
		else throw runtime_error("Directory is not empty!");
	}
	else throw runtime_error("File or directory does not exist!");
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
	throw runtime_error("File or directory already exists!");
}