#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <iostream>
#include <string>
#include <list>

#include "File.h"

using namespace std;

/**
@brief könyvtárakat megvalósító osztály
*/

class Directory
{
private:
	/**
	@brief könyvtár neve
	*/
	string name;
	/**
	@brief könyvtár alkönyvtárai
	Egy lista, amely Directory* poiterekként tárolja a könyvtár alkönyvtárait.
	*/
	list<Directory*> content;
	/**
	@brief könyvtárban található fájlok
	Egy lista, amely File* poiterekként tárolja a könyvtárban található fájlokat.
	*/
	list<File*> files;

public:
	/**
	@brief könyvtár osztály konstruktora
	@param dirName: könyvtár neve, kötelezõ
	*/
	Directory(string dirName);
	/**
	@brief könyvtár osztály dekonstruktora
	dinamikusan foglalt Directory* és File* pointerek felszabadítása, törli az összes tartalmazó fájlt és alkönyvtárat
	*/
	~Directory();

	/**
	@brief rekurzívan törli az összes tartalmazó fájl és alkönyvtárat, destruktor hívja
	*/
    void recursiveDelete();
	/**
	@brief getter függvény a könyvtár nevéhez
	@return könyvtár neve
	*/
	string getName() const;
	/**
	@brief barát << operátor a standard kimenetre vagy fájlba íratáshoz
	@param cout elsõ operandus, hova írjuk ki a könyvtárat, lehet ofstream, cout, cerr ...
	@param dir második operandus, a kiíratandó könyvtárra mutató pointer
	@return paraméterként kapott ostream objektum referenciája
	*/
	friend ostream& operator<<(ostream& cout, Directory* dir);
	/**
	@brief megkeresi, hogy van-e adott nevû alkönyvtár a mappában
	@param dirName a keresendõ könyvtár neve
	@return az_alkönyvtárra_mutató_pointer, ha megtalálta
	@return nullptr, egyébként
	*/
	Directory* searchDir(string dirName);
	/**
	@brief megkeresi, hogy van-e adott nevû fájl a mappában
	@param fileName a keresendõ fájl neve
	@return a_fájlra_mutató_pointer, ha megtalálta
	@return nullptr, egyébként
	*/
	File* searchFile(string fileName);
	/**
	@brief adott nevû alkönyvtárat hoz létre
	@param dirName a létrehozandó alkönyvtár neve
	@return true, ha nincs még a megadott nevû alkönyvtár
	@return hibát dob, egyébként
	@throws runtime_error("File_or_directory_already_exist!") ha már létezik a megadott néven alkönyvtár
	*/
	bool makeDirectory(string dirName);
	/**
	@brief adott nevû fájlt hoz létre
	@param fileName a létrehozandó fájl neve, kötelezõ
	@param content a létrehozandó fájl tartalma, nem kötelezõ
	@return true, ha nincs még a megadott nevû fájl
	@return hibát dob, egyébként
	@throws runtime_error("File_or_directory_already_exist!") ha már létezik a megadott néven alkönyvtár
	*/
	bool makeFile(string fileName, string content = "");
	/**
	@brief ellenõrzi, hogy van-e a könyvtárnak gyereke (alkönyvtár, fájl)
	@return false, ha nincs tartalma
	@return true, egyébként
	*/
	bool hasChild();
	/**
	@brief megkísérel kitörölni adott nevû alkönyvtárat
	@param dirName a törlendõ könyvtár neve
	@param recursive true, ha rekurzívan szeretnénk törölni \n egyébként false
	@return true, ha sikeres a törlés
	@return hibát dob, egyébként
	@throws runtime_error("Directory_is_not_empty!") ha nem üres a könyvtár és nem rekurzívan törlünk
	@throws runtime_error("File_or_directory_does_not_exist!") ha nem létezik adott nevû könyvtár
	*/
	bool remove(string dirName, bool recursive);
};

inline ostream& operator<<(ostream& cout, Directory* dir) {
	for (auto& i : dir->content) cout << i->getName() << endl;
	for (auto& i : dir->files) cout << i->getName() << endl;
	return cout;
}

#endif