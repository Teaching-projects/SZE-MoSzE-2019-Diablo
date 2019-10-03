#include "Directory.h"

Mappa::Mappa(string dirName)
{
    name=dirName;
}

Mappa::~Mappa()
{ }


string Mappa::getName() {
	return name;
}

void Mappa:: recurciveDelete(){

    for(auto& iter : content) {
        iter->recurciveDelete();
        content.remove(iter);
    }
}


list<string> Mappa::list() {
    ::list<string> kids;
    for (auto& iter : content)
	{
		kids.push_back(iter->getName());
	}
	return kids;
}

Mappa* Mappa::search(string dirName) {
	if (content.size() == 0) return nullptr;

	for (auto& iter : content)
	{
		if(( iter->getName())==dirName) return iter;
	}
	 return nullptr;
}

bool Mappa::makeDirectory(string dirName) {
	if (this->search(dirName) == nullptr) {
		content.push_back(new Mappa(dirName));
		return true;
	}
	return false;
}

bool Mappa:: hasChild(){
    return content.size()>0;
}

bool Mappa:: removeDirectory(string dirName){
    Mappa* iter=this->search(dirName);
    bool Child=iter->hasChild();

  	    if(iter!=nullptr && Child==false){
            content.remove(iter);
            return true;
  	    }
  	    else{return false;}


}

bool Mappa:: removeRecursiveDirectory(string dirName){
    Mappa* iter=this->search(dirName);
    iter->recurciveDelete();
    content.remove(iter);

    return true;

  }
