
#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;

class Locatar {
	std::string nume;
	std::string tip_ap;
	int apartament;
	int suprafata;

public:
	Locatar(int ap, const string nume, int suprafata, const string tip_ap) :nume{ nume }, tip_ap{ tip_ap }, suprafata{ suprafata }, apartament{ ap } {}

	Locatar() = default;
	/*
	Copy constructor
	*/
	Locatar(const Locatar& ot)
	{
		apartament = ot.apartament;
		suprafata = ot.suprafata;
		nume = ot.nume;
		tip_ap = ot.tip_ap;
		cout << "Copy constructor called!\n";
	}

	/*
	* Returneaza numele unui locatar
	*/
	string get_nume() const {
		return nume;
	}

	/*
	* Returneaza tipul unui apartament
	*/
	string get_tip() const {
		return tip_ap;
	}

	/*
	* Returneaza apartamentul unui locatar
	*/
	int get_ap() const noexcept {
		return apartament;
	}

	/*
	* Returneaza suprafata unui apartament
	*/
	int get_suprafata() const noexcept {
		return suprafata;
	}
};

/*
*Compara doi locatari dupa tip si suprafata.
* @return true daca primul locatar e mai mare decat al doilea.
*/
bool cmp_tip_suprafata(const Locatar& l1, const Locatar& l2) noexcept;

/*
*Compara doi locatari dupa nume.
* @return true daca primul locatar e mai mare decat al doilea
*/
bool cmp_nume(const Locatar& l1, const Locatar& l2) noexcept;

/*
*Compara doi locatari dupa suprafata.
* @return true daca primul locatar e mai mare decat al doilea
*/
bool cmp_suprafata(const Locatar& l1, const Locatar& l2) noexcept;


void test_create_locatar();
