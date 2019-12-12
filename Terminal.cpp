#include "Terminal.h"

#include <sstream>
#include <iostream>
#include <fstream>

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

bool Terminal::cd(vector<Directory*> dir)
{
	if (dir.empty()) throw runtime_error("No such file or directory!");
	else {
		workingDirectory = dir;
		return true;
	}
}

bool Terminal::ls(vector<Directory*> dir)
{
	if (dir.empty()) throw runtime_error("No such file or directory!");
	else {
		cout << dir.back();
		return true;
	}
}

bool Terminal::mkdir(vector<Directory*> dir, string dirName)
{
	if (dir.empty()) throw runtime_error("No such file or directory!");
	else {
		return dir.back()->makeDirectory(dirName);
	}
}

bool Terminal::touch(vector<Directory*> dir, string fileName)
{
	if (dir.empty()) throw runtime_error("No such file or directory!");
	else {
		return dir.back()->makeFile(fileName);;
	}
}

bool Terminal::echo(vector<Directory*> dir, string fileName, string text)
{
	if (dir.empty()) throw runtime_error("No such file or directory!");
	else {
		File* f = dir.back()->searchFile(fileName);
		if (f != nullptr) f->setContent(text);
		else dir.back()->makeFile(fileName, text);
		return true;
	}
}

vector<string> Terminal::processPath(string path)
{
	vector<string> args;
	if (path[0] == '/') args.push_back("/");
	string temp = "";
	for (auto iter : path) {
		if (iter == '/' && temp.size() != 0) {
			args.push_back(temp);
			temp = "";
		}
		else if (iter != '/') {
			temp += iter;
		}
	}
	if (temp != "") args.push_back(temp);
	return args;
}

vector<Directory*> Terminal::followPath(vector<string> path)
{
	vector<Directory*> actPath;
	if (path[0] == "/") {
		actPath = { root };
		path.erase(path.begin());
	}
	else actPath = workingDirectory;
	for (auto& i : path) {
		if (actPath.size() < 1) return vector<Directory*>{};
		else if (i == "..") actPath.pop_back();
		else {
			Directory* a = actPath.back()->searchDir(i);
			if (a == nullptr) return vector<Directory*>{};
			else actPath.push_back(a);
		}
	}
	return actPath;
}

/*bool mv(vector<Directory*> path1, vector<Directory*> path2) {


}*/

bool Terminal::processCmd(string command)
{
	if (command == "") return true;
	vector<string> args = split(command);
	if ((args.size() == 1 || args.size() == 2) && args[0] == "ls") {
		if (args.size() == 1) return ls(vector<Directory*>{ workingDirectory.back() });
		else return ls(followPath(processPath(args[1])));
	}
	else if (args.size() == 2 && args[0] == "cd") {
		return cd(followPath(processPath(args[1])));
	}
	else if (args.size() == 2 && args[0] == "mkdir") {
		vector<string> p = processPath(args[1]);
		string dirName = p.back();
		p.pop_back();
		if (p.size() < 1) return mkdir(vector<Directory*>{ workingDirectory.back() }, dirName);
		else if (p.front() == "/" && p.size() < 2) return mkdir(vector<Directory*>{ root }, dirName);
		else return mkdir(followPath(p), dirName);
	}
	else if (args.size() == 1 && args[0] == "pwd") {
		cout << pwd();
		return true;
	}
	else if (args.size() == 2 && args[0] == "rm") {
		vector<string> p = processPath(args[1]);
		string dirName = p.back();
		p.pop_back();
		if (p.size() < 1) return workingDirectory.back()->remove(dirName, false);
		else if (p.front() == "/" && p.size() < 2) return root->remove(dirName, false);
		else return followPath(p).back()->remove(dirName, false);
	}
	else if (args.size() == 3 && args[0] == "rm" && args[1] == "-rf") {
		vector<string> p = processPath(args[2]);
		string dirName = p.back();
		p.pop_back();
		if (p.size() < 1) return workingDirectory.back()->remove(dirName, true);
		else if (p.front() == "/" && p.size() < 2) return root->remove(dirName, true);
		else return followPath(p).back()->remove(dirName, true);
	}
	else if (args.size() == 2 && args[0] == "touch") {
		vector<string> p = processPath(args[1]);
		string fileName = p.back();
		p.pop_back();
		if (p.size() < 1) return touch(vector<Directory*>{ workingDirectory.back() }, fileName);
		else if (p.front() == "/" && p.size() < 2) return touch(vector<Directory*>{ root }, fileName);
		else return touch(followPath(p), fileName);
	}
	else if (args.size() == 4 && args[0] == "echo" && args[1][0] == '"' && args[1][args[1].size() - 1] == '"' && args[2] == ">") {
		vector<string> p = processPath(args[3]);
		string fileName = p.back();
		p.pop_back();
		if (p.size() < 1) return echo(vector<Directory*>{ workingDirectory.back() }, fileName, args[1]);
		else if (p.front() == "/" && p.size() < 2) return echo(vector<Directory*>{ root }, fileName, args[1]);
		else return echo(followPath(p), fileName, args[1]);
	}
	else if (args.size() == 2 && args[0]=="exit" && args[1]!=""){
		WriteToFile(args[1]);
	}
	else if (args.size() == 1 && args[0] == "exit" ) {
		WriteToFile("myfile.txt");
	}
	else throw runtime_error("Unrecognized command or missing parameter!");
}

vector<string> Terminal::split(string cmd)
{
	istringstream line(cmd);
	vector<string> args;
	string temp;
	while (line >> temp) args.push_back(temp);
	return args;
}

bool Terminal::WriteToFile(string filename) {
	ofstream f;
	string s = root->makeString();
	f.open(filename);
	if (f.is_open()) {
		f << s;
		f.close();
		return true;
	}
	return false;
}
