#include "Mappa.h"

Mappa::Mappa(string dirName)
{
    name=dirName;
}

Mappa::~Mappa()
{ }


string Mappa::getName() {
	return name;
}

list<string> Mappa::list() {
    string cell="";
    ::list<string> kids;
    for (auto& iter : content)
	{
		kids.push_back(iter->getName());
	}

	return kids;
}

Mappa* Mappa::search(string dirName) {
	if (content.size() == 1) return nullptr;

	for (auto& iter : content)
	{
		if(( iter->getName())==dirName) return iter;

	}
	 return nullptr;

}

bool Mappa::makeDirectory(string dirName) {
	if (this->search(dirName) != nullptr) {
		content.push_back(new Mappa(dirName));
		return true;
	}
	return false;


}
