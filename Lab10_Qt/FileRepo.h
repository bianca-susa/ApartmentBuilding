#pragma once

#include "repo.h"
#include <string>

using std::string;

class FileRepo : public repo
{
private:
	string file_name;

	void load_from_file();
	void save_to_file();

public:
	FileRepo(string file_name) :repo(), file_name{ file_name }
	{
		load_from_file();
	}

	void clear_file();

	void store(const Locatar& l) override
	{
		repo::store(l);
		save_to_file();
	}

	void remove_repo(const int poz) override
	{
		repo::remove_repo(poz);
		save_to_file();
	}

	void insert_repo(const int poz, const Locatar& l) override
	{
		repo::insert_repo(poz, l);
		save_to_file();
	}

	void modify(int poz, Locatar new_l) override
	{
		repo::modify(poz, new_l);
		save_to_file();
	}

	~FileRepo() = default;
};

void test_load_from_file();

void test_save_to_file();
