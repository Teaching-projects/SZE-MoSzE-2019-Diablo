#ifndef TOUCH_H
#define TOUCH_H
#include <string>

using  namespace std;

/**
@brief fájlokat megvalósító osztály
*/

class File
{
private:
	/**
	@brief fájlnév
	*/
    string name;
	/**
	@brief fájl tartalma
	*/
    string content;

public:
	/**
	@brief fájl osztály konstruktora
	@param fName: fájl neve, kötelezõ
	@param content: fájl tartalma egyetlen karakterláncban, nem kötelezõ
	*/
    File(string fName, string content = "");
    ~File();
	/**
	@brief getter függvény a fájl nevéhez
	@return fájl neve
	*/
    string getName() const;
	/**
	@brief setter függvény a fájl tartalmához
	@param text fájl tartalma egyetlen karakterláncban
	*/
	void setContent(string text);
};

#endif
