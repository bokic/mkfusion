#include <QApplication>
#include "parsertest1.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CFTest1 mainWindow;
    mainWindow.show();
    return a.exec();
}
