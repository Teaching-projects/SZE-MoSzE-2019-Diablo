#include "Terminal.h"

Terminal::Terminal()
{
	root = new Directory("/");
	workingDirectory.push_back(root);
}

Terminal::~Terminal()
{
	delete root;
}

string Terminal::pwd()
{
	if (workingDirectory.size() == 1) return "/";
	string path = "";
	for (auto& iter : workingDirectory)
	{
		if (iter->getName() != "/") path += "/" + iter->getName();
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
	Directory* toDir = workingDirectory.back()->searchDir(dirName);
	if (toDir != nullptr) {
		workingDirectory.push_back(toDir);
		return true;
	}
	return false;
}

list<string> Terminal::ls()
{
	return workingDirectory.back()->ls();
}

bool Terminal::mkdir(string dirName)
{
	if (workingDirectory.back()->makeDirectory(dirName)) return true;
	return false;
}

bool Terminal::touch(string fileName)
{
	if (workingDirectory.back()->makeFile(fileName)) return true;
	return false;
}

bool Terminal::echo(string fileName, string text)
{
	File* f = workingDirectory.back()->searchFile(fileName);
	if (f != nullptr) {
		f->setContent(text);
		return true;
	}
	else return false;
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
		return workingDirectory.back()->remove(args[1], false);
	}
	else if (args.size() == 3 && args[0] == "rm" && args[1] == "-rf") {
		return workingDirectory.back()->remove(args[2], true);
	}
	else if (args.size() == 2 && args[0] == "touch") {
		return touch(args[1]);
	}
	else if (args.size() == 4 && args[0] == "echo" && args[1][0] == '"' && args[1][args[1].size() - 1] == '"' && args[2] == ">") {
		return echo(args[3], args[1]);
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
