#include <QtWidgets/Qapplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include <qstring.h>
#include "Bloc.h"
#include "ListaGUI.h"

class FilterGUI : public QWidget
{
private:
	Bloc& ctr;
	QString text;

	QLabel* label = new QLabel(text);
	QLineEdit* edit;

	QPushButton* btn;

	QTableWidget* table;

	void init();
	void connectSignalSlots();
	void reload_list(vector<Locatar> all);

public:

	FilterGUI(Bloc& ctr, QString text) : ctr{ ctr }, text{ text }
	{
		init();
		connectSignalSlots();
	}

	void filtergui();
};
