#pragma once
#include "Locatar.h"
#include <vector>

using std::vector;

class AbstractRepo
{

public:

	virtual ~AbstractRepo() = default;



	/*
	Salvare locatar in lista
	param l : locatarul de salvat in lista
	*/
	virtual void store(const Locatar& l) = 0;

	/*
	* Sterge un locatar din lista
	* param poz : pozitia de la care locatarul va fi sters
	*/
	virtual void remove_repo(const int poz) = 0;

	/*
	* Insereaza un locatar in lista la pozitia data
	* param poz : pozitia la care va fi inserat elementul
	* param l : locatarul care va fi inserat
	*/
	virtual void insert_repo(const int poz, const Locatar& l) = 0;

	/*
	Cauta un locatar in lista
	param ap : apartamentul locatarului vcare se cauta (int)
	param nume : numele locatarului care se cauta (string)
	return : exceptie daca s-a gasit locatarul, pointer la finalul listei altfel
	*/
	virtual const Locatar& find_locatar_repo(int ap, const string& nume) = 0;


	/*
	* Modifica un locatar din lista
	* param poz : pozitia locatarului care va fi modificat
	* param new_l : locatarul cu care va fi inlocuit vechiul locatar
	*/
	virtual void modify(int poz, Locatar new_l) = 0;


	/*
	Verifica daca un locatar exista in lista
	param l : locatarul cautat
	return : true daca nu exista, false daca exista
	*/
	virtual bool exists(const Locatar& l) = 0;

	/*
	* Returneaza lista curenta de locatari
	*/
	virtual const vector<Locatar> get_all_locatari() const noexcept = 0;
};

