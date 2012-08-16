#include "angletester.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AngleTester w;
	w.show();
	return a.exec();
}
