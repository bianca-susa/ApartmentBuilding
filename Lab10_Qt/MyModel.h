#pragma once
#include <QAbstractTableModel>
#include <QBrush>
#include <Qt>
#include <qfont.h>
#include "Locatar.h"
#include <vector>
#include <qdebug.h>
using std::vector;


class MyTableModel :public QAbstractTableModel {
	std::vector<Locatar> all;
public:
	MyTableModel(const std::vector<Locatar>& all) :all{ all } {
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return all.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}
	//Returns the data stored under the given role for the item referred to by the index.
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		qDebug() << "row:" << index.row() << " col:" << index.column() << " role" << role;
		//qDebug() << index.data(role);

		if (role == Qt::ForegroundRole) {
			auto l = this->all[index.row()];
			if (l.get_tip() == "2 camere") {
				return QBrush(Qt::darkRed);
			}
		}
		if (role == Qt::FontRole) {
			QFont f;
			f.setItalic(index.row() % 5 == 1);
			f.setBold(index.row() % 5 == 1);
			return f;
		}
		if (role == Qt::BackgroundRole) {

			int row = index.row();
			QModelIndex i = index.sibling(index.row(), 1);
			if (i.data().toString() == "2") {
				QRadialGradient radialGrad(QPointF(50, 20), 50);
				radialGrad.setColorAt(0, Qt::red);
				radialGrad.setColorAt(1, Qt::yellow);
				QBrush bg(radialGrad);
				return bg;
			}
		}

		if (role == Qt::DisplayRole) {

			Locatar p = all[index.row()];
			if (index.column() == 0) {
				return QString::number(p.get_ap());
			}
			else if (index.column() == 1) {
				return QString::fromStdString(p.get_nume());
			}
			else if (index.column() == 2) {
				return QString::number(p.get_suprafata());
			}
			else if (index.column() == 3) {
				return QString::fromStdString(p.get_tip());
			}
		}

		return QVariant{};
	}

	void set(vector<Locatar> list) {
		this-> all= list;
		auto topLeft = createIndex(0, 0);
		auto bottomR = createIndex(rowCount(), columnCount());
		emit dataChanged(topLeft, bottomR);
	}

	Qt::ItemFlags flags(const QModelIndex& /*index*/) const {
		return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role) const
	{
		if (role == Qt::DisplayRole)
		{
			if (orientation == Qt::Horizontal) {
				switch (section)
				{
				case 0:
					return tr("Apartament");
				case 1:
					return tr("Nume");
				case 2:
					return tr("Suprafata");
				case 3:
					return tr("Tip");
				default:
					return QString("");
				}
			}
		}
		return QVariant();
	}
};
