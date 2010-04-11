#include <qappmainwindow.h>
#include <QApplication>
#include <qcfparser.h>
#include <QDir>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QAppMainWindow main;
	main.show();

	return a.exec();
}
