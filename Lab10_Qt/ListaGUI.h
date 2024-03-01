#pragma once
#include "Bloc.h"
#include <QtWidgets/Qapplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QListWidget.h>
#include "ListaCRUDGUI.h"
#include "ListaGUIReadOnly.h"

class ListaGUI : public QWidget, public Observer {
private:
	Bloc& ctr;
	void init();
	void connectSignalsSlots();
	void reloadList(const vector<Locatar>& all);

	QBrush bgBrush;

	QLabel* label_ap = new QLabel("Apartament");
	QLabel* label_nume = new QLabel("Nume");
	QLabel* label_nr = new QLabel("Nr de elemente de adaugat");
	QLabel* label_fisier = new QLabel("Numele fisierului");

	QLineEdit* edit_ap;
	QLineEdit* edit_nume;
	QLineEdit* edit_nr;
	QLineEdit* nume_fisier;

	QPushButton* btn_add;
	QPushButton* btn_add_random;
	QPushButton* btn_empty;
	QPushButton* btn_export;
	QPushButton* btn_relaod;
	QPushButton* btn_close;

	QPushButton* btnTableWindow;
	QPushButton* btnDrawWindow;


	QListWidget* list;


public:
	ListaGUI(Bloc& ctr) : ctr{ ctr }
	{
		init();
		connectSignalsSlots();
		reloadList(ctr.get_all_lista_notificare_service().get_all_lista_notificare());
	}

	void update() override
	{
		reloadList(ctr.get_all_lista_notificare_service().get_all_lista_notificare());
	}

	~ListaGUI()
	{
		ctr.remove_observer(this);
	}

	void add_lista();

	void add_random();

	void goleste_lista();

	void export_lista();
};
