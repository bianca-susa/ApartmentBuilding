#pragma once

#include "Locatar.h"
#include <vector>
#include <algorithm>
#include <random>
#include <fstream>
#include "Observer.h"
//#include "Bloc.h"
#include "validator.h"

class Bloc;

using std::vector;

class ListaNotificare : public Observable
{
private:
	vector<Locatar> lista_notificare;
public:

	ListaNotificare() = default;

	/*
	* Adauga un locatar in lista
	* @param l: locatar care se adauga (Locatar)
	*
	* post: locatarul va fi adaugat in lista
	*/
	void add_locatar_to_lista(const Locatar& l);
	/*
	* Elimina toti locatarii din lista
	* post: lista este goala
	*/
	void empty_lista();
	/*
	* Adauga un numar random de locatari in lista
	*
	* @param locatari: locatarii din care se alege (vector<Locatar>)
	* @param nr: cati locatari se adauga (int)
	*
	* post: locatarii sunt adaugati in lista curenta
	*/
	void add_random(vector<Locatar> locatari, int nr);

	void export_lista(string file_name);

	/*
	* Returneaza un vector care contine toti locatarii din lista
	*/
	vector<Locatar>& get_all_lista_notificare();
};
