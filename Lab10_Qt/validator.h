#pragma once
#include <string>
#include "Locatar.h"
#include <vector>

using std::vector;
using std::string;
using std::ostream;

class ValidateException {
	vector<string> msg;

public:
	ValidateException(const vector<string>& errors) : msg{ errors } {}

	string get_err_msg()
	{
		string err_msg;
		for (auto el : msg)
		{
			err_msg.append(el);
		}
		return err_msg;
	}

	friend ostream& operator<<(ostream& out, const ValidateException& ex);
};

ostream& operator<<(ostream& out, const ValidateException& ex);

class Validator {
public:
	void validate(const Locatar& l);
	void validate_ap(const int ap);
	void validate_suprafata(const int suprafata);
	void validate_nume(const string& nume);
	void validate_tip(const string& tip);
};

void test_validator();

