 #include <fstream>
#include "FileRepo.h"
#include <vector>
#include <sstream>
#include <assert.h>

using std::ifstream;
using std::ofstream;
using std::stringstream;

void FileRepo::load_from_file()
{
	ifstream fin(file_name);

	if (!fin.is_open())
		throw RepoException("Fisierul nu se poate deschide!");

	string line;

	if (fin.peek() == EOF) return;

	while (!fin.eof())
	{
		string atribute;
		vector<string> atr;
		getline(fin, line);

		stringstream ss(line);
		while (getline(ss, atribute, ','))
		{
			atr.push_back(atribute);
		}

		if (atr.empty()) break;

		int ap = stoi(atr[0]);
		std::string nume = atr[1];
		int suprafata = stoi(atr[2]);
		//std::string tip = atr[3];
		atr[3].erase(std::remove(atr[3].begin(), atr[3].end(), '\n'), atr[3].end());
		std::string tip = atr[3];

		const Locatar l{ ap,nume,suprafata,tip };
		repo::store(l);
	}

	fin.close();
}

void FileRepo::save_to_file()
{
	ofstream fout(file_name);

	for (const Locatar& l : get_all_locatari())
		fout << l.get_ap() << ',' << l.get_nume() << ',' << l.get_suprafata() << ',' << l.get_tip() << '\n';

	fout.close();
}

void FileRepo::clear_file()
{
	ofstream fout;

	fout.open(file_name, ofstream::out | ofstream::trunc);

	fout.close();
}

void test_load_from_file()
{
	try
	{
		FileRepo rep{ "a.txt" }; assert(false);
	}
	catch (RepoException& ex)
	{
		assert(true);
	}

	FileRepo repo{ "testfile.csv" };

	assert(repo.get_all_locatari()[0].get_ap() == 1);
	assert(repo.get_all_locatari()[0].get_nume() == "Pop Ion");
	assert(repo.get_all_locatari()[0].get_suprafata() == 1000);
	assert(repo.get_all_locatari()[0].get_tip() == "2 camere");
}

void test_save_to_file()
{
	FileRepo repo{ "testfile1.csv" };

	Locatar l{ 1, "Popescu Ion", 1500, "studio" };

	repo.store(l);

	assert(repo.get_all_locatari()[0].get_ap() == 1);
	assert(repo.get_all_locatari()[0].get_nume() == "Popescu Ion");
	assert(repo.get_all_locatari()[0].get_suprafata() == 1500);
	assert(repo.get_all_locatari()[0].get_tip() == "studio");

	repo.modify(0, { 2, "Popescu Vasile", 2000, "3 camere" });

	assert(repo.get_all_locatari()[0].get_ap() == 2);
	assert(repo.get_all_locatari()[0].get_nume() == "Popescu Vasile");
	assert(repo.get_all_locatari()[0].get_suprafata() == 2000);
	assert(repo.get_all_locatari()[0].get_tip() == "3 camere");

	Locatar l1{ 1, "Popescu Ionel", 1500, "studio" };

	repo.store(l1);

	assert(repo.get_all_locatari()[1].get_ap() == 1);
	assert(repo.get_all_locatari()[1].get_nume() == "Popescu Ionel");
	assert(repo.get_all_locatari()[1].get_suprafata() == 1500);
	assert(repo.get_all_locatari()[1].get_tip() == "studio");

	Locatar l2{ 3, "Popescu Alina", 1500, "studio" };

	repo.insert_repo(1, l2);

	assert(repo.get_all_locatari()[1].get_ap() == 3);
	assert(repo.get_all_locatari()[1].get_nume() == "Popescu Alina");
	assert(repo.get_all_locatari()[1].get_suprafata() == 1500);
	assert(repo.get_all_locatari()[1].get_tip() == "studio");

	repo.remove_repo(0);
	assert(repo.get_all_locatari().size() == 2);
	repo.clear_file();
}