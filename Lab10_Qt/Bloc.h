#pragma once

#include "Locatar.h"
#include "repo.h"
#include "AbstractRepo.h"
#include "LabRepo.h"
//#include "ListaNotificare.h"
#include "C:\\Users\\bibis\\source\\repos\\Lab10_Qt\\Lab10_Qt\\ListaNotificare.h"
#include "undo.h"
#include "FileRepo.h"
#include <string>
#include <vector>
#include <iterator>
#include <memory>
#include "DTO.h"
#include <unordered_map>

#include <functional>
#include "validator.h"

using std::vector;
using std::function;
using std::unique_ptr;
using std::unordered_map;

class Bloc : public Observable{
	AbstractRepo& rep;
	Validator& validator;

	ListaNotificare lista;
	vector<unique_ptr<ActiuneUndo>> undo_actions;


public:
	Bloc(AbstractRepo& rep, Validator& validator) noexcept : rep{ rep }, validator{ validator } {}

	Bloc(const repo& ot) = delete;

	/*
	Returneaza lista curenta de locatari
	*/
	const vector<Locatar> get_all() noexcept {
		return rep.get_all_locatari();
	}

	/*
	Adauga un nou locatar
	param ap : apartamentul locatarului
	param nume : numele locatarului
	param suprafata : suprafata apartamentului
	param tip_ap : tipul apartamentului
	*/
	void add_locatar(int ap, const string& nume, int suprafata, const string& tip_ap);


	/*
	* Sterge un locatar din lista
	* param ap : apartamentul locatarului care va fi sters
	* param nume : numele locatarului care va fi sters
	*
	* return : 1, daca locatarul a fost sters cu succes, 0 daca nu exista in lista
	*/
	void delete_locatar(int ap, const string& nume);


	/*
	* Cauta un locatar in lista
	* param ap : apartamentul locatarului
	* param nume : numele locatarului
	*
	* return : 1, daca locatarul a fost gasit, 0 daca nu exista in lista
	*/
	const int find_locatar(int ap, const string& nume);

	//const int find_locatar_lista_notificare(int ap, const string& nume);


	/*
	* Modifica un locatar din lista
	* param ap : apartamentul locatarului care va fi modificat
	* param nume : numele locatarului care va fi modificat
	* param new_ap : noul apartament
	* param new_nume : noul nume
	* param new_suprafata : noua suprafata
	* param new_tip : noul tip
	*
	* return : 1, daca locatarul a fost modificat cu succes, 0 daca nu exista in lista
	*/
	void modify_locatar(int ap, const string& nume, int new_ap, const string& new_nume, int suprafata, const string& tip_ap);

	/*
	* Filtreaza lista de locatar dupa suprafata data
	* param suprafata: suprafata data
	*
	* return : lista filtrata
	*/
	void filter_suprafata(const int suprafata, vector<Locatar>& filtered_list);

	/*
	* Filtreaza lista de locatar dupa tip dat
	* param tip: tip dat
	*
	* return : lista filtrata
	*/
	void filter_tip(const string& tip, vector<Locatar>& filtered_list);

	/*
	* Sorteaza locatari dupa nume.
	* return lista sortata dupa nume
	* return type: vector de Locatari
	*/
	vector<Locatar> sort_nume_service();

	/*
	* Sorteaza locatari dupa suprafata.
	* return lista sortata dupa suprafata
	* return type: vector de Locatari
	*/
	vector<Locatar> sort_suprafata_service();

	/*
	* Sorteaza locatari dupa tip si suprafata.
	* return lista sortata dupa tip si suprafata
	* return type: vector de Locatar
	*/
	vector<Locatar> sort_tip_suprafata_service();

	const Locatar& find_locatar_srv(const int ap, const string& nume, vector<Locatar> list);

	const Locatar& find_locatar_srv_1(const int ap, const string& nume, vector<Locatar> list);

	/*
	* Adauga un locatar in lista
	* @param l: locatar care se adauga (Locatar)
	*
	* post: locatarul va fi adaugat in lista
	*/
	void add_locatar_to_lista_service(const int ap, const string& nume);
	/*
	* Elimina toti locatarii din lista
	* post: lista este goala
	*/
	void empty_lista_service();
	/*
	* Adauga un numar random de locatari in lista
	*
	* @param locatari: locatarii din care se alege (vector<Locatar>)
	* @param nr: cati locatari se adauga (int)
	*
	* post: locatarii sunt adaugati in lista curenta
	*/
	int add_random_service(int nr);

	void export_lista_service(const string file_name);

	void undo();

	unordered_map<string, DTO> raport();

	/*
	* Returneaza un vector care contine toti locatarii din lista
	*/
	ListaNotificare& get_all_lista_notificare_service();
};

void test_add();
void test_delete();
void test_find();
void test_modify_locatar();
void test_filter_suprafata();
void test_filter_tip();
void test_sort_nume();
void test_sort_suprafata();
void test_sort_tip_suprafata();
void test_undo();

void test_add_lista();
void test_empty_lista();
void test_add_random();
void test_export();

void teste_bloc();