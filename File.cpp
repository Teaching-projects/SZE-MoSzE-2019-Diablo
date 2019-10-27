#include "File.h"

File::File(string fName){
    name = fName;
}

File::~File(){}

string File:: getName(){
    return name;
}

void File::setContent(string text)
{
	content = text;
}
