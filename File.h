#ifndef TOUCH_H
#define TOUCH_H
#include <string>

using  namespace std;

class File
{
private:
    string name;
    string content;

public:
    File(string fName);
    ~File();
    string getName();
	void setContent(string text);
};

#endif
