#include "validator.h"
#include <assert.h>
#include <sstream>

void Validator::validate(const Locatar& l)
{
	vector<string> msg;
	if (l.get_ap() <= 0) msg.push_back("Apartament invalid!");
	if (l.get_suprafata() <= 0) msg.push_back("Suprafata invalida!");
	if (l.get_nume().size() == 0) msg.push_back("Nume invalid!");
	if (l.get_tip().size() == 0) msg.push_back("Tip invalid!");

	if (msg.size() > 0)
		throw ValidateException(msg);
}

void Validator::validate_ap(const int ap)
{
	vector<string> msg;
	if (ap <= 0) msg.push_back("Apartament invalid!");

	if (msg.size() > 0)
		throw ValidateException(msg);
}
void Validator::validate_suprafata(const int suprafata)
{
	vector<string> msg;
	if (suprafata <= 0) msg.push_back("Suprafata invalida!");

	if (msg.size() > 0)
		throw ValidateException(msg);
}
void Validator::validate_nume(const string& nume)
{
	vector<string> msg;
	if (nume.size() == 0) msg.push_back("Nume invalid!");

	if (msg.size() > 0)
		throw ValidateException(msg);
}
void Validator::validate_tip(const string& tip)
{
	vector<string> msg;
	if (tip.size() == 0) msg.push_back("Tip invalid!");

	if (msg.size() > 0)
		throw ValidateException(msg);
}

ostream& operator<<(ostream& out, const ValidateException& ex)
{
	for (const auto& msg : ex.msg)
		out << msg << " ";
	return out;
}

void test_validator()
{
	Validator v;
	Locatar l{ -4, "", 123, "studio" };
	try
	{
		v.validate(l);
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