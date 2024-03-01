#pragma once
#include <QtWidgets/QApplication>
#include <QWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QListWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QFormLayout>
#include "Bloc.h"
#include <QMessageBox>
#include <string>
#include <set>
#include <vector>
#include <QDebug>
#include <QPainter>
#include <cstdlib>
#include "Observer.h"

using std::to_string;
using std::set;
using std::vector;

class ListaCRUDGUI :public QWidget, public Observer {
private:
	ListaNotificare& p;
	QTableWidget* table;
	QPushButton* btnEmpty;
	void initGUI() {
		QHBoxLayout* ly = new QHBoxLayout;
		this->setLayout(ly);
		table = new QTableWidget;
		btnEmpty = new QPushButton{ "Goleste playlist" };
		ly->addWidget(table);
		ly->addWidget(btnEmpty);
		setAttribute(Qt::WA_DeleteOnClose);
		p.add_observer(this);
	};
	void reloadTableData(const vector<Locatar>& all) {
		this->table->setColumnCount(4);
		this->table->setRowCount(all.size());
		for (int i = 0; i < all.size(); i++) {
			table->setItem(i, 0, new QTableWidgetItem(QString::number(all[i].get_ap())));
			table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(all[i].get_nume())));
			table->setItem(i, 2, new QTableWidgetItem(QString::number(all[i].get_suprafata())));
			table->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(all[i].get_tip())));
		}

	};

	void connectSignalsSlots() {
		p.add_observer(this);
		QObject::connect(btnEmpty, &QPushButton::clicked, [&]() {
			p.empty_lista();
			reloadTableData(p.get_all_lista_notificare());
			});
	}


public:
	ListaCRUDGUI(ListaNotificare& p) :p{ p } {
		initGUI();
		connectSignalsSlots();
		reloadTableData(p.get_all_lista_notificare());
		this->update();
	};

	void update() override {
		this->reloadTableData(p.get_all_lista_notificare());
	}
	~ListaCRUDGUI() {
		p.remove_observer(this);
	}

};