#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <iostream>
#include <string>
#include <list>

#include "File.h"

using namespace std;

/**
@brief k�nyvt�rakat megval�s�t� oszt�ly
*/

class Directory
{
private:
	/**
	@brief k�nyvt�r neve
	*/
	string name;
	/**
	@brief k�nyvt�r alk�nyvt�rai
	Egy lista, amely Directory* poiterekk�nt t�rolja a k�nyvt�r alk�nyvt�rait.
	*/
	list<Directory*> content;
	/**
	@brief k�nyvt�rban tal�lhat� f�jlok
	Egy lista, amely File* poiterekk�nt t�rolja a k�nyvt�rban tal�lhat� f�jlokat.
	*/
	list<File*> files;

public:
	/**
	@brief k�nyvt�r oszt�ly konstruktora
	@param dirName: k�nyvt�r neve, k�telez�
	*/
	Directory(string dirName);
	/**
	@brief k�nyvt�r oszt�ly dekonstruktora
	dinamikusan foglalt Directory* �s File* pointerek felszabad�t�sa, t�rli az �sszes tartalmaz� f�jlt �s alk�nyvt�rat
	*/
	~Directory();

	/**
	@brief rekurz�van t�rli az �sszes tartalmaz� f�jl �s alk�nyvt�rat, destruktor h�vja
	*/
    void recursiveDelete();
	/**
	@brief getter f�ggv�ny a k�nyvt�r nev�hez
	@return k�nyvt�r neve
	*/
	string getName() const;
	/**
	@brief bar�t << oper�tor a standard kimenetre vagy f�jlba �rat�shoz
	@param cout els� operandus, hova �rjuk ki a k�nyvt�rat, lehet ofstream, cout, cerr ...
	@param dir m�sodik operandus, a ki�ratand� k�nyvt�rra mutat� pointer
	@return param�terk�nt kapott ostream objektum referenci�ja
	*/
	friend ostream& operator<<(ostream& cout, Directory* dir);
	/**
	@brief megkeresi, hogy van-e adott nev� alk�nyvt�r a mapp�ban
	@param dirName a keresend� k�nyvt�r neve
	@return az_alk�nyvt�rra_mutat�_pointer, ha megtal�lta
	@return nullptr, egy�bk�nt
	*/
	Directory* searchDir(string dirName);
	/**
	@brief megkeresi, hogy van-e adott nev� f�jl a mapp�ban
	@param fileName a keresend� f�jl neve
	@return a_f�jlra_mutat�_pointer, ha megtal�lta
	@return nullptr, egy�bk�nt
	*/
	File* searchFile(string fileName);
	/**
	@brief adott nev� alk�nyvt�rat hoz l�tre
	@param dirName a l�trehozand� alk�nyvt�r neve
	@return true, ha nincs m�g a megadott nev� alk�nyvt�r
	@return hib�t dob, egy�bk�nt
	@throws runtime_error("File_or_directory_already_exist!") ha m�r l�tezik a megadott n�ven alk�nyvt�r
	*/
	bool makeDirectory(string dirName);
	/**
	@brief adott nev� f�jlt hoz l�tre
	@param fileName a l�trehozand� f�jl neve, k�telez�
	@param content a l�trehozand� f�jl tartalma, nem k�telez�
	@return true, ha nincs m�g a megadott nev� f�jl
	@return hib�t dob, egy�bk�nt
	@throws runtime_error("File_or_directory_already_exist!") ha m�r l�tezik a megadott n�ven alk�nyvt�r
	*/
	bool makeFile(string fileName, string content = "");
	/**
	@brief ellen�rzi, hogy van-e a k�nyvt�rnak gyereke (alk�nyvt�r, f�jl)
	@return false, ha nincs tartalma
	@return true, egy�bk�nt
	*/
	bool hasChild();
	/**
	@brief megk�s�rel kit�r�lni adott nev� alk�nyvt�rat
	@param dirName a t�rlend� k�nyvt�r neve
	@param recursive true, ha rekurz�van szeretn�nk t�r�lni \n egy�bk�nt false
	@return true, ha sikeres a t�rl�s
	@return hib�t dob, egy�bk�nt
	@throws runtime_error("Directory_is_not_empty!") ha nem �res a k�nyvt�r �s nem rekurz�van t�rl�nk
	@throws runtime_error("File_or_directory_does_not_exist!") ha nem l�tezik adott nev� k�nyvt�r
	*/
	bool remove(string dirName, bool recursive);
};

inline ostream& operator<<(ostream& cout, Directory* dir) {
	for (auto& i : dir->content) cout << i->getName() << endl;
	for (auto& i : dir->files) cout << i->getName() << endl;
	return cout;
}

#endif