#include "BlocGUI.h"

using std::to_string;



void BlocGUI::initializeGUIComponents()
{
	QHBoxLayout* ly_main = new QHBoxLayout;
	setLayout(ly_main);

	//ly_main->addLayout(ly_buttons);

	QWidget* left = new QWidget;
	QVBoxLayout* ly_left = new QVBoxLayout;
	left->setLayout(ly_left);

	QWidget* form = new QWidget;
	QFormLayout* ly_form = new QFormLayout;
	form->setLayout(ly_form);

	edit_ap = new QLineEdit;
	edit_nume = new QLineEdit;
	edit_suprafata = new QLineEdit;
	edit_tip = new QLineEdit;

	ly_form->addRow(label_ap, edit_ap);
	ly_form->addRow(label_nume, edit_nume);
	ly_form->addRow(label_suprafata, edit_suprafata);
	ly_form->addRow(label_tip, edit_tip);

	btn_reload = new QPushButton("Afiseaza lista de locatari");
	ly_form->addWidget(btn_reload);

	btn_add = new QPushButton("Adauga locatar");
	ly_form->addWidget(btn_add);

	btn_delete = new QPushButton("Sterge locatar");
	ly_form->addWidget(btn_delete);

	btn_find = new QPushButton("Cauta locatar");
	ly_form->addWidget(btn_find);
	
	btn_modify = new QPushButton("Modifica locatar");
	ly_form->addWidget(btn_modify);

	btn_undo = new QPushButton("Undo");

	edit_new_ap = new QLineEdit;
	edit_new_nume = new QLineEdit;
	edit_new_suprafata = new QLineEdit;
	edit_new_tip = new QLineEdit;

	ly_form->addRow(label_new_ap, edit_new_ap);
	ly_form->addRow(label_new_nume, edit_new_nume);
	ly_form->addRow(label_new_suprafata, edit_new_suprafata);
	ly_form->addRow(label_new_tip, edit_new_tip);

	ly_form->addWidget(btn_undo);

	QVBoxLayout* ly_radio_box = new QVBoxLayout;
	group_box_filter->setLayout(ly_radio_box);
	ly_radio_box->addWidget(radio_filter_tip);
	ly_radio_box->addWidget(radio_filter_suprafata);

	btn_filter = new QPushButton("Filtrare");
	ly_radio_box->addWidget(btn_filter);

	QVBoxLayout* ly_radio_box_sort = new QVBoxLayout;
	group_box_sort->setLayout(ly_radio_box_sort);
	ly_radio_box_sort->addWidget(radio_sort_nume);
	ly_radio_box_sort->addWidget(radio_sort_suprafata);
	ly_radio_box_sort->addWidget(radio_sort_tip_suprafata);

	btn_sort = new QPushButton("Sortare");
	ly_radio_box_sort->addWidget(btn_sort);

	btn_lista_notificare = new QPushButton("Gestiune lista de notificare");
	ly_form->addWidget(btn_lista_notificare);
	
	ly_left->addWidget(form);

	ly_left->addWidget(group_box_filter);
	ly_left->addWidget(group_box_sort);

	btn_close = new QPushButton("Inchide");
	ly_left->addWidget(btn_close);

	QWidget* right = new QWidget;
	QHBoxLayout* ly_right = new QHBoxLayout;
	right->setLayout(ly_right);

	ly_right->addWidget(table);
	ly_right->addLayout(ly_buttons);

	ly_main->addWidget(left);
	ly_main->addWidget(right);
}


void BlocGUI::reload_list(vector<Locatar> all) {
	model = new MyTableModel{ ctr.get_all() };
	table->setModel(model);
	this->model->set(all);
}

void BlocGUI::connectSignalsSlots()
{
	QObject::connect(btn_add, &QPushButton::clicked, this, &BlocGUI::add_gui);

	QObject::connect(btn_delete, &QPushButton::clicked, this, &BlocGUI::delete_gui);

	QObject::connect(btn_modify, &QPushButton::clicked, this, &BlocGUI::modify_gui);

	QObject::connect(btn_find, &QPushButton::clicked, this, &BlocGUI::find_gui);

	QObject::connect(btn_filter, &QPushButton::clicked, this, &BlocGUI::filter_gui);

	QObject::connect(btn_sort, &QPushButton::clicked, this, &BlocGUI::sort_gui);

	QObject::connect(btn_undo, &QPushButton::clicked, this, &BlocGUI::undo_gui);

	QObject::connect(btn_lista_notificare, &QPushButton::clicked, [&]()
		{
			auto lista_gui = new ListaGUI(ctr);
			lista_gui->show();
		});


	QObject::connect(btn_reload, &QPushButton::clicked, [&]() {
		reload_list(ctr.get_all());
		});

	QObject::connect(btn_close, &QPushButton::clicked, [&]()
		{
			this->close();
		});
}

void BlocGUI::add_gui()
{
	try
	{
		clearLayout(ly_buttons);
		int ap = edit_ap->text().toInt();
		string nume = edit_nume->text().toStdString();
		int suprafata = edit_suprafata->text().toInt();
		string tip = edit_tip->text().toStdString();

		edit_ap->clear();
		edit_nume->clear();
		edit_suprafata->clear();
		edit_tip->clear();

		ctr.add_locatar(ap, nume, suprafata, tip);
		

		QMessageBox::information(this, "Info", QString::fromStdString("Locatar adaugat cu succes!"));
		generateButtons(ctr.raport());
		//model = new MyTableModel{ ctr.get_all() };
		//table->setModel(model);
		reload_list(ctr.get_all());
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

void BlocGUI::delete_gui()
{
	try
	{
		clearLayout(ly_buttons);
		int ap = edit_ap->text().toInt();
		string nume = edit_nume->text().toStdString();

		edit_ap->clear();
		edit_nume->clear();
		edit_suprafata->clear();
		edit_tip->clear();

		ctr.delete_locatar(ap, nume);
		reload_list(ctr.get_all());

		QMessageBox::information(this, "Info", QString::fromStdString("Locatar sters cu succes!"));
		generateButtons(ctr.raport());
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

void BlocGUI::modify_gui()
{
	try
	{
		clearLayout(ly_buttons);
		int ap = edit_ap->text().toInt();
		string nume = edit_nume->text().toStdString();

		edit_ap->clear();
		edit_nume->clear();
		edit_suprafata->clear();
		edit_tip->clear();

		int new_ap = edit_new_ap->text().toInt();
		string new_nume = edit_new_nume->text().toStdString();
		int new_suprafata = edit_new_suprafata->text().toInt();
		string new_tip = edit_new_tip->text().toStdString();

		edit_new_ap->clear();
		edit_new_nume->clear();
		edit_new_suprafata->clear();
		edit_new_tip->clear();

		ctr.modify_locatar(ap, nume, new_ap, new_nume, new_suprafata, new_tip);
		reload_list(ctr.get_all());

		QMessageBox::information(this, "Info", QString::fromStdString("Locatar modificat cu succes!"));
		generateButtons(ctr.raport());
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

void BlocGUI::find_gui()
{
	try
	{
		int ap = edit_ap->text().toInt();
		string nume = edit_nume->text().toStdString();

		edit_ap->clear();
		edit_nume->clear();
		edit_suprafata->clear();
		edit_tip->clear();

		int poz = ctr.find_locatar(ap, nume);
		//reload_list(ctr.get_all());

		if (poz != -1)
		{
			Locatar l = ctr.get_all()[poz];
			string loc;
			loc.append("Locatarul este : ");
			loc.append(to_string(l.get_ap()));
			loc.append(" | ");
			loc.append(l.get_nume());
			loc.append(" | ");
			loc.append(to_string(l.get_suprafata()));
			loc.append(" | ");
			loc.append(l.get_tip());

			QMessageBox::information(this, "Info", QString::fromStdString(loc));
		}
		else QMessageBox::warning(this, "Warning", QString::fromStdString("Locatarul nu a fost gasit!"));
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

void BlocGUI::filter_gui()
{
	try
	{

		if (radio_filter_tip->isChecked())
		{
			string tip = "Tip";
			QString t = QString::fromStdString(tip);
			auto f = new FilterGUI(ctr, t);
			f->show();
		}
		else
		{
			if (radio_filter_suprafata->isChecked())
			{
				auto f = new FilterGUI(ctr, "Suprafata");
				f->show();
			}
			else
			{
				QMessageBox::warning(this, "Warning", QString::fromStdString("Alegeti un tip de filtrare!"));
			}
		}
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

void BlocGUI::sort_gui()
{
	try
	{
		vector<Locatar> sorted_list;

		if (radio_sort_nume->isChecked())
		{
			sorted_list = ctr.sort_nume_service();
		}
		else
		{
			if (radio_sort_suprafata->isChecked())
			{
				sorted_list = ctr.sort_suprafata_service();
			}
			else
			{
				if (radio_sort_tip_suprafata->isChecked())
				{
					sorted_list = ctr.sort_tip_suprafata_service();
				}
				else
				{
					QMessageBox::warning(this, "Warning", QString::fromStdString("Alegeti un tip de sortare!"));
				}
			}
		}
		reload_list(sorted_list);
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

void BlocGUI::undo_gui()
{
	try
	{
		ctr.undo();
		reload_list(ctr.get_all());
	}
	catch (RepoException& ex)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.get_err_msg()));
	}
}

void BlocGUI::generateButtons(unordered_map<string, DTO> myMap) {
	for (auto m : myMap) {
		auto btn = new QPushButton{ QString::fromStdString(m.second.get_tip()) };
		int nr = m.second.get_count();
		this->ly_buttons->addWidget(btn);
		QObject::connect(btn, &QPushButton::clicked, [this, btn, nr]() {
			QMessageBox::information(nullptr, "Info", QString::number(nr));
			});
	}
}