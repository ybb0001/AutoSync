#include "AutoSync.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AutoSync w;
	w.show();
	return a.exec();
}
