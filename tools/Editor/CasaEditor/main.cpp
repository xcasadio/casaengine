#include "CasaEditor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CasaEditor w;
	w.show();
	return a.exec();
}
