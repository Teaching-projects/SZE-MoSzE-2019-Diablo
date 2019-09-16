#include "Mappa.h"

Mappa::Mappa(string dirName)
{

}

Mappa::~Mappa()
{ }


string Mappa::getName() {
	return name;
}

list<string> Mappa::list() {
	if (content.size() == 1) cout << "/" << endl;
	string cell = "";
	for (auto& iter : content)
	{
		cell += "/" + iter->getName();
	}
	cout << cell << endl;
}

Mappa* Mappa::search(string dirName) {
	if (content.size() == 1) cout << "/" << endl;

	for (auto& iter : content)
	{
		if(( iter->getName())==dirName)
            {cout<<"siker"<<endl;
        }
		else return false;
	}

}

bool Mappa::makeDirectory(string dirName) {
	if (content.back()->search(dirName) != nullptr) {
		content.back()->getName();
		return true;
	}
	return false;


}
