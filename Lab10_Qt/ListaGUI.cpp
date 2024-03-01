#include "ListaGUI.h"
#include <qtimer.h>

using std::to_string;

void ListaGUI::init()
{
	QHBoxLayout* ly_main = new QHBoxLayout;
	setLayout(ly_main);

	QWidget* left = new QWidget;
	QFormLayout* ly_left = new QFormLayout;
	left->setLayout(ly_left);

	QWidget* form = new QWidget;
	QFormLayout* ly_form = new QFormLayout;
	form->setLayout(ly_form);

	edit_ap = new QLineEdit;
	edit_nume = new QLineEdit;

	ly_form->addRow(label_ap, edit_ap);
	ly_form->addRow(label_nume, edit_nume);

	btn_add = new QPushButton("Adauga locatar");
	ly_form->addWidget(btn_add);

	
	btn_add_random = new QPushButton("Adauga locatari random");
	ly_form->addWidget(btn_add_random);
	
	edit_nr = new QLineEdit;
	ly_form->addRow(label_nr, edit_nr);
	
	btn_empty = new QPushButton("Goleste lista");
	ly_form->addWidget(btn_empty);
	
	btn_export = new QPushButton("Exporta lista in fisier");
	ly_form->addWidget(btn_export);


	nume_fisier = new QLineEdit;
	ly_form->addRow(label_nume, nume_fisier);

	btn_close = new QPushButton("Inchide");
	ly_form->addWidget(btn_close);

	btnTableWindow = new QPushButton{ "ListaCRUDGUI" };
	ly_form->addWidget(btnTableWindow);

	btnDrawWindow = new QPushButton{ "ListaReadOnlyGUI" };
	ly_form->addWidget(btnDrawWindow);

	ly_left->addWidget(form);
	
	QWidget* right = new QWidget;
	QVBoxLayout* ly_right = new QVBoxLayout;
	right->setLayout(ly_right);

	/*int lines = 10, columns = 4;
	table = new QTableWidget{ lines, columns };

	QStringList header_list;
	header_list << "Ap" << "Nume" << "Suprafata" << "Tip";
	this->table->setHorizontalHeaderLabels(header_list);

	this->table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);*/

	list = new QListWidget();

	//ly_right->addWidget(table);
	ly_right->addWidget(list);

	ly_main->addWidget(left);
	ly_main->addWidget(right);
}


void ListaGUI::connectSignalsSlots()
{
	QObject::connect(btn_add, &QPushButton::clicked, this, &ListaGUI::add_lista);

	QObject::connect(btn_add_random, &QPushButton::clicked, this, &ListaGUI::add_random);

	QObject::connect(btn_empty, &QPushButton::clicked, this, &ListaGUI::goleste_lista);

	QObject::connect(btn_export, &QPushButton::clicked, this, &ListaGUI::export_lista);

	QObject::connect(btn_close, &QPushButton::clicked, [&]() {
		this->close();
		});

	QObject::connect(btnTableWindow, &QPushButton::clicked, this, [&]() {
		auto tableWindow = new ListaCRUDGUI{ ctr.get_all_lista_notificare_service() };
		tableWindow->show();
		});

	QObject::connect(btnDrawWindow, &QPushButton::clicked, this, [&]() {
		auto drawWindow = new ListaGUIReadOnly{ ctr.get_all_lista_notificare_service() };
		drawWindow->show();
		});
}

void ListaGUI::reloadList(const vector<Locatar>& all)
{
	/*
	this->table->clearContents();
	this->table->setRowCount(all.size());

	int line = 0;
	for (auto& l : all)
	{
		this->table->setItem(line, 0, new QTableWidgetItem(QString::number(l.get_ap())));
		this->table->setItem(line, 1, new QTableWidgetItem(QString::fromStdString(l.get_nume())));
		this->table->setItem(line, 2, new QTableWidgetItem(QString::number(l.get_suprafata())));
		this->table->setItem(line, 3, new QTableWidgetItem(QString::fromStdString(l.get_tip())));
		line++;
	}
	*/

	this->list->clear();
	for (auto& l : all)
	{
		string str;
		str.append(to_string(l.get_ap()));
		str.append(" | ");
		str.append(l.get_nume());
		str.append(" | ");
		str.append(to_string(l.get_suprafata()));
		str.append(" | ");
		str.append(l.get_tip());

		QStringList label_list;

		label_list.append(QString::fromStdString(str));

		list->addItems(label_list);
	}
}

void ListaGUI::add_lista()
{
	try
	{
		int ap = edit_ap->text().toInt();
		string nume = edit_nume->text().toStdString();

		edit_ap->clear();
		edit_nume->clear();

		ctr.add_locatar_to_lista_service(ap, nume);
		//lista.add_locatar_to_lista(ap, nume);
		reloadList(ctr.get_all_lista_notificare_service().get_all_lista_notificare());

		QMessageBox::information(this, "Info", QString::fromStdString("Locatar adaugat cu succes!"));
	}
	catch (ValidateException& v)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(v.get_err_msg()));
	}
	catch (RepoException& ex)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_err_msg()));
	}
}

void ListaGUI::add_random()
{
	int nr = edit_nr->text().toInt();

	edit_nr->clear();

	ctr.add_random_service(nr);
	//lista.add_random(ctr.get_all(),nr);
	reloadList(ctr.get_all_lista_notificare_service().get_all_lista_notificare());

	QMessageBox::information(this, "Info", QString::fromStdString("Locatari adaugati cu succes!"));
}

void ListaGUI::goleste_lista()
{
	ctr.empty_lista_service();
	//lista.empty_lista();
	reloadList(ctr.get_all_lista_notificare_service().get_all_lista_notificare());

	QMessageBox::information(this, "Info", QString::fromStdString("Locatari eliminati cu succes!"));
}

void ListaGUI::export_lista()
{
	string fisier = nume_fisier->text().toStdString();
	ctr.export_lista_service(fisier);
	//lista.export_lista(fisier);

	QMessageBox::information(this, "Info", QString::fromStdString("Lista exportata cu succes!"));
}
