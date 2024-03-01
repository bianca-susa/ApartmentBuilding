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

class ListaGUIReadOnly :public QWidget, public Observer {
private:
	ListaNotificare& lista;
	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		int x = 0;
		int y = 0;
		for (auto l : lista.get_all_lista_notificare()) {
			x = rand() % 550 + 1;
			y = rand() % 256 + 1;
			qDebug() << x << " " << y;
			QRectF target(x, y, 100, 94);
			QRectF source(0, 0, 750, 720);
			QImage image("image3");

			p.drawImage(target, image, source);

			x += 60;

		}
	}

	void update() override {
		repaint();
	};
	~ListaGUIReadOnly() {
		lista.remove_observer(this);
	}

public:
	ListaGUIReadOnly(ListaNotificare& lista) :lista{ lista } {
		lista.add_observer(this);
	};

};
