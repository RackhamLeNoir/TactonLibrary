#include "tactondebug.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TactonDebug w;
	w.show();
	w.raise();
	return a.exec();
}
