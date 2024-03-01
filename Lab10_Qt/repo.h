#pragma once
#include "Locatar.h"
#include "AbstractRepo.h"

#include <vector>
#include <string>
#include <ostream>

using std::vector;
using std::string;
using std::ostream;



class RepoException
{
	string error_msg;

public:
	RepoException(string error_msg) : error_msg{ error_msg } {};

	string get_err_msg()
	{
		return this->error_msg;
	}
};

class repo : public AbstractRepo
{
	vector<Locatar> all_locatari;

public:
	repo() = default;
	repo(const repo& ot) = delete;

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

void test_store();
void test_remove();
void test_modify();

void teste_repo();

