#include "repo.h"
#include <iostream>
#include <sstream>
#include <assert.h>

using std::ostream;
using std::stringstream;

bool repo::exists(const Locatar& l) {
	try {
		find_locatar_repo(l.get_ap(), l.get_nume());
		return true;
	}
	catch (RepoException) {
		return false;
	}
}

void repo::store(const Locatar& l)
{
	if (exists(l))
	{
		throw RepoException("Locatarul exista deja!");
	}
	all_locatari.push_back(l);
}

void repo::remove_repo(const int poz)
{
	if (poz == -1)
		throw RepoException("Locatarul nu exista!");
	vector<Locatar>::iterator it;
	it = all_locatari.begin() + poz;
	all_locatari.erase(it);
}

void repo::insert_repo(const int poz, const Locatar& l)
{
	all_locatari.insert(all_locatari.begin() + poz, l);
}

const Locatar& repo::find_locatar_repo(int ap, const string& nume)
{
	/*for (int i = 0; i < this->all_locatari.size(); i++)
	{
		if (all_locatari[i].get_ap() == ap && all_locatari[i].get_nume() == nume)
			return i;
	}
	return -1;*/
	vector<Locatar>::iterator f = std::find_if(all_locatari.begin(), all_locatari.end(),
		[=](const Locatar& l) {
			return l.get_ap() == ap && l.get_nume() == nume;
		});

	if (f != all_locatari.end())
		return (*f);
	else
		throw RepoException("Locatarul exista deja!");
}

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

void repo::modify(int poz, Locatar new_l)
{
	if (poz == -1)
		throw RepoException("Locatarul nu exista!");
	all_locatari[poz] = new_l;
}

const vector<Locatar> repo::get_all_locatari() const noexcept
{
	return all_locatari;
}


void test_store()
{
	repo rep;

	assert(rep.get_all_locatari().size() == 0);

	Locatar l1{ 2, "Popescu Ion", 100, "penthouse" };
	rep.store(l1);

	assert(rep.get_all_locatari().size() == 1);

	Locatar l2{ 2, "Popescu Gheorghe", 20, "studio" };
	rep.store(l2);

	assert(rep.get_all_locatari().size() == 2);

	try
	{
		Locatar l3{ 2, "Popescu Gheorghe", 20, "studio" };
		rep.store(l3); assert(false);
	}
	catch (RepoException& ex)
	{
		assert(ex.get_err_msg() == "Locatarul exista deja!");
	}
}
void test_remove()
{
	repo rep;

	assert(rep.get_all_locatari().size() == 0);

	Locatar l1{ 2, "Popescu Ion", 100, "penthouse" };
	rep.store(l1);

	assert(rep.get_all_locatari().size() == 1);

	Locatar l2{ 2, "Popescu Gheorghe", 20, "studio" };
	rep.store(l2);

	assert(rep.get_all_locatari().size() == 2);

	rep.remove_repo(0);

	assert(rep.get_all_locatari().size() == 1);
}

void test_modify()
{
	repo rep;

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
}

void teste_repo()
{
	test_create_locatar();
	test_store();
	test_remove();
	test_modify();
}