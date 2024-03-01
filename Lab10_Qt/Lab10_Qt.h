#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lab10_Qt.h"

class Lab10_Qt : public QMainWindow
{
    Q_OBJECT

public:
    Lab10_Qt(QWidget *parent = nullptr);
    ~Lab10_Qt();

private:
    Ui::Lab10_QtClass ui;
};
