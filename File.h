#ifndef TOUCH_H
#define TOUCH_H
#include <string>

using  namespace std;

/**
@brief f�jlokat megval�s�t� oszt�ly
*/

class File
{
private:
	/**
	@brief f�jln�v
	*/
    string name;
	/**
	@brief f�jl tartalma
	*/
    string content;

public:
	/**
	@brief f�jl oszt�ly konstruktora
	@param fName: f�jl neve, k�telez�
	@param content: f�jl tartalma egyetlen karakterl�ncban, nem k�telez�
	*/
    File(string fName, string content = "");
    ~File();
	/**
	@brief getter f�ggv�ny a f�jl nev�hez
	@return f�jl neve
	*/
    string getName() const;
	/**
	@brief setter f�ggv�ny a f�jl tartalm�hoz
	@param text f�jl tartalma egyetlen karakterl�ncban
	*/
	void setContent(string text);
};

#endif
