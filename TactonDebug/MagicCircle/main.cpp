#include "magiccircle.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MagicCircle w;
	w.show();
	return a.exec();
}
