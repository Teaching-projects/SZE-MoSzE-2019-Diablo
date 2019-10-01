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

/*bool Mappa:: removeDirectory(string dirName){
    for (auto& iter : content)
  	{
  	    if(iter->getName()==dirName){
            content.remove(iter);
            return true;
  	    }
  	    else{return false;}
	}

}*/
bool Mappa:: removeDirectory(string dirName){
    Mappa* iter=this->search(dirName);


  	    if(iter!=nullptr){
            content.remove(iter);
            return true;
  	    }
  	    else{return false;}


}

/*bool Mappa:: removeRecursiveDirectory(string dirName){

    for (auto& iter : content)
  	{
  	    while(iter!=nullptr){
            removeRecursiveDirectory(string dirName);
            iter++;
        }
         if(iter->getName()==dirName){
            content.remove(iter);
            return true;
  	    }
  	    else{return false;}

  	}

  }*/
