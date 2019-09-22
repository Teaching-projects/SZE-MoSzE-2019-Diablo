#include <iostream>
#include <string>

#include "Mappa.h"
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
			if (!terminal->processCmd(cmd)) cout << "Error!" << endl;
		}
	} while (!exit);
}