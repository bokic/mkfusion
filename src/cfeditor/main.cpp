#include <qappmainwindow.h>
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QAppMainWindow main;
	main.show();

	return a.exec();
}
