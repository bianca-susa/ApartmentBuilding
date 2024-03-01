#include "Lab10_Qt.h"
#include "BlocGUI.h"
#include <QtWidgets/QApplication>
#include <qlabel.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Validator val;
    FileRepo rep{ "fisier.csv" };
    Bloc ctr{ rep, val };
    BlocGUI gui{ ctr };

    gui.show();
    return a.exec();
}
