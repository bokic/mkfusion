#include <QApplication>
#include "QAppMainWindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QAppMainWindow main;
	main.show();
	return app.exec();
}
