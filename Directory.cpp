#include "Directory.h"

Directory::Directory(string dirName)
{
	name = dirName;
}

Directory::~Directory()
{ }


string Directory::getName() {
	return name;
}

void Directory::recurciveDelete() {

	for (auto iter = content.begin(); iter != content.end();) {
		auto toDelete = iter;
		++iter;
		(*toDelete)->recurciveDelete();
		content.remove(*toDelete);
	}
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

Directory* Directory::search(string dirName) {
	if (content.size() == 0) return nullptr;

	for (auto& iter : content)
	{
		if ((iter->getName()) == dirName) return iter;
	}
	return nullptr;
}

bool Directory::makeDirectory(string dirName) {
	if (this->search(dirName) == nullptr) {
		content.push_back(new Directory(dirName));
		return true;
	}
	return false;
}

bool Directory::hasChild() {
	return content.size() > 0 || files.size() > 0;
}

bool Directory::remove(string name) {
	File* f = this->searchFile(name);
	if (f != nullptr) {
		files.remove(f);
		return true;
	}

	Directory* iter = this->search(name);
	bool Child = iter->hasChild();

	if (iter != nullptr && Child == false) {
		content.remove(iter);
		return true;
	}
	else { return false; }
}

bool Directory::removeRecursiveDirectory(string dirName) {
	files.clear();
	Directory* iter = this->search(dirName);
	iter->recurciveDelete();
	content.remove(iter);

	return true;

}

File* Directory::searchFile(string fileName)
{
	if (files.size() == 0) return nullptr;
	for (auto& iter : files)
	{
		if ((iter->getName()) == fileName) return iter;
	}
	return nullptr;
}

bool Directory::makeFile(string fileName)
{
	if (this->search(fileName) == nullptr && this->searchFile(fileName) == nullptr) {
		files.push_back(new File(fileName));
		return true;
	}
	return false;
}