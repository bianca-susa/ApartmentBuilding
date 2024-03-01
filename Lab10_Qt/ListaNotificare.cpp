#include "ListaNotificare.h"
#include <fstream>
using std::shuffle;
using std::ofstream;

void ListaNotificare::add_locatar_to_lista(const Locatar& l) {
	this->lista_notificare.push_back(l);
	notify();
}

void ListaNotificare::empty_lista() {
	this->lista_notificare.clear();
	notify();
}

void ListaNotificare::add_random(vector<Locatar> locatari, int nr) {
	shuffle(locatari.begin(), locatari.end(), std::default_random_engine(std::random_device{}())); //amesteca vectorul v
	while (lista_notificare.size() < nr && locatari.size() > 0) {
		lista_notificare.push_back(locatari.back());
		locatari.pop_back();
	}
	notify();
}
vector<Locatar>& ListaNotificare::get_all_lista_notificare() {
	return lista_notificare;
}

void ListaNotificare::export_lista(string file_name)
{
	ofstream out(file_name, ofstream::trunc);
	for (const auto& locatar : lista_notificare) {
		out << locatar.get_ap() << "," << locatar.get_nume() << "," << locatar.get_suprafata() << "," << locatar.get_tip() << "\n";
	}
	out.close();
}