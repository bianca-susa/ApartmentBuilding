#include "Bloc.h"
#include <algorithm>
#include <assert.h>
#include <sstream>

using std::ostream;
using std::stringstream;

void Bloc::add_locatar(int apartament, const string& nume, int suprafata, const string& tip_ap)
{
	Locatar l{ apartament, nume, suprafata, tip_ap };
	validator.validate(l);
	rep.store(l);
	undo_actions.push_back(std::make_unique<UndoAdauga>(this->rep));
	notify();
}

void Bloc::delete_locatar(int apartament, const string& nume)
{

	int poz = find_locatar(apartament, nume);
	validator.validate_ap(apartament);
	validator.validate_nume(nume);

	if (poz >= 0)
	{
		Locatar l = get_all()[poz];
		undo_actions.push_back(std::make_unique<UndoSterge>(l, poz, this->rep));
		notify();
	}

	rep.remove_repo(poz);

}

const int Bloc::find_locatar(int ap, const string& nume)
{
	validator.validate_ap(ap);
	validator.validate_nume(nume);
	for (int i = 0; i < size(rep.get_all_locatari()); i++)
	{
		if (rep.get_all_locatari()[i].get_ap() == ap && rep.get_all_locatari()[i].get_nume() == nume)
			return i;
	}
	return -1;
}


void Bloc::modify_locatar(int ap, const string& nume, int new_ap, const string& new_nume, int suprafata, const string& tip_ap)
{
	const int poz = find_locatar(ap, nume);
	Locatar new_l{ new_ap, new_nume, suprafata, tip_ap };
	validator.validate(new_l);

	if (poz >= 0)
	{
		Locatar l = get_all()[poz];
		undo_actions.push_back(std::make_unique<UndoModifica>(l, poz, this->rep)); 
		notify();
	}

	rep.modify(poz, new_l);
}

void Bloc::filter_suprafata(const int suprafata, vector<Locatar>& filtered_list)
{
	validator.validate_suprafata(suprafata);
	const vector<Locatar>& all_locatari = get_all();
	std::copy_if(all_locatari.begin(), all_locatari.end(), back_inserter(filtered_list),
		[suprafata](const Locatar& l) {
			return l.get_suprafata() == suprafata;
		});

}


void Bloc::filter_tip(const string& tip, vector<Locatar>& filtered_list)
{
	validator.validate_tip(tip);
	const vector<Locatar>& all_locatari = get_all();
	std::copy_if(all_locatari.begin(), all_locatari.end(), back_inserter(filtered_list),
		[tip](const Locatar& l) {
			return l.get_tip() == tip;
		});
}

vector<Locatar> Bloc::sort_nume_service() {
	vector<Locatar> sorted{ rep.get_all_locatari() };
	sort(sorted.begin(), sorted.end(), cmp_nume);
	return sorted;
}

vector<Locatar> Bloc::sort_suprafata_service() {
	vector<Locatar> sorted{ rep.get_all_locatari() };
	sort(sorted.begin(), sorted.end(), cmp_suprafata);
	return sorted;
}

vector<Locatar> Bloc::sort_tip_suprafata_service() {
	vector<Locatar> sorted{ rep.get_all_locatari() };
	sort(sorted.begin(), sorted.end(), cmp_tip_suprafata);
	return sorted;
}


void Bloc::add_locatar_to_lista_service(const int ap, const string& nume)
{
	validator.validate_ap(ap);
	validator.validate_nume(nume);

	int poz = find_locatar(ap, nume);
	if (poz != -1)
		lista.add_locatar_to_lista(get_all()[poz]);
	else throw RepoException("Locatarul nu exista!");
}


void Bloc::empty_lista_service()
{
	lista.empty_lista();
}

int Bloc::add_random_service(int nr)
{
	lista.add_random(get_all(), nr);
	return lista.get_all_lista_notificare().size();
}

void Bloc::export_lista_service(const string file_name)
{
	lista.export_lista(file_name);
}

void Bloc::undo()
{
	if (undo_actions.empty())
		throw RepoException("Nu se mai poate face undo!");
	undo_actions.back()->doUndo();
	undo_actions.pop_back();
}

unordered_map<string, DTO> Bloc::raport() {
	unordered_map<string, DTO> map;
	for (auto i : get_all())
	{
		vector<Locatar> f;
		filter_tip(i.get_tip(), f);

		DTO d{ i.get_tip(), int(f.size()) };
		map[i.get_tip()] = d;

	}
	return map;
}


ListaNotificare& Bloc::get_all_lista_notificare_service()
{
	return this->lista;
}


void test_add()
{
	repo rep;
	Validator v;
	Bloc ctr{ rep , v };

	ctr.add_locatar(2, "Popescu Ion", 11, "studio");
	assert(ctr.get_all().size() == 1);

	ctr.add_locatar(1, "Popescu Vasile", 50, "2 camere");
	assert(ctr.get_all().size() == 2);

	try
	{
		ctr.add_locatar(-5, "", 123, "garsoniera");  assert(false);
	}
	catch (const ValidateException& ex)
	{
		std::stringstream sout;
		sout << ex;
		const auto mesaj = sout.str();
		assert(mesaj.find("invalid") >= 0);
		assert(mesaj.find("Apartament") >= 0);
		assert(mesaj.find("Nume") >= 0);
	}
}


void test_delete()
{
	repo rep;
	Validator v;
	Bloc ctr{ rep , v };

	ctr.add_locatar(2, "Popescu Ion", 11, "studio");
	assert(ctr.get_all().size() == 1);

	ctr.add_locatar(1, "Popescu Vasile", 50, "2 camere");
	assert(ctr.get_all().size() == 2);

	ctr.delete_locatar(1, "Popescu Vasile");
	assert(ctr.get_all().size() == 1);

	try
	{
		ctr.delete_locatar(1, "Popescu Vasile"); assert(false);
	}
	catch (RepoException& ex)
	{
		assert(ex.get_err_msg() == "Locatarul nu exista!");
	}

	try
	{
		ctr.delete_locatar(-2, "Popescu Ion"); assert(false);
	}
	catch (const ValidateException& ex)
	{
		std::stringstream sout;
		sout << ex;
		const auto mesaj = sout.str();
		assert(mesaj.find("invalid") >= 0);
		assert(mesaj.find("Apartament") >= 0);
	}

	try
	{
		ctr.delete_locatar(2, ""); assert(false);
	}
	catch (const ValidateException& ex)
	{
		std::stringstream sout;
		sout << ex;
		const auto mesaj = sout.str();
		assert(mesaj.find("invalid") >= 0);
		assert(mesaj.find("Nume") >= 0);
	}

}

void test_find()
{
	repo rep;
	Validator v;
	Bloc ctr{ rep , v };

	ctr.add_locatar(2, "Popescu Ion", 11, "studio");
	assert(ctr.get_all().size() == 1);

	ctr.add_locatar(1, "Popescu Vasile", 50, "2 camere");
	assert(ctr.get_all().size() == 2);

	int poz = ctr.find_locatar(2, "Popescu Ion");
	assert(poz == 0);

	poz = ctr.find_locatar(1, "Popescu Vasile");
	assert(1);

	poz = ctr.find_locatar(2, "Popescu Gheorghe");
	assert(poz == -1);
}

void test_modify_locatar()
{
	repo rep;
	Validator v;
	Bloc ctr{ rep , v };

	ctr.add_locatar(2, "Popescu Ion", 11, "studio");
	assert(ctr.get_all().size() == 1);

	ctr.add_locatar(1, "Popescu Vasile", 50, "2 camere");
	assert(ctr.get_all().size() == 2);

	assert(ctr.get_all()[1].get_ap() == 1);
	assert(ctr.get_all()[1].get_nume() == "Popescu Vasile");
	assert(ctr.get_all()[1].get_suprafata() == 50);
	assert(ctr.get_all()[1].get_tip() == "2 camere");

	ctr.modify_locatar(1, "Popescu Vasile", 3, "Pop Gheorghe", 100, "3 camere");

	assert(ctr.get_all()[1].get_ap() == 3);
	assert(ctr.get_all()[1].get_nume() == "Pop Gheorghe");
	assert(ctr.get_all()[1].get_suprafata() == 100);
	assert(ctr.get_all()[1].get_tip() == "3 camere");


	try
	{
		ctr.modify_locatar(2, "Popescu Ion", 3, "Pop Gheorghe", -100, ""); assert(false);
	}
	catch (const ValidateException& ex)
	{
		std::stringstream sout;
		sout << ex;
		const auto mesaj = sout.str();
		assert(mesaj.find("invalid") >= 0);
		assert(mesaj.find("Suprafata") >= 0);
		assert(mesaj.find("Tip") >= 0);
	}

	try
	{
		ctr.modify_locatar(10, "Popescu Alina", 3, "Pop Gheorghe", 100, "tip1"); assert(false);
	}
	catch (RepoException& ex)
	{
		assert(ex.get_err_msg() == "Locatarul nu exista!");
	}
}

void test_filter_suprafata()
{
	repo rep;
	Validator v;
	Bloc ctr{ rep , v };

	ctr.add_locatar(2, "Popescu Ion", 11, "studio");
	assert(ctr.get_all().size() == 1);

	ctr.add_locatar(1, "Popescu Vasile", 50, "2 camere");
	assert(ctr.get_all().size() == 2);

	ctr.add_locatar(3, "Popescu Gheorghe", 50, "studio");
	assert(ctr.get_all().size() == 3);

	ctr.add_locatar(4, "Popescu Marcel", 50, "2 camere");
	assert(ctr.get_all().size() == 4);

	vector<Locatar> filtered_list;
	ctr.filter_suprafata(50, filtered_list);
	assert(filtered_list.size() == 3);

	assert(filtered_list[0].get_ap() == 1);
	assert(filtered_list[0].get_nume() == "Popescu Vasile");
	assert(filtered_list[0].get_suprafata() == 50);
	assert(filtered_list[0].get_tip() == "2 camere");

	vector<Locatar> filtered_list1;
	ctr.filter_suprafata(11, filtered_list1);
	assert(filtered_list1.size() == 1);

	try
	{
		vector<Locatar> filtered_list1;
		ctr.filter_suprafata(-11, filtered_list1); assert(false);
	}
	catch (const ValidateException& ex)
	{
		std::stringstream sout;
		sout << ex;
		const auto mesaj = sout.str();
		assert(mesaj.find("invalida") >= 0);
		assert(mesaj.find("Suprafata") >= 0);
	}
}

void test_filter_tip()
{
	repo rep;
	Validator v;
	Bloc ctr{ rep , v };

	ctr.add_locatar(2, "Popescu Ion", 11, "studio");
	assert(ctr.get_all().size() == 1);

	ctr.add_locatar(1, "Popescu Vasile", 50, "2 camere");
	assert(ctr.get_all().size() == 2);

	ctr.add_locatar(3, "Popescu Gheorghe", 50, "studio");
	assert(ctr.get_all().size() == 3);

	ctr.add_locatar(4, "Popescu Marcel", 50, "2 camere");
	assert(ctr.get_all().size() == 4);

	vector<Locatar> filtered_list;
	ctr.filter_tip("studio", filtered_list);
	assert(filtered_list.size() == 2);

	assert(filtered_list[0].get_ap() == 2);
	assert(filtered_list[0].get_nume() == "Popescu Ion");
	assert(filtered_list[0].get_suprafata() == 11);
	assert(filtered_list[0].get_tip() == "studio");

	vector<Locatar> filtered_list1;
	ctr.filter_tip("2 camere", filtered_list1);
	assert(filtered_list1.size() == 2);

	try
	{
		vector<Locatar> filtered_list1;
		ctr.filter_tip("", filtered_list1); assert(false);
	}
	catch (const ValidateException& ex)
	{
		std::stringstream sout;
		sout << ex;
		const auto mesaj = sout.str();
		assert(mesaj.find("invalid") >= 0);
		assert(mesaj.find("Tip") >= 0);
	}
}

void test_sort_nume()
{
	repo rep;
	Validator v;
	Bloc ctr{ rep , v };

	ctr.add_locatar(2, "Popescu Ion", 11, "studio");
	assert(ctr.get_all().size() == 1);

	ctr.add_locatar(1, "Popescu Vasile", 50, "2 camere");
	assert(ctr.get_all().size() == 2);

	ctr.add_locatar(3, "Popescu Ionel", 11, "studio");
	assert(ctr.get_all().size() == 3);

	ctr.add_locatar(4, "Popescu Marian", 50, "2 camere");
	assert(ctr.get_all().size() == 4);

	ctr.add_locatar(5, "Popescu Alina", 11, "studio");
	assert(ctr.get_all().size() == 5);

	ctr.add_locatar(6, "Popescu George", 12, "2 camere");
	assert(ctr.get_all().size() == 6);

	vector<Locatar> sorted = ctr.sort_nume_service();
	assert(sorted.size() == 6);

	assert(sorted[5].get_ap() == 1);
	assert(sorted[5].get_nume() == "Popescu Vasile");
	assert(sorted[5].get_suprafata() == 50);
	assert(sorted[5].get_tip() == "2 camere");

	assert(sorted[0].get_ap() == 5);
	assert(sorted[0].get_nume() == "Popescu Alina");
	assert(sorted[0].get_suprafata() == 11);
	assert(sorted[0].get_tip() == "studio");
}

void test_sort_suprafata()
{
	repo rep;
	Validator v;
	Bloc ctr{ rep , v };

	ctr.add_locatar(2, "Popescu Ion", 11, "studio");
	assert(ctr.get_all().size() == 1);

	ctr.add_locatar(1, "Popescu Vasile", 60, "2 camere");
	assert(ctr.get_all().size() == 2);

	ctr.add_locatar(3, "Popescu Ionel", 11, "studio");
	assert(ctr.get_all().size() == 3);

	ctr.add_locatar(4, "Popescu Marian", 50, "2 camere");
	assert(ctr.get_all().size() == 4);

	ctr.add_locatar(5, "Popescu Alina", 10, "studio");
	assert(ctr.get_all().size() == 5);

	ctr.add_locatar(6, "Popescu George", 12, "2 camere");
	assert(ctr.get_all().size() == 6);

	vector<Locatar> sorted = ctr.sort_suprafata_service();
	assert(sorted.size() == 6);

	assert(sorted[5].get_ap() == 1);
	assert(sorted[5].get_nume() == "Popescu Vasile");
	assert(sorted[5].get_suprafata() == 60);
	assert(sorted[5].get_tip() == "2 camere");

	assert(sorted[0].get_ap() == 5);
	assert(sorted[0].get_nume() == "Popescu Alina");
	assert(sorted[0].get_suprafata() == 10);
	assert(sorted[0].get_tip() == "studio");
}

void test_sort_tip_suprafata()
{
	repo rep;
	Validator v;
	Bloc ctr{ rep , v };

	ctr.add_locatar(2, "Popescu Ion", 15, "studio");
	assert(ctr.get_all().size() == 1);

	ctr.add_locatar(1, "Popescu Vasile", 50, "2 camere");
	assert(ctr.get_all().size() == 2);

	ctr.add_locatar(3, "Popescu Ionel", 20, "studio");
	assert(ctr.get_all().size() == 3);

	ctr.add_locatar(4, "Popescu Marian", 50, "2 camere");
	assert(ctr.get_all().size() == 4);

	ctr.add_locatar(5, "Popescu Alina", 11, "studio");
	assert(ctr.get_all().size() == 5);

	ctr.add_locatar(6, "Popescu George", 12, "2 camere");
	assert(ctr.get_all().size() == 6);

	vector<Locatar> sorted = ctr.sort_tip_suprafata_service();
	assert(sorted.size() == 6);

	assert(sorted[5].get_ap() == 3);
	assert(sorted[5].get_nume() == "Popescu Ionel");
	assert(sorted[5].get_suprafata() == 20);
	assert(sorted[5].get_tip() == "studio");

	assert(sorted[0].get_ap() == 6);
	assert(sorted[0].get_nume() == "Popescu George");
	assert(sorted[0].get_suprafata() == 12);
	assert(sorted[0].get_tip() == "2 camere");
}

/*
void test_add_lista()
{
	repo rep;
	Validator v;
	Bloc ctr{ rep , v };

	ctr.add_locatar(2, "Popescu Ion", 15, "studio");
	assert(ctr.get_all().size() == 1);

	ctr.add_locatar(1, "Popescu Vasile", 50, "2 camere");
	assert(ctr.get_all().size() == 2);

	ctr.add_locatar(3, "Popescu Ionel", 20, "studio");
	assert(ctr.get_all().size() == 3);

	ctr.add_locatar(4, "Popescu Marian", 50, "2 camere");
	assert(ctr.get_all().size() == 4);

	ctr.add_locatar(5, "Popescu Alina", 11, "studio");
	assert(ctr.get_all().size() == 5);

	ctr.add_locatar(6, "Popescu George", 12, "2 camere");
	assert(ctr.get_all().size() == 6);

	assert(ctr.get_all_lista_notificare_service().size() == 0);
	ctr.add_locatar_to_lista_service(3, "Popescu Ionel");
	assert(ctr.get_all_lista_notificare_service().size() == 1);

	try
	{
		ctr.add_locatar_to_lista_service(-2, "Popescu Ion"); assert(false);
	}
	catch (const ValidateException& ex)
	{
		std::stringstream sout;
		sout << ex;
		const auto mesaj = sout.str();
		assert(mesaj.find("invalid") >= 0);
		assert(mesaj.find("Apartament") >= 0);
	}

	/*try
	{
		ctr.add_locatar_to_lista_service(10, "Popescu Ionel"); assert(false);
	}
	catch (RepoException& e)
	{
		assert(e.get_err_msg() == "Locatarul nu exista!");
	}

	ctr.add_locatar_to_lista_service(5, "Popescu Alina");
	assert(ctr.get_all_lista_notificare_service().size() == 2);*
}

void test_add_random()
{
	repo rep;
	Validator v;
	Bloc ctr{ rep , v };

	ctr.add_locatar(2, "Popescu Ion", 15, "studio");
	assert(ctr.get_all().size() == 1);

	ctr.add_locatar(1, "Popescu Vasile", 50, "2 camere");
	assert(ctr.get_all().size() == 2);

	ctr.add_locatar(3, "Popescu Ionel", 20, "studio");
	assert(ctr.get_all().size() == 3);

	ctr.add_locatar(4, "Popescu Marian", 50, "2 camere");
	assert(ctr.get_all().size() == 4);

	ctr.add_locatar(5, "Popescu Alina", 11, "studio");
	assert(ctr.get_all().size() == 5);

	ctr.add_locatar(6, "Popescu George", 12, "2 camere");
	assert(ctr.get_all().size() == 6);

	assert(ctr.get_all_lista_notificare_service().size() == 0);
	assert(ctr.add_random_service(3) == 3);
	assert(ctr.get_all_lista_notificare_service().size() == 3);

}

void test_empty_lista()
{
	repo rep;
	Validator v;
	Bloc ctr{ rep , v };

	ctr.add_locatar(2, "Popescu Ion", 15, "studio");
	assert(ctr.get_all().size() == 1);

	ctr.add_locatar(1, "Popescu Vasile", 50, "2 camere");
	assert(ctr.get_all().size() == 2);

	ctr.add_locatar(3, "Popescu Ionel", 20, "studio");
	assert(ctr.get_all().size() == 3);

	ctr.add_locatar(4, "Popescu Marian", 50, "2 camere");
	assert(ctr.get_all().size() == 4);

	ctr.add_locatar(5, "Popescu Alina", 11, "studio");
	assert(ctr.get_all().size() == 5);

	ctr.add_locatar(6, "Popescu George", 12, "2 camere");
	assert(ctr.get_all().size() == 6);

	assert(ctr.get_all_lista_notificare_service().size() == 0);
	ctr.add_random_service(3);
	assert(ctr.get_all_lista_notificare_service().size() == 3);

	ctr.empty_lista_service();
	assert(ctr.get_all_lista_notificare_service().size() == 0);
}*/

void test_undo()
{
	repo rep;
	Validator v;
	Bloc ctr{ rep , v };

	ctr.add_locatar(2, "Popescu Ion", 15, "studio");
	assert(ctr.get_all().size() == 1);

	ctr.undo();

	try
	{
		ctr.undo(); assert(false);
	}
	catch (RepoException& ex)
	{
		assert(ex.get_err_msg() == "Nu se mai poate face undo!");
	}

	ctr.add_locatar(2, "Popescu Ion", 15, "studio");
	assert(ctr.get_all().size() == 1);

	ctr.add_locatar(1, "Popescu Vasile", 50, "2 camere");
	assert(ctr.get_all().size() == 2);

	ctr.add_locatar(3, "Popescu Ionel", 20, "studio");
	assert(ctr.get_all().size() == 3);

	ctr.undo();
	assert(ctr.get_all().size() == 2);

	ctr.add_locatar(5, "Popescu Alina", 11, "studio");
	assert(ctr.get_all().size() == 3);

	ctr.add_locatar(6, "Popescu George", 12, "2 camere");
	assert(ctr.get_all().size() == 4);

	ctr.delete_locatar(5, "Popescu Alina");
	assert(ctr.get_all().size() == 3);

	ctr.undo();
	assert(ctr.get_all().size() == 4);

	assert(ctr.get_all()[2].get_ap() == 5);
	assert(ctr.get_all()[2].get_nume() == "Popescu Alina");
	assert(ctr.get_all()[2].get_suprafata() == 11);
	assert(ctr.get_all()[2].get_tip() == "studio");

	ctr.modify_locatar(1, "Popescu Vasile", 3, "Pop Gheorghe", 100, "3 camere");

	assert(ctr.get_all()[1].get_ap() == 3);
	assert(ctr.get_all()[1].get_nume() == "Pop Gheorghe");
	assert(ctr.get_all()[1].get_suprafata() == 100);
	assert(ctr.get_all()[1].get_tip() == "3 camere");

	ctr.undo();
	assert(ctr.get_all()[1].get_ap() == 1);
	assert(ctr.get_all()[1].get_nume() == "Popescu Vasile");
	assert(ctr.get_all()[1].get_suprafata() == 50);
	assert(ctr.get_all()[1].get_tip() == "2 camere");
}

/*
void test_export()
{
	repo rep;
	Validator v;
	Bloc ctr{ rep , v };

	ctr.add_locatar(2, "Popescu Ion", 15, "studio");
	assert(ctr.get_all().size() == 1);

	ctr.add_locatar(1, "Popescu Vasile", 50, "2 camere");
	assert(ctr.get_all().size() == 2);

	ctr.add_locatar(3, "Popescu Ionel", 20, "studio");
	assert(ctr.get_all().size() == 3);

	ctr.add_locatar(4, "Popescu Marian", 50, "2 camere");
	assert(ctr.get_all().size() == 4);

	ctr.add_locatar(5, "Popescu Alina", 11, "studio");
	assert(ctr.get_all().size() == 5);

	ctr.add_locatar(6, "Popescu George", 12, "2 camere");
	assert(ctr.get_all().size() == 6);

	assert(ctr.get_all_lista_notificare_service().size() == 0);
	ctr.add_locatar_to_lista_service(3, "Popescu Ionel");
	assert(ctr.get_all_lista_notificare_service().size() == 1);

	ctr.export_lista_service("testfile2.csv");
}*/

/*
void teste_bloc()
{
	test_add();
	test_delete();
	test_find();
	test_modify_locatar();
	test_validator();
	test_filter_suprafata();
	test_filter_tip();
	test_sort_nume();
	test_sort_suprafata();
	test_sort_tip_suprafata();
	test_undo();

	test_add_lista();
	test_add_random();
	test_empty_lista();
	test_export();

}*/