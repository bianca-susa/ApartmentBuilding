#pragma once

#pragma once
#include "Locatar.h"
#include "AbstractRepo.h"

#include <map>
#include <string>
#include <ostream>
#include <vector>

using std::map;
using std::vector;
using std::string;
using std::ostream;

class LabRepo : public AbstractRepo
{
	map<int, Locatar> all;
	float prob;
	int k;
	vector<Locatar> vector_all;

public:
	LabRepo(float prob) : prob{ prob } {
		k = 0;
	}
	LabRepo(const LabRepo& ot) = delete;

	/*
	Salvare locatar in lista
	param l : locatarul de salvat in lista
	*/
	virtual void store(const Locatar& l) override;


	/*
	* Sterge un locatar din lista
	* param poz : pozitia de la care locatarul va fi sters
	*/
	virtual void remove_repo(const int poz) override;

	virtual void insert_repo(const int poz, const Locatar& l) override;

	virtual const Locatar& find_locatar_repo(int ap, const string& nume) override;


	/*
	* Modifica un locatar din lista
	* param poz : pozitia locatarului care va fi modificat
	* param new_l : locatarul cu care va fi inlocuit vechiul locatar
	*/
	virtual void modify(int poz, Locatar new_l) override;

	virtual bool exists(const Locatar& l) override;

	/*
	* Returneaza lista curenta de locatari
	*/
	virtual const vector<Locatar> get_all_locatari() const noexcept override;

};

void test_store_lab();
void test_remove_lab();
void test_modify_lab();

void teste_labrepo();

