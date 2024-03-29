#include <iostream>
#include <string>

#include "Directory.h"
#include "Terminal.h"

using namespace std;

int main() {
	Terminal* terminal = new Terminal();
	bool exit = false;
	do
	{
		cout << endl << "root@adam-niki-PC:" << terminal->pwd() << "# ";
		string cmd;
		getline(cin, cmd);
		if (cmd == "exit") exit = true;
		else {
			cout << endl;
			try
			{
				terminal->processCmd(cmd);
			}
			catch (const exception& e)
			{
				cerr << e.what() << endl;
			}
		}
	} while (!exit);
	delete terminal;
	return 0;
}