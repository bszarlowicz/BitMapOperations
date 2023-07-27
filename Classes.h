#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <vector>
#include "Exceptions.h"
#include "Functions.h"

/*
*Klasa wirtualna
*/
class Bitmapa
{
public:
	virtual unsigned length() const = 0;
	virtual unsigned width() const = 0;

	virtual bool& operator() (unsigned x, unsigned y) = 0;			//indeks
	virtual bool operator() (unsigned x, unsigned y) const = 0;		//WARTOŚĆ

	virtual ~Bitmapa() {}
};

/*
*Klasa będąca pochodną klasy 'Bitmapa', która reperezentuje utworzone bitmapy
*/
class BitmapaExt
	:public Bitmapa
{
public:
	bool** array = nullptr;
	unsigned Length;
	unsigned Width;

	BitmapaExt(unsigned L, unsigned W);

	unsigned length() const;
	unsigned width() const;

	virtual bool& operator() (unsigned x, unsigned y);			
	virtual bool operator() (unsigned x, unsigned y) const;
};

/*
*Przeładowanie operatora '<<'
*/
std::ostream& operator<<(std::ostream& os, const BitmapaExt& mapa);

/*
*Klasa wirtualna
*/
class Przeksztalcenie
{
public:
	virtual void przeksztalc(Bitmapa&) = 0;
};

/*
*Pochodna klasy 'Przeksztalcenie', realizująca filtr morfologiczny - inwerjsa
*/
class Inwersja
	:public Przeksztalcenie
{
public:
	void przeksztalc(Bitmapa& mapa);
};

/*
*Pochodna klasy 'Przeksztalcenie', realizująca filtr morfologiczny - erozja
*/
class Erozja
	:public Przeksztalcenie
{
public:
	void przeksztalc(Bitmapa& mapa);

};

/*
*Pochodna klasy 'Przeksztalcenie', realizująca filtr morfologiczny - dylatacja
*/
class Dylatacja
	:public Przeksztalcenie
{
public:
	void przeksztalc(Bitmapa& mapa);

};

/*
*Pochodna klasy 'Przeksztalcenie', realizująca filtr morfologiczny - zerowanie
*/
class Zerowanie
	:public Przeksztalcenie
{
public:
	void przeksztalc(Bitmapa& mapa);
};

/*
*Pochodna klasy 'Przeksztalcenie', realizująca filtr morfologiczny - uśrednianie
*/
class Usrednianie
	:public Przeksztalcenie
{
public:
	void przeksztalc(Bitmapa& mapa);
};

/*
*Pochodna klasy 'Przeksztalcenie', kolejkująca dodane przekształcenia
*/
class ZlozeniePrzeksztalcen
	:public Przeksztalcenie
{
public:
	std::vector<Przeksztalcenie*> container;

	void dodajPrzeksztalcenie(Przeksztalcenie* p);


	void przeksztalc(Bitmapa& mapa);		//funkcja wirtualna oddziedziczona po klasie 'Przeksztalcenie'
};

/*
*Funckja sprawdzająca sąsiadów jednego elementu(i,j) bitmapy(Erozja)
*@param mapa - referencja do bitmapy
*@param i - numer rzędu
*@param j - numer kolumny
*@return true/false
*/
bool checkNeighboursErozja(Bitmapa& mapa, unsigned i, unsigned j);

/*
*Funckja sprawdzająca sąsiadów jednego elementu(i,j) bitmapy(Dylatacja)
*@param mapa - referencja do bitmapy
*@param i - numer rzędu
*@param j - numer kolumny
*@return true/false
*/
bool checkNeighboursDylatacja(Bitmapa& mapa, unsigned i, unsigned j);

/*
*Funckja sprawdzająca sąsiadów jednego elementu(i,j) bitmapy(Uśrednianie)
*@param mapa - referencja do bitmapy
*@param i - numer rzędu
*@param j - numer kolumny
*@return true/false
*/
bool checkNeighboursUsrdenianie(Bitmapa& mapa, unsigned i, unsigned j);


#endif
