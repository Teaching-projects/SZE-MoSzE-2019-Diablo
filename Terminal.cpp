#include "Terminal.h"

Terminal::Terminal()
{
	root = new Mappa("/");
	workingDirectory.push_back(root);
}

Terminal::~Terminal()
{ }

string Terminal::pwd()
{
	if (workingDirectory.size() == 1) return "/";
	string path = "";
	for (auto& iter : workingDirectory)
	{
		if(iter->getName() != "/") path += "/" + iter->getName();
	}
	return path;
}

bool Terminal::cd(string dirName)
{
	if (dirName == ".." && workingDirectory.size() == 1) return false;
	if (dirName == "..") {
		workingDirectory.pop_back();
		return true;
	}
	Mappa* toDir = workingDirectory.back()->search(dirName);
	if (toDir != nullptr) {
		workingDirectory.push_back(toDir);
		return true;
	}
	return false;
}

list<string> Terminal::ls()
{
	return workingDirectory.back()->list();
}

bool Terminal::mkdir(string dirName)
{
	if (workingDirectory.back()->makeDirectory(dirName)) return true;
	return false;
}

bool Terminal::processCmd(string command)
{
	if (command == "") return true;
	vector<string> args = split(command);
	if (args.size() == 1 && args[0] == "ls") {
		for (auto iter : ls()) cout << iter << endl;
		return true;
	}
	else if (args.size() == 2 && args[0] == "cd") {
		return cd(args[1]);
	}
	else if (args.size() == 2 && args[0] == "mkdir") {
		return mkdir(args[1]);
	}
	else if (args.size() == 1 && args[0] == "pwd") {
		cout << pwd();
		return true;
	}
	else if (args.size() == 2 && args[0] == "rm") {
		return workingDirectory.back()->removeDirectory(args[1]);
	}
	else if (args.size() == 3 && args[0] == "rm" && args[1] == "-rf") {
		return workingDirectory.back()->removeRecursiveDirectory(args[2]);
	}
	else return false;
}

vector<string> Terminal::split(string cmd)
{
	vector<string> args;
	string temp = "";
	for (auto iter : cmd) {
		if (isspace(iter) && temp.size() != 0) {
			args.push_back(temp);
			temp = "";
		}
		else if (!isspace(iter)) {
			temp += iter;
		}
	}
	if (temp != "") args.push_back(temp);
	return args;
}