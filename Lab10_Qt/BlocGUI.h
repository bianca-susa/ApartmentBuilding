#pragma once
#include <QtWidgets/Qapplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <qtableview.h>
#include <QAbstractItemView>
#include <QGroupBox>
#include <QRadioButton>
#include <qstring.h>
#include "Bloc.h"
#include "ListaGUI.h"
#include "ListaGUIReadOnly.h"
#include "FilterGUI.h"
#include "MyModel.h"



class BlocGUI : public QWidget
{
private:
	Bloc& ctr;

	MyTableModel* model;

	QLabel* label_ap = new QLabel{ " Apartament : " };
	QLabel* label_nume = new QLabel{ " Nume : " };
	QLabel* label_suprafata = new QLabel{ " Suprafata : " };
	QLabel* label_tip = new QLabel{ " Tip : " };

	QLabel* label_new_ap = new QLabel{ " Apartament nou : " };
	QLabel* label_new_nume = new QLabel{ " Nume nou : " };
	QLabel* label_new_suprafata = new QLabel{ " Suprafata noua : " };
	QLabel* label_new_tip = new QLabel{ " Tip nou : " };

	//QHBoxLayout* ly_main = new QHBoxLayout;

	QLineEdit* edit_ap;
	QLineEdit* edit_nume;
	QLineEdit* edit_suprafata;
	QLineEdit* edit_tip;

	QLineEdit* edit_new_ap;
	QLineEdit* edit_new_nume;
	QLineEdit* edit_new_suprafata;
	QLineEdit* edit_new_tip;

	QPushButton* btn_add;
	QPushButton* btn_delete;
	QPushButton* btn_modify;
	QPushButton* btn_find;
	QPushButton* btn_close;
	QPushButton* btn_undo;

	QGroupBox* group_box_filter = new QGroupBox("Tip filtrare");

	QRadioButton* radio_filter_tip = new QRadioButton("Filtrare dupa tip");
	QRadioButton* radio_filter_suprafata = new QRadioButton("Filtrare dupa suprafata");
	QPushButton* btn_filter;

	QGroupBox* group_box_sort = new QGroupBox("Tip sortare");

	QRadioButton* radio_sort_nume = new QRadioButton("Sortare dupa nume");
	QRadioButton* radio_sort_suprafata = new QRadioButton("Sortare dupa suprafata");
	QRadioButton* radio_sort_tip_suprafata = new QRadioButton("Sortare dupa tip si suprafata");
	QPushButton* btn_sort;

	QVBoxLayout* ly_buttons = new QVBoxLayout;

	QPushButton* btn_lista_notificare;
	QPushButton* btn_lista_read_only;

	QPushButton* btn_reload;

	//QTableWidget* table;

	QTableView* table = new QTableView;


	void initializeGUIComponents();
	void connectSignalsSlots();
	void reload_list(vector<Locatar> all);

	void clearLayout(QLayout* layout) {
		if (layout == NULL)
			return;
		QLayoutItem* item;
		while ((item = layout->takeAt(0))) {
			if (item->layout()) {
				clearLayout(item->layout());
				delete item->layout();
			}
			if (item->widget()) {
				delete item->widget();
			}
			delete item;
		}
	}

public:
	BlocGUI(Bloc& ctr) : ctr{ ctr } {
		initializeGUIComponents();
		model = new MyTableModel{ ctr.get_all() };
		table->setModel(model);
		connectSignalsSlots();
		reload_list(ctr.get_all());
		generateButtons(ctr.raport());
	}

	void add_gui();

	void delete_gui();

	void modify_gui();

	void find_gui();

	void filter_gui();

	void sort_gui();

	void undo_gui();

	void generateButtons(unordered_map<string, DTO> myMap);
};