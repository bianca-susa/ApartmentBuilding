#include "LabRepo.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <assert.h>
#include <random>
#include "repo.h"

using std::pair;
using std::ostream;
using std::stringstream;
using std::vector;

bool LabRepo::exists(const Locatar& l) {
	try {
		find_locatar_repo(l.get_ap(), l.get_nume());
		return true;
	}
	catch (RepoException) {
		return false;
	}
}

void LabRepo::store(const Locatar& l)
{
	float nr = (rand() % 10 + 1) / 10.0; cout << nr << "\n";
	if (nr < prob)
		throw RepoException("Exceptie!");
	else
	{
		k++;
		all[k] = l;
	}
	/*vector<Locatar> all_locatari = get_all_locatari();
	if (exists(l))
	{
		throw LabRepoException("Locatarul exista deja!");
	}
	all_locatari.push_back(l);*/

}

void LabRepo::remove_repo(const int poz)
{
	/*vector<Locatar> all_locatari = get_all_locatari();
	if (poz == -1)
		throw LabRepoException("Locatarul nu exista!");
	vector<Locatar>::iterator it;
	it = all_locatari.begin() + poz;
	all_locatari.erase(it);*/

	float nr = (rand() % 10 + 1) / 10.0; cout << nr << "\n";
	if (nr < prob)
		throw RepoException("Exceptie!");
	else
	{
		//all.erase(poz);
		auto it = all.find(poz + 1);
		if (it != all.end())
			all.erase(it);
	}

}

void LabRepo::insert_repo(const int poz, const Locatar& l)
{
	vector<Locatar> all_locatari = get_all_locatari();
	all_locatari.insert(all_locatari.begin() + poz, l);

	all.clear();
	for (auto l : all_locatari)
	{
		store(l);
	}
	//all.insert({ poz, l });
}


const Locatar& LabRepo::find_locatar_repo(int ap, const string& nume)
{
	/*for (int i = 0; i < this->all_locatari.size(); i++)
	{
		if (all_locatari[i].get_ap() == ap && all_locatari[i].get_nume() == nume)
			return i;
	}
	return -1;*/
	//float nr = (rand() % 10 + 1) / 10.0; cout << nr << "\n";
	//if (nr < prob)
		//throw RepoException("Exceptie!");
	//else
	//{
	vector<Locatar> all_locatari = get_all_locatari();
	vector<Locatar>::iterator f = std::find_if(all_locatari.begin(), all_locatari.end(),
		[=](const Locatar& l) {
			return l.get_ap() == ap && l.get_nume() == nume;
		});

	if (f != all_locatari.end())
		return (*f);
	else
		throw RepoException("Locatarul exista deja!");
}
//}}


//const Locatar& repo::find_locatar_repo1(int ap, const string& nume)
//{
//	/*for (int i = 0; i < this->all_locatari.size(); i++)
//	{
//		if (all_locatari[i].get_ap() == ap && all_locatari[i].get_nume() == nume)
//			return i;
//	}
//	return -1;*/
//	vector<Locatar>::iterator f = std::find_if(this->all_locatari.begin(), this->all_locatari.end(),
//		[=](const Locatar& l) {
//			return l.get_ap() == ap && l.get_nume() == nume;
//		});
//
//	if (f != this->all_locatari.end())
//		throw RepoException("Locatarul nu exista!");
//	else
//		return (*f);
//}

//const int repo::find_poz(int ap, const string& nume)
//{
//	int iterator{ -1 }, pos{ -1 };
//	for (const auto& loc : all_locatari)
//	{
//		iterator += 1;
//		if (loc.get_ap() == ap && loc.get_nume() == nume) {
//			pos = iterator;
//		}
//	}
//
//	if (pos == -1)
//		throw RepoException("Locatarul nu exista!");
//	return pos;
//}

void LabRepo::modify(int poz, Locatar new_l)
{
	/*vector<Locatar> all_locatari = get_all_locatari();
	if (poz == -1)
		throw LabRepoException("Locatarul nu exista!");
	all_locatari[poz] = new_l;*/

	float nr = (rand() % 10 + 1) / 10.0; cout << nr << "\n";
	if (nr < prob)
		throw RepoException("Exceptie!");
	else
	{
		all.erase(poz + 1);
		all.insert({ poz, new_l });
	}
}

const vector<Locatar> LabRepo::get_all_locatari() const noexcept
{
	vector<Locatar> v;
	for (auto l : all)
		v.push_back(l.second);
	return v;
}


void test_store_lab()
{
	LabRepo rep{ -1 };

	assert(rep.get_all_locatari().size() == 0);

	Locatar l1{ 2, "Popescu Ion", 100, "penthouse" };
	rep.store(l1);

	assert(rep.get_all_locatari().size() == 1);
	assert(rep.exists(l1) == true);

	Locatar l2{ 2, "Popescu Gheorghe", 20, "studio" };
	assert(rep.exists(l2) == false);
	rep.store(l2);

	assert(rep.get_all_locatari().size() == 2);

	Locatar l3{ 2, "Pop George", 20, "studio" };
	rep.insert_repo(1, l3);

	assert(rep.get_all_locatari().size() == 3);

	assert(rep.get_all_locatari()[1].get_ap() == 2);
	assert(rep.get_all_locatari()[1].get_nume() == "Pop George");
	assert(rep.get_all_locatari()[1].get_suprafata() == 20);
	assert(rep.get_all_locatari()[1].get_tip() == "studio");

	LabRepo rep1{ 10 };
	try
	{
		Locatar l4{ 2, "Popescu Gheorghe", 20, "studio" };
		rep1.store(l4); assert(false);
	}
	catch (RepoException& ex)
	{
		assert(ex.get_err_msg() == "Exceptie!");
	}
}

void test_remove_lab()
{
	LabRepo rep{ -1 };

	assert(rep.get_all_locatari().size() == 0);

	Locatar l1{ 2, "Popescu Ion", 100, "penthouse" };
	rep.store(l1);

	assert(rep.get_all_locatari().size() == 1);

	Locatar l2{ 2, "Popescu Gheorghe", 20, "studio" };
	rep.store(l2);

	assert(rep.get_all_locatari().size() == 2);

	rep.remove_repo(0);

	assert(rep.get_all_locatari().size() == 1);

	LabRepo rep1{ 10 };
	try
	{
		rep1.remove_repo(0); assert(false);
	}
	catch (RepoException& ex)
	{
		assert(ex.get_err_msg() == "Exceptie!");
	}
}

void test_modify_lab()
{
	LabRepo rep{ -1 };

	assert(rep.get_all_locatari().size() == 0);

	Locatar l1{ 2, "Popescu Ion", 100, "penthouse" };
	rep.store(l1);

	assert(rep.get_all_locatari().size() == 1);

	Locatar l2{ 1, "Popescu Gheorghe", 20, "studio" };
	rep.store(l2);

	assert(rep.get_all_locatari().size() == 2);

	assert(rep.get_all_locatari()[0].get_ap() == 2);
	assert(rep.get_all_locatari()[0].get_nume() == "Popescu Ion");
	assert(rep.get_all_locatari()[0].get_suprafata() == 100);
	assert(rep.get_all_locatari()[0].get_tip() == "penthouse");

	Locatar new_l{ 3, "Pop Vasile", 25, "studio" };

	rep.modify(0, new_l);
	assert(rep.get_all_locatari().size() == 2);

	assert(rep.get_all_locatari()[0].get_ap() == 3);
	assert(rep.get_all_locatari()[0].get_nume() == "Pop Vasile");
	assert(rep.get_all_locatari()[0].get_suprafata() == 25);
	assert(rep.get_all_locatari()[0].get_tip() == "studio");

	LabRepo rep1{ 10 };
	try
	{
		Locatar new_l{ 3, "Pop Vasile", 25, "studio" };
		rep1.modify(0, new_l); assert(false);
	}
	catch (RepoException& ex)
	{
		assert(ex.get_err_msg() == "Exceptie!");
	}
}

void teste_labrepo()
{
	//test_create_locatar();
	test_store_lab();
	test_remove_lab();
	test_modify_lab();
}
