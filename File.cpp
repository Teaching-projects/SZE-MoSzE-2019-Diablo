#include "File.h"

File::File(string fName, string content) : name(fName), content(content) {}

File::~File(){}

string File:: getName() const {
    return name;
}

void File::setContent(string text)
{
	content = text;
}
