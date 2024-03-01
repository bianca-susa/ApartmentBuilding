#include "FilterGUI.h"

void FilterGUI::init()
{

	QHBoxLayout* ly_main = new QHBoxLayout;
	setLayout(ly_main);

	QWidget* main = new QWidget;
	QFormLayout* ly = new QFormLayout;
	main->setLayout(ly);

	edit = new QLineEdit;
	ly->addRow(label, edit);

	btn = new QPushButton("Filtreaza");
	ly->addWidget(btn);

	int lines = 10;
	int columns = 4;
	this->table = new QTableWidget{ lines, columns };

	QStringList header_list;
	header_list << "Ap" << "Nume" << "Suprafata" << "Tip";
	this->table->setHorizontalHeaderLabels(header_list);

	this->table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	ly_main->addWidget(main);
	ly_main->addWidget(table);
}

void FilterGUI::reload_list(vector<Locatar> all)
{
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
}

void FilterGUI::connectSignalSlots()
{
	QObject::connect(btn, &QPushButton::clicked, this, &FilterGUI::filtergui);
}

void FilterGUI::filtergui()
{
	vector<Locatar> filtered_list;

	try
	{
		if (text == "Suprafata")
		{
			int s = edit->text().toInt();
			ctr.filter_suprafata(s, filtered_list);
			reload_list(filtered_list);
		}

		if (text == "Tip")
		{
			string t = edit->text().toStdString();
			ctr.filter_tip(t, filtered_list);
			reload_list(filtered_list);
		}
	}
	catch (ValidateException& v)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(v.get_err_msg()));
	}
}